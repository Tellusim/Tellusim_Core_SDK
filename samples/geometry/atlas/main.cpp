// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimArray.h>
#include <core/TellusimString.h>
#include <math/TellusimRandom.h>
#include <math/TellusimMath.h>
#include <format/TellusimImage.h>
#include <geometry/TellusimAtlas.h>

/*
 */
using namespace Tellusim;

/*
 */
void print_node(const Atlas2f::Node *node, uint32_t offset = 0) {
	const Vector2f &min = node->bound.min;
	const Vector2f &max = node->bound.max;
	TS_LOGF(Message, "%s%p: %p %p %u: %f %f : %f %f\n", String(offset, ' ').get(), node, node->left, node->right, node->axis, min.x, min.y, max.x, max.y);
	if(node->left) print_node(node->left, offset + 1);
	if(node->right) print_node(node->right, offset + 1);
}

void fill_rect(Image &image, const BoundRectf &rect, const ImageColor &color) {
	ImageSampler sampler(image);
	for(float32_t y = rect.min.y; y < rect.max.y; y += 1.0f) {
		for(float32_t x = rect.min.x; x < rect.max.x; x += 1.0f) {
			sampler.set2D((uint32_t)x, (uint32_t)y, color);
		}
	}
}

void create_image(Image &image, const Atlas2f::Node *node, Random<Vector3i, Vector3f> &random) {
	if(node->axis == 2) {
		Vector3i color = random.geti32(Vector3i(32), Vector3i(255));
		fill_rect(image, node->bound, ImageColor(color.x, color.y, color.z, 255));
	}
	if(node->left) create_image(image, node->left, random);
	if(node->right) create_image(image, node->right, random);
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		
		uint32_t size = 1024;
		
		Image image_0;
		Image image_1;
		image_0.create2D(FormatRGBu8n, 1024);
		image_1.create2D(FormatRGBu8n, 1024);
		
		Array<Atlas2f::Node*> nodes;
		Atlas2f atlas(Vector2f((float32_t)size));
		Random<Vector3i, Vector3f> random(Vector3i(1, 3, 7));
		for(uint32_t i = 0; i < 96; i++) {
			Vector3i size = random.geti32(Vector3i(32), Vector3i(128));
			Atlas2f::Node *node = atlas.insert(Vector2f(size.xy));
			if(node) nodes.append(node);
		}
		
		create_image(image_0, atlas.getRoot(), random);
		
		for(uint32_t i = 0; i < nodes.size() - 2; i++) {
			if(!atlas.remove(nodes[i])) return 1;
		}
		
		print_node(atlas.getRoot());
		
		create_image(image_1, atlas.getRoot(), random);
		
		image_0.save("test_0.png");
		image_1.save("test_1.png");
	}
	
	return 0;
}
