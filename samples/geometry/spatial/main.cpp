// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimArray.h>
#include <core/TellusimString.h>
#include <math/TellusimRandom.h>
#include <geometry/TellusimSpatial.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		
		constexpr uint32_t num_nodes = 1;
		
		using Vector2i = Tellusim::Vector2<int32_t>;
		using Vector2f = Tellusim::Vector2<float32_t>;
		
		Random<Vector2i, Vector2f> random(Vector2i(1, 2));
		
		Array<Spatial::Node2f> nodes(max(num_nodes * 2, 4u));
		for(uint32_t i = 0; i < num_nodes; i++) {
			Vector2f position = random.getf32(Vector2f(0.0f), Vector2f(128.0f));
			Vector2f size = random.getf32(Vector2f(1.0f), Vector2f(2.0f));
			nodes[num_nodes + i].bound.min = position - size;
			nodes[num_nodes + i].bound.max = position + size;
		}
		
		// create spatial tree
		Spatial::create<float32_t>(nodes.get(), num_nodes);
		
		Log::printf("\n");
		for(uint32_t i = 0; i < nodes.size(); i++) {
			const Spatial::Node2f &node = nodes[i];
			Log::printf("%5u: l%u r%u p%u s%u\n", i, node.left, node.right, node.parent, node.spatial);
		}
		
		Log::printf("\n");
		Array<uint32_t> stack(1, 0u);
		while(stack) {
			uint32_t index = stack.back(); stack.removeBack();
			const Spatial::Node2f &node = nodes[index];
			Log::printf("%5u:%s l%u r%u p%u s%u\n", index, String(stack.size(), ' ').get(), node.left, node.right, node.parent, node.spatial);
			if(node.right < node.spatial) stack.append(node.right);
			if(node.left < node.spatial) stack.append(node.left);
		}
		
		// optimize spatial tree
		Spatial::optimize<float32_t>(nodes.get(), num_nodes);
		
		Log::printf("\n");
		for(uint32_t i = 0; i < nodes.size(); i++) {
			const Spatial::Node2f &node = nodes[i];
			Log::printf("%5u: l%u r%u p%u s%u\n", i, node.left, node.right, node.parent, node.spatial);
		}
		
		Log::printf("\n");
		stack.append(0u);
		while(stack) {
			uint32_t index = stack.back(); stack.removeBack();
			const Spatial::Node2f &node = nodes[index];
			Log::printf("%5u:%s l%u r%u p%u s%u\n", index, String(stack.size(), ' ').get(), node.left, node.right, node.parent, node.spatial);
			if(node.right < node.spatial) stack.append(node.right);
			if(node.left < node.spatial) stack.append(node.left);
		}
		
		Log::printf("\n");
		uint32_t indices[num_nodes];
		uint32_t ret_0 = Spatial::intersection(BoundRectf(Vector2f(0.0f), Vector2f(128.0f)), nodes.get(), indices, num_nodes);
		uint32_t ret_1 = Spatial::intersection(BoundRectf(Vector2f(32.0f), Vector2f(64.0f)), nodes.get(), indices, num_nodes);
		uint32_t ret_2 = Spatial::intersection(BoundCirclef(Vector2f(64.0f), 96.0f), nodes.get(), indices, num_nodes);
		uint32_t ret_3 = Spatial::intersection(BoundCirclef(Vector2f(64.0f), 64.0f), nodes.get(), indices, num_nodes);
		TS_LOGF(Message, "bound rect:   %u %u\n", ret_0, ret_1);
		TS_LOGF(Message, "bound circle: %u %u\n", ret_2, ret_3);
	}
	
	if(1) {
		
		constexpr uint32_t num_nodes = 1;
		
		using Vector3i = Tellusim::Vector3<int32_t>;
		using Vector3f = Tellusim::Vector3<float32_t>;
		
		Random<Vector3i, Vector3f> random(Vector3i(1, 2, 3));
		
		Array<Spatial::Node3f> nodes(max(num_nodes * 2, 4u));
		for(uint32_t i = 0; i < num_nodes; i++) {
			Vector3f position = random.getf32(Vector3f(0.0f), Vector3f(128.0f));
			Vector3f size = random.getf32(Vector3f(1.0f), Vector3f(2.0f));
			nodes[num_nodes + i].bound.min = position - size;
			nodes[num_nodes + i].bound.max = position + size;
		}
		
		// create spatial tree
		Spatial::create<float32_t>(nodes.get(), num_nodes);
		
		Log::printf("\n");
		for(uint32_t i = 0; i < nodes.size(); i++) {
			const Spatial::Node3f &node = nodes[i];
			Log::printf("%5u: l%u r%u p%u s%u\n", i, node.left, node.right, node.parent, node.spatial);
		}
		
		Log::printf("\n");
		Array<uint32_t> stack(1, 0u);
		while(stack) {
			uint32_t index = stack.back(); stack.removeBack();
			const Spatial::Node3f &node = nodes[index];
			Log::printf("%5u:%s l%u r%u p%u s%u\n", index, String(stack.size(), ' ').get(), node.left, node.right, node.parent, node.spatial);
			if(node.right < node.spatial) stack.append(node.right);
			if(node.left < node.spatial) stack.append(node.left);
		}
		
		// optimize spatial tree
		Spatial::optimize<float32_t>(nodes.get(), num_nodes);
		
		Log::printf("\n");
		for(uint32_t i = 0; i < nodes.size(); i++) {
			const Spatial::Node3f &node = nodes[i];
			Log::printf("%5u: l%u r%u p%u s%u\n", i, node.left, node.right, node.parent, node.spatial);
		}
		
		Log::printf("\n");
		stack.append(0u);
		while(stack) {
			uint32_t index = stack.back(); stack.removeBack();
			const Spatial::Node3f &node = nodes[index];
			Log::printf("%5u:%s l%u r%u p%u s%u\n", index, String(stack.size(), ' ').get(), node.left, node.right, node.parent, node.spatial);
			if(node.right < node.spatial) stack.append(node.right);
			if(node.left < node.spatial) stack.append(node.left);
		}
		
		Log::printf("\n");
		uint32_t indices[num_nodes];
		uint32_t ret_0 = Spatial::intersection(BoundBoxf(Vector3f(0.0f), Vector3f(128.0f)), nodes.get(), indices, num_nodes);
		uint32_t ret_1 = Spatial::intersection(BoundBoxf(Vector3f(32.0f), Vector3f(96.0f)), nodes.get(), indices, num_nodes);
		uint32_t ret_2 = Spatial::intersection(BoundSpheref(Vector3f(64.0f), 96.0f), nodes.get(), indices, num_nodes);
		uint32_t ret_3 = Spatial::intersection(BoundSpheref(Vector3f(64.0f), 64.0f), nodes.get(), indices, num_nodes);
		TS_LOGF(Message, "bound box:    %u %u\n", ret_0, ret_1);
		TS_LOGF(Message, "bound sphere: %u %u\n", ret_2, ret_3);
	}
	
	if(1) {
		
		constexpr uint32_t size = 512;
		constexpr uint32_t num_nodes = size * size;
		
		using Vector3i = Tellusim::Vector3<int32_t>;
		using Vector3f = Tellusim::Vector3<float32_t>;
		
		Random<Vector3i, Vector3f> random(Vector3i(1, 2, 3));
		
		Array<Spatial::Node3f> nodes(max(num_nodes * 2, 4u));
		for(uint32_t y = 0, i = 0; y < size; y++) {
			for(uint32_t x = 0; x < size; x++, i++) {
				Vector3f position = random.getf32(Vector3f(0.0f), Vector3f((float32_t)size));
				nodes[num_nodes + i].bound.min = position - 1e-3f;
				nodes[num_nodes + i].bound.max = position + 1e-3f;
			}
		}
		Spatial::create<float32_t>(nodes.get(), num_nodes);
		
		for(uint32_t i = 0; i < 32; i++) {
			Vector3f point = random.getf32(Vector3f(0.0f), Vector3f((float32_t)size));
			uint32_t index_0 = Maxu32;
			float32_t distance_0 = Maxf32;
			for(uint32_t j = 0; j < num_nodes; j++) {
				float32_t d = length(nodes[num_nodes + j].bound.getCenter() - point);
				if(distance_0 > d) { distance_0 = d; index_0 = j; }
			}
			uint32_t index_1 = Spatial::closestIntersection<float32_t>(point, nodes.get());
			float32_t distance_1 = length(nodes[num_nodes + index_1].bound.getCenter() - point);
			TS_LOGF(Message, "%3u : %8.2f %8.2f : %8u %8u : %f %f\n", i, point.x, point.y, index_0, index_1, distance_0, distance_1);
		}
	}
	
	if(1) {
		
		constexpr uint32_t num_nodes = 2;
		
		using Vector2f = Tellusim::Vector2<float32_t>;
		
		Array<Spatial::Node2f> nodes(num_nodes * 2);
		nodes[num_nodes + 0].bound.min = Vector2f(-1.0f);
		nodes[num_nodes + 0].bound.max = Vector2f(1.0f);
		nodes[num_nodes + 1].bound.min = Vector2f(-10.0f);
		nodes[num_nodes + 1].bound.max = Vector2f(10.0f);
		nodes[num_nodes + 0].left = 10;
		nodes[num_nodes + 0].right = 11;
		nodes[num_nodes + 0].parent = 12;
		nodes[num_nodes + 0].spatial = 13;
		nodes[num_nodes + 1].left = 14;
		nodes[num_nodes + 1].right = 15;
		nodes[num_nodes + 1].parent = 16;
		nodes[num_nodes + 1].spatial = 17;
		
		// create spatial tree
		Spatial::create<float32_t>(nodes.get(), num_nodes);
		
		Log::printf("\n");
		TS_LOGF(Message, "%u %u %u %u\n", nodes[num_nodes + 0].left, nodes[num_nodes + 0].right, nodes[num_nodes + 0].parent, nodes[num_nodes + 0].spatial);
		TS_LOGF(Message, "%u %u %u %u\n", nodes[num_nodes + 1].left, nodes[num_nodes + 1].right, nodes[num_nodes + 1].parent, nodes[num_nodes + 1].spatial);
		
		Log::printf("\n");
		uint32_t indices[num_nodes];
		uint32_t ret_0 = Spatial::intersection(BoundCirclef(Vector2f(0.0f), 0.1f), nodes.get(), indices, num_nodes);
		uint32_t ret_1 = Spatial::intersection(BoundCirclef(Vector2f(4.0f), 0.1f), nodes.get(), indices, num_nodes);
		uint32_t index_0 = Spatial::closestIntersection<float32_t>(Vector2f(0.0f), nodes.get());
		uint32_t index_1 = Spatial::closestIntersection<float32_t>(Vector2f(4.0f), nodes.get());
		TS_LOGF(Message, "circle:  %u %u\n", ret_0, ret_1);
		TS_LOGF(Message, "closest: %u %u\n", index_0, index_1);
	}
	
	return 0;
}
