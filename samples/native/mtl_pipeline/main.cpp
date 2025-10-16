// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <Metal/Metal.h>

#include <common/common.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimSurface.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	App::setPlatform(PlatformMTL);
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::MTLPipeline", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	MTLDevice device(window);
	if(!device) return 1;
	
	// load vertex shader
	MTLShader vertex_shader = MTLShader(device.loadShader(Shader::TypeVertex, "main.metal", "VERTEX_SHADER=1"));
	if(!vertex_shader) return 1;
	
	// load fragment shader
	MTLShader fragment_shader = MTLShader(device.loadShader(Shader::TypeFragment, "main.metal", "FRAGMENT_SHADER=1"));
	if(!fragment_shader) return 1;
	
	// create render pipeline
	id<MTLRenderPipelineState> pipeline_state = nullptr;
	{
		MTLSurface surface = MTLSurface(window.getSurface());
		
		MTLRenderPipelineDescriptor *descriptor = [MTLRenderPipelineDescriptor new];
		descriptor.rasterSampleCount = 1;
		descriptor.vertexFunction = (__bridge id<MTLFunction>)vertex_shader.getFunction();
		descriptor.fragmentFunction = (__bridge id<MTLFunction>)fragment_shader.getFunction();
		descriptor.vertexDescriptor = [MTLVertexDescriptor new];
		descriptor.colorAttachments[0].pixelFormat = (MTLPixelFormat)surface.getColorPixelFormat();
		descriptor.depthAttachmentPixelFormat = (MTLPixelFormat)surface.getDepthPixelFormat();
		descriptor.stencilAttachmentPixelFormat = (MTLPixelFormat)surface.getDepthPixelFormat();
		
		NSError *error = nullptr;
		id<MTLDevice> mtl_device = (__bridge id<MTLDevice>)device.getMTLDevice();
		pipeline_state = [mtl_device newRenderPipelineStateWithDescriptor:descriptor error:&error];
		if(pipeline_state == nullptr) {
			TS_LOG(Error, error.localizedDescription.UTF8String);
			return 1;
		}
	}
	
	// create depth stencil state
	id<MTLDepthStencilState> depth_stencil_state = nullptr;
	{
		MTLDepthStencilDescriptor *descriptor = [MTLDepthStencilDescriptor new];
		descriptor.depthCompareFunction = MTLCompareFunctionAlways;
		descriptor.depthWriteEnabled = NO;
		
		id<MTLDevice> mtl_device = (__bridge id<MTLDevice>)device.getMTLDevice();
		depth_stencil_state = [mtl_device newDepthStencilStateWithDescriptor:descriptor];
	}
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(Color("#8a8b8c"));
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// window target
		target.begin();
		{
			// create Metal command list
			MTLCommand command = MTLCommand(device.createCommand(target));
			
			// get command encoder
			id<MTLRenderCommandEncoder> encoder = (__bridge id<MTLRenderCommandEncoder>)command.getEncoder();
			
			// set state
			[encoder setDepthStencilState:depth_stencil_state];
			[encoder setRenderPipelineState:pipeline_state];
			
			// set cull mode
			[encoder setCullMode:MTLCullModeBack];
			[encoder setFrontFacingWinding:MTLWindingCounterClockwise];
			
			// create parameters
			float32_t parameters[64];
			parameters[0] = (float32_t)target.getWidth() / target.getHeight(),
			parameters[1] = time;
			
			// set parameters
			[encoder setVertexBytes:parameters length:sizeof(parameters) atIndex:0];
			
			// draw triangle
			[encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];
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
