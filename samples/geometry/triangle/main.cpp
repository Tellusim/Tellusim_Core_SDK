// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <math/TellusimMath.h>
#include <geometry/TellusimTriangle.h>
#include <format/TellusimImage.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	constexpr uint32_t size = 512;
	
	Image closest_image;
	closest_image.create2D(FormatRGBAu8n, size, size);
	ImageSampler closest_sampler(closest_image);
	
	Image intersection_image;
	intersection_image.create2D(FormatRGBAu8n, size, size);
	ImageSampler intersection_sampler(intersection_image);
	
	Matrix4x4f projection = Matrix4x4f::perspective(60.0f, 1.0f, 0.1f, true);
	Matrix4x4f imodelview = inverse(Matrix4x4f::lookAt(Vector3f(0.0f, 0.0f, 2.0f), Vector3f(0.0f), Vector3f(0.0f, 1.0f, 0.0f)));
	Vector3f position = imodelview.getTranslate();
	
	Vector3f v0 = Vector3f(-1.0f,  1.0f, 0.0f);
	Vector3f v1 = Vector3f( 1.0f,  1.0f, 0.0f);
	Vector3f v2 = Vector3f( 0.0f, -1.0f, 0.0f);
	
	for(uint32_t Y = 0; Y < size; Y++) {
		for(uint32_t X = 0; X < size; X++) {
			
			float32_t x = ((float32_t)X / size * 2.0f - 1.0f + projection.m02) / projection.m00;
			float32_t y = ((float32_t)Y / size * 2.0f - 1.0f + projection.m12) / projection.m11;
			Vector3f direction = normalize(imodelview * Vector3f(x, y, -1.0f) - position);
			
			Vector3f c = Triangle::closest(v0, v1, v2, position - direction * ((2.0f - 1e-4f) / direction.z));
			if(c.z > 1e-3f) closest_sampler.set2D(X, Y, ImageColor((uint32_t)min(c.z * 255.0f, 255.0f), 0u, 0u, 255u));
			else closest_sampler.set2D(X, Y, ImageColor((uint32_t)(c.x * 255.0f), (uint32_t)(c.y * 255.0f), (uint32_t)((1.0f - c.x - c.y) * 255.0f), 255u));
			
			Vector3f i = Triangle::intersection(v0, v1, v2, position, direction);
			if(i.z < 1000.0f) intersection_sampler.set2D(X, Y, ImageColor((uint32_t)(i.x * 255.0f), (uint32_t)(i.y * 255.0f), (uint32_t)((1.0f - i.x - i.y) * 255.0f), 255u));
		}
	}
	
	closest_image.save("test_closest.png");
	intersection_image.save("test_intersection.png");
	
	return 0;
}
