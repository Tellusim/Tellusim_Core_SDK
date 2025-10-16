// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>
#include <graphics/TellusimMeshModel.h>
#include <graphics/TellusimSeparableFilter.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ShadowESM", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// shadow size
	constexpr uint32_t shadow_size = 1024;
	constexpr uint32_t filter_size = 12;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Matrix4x4f texcoord;
		Vector4f camera;
		Vector4f light;
		float32_t znear_alpha;
		float32_t shadow_power;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMasks(0, 2, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setUniformMask(0, Shader::MaskVertex | Shader::MaskFragment);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 8);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create shadow pipeline
	Pipeline shadow_pipeline = device.createPipeline();
	shadow_pipeline.setUniformMask(0, Shader::MaskVertex);
	shadow_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, 0, sizeof(float32_t) * 8);
	shadow_pipeline.setDepthFormat(FormatDf32);
	shadow_pipeline.setDepthFunc(Pipeline::DepthFuncGreaterEqual);
	if(!shadow_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "SHADOW_TARGET=1; VERTEX_SHADER=1")) return 1;
	if(!shadow_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "SHADOW_TARGET=1; FRAGMENT_SHADER=1")) return 1;
	if(!shadow_pipeline.create()) return 1;
	
	// create filter
	SeparableFilter filter;
	filter.setInputSource(SeparableFilter::ModeHorizontal, "exp(parameters.x / max(value, 1e-12f))");
	if(!filter.create(device, FormatRf32, filter_size)) return 1;
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.glb")) return 1;
	uint32_t plane_index = mesh.findGeometry("plane");
	uint32_t caster_index = mesh.findGeometry("caster");
	if(plane_index == Maxu32 || caster_index == Maxu32) return 1;
	mesh.setBasis(Mesh::BasisZUpRight);
	
	// create model
	MeshModel model;
	if(!model.create(device, pipeline, mesh)) return 1;
	
	// create samplers
	Sampler point_sampler = device.createSampler(Sampler::FilterPoint, Sampler::WrapModeClamp);
	Sampler linear_sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!point_sampler || !linear_sampler) return 1;
	
	// create shadow texture
	Texture shadow_texture = device.createTexture2D(FormatDf32, shadow_size, Texture::FlagTarget);
	Texture shadow_surface_0 = device.createTexture2D(FormatRf32, shadow_size / 2, shadow_size, Texture::FlagSurface);
	Texture shadow_surface_1 = device.createTexture2D(FormatRf32, shadow_size / 2, shadow_size / 2, Texture::FlagSurface);
	if(!shadow_texture || !shadow_surface_0 || !shadow_surface_1) return 1;
	
	// create window target
	Target window_target = device.createTarget(window);
	window_target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// create shadow target
	Target shadow_target = device.createTarget({ shadow_texture });
	shadow_target.setClearDepth(0.0f);
	
	// create canvas
	Canvas canvas;
	
	// create panel
	ControlRoot root(canvas, true);
	ControlPanel panel(&root, 1, 8.0f, 8.0f);
	panel.setAlign(Control::AlignRightTop);
	panel.setPosition(-8.0f, -8.0f);
	
	// create sliders
	ControlSlider sigma_slider(&panel, "Sigma", 3, 5.0f, 1.0f, 9.0f);
	ControlSlider alpha_slider(&panel, "Alpha", 3, 3.0f, 1.0f, 5.0f);
	ControlSlider power_slider(&panel, "Power", 3, 2.0f, 1.0f, 3.0f);
	sigma_slider.setSize(192.0f, 0.0f);
	alpha_slider.setSize(192.0f, 0.0f);
	power_slider.setSize(192.0f, 0.0f);
	
	float32_t animation_time = 0.0f;
	float32_t old_animation_time = 0.0f;
	bool animation = !app.isArgument("pause");
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// update controls
		update_controls(window, root);
		canvas.create(device, window_target);
		
		// animation time
		if(window.getKeyboardKey(' ', true)) animation = !animation;
		if(animation) animation_time += time - old_animation_time;
		old_animation_time = time;
		
		// shadow caster transform
		Matrix4x4f caster_transform = Matrix4x4f::rotateZ(sin(animation_time * 0.5f) * 15.0f + 90.0f);
		Matrix4x4f plane_transform = Matrix4x4f::translate(-4.5f, 0.0f, -1.2f);
		
		// common parameters
		float32_t znear = 0.01f;
		CommonParameters common_parameters;
		common_parameters.light = Vector4f(4.0f, 0.0f, 2.3f, 0.0f);
		common_parameters.projection = Matrix4x4f::perspective(50.0f, 1.0f, znear, true);
		common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.light), Vector3f::zero, Vector3f::oneZ);
		common_parameters.texcoord = Matrix4x4f::translate(0.5f, 0.5f, 0.0f) * Matrix4x4f::scale(0.5f, 0.5f, 1.0f) * common_parameters.projection * common_parameters.modelview;
		if(shadow_target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
		if(device.getFeatures().depthRangeOneToOne) common_parameters.projection = Matrix4x4f::translate(0.0f, 0.0f, -1.0f) * Matrix4x4f::scale(1.0f, 1.0f, 2.0f) * common_parameters.projection;
		common_parameters.znear_alpha = znear * alpha_slider.getValuef32();
		common_parameters.shadow_power = power_slider.getValuef32();
		
		// filter parameters
		Vector4f filter_parameters = Vector4f::zero;
		filter_parameters.x = common_parameters.znear_alpha;
		filter.setGaussianWeights(filter_size, sigma_slider.getValuef32());
		
		// shadow target
		shadow_target.begin();
		{
			// create command list
			Command command = device.createCommand(shadow_target);
			
			// set pipeline
			command.setPipeline(shadow_pipeline);
			
			// set model buffers
			model.setBuffers(command);
			
			// draw plane
			common_parameters.transform = plane_transform;
			command.setUniform(0, common_parameters);
			model.draw(command, plane_index);
			
			// draw shadow caster
			common_parameters.transform = caster_transform;
			command.setUniform(0, common_parameters);
			model.draw(command, caster_index);
		}
		shadow_target.end();
		
		// flush texture
		device.flushTexture(shadow_texture);
		
		// filter shadow map
		{
			// create command list
			Compute compute = device.createCompute();
			
			// horizontal filter
			Vector4f parameters = Vector4f(common_parameters.znear_alpha);
			filter.dispatch(compute, SeparableFilter::ModeHorizontal, filter_size, shadow_surface_0, shadow_texture, parameters);
			
			// vertical filter
			filter.dispatch(compute, SeparableFilter::ModeVertical, filter_size, shadow_surface_1, shadow_surface_0);
		}
		
		// flush texture
		device.flushTexture(shadow_surface_1);
		
		// window target
		window_target.begin();
		{
			// create command list
			Command command = device.createCommand(window_target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// set shadow texture
			command.setSamplers(0, { point_sampler, linear_sampler });
			command.setTexture(0, shadow_surface_1);
			
			// common parameters
			common_parameters.camera = Vector4f(-4.5f, 4.5f, 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f(-4.5f, 0.0f, -2.0f), Vector3f::oneZ);
			if(window_target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			
			// set model buffers
			model.setBuffers(command);
			
			// draw plane
			common_parameters.transform = plane_transform;
			command.setUniform(0, common_parameters);
			model.draw(command, plane_index);
			
			// draw shadow caster
			common_parameters.transform = caster_transform;
			command.setUniform(0, common_parameters);
			model.draw(command, caster_index);
			
			// draw canvas
			canvas.draw(command, window_target);
		}
		window_target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
