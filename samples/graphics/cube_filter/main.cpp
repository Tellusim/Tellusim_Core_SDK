// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimPipeline.h>
#include <graphics/TellusimCubeFilter.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::CubeFilter", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// create cube filter
	CubeFilter cube_filter;
	if(!cube_filter.create(device, CubeFilter::FlagsAll, 3, 1024, 256)) return 1;
	
	// create cube textures
	Texture cube_texture = device.loadTexture("texture_cube.exr");
	Texture panorama_texture = device.loadTexture("texture_panorama.hdr");
	Texture render_cube_texture = device.createTextureCube(FormatRGBAf16, 32, Texture::FlagSource | Texture::FlagSurface | Texture::FlagMipmaps);
	Texture render_panorama_texture = device.createTexture2D(FormatRGBAf16, 256, 128, Texture::FlagSource | Texture::FlagSurface | Texture::FlagMipmaps);
	Texture mipmaps_cube_texture = device.createTextureCube(FormatRGBAf16, 256, Texture::FlagSource | Texture::FlagSurface | Texture::FlagMipmaps);
	if(!cube_texture || !panorama_texture || !render_cube_texture || !render_panorama_texture || !mipmaps_cube_texture) return 1;
	
	// create filter buffer
	Buffer filter_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(Vector4f) * 32);
	if(!filter_buffer) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 8);
	pipeline.setMultisample(window.getMultisample());
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create trilinear sampler
	Sampler sampler = device.createSampler(Sampler::FilterTrilinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create sphere geometry
	#include "main_sphere.h"
	Buffer sphere_vertex_buffer = device.createBuffer(Buffer::FlagVertex, sphere_vertices, sizeof(float32_t) * num_sphere_vertices);
	Buffer sphere_index_buffer = device.createBuffer(Buffer::FlagIndex, sphere_indices, sizeof(uint32_t) * num_sphere_indices);
	if(!sphere_vertex_buffer || !sphere_index_buffer) return 1;
	
	// create queries
	Query filter_query, render_cube_query, render_panorama_query, mipmaps_query;
	if(device.hasQuery(Query::TypeTime)) {
		filter_query = device.createQuery(Query::TypeTime);
		render_cube_query = device.createQuery(Query::TypeTime);
		render_panorama_query = device.createQuery(Query::TypeTime);
		mipmaps_query = device.createQuery(Query::TypeTime);
		if(!filter_query || !render_cube_query || !render_panorama_query || !mipmaps_query) return 1;
	}
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// FPS counter
		if(fps > 0.0f) {
			String filter_time = String::fromTime((filter_query && filter_query.isAvailable()) ? filter_query.getTime() : 0);
			String render_cube_time = String::fromTime((render_cube_query && render_cube_query.isAvailable()) ? render_cube_query.getTime() : 0);
			String render_panorama_time = String::fromTime((render_panorama_query && render_panorama_query.isAvailable()) ? render_panorama_query.getTime() : 0);
			String mipmaps_time = String::fromTime((mipmaps_query && mipmaps_query.isAvailable()) ? mipmaps_query.getTime() : 0);
			window.setTitle(String::format("%s FPS: %.1f %s/%s/%s/%s", title.get(), fps, filter_time.get(), render_cube_time.get(), render_panorama_time.get(), mipmaps_time.get()).get());
		}
		
		// cube filter
		{
			Compute compute = device.createCompute();
			
			// source texture
			Texture *texture = &cube_texture;
			if(window.getKeyboardKey('p')) texture = &panorama_texture;
			
			// filter source texture
			if(filter_query) compute.beginQuery(filter_query);
			cube_filter.dispatch(compute, filter_buffer, 0, *texture);
			if(filter_query) compute.endQuery(filter_query);
			
			// render cube texture
			if(render_cube_query) compute.beginQuery(render_cube_query);
			cube_filter.dispatch(compute, render_cube_texture, filter_buffer, 0);
			if(render_cube_query) compute.endQuery(render_cube_query);
			
			// render panorama texture
			if(render_panorama_query) compute.beginQuery(render_panorama_query);
			cube_filter.dispatch(compute, render_panorama_texture, filter_buffer, 0);
			if(render_panorama_query) compute.endQuery(render_panorama_query);
			
			// create mipmaps texture
			if(mipmaps_query) compute.beginQuery(mipmaps_query);
			cube_filter.dispatch(compute, mipmaps_cube_texture, *texture);
			if(mipmaps_query) compute.endQuery(mipmaps_query);
		}
		
		// save textures
		if(window.getKeyboardKey('s', true)) {
			
			Image cube_image;
			cube_image.createCube(FormatRGBAf16, render_cube_texture.getWidth(), Image::FlagMipmaps);
			if(device.getTexture(render_cube_texture, cube_image)) cube_image.save("test_cube.exr");
			
			Image panorama_image;
			panorama_image.create2D(FormatRGBAf16, render_panorama_texture.getWidth(), render_panorama_texture.getHeight(), Image::FlagMipmaps);
			if(device.getTexture(render_panorama_texture, panorama_image)) panorama_image.save("test_panorama.exr");
		}
		
		// flush texture
		device.flushTexture(render_cube_texture);
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(0.0f, 6.0f, 0.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			
			// set pipeline
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			if(window.getKeyboardKey('m')) command.setTexture(0, mipmaps_cube_texture);
			else command.setTexture(0, render_cube_texture);
			command.setVertexBuffer(0, sphere_vertex_buffer);
			command.setIndexBuffer(FormatRu32, sphere_index_buffer);
			
			// draw spheres
			for(int32_t z = -3; z <= 3; z++) {
				for(int32_t x = -6; x <= 6; x++) {
					common_parameters.transform = Matrix4x4f::translate((float32_t)x, 0.0f, (float32_t)z) * Matrix4x4f::rotateZ((time + x) * 32.0f) * Matrix4x4f::rotateY((time + z) * 32.0f);
					command.setUniform(0, common_parameters);
					command.drawElements(num_sphere_indices);
				}
			}
		}
		target.end();
		
		if(!window.present()) return false;
		
		// check errors
		device.check();
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
