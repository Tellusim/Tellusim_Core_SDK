// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimFile.h>
#include <core/TellusimDirectory.h>
#include <math/TellusimRandom.h>
#include <format/TellusimImage.h>
#include <platform/TellusimPlatforms.h>

#include "BlueNoise.h"

/*
 */
#define CACHE_PATH		".tellusim/"
#define CACHE_NAME		"noise_shader.cache"

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using namespace Tellusim;
	
	// initialize application
	App app(argc, argv);
	
	// print help
	if(argc < 2 || String(argv[1]) == "-h") {
		Log::printf("Tellusim Blue Noise Image Generator (build " __DATE__ " https://tellusim.com/)\nUsage: %s -o noise.png\n", argv[0]);
		Log::print("  -i <filename>     Input image\n");
		Log::print("  -o <filename>     Output image\n");
		Log::print("  -os <filename>    Spatial image\n");
		Log::print("  -of <filename>    Forward image\n");
		Log::print("  -ox <filename>    Forward X image\n");
		Log::print("  -oy <filename>    Forward Y image\n");
		Log::print("  -oh <filename>    Histogram output\n");
		Log::print("  -bits <bits>      Image bits (8)\n");
		Log::print("  -size <size>      Image size (128)\n");
		Log::print("  -width <width>    Image width (128)\n");
		Log::print("  -height <height>  Image width (128)\n");
		Log::print("  -layers <layers>  Image layers (1)\n");
		Log::print("  -seed <value>     Random seed (random)\n");
		Log::print("  -init <value>     Initial pixels (10%)\n");
		Log::print("  -aspect <value>   Noise aspect ratio (1.0)\n");
		Log::print("  -sigma <value>    Gaussian sigma (2.0)\n");
		Log::print("  -epsilon <value>  Quadratic epsilon (0.01)\n");
		Log::print("  -power <value>    Quadratic power (1.0)\n");
		Log::print("  -device <index>   Computation device index\n");
		return 0;
	}
	
	// parameters
	String input_name;
	String output_name;
	String spatial_name;
	String forward_name;
	String forward_x_name;
	String forward_y_name;
	String histogram_name;
	uint32_t init = 10;
	uint32_t bits = 8;
	uint32_t width = 128;
	uint32_t height = 128;
	uint32_t layers = 1;
	uint32_t seed = (uint32_t)Time::current();
	float32_t aspect = 1.0f;
	float32_t sigma = 2.0f;
	float32_t epsilon = 0.01f;
	float32_t power = 1.0f;
	
	// command line arguments
	for(int32_t i = 1; i < argc; i++) {
		const char *s = argv[i];
		
		// commands
		if(s[0] == '-') {
			while(*s == '-') s++;
			String command = String(s);
			
			if(command == "i" && i + 1 < argc) input_name = argv[++i];
			else if(command == "o" && i + 1 < argc) output_name = argv[++i];
			else if(command == "os" && i + 1 < argc) spatial_name = argv[++i];
			else if(command == "of" && i + 1 < argc) forward_name = argv[++i];
			else if(command == "ox" && i + 1 < argc) forward_x_name = argv[++i];
			else if(command == "oy" && i + 1 < argc) forward_y_name = argv[++i];
			else if(command == "oh" && i + 1 < argc) histogram_name = argv[++i];
			else if((command == "bits" || command == "b") && i + 1 < argc) bits = String::tou32(argv[++i]);
			else if((command == "size" || command == "s") && i + 1 < argc) width = height = String::tou32(argv[++i]);
			else if((command == "width" || command == "w") && i + 1 < argc) width = String::tou32(argv[++i]);
			else if((command == "height" || command == "h") && i + 1 < argc) height = String::tou32(argv[++i]);
			else if((command == "layers" || command == "l") && i + 1 < argc) layers = String::tou32(argv[++i]);
			else if((command == "seed" || command == "r") && i + 1 < argc) seed = String::tou32(argv[++i]);
			else if((command == "init" || command == "p") && i + 1 < argc) init = String::tou32(argv[++i]);
			else if((command == "aspect" || command == "as") && i + 1 < argc) aspect = clamp(String::tof32(argv[++i]), 1.0f / 32.0f, 32.0f);
			else if((command == "sigma" || command == "si") && i + 1 < argc) sigma = max(String::tof32(argv[++i]), 0.0f);
			else if((command == "epsilon" || command == "e") && i + 1 < argc) epsilon = max(String::tof32(argv[++i]), 0.0f);
			else if((command == "power" || command == "po") && i + 1 < argc) power = max(String::tof32(argv[++i]), 0.0f);
		}
		// unknown command
		else {
			TS_LOGF(Error, "%s: invalid command line option \"%s\"\n", argv[0], argv[i]);
			return 1;
		}
	}
	
	// input image
	Image input_image;
	if(input_name) {
		if(!input_image.load(input_name.get())) {
			TS_LOGF(Error, "%s: can't load input image\n", argv[0]);
			return 1;
		}
		width = input_image.getWidth();
		height = input_image.getHeight();
	}
	
	// create context
	Context context(app.getPlatform(), app.getDevice());
	if(!context || !context.create()) {
		TS_LOGF(Error, "%s: can't create context\n", argv[0]);
		return 1;
	}
	
	// create device
	Device device(context);
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOGF(Error, "%s: compute shader is not supported\n", argv[0]);
		return 1;
	}
	Log::printf("Platform: %s Device: %s\n", device.getPlatformName(), device.getName().get());
	
	// noise shader cache
	String path = Directory::getHomeDirectory() + "/" + CACHE_PATH;
	if(Directory::isDirectory(path) || Directory::createDirectory(path)) {
		String name = Directory::getHomeDirectory() + "/" + CACHE_PATH + CACHE_NAME;
		Shader::setCache(name.get());
	}
	
	// create blue noise
	BlueNoise blue_noise;
	if(!blue_noise.create(device, width, height, layers)) {
		TS_LOGF(Error, "%s: can't create BlueNoise\n", argv[0]);
		return 1;
	}
	
	// create image
	if(!input_image) {
		Random<int32_t> random(seed);
		input_image.create2D(FormatRu8n, width, height);
		ImageSampler input_sampler(input_image);
		for(uint32_t i = width * height * init / 100; i > 0; i--) {
			uint32_t x = random.geti32(0, width - 1);
			uint32_t y = random.geti32(0, height - 1);
			input_sampler.set2D(x, y, ImageColor(255u));
		}
		Log::printf("Size: %ux%u Layers: %u Bits: %u Aspect: %g Sigma: %g Epsilon: %g Power: %g Init: %u %% Seed: %u\n", width, height, layers, bits, aspect, sigma, epsilon, power, init, seed);
	} else {
		Log::printf("Size: %ux%u Layers: %u Bits: %u Aspect: %g Sigma: %g Epsilon: %g Power: %g\n", width, height, layers, bits, aspect, sigma, epsilon, power);
	}
	
	// dispatch blue noise
	Image noise_image = blue_noise.dispatch(device, input_image, layers, aspect, sigma, epsilon, power);
	if(!noise_image) {
		TS_LOGF(Error, "%s: can't create noise\n", argv[0]);
		return 1;
	}
	
	// save spatial image
	if(spatial_name) {
		Image spatial_image;
		uint32_t width = noise_image.getWidth();
		uint32_t height = noise_image.getHeight();
		spatial_image.create2D(FormatRGf32, width, height);
		ImageSampler spatial_sampler(spatial_image);
		ImageSampler noise_sampler(noise_image);
		for(uint32_t y = 0; y < noise_image.getHeight(); y++) {
			for(uint32_t x = 0; x < noise_image.getWidth(); x++) {
				ImageColor color = noise_sampler.get2D(x, y);
				uint32_t index = (uint32_t)(color.f.r * (width * height - 1) + 0.5f);
				uint32_t Y = index / width;
				uint32_t X = index % width;
				spatial_sampler.set2D(X, Y, ImageColor((float32_t)x / width, (float32_t)y / height, 0.0f, 0.0f));
			}
		}
		if(!spatial_image.save(spatial_name)) {
			TS_LOGF(Error, "%s: can't save output spatial image\n", argv[0]);
			return 1;
		}
	}
	
	// noise image format
	if(bits == 8) noise_image = noise_image.toFormat(FormatRu8n);
	else if(bits == 16) noise_image = noise_image.toFormat(FormatRu16n);
	else if(bits != 32) {
		TS_LOGF(Error, "%s: invalid image bits %u\n", argv[0], bits);
		return 1;
	}
	
	// save noise image
	if(output_name && noise_image && !noise_image.save(output_name.get())) {
		TS_LOGF(Error, "%s: can't save output image\n", argv[0]);
		return 1;
	}
	
	// forward transform image
	if(forward_name && ispot(width) && ispot(height)) {
		Image forward_image;
		if(layers > 1) {
			for(uint32_t l = 0; l < layers; l++) {
				Image forward_layer = blue_noise.dispatchForward(device, noise_image.getSlice(Layer(l)));
				if(!forward_image && forward_layer) forward_image.create2D(forward_layer.getFormat(), forward_layer.getWidth(), forward_layer.getHeight(), layers);
				if(forward_layer) forward_image.copy(forward_layer, Layer(l));
			}
		} else {
			forward_image = blue_noise.dispatchForward(device, noise_image);
		}
		if(forward_image && !forward_image.save(forward_name.get())) {
			TS_LOGF(Error, "%s: can't save forward image\n", argv[0]);
			return 1;
		}
	}
	
	// forward transform X slice image
	if(forward_x_name && layers > 1 && ispot(width) && ispot(layers)) {
		Image slice_image;
		Image forward_image;
		slice_image.create2D(noise_image.getFormat(), width, layers);
		for(uint32_t y = 0; y < height; y++) {
			ImageSampler slice_sampler(slice_image);
			for(uint32_t l = 0; l < layers; l++) {
				ImageSampler noise_sampler(noise_image, Layer(l));
				for(uint32_t x = 0; x < width; x++) {
					slice_sampler.set2D(x, l, noise_sampler.get2D(x, y));
				}
			}
			Image forward_layer = blue_noise.dispatchForward(device, slice_image);
			if(!forward_image && forward_layer) forward_image.create2D(forward_layer.getFormat(), forward_layer.getWidth(), forward_layer.getHeight(), height);
			if(forward_layer) forward_image.copy(forward_layer, Layer(y));
		}
		if(forward_image && !forward_image.save(forward_x_name.get())) {
			TS_LOGF(Error, "%s: can't save forward X image\n", argv[0]);
			return 1;
		}
	}
	
	// forward transform Y slice image
	if(forward_y_name && layers > 1 && ispot(height) && ispot(layers)) {
		Image slice_image;
		Image forward_image;
		slice_image.create2D(noise_image.getFormat(), layers, height);
		for(uint32_t x = 0; x < width; x++) {
			ImageSampler slice_sampler(slice_image);
			for(uint32_t l = 0; l < layers; l++) {
				ImageSampler noise_sampler(noise_image, Layer(l));
				for(uint32_t y = 0; y < height; y++) {
					slice_sampler.set2D(l, y, noise_sampler.get2D(x, y));
				}
			}
			Image forward_layer = blue_noise.dispatchForward(device, slice_image);
			if(!forward_image && forward_layer) forward_image.create2D(forward_layer.getFormat(), forward_layer.getWidth(), forward_layer.getHeight(), width);
			if(forward_layer) forward_image.copy(forward_layer, Layer(x));
		}
		if(forward_image && !forward_image.save(forward_y_name.get())) {
			TS_LOGF(Error, "%s: can't save forward Y image\n", argv[0]);
			return 1;
		}
	}
	
	// histogram output
	if(histogram_name) {
		Array<uint32_t> histogram;
		if(noise_image.isFloatFormat()) histogram.resize(width * height, 0u);
		else histogram.resize(1 << bits, 0u);
		for(uint32_t l = 0; l < layers; l++) {
			ImageSampler sampler(noise_image, Layer(l));
			if(noise_image.isFloatFormat()) {
				for(uint32_t i = 0; i < sampler.getTexels(); i++) {
					ImageColor pixel = sampler.getTexel(i);
					histogram[(uint32_t)((histogram.size() - 1) * pixel.f.r + 0.5f)]++;
				}
			} else {
				for(uint32_t i = 0; i < sampler.getTexels(); i++) {
					ImageColor pixel = sampler.getTexel(i);
					histogram[pixel.u.r]++;
				}
			}
		}
		File file;
		if(file.open(histogram_name.get(), "wb")) {
			for(uint32_t i = 0; i < histogram.size(); i++) {
				file.printf("%u", histogram[i]);
				file.puts(((i + 1) % 64 == 0) ? "\n" : " ");
			}
			file.close();
		} else {
			TS_LOGF(Error, "%s: can't save histogram\n", argv[0]);
			return 1;
		}
	}
	
	return 0;
}
