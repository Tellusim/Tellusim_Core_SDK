// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimRandom.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>
#include <parallel/TellusimPrefixScan.h>
#include <parallel/TellusimRadixSort.h>
#include <parallel/TellusimSpatialTree.h>
#include <graphics/TellusimMeshModel.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Lights", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of lights
	#if _ANDROID || _IOS
		constexpr uint32_t num_lights = 1024 * 8;
	#else
		constexpr uint32_t num_lights = 1024 * 16;
	#endif
	constexpr uint32_t grid_size[4] = { 16, 16, 128, 256 };
	
	// structures
	struct Vertex {
		float32_t position[3];
		float32_t normal[3];
	};
	
	struct AnimationParameters {
		Vector4f bound_min;
		Vector4f bound_max;
		uint32_t num_lights;
		float32_t ifps;
	};
	
	struct LightParameters {
		Matrix4x4f iprojection;
		Vector4u grid_size;
		float32_t znear;
		float32_t zfar;
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Vector4f window_size;
		Vector4u grid_size;
		Vector4f camera;
		float32_t znear;
		float32_t zfar;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// shader cache
	Shader::setCache("main.cache");
	
	// create target
	Target target = device.createTarget(window);
	
	// create animation kernel
	Kernel animation_kernel = device.createKernel().setUniforms(1).setStorages(3);
	if(!animation_kernel.loadShaderGLSL("main.shader", "COMPUTE_ANIMATION_SHADER=1")) return 1;
	if(!animation_kernel.create()) return 1;
	
	// create light kernel
	Kernel light_kernel = device.createKernel().setUniforms(1).setStorages(4);
	if(!light_kernel.loadShaderGLSL("main.shader", "COMPUTE_LIGHT_SHADER=1")) return 1;
	if(!light_kernel.create()) return 1;
	
	// create depth pipeline
	Pipeline depth_pipeline = device.createPipeline();
	depth_pipeline.setUniformMask(0, Shader::MaskVertex);
	depth_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	depth_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	depth_pipeline.setCullMode(target.isFlipped() ? Pipeline::CullModeFront : Pipeline::CullModeBack);
	depth_pipeline.setMultisample(window.getMultisample());
	depth_pipeline.setColorFormat(window.getColorFormat());
	depth_pipeline.setDepthFormat(window.getDepthFormat());
	depth_pipeline.setDepthFunc(Pipeline::DepthFuncGreaterEqual);
	if(!depth_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_DEPTH_SHADER=1")) return 1;
	if(!depth_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_DEPTH_SHADER=1")) return 1;
	if(!depth_pipeline.create()) return 1;
	
	// create light pipeline
	Pipeline light_pipeline = device.createPipeline(depth_pipeline);
	light_pipeline.setUniformMask(0, Shader::MaskVertexFragment);
	light_pipeline.setStorageMasks(0, 4, Shader::MaskFragment);
	light_pipeline.setDepthFunc(Pipeline::DepthFuncEqual);
	if(!light_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_LIGHT_SHADER=1")) return 1;
	if(!light_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_LIGHT_SHADER=1")) return 1;
	if(!light_pipeline.create()) return 1;
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.glb")) return 1;
	
	mesh.createBounds();
	mesh.createNormals();
	mesh.setBasis(Mesh::BasisZUpRight);
	BoundBoxf bound_box = BoundBoxf(mesh.getBoundBox());
	Vector3f bound_min = bound_box.min * Vector3f(2.0f, 2.0f, 1.2f);
	Vector3f bound_max = bound_box.max * Vector3f(2.0f, 2.0f, 1.2f);
	
	// create model
	MeshModel model;
	if(!model.create(device, light_pipeline, mesh)) return 1;
	
	// create tree
	RadixSort radix_sort;
	PrefixScan prefix_scan;
	SpatialTree spatial_tree;
	uint32_t group_size = min(device.getFeatures().maxGroupSizeX, 256u);
	if(!radix_sort.create(device, RadixSort::ModeSingle, prefix_scan, num_lights, group_size)) return 1;
	if(!spatial_tree.create(device, SpatialTree::FlagSingle, radix_sort, num_lights, group_size)) return 1;
	
	// create lights
	Array<uint32_t> colors(num_lights);
	Array<Vector4f> positions(num_lights);
	Array<Vector4f> velocities(num_lights);
	Random<Vector3i, Vector3f> random(Vector3i(1, 3, 7));
	for(uint32_t i = 0; i < num_lights; i++) {
		float32_t radius = random.getf32(Vector3f(0.2f), Vector3f(1.2f)).x;
		positions[i] = Vector4f(random.getf32(bound_min, bound_max), radius * 256.0f);
		velocities[i] = Vector4f(random.getf32(Vector3f(-0.5f), Vector3f(0.5f)), 0.0f);
		Vector4f color = Vector4f(random.getf32(Vector3f(0.2f), Vector3f(1.2f)), 0.0f);
		colors[i] = Color(color.v).gammaToLinear().getRGBAu8();
	}
	
	// create buffers
	Buffer colors_buffer = device.createBuffer(Buffer::FlagStorage, colors.get(), colors.bytes());
	Buffer positions_buffer = device.createBuffer(Buffer::FlagStorage, positions.get(), positions.bytes());
	Buffer velocities_buffer = device.createBuffer(Buffer::FlagStorage, velocities.get(), velocities.bytes());
	Buffer nodes_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, sizeof(SpatialTree::Node) * num_lights * 2);
	if(!colors_buffer || !positions_buffer || !velocities_buffer || !nodes_buffer) return 1;
	
	uint32_t num_cells = grid_size[0] * grid_size[1] * grid_size[2];
	Buffer grid_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * num_cells);
	Buffer indices_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * 2 * num_cells * grid_size[3]);
	Buffer counters_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * grid_size[0]);
	if(!grid_buffer || !indices_buffer || !counters_buffer) return 1;
	
	float32_t animation_time = 0.0f;
	float32_t old_animation_time = 0.0f;
	bool animation = !app.isArgument("pause");
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// animation time
		if(window.getKeyboardKey(' ', true)) animation = !animation;
		if(animation) animation_time += time - old_animation_time;
		old_animation_time = time;
		
		// window size
		float32_t width = (float32_t)window.getWidth();
		float32_t height = (float32_t)window.getHeight();
		
		// common parameters
		CommonParameters common_parameters;
		common_parameters.znear = 0.1f;
		common_parameters.zfar = 10000.0f;
		common_parameters.camera = Vector4f(sin(animation_time) * 32.0f, 1200.0f * sin(animation_time * 0.1f), 128.0f + cos(animation_time) * 32.0f, 1.0f);
		common_parameters.projection = Matrix4x4f::perspective(60.0f, width / height, common_parameters.znear, true);
		if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
		common_parameters.modelview = Matrix4x4f::lookAt(common_parameters.camera.xyz, Vector3f(0.0f, 1200.0f * sin(animation_time * 0.1f + 0.2f), common_parameters.camera.z), Vector3f::oneZ);
		common_parameters.window_size = Vector4f(width, height, 1.0f / width, 1.0f / height);
		common_parameters.grid_size = Vector4u(grid_size);
		
		// clear buffers
		if(!device.clearBuffer(counters_buffer)) return false;
		
		// update spatial tree
		{
			// create command list
			Compute compute = device.createCompute();
			
			// animation parameters
			AnimationParameters animation_parameters;
			animation_parameters.bound_min = Vector4f(bound_min, 1.0f);
			animation_parameters.bound_max = Vector4f(bound_max, 1.0f);
			animation_parameters.num_lights = num_lights;
			animation_parameters.ifps = animation ? 0.5f : 0.0f;
			
			// dispatch animation kernel
			compute.setKernel(animation_kernel);
			compute.setUniform(0, animation_parameters);
			compute.setStorageBuffers(0, { positions_buffer, velocities_buffer, nodes_buffer });
			compute.dispatch(num_lights);
			compute.barrier(nodes_buffer);
			
			// dispatch spatial tree
			spatial_tree.dispatch(compute, SpatialTree::HashXYZ8, nodes_buffer, 0, num_lights);
			
			// light parameters
			LightParameters light_parameters;
			light_parameters.iprojection = inverse(common_parameters.modelview) * inverse(common_parameters.projection);
			light_parameters.grid_size = common_parameters.grid_size;
			light_parameters.znear = common_parameters.znear;
			light_parameters.zfar = common_parameters.zfar;
			
			// dispatch light kernel
			compute.setKernel(light_kernel);
			compute.setUniform(0, light_parameters);
			compute.setStorageBuffers(0, { counters_buffer, grid_buffer, indices_buffer, nodes_buffer });
			compute.dispatch(grid_size[0], grid_size[1], grid_size[2]);
			compute.barrier({ grid_buffer, indices_buffer });
		}
		
		// set buffer layout
		device.flushBuffer(nodes_buffer);
		
		// window target
		target.setClearDepth(0.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw depth prepass
			command.setPipeline(depth_pipeline);
			command.setUniform(0, common_parameters);
			model.setBuffers(command);
			model.draw(command);
			
			// draw lights
			command.setPipeline(light_pipeline);
			command.setUniform(0, common_parameters);
			command.setStorageBuffers(0, { grid_buffer, indices_buffer, positions_buffer, colors_buffer });
			model.setBuffers(command);
			model.draw(command);
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
