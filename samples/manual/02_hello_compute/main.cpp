// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <math/TellusimMath.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>
#include <parallel/TellusimPrefixScan.h>
#include <parallel/TellusimRadixSort.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create window
	Window window(app.getPlatform(), app.getDevice());
	if(!window || !window.setSize(app.getWidth(), app.getHeight())) return 1;
	if(!window.create("02 Hello Compute") || !window.setHidden(false)) return 1;
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(key == Window::KeyEsc) window.stop();
	});
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// declarations
	#include "main.h"
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
	};
	
	// parameters
	constexpr uint32_t group_size = 128;
	constexpr uint32_t max_emitters = 1024;
	constexpr uint32_t max_particles = 1024 * 1024;
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// create init kernel
	Kernel init_kernel = device.createKernel().setUniforms(1).setStorages(3, BindFlagFixed);
	if(!init_kernel.loadShaderGLSL("main.shader", "INIT_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!init_kernel.create()) return 1;
	
	// create emitter kernel
	Kernel emitter_kernel = device.createKernel().setUniforms(1).setStorages(5, BindFlagFixed).setStorageFlags(0, BindFlagNone);
	if(!emitter_kernel.loadShaderGLSL("main.shader", "EMITTER_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!emitter_kernel.create()) return 1;
	
	// create dispatch kernel
	Kernel dispatch_kernel = device.createKernel().setUniforms(1).setStorages(4, BindFlagFixed);
	if(!dispatch_kernel.loadShaderGLSL("main.shader", "DISPATCH_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!dispatch_kernel.create()) return 1;
	
	// create update kernel
	Kernel update_kernel = device.createKernel().setUniforms(1).setStorages(4, BindFlagFixed);
	if(!update_kernel.loadShaderGLSL("main.shader", "UPDATE_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!update_kernel.create()) return 1;
	
	// create geometry kernel
	Kernel geometry_kernel = device.createKernel().setUniforms(1).setStorages(4, BindFlagFixed);
	if(!geometry_kernel.loadShaderGLSL("main.shader", "GEOMETRY_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!geometry_kernel.create()) return 1;
	
	// create radix sort
	RadixSort radix_sort;
	PrefixScan prefix_scan;
	if(!radix_sort.create(device, RadixSort::FlagSingle | RadixSort::FlagIndirect | RadixSort::FlagOrder, prefix_scan, max_particles)) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthMask(Pipeline::DepthMaskNone);
	pipeline.setDepthFunc(Pipeline::DepthFuncAlways);
	pipeline.setBlend(Pipeline::BlendOpAdd, Pipeline::BlendFuncOne, Pipeline::BlendFuncInvSrcAlpha);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBAf32, 0, offsetof(Vertex, position), sizeof(Vertex), 1);
	pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGBAf32, 0, offsetof(Vertex, velocity), sizeof(Vertex), 1);
	pipeline.addAttribute(Pipeline::AttributeColor, FormatRGBAf32, 0, offsetof(Vertex, color), sizeof(Vertex), 1);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create compute state buffer
	// contains global particle system state
	ComputeState state = {};
	Buffer state_buffer = device.createBuffer(Buffer::FlagStorage, &state, sizeof(state));
	if(!state_buffer) return 1;
	
	// create emitters state buffer
	// contains dynamic emitter parameters
	Buffer emitters_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(EmitterState) * max_emitters * group_size);
	if(!emitters_buffer) return 1;
	
	// create particles state buffer
	// contains per-particle state
	Buffer particles_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(ParticleState) * max_particles);
	if(!particles_buffer) return 1;
	
	// create particle allocator buffer
	// contains new particle indices
	Buffer allocator_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * max_particles);
	if(!allocator_buffer) return 1;
	
	// create particle distances buffer
	// contains camera to particle distances and order indices
	Buffer distances_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * max_particles * 2);
	if(!distances_buffer) return 1;
	
	// create particle vertex buffer
	// contains particle position, velocity, and color
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex | Buffer::FlagStorage, sizeof(Vertex) * max_particles);
	if(!vertex_buffer) return 1;
	
	// create particle indices buffer
	const uint16_t indices_data[] = { 0, 1, 2, 2, 3, 0 };
	Buffer indices_buffer = device.createBuffer(Buffer::FlagIndex, indices_data, sizeof(indices_data));
	if(!indices_buffer) return 1;
	
	// create indirect dispatch buffer
	Compute::DispatchIndirect dispatch_data = {};
	Buffer dispatch_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagIndirect, &dispatch_data, sizeof(dispatch_data));
	if(!dispatch_buffer) return 1;
	
	// create indirect draw buffer
	Command::DrawElementsIndirect draw_data = {};
	Buffer draw_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagIndirect, &draw_data, sizeof(draw_data));
	if(!draw_buffer) return 1;
	
	// create sort parameters buffer
	RadixSort::DispatchParameters sort_data = {};
	Buffer sort_buffer = device.createBuffer(Buffer::FlagStorage, &sort_data, sizeof(sort_data));
	if(!sort_buffer) return 1;
	
	// create texture
	Texture texture = device.loadTexture("particle.png", Texture::FlagMipmaps);
	if(!texture) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterBilinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create target
	Target target = device.createTarget(window);
	if(!target) return 1;
	
	// compute parameters
	ComputeParameters compute_parameters = {};
	compute_parameters.max_emitters = max_emitters;
	compute_parameters.max_particles = max_particles;
	compute_parameters.global_gravity = Vector4f(0.0f, 0.0f, -8.0f, 0.0f);
	compute_parameters.wind_velocity = Vector4f(0.0f, 0.0f, 4.0f, 0.0f);
	compute_parameters.wind_force = 0.2f;
	
	// initialize buffers
	{
		Compute compute = device.createCompute();
		
		// init kernel
		compute.setKernel(init_kernel);
		compute.setUniform(0, compute_parameters);
		compute.setStorageBuffers(0, { emitters_buffer, particles_buffer, allocator_buffer });
		compute.dispatch(max(max_emitters * group_size, max_particles));
		compute.barrier({ emitters_buffer, particles_buffer, allocator_buffer });
	}
	
	// create emitters
	EmitterParameters emitter_0 = {};
	emitter_0.direction = Vector4f(0.0f, 0.0f, 1.0f, 0.0f);
	emitter_0.color_spread = Color(0.2f);
	emitter_0.position_spread = 0.2f;
	emitter_0.velocity_mean = 12.0f;
	emitter_0.radius_mean = 0.2f;
	emitter_0.radius_spread = 0.1f;
	emitter_0.growth_spread = 0.1f;
	emitter_0.angle_spread = Pi2;
	emitter_0.twist_mean = -Pi;
	emitter_0.twist_spread = Pi2;
	emitter_0.twist_damping = 0.1f;
	emitter_0.life_mean = 6.0f;
	emitter_0.life_spread = 2.0f;
	emitter_0.spawn_mean = 2000.0f;
	emitter_0.spawn_spread = 1000.0f;
	
	EmitterParameters emitter_1 = {};
	emitter_1.color_spread = Color(0.2f);
	emitter_1.position_spread = 0.2f;
	emitter_1.velocity_spread = 20.0f;
	emitter_1.radius_mean = 0.1f;
	emitter_1.radius_spread = 0.1f;
	emitter_1.growth_spread = 0.1f;
	emitter_1.angle_spread = Pi2;
	emitter_1.twist_mean = -Pi;
	emitter_1.twist_spread = Pi2;
	emitter_1.twist_damping = 0.1f;
	emitter_1.life_mean = 0.3f;
	emitter_1.life_spread = 0.2f;
	emitter_1.spawn_mean = 10000.0f;
	
	Array<EmitterParameters> emitters;
	for(uint32_t i = 0; i < 5; i++) {
		emitters.append(emitter_0);
		emitters.append(emitter_1);
	}
	
	// old time
	float32_t old_time = (float32_t)Time::seconds();
	
	// main loop
	window.run([&]() {
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Window::update();
		
		// render window
		if(!window.render()) return false;
		
		// current time
		float32_t time = (float32_t)Time::seconds();
		float32_t ifps = min(time - old_time, 1.0f / 60.0f);
		old_time = time;
		
		// update emitters
		for(uint32_t i = 0; i < emitters.size(); i++) {
			float32_t color = time * 0.5f;
			float32_t angle = time + 360.0f * i / emitters.size();
			emitters[i].position.xyz = Matrix4x3f::rotateZ(angle * 8.0f) * Vector3f(32.0f * cos(time), 0.0f, 8.0f);
			emitters[i].color_mean.r = max(cos(color + Pi05) * 0.8f + 0.2f, 0.0f);
			emitters[i].color_mean.g = max(cos(color - Pi05) * 0.8f + 0.2f, 0.0f);
			emitters[i].color_mean.b = max(cos(color - Pi) * 0.8f + 0.2f, 0.0f);
			if((i & 1) == 0) {
				emitters[i].velocity_spread = sin(time) * 4.0f + 2.0f;
				emitters[i].velocity_damping = sin(time) * 0.5f + 0.5f;
			}
		}
		
		// simulate particles
		{
			Compute compute = device.createCompute();
			
			// compute parameters
			compute_parameters.camera = Matrix4x3f::rotateZ(-time * 8.0f) * Vector4f(32.0f, 0.0f, 32.0f, 0.0f);
			compute_parameters.num_emitters = emitters.size();
			compute_parameters.ifps = ifps;
			
			// emitter kernel
			compute.setKernel(emitter_kernel);
			compute.setUniform(0, compute_parameters);
			compute.setStorageData(0, emitters.get(), emitters.bytes());
			compute.setStorageBuffers(1, { state_buffer, emitters_buffer, particles_buffer, allocator_buffer });
			compute.dispatch(emitters.size() * group_size);
			compute.barrier({ state_buffer, emitters_buffer, particles_buffer, allocator_buffer });
			
			// dispatch kernel
			compute.setKernel(dispatch_kernel);
			compute.setUniform(0, compute_parameters);
			compute.setStorageBuffers(0, { state_buffer, dispatch_buffer, draw_buffer, sort_buffer });
			compute.dispatch(1);
			compute.barrier({ dispatch_buffer, draw_buffer, sort_buffer });
			
			// update kernel
			compute.setKernel(update_kernel);
			compute.setUniform(0, compute_parameters);
			compute.setStorageBuffers(0, { state_buffer, particles_buffer, allocator_buffer, distances_buffer });
			compute.setIndirectBuffer(dispatch_buffer);
			compute.dispatchIndirect();
			compute.barrier({ state_buffer, particles_buffer, allocator_buffer, distances_buffer });
			
			// sort particles
			if(!radix_sort.dispatchIndirect(compute, distances_buffer, sort_buffer, 0, RadixSort::FlagOrder)) return false;
			
			// geometry kernel
			compute.setKernel(geometry_kernel);
			compute.setUniform(0, compute_parameters);
			compute.setStorageBuffers(0, { state_buffer, particles_buffer, distances_buffer, vertex_buffer });
			compute.setIndirectBuffer(dispatch_buffer);
			compute.dispatchIndirect();
		}
		
		// flush render buffers
		device.flushBuffers({ vertex_buffer, draw_buffer });
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(compute_parameters.camera.xyz, Vector3f::zero, Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			
			// set pipeline
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTexture(0, texture);
			command.setUniform(0, common_parameters);
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu16, indices_buffer);
			
			// draw particles
			command.setIndirectBuffer(draw_buffer);
			command.drawElementsIndirect(1);
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
