// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#define Color		vec4
#define Vector4f	vec4
#define Vector2i	ivec2
#define float32_t	float
#define uint32_t	uint

#include "main.h"

/*
 */
#define UDIV(A, B)	(((A) + (B) - 1u) / (B))

/*
 */
#if CLAY_WGSL
	#define NUM_PARTICLES	state[0]
	#define NEW_PARTICLES	state[1]
#else
	#define NUM_PARTICLES	state.num_particles
	#define NEW_PARTICLES	state.new_particles
#endif

/*
 */
#if INIT_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(binding = 0) uniform ComputeParametersBuffer { ComputeParameters compute; };
	
	layout(std430, binding = 1) writeonly buffer EmitterStateBuffer { EmitterState emitters_buffer[]; };
	layout(std430, binding = 2) writeonly buffer ParticleStateBuffer { ParticleState particles_buffer[]; };
	layout(std430, binding = 3) writeonly buffer IndicesBuffer { uint allocator_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		
		// initialize emitters
		[[branch]] if(global_id < compute.max_emitters * GROUP_SIZE) {
			emitters_buffer[global_id].position = vec4(0.0f);
			emitters_buffer[global_id].velocity = vec4(0.0f);
			emitters_buffer[global_id].seed = ivec2(global_id);
			emitters_buffer[global_id].spawn = 0.0f;
		}
		
		// initialize particles
		[[branch]] if(global_id < compute.max_particles) {
			particles_buffer[global_id].position = vec4(1e16f);
			particles_buffer[global_id].velocity = vec4(0.0f);
			particles_buffer[global_id].radius = 0.0f;
			particles_buffer[global_id].angle = 0.0f;
			particles_buffer[global_id].life = 0.0f;
		}
		
		// initialize particle indices
		[[branch]] if(global_id < compute.max_particles) {
			allocator_buffer[global_id] = compute.max_particles - global_id - 1u;
		}
	}
	
#elif EMITTER_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(binding = 0) uniform ComputeParametersBuffer { ComputeParameters compute; };
	layout(std430, binding = 1) readonly buffer EmitterParametersBuffer { EmitterParameters emitters[]; };
	
	#if CLAY_WGSL
		layout(std430, binding = 2) buffer StateBuffer { uint state[]; };
	#else
		layout(std430, binding = 2) buffer StateBuffer { ComputeState state; };
	#endif
	layout(std430, binding = 3) buffer EmitterStateBuffer { EmitterState emitters_buffer[]; };
	
	layout(std430, binding = 4) buffer ParticleStateBuffer { ParticleState particles_buffer[]; };
	layout(std430, binding = 5) buffer IndicesBuffer { uint allocator_buffer[]; };
	
	/*
	 */
	shared EmitterParameters emitter;
	shared vec3 emitter_old_position;
	shared vec3 emitter_old_velocity;
	shared vec3 emitter_velocity;
	shared uint num_particles;
	shared uint new_index;
	
	/*
	 */
	float get_random(uint index) {
		emitters_buffer[index].seed = ((emitters_buffer[index].seed * ivec2(16807, 48271) + ivec2(11, 23)) >> 2) & 0x0fffffff;
		return intBitsToFloat(((emitters_buffer[index].seed.x - emitters_buffer[index].seed.y) & 0x7fffff) + 0x3f000000) * 2.0f - 1.0f;
	}
	
	vec3 get_random_sphere(uint index, float radius, float offset) {
		float theta = get_random(index) * 6.28f;
		float c = get_random(index) * 2.0f - 1.0f;
		float s = sqrt(max(1.0f - c * c, 0.0f));
		float r = pow(get_random(index), 1.0f / 3.0f) * radius + offset;
		return vec3(sin(theta) * s, cos(theta) * s, c) * r;
	}
	
	/*
	 */
	void main() {
		
		uint group_id = gl_WorkGroupID.x;
		uint global_id = gl_GlobalInvocationID.x;
		uint local_id = gl_LocalInvocationIndex;
		
		// spawn particles
		[[branch]] if(local_id == 0u) {
			
			// emitter parameters
			emitter = emitters[group_id];
			
			// number of new particles
			num_particles = uint(floor(emitters_buffer[global_id].spawn));
			emitters_buffer[global_id].spawn += (emitter.spawn_mean + emitter.spawn_spread * get_random(global_id)) * compute.ifps - float(num_particles);
			
			// allocate particles
			[[branch]] if(num_particles != 0u) {
				new_index = atomicAdd(NEW_PARTICLES, num_particles) + num_particles;
				[[branch]] if(new_index > compute.max_particles) {
					atomicSub(NEW_PARTICLES, num_particles);
					num_particles = 0u;
				}
			}
			
			// emitter position and velocity
			emitter_old_position = emitters_buffer[global_id].position.xyz;
			emitter_old_velocity = emitters_buffer[global_id].velocity.xyz;
			emitter_velocity = (emitter.position.xyz - emitter_old_position) / compute.ifps;
			emitters_buffer[global_id].position.xyz = emitter.position.xyz;
			emitters_buffer[global_id].velocity.xyz = emitter_velocity;
		}
		memoryBarrierShared(); barrier();
		
		// create particles
		uint num_iterations = UDIV(num_particles, GROUP_SIZE);
		[[loop]] for(uint i = 0u; i < num_iterations; i++) {
			
			// iteration index
			uint j = GROUP_SIZE * i + local_id;
			
			// create particle
			[[branch]] if(j < num_particles) {
				
				// new particle index
				uint index = allocator_buffer[compute.max_particles - new_index + j];
				
				// particle position
				float k = float(j) / float(num_particles);
				vec3 position = mix(emitter_old_position, emitter.position.xyz, k);
				particles_buffer[index].position.xyz = position + get_random_sphere(global_id, emitter.position_mean, emitter.position_spread * get_random(global_id));
				
				// particle velocity
				vec3 velocity = mix(emitter_old_velocity, emitter_velocity, k);
				particles_buffer[index].velocity.xyz = velocity + emitter.direction.xyz * emitter.velocity_mean + get_random_sphere(global_id, emitter.velocity_spread, 0.0f);
				particles_buffer[index].velocity_damping = emitter.velocity_damping;
				
				// particle color
				vec4 color = vec4(get_random(global_id), get_random(global_id), get_random(global_id), 1.0f);
				particles_buffer[index].color = clamp(emitter.color_mean + emitter.color_spread * color, 0.0f, 1.0f);
				
				// particle radius
				particles_buffer[index].radius = emitter.radius_mean + emitter.radius_spread * get_random(global_id);
				particles_buffer[index].growth = emitter.growth_mean + emitter.growth_spread * get_random(global_id);
				particles_buffer[index].growth_damping = emitter.growth_damping;
				
				// particle angle
				particles_buffer[index].angle = emitter.angle_mean + emitter.angle_spread * get_random(global_id);
				particles_buffer[index].twist = emitter.twist_mean + emitter.twist_spread * get_random(global_id);
				particles_buffer[index].twist_damping = emitter.twist_damping;
				
				// particle life time
				particles_buffer[index].life = emitter.life_mean + emitter.life_spread * get_random(global_id);
				particles_buffer[index].time = 0.0f;
				
				// update the number of particles
				atomicMax(NUM_PARTICLES, index + 1u);
			}
		}
	}

#elif DISPATCH_SHADER
	
	// Compute::DispatchIndirect
	struct DispatchIndirect {
		uint group_width;
		uint group_height;
		uint group_depth;
	};
	
	// Command::DrawElementsIndirect
	struct DrawElementsIndirect {
		uint num_indices;
		uint num_instances;
		uint base_index;
		int base_vertex;
		uint base_instance;
	};
	
	// RadixSort::DispatchParameters
	struct RadixSortParameters {
		uint keys_offset;
		uint data_offset;
		uint size;
	};
	
	layout(local_size_x = 1) in;
	
	layout(binding = 0) uniform ComputeParametersBuffer { ComputeParameters compute; };
	
	layout(std430, binding = 1) readonly buffer StateBuffer { ComputeState state; };
	
	layout(std430, binding = 2) writeonly buffer DispatchBuffer { DispatchIndirect dispatch_buffer; };
	layout(std430, binding = 3) writeonly buffer DrawBuffer { DrawElementsIndirect draw_buffer; };
	layout(std430, binding = 4) writeonly buffer SortBuffer { RadixSortParameters sort_buffer; };
	
	/*
	 */
	void main() {
		
		// dispatch indirect
		dispatch_buffer.group_width = UDIV(state.num_particles, GROUP_SIZE);
		dispatch_buffer.group_height = 1u;
		dispatch_buffer.group_depth = 1u;
		
		// draw elements indirect
		draw_buffer.num_indices = 6u;
		draw_buffer.num_instances = state.num_particles;
		draw_buffer.base_index = 0u;
		draw_buffer.base_vertex = 0;
		draw_buffer.base_instance = 0u;
		
		// radix sort parameters
		sort_buffer.keys_offset = 0u;
		sort_buffer.data_offset = compute.max_particles;
		sort_buffer.size = state.num_particles;
	}

#elif UPDATE_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(binding = 0) uniform ComputeParametersBuffer { ComputeParameters compute; };
	
	#if CLAY_WGSL
		layout(std430, binding = 1) buffer StateBuffer { uint state[]; };
	#else
		layout(std430, binding = 1) buffer StateBuffer { ComputeState state; };
	#endif
	
	layout(std430, binding = 2) buffer ParticleStateBuffer { ParticleState particles_buffer[]; };
	layout(std430, binding = 3) buffer IndicesBuffer { uint allocator_buffer[]; };
	
	layout(std430, binding = 4) writeonly buffer DistancesBuffer { uint distances_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		
		#if CLAY_WGSL
			[[branch]] if(global_id < atomicAdd(NUM_PARTICLES, 0u)) {
		#else
			[[branch]] if(global_id < NUM_PARTICLES) {
		#endif
			
			[[branch]] if(particles_buffer[global_id].life > 0.0f) {
				
				// particle velocity
				particles_buffer[global_id].velocity.xyz += compute.global_gravity.xyz * compute.ifps;
				particles_buffer[global_id].velocity.xyz += (compute.wind_velocity.xyz - particles_buffer[global_id].velocity.xyz) * compute.wind_force * compute.ifps;
				
				// particle position
				particles_buffer[global_id].position.xyz += particles_buffer[global_id].velocity.xyz * compute.ifps;
				particles_buffer[global_id].velocity *= exp(-(particles_buffer[global_id].velocity_damping + compute.velocity_damping) * compute.ifps);
				
				// particle radius
				particles_buffer[global_id].radius += particles_buffer[global_id].growth * compute.ifps;
				particles_buffer[global_id].growth *= exp(-(particles_buffer[global_id].growth_damping + compute.growth_damping) * compute.ifps);
				
				// particle angle
				particles_buffer[global_id].angle += particles_buffer[global_id].twist * compute.ifps;
				particles_buffer[global_id].twist *= exp(-(particles_buffer[global_id].twist_damping + compute.twist_damping) * compute.ifps);
				
				// particle time
				particles_buffer[global_id].time += compute.ifps;
				
				// remove particle
				[[branch]] if(particles_buffer[global_id].time > particles_buffer[global_id].life || particles_buffer[global_id].radius < 0.0f) {
					
					// clear particle
					particles_buffer[global_id].position = vec4(1e16f);
					particles_buffer[global_id].velocity = vec4(0.0f);
					particles_buffer[global_id].radius = 0.0f;
					particles_buffer[global_id].life = 0.0f;
					
					// remove particle index
					uint new_index = atomicDecrement(NEW_PARTICLES);
					allocator_buffer[compute.max_particles - new_index] = global_id;
				}
			}
			
			// particle distance
			float distance = length(particles_buffer[global_id].position.xyz - compute.camera.xyz);
			distances_buffer[global_id] = ~0u - (floatBitsToUint(distance) ^ 0x80000000u);
		}
	}
	
#elif GEOMETRY_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(binding = 0) uniform ComputeParametersBuffer { ComputeParameters compute; };
	
	layout(std430, binding = 1) readonly buffer StateBuffer { ComputeState state; };
	
	layout(std430, binding = 2) readonly buffer ParticleStateBuffer { ParticleState particles_buffer[]; };
	layout(std430, binding = 3) readonly buffer DistancesBuffer { uint distances_buffer[]; };
	
	layout(std430, binding = 4) writeonly buffer VertexBuffer { Vertex vertex_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		
		[[branch]] if(global_id < state.num_particles) {
			
			// sorted particle order
			uint index = distances_buffer[compute.max_particles + global_id];
			
			// position and radius
			vertex_buffer[global_id].position = vec4(particles_buffer[index].position.xyz, particles_buffer[index].radius);
			
			// velocity and angle
			vertex_buffer[global_id].velocity = vec4(particles_buffer[index].velocity.xyz, particles_buffer[index].angle);
			
			// color
			float fade = clamp(1.0f - 1.0f * particles_buffer[index].time / particles_buffer[index].life, 0.0f, 1.0f);
			vertex_buffer[global_id].color = particles_buffer[index].color * fade;
		}
	}
	
#elif VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec4 in_velocity;
	layout(location = 2) in vec4 in_color;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
	};
	
	layout(location = 0) out vec2 s_texcoord;
	layout(location = 1) out vec4 s_color;
	
	/*
	 */
	void main() {
		
		// particle position
		vec4 position = vec4(in_position.xyz, 1.0f);
		gl_Position = projection * (modelview * position);
		
		// texture coordinates
		uint index = gl_VertexIndex;
		vec2 texcoord = vec2(-1.0f, -1.0f);
		if(index >= 1u && index <= 2u) texcoord.x = 1.0f;
		if(index >= 2u) texcoord.y = 1.0f;
		
		// rotation angle
		float s = sin(in_velocity.w);
		float c = cos(in_velocity.w);
		
		// particle size
		vec2 size = vec2(projection[0].x, projection[1].y) * in_position.w;
		gl_Position.xy += vec2(s * texcoord.x + c * texcoord.y, c * texcoord.x - s * texcoord.y) * size;
		
		// particle parameters
		s_texcoord = texcoord * 0.5f + 0.5f;
		s_color = in_color;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(location = 0) in vec2 s_texcoord;
	layout(location = 1) in vec4 s_color;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		out_color = s_color * texture(sampler2D(in_texture, in_sampler), s_texcoord).x;
	}
	
#endif
