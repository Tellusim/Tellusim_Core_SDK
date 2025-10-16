// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <graphics/TellusimMeshModel.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ShadowPCF", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// shadow size
	constexpr uint32_t shadow_size = 1024;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Matrix4x4f texcoord;
		Vector4f camera;
		Vector4f light;
		float32_t znear;
		float32_t radius;
		float32_t penumbra;
		float32_t samples;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMasks(0, 3, Shader::MaskFragment);
	pipeline.setTextureMasks(0, 2, Shader::MaskFragment);
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
	shadow_pipeline.setDepthBias(-8.0f, -8.0f);
	shadow_pipeline.setDepthFunc(Pipeline::DepthFuncGreaterEqual);
	if(!shadow_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "SHADOW_TARGET=1; VERTEX_SHADER=1")) return 1;
	if(!shadow_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "SHADOW_TARGET=1; FRAGMENT_SHADER=1")) return 1;
	if(!shadow_pipeline.create()) return 1;
	
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
	Sampler noise_sampler = device.createSampler(Sampler::FilterPoint, Sampler::WrapModeRepeat);
	Sampler point_sampler = device.createSampler(Sampler::FilterPoint, Sampler::WrapModeClamp);
	if(!noise_sampler || !point_sampler) return 1;
	
	// create shadow sampler
	Sampler shadow_sampler = device.createSampler();
	shadow_sampler.setFilter(Sampler::FilterLinear);
	shadow_sampler.setWrapMode(Sampler::WrapModeClamp);
	shadow_sampler.setCompareFunc(Sampler::CompareFuncGreaterEqual);
	if(!shadow_sampler.create()) return 1;
	
	// create noise texture
	Texture noise_texture = device.loadTexture("noise.png");
	if(!noise_texture) return 1;
	
	// create shadow texture
	Texture shadow_texture = device.createTexture2D(FormatDf32, shadow_size, Texture::FlagTarget);
	if(!shadow_texture) return 1;
	
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
	ControlSlider radius_slider(&panel, "Radius", 3, 8.0f, 0.0f, 16.0f);
	ControlSlider penumbra_slider(&panel, "Penumbra", 3, 0.5f, 0.0f, 2.0f);
	ControlSlider samples_slider(&panel, "Samples", 0, 8, 4, 32);
	radius_slider.setSize(192.0f, 0.0f);
	penumbra_slider.setSize(192.0f, 0.0f);
	samples_slider.setSize(192.0f, 0.0f);
	
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
		CommonParameters common_parameters;
		common_parameters.znear = 0.01f;
		common_parameters.light = Vector4f(4.0f, 0.0f, 2.3f, 0.0f);
		common_parameters.projection = Matrix4x4f::perspective(50.0f, 1.0f, common_parameters.znear, true);
		common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.light), Vector3f::zero, Vector3f::oneZ);
		common_parameters.texcoord = Matrix4x4f::translate(0.5f, 0.5f, 0.0f) * Matrix4x4f::scale(0.5f, 0.5f, 1.0f) * common_parameters.projection * common_parameters.modelview;
		if(shadow_target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
		if(device.getFeatures().depthRangeOneToOne) common_parameters.projection = Matrix4x4f::translate(0.0f, 0.0f, -1.0f) * Matrix4x4f::scale(1.0f, 1.0f, 2.0f) * common_parameters.projection;
		common_parameters.radius = radius_slider.getValuef32() * 2.0f / shadow_size;
		common_parameters.penumbra = penumbra_slider.getValuef32() * 0.02f;
		common_parameters.samples = samples_slider.getValuef32();
		
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
		
		// window target
		window_target.begin();
		{
			// create command list
			Command command = device.createCommand(window_target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// set shadow texture
			command.setSamplers(0, { noise_sampler, point_sampler, shadow_sampler });
			command.setTextures(0, { noise_texture, shadow_texture });
			
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
