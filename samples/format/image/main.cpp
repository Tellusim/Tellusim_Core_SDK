// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimString.h>
#include <core/TellusimStream.h>
#include <format/TellusimImage.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// flip image
	if(1) {
		Image image;
		Region region = Region(20, 20, 100, 100);
		if(!image.load("test_stream.jpg")) return 1;
		if(!image.flipX(region) || !image.save("test_save_flip_x_r.png") || !image.flipX(region)) return 1;
		if(!image.flipY(region) || !image.save("test_save_flip_y_r.png") || !image.flipY(region)) return 1;
		if(!image.flipX() || !image.save("test_save_flip_x.png") || !image.flipX()) return 1;
		if(!image.flipY() || !image.save("test_save_flip_y.png") || !image.flipY()) return 1;
	}
	
	// copy image
	if(1) {
		Image image;
		Region region = Region(40, 40, 40, 40);
		if(!image.load("test_stream.jpg")) return 1;
		if(!image.copy(image, Origin(0, 0), region)) return 1;
		if(!image.copy(image, Origin(0, 40), region)) return 1;
		if(!image.copy(image, Origin(40, 0), region)) return 1;
		if(!image.save("test_save_copy.png")) return 1;
	}
	
	// rotate image
	if(1) {
		Image image;
		if(!image.load("test_stream.jpg")) return 1;
		if(!image.getRotated(0).save("test_save_rotate_0.png")) return 1;
		if(!image.getRotated(1).save("test_save_rotate_1.png")) return 1;
		if(!image.getRotated(2).save("test_save_rotate_2.png")) return 1;
		if(!image.getRotated(3).save("test_save_rotate_3.png")) return 1;
	}
	
	// resize image
	if(1) {
		Image image;
		if(!image.load("test_stream.png")) return 1;
		if(!image.getResized(Size(32, 32), Image::FilterBox, Image::FilterPoint).save("test_save_min_b.png")) return 1;
		if(!image.getResized(Size(32, 32), Image::FilterPoint, Image::FilterPoint).save("test_save_min_p.png")) return 1;
		if(!image.getResized(Size(1024, 1024), Image::FilterPoint, Image::FilterPoint).save("test_save_mag_p.png")) return 1;
		if(!image.getResized(Size(1024, 1024), Image::FilterLinear, Image::FilterLinear).save("test_save_mag_l.png")) return 1;
		if(!image.getResized(Size(1024, 1024), Image::FilterCubic, Image::FilterCubic).save("test_save_mag_c.png")) return 1;
	}
	
	// convert to format
	if(1) {
		Image image;
		if(!image.load("test_stream.png")) return 1;
		if(!image.toFormat(FormatRu16n).toFormat(FormatRu8).save("test_format_Ru8.png")) return 1;
		if(!image.toFormat(FormatRGu16n).toFormat(FormatRGu8).save("test_format_RGu8.png")) return 1;
		if(!image.toFormat(FormatRGBu16n).toFormat(FormatRGBu8).save("test_format_RGBu8.png")) return 1;
		if(!image.toFormat(FormatRGBAu16n).toFormat(FormatRGBAu8).save("test_format_RGBAu8.png")) return 1;
	}
	
	// Cube image sampler
	if(1) {
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Image image;
		image.createCube(FormatRGBu8n, 256);
		
		ImageSampler sampler(image);
		for(float32_t phi = 0; phi < Pi2; phi += 1.0f / 512.0f) {
			for(float32_t theta = 0; theta < Pi2; theta += 1.0f / 256.0f) {
				float32_t x = sin(phi) * sin(theta);
				float32_t y = cos(phi) * sin(theta);
				float32_t z = cos(theta);
				uint32_t r = (uint32_t)((x * 0.5f + 0.5f) * 255.0f);
				uint32_t g = (uint32_t)((y * 0.5f + 0.5f) * 255.0f);
				uint32_t b = (uint32_t)((z * 0.5f + 0.5f) * 255.0f);
				sampler.setCube(x, y, z, ImageColor(r, g, b, 255u));
			}
		}
		
		image.save("test_sampler_cube.ktx");
	}
	
	// extern image stream
	if(1) {
		
		// extern image format
		class ExternImageStream : public ImageStream {
				
			public:
				
				// register image format
				ExternImageStream(const char *name) : ImageStream(FlagLoadSave, name) { }
				
				// load extern image stream
				virtual bool load(Stream &stream, Image &image, Image::Flags flags, uint32_t offset, Async *async) {
					
					// extern header
					bool status = true;
					String header = stream.readString(&status);
					if(!status || header != "ExternImageStream") return false;
					
					// image parameters
					uint32_t width = stream.readu32(&status);
					uint32_t height = stream.readu32(&status);
					Format format = findFormatName(stream.readString(&status).get());
					if(!status || format == FormatUnknown) return false;
					
					TS_LOGF(Message, "ExternImageStream::load(): load 2D %s %ux%u from %s stream\n", getFormatName(format), width, height, stream.getName().get());
					
					// image data
					if(!image.create2D(format, width, height)) return false;
					if(stream.read(image.getData(), image.getDataSize()) != image.getDataSize()) return 1;
					
					return true;
				}
				
				// save extern image stream
				virtual bool save(Stream &stream, const Image &image, Image::Flags flags, uint32_t quality) {
					
					TS_LOGF(Message, "ExternImageStream::save(): save %s into %s stream\n", image.getDescription().get(), stream.getName().get());
					
					// extern header
					if(!stream.writeString("ExternImageStream")) return 1;
					
					// image parameters
					if(!stream.writeu32(image.getWidth())) return 1;
					if(!stream.writeu32(image.getHeight())) return 1;
					if(!stream.writeString(image.getFormatName())) return 1;
					
					// image data
					if(stream.write(image.getData(), image.getDataSize()) != image.getDataSize()) return 1;
					
					return true;
				}
		};
		
		// regiter image format
		ExternImageStream image_stream("eis");
		
		{
			Image image;
			if(!image.load("test_stream.png")) return 1;
			if(!image.save("test_save.eis")) return 1;
			if(!image.load("test_save.eis")) return 1;
		}
	}
	
	return 0;
}
