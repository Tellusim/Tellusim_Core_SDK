// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_ORDER_H__
#define __TELLUSIM_MATH_ORDER_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Order utils
	 */
	namespace Order {
		
		/// Hilbert curve
		template <class Type = uint32_t> Type hilbert2(uint32_t size, uint32_t x, uint32_t y) {
			Type index = 0;
			TS_ASSERT(((size & (size - 1)) == 0));
			for(uint32_t s = size >> 1; s > 0; s >>= 1) {
				uint32_t rx = ((x & s) != 0);
				uint32_t ry = ((y & s) != 0);
				index += ((rx * 3) ^ ry) * s * s;
				if(ry == 0) {
					if(rx == 1) {
						x = size - x - 1;
						y = size - y - 1;
					}
					swap(x, y);
				}
			}
			return index;
		}
		
		/// inverse Hilbert curve
		template <class Type = uint32_t> void ihilbert2(uint32_t size, Type index, uint32_t &x, uint32_t &y) {
			x = 0; y = 0;
			TS_ASSERT(((size & (size - 1)) == 0));
			for(uint32_t s = 1; s < size; s <<= 1, index >>= 2) {
				uint32_t rx = (index >> 1) & 1;
				uint32_t ry = (index ^ rx) & 1;
				if(ry == 0) {
					if(rx == 1) {
						x = s - x - 1;
						y = s - y - 1;
					}
					swap(x, y);
				}
				x += s * rx;
				y += s * ry;
			}
		}
	}
}

#endif /* __TELLUSIM_MATH_ORDER_H__ */
