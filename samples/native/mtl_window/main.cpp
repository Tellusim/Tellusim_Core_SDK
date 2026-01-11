// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <Cocoa/Cocoa.h>
#include <Carbon/Carbon.h>
#include <MetalKit/MetalKit.h>

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
#define EXTERNAL_DEVICE		1

/*
 */
using namespace Tellusim;

/*
 */
@interface MTLWindow : NSWindow<MTKViewDelegate> {
		
		MTKView *mtl_view;
		id<MTLDevice> mtl_device;
		id<MTLCommandQueue> mtl_queue;
		
		MTLContext context;
		
		MTLSurface surface;
		
		Device device;
		Pipeline pipeline;
		Buffer vertex_buffer;
		Buffer index_buffer;
		
		bool initialized;
	}
	
	-(id)initWithRect: (NSRect)rect;
	
	-(void)mtkView: (MTKView*)view drawableSizeWillChange: (CGSize)size;
	-(void)drawInMTKView: (MTKView*)view;
	
	-(void)keyDown: (NSEvent*)event;
	
@end

/*
 */
@implementation MTLWindow
	
	/*
	 */
	-(id)initWithRect: (NSRect)rect {
		
		initialized = false;
		
		#if EXTERNAL_DEVICE
			
			// create Metal device
			mtl_device = MTLCreateSystemDefaultDevice();
			if(mtl_device == nullptr) {
				TS_LOG(Error, "MTLWindow::initWithRect(): can't get Metal device\n");
				return self;
			}
			
			// create command queue
			mtl_queue = [mtl_device newCommandQueue];
			
			// create external context
			if(!context.create((__bridge void*)mtl_device, (__bridge void*)mtl_queue)) {
				TS_LOG(Error, "MTKWidget::create_context(): can't create context\n");
				return self;
			}
			
			// create surface
			surface = MTLSurface(context);
			if(!surface) {
				TS_LOG(Error, "MTLWindow::initWithRect(): can't create surface\n");
				return self;
			}
			
		#else
			
			// create internal context
			if(!context.create()) {
				TS_LOG(Error, "MTKWidget::create_context(): can't create context\n");
				return self;
			}
			
			// create surface
			surface = MTLSurface(context);
			if(!surface) {
				TS_LOG(Error, "MTLWindow::initWithRect(): can't create surface\n");
				return self;
			}
			
			// internal device
			mtl_device = (__bridge id<MTLDevice>)surface.getDevice();
			mtl_queue = (__bridge id<MTLCommandQueue>)surface.getQueue();
			
		#endif
		
		// create window
		NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskResizable | NSWindowStyleMaskClosable;
		self = [super initWithContentRect:rect styleMask:style backing:NSBackingStoreBuffered defer:YES];
		self.releasedWhenClosed = YES;
		
		// create Metal view
		mtl_view = [[MTKView alloc] initWithFrame:rect device:mtl_device];
		mtl_view.colorPixelFormat = MTLPixelFormatBGRA8Unorm;
		if(mtl_device.isDepth24Stencil8PixelFormatSupported) mtl_view.depthStencilPixelFormat = MTLPixelFormatDepth24Unorm_Stencil8;
		else mtl_view.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
		mtl_view.sampleCount = 4;
		mtl_view.delegate = self;
		
		// window context view
		self.contentView = mtl_view;
		
		// create surface
		surface.setSize((uint32_t)rect.size.width, (uint32_t)rect.size.height);
		surface.setColorFormat(FormatBGRAu8n);
		if(mtl_device.isDepth24Stencil8PixelFormatSupported) surface.setDepthFormat(FormatDu24Su8);
		else surface.setDepthFormat(FormatDf32Su8);
		surface.setMultisample(mtl_view.sampleCount);
		
		// create device
		device = Device(surface);
		if(!device) return self;
		
		// create pipeline
		pipeline = device.createPipeline();
		pipeline.setUniformMask(0, Shader::MaskVertex);
		pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 6);
		pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 6);
		pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
		pipeline.setColorFormat(surface.getColorFormat());
		pipeline.setDepthFormat(surface.getDepthFormat());
		pipeline.setMultisample(surface.getMultisample());
		if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return self;
		if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return self;
		if(!pipeline.create()) return self;
		
		// create mesh geometry
		#include "main_mesh.h"
		vertex_buffer = device.createBuffer(Buffer::FlagVertex, mesh_vertices, sizeof(float32_t) * num_mesh_vertices);
		index_buffer = device.createBuffer(Buffer::FlagIndex, mesh_indices, sizeof(uint32_t) * num_mesh_indices);
		if(!vertex_buffer || !index_buffer) return self;
		
		initialized = true;
		
		return self;
	}
	
	/*
	 */
	-(void)mtkView: (MTKView*)view drawableSizeWillChange: (CGSize)size {
		
		// check status
		if(!initialized) return;
		
		// surface size
		surface.setSize((uint32_t)size.width, (uint32_t)size.height);
	}
	
	/*
	 */
	-(void)drawInMTKView: (MTKView*)view {
		
		// check status
		if(!initialized) return;
		
		@autoreleasepool {
			
			// structures
			struct CommonParameters {
				Matrix4x4f projection;
				Matrix4x4f modelview;
				Matrix4x4f transform;
				Vector4f camera;
			};
			
			// render pass descriptor
			MTLRenderPassDescriptor *descriptor = view.currentRenderPassDescriptor;
			surface.setDescriptor((__bridge void*)descriptor);
			
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
				command.drawElements(index_buffer.getSize() / 4);
			}
			target.end();
			
			// flush context
			device.flush();
			
			// present drawable
			id<MTLCommandBuffer> command = (__bridge id<MTLCommandBuffer>)surface.getCommand();
			[command presentDrawable:view.currentDrawable];
			
			// flip context
			device.flip();
		}
	}
	
	/*
	 */
	-(void)keyDown: (NSEvent*)event {
		if(event.keyCode == kVK_Escape) {
			[NSApp stop:nullptr];
		}
	}
	
@end

/*
 */
@interface MTKDelegate : NSObject<NSApplicationDelegate> {
		
		MTLWindow *window;
	}
	
@end

/*
 */
@implementation MTKDelegate
	
	// application finish launching
	-(void)applicationDidFinishLaunching: (NSNotification*)notification {
		
		// screen scale
		CGFloat scale = NSScreen.mainScreen.backingScaleFactor;
		
		// window size
		CGFloat width = 1600.0f / scale;
		CGFloat height = 900.0f / scale;
		NSRect screen = NSScreen.mainScreen.frame;
		CGFloat x = (screen.size.width - width) / 2.0f;
		CGFloat y = (screen.size.height - height) / 2.0f;
		
		// create window
		window = [[MTLWindow alloc] initWithRect:NSMakeRect(x, y, width, height)];
		[window makeKeyAndOrderFront:nullptr];
		window.title = @"Metal Tellusim::MTLWindow";
	}
	
	// exit on last window close
	-(BOOL)applicationShouldTerminateAfterLastWindowClosed: (NSApplication*)app {
		return YES;
	}
	
@end

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// initialize application
	[NSApplication sharedApplication];
	NSApp.activationPolicy = NSApplicationActivationPolicyRegular;
	NSApp.presentationOptions = NSApplicationPresentationDefault;
	
	// application delegate
	MTKDelegate *delegate = [[MTKDelegate alloc] init];
	NSApp.delegate = delegate;
	
	// run application
	[NSApp run];
	
	return 0;
}
