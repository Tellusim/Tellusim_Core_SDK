// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*****************************************************************************\
 *
 * Base
 *
\*****************************************************************************/

/*
 */
tsBase = Object.freeze({
	
	/// 8-bit integer constants
	Mini8 : -127 - 1,
	Maxi8 :  127,
	Maxu8 : -1,
	
	/// 16-bit integer constants
	Mini16 : -32767 - 1,
	Maxi16 :  32767,
	Maxu16 : -1,
	
	/// 32-bit integer constants
	Mini32 : -2147483647 - 1,
	Maxi32 :  2147483647,
	Maxu32 : -1,
	
	/// 64-bit integer constants
	Mini64 : -9223372036854775807 - 1,
	Maxi64 :  9223372036854775807,
	Maxu64 : -1,
	
	/// 16-bit floating point constants
	Minf16 : 5.96046448e-08,
	Maxf16 : 65504.0,
	
	/// 32-bit floating point constants
	Minf32 : 1.17549435e-38,
	Maxf32 : 3.40282346e+38,
	Pi : 3.141592653589793,
	Pi2 : 6.283185307179586,
	Pi05 : 1.570796326794897,
	Sqrt2 : 1.4142135623730951,
	Deg2Rad : 0.017453292519943,
	Rad2Deg : 57.295779513082325,
	
	/// 64-bit floating point constants
	Minf64 : 2.22507385850720138e-308,
	Maxf64 : 1.79769313486231571e+308,
	Pid : 3.141592653589793115997963468544,
	Pi2d : 6.283185307179586231995926937088,
	Pi05d : 1.570796326794896557998981734272,
	Sqrt2d : 1.414213562373095145474621858739,
	Deg2Radd : 0.017453292519943295474371680598,
	Rad2Degd : 57.295779513082322864647721871734,
});
Module['Base'] = tsBase;

/*****************************************************************************\
 *
 * Self
 *
\*****************************************************************************/

/*
 */
function ts_new(type, self) {
	object = Object.create(type.prototype);
	type.finalizer.register(object, self);
	object.self = self;
	return object;
}

/*
 */
function ts_bind(type, object, self) {
	type.finalizer.register(object, self);
	object.self = self;
}

/*****************************************************************************\
 *
 * Arguments
 *
\*****************************************************************************/

/*
 */
var ts_args = {
	
	buffer : undefined,
	buffers : [],
	capacity : 0,
	offset : 1024,
	
	reset() {
		if(ts_args.capacity < ts_args.offset) {
			_ts_free(ts_args.buffer);
			ts_args.capacity = (ts_args.offset * 3 + 2) >> 1;
			ts_args.buffer = _ts_malloc(ts_args.capacity);
		}
		for(let i = 0; i < ts_args.buffers.length; i++) {
			_ts_free(ts_args.buffers[i]);
		}
		ts_args.buffers.length = 0;
		ts_args.offset = 0;
	},
	allocate(array, heap) {
		let size = (heap.BYTES_PER_ELEMENT * array.length + 7) & ~7;
		if(ts_args.offset + size > ts_args.capacity) {
			let ret = _ts_malloc(size);
			ts_args.buffers.push(ret);
			ts_args.offset += size;
			return ret;
		}
		let ret = ts_args.buffer + ts_args.offset;
		ts_args.offset += size;
		return ret;
	},
	copy(offset, array, heap) {
		offset /= heap.BYTES_PER_ELEMENT;
		for(let i = 0; i < array.length; i++) {
			heap[offset + i] = array[i];
		}
	}
}

/*
 */
function ts_str(str, reset) {
	if(typeof str === 'string') {
		if(reset === true) ts_args.reset();
		let array = intArrayFromString(str);
		let offset = ts_args.allocate(array, HEAP8);
		ts_args.copy(offset, array, HEAP8);
		return offset;
	}
	return str;
}

function ts_array(array, reset, heap) {
	if(heap === undefined) {
		if(array instanceof ArrayBuffer) { array = new Uint8Array(array); heap = HEAP8; }
		else if(array instanceof Int8Array || array instanceof Uint8Array) heap = HEAP8;
		else if(array instanceof Int16Array || array instanceof Uint16Array) heap = HEAP16;
		else if(array instanceof Int32Array || array instanceof Uint32Array) heap = HEAP32;
		else if(array instanceof Float32Array) heap = HEAPF32;
		else if(array instanceof Float64Array) heap = HEAPF64;
		else if(typeof array === 'string') return ts_str(array, reset);
		else throw('unknown array type ' + typeof array);
	}
	if(typeof array === 'object') {
		if(reset === true) ts_args.reset();
		let offset = ts_args.allocate(array, heap);
		ts_args.copy(offset, array, heap);
		return offset;
	}
	return array;
}

function ts_array2(array, reset) {
	if(array instanceof Array) {
		if(reset) ts_args.reset();
		let offset = ts_args.allocate(array, HEAP32);
		let index = offset / HEAP32.BYTES_PER_ELEMENT;
		for(let i = 0; i < array.length; i++) {
			HEAP32[index + i] = ts_array(array[i]);
		}
		return offset;
	}
	return array;
}

/*
 */
function ts_i8(array, reset) { return ts_array(array, reset, HEAP8); }
function ts_i16(array, reset) { return ts_array(array, reset, HEAP16); }
function ts_i32(array, reset) { return ts_array(array, reset, HEAP32); }
function ts_f32(array, reset) { return ts_array(array, reset, HEAPF32); }
function ts_f64(array, reset) { return ts_array(array, reset, HEAPF64); }

/*****************************************************************************\
 *
 * Color
 *
\*****************************************************************************/

/*
 */
function tsColor(r, g, b, a) {
	if(r instanceof tsColor && g === undefined) return ts_bind(tsColor, this, _tsColor_copy(r.self));
	if(r instanceof tsColor && g !== undefined) return ts_bind(tsColor, this, _tsColor_new_ca(r.self, g));
	if(r instanceof Array && r.length === 4) return ts_bind(tsColor, this, _tsColor_new_af(ts_f32(r, true)));
	if(r !== undefined && g !== undefined && b !== undefined && a !== undefined) return ts_bind(tsColor, this, _tsColor_new_rgba(r, g, b, a));
	if(r !== undefined && g !== undefined) return ts_bind(tsColor, this, _tsColor_new_la(r, g));
	if(r !== undefined && g === undefined) return ts_bind(tsColor, this, _tsColor_new_v(r));
	if(r === undefined && g === undefined) return ts_bind(tsColor, this, _tsColor_new());
	throw 'invalid Color() arguments';
}
Module['Color'] = tsColor;
tsColor.finalizer = new FinalizationRegistry((self) => { _tsColor_delete(self); });
tsColor.prototype = Object.create(tsColor.prototype);
tsColor.prototype.constructor = tsColor;

tsColor.prototype['toBytes'] = tsColor.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 16); }
tsColor.prototype['toArray'] = tsColor.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 4); }
tsColor.prototype['toString'] = tsColor.prototype.toString = function() { return '(' + this.r + ' ' + this.g + ' ' + this.b + ' ' + this.a + ')'; };

/*
 */
tsColor.prototype['set'] = tsColor.prototype.set = function(index, v) { _tsColor_set_index(this.self, index, v); };
tsColor.prototype['get'] = tsColor.prototype.get = function(index) { return _tsColor_get_index(this.self, index); };

tsColor.prototype['set_r'] = tsColor.prototype.set_r = function(r) { _tsColor_set_r(this.self, r); };
tsColor.prototype['set_g'] = tsColor.prototype.set_g = function(g) { _tsColor_set_g(this.self, g); };
tsColor.prototype['set_b'] = tsColor.prototype.set_b = function(b) { _tsColor_set_b(this.self, b); };
tsColor.prototype['set_a'] = tsColor.prototype.set_a = function(a) { _tsColor_set_a(this.self, a); };

tsColor.prototype['get_r'] = tsColor.prototype.get_r = function() { return _tsColor_get_r(this.self); };
tsColor.prototype['get_g'] = tsColor.prototype.get_g = function() { return _tsColor_get_g(this.self); };
tsColor.prototype['get_b'] = tsColor.prototype.get_b = function() { return _tsColor_get_b(this.self); };
tsColor.prototype['get_a'] = tsColor.prototype.get_a = function() { return _tsColor_get_a(this.self); };

Object.defineProperty(tsColor.prototype, 'r', { set: tsColor.prototype.set_r, get: tsColor.prototype.get_r });
Object.defineProperty(tsColor.prototype, 'g', { set: tsColor.prototype.set_g, get: tsColor.prototype.get_g });
Object.defineProperty(tsColor.prototype, 'b', { set: tsColor.prototype.set_b, get: tsColor.prototype.get_b });
Object.defineProperty(tsColor.prototype, 'a', { set: tsColor.prototype.set_a, get: tsColor.prototype.get_a });

/*
 */
tsColor.prototype['mul'] = tsColor.prototype.mul = function(v) {
	if(v instanceof tsColor) return ts_new(tsColor, _tsColor_mul(this.self, v.self));
	return ts_new(tsColor, _tsColor_mul1(this.self, v));
};
tsColor.prototype['div'] = tsColor.prototype.div = function(v) {
	if(v instanceof tsColor) return ts_new(_tsColor_div(this.self, v.self));
	return ts_new(tsColor, _tsColor_div1(this.self, v));
};
tsColor.prototype['add'] = tsColor.prototype.add = function(v) {
	if(v instanceof tsColor) return ts_new(tsColor, _tsColor_add(this.self, v.self));
	return ts_new(tsColor, _tsColor_add1(this.self, v));
};
tsColor.prototype['sub'] = tsColor.prototype.sub = function(v) {
	if(v instanceof tsColor) return ts_new(tsColor, _tsColor_sub(this.self, v.self));
	return ts_new(tsColor, _tsColor_sub1(this.self, v));
};

tsColor['hsv'] = tsColor.hsv = function(h, s, v) { return ts_new(tsColor, _tsColor_hsv(h, s, v)); };
tsColor['temperature'] = tsColor.temperature = function(t) { return ts_new(tsColor, _tsColor_temperature(t)); };

tsColor['min'] = tsColor.min = function(v0, v1) { return ts_new(tsColor, _tsColor_min(v0.self, v1.self)); };
tsColor['max'] = tsColor.max = function(v0, v1) { return ts_new(tsColor, _tsColor_max(v0.self, v1.self)); };

tsColor.prototype['clamp'] = tsColor.prototype.clamp = function(v0, v1) { return ts_new(tsColor, _tsColor_clamp(this.self, v0.self, v1.self)); };
tsColor.prototype['saturate'] = tsColor.prototype.saturate = function() { return ts_new(tsColor, _tsColor_saturate(this.self)); };

tsColor['lerp'] = tsColor.lerp = function(v0, v1, k) { return ts_new(tsColor, _tsColor_lerp(v0.self, v1.self, k)); };

tsColor['zero'] = tsColor.zero = function() { return ts_new(tsColor, _tsColor_new_rgba(0.0, 0.0, 0.0, 0.0)); };
tsColor['black'] = tsColor.black = function() { return ts_new(tsColor, _tsColor_new_rgba(0.0, 0.0, 0.0, 1.0)); };
tsColor['white'] = tsColor.white = function() { return ts_new(tsColor, _tsColor_new_rgba(1.0, 1.0, 1.0, 1.0)); };
tsColor['gray'] = tsColor.gray = function() { return ts_new(tsColor, _tsColor_new_rgba(0.5, 0.5, 0.5, 1.0)); };

tsColor['red'] = tsColor.red = function() { return ts_new(tsColor, _tsColor_new_rgba(1.0, 0.0, 0.0, 1.0)); };
tsColor['yellow'] = tsColor.yellow = function() { return ts_new(tsColor, _tsColor_new_rgba(1.0, 1.0, 0.0, 1.0)); };
tsColor['green'] = tsColor.green = function() { return ts_new(tsColor, _tsColor_new_rgba(0.0, 1.0, 0.0, 1.0)); };
tsColor['cyan'] = tsColor.cyan = function() { return ts_new(tsColor, _tsColor_new_rgba(0.0, 1.0, 1.0, 1.0)); };
tsColor['blue'] = tsColor.blue = function() { return ts_new(tsColor, _tsColor_new_rgba(0.0, 0.0, 1.0, 1.0)); };
tsColor['magenta'] = tsColor.magenta = function() { return ts_new(tsColor, _tsColor_new_rgba(1.0, 0.0, 1.0, 1.0)); };

/*****************************************************************************\
 *
 * ImageColor
 *
\*****************************************************************************/

/*
 */
function tsImageColor(r, g, b, a) {
	if(r instanceof tsImageColor && g === undefined) return ts_bind(tsImageColor, this, _tsImageColor_copy(r.self));
	if(r instanceof tsColor && g !== undefined) return ts_bind(tsImageColor, this, _tsImageColor_new_c(r.self, g));
	if(r !== undefined && g !== undefined && b !== undefined && a !== undefined) return ts_bind(tsImageColor, this, _tsImageColor_new_rgba(r, g, b, a));
	if(r !== undefined && g !== undefined) return ts_bind(tsImageColor, this, _tsImageColor_new_la(r, g));
	if(r !== undefined && g === undefined) return ts_bind(tsImageColor, this, _tsImageColor_new_v(r));
	if(r === undefined && g === undefined) return ts_bind(tsImageColor, this, _tsImageColor_new());
	throw 'invalid ImageColor() arguments';
}
Module['ImageColor'] = tsImageColor;
tsImageColor.finalizer = new FinalizationRegistry((self) => { _tsImageColor_delete(self); });
tsImageColor.prototype = Object.create(tsImageColor.prototype);
tsImageColor.prototype.constructor = tsImageColor;

tsImageColor.prototype['toBytes'] = tsImageColor.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 16); }
tsImageColor.prototype['toArray'] = tsImageColor.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 4); }
tsImageColor.prototype['toString'] = tsImageColor.prototype.toString = function() { return '(' + this.ri + ' ' + this.gi + ' ' + this.bi + ' ' + this.ai + ')'; };

/*
 */
tsImageColor.prototype['set'] = tsImageColor.prototype.set = function(color, format) { _tsImageColor_set_c(this.self, color.self, format); };
tsImageColor.prototype['get'] = tsImageColor.prototype.get = function(format) { return ts_new(tsColor, _tsImageColor_get_c(this.self, format)); };

tsImageColor.prototype['set_ri'] = tsImageColor.prototype.set_ri = function(r) { _tsImageColor_set_ri(this.self, r); };
tsImageColor.prototype['set_gi'] = tsImageColor.prototype.set_gi = function(g) { _tsImageColor_set_gi(this.self, g); };
tsImageColor.prototype['set_bi'] = tsImageColor.prototype.set_bi = function(b) { _tsImageColor_set_bi(this.self, b); };
tsImageColor.prototype['set_ai'] = tsImageColor.prototype.set_ai = function(a) { _tsImageColor_set_ai(this.self, a); };
tsImageColor.prototype['set_rf'] = tsImageColor.prototype.set_rf = function(r) { _tsImageColor_set_rf(this.self, r); };
tsImageColor.prototype['set_gf'] = tsImageColor.prototype.set_gf = function(g) { _tsImageColor_set_gf(this.self, g); };
tsImageColor.prototype['set_bf'] = tsImageColor.prototype.set_bf = function(b) { _tsImageColor_set_bf(this.self, b); };
tsImageColor.prototype['set_af'] = tsImageColor.prototype.set_af = function(a) { _tsImageColor_set_af(this.self, a); };

tsImageColor.prototype['get_ri'] = tsImageColor.prototype.get_ri = function() { return _tsImageColor_get_ri(this.self); };
tsImageColor.prototype['get_gi'] = tsImageColor.prototype.get_gi = function() { return _tsImageColor_get_gi(this.self); };
tsImageColor.prototype['get_bi'] = tsImageColor.prototype.get_bi = function() { return _tsImageColor_get_bi(this.self); };
tsImageColor.prototype['get_ai'] = tsImageColor.prototype.get_ai = function() { return _tsImageColor_get_ai(this.self); };
tsImageColor.prototype['get_rf'] = tsImageColor.prototype.get_rf = function() { return _tsImageColor_get_rf(this.self); };
tsImageColor.prototype['get_gf'] = tsImageColor.prototype.get_gf = function() { return _tsImageColor_get_gf(this.self); };
tsImageColor.prototype['get_bf'] = tsImageColor.prototype.get_bf = function() { return _tsImageColor_get_bf(this.self); };
tsImageColor.prototype['get_af'] = tsImageColor.prototype.get_af = function() { return _tsImageColor_get_af(this.self); };

Object.defineProperty(tsImageColor.prototype, 'ri', { set: tsImageColor.prototype.set_ri, get: tsImageColor.prototype.get_ri });
Object.defineProperty(tsImageColor.prototype, 'gi', { set: tsImageColor.prototype.set_gi, get: tsImageColor.prototype.get_gi });
Object.defineProperty(tsImageColor.prototype, 'bi', { set: tsImageColor.prototype.set_bi, get: tsImageColor.prototype.get_bi });
Object.defineProperty(tsImageColor.prototype, 'ai', { set: tsImageColor.prototype.set_ai, get: tsImageColor.prototype.get_ai });
Object.defineProperty(tsImageColor.prototype, 'rf', { set: tsImageColor.prototype.set_rf, get: tsImageColor.prototype.get_rf });
Object.defineProperty(tsImageColor.prototype, 'gf', { set: tsImageColor.prototype.set_gf, get: tsImageColor.prototype.get_gf });
Object.defineProperty(tsImageColor.prototype, 'bf', { set: tsImageColor.prototype.set_bf, get: tsImageColor.prototype.get_bf });
Object.defineProperty(tsImageColor.prototype, 'af', { set: tsImageColor.prototype.set_af, get: tsImageColor.prototype.get_af });

/*****************************************************************************\
 *
 * BoundRectf
 *
\*****************************************************************************/

/*
 */
function tsBoundRectf(min, max) {
	if(min instanceof tsBoundRectf) return ts_bind(tsBoundRectf, this, _tsBoundRectf_copy(min.self));
	if(min instanceof tsBoundRectd) return ts_bind(tsBoundRectf, this, _tsBoundRectf_new_brd(min.self));
	if(min instanceof tsBoundCirclef) return ts_bind(tsBoundRectf, this, _tsBoundRectf_new_bc(min.self));
	if(min instanceof tsVector2f && max instanceof tsVector2f) return ts_bind(tsBoundRectf, this, _tsBoundRectf_new_mm(min.self, max.self));
	if(min === undefined) return ts_bind(tsBoundRectf, this, _tsBoundRectf_new());
	throw 'invalid BoundRectf() arguments';
}
Module['BoundRectf'] = tsBoundRectf;
tsBoundRectf.finalizer = new FinalizationRegistry((self) => { _tsBoundRectf_delete(self); });
tsBoundRectf.prototype = Object.create(tsBoundRectf.prototype);
tsBoundRectf.prototype.constructor = tsBoundRectf;

tsBoundRectf.prototype['toBytes'] = tsBoundRectf.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 16); }
tsBoundRectf.prototype['toArray'] = tsBoundRectf.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 4); }
tsBoundRectf.prototype['toString'] = tsBoundRectf.prototype.toString = function() { return this.min + ' : ' + this.max; };

/*
 */
tsBoundRectf.prototype['set_min'] = tsBoundRectf.prototype.set_min = function(min) { _tsBoundRectf_set_min(this.self, min.self); };
tsBoundRectf.prototype['set_max'] = tsBoundRectf.prototype.set_max = function(max) { _tsBoundRectf_set_max(this.self, max.self); };
tsBoundRectf.prototype['set_x0'] = tsBoundRectf.prototype.set_x0 = function(x) { _tsBoundRectf_set_x0(this.self, x); };
tsBoundRectf.prototype['set_y0'] = tsBoundRectf.prototype.set_y0 = function(y) { _tsBoundRectf_set_y0(this.self, y); };
tsBoundRectf.prototype['set_x1'] = tsBoundRectf.prototype.set_x1 = function(x) { _tsBoundRectf_set_x1(this.self, x); };
tsBoundRectf.prototype['set_y1'] = tsBoundRectf.prototype.set_y1 = function(y) { _tsBoundRectf_set_y1(this.self, y); };

tsBoundRectf.prototype['get_min'] = tsBoundRectf.prototype.get_min = function() { return ts_new(tsVector2f, _tsBoundRectf_get_min(this.self)); };
tsBoundRectf.prototype['get_max'] = tsBoundRectf.prototype.get_max = function() { return ts_new(tsVector2f, _tsBoundRectf_get_max(this.self)); };
tsBoundRectf.prototype['get_x0'] = tsBoundRectf.prototype.get_x0 = function() { return _tsBoundRectf_get_x0(this.self); };
tsBoundRectf.prototype['get_y0'] = tsBoundRectf.prototype.get_y0 = function() { return _tsBoundRectf_get_y0(this.self); };
tsBoundRectf.prototype['get_x1'] = tsBoundRectf.prototype.get_x1 = function() { return _tsBoundRectf_get_x1(this.self); };
tsBoundRectf.prototype['get_y1'] = tsBoundRectf.prototype.get_y1 = function() { return _tsBoundRectf_get_y1(this.self); };

Object.defineProperty(tsBoundRectf.prototype, 'min', { set: tsBoundRectf.prototype.set_min, get: tsBoundRectf.prototype.get_min });
Object.defineProperty(tsBoundRectf.prototype, 'max', { set: tsBoundRectf.prototype.set_max, get: tsBoundRectf.prototype.get_max });
Object.defineProperty(tsBoundRectf.prototype, 'x0', { set: tsBoundRectf.prototype.set_x0, get: tsBoundRectf.prototype.get_x0 });
Object.defineProperty(tsBoundRectf.prototype, 'y0', { set: tsBoundRectf.prototype.set_y0, get: tsBoundRectf.prototype.get_y0 });
Object.defineProperty(tsBoundRectf.prototype, 'x1', { set: tsBoundRectf.prototype.set_x1, get: tsBoundRectf.prototype.get_x1 });
Object.defineProperty(tsBoundRectf.prototype, 'y1', { set: tsBoundRectf.prototype.set_y1, get: tsBoundRectf.prototype.get_y1 });

/*
 */
tsBoundRectf.prototype['expand'] = tsBoundRectf.prototype.expand = function(v) {
	if(v instanceof tsVector2f) return _tsBoundRectf_expand1(this.self, v.self);
	if(v instanceof tsBoundRectf) return _tsBoundRectf_expand(this.self, v.self);
	throw 'invalid BoundRectf.expand() arguments';
};

tsBoundRectf.prototype['inside'] = tsBoundRectf.prototype.inside = function(v) {
	if(v instanceof tsVector2f) return _tsBoundRectf_inside1(this.self, v.self);
	if(v instanceof tsBoundRectf) return _tsBoundRectf_inside(this.self, v.self);
	throw 'invalid BoundRectf.inside() arguments';
};

tsBoundRectf.prototype['distance'] = tsBoundRectf.prototype.distance = function(v) {
	if(v instanceof tsVector2f) return _tsBoundRectf_distance(this.self, v.self);
	throw 'invalid BoundRectf.distance() arguments';
};

/*****************************************************************************\
 *
 * BoundRectd
 *
\*****************************************************************************/

/*
 */
function tsBoundRectd(min, max) {
	if(min instanceof tsBoundRectd) return ts_bind(tsBoundRectd, this, _tsBoundRectd_copy(min.self));
	if(min instanceof tsBoundRectf) return ts_bind(tsBoundRectd, this, _tsBoundRectd_new_brf(min.self));
	if(min instanceof tsBoundCircled) return ts_bind(tsBoundRectd, this, _tsBoundRectd_new_bc(min.self));
	if(min instanceof tsVector2d && max instanceof tsVector2d) return ts_bind(tsBoundRectd, this, _tsBoundRectd_new_mm(min.self, max.self));
	if(min === undefined) return ts_bind(tsBoundRectd, this, _tsBoundRectd_new());
	throw 'invalid BoundRectd arguments';
}
Module['BoundRectd'] = tsBoundRectd;
tsBoundRectd.finalizer = new FinalizationRegistry((self) => { _tsBoundRectd_delete(self); });
tsBoundRectd.prototype = Object.create(tsBoundRectd.prototype);
tsBoundRectd.prototype.constructor = tsBoundRectd;

tsBoundRectd.prototype['toBytes'] = tsBoundRectd.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 32); }
tsBoundRectd.prototype['toArray'] = tsBoundRectd.prototype.getArray = function() { return new Float64Array(HEAPF64.buffer, this.self, 4); }
tsBoundRectd.prototype['toString'] = tsBoundRectd.prototype.toString = function() { return this.min + ' : ' + this.max; };

/*
 */
tsBoundRectd.prototype['set_min'] = tsBoundRectd.prototype.set_min = function(min) { _tsBoundRectd_set_min(this.self, min.self); };
tsBoundRectd.prototype['set_max'] = tsBoundRectd.prototype.set_max = function(max) { _tsBoundRectd_set_max(this.self, max.self); };
tsBoundRectd.prototype['set_x0'] = tsBoundRectd.prototype.set_x0 = function(x) { _tsBoundRectd_set_x0(this.self, x); };
tsBoundRectd.prototype['set_y0'] = tsBoundRectd.prototype.set_y0 = function(y) { _tsBoundRectd_set_y0(this.self, y); };
tsBoundRectd.prototype['set_x1'] = tsBoundRectd.prototype.set_x1 = function(x) { _tsBoundRectd_set_x1(this.self, x); };
tsBoundRectd.prototype['set_y1'] = tsBoundRectd.prototype.set_y1 = function(y) { _tsBoundRectd_set_y1(this.self, y); };

tsBoundRectd.prototype['get_min'] = tsBoundRectd.prototype.get_min = function() { return ts_new(tsVector2d, _tsBoundRectd_get_min(this.self)); };
tsBoundRectd.prototype['get_max'] = tsBoundRectd.prototype.get_max = function() { return ts_new(tsVector2d, _tsBoundRectd_get_max(this.self)); };
tsBoundRectd.prototype['get_x0'] = tsBoundRectd.prototype.get_x0 = function() { return _tsBoundRectd_get_x0(this.self); };
tsBoundRectd.prototype['get_y0'] = tsBoundRectd.prototype.get_y0 = function() { return _tsBoundRectd_get_y0(this.self); };
tsBoundRectd.prototype['get_x1'] = tsBoundRectd.prototype.get_x1 = function() { return _tsBoundRectd_get_x1(this.self); };
tsBoundRectd.prototype['get_y1'] = tsBoundRectd.prototype.get_y1 = function() { return _tsBoundRectd_get_y1(this.self); };

Object.defineProperty(tsBoundRectd.prototype, 'min', { set: tsBoundRectd.prototype.set_min, get: tsBoundRectd.prototype.get_min });
Object.defineProperty(tsBoundRectd.prototype, 'max', { set: tsBoundRectd.prototype.set_max, get: tsBoundRectd.prototype.get_max });
Object.defineProperty(tsBoundRectd.prototype, 'x0', { set: tsBoundRectd.prototype.set_x0, get: tsBoundRectd.prototype.get_x0 });
Object.defineProperty(tsBoundRectd.prototype, 'y0', { set: tsBoundRectd.prototype.set_y0, get: tsBoundRectd.prototype.get_y0 });
Object.defineProperty(tsBoundRectd.prototype, 'x1', { set: tsBoundRectd.prototype.set_x1, get: tsBoundRectd.prototype.get_x1 });
Object.defineProperty(tsBoundRectd.prototype, 'y1', { set: tsBoundRectd.prototype.set_y1, get: tsBoundRectd.prototype.get_y1 });

/*
 */
tsBoundRectd.prototype['expand'] = tsBoundRectd.prototype.expand = function(v) {
	if(v instanceof tsVector2d) return _tsBoundRectd_expand1(this.self, v.self);
	if(v instanceof tsBoundRectd) return _tsBoundRectd_expand(this.self, v.self);
	throw 'invalid BoundRectd.expand() arguments';
};

tsBoundRectd.prototype['inside'] = tsBoundRectd.prototype.inside = function(v) {
	if(v instanceof tsVector2d) return _tsBoundRectd_inside1(this.self, v.self);
	if(v instanceof tsBoundRectd) return _tsBoundRectd_inside(this.self, v.self);
	throw 'invalid BoundRectd.inside() arguments';
};

tsBoundRectd.prototype['distance'] = tsBoundRectd.prototype.distance = function(v) {
	if(v instanceof tsVector2d) return _tsBoundRectd_distance(this.self, v.self);
	throw 'invalid BoundRectd.distance() arguments';
};

/*****************************************************************************\
 *
 * BoundCirclef
 *
\*****************************************************************************/

/*
 */
function tsBoundCirclef(center, radius) {
	if(center instanceof tsBoundCirclef) return ts_bind(tsBoundCirclef, this, _tsBoundCirclef_copy(center.self));
	if(center instanceof tsBoundCircled) return ts_bind(tsBoundCirclef, this, _tsBoundCirclef_new_bcd(center.self));
	if(center instanceof tsBoundRectf) return ts_bind(tsBoundCirclef, this, _tsBoundCirclef_new_br(center.self));
	if(center instanceof tsVector2f && max !== undefined) return ts_bind(tsBoundCirclef, this, _tsBoundCirclef_new_cr(center.self, radius));
	if(center === undefined) return ts_bind(tsBoundCirclef, this, _tsBoundCirclef_new());
	throw 'invalid BoundCirclef() arguments';
}
Module['BoundCirclef'] = tsBoundCirclef;
tsBoundCirclef.finalizer = new FinalizationRegistry((self) => { _tsBoundCirclef_delete(self); });
tsBoundCirclef.prototype = Object.create(tsBoundCirclef.prototype);
tsBoundCirclef.prototype.constructor = tsBoundCirclef;

tsBoundCirclef.prototype['toBytes'] = tsBoundCirclef.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 12); }
tsBoundCirclef.prototype['toArray'] = tsBoundCirclef.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 3); }
tsBoundCirclef.prototype['toString'] = tsBoundCirclef.prototype.toString = function() { return this.center + ' : ' + this.radius; };

/*
 */
tsBoundCirclef.prototype['set_center'] = tsBoundCirclef.prototype.set_center = function(center) { _tsBoundCirclef_set_center(this.self, center.self); };
tsBoundCirclef.prototype['set_radius'] = tsBoundCirclef.prototype.set_radius = function(radius) { _tsBoundCirclef_set_radius(this.self, radius); };
tsBoundCirclef.prototype['set_x'] = tsBoundCirclef.prototype.set_x = function(x) { _tsBoundCirclef_set_x(this.self, x); };
tsBoundCirclef.prototype['set_y'] = tsBoundCirclef.prototype.set_y = function(y) { _tsBoundCirclef_set_y(this.self, y); };

tsBoundCirclef.prototype['get_center'] = tsBoundCirclef.prototype.get_center = function() { return ts_new(tsVector2f, _tsBoundCirclef_get_center(this.self)); };
tsBoundCirclef.prototype['get_radius'] = tsBoundCirclef.prototype.get_radius = function() { return _tsBoundCirclef_get_radius(this.self); };
tsBoundCirclef.prototype['get_x'] = tsBoundCirclef.prototype.get_x = function() { return _tsBoundCirclef_get_x(this.self); };
tsBoundCirclef.prototype['get_y'] = tsBoundCirclef.prototype.get_y = function() { return _tsBoundCirclef_get_y(this.self); };

Object.defineProperty(tsBoundCirclef.prototype, 'center', { set: tsBoundCirclef.prototype.set_center, get: tsBoundCirclef.prototype.get_center });
Object.defineProperty(tsBoundCirclef.prototype, 'radius', { set: tsBoundCirclef.prototype.set_radius, get: tsBoundCirclef.prototype.get_radius });
Object.defineProperty(tsBoundCirclef.prototype, 'x', { set: tsBoundCirclef.prototype.set_x, get: tsBoundCirclef.prototype.get_x });
Object.defineProperty(tsBoundCirclef.prototype, 'y', { set: tsBoundCirclef.prototype.set_y, get: tsBoundCirclef.prototype.get_y });

/*
 */
tsBoundCirclef.prototype['expand'] = tsBoundCirclef.prototype.expand = function(v) {
	if(v instanceof tsVector2f) return _tsBoundCirclef_expand1(this.self, v.self);
	if(v instanceof tsBoundCirclef) return _tsBoundCirclef_expand(this.self, v.self);
	throw 'invalid BoundCirclef.expand() arguments';
};
tsBoundCirclef.prototype['expandRadius'] = tsBoundCirclef.prototype.expandRadius = function(v) {
	if(v instanceof tsVector2f) return _tsBoundCirclef_expandRadius1(this.self, v.self);
	if(v instanceof tsBoundCirclef) return _tsBoundCirclef_expandRadius(this.self, v.self);
	throw 'invalid BoundCirclef.expandRadius() arguments';
};

tsBoundCirclef.prototype['inside'] = tsBoundCirclef.prototype.inside = function(v) {
	if(v instanceof tsVector2f) return _tsBoundCirclef_inside1(this.self, v.self);
	if(v instanceof tsBoundCirclef) return _tsBoundCirclef_inside(this.self, v.self);
	throw 'invalid BoundCirclef.inside() arguments';
};

tsBoundCirclef.prototype['distance'] = tsBoundCirclef.prototype.distance = function(v) {
	if(v instanceof tsVector2f) return _tsBoundCirclef_distance(this.self, v.self);
	throw 'invalid BoundCirclef.distance() arguments';
};

/*****************************************************************************\
 *
 * BoundCircled
 *
\*****************************************************************************/

/*
 */
function tsBoundCircled(center, radius) {
	if(center instanceof tsBoundCircled) return ts_bind(tsBoundCircled, this, _tsBoundCircled_copy(center.self));
	if(center instanceof tsBoundCirclef) return ts_bind(tsBoundCircled, this, _tsBoundCircled_new_bcf(center.self));
	if(center instanceof tsBoundRectd) return ts_bind(tsBoundCircled, this, _tsBoundCircled_new_br(center.self));
	if(center instanceof tsVector2d && max !== undefined) return ts_bind(tsBoundCircled, this, _tsBoundCircled_new_cr(center.self, radius));
	if(center === undefined) return ts_bind(tsBoundCircled, this, _tsBoundCircled_new());
	throw 'invalid BoundCircled() arguments';
}
Module['BoundCircled'] = tsBoundCircled;
tsBoundCircled.finalizer = new FinalizationRegistry((self) => { _tsBoundCircled_delete(self); });
tsBoundCircled.prototype = Object.create(tsBoundCircled.prototype);
tsBoundCircled.prototype.constructor = tsBoundCircled;

tsBoundCircled.prototype['toBytes'] = tsBoundCircled.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 24); }
tsBoundCircled.prototype['toArray'] = tsBoundCircled.prototype.getArray = function() { return new Float64Array(HEAPF64.buffer, this.self, 3); }
tsBoundCircled.prototype['toString'] = tsBoundCircled.prototype.toString = function() { return this.center + ' : ' + this.radius; };

/*
 */
tsBoundCircled.prototype['set_center'] = tsBoundCircled.prototype.set_center = function(center) { _tsBoundCircled_set_center(this.self, center.self); };
tsBoundCircled.prototype['set_radius'] = tsBoundCircled.prototype.set_radius = function(radius) { _tsBoundCircled_set_radius(this.self, radius); };
tsBoundCircled.prototype['set_x'] = tsBoundCircled.prototype.set_x = function(x) { _tsBoundCircled_set_x(this.self, x); };
tsBoundCircled.prototype['set_y'] = tsBoundCircled.prototype.set_y = function(y) { _tsBoundCircled_set_y(this.self, y); };

tsBoundCircled.prototype['get_center'] = tsBoundCircled.prototype.get_center = function() { return ts_new(tsVector2d, _tsBoundCircled_get_center(this.self)); };
tsBoundCircled.prototype['get_radius'] = tsBoundCircled.prototype.get_radius = function() { return _tsBoundCircled_get_radius(this.self); };
tsBoundCircled.prototype['get_x'] = tsBoundCircled.prototype.get_x = function() { return _tsBoundCircled_get_x(this.self); };
tsBoundCircled.prototype['get_y'] = tsBoundCircled.prototype.get_y = function() { return _tsBoundCircled_get_y(this.self); };

Object.defineProperty(tsBoundCircled.prototype, 'center', { set: tsBoundCircled.prototype.set_center, get: tsBoundCircled.prototype.get_center });
Object.defineProperty(tsBoundCircled.prototype, 'radius', { set: tsBoundCircled.prototype.set_radius, get: tsBoundCircled.prototype.get_radius });
Object.defineProperty(tsBoundCircled.prototype, 'x', { set: tsBoundCircled.prototype.set_x, get: tsBoundCircled.prototype.get_x });
Object.defineProperty(tsBoundCircled.prototype, 'y', { set: tsBoundCircled.prototype.set_y, get: tsBoundCircled.prototype.get_y });

/*
 */
tsBoundCircled.prototype['expand'] = tsBoundCircled.prototype.expand = function(v) {
	if(v instanceof tsVector2d) return _tsBoundCircled_expand1(this.self, v.self);
	if(v instanceof tsBoundCircled) return _tsBoundCircled_expand(this.self, v.self);
	throw 'invalid BoundCircled.expand() arguments';
};
tsBoundCircled.prototype['expandRadius'] = tsBoundCircled.prototype.expandRadius = function(v) {
	if(v instanceof tsVector2d) return _tsBoundCircled_expandRadius1(this.self, v.self);
	if(v instanceof tsBoundCircled) return _tsBoundCircled_expandRadius(this.self, v.self);
	throw 'invalid BoundCircled.expandRadius() arguments';
};

tsBoundCircled.prototype['inside'] = tsBoundCircled.prototype.inside = function(v) {
	if(v instanceof tsVector2d) return _tsBoundCircled_inside1(this.self, v.self);
	if(v instanceof tsBoundCircled) return _tsBoundCircled_inside(this.self, v.self);
	throw 'invalid BoundCircled.inside() arguments';
};

tsBoundCircled.prototype['distance'] = tsBoundCircled.prototype.distance = function(v) {
	if(v instanceof tsVector2d) return _tsBoundCircled_distance(this.self, v.self);
	throw 'invalid BoundCircled.distance() arguments';
};

/*****************************************************************************\
 *
 * BoundBoxf
 *
\*****************************************************************************/

/*
 */
function tsBoundBoxf(min, max) {
	if(min instanceof tsBoundBoxf) return ts_bind(tsBoundBoxf, this, _tsBoundBoxf_copy(min.self));
	if(min instanceof tsBoundBoxd) return ts_bind(tsBoundBoxf, this, _tsBoundBoxf_new_bbd(min.self));
	if(min instanceof tsBoundSpheref) return ts_bind(tsBoundBoxf, this, _tsBoundBoxf_new_bs(min.self));
	if(min instanceof tsVector3f && max instanceof tsVector3f) return ts_bind(tsBoundBoxf, this, _tsBoundBoxf_new_mm(min.self, max.self));
	if(min === undefined) return ts_bind(tsBoundBoxf, this, _tsBoundBoxf_new());
	throw 'invalid BoundBoxf() arguments';
}
Module['BoundBoxf'] = tsBoundBoxf;
tsBoundBoxf.finalizer = new FinalizationRegistry((self) => { _tsBoundBoxf_delete(self); });
tsBoundBoxf.prototype = Object.create(tsBoundBoxf.prototype);
tsBoundBoxf.prototype.constructor = tsBoundBoxf;

tsBoundBoxf.prototype['toBytes'] = tsBoundBoxf.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 24); }
tsBoundBoxf.prototype['toArray'] = tsBoundBoxf.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 6); }
tsBoundBoxf.prototype['toString'] = tsBoundBoxf.prototype.toString = function() { return this.min + ' : ' + this.max; };

/*
 */
tsBoundBoxf.prototype['set_min'] = tsBoundBoxf.prototype.set_min = function(min) { _tsBoundBoxf_set_min(this.self, min.self); };
tsBoundBoxf.prototype['set_max'] = tsBoundBoxf.prototype.set_max = function(max) { _tsBoundBoxf_set_max(this.self, max.self); };
tsBoundBoxf.prototype['set_x0'] = tsBoundBoxf.prototype.set_x0 = function(x) { _tsBoundBoxf_set_x0(this.self, x); };
tsBoundBoxf.prototype['set_y0'] = tsBoundBoxf.prototype.set_y0 = function(y) { _tsBoundBoxf_set_y0(this.self, y); };
tsBoundBoxf.prototype['set_z0'] = tsBoundBoxf.prototype.set_z0 = function(z) { _tsBoundBoxf_set_z0(this.self, z); };
tsBoundBoxf.prototype['set_x1'] = tsBoundBoxf.prototype.set_x1 = function(x) { _tsBoundBoxf_set_x1(this.self, x); };
tsBoundBoxf.prototype['set_y1'] = tsBoundBoxf.prototype.set_y1 = function(y) { _tsBoundBoxf_set_y1(this.self, y); };
tsBoundBoxf.prototype['set_z1'] = tsBoundBoxf.prototype.set_z1 = function(z) { _tsBoundBoxf_set_z1(this.self, z); };

tsBoundBoxf.prototype['get_min'] = tsBoundBoxf.prototype.get_min = function() { return ts_new(tsVector3f, _tsBoundBoxf_get_min(this.self)); };
tsBoundBoxf.prototype['get_max'] = tsBoundBoxf.prototype.get_max = function() { return ts_new(tsVector3f, _tsBoundBoxf_get_max(this.self)); };
tsBoundBoxf.prototype['get_x0'] = tsBoundBoxf.prototype.get_x0 = function() { return _tsBoundBoxf_get_x0(this.self); };
tsBoundBoxf.prototype['get_y0'] = tsBoundBoxf.prototype.get_y0 = function() { return _tsBoundBoxf_get_y0(this.self); };
tsBoundBoxf.prototype['get_z0'] = tsBoundBoxf.prototype.get_z0 = function() { return _tsBoundBoxf_get_z0(this.self); };
tsBoundBoxf.prototype['get_x1'] = tsBoundBoxf.prototype.get_x1 = function() { return _tsBoundBoxf_get_x1(this.self); };
tsBoundBoxf.prototype['get_y1'] = tsBoundBoxf.prototype.get_y1 = function() { return _tsBoundBoxf_get_y1(this.self); };
tsBoundBoxf.prototype['get_z1'] = tsBoundBoxf.prototype.get_z1 = function() { return _tsBoundBoxf_get_z1(this.self); };

Object.defineProperty(tsBoundBoxf.prototype, 'min', { set: tsBoundBoxf.prototype.set_min, get: tsBoundBoxf.prototype.get_min });
Object.defineProperty(tsBoundBoxf.prototype, 'max', { set: tsBoundBoxf.prototype.set_max, get: tsBoundBoxf.prototype.get_max });
Object.defineProperty(tsBoundBoxf.prototype, 'x0', { set: tsBoundBoxf.prototype.set_x0, get: tsBoundBoxf.prototype.get_x0 });
Object.defineProperty(tsBoundBoxf.prototype, 'y0', { set: tsBoundBoxf.prototype.set_y0, get: tsBoundBoxf.prototype.get_y0 });
Object.defineProperty(tsBoundBoxf.prototype, 'z0', { set: tsBoundBoxf.prototype.set_z0, get: tsBoundBoxf.prototype.get_z0 });
Object.defineProperty(tsBoundBoxf.prototype, 'x1', { set: tsBoundBoxf.prototype.set_x1, get: tsBoundBoxf.prototype.get_x1 });
Object.defineProperty(tsBoundBoxf.prototype, 'y1', { set: tsBoundBoxf.prototype.set_y1, get: tsBoundBoxf.prototype.get_y1 });
Object.defineProperty(tsBoundBoxf.prototype, 'z1', { set: tsBoundBoxf.prototype.set_z1, get: tsBoundBoxf.prototype.get_z1 });

/*
 */
tsBoundBoxf.prototype['expand'] = tsBoundBoxf.prototype.expand = function(v) {
	if(v instanceof tsVector3f) return _tsBoundBoxf_expand1(this.self, v.self);
	if(v instanceof tsBoundBoxf) return _tsBoundBoxf_expand(this.self, v.self);
	throw 'invalid BoundBoxf.expand() arguments';
};

tsBoundBoxf.prototype['inside'] = tsBoundBoxf.prototype.inside = function(v) {
	if(v instanceof tsVector3f) return _tsBoundBoxf_inside1(this.self, v.self);
	if(v instanceof tsBoundBoxf) return _tsBoundBoxf_inside(this.self, v.self);
	throw 'invalid BoundBoxf.inside() arguments';
};

tsBoundBoxf.prototype['distance'] = tsBoundBoxf.prototype.distance = function(v) {
	if(v instanceof tsVector3f) return _tsBoundBoxf_distance(this.self, v.self);
	throw 'invalid BoundBoxf.distance() arguments';
};

/*****************************************************************************\
 *
 * BoundBoxd
 *
\*****************************************************************************/

/*
 */
function tsBoundBoxd(min, max) {
	if(min instanceof tsBoundBoxd) return ts_bind(tsBoundBoxd, this, _tsBoundBoxd_copy(min.self));
	if(min instanceof tsBoundBoxf) return ts_bind(tsBoundBoxd, this, _tsBoundBoxd_new_bbf(min.self));
	if(min instanceof tsBoundSphered) return ts_bind(tsBoundBoxd, this, _tsBoundBoxd_new_bs(min.self));
	if(min instanceof tsVector3d && max instanceof tsVector3d) return ts_bind(tsBoundBoxd, this, _tsBoundBoxd_new_mm(min.self, max.self));
	if(min === undefined) return ts_bind(tsBoundBoxd, this, _tsBoundBoxd_new());
	throw 'invalid BoundBoxd() arguments';
}
Module['BoundBoxd'] = tsBoundBoxd;
tsBoundBoxd.finalizer = new FinalizationRegistry((self) => { _tsBoundBoxd_delete(self); });
tsBoundBoxd.prototype = Object.create(tsBoundBoxd.prototype);
tsBoundBoxd.prototype.constructor = tsBoundBoxd;

tsBoundBoxd.prototype['toBytes'] = tsBoundBoxd.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 48); }
tsBoundBoxd.prototype['toArray'] = tsBoundBoxd.prototype.getArray = function() { return new Float64Array(HEAPF64.buffer, this.self, 6); }
tsBoundBoxd.prototype['toString'] = tsBoundBoxd.prototype.toString = function() { return this.min + ' : ' + this.max; };

/*
 */
tsBoundBoxd.prototype['set_min'] = tsBoundBoxd.prototype.set_min = function(min) { _tsBoundBoxd_set_min(this.self, min.self); };
tsBoundBoxd.prototype['set_max'] = tsBoundBoxd.prototype.set_max = function(max) { _tsBoundBoxd_set_max(this.self, max.self); };
tsBoundBoxd.prototype['set_x0'] = tsBoundBoxd.prototype.set_x0 = function(x) { _tsBoundBoxd_set_x0(this.self, x); };
tsBoundBoxd.prototype['set_y0'] = tsBoundBoxd.prototype.set_y0 = function(y) { _tsBoundBoxd_set_y0(this.self, y); };
tsBoundBoxd.prototype['set_z0'] = tsBoundBoxd.prototype.set_z0 = function(z) { _tsBoundBoxd_set_z0(this.self, z); };
tsBoundBoxd.prototype['set_x1'] = tsBoundBoxd.prototype.set_x1 = function(x) { _tsBoundBoxd_set_x1(this.self, x); };
tsBoundBoxd.prototype['set_y1'] = tsBoundBoxd.prototype.set_y1 = function(y) { _tsBoundBoxd_set_y1(this.self, y); };
tsBoundBoxd.prototype['set_z1'] = tsBoundBoxd.prototype.set_z1 = function(z) { _tsBoundBoxd_set_z1(this.self, z); };

tsBoundBoxd.prototype['get_min'] = tsBoundBoxd.prototype.get_min = function() { return ts_new(tsVector3d, _tsBoundBoxd_get_min(this.self)); };
tsBoundBoxd.prototype['get_max'] = tsBoundBoxd.prototype.get_max = function() { return ts_new(tsVector3d, _tsBoundBoxd_get_max(this.self)); };
tsBoundBoxd.prototype['get_x0'] = tsBoundBoxd.prototype.get_x0 = function() { return _tsBoundBoxd_get_x0(this.self); };
tsBoundBoxd.prototype['get_y0'] = tsBoundBoxd.prototype.get_y0 = function() { return _tsBoundBoxd_get_y0(this.self); };
tsBoundBoxd.prototype['get_z0'] = tsBoundBoxd.prototype.get_z0 = function() { return _tsBoundBoxd_get_z0(this.self); };
tsBoundBoxd.prototype['get_x1'] = tsBoundBoxd.prototype.get_x1 = function() { return _tsBoundBoxd_get_x1(this.self); };
tsBoundBoxd.prototype['get_y1'] = tsBoundBoxd.prototype.get_y1 = function() { return _tsBoundBoxd_get_y1(this.self); };
tsBoundBoxd.prototype['get_z1'] = tsBoundBoxd.prototype.get_z1 = function() { return _tsBoundBoxd_get_z1(this.self); };

Object.defineProperty(tsBoundBoxd.prototype, 'min', { set: tsBoundBoxd.prototype.set_min, get: tsBoundBoxd.prototype.get_min });
Object.defineProperty(tsBoundBoxd.prototype, 'max', { set: tsBoundBoxd.prototype.set_max, get: tsBoundBoxd.prototype.get_max });
Object.defineProperty(tsBoundBoxd.prototype, 'x0', { set: tsBoundBoxd.prototype.set_x0, get: tsBoundBoxd.prototype.get_x0 });
Object.defineProperty(tsBoundBoxd.prototype, 'y0', { set: tsBoundBoxd.prototype.set_y0, get: tsBoundBoxd.prototype.get_y0 });
Object.defineProperty(tsBoundBoxd.prototype, 'z0', { set: tsBoundBoxd.prototype.set_z0, get: tsBoundBoxd.prototype.get_z0 });
Object.defineProperty(tsBoundBoxd.prototype, 'x1', { set: tsBoundBoxd.prototype.set_x1, get: tsBoundBoxd.prototype.get_x1 });
Object.defineProperty(tsBoundBoxd.prototype, 'y1', { set: tsBoundBoxd.prototype.set_y1, get: tsBoundBoxd.prototype.get_y1 });
Object.defineProperty(tsBoundBoxd.prototype, 'z1', { set: tsBoundBoxd.prototype.set_z1, get: tsBoundBoxd.prototype.get_z1 });

/*
 */
tsBoundBoxd.prototype['expand'] = tsBoundBoxd.prototype.expand = function(v) {
	if(v instanceof tsVector3d) return _tsBoundBoxd_expand1(this.self, v.self);
	if(v instanceof tsBoundBoxd) return _tsBoundBoxd_expand(this.self, v.self);
	throw 'invalid BoundBoxd.expand() arguments';
};

tsBoundBoxd.prototype['inside'] = tsBoundBoxd.prototype.inside = function(v) {
	if(v instanceof tsVector3d) return _tsBoundBoxd_inside1(this.self, v.self);
	if(v instanceof tsBoundBoxd) return _tsBoundBoxd_inside(this.self, v.self);
	throw 'invalid BoundBoxd.inside() arguments';
};

tsBoundBoxd.prototype['distance'] = tsBoundBoxd.prototype.distance = function(v) {
	if(v instanceof tsVector3d) return _tsBoundBoxd_distance(this.self, v.self);
	throw 'invalid BoundBoxd.distance() arguments';
};

/*****************************************************************************\
 *
 * BoundSpheref
 *
\*****************************************************************************/

/*
 */
function tsBoundSpheref(center, radius) {
	if(center instanceof tsBoundSpheref) return ts_bind(tsBoundSpheref, this, _tsBoundSpheref_copy(center.self));
	if(center instanceof tsBoundSphered) return ts_bind(tsBoundSpheref, this, _tsBoundSpheref_new_bsd(center.self));
	if(center instanceof tsBoundBoxf) return ts_bind(tsBoundSpheref, this, _tsBoundSpheref_new_bb(center.self));
	if(center instanceof tsVector3f && max !== undefined) return ts_bind(tsBoundSpheref, this, _tsBoundSpheref_new_cr(center.self, radius));
	if(center === undefined) return ts_bind(tsBoundSpheref, this, _tsBoundSpheref_new());
	throw 'invalid BoundSpheref() arguments';
}
Module['BoundSpheref'] = tsBoundSpheref;
tsBoundSpheref.finalizer = new FinalizationRegistry((self) => { _tsBoundSpheref_delete(self); });
tsBoundSpheref.prototype = Object.create(tsBoundSpheref.prototype);
tsBoundSpheref.prototype.constructor = tsBoundSpheref;

tsBoundSpheref.prototype['toBytes'] = tsBoundSpheref.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 16); }
tsBoundSpheref.prototype['toArray'] = tsBoundSpheref.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 4); }
tsBoundSpheref.prototype['toString'] = tsBoundSpheref.prototype.toString = function() { return this.center + ' : ' + this.radius; };

/*
 */
tsBoundSpheref.prototype['set_center'] = tsBoundSpheref.prototype.set_center = function(center) { _tsBoundSpheref_set_center(this.self, center.self); };
tsBoundSpheref.prototype['set_radius'] = tsBoundSpheref.prototype.set_radius = function(radius) { _tsBoundSpheref_set_radius(this.self, radius); };
tsBoundSpheref.prototype['set_x'] = tsBoundSpheref.prototype.set_x = function(x) { _tsBoundSpheref_set_x(this.self, x); };
tsBoundSpheref.prototype['set_y'] = tsBoundSpheref.prototype.set_y = function(y) { _tsBoundSpheref_set_y(this.self, y); };
tsBoundSpheref.prototype['set_z'] = tsBoundSpheref.prototype.set_z = function(z) { _tsBoundSpheref_set_z(this.self, z); };

tsBoundSpheref.prototype['get_center'] = tsBoundSpheref.prototype.get_center = function() { return ts_new(tsVector3f, _tsBoundSpheref_get_center(this.self)); };
tsBoundSpheref.prototype['get_radius'] = tsBoundSpheref.prototype.get_radius = function() { return _tsBoundSpheref_get_radius(this.self); };
tsBoundSpheref.prototype['get_x'] = tsBoundSpheref.prototype.get_x = function() { return _tsBoundSpheref_get_x(this.self); };
tsBoundSpheref.prototype['get_y'] = tsBoundSpheref.prototype.get_y = function() { return _tsBoundSpheref_get_y(this.self); };
tsBoundSpheref.prototype['get_z'] = tsBoundSpheref.prototype.get_z = function() { return _tsBoundSpheref_get_z(this.self); };

Object.defineProperty(tsBoundSpheref.prototype, 'center', { set: tsBoundSpheref.prototype.set_center, get: tsBoundSpheref.prototype.get_center });
Object.defineProperty(tsBoundSpheref.prototype, 'radius', { set: tsBoundSpheref.prototype.set_radius, get: tsBoundSpheref.prototype.get_radius });
Object.defineProperty(tsBoundSpheref.prototype, 'x', { set: tsBoundSpheref.prototype.set_x, get: tsBoundSpheref.prototype.get_x });
Object.defineProperty(tsBoundSpheref.prototype, 'y', { set: tsBoundSpheref.prototype.set_y, get: tsBoundSpheref.prototype.get_y });
Object.defineProperty(tsBoundSpheref.prototype, 'z', { set: tsBoundSpheref.prototype.set_z, get: tsBoundSpheref.prototype.get_z });

/*
 */
tsBoundSpheref.prototype['expand'] = tsBoundSpheref.prototype.expand = function(v) {
	if(v instanceof tsVector3f) return _tsBoundSpheref_expand1(this.self, v.self);
	if(v instanceof tsBoundSpheref) return _tsBoundSpheref_expand(this.self, v.self);
	throw 'invalid BoundSpheref.expand() arguments';
};
tsBoundSpheref.prototype['expandRadius'] = tsBoundSpheref.prototype.expandRadius = function(v) {
	if(v instanceof tsVector3f) return _tsBoundSpheref_expandRadius1(this.self, v.self);
	if(v instanceof tsBoundSpheref) return _tsBoundSpheref_expandRadius(this.self, v.self);
	throw 'invalid BoundSpheref.expandRadius() arguments';
};

tsBoundSpheref.prototype['inside'] = tsBoundSpheref.prototype.inside = function(v) {
	if(v instanceof tsVector3f) return _tsBoundSpheref_inside1(this.self, v.self);
	if(v instanceof tsBoundSpheref) return _tsBoundSpheref_inside(this.self, v.self);
	throw 'invalid BoundSpheref.inside() arguments';
};

tsBoundSpheref.prototype['distance'] = tsBoundSpheref.prototype.distance = function(v) {
	if(v instanceof tsVector3f) return _tsBoundSpheref_distance(this.self, v.self);
	throw 'invalid BoundSpheref.distance() arguments';
};

/*****************************************************************************\
 *
 * BoundSpheref
 *
\*****************************************************************************/

/*
 */
function tsBoundSphered(center, radius) {
	if(center instanceof tsBoundSphered) return ts_bind(tsBoundSphered, this, _tsBoundSphered_copy(center.self));
	if(center instanceof tsBoundSpheref) return ts_bind(tsBoundSphered, this, _tsBoundSphered_new_bsf(center.self));
	if(center instanceof tsBoundBoxd) return ts_bind(tsBoundSphered, this, _tsBoundSphered_new_bb(center.self));
	if(center instanceof tsVector3d && max !== undefined) return ts_bind(tsBoundSphered, this, _tsBoundSphered_new_cr(center.self, radius));
	if(center === undefined) return ts_bind(tsBoundSphered, this, _tsBoundSphered_new());
	throw 'invalid BoundSphered() arguments';
}
Module['BoundSphered'] = tsBoundSphered;
tsBoundSphered.finalizer = new FinalizationRegistry((self) => { _tsBoundSphered_delete(self); });
tsBoundSphered.prototype = Object.create(tsBoundSphered.prototype);
tsBoundSphered.prototype.constructor = tsBoundSphered;

tsBoundSphered.prototype['toBytes'] = tsBoundSphered.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 16); }
tsBoundSphered.prototype['toArray'] = tsBoundSphered.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 4); }
tsBoundSphered.prototype['toString'] = tsBoundSphered.prototype.toString = function() { return this.center + ' : ' + this.radius; };

/*
 */
tsBoundSphered.prototype['set_center'] = tsBoundSphered.prototype.set_center = function(center) { _tsBoundSphered_set_center(this.self, center.self); };
tsBoundSphered.prototype['set_radius'] = tsBoundSphered.prototype.set_radius = function(radius) { _tsBoundSphered_set_radius(this.self, radius); };
tsBoundSphered.prototype['set_x'] = tsBoundSphered.prototype.set_x = function(x) { _tsBoundSphered_set_x(this.self, x); };
tsBoundSphered.prototype['set_y'] = tsBoundSphered.prototype.set_y = function(y) { _tsBoundSphered_set_y(this.self, y); };
tsBoundSphered.prototype['set_z'] = tsBoundSphered.prototype.set_z = function(z) { _tsBoundSphered_set_z(this.self, z); };

tsBoundSphered.prototype['get_center'] = tsBoundSphered.prototype.get_center = function() { return ts_new(tsVector3d, _tsBoundSphered_get_center(this.self)); };
tsBoundSphered.prototype['get_radius'] = tsBoundSphered.prototype.get_radius = function() { return _tsBoundSphered_get_radius(this.self); };
tsBoundSphered.prototype['get_x'] = tsBoundSphered.prototype.get_x = function() { return _tsBoundSphered_get_x(this.self); };
tsBoundSphered.prototype['get_y'] = tsBoundSphered.prototype.get_y = function() { return _tsBoundSphered_get_y(this.self); };
tsBoundSphered.prototype['get_z'] = tsBoundSphered.prototype.get_z = function() { return _tsBoundSphered_get_z(this.self); };

Object.defineProperty(tsBoundSphered.prototype, 'center', { set: tsBoundSphered.prototype.set_center, get: tsBoundSphered.prototype.get_center });
Object.defineProperty(tsBoundSphered.prototype, 'radius', { set: tsBoundSphered.prototype.set_radius, get: tsBoundSphered.prototype.get_radius });
Object.defineProperty(tsBoundSphered.prototype, 'x', { set: tsBoundSphered.prototype.set_x, get: tsBoundSphered.prototype.get_x });
Object.defineProperty(tsBoundSphered.prototype, 'y', { set: tsBoundSphered.prototype.set_y, get: tsBoundSphered.prototype.get_y });
Object.defineProperty(tsBoundSphered.prototype, 'z', { set: tsBoundSphered.prototype.set_z, get: tsBoundSphered.prototype.get_z });

/*
 */
tsBoundSphered.prototype['expand'] = tsBoundSphered.prototype.expand = function(v) {
	if(v instanceof tsVector3d) return _tsBoundSphered_expand1(this.self, v.self);
	if(v instanceof tsBoundSphered) return _tsBoundSphered_expand(this.self, v.self);
	throw 'invalid BoundSphered.expand() arguments';
};
tsBoundSphered.prototype['expandRadius'] = tsBoundSphered.prototype.expandRadius = function(v) {
	if(v instanceof tsVector3d) return _tsBoundSphered_expandRadius1(this.self, v.self);
	if(v instanceof tsBoundSphered) return _tsBoundSphered_expandRadius(this.self, v.self);
	throw 'invalid BoundSphered.expandRadius() arguments';
};

tsBoundSphered.prototype['inside'] = tsBoundSphered.prototype.inside = function(v) {
	if(v instanceof tsVector3d) return _tsBoundSphered_inside1(this.self, v.self);
	if(v instanceof tsBoundSphered) return _tsBoundSphered_inside(this.self, v.self);
	throw 'invalid BoundSphered.inside() arguments';
};

tsBoundSphered.prototype['distance'] = tsBoundSphered.prototype.distance = function(v) {
	if(v instanceof tsVector3d) return _tsBoundSphered_distance(this.self, v.self);
	throw 'invalid BoundSphered.distance() arguments';
};

/*****************************************************************************\
 *
 * BoundFrustumf
 *
\*****************************************************************************/

/*
 */
function tsBoundFrustumf(projection, modelview, aspect) {
	if(projection instanceof tsBoundFrustumf) return ts_bind(tsBoundFrustumf, this, _tsBoundFrustumf_copy(projection.self));
	if(projection instanceof tsBoundFrustumd) return ts_bind(tsBoundFrustumf, this, _tsBoundFrustumf_new_bfd(projection.self));
	if(projection instanceof tsMatrix4x4f && modelview instanceof tsMatrix4x4f && aspect !== undefined) return ts_bind(tsBoundFrustumf, this, _tsBoundFrustumf_new_pma(projection.self, modelview.self, aspect));
	if(projection instanceof tsMatrix4x4f && modelview instanceof tsMatrix4x4f) return ts_bind(tsBoundFrustumf, this, _tsBoundFrustumf_new_pma(projection.self, modelview.self, 1.0));
	if(projection === undefined) return ts_bind(tsBoundFrustumf, this, _tsBoundFrustumf_new());
	throw 'invalid BoundFrustumf() arguments';
}
Module['BoundFrustumf'] = tsBoundFrustumf;
tsBoundFrustumf.finalizer = new FinalizationRegistry((self) => { _tsBoundFrustumf_delete(self); });
tsBoundFrustumf.prototype = Object.create(tsBoundFrustumf.prototype);
tsBoundFrustumf.prototype.constructor = tsBoundFrustumf;

/*
 */
tsBoundFrustumf.prototype['set'] = tsBoundFrustumf.prototype.set = function(projection, modelview, aspect) {
	if(projection instanceof tsMatrix4x4f && modelview instanceof tsMatrix4x4f && aspect !== undefined) return _tsBoundFrustumf_set(projection.self, modelview.self, aspect);
	if(projection instanceof tsMatrix4x4f && modelview instanceof tsMatrix4x4f) return _tsBoundFrustumf_set(projection.self, modelview.self, 1.0);
	throw 'invalid BoundFrustumf.set() arguments';
};

tsBoundFrustumf.prototype['inside'] = tsBoundFrustumf.prototype.inside = function(b) {
	if(b instanceof tsBoundBoxf) return _tsBoundFrustumf_inside_bb(this.self, b.self);
	if(b instanceof tsBoundSpheref) return _tsBoundFrustumf_inside_bs(this.self, b.self);
	throw 'invalid BoundFrustumf.inside() arguments';
};

/*****************************************************************************\
 *
 * BoundFrustumd
 *
\*****************************************************************************/

/*
 */
function tsBoundFrustumd(projection, modelview, aspect) {
	if(projection instanceof tsBoundFrustumd) return ts_bind(tsBoundFrustumd, this, _tsBoundFrustumd_copy(projection.self));
	if(projection instanceof tsBoundFrustumf) return ts_bind(tsBoundFrustumd, this, _tsBoundFrustumd_new_bff(projection.self));
	if(projection instanceof tsMatrix4x4d && modelview instanceof tsMatrix4x4d && aspect !== undefined) return ts_bind(tsBoundFrustumd, this, _tsBoundFrustumd_new_pma(projection.self, modelview.self, aspect));
	if(projection instanceof tsMatrix4x4d && modelview instanceof tsMatrix4x4d) return ts_bind(tsBoundFrustumd, this, _tsBoundFrustumd_new_pma(projection.self, modelview.self, 1.0));
	if(projection === undefined) return ts_bind(tsBoundFrustumd, this, _tsBoundFrustumd_new());
	throw 'invalid BoundFrustumd() arguments';
}
Module['BoundFrustumd'] = tsBoundFrustumd;
tsBoundFrustumd.finalizer = new FinalizationRegistry((self) => { _tsBoundFrustumd_delete(self); });
tsBoundFrustumd.prototype = Object.create(tsBoundFrustumd.prototype);
tsBoundFrustumd.prototype.constructor = tsBoundFrustumd;

/*
 */
tsBoundFrustumd.prototype['set'] = tsBoundFrustumd.prototype.set = function(projection, modelview, aspect) {
	if(projection instanceof tsMatrix4x4d && modelview instanceof tsMatrix4x4d && aspect !== undefined) return _tsBoundFrustumd_set(projection.self, modelview.self, aspect);
	if(projection instanceof tsMatrix4x4d && modelview instanceof tsMatrix4x4d) return _tsBoundFrustumd_set(projection.self, modelview.self, 1.0);
	throw 'invalid BoundFrustumd.set() arguments';
};

tsBoundFrustumd.prototype['inside'] = tsBoundFrustumd.prototype.inside = function(b) {
	if(b instanceof tsBoundBoxd) return _tsBoundFrustumd_inside_bb(this.self, b.self);
	if(b instanceof tsBoundSphered) return _tsBoundFrustumd_inside_bs(this.self, b.self);
	throw 'invalid BoundFrustumd.inside() arguments';
};

/*****************************************************************************\
 *
 * Origin
 *
\*****************************************************************************/

/*
 */
function tsOrigin(x, y, z) {
	if(x instanceof tsOrigin) return ts_bind(tsOrigin, this, _tsOrigin_copy(x.self));
	if(x !== undefined && y !== undefined && z !== undefined) return ts_bind(tsOrigin, this, _tsOrigin_new_xyz(x, y, z));
	if(x !== undefined && y !== undefined) return ts_bind(tsOrigin, this, _tsOrigin_new_xy(x, y));
	if(x === undefined) return ts_bind(tsOrigin, this, _tsOrigin_new());
	throw 'invalid Origin() arguments';
}
Module['Origin'] = tsOrigin;
tsOrigin.finalizer = new FinalizationRegistry((self) => { _tsOrigin_delete(self); });
tsOrigin.prototype = Object.create(tsOrigin.prototype);
tsOrigin.prototype.constructor = tsOrigin;

tsOrigin.prototype['toString'] = tsOrigin.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' ' + this.z + ')'; };

/*
 */
tsOrigin.prototype['set_x'] = tsOrigin.prototype.set_x = function(x) { _tsOrigin_set_x(this.self, x); };
tsOrigin.prototype['set_y'] = tsOrigin.prototype.set_y = function(y) { _tsOrigin_set_y(this.self, y); };
tsOrigin.prototype['set_z'] = tsOrigin.prototype.set_z = function(z) { _tsOrigin_set_z(this.self, z); };

tsOrigin.prototype['get_x'] = tsOrigin.prototype.get_x = function() { return _tsOrigin_get_x(this.self); };
tsOrigin.prototype['get_y'] = tsOrigin.prototype.get_y = function() { return _tsOrigin_get_y(this.self); };
tsOrigin.prototype['get_z'] = tsOrigin.prototype.get_z = function() { return _tsOrigin_get_z(this.self); };

Object.defineProperty(tsOrigin.prototype, 'x', { set: tsOrigin.prototype.set_x, get: tsOrigin.prototype.get_x });
Object.defineProperty(tsOrigin.prototype, 'y', { set: tsOrigin.prototype.set_y, get: tsOrigin.prototype.get_y });
Object.defineProperty(tsOrigin.prototype, 'z', { set: tsOrigin.prototype.set_z, get: tsOrigin.prototype.get_z });

/*****************************************************************************\
 *
 * Size
 *
\*****************************************************************************/

/*
 */
function tsSize(width, height, depth) {
	if(width instanceof tsSize) return ts_bind(tsSize, this, _tsSize_copy(width.self));
	if(width !== undefined && height !== undefined && depth !== undefined) return ts_bind(tsSize, this, _tsSize_new_whd(width, height, depth));
	if(width !== undefined && height !== undefined) return ts_bind(tsSize, this, _tsSize_new_wh(width, height));
	if(width === undefined) return ts_bind(tsSize, this, _tsSize_new());
	throw 'invalid Size() arguments';
}
Module['Size'] = tsSize;
tsSize.finalizer = new FinalizationRegistry((self) => { _tsSize_delete(self); });
tsSize.prototype = Object.create(tsSize.prototype);
tsSize.prototype.constructor = tsSize;

tsSize.prototype['toString'] = tsSize.prototype.toString = function() { return '(' + this.width + ' ' + this.height + ' ' + this.depth + ')'; };

/*
 */
tsSize.prototype['set_width'] = tsSize.prototype.set_width = function(width) { _tsSize_set_width(this.self, width); };
tsSize.prototype['set_height'] = tsSize.prototype.set_height = function(height) { _tsSize_set_height(this.self, height); };
tsSize.prototype['set_depth'] = tsSize.prototype.set_depth = function(depth) { _tsSize_set_depth(this.self, depth); };

tsSize.prototype['get_width'] = tsSize.prototype.get_width = function() { return _tsSize_get_width(this.self); };
tsSize.prototype['get_height'] = tsSize.prototype.get_height = function() { return _tsSize_get_height(this.self); };
tsSize.prototype['get_depth'] = tsSize.prototype.get_depth = function() { return _tsSize_get_depth(this.self); };

Object.defineProperty(tsSize.prototype, 'width', { set: tsSize.prototype.set_width, get: tsSize.prototype.get_width });
Object.defineProperty(tsSize.prototype, 'height', { set: tsSize.prototype.set_height, get: tsSize.prototype.get_height });
Object.defineProperty(tsSize.prototype, 'depth', { set: tsSize.prototype.set_depth, get: tsSize.prototype.get_depth });

/*****************************************************************************\
 *
 * Region
 *
\*****************************************************************************/

/*
 */
function tsRegion(x, y, z, width, height, depth) {
	if(x instanceof tsRegion) return ts_bind(tsRegion, this, _tsRegion_copy(x.self));
	if(x instanceof tsOrigin && y instanceof tsSize) return ts_bind(tsRegion, this, _tsRegion_new_os(x.self, y.self));
	if(x !== undefined && y !== undefined && z !== undefined && width !== undefined && height !== undefined && depth !== undefined) return ts_bind(tsRegion, this, _tsRegion_new_xyzwhz(x, y, z, width, height, depth));
	if(x !== undefined && y !== undefined && z !== undefined && width !== undefined) return ts_bind(tsRegion, this, _tsRegion_new_xywh(x, y, z, width));
	if(x === undefined) return ts_bind(tsRegion, this, _tsRegion_new());
	throw 'invalid Region() arguments';
}
Module['Region'] = tsRegion;
tsRegion.finalizer = new FinalizationRegistry((self) => { _tsRegion_delete(self); });
tsRegion.prototype = Object.create(tsRegion.prototype);
tsRegion.prototype.constructor = tsRegion;

tsRegion.prototype['toString'] = tsRegion.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' ' + this.z + ' : ' + this.width + ' ' + this.height + ' ' + this.depth + ')'; };

/*
 */
tsRegion.prototype['set_x'] = tsRegion.prototype.set_x = function(x) { _tsRegion_set_x(this.self, x); };
tsRegion.prototype['set_y'] = tsRegion.prototype.set_y = function(y) { _tsRegion_set_y(this.self, y); };
tsRegion.prototype['set_z'] = tsRegion.prototype.set_z = function(z) { _tsRegion_set_z(this.self, z); };
tsRegion.prototype['set_width'] = tsRegion.prototype.set_width = function(width) { _tsRegion_set_width(this.self, width); };
tsRegion.prototype['set_height'] = tsRegion.prototype.set_height = function(height) { _tsRegion_set_height(this.self, height); };
tsRegion.prototype['set_depth'] = tsRegion.prototype.set_depth = function(depth) { _tsRegion_set_depth(this.self, depth); };

tsRegion.prototype['get_x'] = tsRegion.prototype.get_x = function() { return _tsRegion_get_x(this.self); };
tsRegion.prototype['get_y'] = tsRegion.prototype.get_y = function() { return _tsRegion_get_y(this.self); };
tsRegion.prototype['get_z'] = tsRegion.prototype.get_z = function() { return _tsRegion_get_z(this.self); };
tsRegion.prototype['get_width'] = tsRegion.prototype.get_width = function() { return _tsRegion_get_width(this.self); };
tsRegion.prototype['get_height'] = tsRegion.prototype.get_height = function() { return _tsRegion_get_height(this.self); };
tsRegion.prototype['get_depth'] = tsRegion.prototype.get_depth = function() { return _tsRegion_get_depth(this.self); };

Object.defineProperty(tsRegion.prototype, 'x', { set: tsRegion.prototype.set_x, get: tsRegion.prototype.get_x });
Object.defineProperty(tsRegion.prototype, 'y', { set: tsRegion.prototype.set_y, get: tsRegion.prototype.get_y });
Object.defineProperty(tsRegion.prototype, 'z', { set: tsRegion.prototype.set_z, get: tsRegion.prototype.get_z });
Object.defineProperty(tsRegion.prototype, 'width', { set: tsRegion.prototype.set_width, get: tsRegion.prototype.get_width });
Object.defineProperty(tsRegion.prototype, 'height', { set: tsRegion.prototype.set_height, get: tsRegion.prototype.get_height });
Object.defineProperty(tsRegion.prototype, 'depth', { set: tsRegion.prototype.set_depth, get: tsRegion.prototype.get_depth });

/*****************************************************************************\
 *
 * Slice
 *
\*****************************************************************************/

/*
 */
function tsFace(index, size) {
	if(index === undefined) index = 0;
	if(size === undefined) size = 1;
	this.index = index;
	this.size = size;
}
Module['Face'] = tsFace;
tsFace.prototype = Object.create(tsFace.prototype);
tsFace.prototype.constructor = tsFace;

tsFace.prototype['toString'] = tsFace.prototype.toString = function() { return '(' + this.index + ' ' + this.size+ ')' };

/*
 */
function tsLayer(index, size) {
	if(index === undefined) index = 0;
	if(size === undefined) size = 1;
	this.index = index;
	this.size = size;
}
Module['Layer'] = tsLayer;
tsLayer.prototype = Object.create(tsLayer.prototype);
tsLayer.prototype.constructor = tsLayer;

tsLayer.prototype['toString'] = tsLayer.prototype.toString = function() { return '(' + this.index + ' ' + this.size+ ')' };

/*
 */
function tsMipmap(index, size) {
	if(index === undefined) index = 0;
	if(size === undefined) size = 1;
	this.index = index;
	this.size = size;
}
Module['Mipmap'] = tsMipmap;
tsMipmap.prototype = Object.create(tsMipmap.prototype);
tsMipmap.prototype.constructor = tsMipmap;

tsMipmap.prototype['toString'] = tsMipmap.prototype.toString = function() { return '(' + this.index + ' ' + this.size+ ')' };

/*
 */
function tsSlice(slice) {
	if(slice instanceof tsSlice) return ts_bind(tsSlice, this, _tsSlice_copy(slice.self));
	if(slice instanceof tsFace) return ts_bind(tsSlice, this, _tsSlice_new_f(slice.index, slice.size));
	if(slice instanceof tsLayer) return ts_bind(tsSlice, this, _tsSlice_new_l(slice.index, slice.size));
	if(slice instanceof tsMipmap) return ts_bind(tsSlice, this, _tsSlice_new_m(slice.index, slice.size));
	if(slice === undefined) return ts_bind(tsSlice, this, _tsSlice_new());
	throw 'invalid Slice() arguments';
}
Module['Slice'] = tsSlice;
tsSlice.finalizer = new FinalizationRegistry((self) => { _tsSlice_delete(self); });
tsSlice.prototype = Object.create(tsSlice.prototype);
tsSlice.prototype.constructor = tsSlice;

tsSlice.prototype['toString'] = tsSlice.prototype.toString = function() { return '(' + this.face + ' ' + this.faces + ') : (' + this.layer + ' ' + this.layers + ') : (' + this.mipmap + ' ' + this.mipmaps + ')'; };

/*
 */
tsSlice.prototype['set_face'] = tsSlice.prototype.set_face = function(face) { _tsSlice_set_face(this.self, face); };
tsSlice.prototype['set_faces'] = tsSlice.prototype.set_faces = function(faces) { _tsSlice_set_faces(this.self, faces); };
tsSlice.prototype['set_layer'] = tsSlice.prototype.set_layer = function(layer) { _tsSlice_set_layer(this.self, layer); };
tsSlice.prototype['set_layers'] = tsSlice.prototype.set_layers = function(layers) { _tsSlice_set_layers(this.self, layers); };
tsSlice.prototype['set_mipmap'] = tsSlice.prototype.set_mipmap = function(mipmap) { _tsSlice_set_mipmap(this.self, mipmap); };
tsSlice.prototype['set_mipmaps'] = tsSlice.prototype.set_mipmaps = function(mipmaps) { _tsSlice_set_mipmaps(this.self, mipmaps); };

tsSlice.prototype['get_face'] = tsSlice.prototype.get_face = function() { return _tsSlice_get_face(this.self); };
tsSlice.prototype['get_faces'] = tsSlice.prototype.get_faces = function() { return _tsSlice_get_faces(this.self); };
tsSlice.prototype['get_layer'] = tsSlice.prototype.get_layer = function() { return _tsSlice_get_layer(this.self); };
tsSlice.prototype['get_layers'] = tsSlice.prototype.get_layers = function() { return _tsSlice_get_layers(this.self); };
tsSlice.prototype['get_mipmap'] = tsSlice.prototype.get_mipmap = function() { return _tsSlice_get_mipmap(this.self); };
tsSlice.prototype['get_mipmaps'] = tsSlice.prototype.get_mipmaps = function() { return _tsSlice_get_mipmaps(this.self); };

Object.defineProperty(tsSlice.prototype, 'face', { set: tsSlice.prototype.set_face, get: tsSlice.prototype.get_face });
Object.defineProperty(tsSlice.prototype, 'faces', { set: tsSlice.prototype.set_faces, get: tsSlice.prototype.get_faces });
Object.defineProperty(tsSlice.prototype, 'layer', { set: tsSlice.prototype.set_layer, get: tsSlice.prototype.get_layer });
Object.defineProperty(tsSlice.prototype, 'layers', { set: tsSlice.prototype.set_layers, get: tsSlice.prototype.get_layers });
Object.defineProperty(tsSlice.prototype, 'mipmap', { set: tsSlice.prototype.set_mipmap, get: tsSlice.prototype.get_mipmap });
Object.defineProperty(tsSlice.prototype, 'mipmaps', { set: tsSlice.prototype.set_mipmaps, get: tsSlice.prototype.get_mipmaps });

/*****************************************************************************\
 *
 * Viewport
 *
\*****************************************************************************/

/*
 */
function tsViewport(x, y, width, height, znear, zfar) {
	if(x instanceof tsViewport) return ts_bind(tsViewport, this, _tsViewport_copy(x.self));
	if(x !== undefined && y !== undefined && width !== undefined && height !== undefined && znear !== undefined && zfar !== undefined) return ts_bind(tsViewport, this, _tsViewport_new_xywhnf(x, y, width, height, znear, zfar));
	if(x !== undefined && y !== undefined && width !== undefined && height !== undefined) return ts_bind(tsViewport, this, _tsViewport_new_xywh(x, y, width, height));
	if(x === undefined) return ts_bind(tsViewport, this, _tsViewport_new());
	throw 'invalid Viewport() arguments';
}
Module['Viewport'] = tsViewport;
tsViewport.finalizer = new FinalizationRegistry((self) => { _tsViewport_delete(self); });
tsViewport.prototype = Object.create(tsViewport.prototype);
tsViewport.prototype.constructor = tsViewport;

tsViewport.prototype['toString'] = tsViewport.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' : ' + this.width + ' ' + this.height + ' : ' + this.znear + ' : ' + this.zfar + ')'; };

/*
 */
tsViewport.prototype['set_x'] = tsViewport.prototype.set_x = function(x) { _tsViewport_set_x(this.self, x); };
tsViewport.prototype['set_y'] = tsViewport.prototype.set_y = function(y) { _tsViewport_set_y(this.self, y); };
tsViewport.prototype['set_width'] = tsViewport.prototype.set_width = function(width) { _tsViewport_set_width(this.self, width); };
tsViewport.prototype['set_height'] = tsViewport.prototype.set_height = function(height) { _tsViewport_set_height(this.self, height); };
tsViewport.prototype['set_znear'] = tsViewport.prototype.set_znear = function(znear) { _tsViewport_set_z(this.self, znear); };
tsViewport.prototype['set_zfar'] = tsViewport.prototype.set_zfar = function(zfar) { _tsViewport_set_z(this.self, zfar); };

tsViewport.prototype['get_x'] = tsViewport.prototype.get_x = function() { return _tsViewport_get_x(this.self); };
tsViewport.prototype['get_y'] = tsViewport.prototype.get_y = function() { return _tsViewport_get_y(this.self); };
tsViewport.prototype['get_width'] = tsViewport.prototype.get_width = function() { return _tsViewport_get_width(this.self); };
tsViewport.prototype['get_height'] = tsViewport.prototype.get_height = function() { return _tsViewport_get_height(this.self); };
tsViewport.prototype['get_znear'] = tsViewport.prototype.get_znear = function() { return _tsViewport_get_znear(this.self); };
tsViewport.prototype['get_zfar'] = tsViewport.prototype.get_zfar = function() { return _tsViewport_get_zfar(this.self); };

Object.defineProperty(tsViewport.prototype, 'x', { set: tsViewport.prototype.set_x, get: tsViewport.prototype.get_x });
Object.defineProperty(tsViewport.prototype, 'y', { set: tsViewport.prototype.set_y, get: tsViewport.prototype.get_y });
Object.defineProperty(tsViewport.prototype, 'width', { set: tsViewport.prototype.set_width, get: tsViewport.prototype.get_width });
Object.defineProperty(tsViewport.prototype, 'height', { set: tsViewport.prototype.set_height, get: tsViewport.prototype.get_height });
Object.defineProperty(tsViewport.prototype, 'znear', { set: tsViewport.prototype.set_znear, get: tsViewport.prototype.get_znear });
Object.defineProperty(tsViewport.prototype, 'zfar', { set: tsViewport.prototype.set_zfar, get: tsViewport.prototype.get_zfar });

/*****************************************************************************\
 *
 * Scissor
 *
\*****************************************************************************/

/*
 */
function tsScissor(x, y, width, height) {
	if(x instanceof tsScissor) return ts_bind(tsScissor, this, _tsScissor_copy(x.self));
	if(x !== undefined && y !== undefined && width !== undefined && height !== undefined) return ts_bind(tsScissor, this, _tsScissor_new_xywh(x, y, width, height));
	if(x === undefined) return ts_bind(tsScissor, this, _tsScissor_new());
	throw 'invalid Scissor() arguments';
}
Module['Scissor'] = tsScissor;
tsScissor.finalizer = new FinalizationRegistry((self) => { _tsScissor_delete(self); });
tsScissor.prototype = Object.create(tsScissor.prototype);
tsScissor.prototype.constructor = tsScissor;

tsScissor.prototype['toString'] = tsScissor.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' : ' + this.width + ' ' + this.height + ')'; };

/*
 */
tsScissor.prototype['set_x'] = tsScissor.prototype.set_x = function(x) { _tsScissor_set_x(this.self, x); };
tsScissor.prototype['set_y'] = tsScissor.prototype.set_y = function(y) { _tsScissor_set_y(this.self, y); };
tsScissor.prototype['set_width'] = tsScissor.prototype.set_width = function(width) { _tsScissor_set_width(this.self, width); };
tsScissor.prototype['set_height'] = tsScissor.prototype.set_height = function(height) { _tsScissor_set_height(this.self, height); };

tsScissor.prototype['get_x'] = tsScissor.prototype.get_x = function() { return _tsScissor_get_x(this.self); };
tsScissor.prototype['get_y'] = tsScissor.prototype.get_y = function() { return _tsScissor_get_y(this.self); };
tsScissor.prototype['get_width'] = tsScissor.prototype.get_width = function() { return _tsScissor_get_width(this.self); };
tsScissor.prototype['get_height'] = tsScissor.prototype.get_height = function() { return _tsScissor_get_height(this.self); };

Object.defineProperty(tsScissor.prototype, 'x', { set: tsScissor.prototype.set_x, get: tsScissor.prototype.get_x });
Object.defineProperty(tsScissor.prototype, 'y', { set: tsScissor.prototype.set_y, get: tsScissor.prototype.get_y });
Object.defineProperty(tsScissor.prototype, 'width', { set: tsScissor.prototype.set_width, get: tsScissor.prototype.get_width });
Object.defineProperty(tsScissor.prototype, 'height', { set: tsScissor.prototype.set_height, get: tsScissor.prototype.get_height });

/*****************************************************************************\
 *
 * Rect
 *
\*****************************************************************************/

/*
 */
function tsRect(left, right, bottom, top) {
	if(left instanceof tsRect) return ts_bind(tsRect, this, _tsRect_copy(left.self));
	if(left !== undefined && right !== undefined && bottom !== undefined && top !== undefined) return ts_bind(tsRect, this, _tsRect_new_lrbt(left, right, bottom, top));
	if(left === undefined) return ts_bind(tsRect, this, _tsRect_new());
	throw 'invalid Rect() arguments';
}
Module['Rect'] = tsRect;
tsRect.finalizer = new FinalizationRegistry((self) => { _tsRect_delete(self); });
tsRect.prototype = Object.create(tsRect.prototype);
tsRect.prototype.constructor = tsRect;

tsRect.prototype['toString'] = tsRect.prototype.toString = function() { return '(' + this.left + ' ' + this.right + ' : ' + this.bottom + ' ' + this.top + ')'; };

/*
 */
tsRect.prototype['set_left'] = tsRect.prototype.set_left = function(left) { _tsRect_set_left(this.self, left); };
tsRect.prototype['set_right'] = tsRect.prototype.set_right = function(right) { _tsRect_set_right(this.self, right); };
tsRect.prototype['set_bottom'] = tsRect.prototype.set_bottom = function(bottom) { _tsRect_set_bottom(this.self, bottom); };
tsRect.prototype['set_top'] = tsRect.prototype.set_top = function(top) { _tsRect_set_top(this.self, top); };

tsRect.prototype['get_left'] = tsRect.prototype.get_left = function() { return _tsRect_get_left(this.self); };
tsRect.prototype['get_right'] = tsRect.prototype.get_right = function() { return _tsRect_get_right(this.self); };
tsRect.prototype['get_bottom'] = tsRect.prototype.get_bottom = function() { return _tsRect_get_bottom(this.self); };
tsRect.prototype['get_top'] = tsRect.prototype.get_top = function() { return _tsRect_get_top(this.self); };

Object.defineProperty(tsRect.prototype, 'left', { set: tsRect.prototype.set_left, get: tsRect.prototype.get_left });
Object.defineProperty(tsRect.prototype, 'right', { set: tsRect.prototype.set_right, get: tsRect.prototype.get_right });
Object.defineProperty(tsRect.prototype, 'bottom', { set: tsRect.prototype.set_bottom, get: tsRect.prototype.get_bottom });
Object.defineProperty(tsRect.prototype, 'top', { set: tsRect.prototype.set_top, get: tsRect.prototype.get_top });

/*****************************************************************************\
 *
 * FontStyle
 *
\*****************************************************************************/

/*
 */
function tsFontStyle(style) {
	if(style instanceof tsFontStyle) return ts_bind(tsFontStyle, this, _tsFontStyle_copy(style.self));
	if(style === undefined) return ts_bind(tsFontStyle, this, _tsFontStyle_new());
	throw 'invalid FontStyle() arguments';
}
Module['FontStyle'] = tsFontStyle;
tsFontStyle.finalizer = new FinalizationRegistry((self) => { _tsFontStyle_delete(self); });
tsFontStyle.prototype = Object.create(tsFontStyle.prototype);
tsFontStyle.prototype.constructor = tsFontStyle;

tsFontStyle.prototype['toString'] = tsFontStyle.prototype.toString = function() { return '(' + this.size + ' ' + this.scale + ' ' + this.fixed + ' ' + this.kerning + ' : ' + this.spacing + ' ' + this.color + ' : ' + this.offset + ' ' + this.shadow + ')'; };

/*
 */
tsFontStyle.prototype['set_size'] = tsFontStyle.prototype.set_size = function(size) { _tsFontStyle_set_size(this.self, size); };
tsFontStyle.prototype['set_scale'] = tsFontStyle.prototype.set_scale = function(scale) { _tsFontStyle_set_scale(this.self, scale); };
tsFontStyle.prototype['set_fixed'] = tsFontStyle.prototype.set_fixed = function(fixed) { _tsFontStyle_set_fixed(this.self, fixed); };
tsFontStyle.prototype['set_kerning'] = tsFontStyle.prototype.set_kerning = function(kerning) { _tsFontStyle_set_kerning(this.self, kerning); };
tsFontStyle.prototype['set_spacing'] = tsFontStyle.prototype.set_spacing = function(spacing) { _tsFontStyle_set_spacing(this.self, spacing.self); };
tsFontStyle.prototype['set_color'] = tsFontStyle.prototype.set_color = function(color) { _tsFontStyle_set_color(this.self, color.self); };
tsFontStyle.prototype['set_offset'] = tsFontStyle.prototype.set_offset = function(offset) { _tsFontStyle_set_offset(this.self, offset.self); };
tsFontStyle.prototype['set_shadow'] = tsFontStyle.prototype.set_shadow = function(shadow) { _tsFontStyle_set_shadow(this.self, shadow.self); };

tsFontStyle.prototype['get_size'] = tsFontStyle.prototype.get_size = function() { return _tsFontStyle_get_size(this.self); };
tsFontStyle.prototype['get_scale'] = tsFontStyle.prototype.get_scale = function() { return _tsFontStyle_get_scale(this.self); };
tsFontStyle.prototype['get_fixed'] = tsFontStyle.prototype.get_fixed = function() { return _tsFontStyle_get_fixed(this.self); };
tsFontStyle.prototype['get_kerning'] = tsFontStyle.prototype.get_kerning = function() { return _tsFontStyle_get_kerning(this.self); };
tsFontStyle.prototype['get_spacing'] = tsFontStyle.prototype.get_spacing = function() { return ts_new(tsVector2f, _tsFontStyle_get_spacing(this.self)); };
tsFontStyle.prototype['get_color'] = tsFontStyle.prototype.get_color = function() { return ts_new(tsColor, _tsFontStyle_get_color(this.self)); };
tsFontStyle.prototype['get_offset'] = tsFontStyle.prototype.get_offset = function() { return ts_new(tsVector3f, _tsFontStyle_get_offset(this.self)); };
tsFontStyle.prototype['get_shadow'] = tsFontStyle.prototype.get_shadow = function() { return ts_new(tsColor, _tsFontStyle_get_shadow(this.self)); };

Object.defineProperty(tsFontStyle.prototype, 'size', { set: tsFontStyle.prototype.set_size, get: tsFontStyle.prototype.get_size });
Object.defineProperty(tsFontStyle.prototype, 'scale', { set: tsFontStyle.prototype.set_scale, get: tsFontStyle.prototype.get_scale });
Object.defineProperty(tsFontStyle.prototype, 'fixed', { set: tsFontStyle.prototype.set_fixed, get: tsFontStyle.prototype.get_fixed });
Object.defineProperty(tsFontStyle.prototype, 'kerning', { set: tsFontStyle.prototype.set_kerning, get: tsFontStyle.prototype.get_kerning });
Object.defineProperty(tsFontStyle.prototype, 'spacing', { set: tsFontStyle.prototype.set_spacing, get: tsFontStyle.prototype.get_spacing });
Object.defineProperty(tsFontStyle.prototype, 'color', { set: tsFontStyle.prototype.set_color, get: tsFontStyle.prototype.get_color });
Object.defineProperty(tsFontStyle.prototype, 'offset', { set: tsFontStyle.prototype.set_offset, get: tsFontStyle.prototype.get_offset });
Object.defineProperty(tsFontStyle.prototype, 'shadow', { set: tsFontStyle.prototype.set_shadow, get: tsFontStyle.prototype.get_shadow });

/*****************************************************************************\
 *
 * StrokeStyle
 *
\*****************************************************************************/

/*
 */
function tsStrokeStyle() {
	if(arguments.length == 3 && arguments[2] instanceof tsColor) return ts_bind(tsStrokeStyle, this, _tsStrokeStyle_new_woc(arguments[0], arguments[1], arguments[2].self));
	if(arguments.length == 2 && arguments[1] instanceof tsColor) return ts_bind(tsStrokeStyle, this, _tsStrokeStyle_new_wc(arguments[0], arguments[1].self));
	if(arguments.length == 2) return ts_bind(tsStrokeStyle, this, _tsStrokeStyle_new_wo(arguments[0], arguments[1]));
	if(arguments.length == 1 && arguments[0] instanceof tsColor) return ts_bind(tsStrokeStyle, this, _tsStrokeStyle_new_c(arguments[0].self));
	if(arguments.length == 1) return ts_bind(tsStrokeStyle, this, _tsStrokeStyle_new_w(arguments[0]));
	if(arguments.length == 0) return ts_bind(tsStrokeStyle, this, _tsStrokeStyle_new());
	throw 'invalid StrokeStyle() arguments';
}
Module['StrokeStyle'] = tsStrokeStyle;
tsStrokeStyle.finalizer = new FinalizationRegistry((self) => { _tsStrokeStyle_delete(self); });
tsStrokeStyle.prototype = Object.create(tsStrokeStyle.prototype);
tsStrokeStyle.prototype.constructor = tsStrokeStyle;

tsStrokeStyle.prototype['toString'] = tsStrokeStyle.prototype.toString = function() { return '(' + this.width + ' ' + this.offset + ' : ' + this.color + ')'; };

/*
 */
tsStrokeStyle.prototype['set_width'] = tsStrokeStyle.prototype.set_width = function(width) { _tsStrokeStyle_set_width(this.self, width); };
tsStrokeStyle.prototype['set_offset'] = tsStrokeStyle.prototype.set_offset = function(offset) { _tsStrokeStyle_set_offset(this.self, offset); };
tsStrokeStyle.prototype['set_color'] = tsStrokeStyle.prototype.set_color = function(color) { _tsStrokeStyle_set_color(this.self, color.self); };

tsStrokeStyle.prototype['get_width'] = tsStrokeStyle.prototype.get_width = function() { return _tsStrokeStyle_get_width(this.self); };
tsStrokeStyle.prototype['get_offset'] = tsStrokeStyle.prototype.get_offset = function() { return _tsStrokeStyle_get_offset(this.self); };
tsStrokeStyle.prototype['get_color'] = tsStrokeStyle.prototype.get_color = function() { return ts_new(tsColor, _tsStrokeStyle_get_color(this.self)); };

Object.defineProperty(tsStrokeStyle.prototype, 'width', { set: tsStrokeStyle.prototype.set_width, get: tsStrokeStyle.prototype.get_width });
Object.defineProperty(tsStrokeStyle.prototype, 'offset', { set: tsStrokeStyle.prototype.set_offset, get: tsStrokeStyle.prototype.get_offset });
Object.defineProperty(tsStrokeStyle.prototype, 'color', { set: tsStrokeStyle.prototype.set_color, get: tsStrokeStyle.prototype.get_color });

/*****************************************************************************\
 *
 * GradientStyle
 *
\*****************************************************************************/

/*
 */
function tsGradientStyle(style) {
	if(style instanceof tsGradientStyle) return ts_bind(tsGradientStyle, this, _tsGradientStyle_copy(style.self));
	if(style === undefined) return ts_bind(tsGradientStyle, this, _tsGradientStyle_new());
	throw 'invalid GradientStyle() arguments';
}
Module['GradientStyle'] = tsGradientStyle;
tsGradientStyle.finalizer = new FinalizationRegistry((self) => { _tsGradientStyle_delete(self); });
tsGradientStyle.prototype = Object.create(tsGradientStyle.prototype);
tsGradientStyle.prototype.constructor = tsGradientStyle;

tsGradientStyle.prototype['toString'] = tsGradientStyle.prototype.toString = function() { return '(' + this.radius + ' ' + this.length + ' : ' + this.center + ' ' + this.axis + ' : ' + this.color_0 + ' ' + this.color_1 + ')'; };

/*
 */
tsGradientStyle.prototype['set_radius'] = tsGradientStyle.prototype.set_radius = function(radius) { _tsGradientStyle_set_radius(this.self, radius); };
tsGradientStyle.prototype['set_length'] = tsGradientStyle.prototype.set_length = function(length) { _tsGradientStyle_set_length(this.self, length); };
tsGradientStyle.prototype['set_center'] = tsGradientStyle.prototype.set_center = function(center) { _tsGradientStyle_set_center(this.self, center.self); };
tsGradientStyle.prototype['set_axis'] = tsGradientStyle.prototype.set_axis = function(axis) { _tsGradientStyle_set_axis(this.self, axis.self); };
tsGradientStyle.prototype['set_color_0'] = tsGradientStyle.prototype.set_color_0 = function(color_0) { _tsGradientStyle_set_color_0(this.self, color_0.self); };
tsGradientStyle.prototype['set_color_1'] = tsGradientStyle.prototype.set_color_1 = function(color_1) { _tsGradientStyle_set_color_1(this.self, color_1.self); };

tsGradientStyle.prototype['get_radius'] = tsGradientStyle.prototype.get_radius = function() { return _tsGradientStyle_get_radius(this.self); };
tsGradientStyle.prototype['get_length'] = tsGradientStyle.prototype.get_length = function() { return _tsGradientStyle_get_length(this.self); };
tsGradientStyle.prototype['get_center'] = tsGradientStyle.prototype.get_center = function() { return ts_new(tsVector2f, _tsGradientStyle_get_center(this.self)); };
tsGradientStyle.prototype['get_axis'] = tsGradientStyle.prototype.get_axis = function() { return ts_new(tsVector3f, _tsGradientStyle_get_axis(this.self)); };
tsGradientStyle.prototype['get_color_0'] = tsGradientStyle.prototype.get_color_0 = function() { return ts_new(tsColor, _tsGradientStyle_get_color_0(this.self)); };
tsGradientStyle.prototype['get_color_1'] = tsGradientStyle.prototype.get_color_1 = function() { return ts_new(tsColor, _tsGradientStyle_get_color_1(this.self)); };

Object.defineProperty(tsGradientStyle.prototype, 'radius', { set: tsGradientStyle.prototype.set_radius, get: tsGradientStyle.prototype.get_radius });
Object.defineProperty(tsGradientStyle.prototype, 'length', { set: tsGradientStyle.prototype.set_length, get: tsGradientStyle.prototype.get_length });
Object.defineProperty(tsGradientStyle.prototype, 'center', { set: tsGradientStyle.prototype.set_center, get: tsGradientStyle.prototype.get_center });
Object.defineProperty(tsGradientStyle.prototype, 'axis', { set: tsGradientStyle.prototype.set_axis, get: tsGradientStyle.prototype.get_axis });
Object.defineProperty(tsGradientStyle.prototype, 'color_0', { set: tsGradientStyle.prototype.set_color_0, get: tsGradientStyle.prototype.get_color_0 });
Object.defineProperty(tsGradientStyle.prototype, 'color_1', { set: tsGradientStyle.prototype.set_color_1, get: tsGradientStyle.prototype.get_color_1 });

/*****************************************************************************\
 *
 * CanvasVertex
 *
\*****************************************************************************/

/*
 */
function tsCanvasVertex(vertex) {
	if(vertex instanceof tsCanvasVertex) return ts_bind(tsCanvasVertex, this, _tsCanvasVertex_copy(vertex.self));
	if(vertex === undefined) return ts_bind(tsCanvasVertex, this, _tsCanvasVertex_new());
	throw 'invalid CanvasVertex() arguments';
}
Module['CanvasVertex'] = tsCanvasVertex;
tsCanvasVertex.finalizer = new FinalizationRegistry((self) => { _tsCanvasVertex_delete(self); });
tsCanvasVertex.prototype = Object.create(tsCanvasVertex.prototype);
tsCanvasVertex.prototype.constructor = tsCanvasVertex;

tsCanvasVertex.prototype['toString'] = tsCanvasVertex.prototype.toString = function() { return '(' + this.positions + ' : ' + this.texcoord + ' : ' + this.color + ')'; };

/*
 */
tsCanvasVertex.prototype['set_position'] = tsCanvasVertex.prototype.set_position = function(position) { _tsCanvasVertex_set_position(this.self, position.self); };
tsCanvasVertex.prototype['set_texcoord'] = tsCanvasVertex.prototype.set_texcoord = function(texcoord) { _tsCanvasVertex_set_texcoord(this.self, texcoord.self); };
tsCanvasVertex.prototype['set_color'] = tsCanvasVertex.prototype.set_color = function(color) { _tsCanvasVertex_set_color(this.self, color); };

tsCanvasVertex.prototype['get_position'] = tsCanvasVertex.prototype.get_position = function() { return ts_new(tsVector3f, _tsCanvasVertex_get_position(this.self)); };
tsCanvasVertex.prototype['get_texcoord'] = tsCanvasVertex.prototype.get_texcoord = function() { return ts_new(tsVector2f, _tsCanvasVertex_get_texcoord(this.self)); };
tsCanvasVertex.prototype['get_color'] = tsCanvasVertex.prototype.get_color = function() { return _tsCanvasVertex_get_color(this.self); };

Object.defineProperty(tsCanvasVertex.prototype, 'position', { set: tsCanvasVertex.prototype.set_position, get: tsCanvasVertex.prototype.get_position });
Object.defineProperty(tsCanvasVertex.prototype, 'texcoord', { set: tsCanvasVertex.prototype.set_texcoord, get: tsCanvasVertex.prototype.get_texcoord });
Object.defineProperty(tsCanvasVertex.prototype, 'color', { set: tsCanvasVertex.prototype.set_color, get: tsCanvasVertex.prototype.get_color });

/*****************************************************************************\
 *
 * CanvasShapeVertex
 *
\*****************************************************************************/

/*
 */
function tsCanvasShapeVertex(vertex) {
	if(vertex instanceof tsCanvasShapeVertex) return ts_bind(tsCanvasShapeVertex, this, _tsCanvasShapeVertex_copy(vertex.self));
	if(vertex === undefined) return ts_bind(tsCanvasShapeVertex, this, _tsCanvasShapeVertex_new());
	throw 'invalid CanvasShapeVertex() arguments';
}
Module['CanvasShapeVertex'] = tsCanvasShapeVertex;
tsCanvasShapeVertex.finalizer = new FinalizationRegistry((self) => { _tsCanvasShapeVertex_delete(self); });
tsCanvasShapeVertex.prototype = Object.create(tsCanvasShapeVertex.prototype);
tsCanvasShapeVertex.prototype.constructor = tsCanvasShapeVertex;

tsCanvasShapeVertex.prototype['toString'] = tsCanvasShapeVertex.prototype.toString = function() { return '(' + this.positions + ' : ' + this.parameters + ' : ' + this.texcoord + ')'; };

/*
 */
tsCanvasShapeVertex.prototype['set_position'] = tsCanvasShapeVertex.prototype.set_position = function(position) { _tsCanvasShapeVertex_set_position(this.self, position.self); };
tsCanvasShapeVertex.prototype['set_parameters'] = tsCanvasShapeVertex.prototype.set_parameters = function(parameters) { _tsCanvasShapeVertex_set_parameters(this.self, parameters.self); };
tsCanvasShapeVertex.prototype['set_texcoord'] = tsCanvasShapeVertex.prototype.set_texcoord = function(texcoord) { _tsCanvasShapeVertex_set_texcoord(this.self, texcoord.self); };

tsCanvasShapeVertex.prototype['get_position'] = tsCanvasShapeVertex.prototype.get_position = function() { return ts_new(tsVector4f, _tsCanvasShapeVertex_get_position(this.self)); };
tsCanvasShapeVertex.prototype['get_parameters'] = tsCanvasShapeVertex.prototype.get_parameters = function() { return ts_new(tsVector4f, _tsCanvasShapeVertex_get_parameters(this.self)); };
tsCanvasShapeVertex.prototype['get_texcoord'] = tsCanvasShapeVertex.prototype.get_texcoord = function() { return ts_new(tsVector2f, _tsCanvasShapeVertex_get_texcoord(this.self)); };

Object.defineProperty(tsCanvasShapeVertex.prototype, 'position', { set: tsCanvasShapeVertex.prototype.set_position, get: tsCanvasShapeVertex.prototype.get_position });
Object.defineProperty(tsCanvasShapeVertex.prototype, 'parameters', { set: tsCanvasShapeVertex.prototype.set_parameters, get: tsCanvasShapeVertex.prototype.get_parameters });
Object.defineProperty(tsCanvasShapeVertex.prototype, 'texcoord', { set: tsCanvasShapeVertex.prototype.set_texcoord, get: tsCanvasShapeVertex.prototype.get_texcoord });

/*****************************************************************************\
 *
 * CanvasStripVertex
 *
\*****************************************************************************/

/*
 */
function tsCanvasStripVertex(vertex) {
	if(vertex instanceof tsCanvasStripVertex) return ts_bind(tsCanvasStripVertex, this, _tsCanvasStripVertex_copy(vertex.self));
	if(vertex === undefined) return ts_bind(tsCanvasStripVertex, this, _tsCanvasStripVertex_new());
	throw 'invalid CanvasStripVertex() arguments';
}
Module['CanvasStripVertex'] = tsCanvasStripVertex;
tsCanvasStripVertex.finalizer = new FinalizationRegistry((self) => { _tsCanvasStripVertex_delete(self); });
tsCanvasStripVertex.prototype = Object.create(tsCanvasStripVertex.prototype);
tsCanvasStripVertex.prototype.constructor = tsCanvasStripVertex;

tsCanvasStripVertex.prototype['toString'] = tsCanvasStripVertex.prototype.toString = function() { return '(' + this.positions + ' : ' + this.parameters + ' : ' + this.adjacencies + ')'; };

/*
 */
tsCanvasStripVertex.prototype['set_position'] = tsCanvasStripVertex.prototype.set_position = function(position) { _tsCanvasStripVertex_set_position(this.self, position.self); };
tsCanvasStripVertex.prototype['set_parameters'] = tsCanvasStripVertex.prototype.set_parameters = function(parameters) { _tsCanvasStripVertex_set_parameters(this.self, parameters.self); };
tsCanvasStripVertex.prototype['set_adjacencies'] = tsCanvasStripVertex.prototype.set_adjacencies = function(adjacencies) { _tsCanvasStripVertex_set_adjacencies(this.self, adjacencies.self); };

tsCanvasStripVertex.prototype['get_position'] = tsCanvasStripVertex.prototype.get_position = function() { return ts_new(tsVector4f, _tsCanvasStripVertex_get_position(this.self)); };
tsCanvasStripVertex.prototype['get_parameters'] = tsCanvasStripVertex.prototype.get_parameters = function() { return ts_new(tsVector4f, _tsCanvasStripVertex_get_parameters(this.self)); };
tsCanvasStripVertex.prototype['get_adjacencies'] = tsCanvasStripVertex.prototype.get_adjacencies = function() { return ts_new(tsVector2f, _tsCanvasStripVertex_get_adjacencies(this.self)); };

Object.defineProperty(tsCanvasStripVertex.prototype, 'position', { set: tsCanvasStripVertex.prototype.set_position, get: tsCanvasStripVertex.prototype.get_position });
Object.defineProperty(tsCanvasStripVertex.prototype, 'parameters', { set: tsCanvasStripVertex.prototype.set_parameters, get: tsCanvasStripVertex.prototype.get_parameters });
Object.defineProperty(tsCanvasStripVertex.prototype, 'adjacencies', { set: tsCanvasStripVertex.prototype.set_adjacencies, get: tsCanvasStripVertex.prototype.get_adjacencies });

/*****************************************************************************\
 *
 * Tensor
 *
\*****************************************************************************/

/*
 */
function tsTensor(tensor) {
	if(tensor instanceof tsTensor) return ts_bind(tsTensor, this, _tsTensor_copy(tensor.self));
	if(tensor === undefined) return ts_bind(tsTensor, this, _tsTensor_new());
	throw 'invalid Tensor() arguments';
}
Module['Tensor'] = tsTensor;
tsTensor.finalizer = new FinalizationRegistry((self) => { _tsTensor_delete(self); });
tsTensor.prototype = Object.create(tsTensor.prototype);
tsTensor.prototype.constructor = tsTensor;

/*****************************************************************************\
 *
 * Command
 *
\*****************************************************************************/

/*
 */
tsCommand.prototype['setUniform'] = tsCommand.prototype.setUniform = function(index, data) {
	_tsCommand_setUniformData(this.self, index, ts_array(data, true), data.byteLength);
};

tsCommand.prototype['setStorage'] = tsCommand.prototype.setStorage = function(index, data) {
	_tsCommand_setStorageData(this.self, index, ts_array(data, true), data.byteLength);
};

tsCommand.prototype['setVertices'] = tsCommand.prototype.setVertices = function(index, data) {
	_tsCommand_setVertexData(this.self, index, ts_array(data, true), data.byteLength);
};

tsCommand.prototype['setIndices'] = tsCommand.prototype.setIndices = function(data) {
	let format = tsFormat.Unknown;
	if(data instanceof Int16Array || data instanceof Uint16Array) format = tsFormat.Ru16;
	else if(data instanceof Int32Array || data instanceof Uint32Array) format = tsFormat.Ru32;
	_tsCommand_setIndexData(this.self, format, ts_array(data, true), data.byteLength);
};

tsCommand.prototype['setIndirect'] = tsCommand.prototype.setIndirect = function(data) {
	_tsCommand_setIndirectData(this.self, ts_array(data, true), data.byteLength);
};

/*****************************************************************************\
 *
 * Compute
 *
\*****************************************************************************/

/*
 */
tsCompute.prototype['setUniform'] = tsCompute.prototype.setUniform = function(index, data) {
	_tsCompute_setUniformData(this.self, index, ts_array(data, true), data.byteLength);
};

tsCompute.prototype['setStorage'] = tsCompute.prototype.setStorage = function(index, data) {
	_tsCompute_setStorageData(this.self, index, ts_array(data, true), data.byteLength);
};

tsCompute.prototype['setIndirect'] = tsCompute.prototype.setIndirect = function(data) {
	_tsCompute_setIndirectData(this.self, ts_array(data, true), data.byteLength);
};

/*****************************************************************************\
 *
 * MeshAttribute
 *
\*****************************************************************************/

/*
 */
tsMeshAttribute.prototype['set'] = tsMeshAttribute.prototype.set = function(index, src) {
	if(src instanceof tsVector2i) return _tsMeshAttribute_setValue(this.self, index, src.self, 8);
	if(src instanceof tsVector2f) return _tsMeshAttribute_setValue(this.self, index, src.self, 8);
	if(src instanceof tsVector3i) return _tsMeshAttribute_setValue(this.self, index, src.self, 12);
	if(src instanceof tsVector3f) return _tsMeshAttribute_setValue(this.self, index, src.self, 12);
	if(src instanceof tsVector4i) return _tsMeshAttribute_setValue(this.self, index, src.self, 16);
	if(src instanceof tsVector4f) return _tsMeshAttribute_setValue(this.self, index, src.self, 16);
	_tsMeshAttribute_setValue(this.self, index, ts_array(src), src.byteLength);
};

/*****************************************************************************\
 *
 * Platform
 *
\*****************************************************************************/

/*
 */
async function run_webgpu(main, app) {
	
	// check WebGPU support
	if(!navigator.gpu) {
		tsLog.print(tsLog.Level.Warning, 'run_webgpu(): WebGPU is not supported\n');
		app.create(tsPlatform.GLES);
		return main(Module, app);
	}
	
	// request WebGPU adapter
	let adapter = await navigator.gpu.requestAdapter();
	if(!adapter) {
		tsLog.print(tsLog.Level.Warning, 'run_webgpu(): can\'t request WGPUAdapter\n');
		app.create(tsPlatform.GLES);
		return main(Module, app);
	}
	
	// request WebGPU device
	let device = await adapter.requestDevice();
	if(!device) {
		tsLog.print(tsLog.Level.Warning, 'run_webgpu(): can\'t request WGPUDevice\n');
		app.create(tsPlatform.GLES);
		return main(Module, app);
	}
	
	// preinitialized WebGPU device
	Module['preinitializedWebGPUDevice'] = device;
	
	// initialize WebGPU
	tsWGContext.open(0, 0, 0);
	
	// run application
	return main(Module, app);
}

/*
 */
Module['run'] = function(main) {
	
	// create application
	let app = new tsApp(location.search.substring(1).split('&'));
	if(!app.create()) {
		tsLog.print(tsLog.Level.Error, 'run(): can\'t create App\n');
		return;
	}
	
	// run application
	if(app.platform == tsPlatform.GLES) main(Module, app);
	else run_webgpu(main, app);
};
