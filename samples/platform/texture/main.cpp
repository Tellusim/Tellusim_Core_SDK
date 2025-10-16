// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <math/TellusimSimd.h>
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
	String title = String::format("%s Tellusim::Texture", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// texture size
	constexpr uint32_t size = 64;
	constexpr float32_t scale = 16.0f;
	constexpr float32_t isize = scale * 2.0f / (size - 1);
	
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
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create cube geometry
	#include "main_cube.h"
	constexpr uint32_t num_vertices = num_cube_vertices;
	constexpr uint32_t num_indices = num_cube_indices;
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex, cube_vertices, sizeof(float32_t) * num_vertices);
	Buffer index_buffer = device.createBuffer(Buffer::FlagIndex, cube_indices, sizeof(uint32_t) * num_indices);
	if(!vertex_buffer || !index_buffer) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterTrilinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create texture
	Image image;
	if(!image.create3D(FormatRGBAu8n, size, size, size)) return 1;
	Texture texture = device.createTexture3D(FormatRGBAu8n, size, size, size, Texture::FlagSource);
	if(!texture) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s FPS: %.1f", title.get(), fps).get());
		
		// update texture
		float32x8_t points_x;
		float32x8_t points_y;
		float32x8_t points_z;
		for(uint32_t i = 0; i < 8; i++) {
			float32_t offset = Pi2 * i / 8;
			points_x.v[i] = (sin(time * 0.5f + offset) * 0.75f + 1.0f) * scale;
			points_y.v[i] = (cos(time * 0.5f + offset) * 0.75f + 1.0f) * scale;
			points_z.v[i] = (sin(time * 1.3f + offset * 2.0f) * 0.75f + 1.0f) * scale;
		}
		
		uint8_t *data = image.getData();
		for(uint32_t z = 0; z < size; z++) {
			float32x8_t dz = points_z - z * isize;
			for(uint32_t y = 0; y < size; y++) {
				float32x8_t dy = points_y - y * isize;
				for(uint32_t x = 0; x < size; x++, data += 4) {
					float32x8_t dx = points_x - x * isize;
					float32x8_t length2 = dx * dx + dy * dy + dz * dz;
					uint32x8_t c = uint32x8_t(rcp(length2 + 1.0f) * 255.0f);
					data[0] = (uint8_t)min(c.x0 + c.w0 + c.z1, 255u);
					data[1] = (uint8_t)min(c.y0 + c.x1 + c.w1, 255u);
					data[2] = (uint8_t)min(c.z0 + c.y1 + c.w1, 255u);
				}
			}
		}
		
		// set texture
		if(image.getFormat() == texture.getFormat() && !device.setTexture(texture, image)) return false;
		else if(!device.setTexture(texture, image.toFormat(texture.getFormat(), Image::FlagFast))) return false;
		device.flushTexture(texture);
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// set texture
			command.setTexture(0, texture);
			command.setSampler(0, sampler);
			
			// set buffers
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			
			// set parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(0.8f, 0.8f, 0.6f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(time * 4.0f);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw geometry
			command.drawElements(num_indices);
		}
		target.end();
		
		if(!window.present()) return false;
		
		device.check();
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
