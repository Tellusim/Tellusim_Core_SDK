// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	window_flags |= Window::FlagMultisample4;
	String title = String::format("%s Tellusim::Stencil", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
		Vector4f color;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// load color shader
	Shader fragment_color_shader = device.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1; COLOR=1");
	if(!fragment_color_shader) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 8);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setMultisample(window.getMultisample());
	pipeline.setStencilMask(0xff);
	if(window.getPlatform() == PlatformVK) {
		pipeline.setFrontMode(Pipeline::FrontModeCW);
	}
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	
	// create depth less pipeline
	Pipeline depth_less_pipeline = device.createPipeline(pipeline);
	depth_less_pipeline.setDepthFunc(Pipeline::DepthFuncLess);
	depth_less_pipeline.setColorMask(Pipeline::ColorMaskNone);
	depth_less_pipeline.setCullMode(Pipeline::CullModeBack);
	if(!depth_less_pipeline.create()) return 1;
	
	// create depth subtract pipeline
	Pipeline depth_subtract_pipeline = device.createPipeline(pipeline);
	depth_subtract_pipeline.setDepthMask(Pipeline::DepthMaskNone);
	depth_subtract_pipeline.setDepthFunc(Pipeline::DepthFuncLess);
	depth_subtract_pipeline.setColorMask(Pipeline::ColorMaskNone);
	depth_subtract_pipeline.setStencilBackFunc(Pipeline::StencilFuncAlways, Pipeline::StencilOpDecrWrap);
	depth_subtract_pipeline.setStencilFrontFunc(Pipeline::StencilFuncAlways, Pipeline::StencilOpIncrWrap);
	if(!depth_subtract_pipeline.create()) return 1;
	
	// create depth replace pipeline
	Pipeline depth_replace_pipeline = device.createPipeline(pipeline);
	depth_replace_pipeline.setDepthFunc(Pipeline::DepthFuncGreater);
	depth_replace_pipeline.setColorMask(Pipeline::ColorMaskNone);
	depth_replace_pipeline.setStencilFunc(Pipeline::StencilFuncEqual, Pipeline::StencilOpKeep, Pipeline::StencilOpDecrWrap, Pipeline::StencilOpDecrWrap);
	depth_replace_pipeline.setCullMode(Pipeline::CullModeFront);
	if(!depth_replace_pipeline.create()) return 1;
	
	// create depth remove pipeline
	Pipeline depth_remove_pipeline = device.createPipeline(pipeline);
	depth_remove_pipeline.setDepthFunc(Pipeline::DepthFuncLess);
	depth_remove_pipeline.setColorMask(Pipeline::ColorMaskNone);
	depth_remove_pipeline.setCullMode(Pipeline::CullModeFront);
	if(!depth_remove_pipeline.create()) return 1;
	
	// create color outside pipeline
	Pipeline color_outside_pipeline = device.createPipeline(pipeline);
	color_outside_pipeline.addShader(fragment_color_shader);
	color_outside_pipeline.setDepthFunc(Pipeline::DepthFuncEqual);
	color_outside_pipeline.setCullMode(Pipeline::CullModeBack);
	if(!color_outside_pipeline.create()) return 1;
	
	// create color inside pipeline
	Pipeline color_inside_pipeline = device.createPipeline(pipeline);
	color_inside_pipeline.addShader(fragment_color_shader);
	color_inside_pipeline.setDepthFunc(Pipeline::DepthFuncEqual);
	color_inside_pipeline.setCullMode(Pipeline::CullModeFront);
	if(!color_inside_pipeline.create()) return 1;
	
	// create pipeline
	pipeline.addShader(fragment_color_shader);
	pipeline.setDepthFunc(Pipeline::DepthFuncLess);
	pipeline.setCullMode(Pipeline::CullModeBack);
	if(!pipeline.create()) return 1;
	
	// create cube geometry
	#include "main_cube.h"
	Buffer cube_vertex_buffer = device.createBuffer(Buffer::FlagVertex, cube_vertices, sizeof(float32_t) * num_cube_vertices);
	Buffer cube_index_buffer = device.createBuffer(Buffer::FlagIndex, cube_indices, sizeof(uint32_t) * num_cube_indices);
	if(!cube_vertex_buffer || !cube_index_buffer) return 1;
	
	// create icosa geometry
	#include "main_icosa.h"
	Buffer icosa_vertex_buffer = device.createBuffer(Buffer::FlagVertex, icosa_vertices, sizeof(float32_t) * num_icosa_vertices);
	Buffer icosa_index_buffer = device.createBuffer(Buffer::FlagIndex, icosa_indices, sizeof(uint32_t) * num_icosa_indices);
	if(!icosa_vertex_buffer || !icosa_index_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// window target
		target.setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(1.0f, 1.0f, 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			
			// cube transforms
			Matrix4x4f cube_transforms[13];
			float32_t a = 0.42f + sin(time) * 0.02f;
			float32_t b = 0.55f + sin(time) * 0.02f;
			Matrix4x4f cube_transform = Matrix4x4f::rotateZ(time * 16.0f) * Matrix4x4f::rotateX(time * 16.0f);
			cube_transforms[0] =  Matrix4x4f::scale(2.0f, a, a) * Matrix4x4f::translate( 0.0f,  b,  b);
			cube_transforms[1] =  Matrix4x4f::scale(2.0f, a, a) * Matrix4x4f::translate( 0.0f,  b, -b);
			cube_transforms[2] =  Matrix4x4f::scale(2.0f, a, a) * Matrix4x4f::translate( 0.0f, -b,  b);
			cube_transforms[3] =  Matrix4x4f::scale(2.0f, a, a) * Matrix4x4f::translate( 0.0f, -b, -b);
			cube_transforms[4] =  Matrix4x4f::scale(a, 2.0f, a) * Matrix4x4f::translate( b,  0.0f,  b);
			cube_transforms[5] =  Matrix4x4f::scale(a, 2.0f, a) * Matrix4x4f::translate( b,  0.0f, -b);
			cube_transforms[6] =  Matrix4x4f::scale(a, 2.0f, a) * Matrix4x4f::translate(-b,  0.0f,  b);
			cube_transforms[7] =  Matrix4x4f::scale(a, 2.0f, a) * Matrix4x4f::translate(-b,  0.0f, -b);
			cube_transforms[8] =  Matrix4x4f::scale(a, a, 2.0f) * Matrix4x4f::translate( b,  b,  0.0f);
			cube_transforms[9] =  Matrix4x4f::scale(a, a, 2.0f) * Matrix4x4f::translate( b, -b,  0.0f);
			cube_transforms[10] = Matrix4x4f::scale(a, a, 2.0f) * Matrix4x4f::translate(-b,  b,  0.0f);
			cube_transforms[11] = Matrix4x4f::scale(a, a, 2.0f) * Matrix4x4f::translate(-b, -b,  0.0f);
			cube_transforms[12] = Matrix4x4f::scale(Vector3f((b * a + a * 0.5f) * 2.0f));
			
			// draw cube
			auto draw_cube = [&](const Matrix4x4f &transform) {
				command.setVertexBuffer(0, cube_vertex_buffer);
				command.setIndexBuffer(FormatRu32, cube_index_buffer);
				common_parameters.transform = cube_transform * transform;
				command.setUniform(0, common_parameters);
				command.drawElements(num_cube_indices);
			};
			
			// depth less pass
			command.setPipeline(depth_less_pipeline);
			draw_cube(Matrix4x4f::identity);
			
			for(uint32_t j = 0; j < TS_COUNTOF(cube_transforms); j++) {
				for(uint32_t i = 0; i < TS_COUNTOF(cube_transforms) - j; i++) {
					
					// depth subtract pass
					command.setPipeline(depth_subtract_pipeline);
					command.setStencilRef(0x00);
					draw_cube(cube_transforms[i]);
					
					// depth replace pass
					command.setPipeline(depth_replace_pipeline);
					command.setStencilRef(0x01);
					draw_cube(cube_transforms[i]);
				}
			}
			
			// depth remove pass
			command.setPipeline(depth_remove_pipeline);
			draw_cube(Matrix4x4f::identity);
			
			// draw outside pass
			command.setPipeline(color_outside_pipeline);
			common_parameters.color = Vector4f(0.3f, 0.8f, 0.8f, 1.0f);
			draw_cube(Matrix4x4f::identity);
			
			// draw inside pass
			command.setPipeline(color_inside_pipeline);
			common_parameters.color = Vector4f(0.3f, 0.8f, 0.3f, -1.0f);
			for(uint32_t i = 0; i < TS_COUNTOF(cube_transforms); i++) {
				draw_cube(cube_transforms[i]);
			}
			
			// draw icosa
			command.setPipeline(pipeline);
			command.setVertexBuffer(0, icosa_vertex_buffer);
			command.setIndexBuffer(FormatRu32, icosa_index_buffer);
			common_parameters.transform = Matrix4x4f::rotateZ(-time * 16.0f) * Matrix4x4f::rotateX(time * 16.0f) * Matrix4x4f::scale(0.9f);
			common_parameters.color = Vector4f(0.7f, 0.7f, 0.7f, 1.0f);
			command.setUniform(0, common_parameters);
			command.drawElements(num_icosa_indices);
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
