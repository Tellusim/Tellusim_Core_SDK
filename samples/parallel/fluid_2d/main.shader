// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_ADVECTION_SHADER
	
	layout(local_size_x = 8, local_size_y = 8) in;
	
	layout(std140, binding = 0) uniform AdvectionParameters {
		vec2 mouse_texcoord;
		vec2 mouse_velocity;
		float mouse_radius;
		float ifps;
	};
	
	layout(binding = 0, set = 2) uniform sampler in_linear_sampler;
	layout(binding = 0, set = 1) uniform texture2D in_velocity_texture;
	layout(binding = 1, set = 1, rg32f) uniform writeonly image2D out_surface;
	
	/*
	 */
	void main() {
		
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		vec2 texture_size = vec2(textureSize(in_velocity_texture, 0).xy);
		vec2 velocity = texelFetch(in_velocity_texture, global_id, 0).xy;
		vec2 texcoord = vec2(global_id) + 0.5f - velocity * texture_size * ifps;
		
		vec2 t1 = floor(texcoord - 0.5f) + 0.5f;
		vec2 f1 = texcoord - t1;
		vec2 f2 = f1 * f1, f3 = f2 * f1;
		vec2 w0 = f2 - (f3 + f1) * 0.5f;
		vec2 w1 = f3 * 1.5f - f2 * 2.5f + 1.0f;
		vec2 w3 = (f3 - f2) * 0.5f;
		vec2 w2 = 1.0f - w0 - w1 - w3;
		
		#if CLAY_WG
			
			ivec2 it0 = ivec2(t1 - 1.0f);
			ivec2 it1 = ivec2(t1 + 0.0f);
			ivec2 it2 = ivec2(t1 + 1.0f);
			ivec2 it3 = ivec2(t1 + 2.0f);
			
			velocity  = texelFetch(in_velocity_texture, ivec2(it0.x, it0.y), 0).xy * (w0.x * w0.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it1.x, it0.y), 0).xy * (w1.x * w0.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it2.x, it0.y), 0).xy * (w2.x * w0.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it3.x, it0.y), 0).xy * (w3.x * w0.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it0.x, it1.y), 0).xy * (w0.x * w1.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it1.x, it1.y), 0).xy * (w1.x * w1.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it2.x, it1.y), 0).xy * (w2.x * w1.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it3.x, it1.y), 0).xy * (w3.x * w1.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it0.x, it2.y), 0).xy * (w0.x * w2.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it1.x, it2.y), 0).xy * (w1.x * w2.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it2.x, it2.y), 0).xy * (w2.x * w2.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it3.x, it2.y), 0).xy * (w3.x * w2.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it0.x, it3.y), 0).xy * (w0.x * w3.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it1.x, it3.y), 0).xy * (w1.x * w3.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it2.x, it3.y), 0).xy * (w2.x * w3.y);
			velocity += texelFetch(in_velocity_texture, ivec2(it3.x, it3.y), 0).xy * (w3.x * w3.y);
			
		#else
			
			w1 += w2;
			vec2 t0 = (t1 - 1.0f) / texture_size;
			vec2 t3 = (t1 + 2.0f) / texture_size;
			t1 = (t1 + w2 / w1) / texture_size;
			
			velocity  = textureLod(sampler2D(in_velocity_texture, in_linear_sampler), vec2(t0.x, t0.y), 0.0f).xy * (w0.x * w0.y);
			velocity += textureLod(sampler2D(in_velocity_texture, in_linear_sampler), vec2(t1.x, t0.y), 0.0f).xy * (w1.x * w0.y);
			velocity += textureLod(sampler2D(in_velocity_texture, in_linear_sampler), vec2(t3.x, t0.y), 0.0f).xy * (w3.x * w0.y);
			velocity += textureLod(sampler2D(in_velocity_texture, in_linear_sampler), vec2(t0.x, t1.y), 0.0f).xy * (w0.x * w1.y);
			velocity += textureLod(sampler2D(in_velocity_texture, in_linear_sampler), vec2(t1.x, t1.y), 0.0f).xy * (w1.x * w1.y);
			velocity += textureLod(sampler2D(in_velocity_texture, in_linear_sampler), vec2(t3.x, t1.y), 0.0f).xy * (w3.x * w1.y);
			velocity += textureLod(sampler2D(in_velocity_texture, in_linear_sampler), vec2(t0.x, t3.y), 0.0f).xy * (w0.x * w3.y);
			velocity += textureLod(sampler2D(in_velocity_texture, in_linear_sampler), vec2(t1.x, t3.y), 0.0f).xy * (w1.x * w3.y);
			velocity += textureLod(sampler2D(in_velocity_texture, in_linear_sampler), vec2(t3.x, t3.y), 0.0f).xy * (w3.x * w3.y);
			
		#endif
		
		vec2 direction = (texcoord / texture_size - mouse_texcoord) / mouse_radius;
		velocity += mouse_velocity * clamp(1.0f - dot(direction, direction), 0.0f, 1.0f);
		
		vec2 vignette = smoothstep(vec2(0.0f), vec2(texture_size.y / texture_size.x, 1.0f) * 0.02f, 1.0f - abs(vec2(global_id) / texture_size * 2.0f - 1.0f));
		velocity *= vignette.x * vignette.y;
		
		imageStore(out_surface, global_id, vec4(velocity, 0.0f, 0.0f));
	}
	
#elif COMPUTE_DIFFUSE_SHADER
	
	layout(local_size_x = 8, local_size_y = 8) in;
	
	layout(std140, binding = 0) uniform DiffuseParameters {
		float viscosity;
		float ifps;
	};
	
	layout(binding = 0, set = 1) uniform texture2D in_velocity_texture;
	layout(binding = 1, set = 1, rgba32f) uniform writeonly image2D out_surface;
	
	/*
	 */
	void main() {
		
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		vec2 texture_size = vec2(textureSize(in_velocity_texture, 0).xy);
		vec4 velocity = texelFetch(in_velocity_texture, global_id, 0);
		
		float dx = float(global_id.x);
		float dy = float(global_id.y);
		if(dy * 2.0f >= texture_size.y) dy -= texture_size.y;
		
		float radius = dx * dx + dy * dy;
		velocity *= exp(-radius * viscosity * ifps);
		
		if(radius > 0.0f) {
			float r = (dx * velocity.x + dy * velocity.y);
			float i = (dx * velocity.z + dy * velocity.w);
			velocity -= vec4(r * dx, r * dy, i * dx, i * dy) / radius;
		}
		
		imageStore(out_surface, global_id, velocity);
	}
	
#elif COMPUTE_UPDATE_SHADER
	
	layout(local_size_x = 8, local_size_y = 8) in;
	
	layout(std140, binding = 0) uniform UpdateParameters {
		float ifps;
	};
	
	layout(binding = 0, set = 2) uniform sampler in_linear_sampler;
	layout(binding = 0, set = 1) uniform texture2D in_velocity_texture;
	layout(binding = 1, set = 1) uniform texture2D in_color_texture;
	layout(binding = 2, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	/*
	 */
	void main() {
		
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		vec2 texture_size = vec2(textureSize(in_velocity_texture, 0).xy);
		vec2 velocity = texelFetch(in_velocity_texture, global_id, 0).xy;
		vec2 texcoord = vec2(global_id) + 0.5f - velocity * texture_size * ifps;
		
		vec2 t1 = floor(texcoord - 0.5f) + 0.5f;
		vec2 f1 = texcoord - t1;
		vec2 f2 = f1 * f1, f3 = f2 * f1;
		vec2 w0 = f2 - (f3 + f1) * 0.5f;
		vec2 w1 = f3 * 1.5f - f2 * 2.5f + 1.0f;
		vec2 w3 = (f3 - f2) * 0.5f;
		vec2 w2 = 1.0f - w0 - w1 - w3; w1 += w2;
		vec2 t0 = (t1 - 1.0f) / texture_size;
		vec2 t3 = (t1 + 2.0f) / texture_size;
		t1 = (t1 + w2 / w1) / texture_size;
		
		vec4 color = vec4(0.0f);
		color += textureLod(sampler2D(in_color_texture, in_linear_sampler), vec2(t0.x, t0.y), 0.0f) * (w0.x * w0.y);
		color += textureLod(sampler2D(in_color_texture, in_linear_sampler), vec2(t1.x, t0.y), 0.0f) * (w1.x * w0.y);
		color += textureLod(sampler2D(in_color_texture, in_linear_sampler), vec2(t3.x, t0.y), 0.0f) * (w3.x * w0.y);
		color += textureLod(sampler2D(in_color_texture, in_linear_sampler), vec2(t0.x, t1.y), 0.0f) * (w0.x * w1.y);
		color += textureLod(sampler2D(in_color_texture, in_linear_sampler), vec2(t1.x, t1.y), 0.0f) * (w1.x * w1.y);
		color += textureLod(sampler2D(in_color_texture, in_linear_sampler), vec2(t3.x, t1.y), 0.0f) * (w3.x * w1.y);
		color += textureLod(sampler2D(in_color_texture, in_linear_sampler), vec2(t0.x, t3.y), 0.0f) * (w0.x * w3.y);
		color += textureLod(sampler2D(in_color_texture, in_linear_sampler), vec2(t1.x, t3.y), 0.0f) * (w1.x * w3.y);
		color += textureLod(sampler2D(in_color_texture, in_linear_sampler), vec2(t3.x, t3.y), 0.0f) * (w3.x * w3.y);
		
		imageStore(out_surface, global_id, color);
	}

#elif VERTEX_SHADER
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = vec2(0.0f);
		if(gl_VertexIndex == 0) texcoord.x = 2.0f;
		if(gl_VertexIndex == 2) texcoord.y = 2.0f;
		
		gl_Position = vec4(texcoord * 2.0f - 1.0f, 0.0f, 1.0f);
		
		#if CLAY_VK
			texcoord.y = 1.0f - texcoord.y;
		#endif
		
		s_texcoord = texcoord;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform sampler in_sampler;
	layout(binding = 0, set = 0) uniform texture2D in_texture;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		out_color = texture(sampler2D(in_texture, in_sampler), s_texcoord);
	}
	
#endif
