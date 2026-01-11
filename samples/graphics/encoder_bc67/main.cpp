// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimContext.h>
#include <graphics/TellusimEncoderBC67.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create context
	Context context(app.getPlatform(), app.getDevice());
	if(!context || !context.create()) return 1;
	
	// create device
	Device device(context);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// print device info
	TS_LOGF(Message, "%s (%s)\n", device.getName().get(), device.getPlatformName());
	
	// shader cache
	Shader::setCache("main.cache");
	
	// create encoder
	EncoderBC67 encoder;
	if(!encoder.create(device, EncoderBC67::FlagsAll)) return 1;
	
	// load texture
	Texture src_texture = device.loadTexture("texture.png");
	
	// encoder formats
	struct EncoderFormat {
		Format format;
		EncoderBC67::Mode mode;
		const char *postfix;
	};
	const EncoderFormat formats[] = {
		{ FormatBC6RGBf16s, EncoderBC67::ModeBC6RGBf16s, "bc6s" },
		{ FormatBC6RGBf16u, EncoderBC67::ModeBC6RGBf16u, "bc6u" },
		{ FormatBC7RGBAu8n, EncoderBC67::ModeBC7RGBAu8n, "bc7"  },
	};
	
	// encode textures
	for(uint32_t i = 0; i < TS_COUNTOF(formats); i++) {
		const EncoderFormat &format = formats[i];
		
		// create intermediate image
		uint32_t width = src_texture.getWidth();
		uint32_t height = src_texture.getHeight();
		uint32_t block_size = getFormatBlockWidth(format.format);
		Image dest_image = Image(Image::Type2D, FormatRGBAu32, Size(udiv(width, block_size), udiv(height, block_size)));
		
		// create intermediate texture
		Texture dest_texture = device.createTexture(dest_image, Texture::FlagSurface | Texture::FlagSource);
		if(!dest_texture) return 1;
		
		// dispatch encoder
		{
			Compute compute = device.createCompute();
			encoder.dispatch(compute, format.mode, dest_texture, src_texture);
		}
		
		// flush context
		context.flush();
		
		// get intermediate image data
		if(!device.getTexture(dest_texture, dest_image)) return 1;
		
		// copy image data
		Image image = Image(Image::Type2D, format.format, Size(width, height));
		memcpy(image.getData(), dest_image.getData(), min(image.getDataSize(), dest_image.getDataSize()));
		
		// save encoded image
		image.save(String::format("texture_%s.dds", format.postfix));
		
		// check errors
		device.check();
	}
	
	// finish context
	context.finish();
	
	return 0;
}
