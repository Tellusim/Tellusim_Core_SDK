// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 icamera;
		vec4 ilight;
		vec4 camera;
		vec4 light;
	};
	
	layout(location = 0) out vec3 s_position;
	layout(location = 1) out vec3 s_camera;
	layout(location = 2) out vec3 s_light;
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		gl_Position = projection * (modelview * position);
		
		s_position = in_position.xyz;
		s_camera = icamera.xyz;
		s_light = ilight.xyz;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	layout(binding = 0, set = 1) uniform textureCube in_texture;
	
	layout(location = 0) in vec3 s_position;
	layout(location = 1) in vec3 s_camera;
	layout(location = 2) in vec3 s_light;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	float get_noise(vec2 p) {
		return fract(77.621f * fract(dot(p, vec2(370.19f, 444.97f))));
	}
	
	/*
	 */
	void main() {
		
		float outer_radius = 0.5f;
		float inner_radius = 0.4f;
		float trace_step = 0.01f;
		
		// quadratic equation
		vec3 direction = s_position - s_camera;
		float a = dot(direction, direction);
		float b = dot(direction, s_camera);
		float c = dot(s_camera, s_camera);
		
		// outer sphere intersection
		float d0 = b * b - a * (c - outer_radius * outer_radius);
		float k0 = -(b + sqrt(max(d0, 0.0f))) / a;
		vec3 position = s_camera + direction * k0;
		
		// inner sphere intersection
		float d1 = b * b - a * (c - inner_radius * inner_radius);
		float k1 = -(b + sqrt(max(d1, 0.0f))) / a;
		if(d1 < 0.0f) k1 = -(b - sqrt(max(d0, 0.0f))) / a;
		vec3 back_position = s_camera + direction * k1;
		
		// lod level
		float lod = 0.0f;
		vec3 dx = dFdx(position);
		vec3 dy = dFdy(position);
		vec3 abs_position = abs(position);
		float max_position = max(abs_position.x, max(abs_position.y, abs_position.z));
		if(max_position == abs_position.x) lod = max(dot(dx.yz, dx.yz), dot(dy.yz, dy.yz));
		else if(max_position == abs_position.y) lod = max(dot(dx.xz, dx.xz), dot(dy.xz, dy.xz));
		else if(max_position == abs_position.z) lod = max(dot(dx.xy, dx.xy), dot(dy.xy, dy.xy));
		lod = log2(lod * 128.0f * 128.0f * 4.0f / (max_position * max_position)) * 0.5f;
		
		// initial height
		float radius = length(position);
		float old_height = textureLod(samplerCube(in_texture, in_sampler), position, lod).x;
		old_height = inner_radius + (outer_radius - inner_radius) * old_height - radius;
		
		// intersection parameters
		bool intersection = false;
		float istep = 1.0f / trace_step;
		float steps = length(back_position - position) * istep;
		vec3 step = (back_position - position) / steps;
		position += step;
		
		// height intersection
		[[loop]] for(float i = 0.0f; i < steps; i += 0.5f) {
			radius = length(position);
			if(radius > outer_radius + trace_step) i = steps;
			float height = textureLod(samplerCube(in_texture, in_sampler), position, lod).x;
			height = inner_radius + (outer_radius - inner_radius) * height - radius;
			[[branch]] if(height * old_height <= 0.0f) {
				if(dot(step, step) < 1e-6f) i = steps;
				intersection = true;
				step = -step * 0.5f;
				position += step;
			} else {
				position += step * max(abs(height * istep) * 0.5f, 1.0f);
			}
			old_height = height;
		}
		if(!intersection) discard;
		
		// calculate normal
		abs_position = abs(position);
		max_position = max(abs_position.x, max(abs_position.y, abs_position.z)) / 64.0f;
		vec3 position_xp = normalize(position + vec3(max_position, 0.0f, 0.0f));
		vec3 position_xn = normalize(position - vec3(max_position, 0.0f, 0.0f));
		vec3 position_yp = normalize(position + vec3(0.0f, max_position, 0.0f));
		vec3 position_yn = normalize(position - vec3(0.0f, max_position, 0.0f));
		vec3 position_zp = normalize(position + vec3(0.0f, 0.0f, max_position));
		vec3 position_zn = normalize(position - vec3(0.0f, 0.0f, max_position));
		position_xp *= inner_radius + (outer_radius - inner_radius) * textureLod(samplerCube(in_texture, in_sampler), position_xp, lod).x;
		position_xn *= inner_radius + (outer_radius - inner_radius) * textureLod(samplerCube(in_texture, in_sampler), position_xn, lod).x;
		position_yp *= inner_radius + (outer_radius - inner_radius) * textureLod(samplerCube(in_texture, in_sampler), position_yp, lod).x;
		position_yn *= inner_radius + (outer_radius - inner_radius) * textureLod(samplerCube(in_texture, in_sampler), position_yn, lod).x;
		position_zp *= inner_radius + (outer_radius - inner_radius) * textureLod(samplerCube(in_texture, in_sampler), position_zp, lod).x;
		position_zn *= inner_radius + (outer_radius - inner_radius) * textureLod(samplerCube(in_texture, in_sampler), position_zn, lod).x;
		vec3 normal_x = normalize(cross(position_yp - position_yn, position_zp - position_zn)) * sign(position.x);
		vec3 normal_y = normalize(cross(position_zp - position_zn, position_xp - position_xn)) * sign(position.y);
		vec3 normal_z = normalize(cross(position_xp - position_xn, position_yp - position_yn)) * sign(position.z);
		vec3 normal = normalize(normal_x * abs_position.x + normal_y * abs_position.y + normal_z * abs_position.z);
		
		// light parameters
		vec3 view_vector = normalize(s_camera - position.xyz);
		vec3 light_vector = normalize(s_light - position.xyz);
		
		float shadow = 1.0f;
		float diffuse = clamp(dot(light_vector, normal), 0.0f, 1.0f) * 0.5f;
		float specular = pow(clamp(dot(reflect(-light_vector, normal), view_vector), 0.0f, 1.0f), 32.0f);
		
		[[branch]] if(diffuse > 0.0f) {
			
			float height = length(position);
			step = light_vector * trace_step;
			position += step * get_noise(gl_FragCoord.xy / 1024.0f);
			steps = 64.0f;
			
			[[loop]] for(float i = 0.0f; i < steps; i += 1.0f) {
				float radius = length(position);
				if(radius > outer_radius + trace_step) i = steps;
				float h = textureLod(samplerCube(in_texture, in_sampler), position, lod).x;
				h = inner_radius + (outer_radius - inner_radius) * h - height;
				shadow = max(shadow - max(h * 4.0f, 0.0f), 0.0f);
				position += step;
			}
		}
		
		out_color = vec4(pow((diffuse + specular) * clamp(shadow + 0.05f, 0.0f, 1.0f), 1.0f / 2.2f));
	}
	
#endif
