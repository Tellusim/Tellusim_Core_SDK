// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <Metal/Metal.h>
#include <QuartzCore/CAMetalLayer.h>

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <math/TellusimMath.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimSurface.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimDevice.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	class MTLGLFWWindow {
			
		public:
			
			MTLGLFWWindow();
			~MTLGLFWWindow();
			
			// create window
			bool create();
			
			// main loop
			bool run();
			
		private:
			
			// rendering loop
			bool create_mtl();
			bool render_mtl();
			
			bool done = false;
			
			GLFWwindow *window = nullptr;
			CAMetalLayer *layer = nullptr;
			
			MTLContext context;
			MTLSurface surface;
			
			Device device;
			
			Pipeline pipeline;
			Buffer vertex_buffer;
			Buffer index_buffer;
			
			MTLTexture depth_stencil_texture;
	};
	
	/*
	 */
	MTLGLFWWindow::MTLGLFWWindow() {
		
	}
	
	MTLGLFWWindow::~MTLGLFWWindow() {
		
		// terminate GLFW
		if(window) glfwDestroyWindow(window);
		glfwTerminate();
	}
	
	/*
	 */
	bool MTLGLFWWindow::create() {
		
		TS_ASSERT(window == nullptr);
		
		// initialize GLFW
		if(!glfwInit()) {
			TS_LOG(Error, "MTLGLFWWindow::create(): can't init GLFW\n");
			return false;
		}
		
		// create context
		if(!context.create()) {
			TS_LOG(Error, "MTLGLFWWindow::create(): can't create context\n");
			return false;
		}
		
		// window size
		float32_t scale = NSScreen.mainScreen.backingScaleFactor;
		int32_t width = (int32_t)(1600 / scale);
		int32_t height = (int32_t)(900 / scale);
		
		// create window
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(width, height, "Metal Tellusim::MTLGLFWWindow", nullptr, nullptr);
		if(!window) {
			TS_LOG(Error, "MTLGLFWWindow::create(): can't create window\n");
			return false;
		}
		
		// create Matal layer
		layer = [CAMetalLayer layer];
		layer.device = (__bridge id<MTLDevice>)context.getDevice();
		layer.contentsScale = scale;
		layer.opaque = YES;
		
		// set Metal layer
		NSWindow *ns_window = glfwGetCocoaWindow(window);
		ns_window.contentView.layer = layer;
		ns_window.contentView.wantsLayer = YES;
		
		// create surface
		surface = MTLSurface(context);
		if(!surface) {
			TS_LOG(Error, "MTLGLFWWindow::create(): can't create context\n");
			return false;
		}
		
		// create device
		device = Device(surface);
		if(!device) {
			TS_LOG(Error, "MTLGLFWWindow::create(): can't create device\n");
			return false;
		}
		
		// initialize Metal
		if(!create_mtl()) {
			TS_LOG(Error, "MTLGLFWWindow::create(): can't create Metal\n");
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	bool MTLGLFWWindow::create_mtl() {
		
		// create surface
		surface.setColorFormat(FormatRGBAu8n);
		id<MTLDevice> mtl_device = (__bridge id<MTLDevice>)context.getDevice();
		if(mtl_device.isDepth24Stencil8PixelFormatSupported) surface.setDepthFormat(FormatDu24Su8);
		else surface.setDepthFormat(FormatDf32Su8);
		
		// create pipeline
		pipeline = device.createPipeline();
		pipeline.setUniformMask(0, Shader::MaskVertex);
		pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 6);
		pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 6);
		pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
		pipeline.setColorFormat(surface.getColorFormat());
		pipeline.setDepthFormat(surface.getDepthFormat());
		pipeline.setMultisample(surface.getMultisample());
		if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return false;
		if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return false;
		if(!pipeline.create()) return false;
		
		// create mesh geometry
		#include "main_mesh.h"
		vertex_buffer = device.createBuffer(Buffer::FlagVertex, mesh_vertices, sizeof(float32_t) * num_mesh_vertices);
		index_buffer = device.createBuffer(Buffer::FlagIndex, mesh_indices, sizeof(uint32_t) * num_mesh_indices);
		if(!vertex_buffer || !index_buffer) return false;
		
		return true;
	}
	
	/*
	 */
	bool MTLGLFWWindow::render_mtl() {
		
		// next drawable
		id<CAMetalDrawable> drawable = [layer nextDrawable];
		
		// render pass descriptor
		MTLRenderPassDescriptor *descriptor = [MTLRenderPassDescriptor renderPassDescriptor];
		descriptor.colorAttachments[0].texture = drawable.texture;
		descriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
		descriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
		descriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.0f, 0.0f, 0.0f, 0.0f);
		descriptor.depthAttachment.texture = (__bridge id<MTLTexture>)depth_stencil_texture.getMTLTexture();
		descriptor.depthAttachment.loadAction = MTLLoadActionClear;
		descriptor.depthAttachment.storeAction = MTLStoreActionStore;
		descriptor.depthAttachment.clearDepth = 1.0f;
		descriptor.stencilAttachment.texture = (__bridge id<MTLTexture>)depth_stencil_texture.getMTLTexture();
		descriptor.stencilAttachment.loadAction = MTLLoadActionClear;
		descriptor.stencilAttachment.storeAction = MTLStoreActionStore;
		descriptor.stencilAttachment.clearStencil = 0x00;
		surface.setDescriptor((__bridge void*)descriptor);
		
		// structures
		struct CommonParameters {
			Matrix4x4f projection;
			Matrix4x4f modelview;
			Matrix4x4f transform;
			Vector4f camera;
		};
		
		// widget target
		Target target = device.createTarget(surface);
		target.setClearColor(Color("#8a8b8c"));
		target.begin();
		{
			// current time
			float32_t time = (float32_t)Time::seconds();
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(2.0f, 2.0f, 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)surface.getWidth() / surface.getHeight(), 0.1f, 1000.0f);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(time * 32.0f) * Matrix4x4f::rotateY(60.0f + time * 8.0f);
			
			// create command list
			Command command = device.createCommand(target);
			
			// draw mesh
			command.setPipeline(pipeline);
			command.setUniform(0, common_parameters);
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			command.drawElements((uint32_t)index_buffer.getSize() / 4);
		}
		target.end();
		
		// flush context
		context.flush();
		
		// present drawable
		id<MTLCommandBuffer> command = (__bridge id<MTLCommandBuffer>)surface.getCommand();
		[command presentDrawable:drawable];
		
		// flip context
		device.flip();
		
		return true;
	}
	
	/*
	 */
	bool MTLGLFWWindow::run() {
		
		// main loop
		while(!done) {
			
			// pool events
			glfwPollEvents();
			done |= (glfwWindowShouldClose(window) != 0);
			done |= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
			
			// surface size
			int32_t width, height;
			glfwGetFramebufferSize(window, &width, &height);
			surface.setSize(width, height);
			
			// resize buffers
			if(!depth_stencil_texture || depth_stencil_texture.getWidth() != (uint32_t)width || depth_stencil_texture.getHeight() != (uint32_t)height) {
				depth_stencil_texture = device.createTexture2D(surface.getDepthFormat(), width, height, Texture::FlagTarget);
				if(!depth_stencil_texture) {
					TS_LOG(Error, "MTLGLFWWindow::run(): can't create depth stencil\n");
					return false;
				}
			}
			
			@autoreleasepool {
				
				// render application
				if(!render_mtl()) {
					return false;
				}
			}
		}
		
		return true;
	}
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create window
	Tellusim::MTLGLFWWindow window;
	if(!window.create()) return 1;
	
	// run application
	window.run();
	
	return 0;
}
