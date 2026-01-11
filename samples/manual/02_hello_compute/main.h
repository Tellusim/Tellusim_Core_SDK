// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __MAIN_H__
#define __MAIN_H__

/*
 */
struct ComputeParameters {
	Vector4f camera;
	Vector4f global_gravity;
	Vector4f wind_velocity;
	uint32_t num_emitters;
	uint32_t max_emitters;
	uint32_t max_particles;
	float32_t wind_force;
	float32_t velocity_damping;
	float32_t growth_damping;
	float32_t twist_damping;
	float32_t ifps;
};

/*
 */
struct ComputeState {
	uint32_t num_particles;
	uint32_t new_particles;
	uint32_t padding[2];
};

/*
 */
struct EmitterParameters {
	Vector4f position;
	Vector4f direction;
	Color color_mean;
	Color color_spread;
	float32_t position_mean;
	float32_t position_spread;
	float32_t velocity_mean;
	float32_t velocity_spread;
	float32_t velocity_damping;
	float32_t radius_mean;
	float32_t radius_spread;
	float32_t growth_mean;
	float32_t growth_spread;
	float32_t growth_damping;
	float32_t angle_mean;
	float32_t angle_spread;
	float32_t twist_mean;
	float32_t twist_spread;
	float32_t twist_damping;
	float32_t life_mean;
	float32_t life_spread;
	float32_t spawn_mean;
	float32_t spawn_spread;
	uint32_t padding;
};

/*
 */
struct EmitterState {
	Vector4f position;
	Vector4f velocity;
	Vector2i seed;
	float32_t spawn;
	uint32_t padding;
};

/*
 */
struct ParticleState {
	Vector4f position;
	Vector4f color;
	Vector4f velocity;
	float32_t velocity_damping;
	float32_t radius;
	float32_t growth;
	float32_t growth_damping;
	float32_t angle;
	float32_t twist;
	float32_t twist_damping;
	float32_t life;
	float32_t time;
	uint32_t padding[3];
};

/*
 */
struct Vertex {
	Vector4f position;
	Vector4f velocity;
	Vector4f color;
};

#endif /* __MAIN_H__ */
