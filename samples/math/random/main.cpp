// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimArray.h>
#include <core/TellusimString.h>
#include <math/TellusimSimd.h>
#include <math/TellusimVector.h>
#include <math/TellusimRandom.h>
#include <format/TellusimImage.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using Tellusim::int32x4_t;
	using Tellusim::float32x4_t;
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		Random<> random(1);
		
		constexpr uint32_t size = 32;
		constexpr uint32_t num = 1024 * 1024;
		
		uint32_t counter[size] = {};
		for(uint32_t i = 0; i < num; i++) {
			uint32_t v = (uint32_t)(random.getf32() * (float32_t)size);
			if(v < size) counter[v]++;
		}
		uint32_t max_counter = 0;
		for(uint32_t i = 0; i < size; i++) {
			max_counter = max(max_counter, counter[i]);
		}
		Log::printf("%u: ", max_counter);
		for(uint32_t i = 0; i < size; i++) {
			Log::printf("%u ", max_counter - counter[i]);
		}
		Log::print("\n");
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		constexpr uint32_t size = 32;
		constexpr uint32_t num = 1024 * 1024;
		
		Random<int32x4_t, float32x4_t> random(int32x4_t(1));
		
		uint32_t counter[size] = {};
		for(uint32_t i = 0; i < num; i++) {
			uint32_t v = (uint32_t)(random.getf32().x * (float32_t)size);
			if(v < size) counter[v]++;
		}
		uint32_t max_counter = 0;
		for(uint32_t i = 0; i < size; i++) {
			max_counter = max(max_counter, counter[i]);
		}
		Log::printf("%u: ", max_counter);
		for(uint32_t i = 0; i < size; i++) {
			Log::printf("%u ", max_counter - counter[i]);
		}
		Log::print("\n");
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		constexpr uint32_t size = 32;
		constexpr uint32_t num = 1024 * 1024;
		
		using Vector3i = Vector3<int32_t>;
		using Vector3f = Vector3<float32_t>;
		
		Random<Vector3i, Vector3f> random(Vector3i(1));
		
		uint32_t counter[size] = {};
		for(uint32_t i = 0; i < num; i++) {
			uint32_t v = (uint32_t)(random.getf32().x * (float32_t)size);
			if(v < size) counter[v]++;
		}
		uint32_t max_counter = 0;
		for(uint32_t i = 0; i < size; i++) {
			max_counter = max(max_counter, counter[i]);
		}
		Log::printf("%u: ", max_counter);
		for(uint32_t i = 0; i < size; i++) {
			Log::printf("%u ", max_counter - counter[i]);
		}
		Log::print("\n");
	}
	
	if(1) {
		
		Random<int32x4_t, float32x4_t> random(int32x4_t(1, 2, 3, 4));
		
		constexpr uint32_t size = 1024;
		
		Image image;
		image.create2D(FormatRGBu8, size, size);
		
		ImageSampler sampler(image);
		for(uint32_t y = 0; y < image.getHeight(); y++) {
			for(uint32_t x = 0; x < image.getWidth(); x++) {
				sampler.set2D(x, y, ImageColor(random.geti32(255).v));
			}
		}
		
		image.save("test_random.tga");
	}
	
	if(1) {
		
		constexpr uint32_t size = 1024;
		
		constexpr uint32_t samples = size;
		
		using Vector2f = Vector2<float32_t>;
		
		Image image;
		image.create2D(FormatRGBu8, size, size);
		
		ImageSampler sampler(image);
		for(uint32_t i = 0; i < samples; i++) {
			Vector2f position = Stratified::halton23<Vector2f>(i);
			uint32_t x = (uint32_t)((position.x * 0.9f + 0.05f) * size);
			uint32_t y = (uint32_t)((position.y * 0.9f + 0.05f) * size);
			sampler.set2D(x, y, ImageColor(255));
		}
		
		image.save("test_halton23.tga");
	}
	
	if(1) {
		
		constexpr uint32_t size = 1024;
		
		constexpr uint32_t samples = size;
		
		using Vector2f = Vector2<float32_t>;
		
		Image image;
		image.create2D(FormatRGBu8, size, size);
		
		ImageSampler sampler(image);
		for(uint32_t i = 0; i < samples; i++) {
			Vector2f position = Stratified::halton34<Vector2f>(i);
			uint32_t x = (uint32_t)((position.x * 0.9f + 0.05f) * size);
			uint32_t y = (uint32_t)((position.y * 0.9f + 0.05f) * size);
			sampler.set2D(x, y, ImageColor(255));
		}
		
		image.save("test_halton34.tga");
	}
	
	if(1) {
		
		constexpr uint32_t size = 1024;
		
		constexpr uint32_t samples = size;
		
		using Vector2d = Vector2<float64_t>;
		
		Image image;
		image.create2D(FormatRGBu8, size, size);
		
		ImageSampler sampler(image);
		for(uint32_t i = 0; i < samples; i++) {
			Vector2d position = Stratified::hammersley<Vector2d>(i + 2313, samples);
			uint32_t x = (uint32_t)((position.x * 0.9f + 0.05f) * size);
			uint32_t y = (uint32_t)((position.y * 0.9f + 0.05f) * size);
			sampler.set2D(x, y, ImageColor(255));
		}
		
		image.save("test_hammersley.tga");
	}
	
	if(1) {
		
		constexpr uint32_t size = 1024;
		
		constexpr uint32_t samples = size;
		
		using Vector2f = Vector2<float32_t>;
		
		Image image;
		image.create2D(FormatRGBu8, size, size);
		
		ImageSampler sampler(image);
		for(uint32_t i = 0; i < samples; i++) {
			Vector2f position_0 = Stratified::vogel<Vector2f>(i, samples);
			Vector2f position_1 = Stratified::vogelFast<Vector2f>(i, samples);
			uint32_t x0 = (uint32_t)((position_0.x * 0.45f + 0.5f) * size);
			uint32_t y0 = (uint32_t)((position_0.y * 0.45f + 0.5f) * size);
			uint32_t x1 = (uint32_t)((position_1.x * 0.45f + 0.5f) * size);
			uint32_t y1 = (uint32_t)((position_1.y * 0.45f + 0.5f) * size);
			sampler.set2D(x1 - 1, y1, ImageColor(255, 0, 0, 255));
			sampler.set2D(x1 + 1, y1, ImageColor(255, 0, 0, 255));
			sampler.set2D(x1, y1 - 1, ImageColor(255, 0, 0, 255));
			sampler.set2D(x1, y1 + 1, ImageColor(255, 0, 0, 255));
			sampler.set2D(x0, y0, ImageColor(255));
		}
		
		image.save("test_vogel.tga");
	}
	
	if(1) {
		
		using Vector2u = Vector2<uint32_t>;
		using Vector2d = Vector2<float64_t>;
		
		constexpr uint32_t size = 4;
		constexpr uint32_t samples = 7;
		constexpr uint32_t bins = size * size;
		
		Array<Vector2u> order(1);
		float64_t distance = Maxf32;
		Array<Vector2d> positions[bins];
		for(uint32_t i = 0; i < 1024 * 1024; i++) {
			Vector2d position = Stratified::halton23<Vector2d>(i);
			uint32_t x = (uint32_t)(position.x * size);
			uint32_t y = (uint32_t)(position.y * size);
			if(x >= size) continue;
			if(y >= size) continue;
			uint32_t index = size * y + x;
			float64_t d = length(position - 0.3 / size);
			if(distance > d) {
				order[0] = Vector2u(index, positions[index].size());
				distance = d;
			}
			positions[index].append(position);
		}
		
		// histogram
		uint32_t histogram[bins] = {};
		histogram[order[0].x]++;
		
		while(true) {
			
			// find minimal histogram counter
			uint32_t counter = Maxu32;
			for(uint32_t i = 0; i < bins; i++) {
				counter = min(counter, histogram[i]);
			}
			if(counter == samples) break;
			
			// find the farthest position
			float64_t distance = 0.0;
			Vector2u index = Vector2u(Maxu32);
			for(uint32_t i = 0; i < bins; i++) {
				if(histogram[i] != counter) continue;
				for(uint32_t j = 0; j < positions[i].size(); j++) {
					float64_t d = Maxf32;
					for(uint32_t k = 0; k < order.size(); k++) {
						Vector2d offset = positions[i][j] - positions[order[k].x][order[k].y];
						d = min(d, length(offset + Vector2d( 0.0,  1.0)));
						d = min(d, length(offset + Vector2d( 0.0, -1.0)));
						d = min(d, length(offset + Vector2d( 1.0,  0.0)));
						d = min(d, length(offset + Vector2d(-1.0,  0.0)));
						d = min(d, length(offset + Vector2d( 1.0,  1.0)));
						d = min(d, length(offset + Vector2d( 1.0, -1.0)));
						d = min(d, length(offset + Vector2d( 1.0,  1.0)));
						d = min(d, length(offset + Vector2d(-1.0,  1.0)));
						d = min(d, length(offset));
						if(distance > d) break;
					}
					if(distance < d) {
						index = Vector2u(i, j);
						distance = d;
					}
				}
			}
			
			// update sequence
			histogram[index.x]++;
			order.append(index);
		}
		
		Image image;
		uint32_t width = 512;
		image.create2D(FormatRGBu8, width, width);
		ImageSampler sampler(image);
		for(uint32_t y = 1; y < size; y++) {
			for(uint32_t x = 0; x < width; x++) {
				sampler.set2D(y * width / size, x, ImageColor(127));
				sampler.set2D(x, y * width / size, ImageColor(127));
			}
		}
		
		Random<> random(1);
		for(uint32_t i = 0; i < order.size(); i++) {
			swap(order[i], order[random.geti32(order.size() - 1)]);
		}
		
		Log::printf("static const float32_t offsets[%u * 2] = {", samples * bins);
		for(uint32_t i = 0; i < order.size(); i++) {
			if(i % 8 == 0) Log::print("\n\t");
			const Vector2d &position = positions[order[i].x][order[i].y];
			Log::printf("%.5ff, %.5ff,", position.x, position.y);
			if(i % 8 != 0 && i % 8 != 7) Log::printf(" ");
			uint32_t x = (uint32_t)(position.x * width);
			uint32_t y = (uint32_t)(position.y * width);
			sampler.set2D(x, y, ImageColor(255));
		}
		Log::printf("\n};\n");
		
		image.save("test_samples.tga");
	}
	
	return 0;
}
