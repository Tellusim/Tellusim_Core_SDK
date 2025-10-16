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

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ShadowTracing", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f imodelviewprojection;
		Matrix4x4f transform;
		Vector4f camera;
		Vector4f light;
		float32_t znear;
		float32_t radius;
		float32_t samples;
		uint32_t num_nodes;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute tracing support
	if(!device.getFeatures().computeTracing) {
		TS_LOG(Error, "compute tracing is not supported\n");
		return 0;
	}
	
	// create kernel
	Kernel kernel = device.createKernel().setSamplers(1).setTextures(3).setSurfaces(1).setUniforms(1).setTracings(1);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!kernel.create()) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 8);
	pipeline.setColorFormat(0, FormatRGBAf16);
	pipeline.setDepthFormat(FormatDf32);
	pipeline.setDepthFunc(Pipeline::DepthFuncGreaterEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.glb")) return 1;
	uint32_t plane_index = mesh.findGeometry("plane");
	uint32_t caster_index = mesh.findGeometry("caster");
	if(plane_index == Maxu32 || caster_index == Maxu32) return 1;
	mesh.setBasis(Mesh::BasisZUpRight);
	
	// create model
	MeshModel model;
	if(!model.create(device, pipeline, mesh, MeshModel::DefaultFlags | MeshModel::FlagIndices32 | MeshModel::FlagBufferStorage | MeshModel::FlagBufferTracing)) return 1;
	Buffer vertex_buffer = model.getVertexBuffer();
	Buffer index_buffer = model.getIndexBuffer();
	
	// create tracing
	Tracing tracing = device.createTracing();
	tracing.addVertexBuffer(model.getNumGeometryVertices(caster_index), pipeline.getAttributeFormat(0), model.getVertexBufferStride(caster_index), vertex_buffer);
	tracing.addIndexBuffer(model.getNumIndices(), model.getIndexFormat(), index_buffer);
	if(!tracing.create(Tracing::TypeTriangle, Tracing::FlagCompact | Tracing::FlagFastTrace)) return 1;
	
	// create scratch buffer
	Buffer scratch_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagScratch, tracing.getBuildSize() + 1024 * 8);
	if(!scratch_buffer) return 1;
	
	// build tracing
	if(!device.buildTracing(tracing, scratch_buffer, Tracing::FlagCompact)) return 1;
	device.flushTracing(tracing);
	
	// create instance
	Tracing::Instance instance = {};
	instance.mask = 0xff;
	instance.tracing = &tracing;
	
	// create instances buffer
	Buffer instances_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing, 64);
	if(!instances_buffer) return 1;
	
	// create instance tracing
	Tracing instance_tracing = device.createTracing(1, instances_buffer);
	if(!instance_tracing) return 1;
	
	// create sampler
	Sampler noise_sampler = device.createSampler(Sampler::FilterPoint, Sampler::WrapModeRepeat);
	if(!noise_sampler) return 1;
	
	// create noise texture
	Texture noise_texture = device.loadTexture("noise.png");
	if(!noise_texture) return 1;
	
	// create target textures
	Texture normal_texture, depth_texture, color_surface;
	
	// create window target
	Target window_target = device.createTarget(window);
	
	// create render target
	Target render_target = device.createTarget();
	render_target.setClearDepth(0.0f);
	
	// create canvas
	Canvas canvas;
	
	// create root
	ControlRoot root(canvas, true);
	
	// create rect
	ControlRect color_rect(&root);
	color_rect.setAlign(Control::AlignExpand);
	color_rect.setMode(CanvasElement::ModeTextureFetch);
	color_rect.setBlend(Pipeline::BlendOpAdd, Pipeline::BlendFuncOne, Pipeline::BlendFuncZero);
	
	// create panel
	ControlPanel panel(&root, 1, 8.0f, 8.0f);
	panel.setAlign(Control::AlignRightTop);
	panel.setPosition(-8.0f, -8.0f);
	
	// create sliders
	ControlSlider radius_slider(&panel, "Radius", 2, 1.0f, 0.0f, 2.0f);
	ControlSlider samples_slider(&panel, "Samples", 0, 4, 1, 32);
	radius_slider.setSize(192.0f, 0.0f);
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
		
		// resize target textures
		if(!color_surface || color_surface.getWidth() != window.getWidth() || color_surface.getHeight() != window.getHeight()) {
			device.releaseTexture(depth_texture);
			device.releaseTexture(normal_texture);
			device.releaseTexture(color_surface);
			depth_texture = device.createTexture2D(FormatDf32, window.getWidth(), window.getHeight(), Texture::FlagTarget);
			normal_texture = device.createTexture2D(FormatRGBAf16, window.getWidth(), window.getHeight(), Texture::FlagTarget);
			color_surface = device.createTexture2D(FormatRGBAu8n, window.getWidth(), window.getHeight(), Texture::FlagSurface);
			if(!depth_texture || !normal_texture || !color_surface) return false;
			color_rect.setTexture(color_surface);
		}
		
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
		common_parameters.znear = 0.1f;
		common_parameters.camera = Vector4f(-4.5f, 4.5f, 1.0f, 0.0f);
		common_parameters.light = Vector4f(4.0f, 0.0f, 2.3f, 0.0f);
		common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), common_parameters.znear, true);
		common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f(-4.5f, 0.0f, -2.0f), Vector3f::oneZ);
		if(render_target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
		common_parameters.radius = radius_slider.getValuef32() * 0.02f;
		common_parameters.samples = samples_slider.getValuef32();
		
		// build instance tracing
		caster_transform.get(instance.transform, 12);
		if(!device.setTracing(instance_tracing, &instance, 1)) return false;
		if(!device.buildTracing(instance_tracing, scratch_buffer)) return false;
		device.flushTracing(instance_tracing);
		
		// flush textures
		device.flushTextures({ depth_texture, normal_texture }, Texture::FlagTarget);
		
		// render target
		render_target.setColorTexture(normal_texture);
		render_target.setDepthTexture(depth_texture);
		render_target.begin();
		{
			// create command list
			Command command = device.createCommand(render_target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
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
		render_target.end();
		
		device.flushTextures({ depth_texture, normal_texture });
		
		// shadow kernel
		{
			// create command list
			Compute compute = device.createCompute();
			
			// set kernel
			compute.setKernel(kernel);
			common_parameters.imodelviewprojection = inverse(common_parameters.projection * common_parameters.modelview);
			compute.setUniform(0, common_parameters);
			compute.setSampler(0, noise_sampler);
			compute.setTextures(0, { depth_texture, normal_texture, noise_texture });
			compute.setTracing(0, instance_tracing);
			compute.setSurfaceTexture(0, color_surface);
			
			// dispatch kernel
			compute.dispatch(color_surface);
			compute.barrier(color_surface);
		}
		
		// flush texture
		device.flushTexture(color_surface);
		
		// window target
		window_target.begin();
		{
			// create command list
			Command command = device.createCommand(window_target);
			
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
