// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimSurface.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
class OffscreenWindow : public Window {
		
	public:
		
		// constructor
		OffscreenWindow() { }
		explicit OffscreenWindow(Surface &surface) : Window(surface) { }
		virtual ~OffscreenWindow() { }
		
		// create window
		virtual bool create(Flags flags = DefaultFlags) {
			
			// create surface
			surface = getSurface();
			surface.setSize(getWidth(), getHeight());
			surface.setColorFormat(FormatRGBAu8n);
			surface.setDepthFormat(FormatDf32);
			
			// create device
			device = Device(surface);
			if(!device) return false;
			
			// create target
			target = device.createTarget();
			if(!target) return false;
			
			// create textures
			color_texture = device.createTexture2D(getColorFormat(), getWidth(), getHeight(), Texture::FlagTarget | Texture::FlagSource);
			depth_texture = device.createTexture2D(getDepthFormat(), getWidth(), getHeight(), Texture::FlagTarget);
			if(!color_texture || !depth_texture) return false;
			target.setColorTexture(color_texture);
			target.setDepthTexture(depth_texture);
			
			return true;
		}
		
		// render window
		virtual bool render() {
			
			// begin target
			target.begin();
			
			// swap target
			target.swap(surface);
			
			// end target
			if(target.isAtomic()) target.end();
			
			return true;
		}
		
		// present window
		virtual bool present() {
			
			// swap target
			target.swap(surface);
			
			// end target
			if(target.isEnabled()) target.end();
			
			// flip context
			if(!device.flip()) {
				TS_LOG(Error, "OffscreenWindow::present(): can't flip context\n");
				return false;
			}
			
			// get image
			Image image;
			image.create2D(color_texture.getFormat(), getWidth(), getHeight());
			if(device.getTexture(color_texture, image)) {
				String name = String::format("render_%02u.png", counter++);
				if(image.getFormat() != FormatRGBAu8n) image = image.toFormat(FormatRGBAu8n);
				if(image.save(name)) TS_LOGF(Message, "%s\n", name.get());
			}
			
			// stop application
			if(counter > 8) stop();
			
			// limit framerate
			Time::sleep(Time::Seconds / 20);
			
			return true;
		}
		
		// finish context
		virtual bool finish() {
			return device.finish();
		}
		
	private:
		
		Surface surface;
		Device device;
		
		Target target;
		Texture color_texture;
		Texture depth_texture;
		
		uint32_t counter = 0;
};

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create context
	Context context(app.getPlatform(), app.getDevice());
	if(!context || !context.create()) return 1;
	
	// create surface
	Surface surface(context);
	if(!surface) return 1;
	
	// create window
	OffscreenWindow window;
	window = OffscreenWindow(surface);
	window.setSize(app.getWidth(), app.getHeight());
	if(!window.create() || !window.setHidden(false)) return 1;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
	};
	
	// create devices
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 6);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 6);
	pipeline.setMultisample(window.getMultisample());
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create model geometry
	#include "main_model.h"
	Buffer model_vertex_buffer = device.createBuffer(Buffer::FlagVertex, model_vertices, sizeof(float32_t) * num_model_vertices);
	Buffer model_index_buffer = device.createBuffer(Buffer::FlagIndex, model_indices, sizeof(uint16_t) * num_model_indices);
	if(!model_vertex_buffer || !model_index_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(0.0f, 2.0f, 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(time * 16.0f) * Matrix4x4f::rotateY(time * 8.0f) * Matrix4x4f::rotateX(time * 4.0f);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// draw model
			command.setUniform(0, common_parameters);
			command.setVertexBuffer(0, model_vertex_buffer);
			command.setIndexBuffer(FormatRu16, model_index_buffer);
			command.drawElements(num_model_indices);
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
