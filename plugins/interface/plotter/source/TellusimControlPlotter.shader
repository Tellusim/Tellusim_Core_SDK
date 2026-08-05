// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#if VERTEX_SHADER
	
	#version 420 core
	
	layout(std140, row_major, binding = 0) uniform CanvasParameters {
		mat4 canvas_transform;
		vec4 canvas_color;
		vec2 canvas_size;
	};
	
	layout(std140, row_major, binding = 1) uniform ElementParameters {
		mat4 element_transform;
		vec4 element_color;
		float element_mipmap;
	};
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec4 in_parameters;
	layout(location = 2) in vec2 in_texcoord;
	
	layout(location = 0) centroid out vec2 s_texcoord;
	layout(location = 1) centroid out vec4 s_color;
	
	/*
	 */
	void main() {
		
		gl_Position = canvas_transform * (element_transform * vec4(in_position.xyz, 1.0f));
		
		s_texcoord = in_texcoord;
		
		s_color = canvas_color * element_color;
	}
	
#elif FRAGMENT_SHADER
	
	#version 420 core
	
	layout(location = 0) centroid in vec2 s_texcoord;
	layout(location = 1) centroid in vec4 s_color;
	
	layout(std140, binding = 3) uniform PlotParameters {
		vec4 plot_color;
		vec4 line_color;
		vec4 axis_color;
		vec4 range_x;
		vec4 range_y;
		float line_width;
		float axis_width;
		int max_values;
		int num_values;
	};
	
	layout(std140, binding = 4) uniform ValueParameters {
		vec4 values[MAX_VALUES / 4];
	};
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	float distance(vec2 p0, vec2 p1, vec2 p) {
		vec2 p10 = p1 - p0;
	    float k = clamp(dot(p - p0, p10) / dot(p10, p10), 0.0f, 1.0f);
	    return min(min(length(p0 - p), length(p1 - p)), length(p0 + p10 * k - p));
	}
	
	/*
	 */
	float get_value(int index) {
		index = index % max_values;
		vec4 value_4 = values[index >> 2];
		index &= 0x03;
		float value = value_4.x;
		if(index == 1) value = value_4.y;
		else if(index == 2) value = value_4.z;
		else if(index == 3) value = value_4.w;
		return (value - range_y.x) / range_y.y;
	}
	
	/*
	 */
	void main() {
		
		vec4 color = plot_color;
		
		float dx = dFdx(s_texcoord.x);
		float dy = abs(dFdy(s_texcoord.y));
		if(range_x.z > 0.0f) {
			float scale = range_x.y * range_x.z;
			float offset = range_x.x * range_x.z + range_x.w;
			color = mix(color, axis_color, smoothstep(dx * scale * axis_width, 0.0f, abs(s_texcoord.x * scale + offset - floor(s_texcoord.x * scale + offset + 0.5f)) * 2.0f));
		}
		if(range_y.z > 0.0f) {
			float scale = range_y.y * range_y.z;
			float offset = range_y.x * range_y.z;
			color = mix(color, axis_color, smoothstep(dy * scale * axis_width, 0.0f, abs(s_texcoord.y * scale + offset - floor(s_texcoord.y * scale + offset + 0.5f)) * 2.0f));
		}
		
		if(num_values > 3) {
			float step = 1.0f / float(max_values - 3);
			int index = int(s_texcoord.x * float(max_values - 3)) + 2;
			if(index > 1 && index + 2 < num_values) {
				float d = 1.0f;
				float x0 = float(index + 0) * step;
				float x1 = float(index - 1) * step;
				float x2 = float(index - 2) * step;
				float x3 = float(index - 3) * step;
				if(num_values > max_values) index += num_values - max_values;
				float y0 = get_value(index + 1);
				float y1 = get_value(index + 0);
				float y2 = get_value(index - 1);
				float y3 = get_value(index - 2);
				d = min(d, distance(vec2(x0, y0), vec2(x1, y1), s_texcoord));
				d = min(d, distance(vec2(x1, y1), vec2(x2, y2), s_texcoord));
				d = min(d, distance(vec2(x2, y2), vec2(x3, y3), s_texcoord));
				color = max(color, line_color * pow(smoothstep(line_width, 0.0f, d / min(dx, dy)), 2.0f));
			}
		}
		
		out_color = s_color * color;
	}
	
#endif
