// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <math/TellusimMath.h>
#include <math/TellusimSimd.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>
#include <parallel/TellusimPrefixScan.h>
#include <parallel/TellusimRadixSort.h>

#include "panel.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using Tellusim::float16x4_t;
	using Tellusim::float32x4_t;
	using Tellusim::float16x8_t;
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create window
	Window window(app.getPlatform(), app.getDevice());
	if(!window || !window.setSize(app.getWidth(), app.getHeight())) return 1;
	if(!window.create("07 Hello Splatting") || !window.setHidden(false)) return 1;
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(key == Window::KeyEsc) window.stop();
	});
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// declarations
	#include "main.h"
	
	// splatting parameters
	constexpr uint32_t max_width = 8192;
	constexpr uint32_t max_height = 4096;
	constexpr uint32_t max_overdraw = 8;
	constexpr uint32_t group_size = 64;
	constexpr uint32_t group_width = 32;
	constexpr uint32_t group_height = 16;
	
	constexpr uint32_t max_tiles = max_width * max_height / (group_width * group_height);
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;			// projection matrix
		Matrix4x4f modelview;			// modelview matrix
		Vector4f camera;				// camera position
		uint32_t tiles_width;			// tiles width
		uint32_t tiles_height;			// tiles height
		uint32_t surface_width;			// surface width
		uint32_t surface_height;		// surface height
		uint32_t max_gaussians;			// maximum number of Gaussians
		uint32_t num_gaussians;			// number of Gaussians
		uint32_t num_tiles;				// number of tiles
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// device info
	TS_LOGF(Message, "Device: %s\n", device.getName().get());
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// load Gaussians
	Array<Gaussian> gaussians;
	{
		using Tellusim::exp;
		
		TS_LOG(Verbose, "Loading Gaussians\n");
		
		Mesh mesh;
		if(!mesh.load("splats.ply") || !mesh.getNumGeometries()) return 1;
		
		// position attribute
		MeshGeometry geometry = mesh.getGeometry(0);
		MeshAttribute position_attribute = geometry.getAttribute(MeshAttribute::TypePosition);
		if(!position_attribute || position_attribute.getFormat() != FormatRGBf32) return 1;
		const Vector3f *position_data = (const Vector3f*)position_attribute.getData();
		
		// spatial attributes
		#define GET_ATTRIBUTE(NAME) \
			uint32_t NAME ## _index = geometry.findAttribute(#NAME); \
			if(NAME ## _index == Maxu32) return 1; \
			MeshAttribute NAME ## _attribute = geometry.getAttribute(NAME ## _index); \
			if(NAME ## _attribute.getSize() != position_attribute.getSize()) return 1; \
			if(NAME ## _attribute.getFormat() != FormatRf32) return 1; \
			const float32_t *NAME ## _data = (const float32_t*)NAME ## _attribute.getData();
		
		GET_ATTRIBUTE(scale_0)
		GET_ATTRIBUTE(scale_1)
		GET_ATTRIBUTE(scale_2)
		GET_ATTRIBUTE(opacity)
		GET_ATTRIBUTE(rot_0)
		GET_ATTRIBUTE(rot_1)
		GET_ATTRIBUTE(rot_2)
		GET_ATTRIBUTE(rot_3)
		
		// harmonic attributes
		GET_ATTRIBUTE(f_dc_0)
		GET_ATTRIBUTE(f_dc_1)
		GET_ATTRIBUTE(f_dc_2)
		const float32_t *harmonics_data[45];
		for(uint32_t i = 0; i < TS_COUNTOF(harmonics_data); i++) {
			uint32_t index = geometry.findAttribute(String::format("f_rest_%u", i).get());
			if(index == Maxu32) return 1;
			MeshAttribute attribute = geometry.getAttribute(index);
			if(attribute.getSize() != attribute.getSize()) return 1;
			if(attribute.getFormat() != FormatRf32) return 1;
			harmonics_data[i] = (const float32_t*)attribute.getData();
		}
		
		TS_LOG(Verbose, "Creating Gaussians\n");
		
		// create Gaussians
		float32x4_t harmonics[16];
		gaussians.reserve(position_attribute.getSize());
		for(uint32_t i = 0; i < position_attribute.getSize(); i++) {
			
			// check opacity
			float32_t opacity = 1.0f / (1.0f + exp(-opacity_data[i]));
			if(opacity < 8.0f / 255.0f) continue;
			
			// create gaussian
			Gaussian &gaussian = gaussians.append();
			
			// copy position
			gaussian.position.set(position_data[i], 1.0f);
			
			// pack rotation, scale, and opacity
			Vector4f scale = Vector4f(exp(scale_0_data[i]), exp(scale_1_data[i]), exp(scale_2_data[i]), opacity);
			Quaternionf rotation = normalize(Quaternionf(rot_1_data[i], rot_2_data[i], rot_3_data[i], rot_0_data[i]));
			gaussian.rotation_scale = float16x8_t(float16x4_t(float32x4_t(rotation.q)), float16x4_t(float32x4_t(scale.v)));
			
			// copy harmonics
			harmonics[0].x = f_dc_0_data[i];
			harmonics[0].y = f_dc_1_data[i];
			harmonics[0].z = f_dc_2_data[i];
			for(uint32_t j = 1, k = 0; j < 16; j++, k++) {
				harmonics[j].x = harmonics_data[k +  0][i];
				harmonics[j].y = harmonics_data[k + 15][i];
				harmonics[j].z = harmonics_data[k + 30][i];
			}
			
			// don't waste alpha channel
			harmonics[0].w = harmonics[14].x;
			harmonics[1].w = harmonics[14].y;
			harmonics[2].w = harmonics[14].z;
			harmonics[3].w = harmonics[15].x;
			harmonics[4].w = harmonics[15].y;
			harmonics[5].w = harmonics[15].z;
			
			// float32_t to float16_t
			for(uint32_t j = 0, k = 0; j < 7; j++, k += 2) {
				gaussian.harmonics[j] = float16x8_t(float16x4_t(harmonics[k + 0]), float16x4_t(harmonics[k + 1]));
			}
		}
		
		TS_LOGF(Verbose, "Done %u %u %s %s\n", gaussians.size(), position_attribute.getSize(), String::fromBytes(sizeof(Gaussian)).get(), String::fromBytes(gaussians.bytes()).get());
	}
	
	// maximum number of Gaussians
	// each Gaussian can be present in more than one tile
	uint32_t max_gaussians = TS_ALIGN4(gaussians.size()) * max_overdraw;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create clear kernel
	// clears counter buffer
	Kernel clear_kernel = device.createKernel().setUniforms(1).setStorages(1, BindFlagFixed);
	if(!clear_kernel.loadShaderGLSL("main.shader", "CLEAR_SHADER=1; GROUP_SIZE=%u", group_size)) return 1;
	if(!clear_kernel.create()) return 1;
	
	// create Gaussian kernel
	// creates Gaussian parameters and counts the number of Gaussians per tile
	Kernel gaussian_kernel = device.createKernel().setUniforms(1).setStorages(2, BindFlagFixed);
	if(!gaussian_kernel.loadShaderGLSL("main.shader", "GAUSSIAN_SHADER=1; GROUP_SIZE=%u; GROUP_WIDTH=%u; GROUP_HEIGHT=%u", group_size, group_width, group_height)) return 1;
	if(!gaussian_kernel.create()) return 1;
	
	// create align kernel
	// aligns counter buffer
	Kernel align_kernel = device.createKernel().setUniforms(1).setStorages(1, BindFlagFixed);
	if(!align_kernel.loadShaderGLSL("main.shader", "ALIGN_SHADER=1; GROUP_SIZE=%u", group_size)) return 1;
	if(!align_kernel.create()) return 1;
	
	// create dispatch kernel
	// creates dispatch arguments for scatter kernel and radix sort
	Kernel dispatch_kernel = device.createKernel().setUniforms(1).setStorages(2, BindFlagFixed);
	if(!dispatch_kernel.loadShaderGLSL("main.shader", "DISPATCH_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!dispatch_kernel.create()) return 1;
	
	// create scatter kernel
	// creates Gaussian depth and indices to each tile
	Kernel scatter_kernel = device.createKernel().setUniforms(1).setStorages(3, BindFlagFixed);
	if(!scatter_kernel.loadShaderGLSL("main.shader", "SCATTER_SHADER=1; GROUP_SIZE=%u; GROUP_WIDTH=%u; GROUP_HEIGHT=%u", group_size, group_width, group_height)) return 1;
	if(!scatter_kernel.create()) return 1;
	
	// create Splatting kernel
	// rasterizes Gaussians
	Kernel splatting_kernel = device.createKernel().setUniforms(1).setStorages(3, BindFlagFixed).setSurfaces(1);
	if(!splatting_kernel.loadShaderGLSL("main.shader", "SPLATTING_SHADER=1; GROUP_WIDTH=%u; GROUP_HEIGHT=%u", group_width, group_height)) return 1;
	if(!splatting_kernel.create()) return 1;
	
	// create radix sort
	RadixSort radix_sort;
	PrefixScan prefix_scan;
	if(!radix_sort.create(device, RadixSort::FlagsAll, prefix_scan, 1024 * 8, 256, 1024 * 8)) return 1;
	
	// create Gaussians buffer
	Buffer gaussians_buffer = device.createBuffer(Buffer::FlagStorage, gaussians.get(), gaussians.bytes());
	if(!gaussians) return 1;
	
	// create counter buffer
	// the number of Gaussians per tile, the last element is the number of visible Gaussians
	Buffer count_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * (max_tiles * 2 + 4));
	if(!count_buffer) return 1;
	
	// create dispatch buffer
	// indirect dispatch arguments for radix sort, the last argument is scatter kernel dispatch argument
	Buffer dispatch_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagIndirect, sizeof(Compute::DispatchIndirect) * (max_tiles + 1));
	if(!dispatch_buffer) return 1;
	
	// create order buffer
	// visible Gaussian depth and indices
	Buffer order_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * max_gaussians * 2);
	if(!order_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	if(!target) return 1;
	
	// create queries
	Query gaussian_query;
	Query scatter_query;
	Query radix_query;
	Query splatting_query;
	if(device.hasQuery(Query::TypeTime)) {
		gaussian_query = device.createQuery(Query::TypeTime);
		scatter_query = device.createQuery(Query::TypeTime);
		radix_query = device.createQuery(Query::TypeTime);
		splatting_query = device.createQuery(Query::TypeTime);
		if(!gaussian_query || !scatter_query || !radix_query || !splatting_query) return 1;
	}
	
	// create panel
	Panel panel(device);
	
	// compute surface
	Texture surface;
	
	// default position
	float32_t tx = -0.41f;
	float32_t ty = 0.16f;
	float32_t tz = -2.0f;
	float32_t rx = 230.0f;
	float32_t ry = 0.0f;
	float32_t fov = 35.0f;
	
	// main loop
	window.run([&]() {
		
		Window::update();
		
		// render window
		if(!window.render()) return false;
		
		// get queries
		if(gaussian_query && gaussian_query.isAvailable()) {
			String gaussian_time = String::fromTime(gaussian_query.getTime());
			String scatter_time = String::fromTime(scatter_query.getTime());
			String radix_time = String::fromTime(radix_query.getTime());
			String splatting_time = String::fromTime(splatting_query.getTime());
			panel.setInfo(String::format("\nGaussian: %s\nScatter: %s\nRadix: %s\nSplatting: %s", gaussian_time.get(), scatter_time.get(), radix_time.get(), splatting_time.get()));
		}
		
		// update panel
		panel.update(window, device, target);
		
		// position control
		bool changed = false;
		float32_t ifps = 1.0f / panel.getFps();
		if(window.getKeyboardKey('q')) { tx += ifps * 0.5f; changed = true; }
		if(window.getKeyboardKey('a')) { tx -= ifps * 0.5f; changed = true; }
		if(window.getKeyboardKey('w')) { ty += ifps * 0.5f; changed = true; }
		if(window.getKeyboardKey('s')) { ty -= ifps * 0.5f; changed = true; }
		if(window.getKeyboardKey('e')) { tz += ifps * 0.5f; changed = true; }
		if(window.getKeyboardKey('d')) { tz -= ifps * 0.5f; changed = true; }
		if(window.getKeyboardKey('r')) { rx += ifps * 10.0f; changed = true; }
		if(window.getKeyboardKey('f')) { rx -= ifps * 10.0f; changed = true; }
		if(window.getKeyboardKey('t')) { ry += ifps * 10.0f; changed = true; }
		if(window.getKeyboardKey('g')) { ry -= ifps * 10.0f; changed = true; }
		if(window.getKeyboardKey('y')) { fov += ifps * 10.0f; changed = true; }
		if(window.getKeyboardKey('h')) { fov -= ifps * 10.0f; changed = true; }
		if(changed) TS_LOGF(Message, "%.2f %.2f %.2f %.2f %.2f %.2f\n", tx, ty, tz, rx, ry, fov);
		
		// time control
		float32_t time = (float32_t)Time::seconds();
		if(window.getKeyboardKey('1')) time = 0.0f;
		
		// create surface
		uint32_t width = min(window.getWidth(), max_width);
		uint32_t height = min(window.getHeight(), max_height);
		#if _ANDROID || _IOS
			width /= 2;
			height /= 2;
		#endif
		if(window.getKeyboardKey('2')) { width = 1600; height = 900; }
		if(window.getKeyboardKey('3')) { width = 1920; height = 1080; }
		if(window.getKeyboardKey('4')) { width = 2560; height = 1440; }
		if(window.getKeyboardKey('5')) { width = 3840; height = 2160; }
		if(!surface || surface.getWidth() != width || surface.getHeight() != height) {
			device.releaseTexture(surface);
			surface = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagSurface);
			if(!surface) return false;
		}
		
		{
			Compute compute = device.createCompute();
			
			// number of tiles
			uint32_t tiles_width = udiv(width, group_width);
			uint32_t tiles_height = udiv(height, group_height);
			uint32_t num_tiles = TS_ALIGN4(tiles_width * tiles_height);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(Matrix4x3f::rotateZ(time * 8.0f) * Vector3f(Vector2f(Tellusim::sin(time) * 0.4f + 1.6f), 1.2f), 1.0f);
			common_parameters.projection = Matrix4x4f::perspective(fov, (float32_t)surface.getWidth() / surface.getHeight(), 0.1f, true);
			common_parameters.modelview = Matrix4x4f::lookAt(common_parameters.camera.xyz, Vector3f::zero, Vector3f::oneZ);
			common_parameters.tiles_width = tiles_width;
			common_parameters.tiles_height = tiles_height;
			common_parameters.surface_width = width;
			common_parameters.surface_height = height;
			common_parameters.max_gaussians = max_gaussians;
			common_parameters.num_gaussians = gaussians.size();
			common_parameters.num_tiles = num_tiles;
			
			// transform scene
			Matrix4x4f transform = Matrix4x4f::translate(-tx, -ty, -tz) * Matrix4x4f::rotateY(ry) * Matrix4x4f::rotateX(rx);
			common_parameters.modelview *= transform;
			
			common_parameters.camera = inverse(transform) * common_parameters.camera;
			
			// begin query
			if(gaussian_query) compute.beginQuery(gaussian_query);
				
				// dispatch clear kernel
				compute.setKernel(clear_kernel);
				compute.setUniform(0, num_tiles);
				compute.setStorageBuffer(0, count_buffer);
				compute.dispatch(num_tiles);
				compute.barrier(count_buffer);
				
				// dispatch Gaussian kernel
				compute.setKernel(gaussian_kernel);
				compute.setUniform(0, common_parameters);
				compute.setStorageBuffers(0, {
					gaussians_buffer,
					count_buffer,
				});
				compute.dispatch(gaussians.size());
				compute.barrier({
					gaussians_buffer,
					count_buffer,
				});
				
				// dispatch align kernel
				compute.setKernel(align_kernel);
				compute.setUniform(0, num_tiles);
				compute.setStorageBuffer(0, count_buffer);
				compute.dispatch(num_tiles);
				compute.barrier(count_buffer);
				
				// dispatch prefix scan
				// creates offsets to copy Gaussian index and depth parameters
				prefix_scan.dispatch(compute, count_buffer, 0, num_tiles);
				
				// dispatch kernel
				compute.setKernel(dispatch_kernel);
				compute.setUniform(0, common_parameters);
				compute.setStorageBuffers(0, {
					count_buffer,
					dispatch_buffer,
				});
				compute.dispatch(num_tiles);
				compute.barrier({
					count_buffer,
					dispatch_buffer,
				});
				
			// end query
			if(gaussian_query) compute.endQuery(gaussian_query);
			
			// begin query
			if(scatter_query) compute.beginQuery(scatter_query);
				
				// dispatch scatter kernel
				compute.setKernel(scatter_kernel);
				compute.setUniform(0, common_parameters);
				compute.setStorageBuffers(0, {
					gaussians_buffer,
					count_buffer,
					order_buffer,
				});
				compute.setIndirectBuffer(dispatch_buffer, sizeof(Compute::DispatchIndirect) * num_tiles);
				compute.dispatchIndirect();
				compute.barrier({
					count_buffer,
					order_buffer,
				});
				
			// end query
			if(scatter_query) compute.endQuery(scatter_query);
			
			// begin query
			if(radix_query) compute.beginQuery(radix_query);
				
				// dispatch radix sort
				// sorts Gaussians in each tile
				radix_sort.dispatchIndirect(compute, order_buffer, num_tiles, dispatch_buffer, 0, RadixSort::FlagNone, 24);
				
			// end query
			if(radix_query) compute.endQuery(radix_query);
			
			// begin query
			if(splatting_query) compute.beginQuery(splatting_query);
				
				// dispatch Splatting kernel
				compute.setKernel(splatting_kernel);
				compute.setUniform(0, common_parameters);
				compute.setStorageBuffers(0, {
					gaussians_buffer,
					count_buffer,
					order_buffer,
				});
				compute.setSurfaceTexture(0, surface);
				compute.dispatch(width / 4, height / 2);
				compute.barrier(surface);
				
			// end query
			if(splatting_query) compute.endQuery(splatting_query);
		}
		
		// flush surface
		device.flushTexture(surface);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw surface
			command.setPipeline(pipeline);
			command.setTexture(0, surface);
			command.drawArrays(3);
			
			// draw panel
			panel.draw(command, target);
		}
		target.end();
		
		// present window
		if(!window.present()) return false;
		
		// check errors
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

/*
 */
#if _ANDROID
	#include <system/TellusimAndroid.h>
	TS_DECLARE_ANDROID_NATIVE_ACTIVITY
#endif
