// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#if DECLARE_TEXTURE_SAMPLE
vec4 textureSample(vec2 texcoord) {
	return texture(sampler2D(TEXTURE, in_sampler), s_texcoord);
}
#endif
