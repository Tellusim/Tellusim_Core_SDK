// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <webp/decode.h>
#include <webp/encode.h>
#if _WIN32
	#pragma comment(lib, "webp.lib")
#endif

#include <core/TellusimLog.h>
#include <core/TellusimStream.h>
#include <format/TellusimImage.h>

/*
 */
#define WEBP_MAGIC	0x46464952

/*
 */
namespace Tellusim {
	
	/*
	 */
	class ImageStreamWEBP : public ImageStream {
			
		public:
			
			ImageStreamWEBP(const char *name, uint32_t magic) : ImageStream(FlagLoadSave, name, magic) { }
			
			virtual bool info(Stream &stream, Image &image, Image::Flags flags, uint32_t offset, Async *async);
			virtual bool load(Stream &stream, Image &image, Image::Flags flags, uint32_t offset, Async *async);
			virtual bool save(Stream &stream, const Image &image, Image::Flags flags, uint32_t quality);
			
		private:
			
			static int32_t writer(const uint8_t *data, size_t size, const WebPPicture *picture);
	};
	
	/*
	 */
	bool ImageStreamWEBP::info(Stream &stream, Image &image, Image::Flags flags, uint32_t offset, Async *async) {
		
		// stream data
		size_t size = stream.getSize();
		const uint8_t *data = stream.getData();
		
		// read stream
		Array<uint8_t> data_buffer;
		if(data == nullptr) {
			data_buffer.resize((uint32_t)size);
			if(stream.read(data_buffer.get(), size) != size) {
				TS_LOGE(Error, "ImageStreamWEBP::info(): can't read stream\n");
				return false;
			}
			data = data_buffer.get();
		}
		
		// init config
		WebPDecoderConfig config;
		WebPInitDecoderConfig(&config);
		
		// get features
		VP8StatusCode ret = WebPGetFeatures(data, size, &config.input);
		if(ret != VP8_STATUS_OK) {
			TS_LOGF(Error, "ImageStreamWEBP::info(): can't get features %u\n", ret);
			return false;
		}
		
		// create image
		Format format = (config.input.has_alpha) ? FormatRGBAu8n : FormatRGBu8n;
		image.create2D(format, config.input.width, config.input.height, Image::FlagNoAllocate);
		
		return true;
	}
	
	/*
	 */
	bool ImageStreamWEBP::load(Stream &stream, Image &image, Image::Flags flags, uint32_t offset, Async *async) {
		
		// stream data
		size_t size = stream.getSize();
		const uint8_t *data = stream.getData();
		
		// read stream
		Array<uint8_t> data_buffer;
		if(data == nullptr) {
			data_buffer.resize((uint32_t)size);
			if(stream.read(data_buffer.get(), size) != size) {
				TS_LOGE(Error, "ImageStreamWEBP::load(): can't read stream\n");
				return false;
			}
			data = data_buffer.get();
		}
		
		// init config
		WebPDecoderConfig config;
		WebPInitDecoderConfig(&config);
		
		// get features
		VP8StatusCode ret = WebPGetFeatures(data, size, &config.input);
		if(ret != VP8_STATUS_OK) {
			TS_LOGF(Error, "ImageStreamWEBP::load(): can't get features %u\n", ret);
			return false;
		}
		
		// create image
		Format format = (config.input.has_alpha) ? FormatRGBAu8n : FormatRGBu8n;
		image.create2D(format, config.input.width, config.input.height, Image::FlagNoClear);
		
		// external memory
		config.output.colorspace = (config.input.has_alpha) ? MODE_RGBA : MODE_RGB;
		config.output.u.RGBA.rgba = image.getData();
		config.output.u.RGBA.stride = (int32_t)image.getStride();
		config.output.u.RGBA.size = image.getDataSize();
		config.output.is_external_memory = 1;
		
		// decode image
		ret = WebPDecode(data, size, &config);
		if(ret != VP8_STATUS_OK) {
			TS_LOGF(Error, "ImageStreamWEBP::load(): can't decode image %u\n", ret);
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	bool ImageStreamWEBP::save(Stream &stream, const Image &image, Image::Flags flags, uint32_t quality) {
		
		TS_ASSERT(image && "ImageStreamWEBP::save(): image is not allocated");
		
		// check type
		if(!image.is2DType()) {
			TS_LOGF(Error, "ImageStreamWEBP::save(): can't save %s image\n", image.getTypeName());
			return false;
		}
		if(image.hasLayers()) {
			TS_LOGF(Error, "ImageStreamWEBP::save(): can't save %s array image\n", image.getTypeName());
			return false;
		}
		
		// init config
		WebPConfig config;
		WebPConfigInit(&config);
		
		// encoder quality
		config.quality = (float32_t)quality;
		
		// init picture
		WebPPicture picture;
		WebPPictureInit(&picture);
		
		// picture size
		picture.width = image.getWidth();
		picture.height = image.getHeight();
		
		// picture writer
		picture.writer = writer;
		picture.custom_ptr = &stream;
		
		// image format
		int32_t ret = 0;
		Format format = image.getFormat();
		if(format == FormatRGBu8 || format == FormatRGBu8n) ret = WebPPictureImportRGB(&picture, image.getData(), (int32_t)image.getStride());
		else if(format == FormatRGBAu8 || format == FormatRGBAu8n) ret = WebPPictureImportRGBA(&picture, image.getData(), (int32_t)image.getStride());
		else {
			TS_LOGF(Error, "ImageStreamWEBP::save(): can't save %s image\n", image.getFormatName());
			WebPPictureFree(&picture);
			return false;
		}
		
		// encode image
		if(!ret || !WebPEncode(&config, &picture)) {
			TS_LOGF(Error, "ImageStreamWEBP::save(): can't encode image %u\n", picture.error_code);
			WebPPictureFree(&picture);
			return false;
		}
		
		// free picture
		WebPPictureFree(&picture);
		
		return true;
	}
	
	/*
	 */
	int32_t ImageStreamWEBP::writer(const uint8_t *data, size_t size, const WebPPicture *picture) {
		Stream *stream = (Stream*)picture->custom_ptr;
		return (stream->write(data, size) == size);
	}
	
	/*
	 */
	static ImageStreamWEBP image_stream_webp("webp", WEBP_MAGIC);
}
