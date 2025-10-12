// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*****************************************************************************\
 *
 * Vector2i
 *
\*****************************************************************************/

/*
 */
function tsVector2i(x, y) {
	if(x instanceof tsVector2i) return ts_bind(tsVector2i, this, _tsVector2i_copy(x.self));
	if(x instanceof tsVector3i) return ts_bind(tsVector2i, this, _tsVector2i_new_v3i(x.self));
	if(x instanceof tsVector4i) return ts_bind(tsVector2i, this, _tsVector2i_new_v4i(x.self));
	if(x instanceof tsVector2f) return ts_bind(tsVector2i, this, _tsVector2i_new_v2f(x.self));
	if(x instanceof tsVector2d) return ts_bind(tsVector2i, this, _tsVector2i_new_v2d(x.self));
	if(x instanceof Array && x.length === 2) return ts_bind(tsVector2i, this, _tsVector2i_new_ai(ts_i32(x, true)));
	if(x !== undefined && y !== undefined) return ts_bind(tsVector2i, this, _tsVector2i_new_xy(x, y));
	if(x !== undefined) return ts_bind(tsVector2i, this, _tsVector2i_new_v(x));
	if(x === undefined) return ts_bind(tsVector2i, this, _tsVector2i_new());
	throw 'invalid Vector2i() arguments';
}
Module['Vector2i'] = tsVector2i;
tsVector2i.finalizer = new FinalizationRegistry((self) => { _tsVector2i_delete(self); });
tsVector2i.prototype = Object.create(tsVector2i.prototype);
tsVector2i.prototype.constructor = tsVector2i;

tsVector2i.prototype['toBytes'] = tsVector2i.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 8); };
tsVector2i.prototype['toArray'] = tsVector2i.prototype.getArray = function() { return new Int32Array(HEAP32.buffer, this.self, 2); };
tsVector2i.prototype['toString'] = tsVector2i.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ')'; };

/*
 */
tsVector2i.prototype['set'] = tsVector2i.prototype.set = function(index, s) { _tsVector2i_set_index(this.self, index, s); };
tsVector2i.prototype['get'] = tsVector2i.prototype.get = function(index) { return _tsVector2i_get_index(this.self, index); };

tsVector2i.prototype['set_x'] = tsVector2i.prototype.set_x = function(x) { _tsVector2i_set_x(this.self, x); };
tsVector2i.prototype['set_y'] = tsVector2i.prototype.set_y = function(y) { _tsVector2i_set_y(this.self, y); };

tsVector2i.prototype['get_x'] = tsVector2i.prototype.get_x = function() { return _tsVector2i_get_x(this.self); };
tsVector2i.prototype['get_y'] = tsVector2i.prototype.get_y = function() { return _tsVector2i_get_y(this.self); };

Object.defineProperty(tsVector2i.prototype, 'x', { get: tsVector2i.prototype.get_x, set: tsVector2i.prototype.set_x });
Object.defineProperty(tsVector2i.prototype, 'y', { get: tsVector2i.prototype.get_y, set: tsVector2i.prototype.set_y });

/*
 */
tsVector2i.prototype['neg'] = tsVector2i.prototype.neg = function() { return ts_new(tsVector2i, _tsVector2i_neg(this.self)); };

tsVector2i.prototype['mul'] = tsVector2i.prototype.mul = function(v) {
	if(v instanceof tsVector2i) return ts_new(tsVector2i, _tsVector2i_mul(this.self, v.self));
	return ts_new(tsVector2i, _tsVector2i_mul1(this.self, v));
};
tsVector2i.prototype['div'] = tsVector2i.prototype.div = function(v) {
	if(v instanceof tsVector2i) return ts_new(tsVector2i, _tsVector2i_div(this.self, v.self));
	return ts_new(tsVector2i, _tsVector2i_div1(this.self, v));
};
tsVector2i.prototype['add'] = tsVector2i.prototype.add = function(v) {
	if(v instanceof tsVector2i) return ts_new(tsVector2i, _tsVector2i_add(this.self, v.self));
	return ts_new(tsVector2i, _tsVector2i_add1(this.self, v));
};
tsVector2i.prototype['sub'] = tsVector2i.prototype.sub = function(v) {
	if(v instanceof tsVector2i) return ts_new(tsVector2i, _tsVector2i_sub(this.self, v.self));
	return ts_new(tsVector2i, _tsVector2i_sub1(this.self, v));
};

tsVector2i.prototype['and'] = tsVector2i.prototype.and = function(v) {
	if(v instanceof tsVector2i) return ts_new(tsVector2i, _tsVector2i_and(this.self, v.self));
	return ts_new(tsVector2i, _tsVector2i_and1(this.self, v));
};
tsVector2i.prototype['or'] = tsVector2i.prototype.or = function(v) {
	if(v instanceof tsVector2i) return ts_new(tsVector2i, _tsVector2i_or(this.self, v.self));
	return ts_new(tsVector2i, _tsVector2i_or1(this.self, v));
};
tsVector2i.prototype['xor'] = tsVector2i.prototype.xor = function(v) {
	if(v instanceof tsVector2i) return ts_new(tsVector2i, _tsVector2i_xor(this.self, v.self));
	return ts_new(tsVector2i, _tsVector2i_xor1(this.self, v));
};
tsVector2i.prototype['shl'] = tsVector2i.prototype.shl = function(v) {
	return ts_new(tsVector2i, _tsVector2i_shl1(this.self, v));
};
tsVector2i.prototype['shr'] = tsVector2i.prototype.shr = function(v) {
	return ts_new(tsVector2i, _tsVector2i_shr1(this.self, v));
};

tsVector2i.prototype['abs'] = tsVector2i.prototype.abs = function() { return ts_new(tsVector2i, _tsVector2i_abs(this.self)); };

tsVector2i['min'] = tsVector2i.min = function(v0, v1) { return ts_new(tsVector2i, _tsVector2i_min(v0.self, v1.self)); };
tsVector2i['max'] = tsVector2i.max = function(v0, v1) { return ts_new(tsVector2i, _tsVector2i_max(v0.self, v1.self)); };

tsVector2i.prototype['clamp'] = tsVector2i.prototype.clamp = function(v0, v1) { return ts_new(tsVector2i, _tsVector2i_clamp(this.self, v0.self, v1.self)); };

tsVector2i['zero'] = tsVector2i.zero = function() { return ts_new(tsVector2i, _tsVector2i_new_v(0)); };
tsVector2i['one'] = tsVector2i.one = function() { return ts_new(tsVector2i, _tsVector2i_new_v(1)); };

/*****************************************************************************\
 *
 * Vector2f
 *
\*****************************************************************************/

/*
 */
function tsVector2f(x, y) {
	if(x instanceof tsVector2f) return ts_bind(tsVector2f, this, _tsVector2f_copy(x.self));
	if(x instanceof tsVector3f) return ts_bind(tsVector2f, this, _tsVector2f_new_v3f(x.self));
	if(x instanceof tsVector4f) return ts_bind(tsVector2f, this, _tsVector2f_new_v4f(x.self));
	if(x instanceof tsVector2i) return ts_bind(tsVector2f, this, _tsVector2f_new_v2i(x.self));
	if(x instanceof tsVector2d) return ts_bind(tsVector2f, this, _tsVector2f_new_v2d(x.self));
	if(x instanceof Array && x.length === 2) return ts_bind(tsVector2f, this, _tsVector2f_new_af(ts_f32(x, true)));
	if(x !== undefined && y !== undefined) return ts_bind(tsVector2f, this, _tsVector2f_new_xy(x, y));
	if(x !== undefined) return ts_bind(tsVector2f, this, _tsVector2f_new_v(x));
	if(x === undefined) return ts_bind(tsVector2f, this, _tsVector2f_new());
	throw 'invalid Vector2f() arguments';
}
Module['Vector2f'] = tsVector2f;
tsVector2f.finalizer = new FinalizationRegistry((self) => { _tsVector2f_delete(self); });
tsVector2f.prototype = Object.create(tsVector2f.prototype);
tsVector2f.prototype.constructor = tsVector2f;

tsVector2f.prototype['toBytes'] = tsVector2f.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 8); };
tsVector2f.prototype['toArray'] = tsVector2f.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 2); };
tsVector2f.prototype['toString'] = tsVector2f.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ')'; };

/*
 */
tsVector2f.prototype['set'] = tsVector2f.prototype.set = function(index, s) { _tsVector2f_set_index(this.self, index, s); };
tsVector2f.prototype['get'] = tsVector2f.prototype.get = function(index) { return _tsVector2f_get_index(this.self, index); };

tsVector2f.prototype['set_x'] = tsVector2f.prototype.set_x = function(x) { _tsVector2f_set_x(this.self, x); };
tsVector2f.prototype['set_y'] = tsVector2f.prototype.set_y = function(y) { _tsVector2f_set_y(this.self, y); };

tsVector2f.prototype['get_x'] = tsVector2f.prototype.get_x = function() { return _tsVector2f_get_x(this.self); };
tsVector2f.prototype['get_y'] = tsVector2f.prototype.get_y = function() { return _tsVector2f_get_y(this.self); };

Object.defineProperty(tsVector2f.prototype, 'x', { get: tsVector2f.prototype.get_x, set: tsVector2f.prototype.set_x });
Object.defineProperty(tsVector2f.prototype, 'y', { get: tsVector2f.prototype.get_y, set: tsVector2f.prototype.set_y });

/*
 */
tsVector2f.prototype['neg'] = tsVector2f.prototype.neg = function() { return ts_new(tsVector2f, _tsVector2f_neg(this.self)); };

tsVector2f.prototype['mul'] = tsVector2f.prototype.mul = function(v) {
	if(v instanceof tsVector2f) return ts_new(tsVector2f, _tsVector2f_mul(this.self, v.self));
	if(v instanceof tsMatrix3x2f) return ts_new(tsVector2f, _tsMatrix3x2f_mul2t(this.self, v.self));
	if(v instanceof tsMatrix4x3f) return ts_new(tsVector2f, _tsMatrix4x3f_mul2t(this.self, v.self));
	if(v instanceof tsMatrix4x4f) return ts_new(tsVector2f, _tsMatrix4x4f_mul2t(this.self, v.self));
	if(v instanceof tsQuaternionf) return ts_new(tsVector2f, _tsQuaternionf_mul2t(this.self, v.self));
	return ts_new(tsVector2f, _tsVector2f_mul1(this.self, v));
};
tsVector2f.prototype['div'] = tsVector2f.prototype.div = function(v) {
	if(v instanceof tsVector2f) return ts_new(tsVector2f, _tsVector2f_div(this.self, v.self));
	return ts_new(tsVector2f, _tsVector2f_div1(this.self, v));
};
tsVector2f.prototype['add'] = tsVector2f.prototype.add = function(v) {
	if(v instanceof tsVector2f) return ts_new(tsVector2f, _tsVector2f_add(this.self, v.self));
	return ts_new(tsVector2f, _tsVector2f_add1(this.self, v));
};
tsVector2f.prototype['sub'] = tsVector2f.prototype.sub = function(v) {
	if(v instanceof tsVector2f) return ts_new(tsVector2f, _tsVector2f_sub(this.self, v.self));
	return ts_new(tsVector2f, _tsVector2f_sub1(this.self, v));
};

tsVector2f.prototype['abs'] = tsVector2f.prototype.abs = function() { return ts_new(tsVector2f, _tsVector2f_abs(this.self)); };

tsVector2f['min'] = tsVector2f.min = function(v0, v1) { return ts_new(tsVector2f, _tsVector2f_min(v0.self, v1.self)); };
tsVector2f['max'] = tsVector2f.max = function(v0, v1) { return ts_new(tsVector2f, _tsVector2f_max(v0.self, v1.self)); };

tsVector2f.prototype['clamp'] = tsVector2f.prototype.clamp = function(v0, v1) { return ts_new(tsVector2f, _tsVector2f_clamp(this.self, v0.self, v1.self)); };
tsVector2f.prototype['saturate'] = tsVector2f.prototype.saturate = function() { return ts_new(tsVector2f, _tsVector2f_saturate(this.self)); };

tsVector2f['dot'] = tsVector2f.dot = function(v0, v1) { return _tsVector2f_dot(v0.self, v1.self); };
tsVector2f['cross'] = tsVector2f.cross = function(v0, v1) { return ts_new(tsVector2f, _tsVector2f_cross(v0.self, v1.self)); };

tsVector2f.prototype['length'] = tsVector2f.prototype.length = function() { return _tsVector2f_length(this.self); };

tsVector2f.prototype['normalize'] = tsVector2f.prototype.normalize = function() { return ts_new(tsVector2f, _tsVector2f_normalize(this.self)); };

tsVector2f['lerp'] = tsVector2f.lerp = function(v0, v1, k) { return ts_new(tsVector2f, _tsVector2f_lerp(v0.self, v1.self, k)); };

tsVector2f['zero'] = tsVector2f.zero = function() { return ts_new(tsVector2f, _tsVector2f_new_v(0.0)); };
tsVector2f['one'] = tsVector2f.one = function() { return ts_new(tsVector2f, _tsVector2f_new_v(1.0)); };

/*****************************************************************************\
 *
 * Vector2d
 *
\*****************************************************************************/

/*
 */
function tsVector2d(x, y) {
	if(x instanceof tsVector2d) return ts_bind(tsVector2d, this, _tsVector2d_copy(x.self));
	if(x instanceof tsVector3d) return ts_bind(tsVector2d, this, _tsVector2d_new_v3d(x.self));
	if(x instanceof tsVector4d) return ts_bind(tsVector2d, this, _tsVector2d_new_v4d(x.self));
	if(x instanceof tsVector2i) return ts_bind(tsVector2d, this, _tsVector2d_new_v2i(x.self));
	if(x instanceof tsVector2f) return ts_bind(tsVector2d, this, _tsVector2d_new_v2f(x.self));
	if(x instanceof Array && x.length === 2) return ts_bind(tsVector2d, this, _tsVector2d_new_ad(ts_f64(x, true)));
	if(x !== undefined && y !== undefined) return ts_bind(tsVector2d, this, _tsVector2d_new_xy(x, y));
	if(x !== undefined) return ts_bind(tsVector2d, this, _tsVector2d_new_v(x));
	if(x === undefined) return ts_bind(tsVector2d, this, _tsVector2d_new());
	throw 'invalid Vector2d() arguments';
}
Module['Vector2d'] = tsVector2d;
tsVector2d.finalizer = new FinalizationRegistry((self) => { _tsVector2d_delete(self); });
tsVector2d.prototype = Object.create(tsVector2d.prototype);
tsVector2d.prototype.constructor = tsVector2d;

tsVector2d.prototype['toBytes'] = tsVector2d.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 16); };
tsVector2d.prototype['toArray'] = tsVector2d.prototype.getArray = function() { return new Float64Array(HEAPF64.buffer, this.self, 2); };
tsVector2d.prototype['toString'] = tsVector2d.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ')'; };

/*
 */
tsVector2d.prototype['set'] = tsVector2d.prototype.set = function(index, s) { _tsVector2d_set_index(this.self, index, s); };
tsVector2d.prototype['get'] = tsVector2d.prototype.get = function(index) { return _tsVector2d_get_index(this.self, index); };

tsVector2d.prototype['set_x'] = tsVector2d.prototype.set_x = function(x) { _tsVector2d_set_x(this.self, x); };
tsVector2d.prototype['set_y'] = tsVector2d.prototype.set_y = function(y) { _tsVector2d_set_y(this.self, y); };

tsVector2d.prototype['get_x'] = tsVector2d.prototype.get_x = function() { return _tsVector2d_get_x(this.self); };
tsVector2d.prototype['get_y'] = tsVector2d.prototype.get_y = function() { return _tsVector2d_get_y(this.self); };

Object.defineProperty(tsVector2d.prototype, 'x', { get: tsVector2d.prototype.get_x, set: tsVector2d.prototype.set_x });
Object.defineProperty(tsVector2d.prototype, 'y', { get: tsVector2d.prototype.get_y, set: tsVector2d.prototype.set_y });

/*
 */
tsVector2d.prototype['neg'] = tsVector2d.prototype.neg = function() { return ts_new(tsVector2d, _tsVector2d_neg(this.self)); };

tsVector2d.prototype['mul'] = tsVector2d.prototype.mul = function(v) {
	if(v instanceof tsVector2d) return ts_new(tsVector2d, _tsVector2d_mul(this.self, v.self));
	if(v instanceof tsMatrix3x2d) return ts_new(tsVector2d, _tsMatrix3x2d_mul2t(this.self, v.self));
	if(v instanceof tsMatrix4x3d) return ts_new(tsVector2d, _tsMatrix4x3d_mul2t(this.self, v.self));
	if(v instanceof tsMatrix4x4d) return ts_new(tsVector2d, _tsMatrix4x4d_mul2t(this.self, v.self));
	if(v instanceof tsQuaternionf) return ts_new(tsVector2d, _tsQuaternionf_mul2t(this.self, v.self));
	return ts_new(tsVector2d, _tsVector2d_mul1(this.self, v));
};
tsVector2d.prototype['div'] = tsVector2d.prototype.div = function(v) {
	if(v instanceof tsVector2d) return ts_new(tsVector2d, _tsVector2d_div(this.self, v.self));
	return ts_new(tsVector2d, _tsVector2d_div1(this.self, v));
};
tsVector2d.prototype['add'] = tsVector2d.prototype.add = function(v) {
	if(v instanceof tsVector2d) return ts_new(tsVector2d, _tsVector2d_add(this.self, v.self));
	return ts_new(tsVector2d, _tsVector2d_add1(this.self, v));
};
tsVector2d.prototype['sub'] = tsVector2d.prototype.sub = function(v) {
	if(v instanceof tsVector2d) return ts_new(tsVector2d, _tsVector2d_sub(this.self, v.self));
	return ts_new(tsVector2d, _tsVector2d_sub1(this.self, v));
};

tsVector2d.prototype['abs'] = tsVector2d.prototype.abs = function() { return ts_new(tsVector2d, _tsVector2d_abs(this.self)); };

tsVector2d['min'] = tsVector2d.min = function(v0, v1) { return ts_new(tsVector2d, _tsVector2d_min(v0.self, v1.self)); };
tsVector2d['max'] = tsVector2d.max = function(v0, v1) { return ts_new(tsVector2d, _tsVector2d_max(v0.self, v1.self)); };

tsVector2d.prototype['clamp'] = tsVector2d.prototype.clamp = function(v0, v1) { return ts_new(tsVector2d, _tsVector2d_clamp(this.self, v0.self, v1.self)); };
tsVector2d.prototype['saturate'] = tsVector2d.prototype.saturate = function() { return ts_new(tsVector2d, _tsVector2d_saturate(this.self)); };

tsVector2d['dot'] = tsVector2d.dot = function(v0, v1) { return _tsVector2d_dot(v0.self, v1.self); };
tsVector2d['cross'] = tsVector2d.cross = function(v0, v1) { return ts_new(tsVector2d, _tsVector2d_cross(v0.self, v1.self)); };

tsVector2d.prototype['length'] = tsVector2d.prototype.length = function() { return _tsVector2d_length(this.self); };

tsVector2d.prototype['normalize'] = tsVector2d.prototype.normalize = function() { return ts_new(tsVector2d, _tsVector2d_normalize(this.self)); };

tsVector2d['lerp'] = tsVector2d.lerp = function(v0, v1, k) { return ts_new(tsVector2d, _tsVector2d_lerp(v0.self, v1.self, k)); };

tsVector2d['zero'] = tsVector2d.zero = function() { return ts_new(tsVector2d, _tsVector2d_new_v(0.0)); };
tsVector2d['one'] = tsVector2d.one = function() { return ts_new(tsVector2d, _tsVector2d_new_v(1.0)); };

/*****************************************************************************\
 *
 * Vector3i
 *
\*****************************************************************************/

/*
 */
function tsVector3i(x, y, z) {
	if(x instanceof tsVector3i && y === undefined) return ts_bind(tsVector3i, this, _tsVector3i_copy(x.self));
	if(x instanceof tsVector2i && y !== undefined) return ts_bind(tsVector3i, this, _tsVector3i_new_v2i(x.self, y));
	if(x instanceof tsVector4i && y === undefined) return ts_bind(tsVector3i, this, _tsVector3i_new_v4i(x.self));
	if(x instanceof tsVector3f && y !== undefined) return ts_bind(tsVector3i, this, _tsVector3i_new_v3f(x.self, y));
	if(x instanceof tsVector3d && y !== undefined) return ts_bind(tsVector3i, this, _tsVector3i_new_v3d(x.self, y));
	if(x instanceof Array && x.length === 3) return ts_bind(tsVector3i, this, _tsVector3i_new_ai(ts_i32(x, true)));
	if(x !== undefined && y !== undefined && z !== undefined) return ts_bind(tsVector3i, this, _tsVector3i_new_xyz(x, y, z));
	if(x !== undefined && y === undefined) return ts_bind(tsVector3i, this, _tsVector3i_new_v(x));
	if(x === undefined && y === undefined) return ts_bind(tsVector3i, this, _tsVector3i_new());
	throw 'invalid Vector3i() arguments';
}
Module['Vector3i'] = tsVector3i;
tsVector3i.finalizer = new FinalizationRegistry((self) => { _tsVector3i_delete(self); });
tsVector3i.prototype = Object.create(tsVector3i.prototype);
tsVector3i.prototype.constructor = tsVector3i;

tsVector3i.prototype['toBytes'] = tsVector3i.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 12); };
tsVector3i.prototype['toArray'] = tsVector3i.prototype.getArray = function() { return new Int32Array(HEAP32.buffer, this.self, 3); };
tsVector3i.prototype['toString'] = tsVector3i.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' ' + this.z + ')'; };

/*
 */
tsVector3i.prototype['set'] = tsVector3i.prototype.set = function(index, s) { _tsVector3i_set_index(this.self, index, s); };
tsVector3i.prototype['get'] = tsVector3i.prototype.get = function(index) { return _tsVector3i_get_index(this.self, index); };

tsVector3i.prototype['set_x'] = tsVector3i.prototype.set_x = function(x) { _tsVector3i_set_x(this.self, x); };
tsVector3i.prototype['set_y'] = tsVector3i.prototype.set_y = function(y) { _tsVector3i_set_y(this.self, y); };
tsVector3i.prototype['set_z'] = tsVector3i.prototype.set_z = function(z) { _tsVector3i_set_z(this.self, z); };

tsVector3i.prototype['get_x'] = tsVector3i.prototype.get_x = function() { return _tsVector3i_get_x(this.self); };
tsVector3i.prototype['get_y'] = tsVector3i.prototype.get_y = function() { return _tsVector3i_get_y(this.self); };
tsVector3i.prototype['get_z'] = tsVector3i.prototype.get_z = function() { return _tsVector3i_get_z(this.self); };

Object.defineProperty(tsVector3i.prototype, 'x', { get: tsVector3i.prototype.get_x, set: tsVector3i.prototype.set_x });
Object.defineProperty(tsVector3i.prototype, 'y', { get: tsVector3i.prototype.get_y, set: tsVector3i.prototype.set_y });
Object.defineProperty(tsVector3i.prototype, 'z', { get: tsVector3i.prototype.get_z, set: tsVector3i.prototype.set_z });

/*
 */
tsVector3i.prototype['neg'] = tsVector3i.prototype.neg = function() { return ts_new(tsVector3i, _tsVector3i_neg(this.self)); };

tsVector3i.prototype['mul'] = tsVector3i.prototype.mul = function(v) {
	if(v instanceof tsVector3i) return ts_new(tsVector3i, _tsVector3i_mul(this.self, v.self));
	return ts_new(tsVector3i, _tsVector3i_mul1(this.self, v));
};
tsVector3i.prototype['div'] = tsVector3i.prototype.div = function(v) {
	if(v instanceof tsVector3i) return ts_new(tsVector3i, _tsVector3i_div(this.self, v.self));
	return ts_new(tsVector3i, _tsVector3i_div1(this.self, v));
};
tsVector3i.prototype['add'] = tsVector3i.prototype.add = function(v) {
	if(v instanceof tsVector3i) return ts_new(tsVector3i, _tsVector3i_add(this.self, v.self));
	return ts_new(tsVector3i, _tsVector3i_add1(this.self, v));
};
tsVector3i.prototype['sub'] = tsVector3i.prototype.sub = function(v) {
	if(v instanceof tsVector3i) return ts_new(tsVector3i, _tsVector3i_sub(this.self, v.self));
	return ts_new(tsVector3i, _tsVector3i_sub1(this.self, v));
};

tsVector3i.prototype['and'] = tsVector3i.prototype.and = function(v) {
	if(v instanceof tsVector3i) return ts_new(tsVector3i, _tsVector3i_and(this.self, v.self));
	return ts_new(tsVector3i, _tsVector3i_and1(this.self, v));
};
tsVector3i.prototype['or'] = tsVector3i.prototype.or = function(v) {
	if(v instanceof tsVector3i) return ts_new(tsVector3i, _tsVector3i_or(this.self, v.self));
	return ts_new(tsVector3i, _tsVector3i_or1(this.self, v));
};
tsVector3i.prototype['xor'] = tsVector3i.prototype.xor = function(v) {
	if(v instanceof tsVector3i) return ts_new(tsVector3i, _tsVector3i_xor(this.self, v.self));
	return ts_new(tsVector3i, _tsVector3i_xor1(this.self, v));
};
tsVector3i.prototype['shl'] = tsVector3i.prototype.shl = function(v) {
	return ts_new(tsVector3i, _tsVector3i_shl1(this.self, v));
};
tsVector3i.prototype['shr'] = tsVector3i.prototype.shr = function(v) {
	return ts_new(tsVector3i, _tsVector3i_shr1(this.self, v));
};

tsVector3i.prototype['abs'] = tsVector3i.prototype.abs = function() { return ts_new(tsVector3i, _tsVector3i_abs(this.self)); };

tsVector3i['min'] = tsVector3i.min = function(v0, v1) { return ts_new(tsVector3i, _tsVector3i_min(v0.self, v1.self)); };
tsVector3i['max'] = tsVector3i.max = function(v0, v1) { return ts_new(tsVector3i, _tsVector3i_max(v0.self, v1.self)); };

tsVector3i.prototype['clamp'] = tsVector3i.prototype.clamp = function(v0, v1) { return ts_new(tsVector3i, _tsVector3i_clamp(this.self, v0.self, v1.self)); };

tsVector3i['zero'] = tsVector3i.zero = function() { return ts_new(tsVector3i, _tsVector3i_new_v(0)); };
tsVector3i['one'] = tsVector3i.one = function() { return ts_new(tsVector3i, _tsVector3i_new_v(1)); };

/*****************************************************************************\
 *
 * Vector3f
 *
\*****************************************************************************/

/*
 */
function tsVector3f(x, y, z) {
	if(x instanceof tsVector3f && y === undefined) return ts_bind(tsVector3f, this, _tsVector3f_copy(x.self));
	if(x instanceof tsVector2f && y !== undefined) return ts_bind(tsVector3f, this, _tsVector3f_new_v2f(x.self, y));
	if(x instanceof tsVector4f && y === undefined) return ts_bind(tsVector3f, this, _tsVector3f_new_v4f(x.self));
	if(x instanceof tsVector3i && y !== undefined) return ts_bind(tsVector3f, this, _tsVector3f_new_v3i(x.self, y));
	if(x instanceof tsVector3d && y !== undefined) return ts_bind(tsVector3f, this, _tsVector3f_new_v3d(x.self, y));
	if(x instanceof Array && x.length === 3) return ts_bind(tsVector3f, this, _tsVector3f_new_af(ts_f32(x, true)));
	if(x !== undefined && y !== undefined && z !== undefined) return ts_bind(tsVector3f, this, _tsVector3f_new_xyz(x, y, z));
	if(x !== undefined && y === undefined) return ts_bind(tsVector3f, this, _tsVector3f_new_v(x));
	if(x === undefined && y === undefined) return ts_bind(tsVector3f, this, _tsVector3f_new());
	throw 'invalid Vector3f() arguments';
}
Module['Vector3f'] = tsVector3f;
tsVector3f.finalizer = new FinalizationRegistry((self) => { _tsVector3f_delete(self); });
tsVector3f.prototype = Object.create(tsVector3f.prototype);
tsVector3f.prototype.constructor = tsVector3f;

tsVector3f.prototype['toBytes'] = tsVector3f.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 12); };
tsVector3f.prototype['toArray'] = tsVector3f.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 3); };
tsVector3f.prototype['toString'] = tsVector3f.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' ' + this.z + ')'; };

/*
 */
tsVector3f.prototype['set'] = tsVector3f.prototype.set = function(index, s) { _tsVector3f_set_index(this.self, index, s); };
tsVector3f.prototype['get'] = tsVector3f.prototype.get = function(index) { return _tsVector3f_get_index(this.self, index); };

tsVector3f.prototype['set_x'] = tsVector3f.prototype.set_x = function(x) { _tsVector3f_set_x(this.self, x); };
tsVector3f.prototype['set_y'] = tsVector3f.prototype.set_y = function(y) { _tsVector3f_set_y(this.self, y); };
tsVector3f.prototype['set_z'] = tsVector3f.prototype.set_z = function(z) { _tsVector3f_set_z(this.self, z); };

tsVector3f.prototype['get_x'] = tsVector3f.prototype.get_x = function() { return _tsVector3f_get_x(this.self); };
tsVector3f.prototype['get_y'] = tsVector3f.prototype.get_y = function() { return _tsVector3f_get_y(this.self); };
tsVector3f.prototype['get_z'] = tsVector3f.prototype.get_z = function() { return _tsVector3f_get_z(this.self); };

Object.defineProperty(tsVector3f.prototype, 'x', { get: tsVector3f.prototype.get_x, set: tsVector3f.prototype.set_x });
Object.defineProperty(tsVector3f.prototype, 'y', { get: tsVector3f.prototype.get_y, set: tsVector3f.prototype.set_y });
Object.defineProperty(tsVector3f.prototype, 'z', { get: tsVector3f.prototype.get_z, set: tsVector3f.prototype.set_z });

/*
 */
tsVector3f.prototype['neg'] = tsVector3f.prototype.neg = function() { return ts_new(tsVector3f, _tsVector3f_neg(this.self)); };

tsVector3f.prototype['mul'] = tsVector3f.prototype.mul = function(v) {
	if(v instanceof tsVector3f) return ts_new(tsVector3f, _tsVector3f_mul(this.self, v.self));
	if(v instanceof tsMatrix4x3f) return ts_new(tsVector3f, _tsMatrix4x3f_mul3t(this.self, v.self));
	if(v instanceof tsMatrix4x4f) return ts_new(tsVector3f, _tsMatrix4x4f_mul3t(this.self, v.self));
	if(v instanceof tsQuaternionf) return ts_new(tsVector3f, _tsQuaternionf_mul3t(this.self, v.self));
	return ts_new(tsVector3f, _tsVector3f_mul1(this.self, v));
};
tsVector3f.prototype['div'] = tsVector3f.prototype.div = function(v) {
	if(v instanceof tsVector3f) return ts_new(tsVector3f, _tsVector3f_div(this.self, v.self));
	return ts_new(tsVector3f, _tsVector3f_div1(this.self, v));
};
tsVector3f.prototype['add'] = tsVector3f.prototype.add = function(v) {
	if(v instanceof tsVector3f) return ts_new(tsVector3f, _tsVector3f_add(this.self, v.self));
	return ts_new(tsVector3f, _tsVector3f_add1(this.self, v));
};
tsVector3f.prototype['sub'] = tsVector3f.prototype.sub = function(v) {
	if(v instanceof tsVector3f) return ts_new(tsVector3f, _tsVector3f_sub(this.self, v.self));
	return ts_new(tsVector3f, _tsVector3f_sub1(this.self, v));
};

tsVector3f.prototype['abs'] = tsVector3f.prototype.abs = function() { return ts_new(tsVector3f, _tsVector3f_abs(this.self)); };

tsVector3f['min'] = tsVector3f.min = function(v0, v1) { return ts_new(tsVector3f, _tsVector3f_min(v0.self, v1.self)); };
tsVector3f['max'] = tsVector3f.max = function(v0, v1) { return ts_new(tsVector3f, _tsVector3f_max(v0.self, v1.self)); };

tsVector3f.prototype['clamp'] = tsVector3f.prototype.clamp = function(v0, v1) { return ts_new(tsVector3f, _tsVector3f_clamp(this.self, v0.self, v1.self)); };
tsVector3f.prototype['saturate'] = tsVector3f.prototype.saturate = function() { return ts_new(tsVector3f, _tsVector3f_saturate(this.self)); };

tsVector3f['dot'] = tsVector3f.dot = function(v0, v1) { return _tsVector3f_dot(v0.self, v1.self); };
tsVector3f['cross'] = tsVector3f.cross = function(v0, v1) { return ts_new(tsVector3f, _tsVector3f_cross(v0.self, v1.self)); };

tsVector3f.prototype['length'] = tsVector3f.prototype.length = function() { return _tsVector3f_length(this.self); };

tsVector3f.prototype['normalize'] = tsVector3f.prototype.normalize = function() { return ts_new(tsVector3f, _tsVector3f_normalize(this.self)); };

tsVector3f['lerp'] = tsVector3f.lerp = function(v0, v1, k) { return ts_new(tsVector3f, _tsVector3f_lerp(v0.self, v1.self, k)); };

tsVector3f['zero'] = tsVector3f.zero = function() { return ts_new(tsVector3f, _tsVector3f_new_v(0.0)); };
tsVector3f['one'] = tsVector3f.one = function() { return ts_new(tsVector3f, _tsVector3f_new_v(1.0)); };

/*****************************************************************************\
 *
 * Vector3d
 *
\*****************************************************************************/

/*
 */
function tsVector3d(x, y, z) {
	if(x instanceof tsVector3d && y === undefined) return ts_bind(tsVector3d, this, _tsVector3d_copy(x.self));
	if(x instanceof tsVector2d && y !== undefined) return ts_bind(tsVector3d, this, _tsVector3d_new_v2d(x.self, y));
	if(x instanceof tsVector4d && y === undefined) return ts_bind(tsVector3d, this, _tsVector3d_new_v4d(x.self));
	if(x instanceof tsVector3i && y !== undefined) return ts_bind(tsVector3d, this, _tsVector3d_new_v3i(x.self, y));
	if(x instanceof tsVector3f && y !== undefined) return ts_bind(tsVector3d, this, _tsVector3d_new_v3f(x.self, y));
	if(x instanceof Array && x.length === 3) return ts_bind(tsVector3d, this, _tsVector3d_new_ad(ts_f64(x, true)));
	if(x !== undefined && y !== undefined && z !== undefined) return ts_bind(tsVector3d, this, _tsVector3d_new_xyz(x, y, z));
	if(x !== undefined && y === undefined) return ts_bind(tsVector3d, this, _tsVector3d_new_v(x));
	if(x === undefined && y === undefined) return ts_bind(tsVector3d, this, _tsVector3d_new());
	throw 'invalid Vector3d() arguments';
}
Module['Vector3d'] = tsVector3d;
tsVector3d.finalizer = new FinalizationRegistry((self) => { _tsVector3d_delete(self); });
tsVector3d.prototype = Object.create(tsVector3d.prototype);
tsVector3d.prototype.constructor = tsVector3d;

tsVector3d.prototype['toBytes'] = tsVector3d.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 24); };
tsVector3d.prototype['toArray'] = tsVector3d.prototype.getArray = function() { return new Float64Array(HEAPF64.buffer, this.self, 3); };
tsVector3d.prototype['toString'] = tsVector3d.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' ' + this.z + ')'; };

/*
 */
tsVector3d.prototype['set'] = tsVector3d.prototype.set = function(index, s) { _tsVector3d_set_index(this.self, index, s); };
tsVector3d.prototype['get'] = tsVector3d.prototype.get = function(index) { return _tsVector3d_get_index(this.self, index); };

tsVector3d.prototype['set_x'] = tsVector3d.prototype.set_x = function(x) { _tsVector3d_set_x(this.self, x); };
tsVector3d.prototype['set_y'] = tsVector3d.prototype.set_y = function(y) { _tsVector3d_set_y(this.self, y); };
tsVector3d.prototype['set_z'] = tsVector3d.prototype.set_z = function(z) { _tsVector3d_set_z(this.self, z); };

tsVector3d.prototype['get_x'] = tsVector3d.prototype.get_x = function() { return _tsVector3d_get_x(this.self); };
tsVector3d.prototype['get_y'] = tsVector3d.prototype.get_y = function() { return _tsVector3d_get_y(this.self); };
tsVector3d.prototype['get_z'] = tsVector3d.prototype.get_z = function() { return _tsVector3d_get_z(this.self); };

Object.defineProperty(tsVector3d.prototype, 'x', { get: tsVector3d.prototype.get_x, set: tsVector3d.prototype.set_x });
Object.defineProperty(tsVector3d.prototype, 'y', { get: tsVector3d.prototype.get_y, set: tsVector3d.prototype.set_y });
Object.defineProperty(tsVector3d.prototype, 'z', { get: tsVector3d.prototype.get_z, set: tsVector3d.prototype.set_z });

/*
 */
tsVector3d.prototype['neg'] = tsVector3d.prototype.neg = function() { return ts_new(tsVector3d, _tsVector3d_neg(this.self)); };

tsVector3d.prototype['mul'] = tsVector3d.prototype.mul = function(v) {
	if(v instanceof tsVector3d) return ts_new(tsVector3d, _tsVector3d_mul(this.self, v.self));
	if(v instanceof tsMatrix4x3d) return ts_new(tsVector3d, _tsMatrix4x3d_mul3t(this.self, v.self));
	if(v instanceof tsMatrix4x4d) return ts_new(tsVector3d, _tsMatrix4x4d_mul3t(this.self, v.self));
	if(v instanceof tsQuaterniond) return ts_new(tsVector3d, _tsQuaterniond_mul3t(this.self, v.self));
	return ts_new(tsVector3d, _tsVector3d_mul1(this.self, v));
};
tsVector3d.prototype['div'] = tsVector3d.prototype.div = function(v) {
	if(v instanceof tsVector3d) return ts_new(tsVector3d, _tsVector3d_div(this.self, v.self));
	return ts_new(tsVector3d, _tsVector3d_div1(this.self, v));
};
tsVector3d.prototype['add'] = tsVector3d.prototype.add = function(v) {
	if(v instanceof tsVector3d) return ts_new(tsVector3d, _tsVector3d_add(this.self, v.self));
	return ts_new(tsVector3d, _tsVector3d_add1(this.self, v));
};
tsVector3d.prototype['sub'] = tsVector3d.prototype.sub = function(v) {
	if(v instanceof tsVector3d) return ts_new(tsVector3d, _tsVector3d_sub(this.self, v.self));
	return ts_new(tsVector3d, _tsVector3d_sub1(this.self, v));
};

tsVector3d.prototype['abs'] = tsVector3d.prototype.abs = function() { return ts_new(tsVector3d, _tsVector3d_abs(this.self)); };

tsVector3d['min'] = tsVector3d.min = function(v0, v1) { return ts_new(tsVector3d, _tsVector3d_min(v0.self, v1.self)); };
tsVector3d['max'] = tsVector3d.max = function(v0, v1) { return ts_new(tsVector3d, _tsVector3d_max(v0.self, v1.self)); };

tsVector3d.prototype['clamp'] = tsVector3d.prototype.clamp = function(v0, v1) { return ts_new(tsVector3d, _tsVector3d_clamp(this.self, v0.self, v1.self)); };
tsVector3d.prototype['saturate'] = tsVector3d.prototype.saturate = function() { return ts_new(tsVector3d, _tsVector3d_saturate(this.self)); };

tsVector3d['dot'] = tsVector3d.dot = function(v0, v1) { return _tsVector3d_dot(v0.self, v1.self); };
tsVector3d['cross'] = tsVector3d.cross = function(v0, v1) { return ts_new(tsVector3d, _tsVector3d_cross(v0.self, v1.self)); };

tsVector3d.prototype['length'] = tsVector3d.prototype.length = function() { return _tsVector3d_length(this.self); };

tsVector3d.prototype['normalize'] = tsVector3d.prototype.normalize = function() { return ts_new(tsVector3d, _tsVector3d_normalize(this.self)); };

tsVector3d['lerp'] = tsVector3d.lerp = function(v0, v1, k) { return ts_new(tsVector3d, _tsVector3d_lerp(v0.self, v1.self, k)); };

tsVector3d['zero'] = tsVector3d.zero = function() { return ts_new(tsVector3d, _tsVector3d_new_v(0.0)); };
tsVector3d['one'] = tsVector3d.one = function() { return ts_new(tsVector3d, _tsVector3d_new_v(1.0)); };

/*****************************************************************************\
 *
 * Vector4i
 *
\*****************************************************************************/

/*
 */
function tsVector4i(x, y, z, w) {
	if(x instanceof tsVector4i && y === undefined && z === undefined) return ts_bind(tsVector4i, this, _tsVector4i_copy(x.self));
	if(x instanceof tsVector2i && y !== undefined && z !== undefined) return ts_bind(tsVector4i, this, _tsVector4i_new_v2i(x.self, y, z));
	if(x instanceof tsVector3i && y !== undefined && z === undefined) return ts_bind(tsVector4i, this, _tsVector4i_new_v3i(x.self, y));
	if(x instanceof tsVector4f && y !== undefined && z !== undefined) return ts_bind(tsVector4i, this, _tsVector4i_new_v4f(x.self, y, z));
	if(x instanceof tsVector4d && y !== undefined && z !== undefined) return ts_bind(tsVector4i, this, _tsVector4i_new_v4d(x.self, y, z));
	if(x instanceof Array && x.length === 4) return ts_bind(tsVector4i, this, _tsVector4i_new_ai(ts_i32(x, true)));
	if(x !== undefined && y !== undefined && z !== undefined && w !== undefined) return ts_bind(tsVector4i, this, _tsVector4i_new_xyzw(x, y, z, w));
	if(x !== undefined && y === undefined) return ts_bind(tsVector4i, this, _tsVector4i_new_v(x));
	if(x === undefined && y === undefined) return ts_bind(tsVector4i, this, _tsVector4i_new());
	throw 'invalid Vector4i() arguments';
}
Module['Vector4i'] = tsVector4i;
tsVector4i.finalizer = new FinalizationRegistry((self) => { _tsVector4i_delete(self); });
tsVector4i.prototype = Object.create(tsVector4i.prototype);
tsVector4i.prototype.constructor = tsVector4i;

tsVector4i.prototype['toBytes'] = tsVector4i.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 16); };
tsVector4i.prototype['toArray'] = tsVector4i.prototype.getArray = function() { return new Int32Array(HEAP32.buffer, this.self, 4); };
tsVector4i.prototype['toString'] = tsVector4i.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' ' + this.z + ' ' + this.w + ')'; };

/*
 */
tsVector4i.prototype['set'] = tsVector4i.prototype.set = function(index, s) { _tsVector4i_set_index(this.self, index, s); };
tsVector4i.prototype['get'] = tsVector4i.prototype.get = function(index) { return _tsVector4i_get_index(this.self, index); };

tsVector4i.prototype['set_x'] = tsVector4i.prototype.set_x = function(x) { _tsVector4i_set_x(this.self, x); };
tsVector4i.prototype['set_y'] = tsVector4i.prototype.set_y = function(y) { _tsVector4i_set_y(this.self, y); };
tsVector4i.prototype['set_z'] = tsVector4i.prototype.set_z = function(z) { _tsVector4i_set_z(this.self, z); };
tsVector4i.prototype['set_w'] = tsVector4i.prototype.set_w = function(w) { _tsVector4i_set_w(this.self, w); };

tsVector4i.prototype['get_x'] = tsVector4i.prototype.get_x = function() { return _tsVector4i_get_x(this.self); };
tsVector4i.prototype['get_y'] = tsVector4i.prototype.get_y = function() { return _tsVector4i_get_y(this.self); };
tsVector4i.prototype['get_z'] = tsVector4i.prototype.get_z = function() { return _tsVector4i_get_z(this.self); };
tsVector4i.prototype['get_w'] = tsVector4i.prototype.get_w = function() { return _tsVector4i_get_w(this.self); };

Object.defineProperty(tsVector4i.prototype, 'x', { get: tsVector4i.prototype.get_x, set: tsVector4i.prototype.set_x });
Object.defineProperty(tsVector4i.prototype, 'y', { get: tsVector4i.prototype.get_y, set: tsVector4i.prototype.set_y });
Object.defineProperty(tsVector4i.prototype, 'z', { get: tsVector4i.prototype.get_z, set: tsVector4i.prototype.set_z });
Object.defineProperty(tsVector4i.prototype, 'w', { get: tsVector4i.prototype.get_w, set: tsVector4i.prototype.set_w });

/*
 */
tsVector4i.prototype['neg'] = tsVector4i.prototype.neg = function() { return ts_new(tsVector4i, _tsVector4i_neg(this.self)); };

tsVector4i.prototype['mul'] = tsVector4i.prototype.mul = function(v) {
	if(v instanceof tsVector4i) return ts_new(tsVector4i, _tsVector4i_mul(this.self, v.self));
	return ts_new(tsVector4i, _tsVector4i_mul1(this.self, v));
};
tsVector4i.prototype['div'] = tsVector4i.prototype.div = function(v) {
	if(v instanceof tsVector4i) return ts_new(tsVector4i, _tsVector4i_div(this.self, v.self));
	return ts_new(tsVector4i, _tsVector4i_div1(this.self, v));
};
tsVector4i.prototype['add'] = tsVector4i.prototype.add = function(v) {
	if(v instanceof tsVector4i) return ts_new(tsVector4i, _tsVector4i_add(this.self, v.self));
	return ts_new(tsVector4i, _tsVector4i_add1(this.self, v));
};
tsVector4i.prototype['sub'] = tsVector4i.prototype.sub = function(v) {
	if(v instanceof tsVector4i) return ts_new(tsVector4i, _tsVector4i_sub(this.self, v.self));
	return ts_new(tsVector4i, _tsVector4i_sub1(this.self, v));
};

tsVector4i.prototype['and'] = tsVector4i.prototype.and = function(v) {
	if(v instanceof tsVector4i) return ts_new(tsVector4i, _tsVector4i_and(this.self, v.self));
	return ts_new(tsVector4i, _tsVector4i_and1(this.self, v));
};
tsVector4i.prototype['or'] = tsVector4i.prototype.or = function(v) {
	if(v instanceof tsVector4i) return ts_new(tsVector4i, _tsVector4i_or(this.self, v.self));
	return ts_new(tsVector4i, _tsVector4i_or1(this.self, v));
};
tsVector4i.prototype['xor'] = tsVector4i.prototype.xor = function(v) {
	if(v instanceof tsVector4i) return ts_new(tsVector4i, _tsVector4i_xor(this.self, v.self));
	return ts_new(tsVector4i, _tsVector4i_xor1(this.self, v));
};
tsVector4i.prototype['shl'] = tsVector4i.prototype.shl = function(v) {
	return ts_new(tsVector4i, _tsVector4i_shl1(this.self, v));
};
tsVector4i.prototype['shr'] = tsVector4i.prototype.shr = function(v) {
	return ts_new(tsVector4i, _tsVector4i_shr1(this.self, v));
};

tsVector4i.prototype['abs'] = tsVector4i.prototype.abs = function() { return ts_new(tsVector4i, _tsVector4i_abs(this.self)); };

tsVector4i['min'] = tsVector4i.min = function(v0, v1) { return ts_new(tsVector4i, _tsVector4i_min(v0.self, v1.self)); };
tsVector4i['max'] = tsVector4i.max = function(v0, v1) { return ts_new(tsVector4i, _tsVector4i_max(v0.self, v1.self)); };

tsVector4i.prototype['clamp'] = tsVector4i.prototype.clamp = function(v0, v1) { return ts_new(tsVector4i, _tsVector4i_clamp(this.self, v0.self, v1.self)); };

tsVector4i['zero'] = tsVector4i.zero = function() { return ts_new(tsVector4i, _tsVector4i_new_v(0)); };
tsVector4i['one'] = tsVector4i.one = function() { return ts_new(tsVector4i, _tsVector4i_new_v(1)); };

/*****************************************************************************\
 *
 * Vector4f
 *
\*****************************************************************************/

/*
 */
function tsVector4f(x, y, z, w) {
	if(x instanceof tsVector4f && y === undefined && z === undefined) return ts_bind(tsVector4f, this, _tsVector4f_copy(x.self));
	if(x instanceof tsVector2f && y !== undefined && z !== undefined) return ts_bind(tsVector4f, this, _tsVector4f_new_v2f(x.self, y, z));
	if(x instanceof tsVector3f && y !== undefined && z === undefined) return ts_bind(tsVector4f, this, _tsVector4f_new_v3f(x.self, y));
	if(x instanceof tsVector4i && y !== undefined && z !== undefined) return ts_bind(tsVector4f, this, _tsVector4f_new_v4i(x.self, y, z));
	if(x instanceof tsVector4d && y !== undefined && z !== undefined) return ts_bind(tsVector4f, this, _tsVector4f_new_v4d(x.self, y, z));
	if(x instanceof Array && x.length === 4) return ts_bind(tsVector4f, this, _tsVector4f_new_af(ts_f32(x, true)));
	if(x !== undefined && y !== undefined && z !== undefined && w !== undefined) return ts_bind(tsVector4f, this, _tsVector4f_new_xyzw(x, y, z, w));
	if(x !== undefined && y === undefined) return ts_bind(tsVector4f, this, _tsVector4f_new_v(x));
	if(x === undefined && y === undefined) return ts_bind(tsVector4f, this, _tsVector4f_new());
	throw 'invalid Vector4f() arguments';
}
Module['Vector4f'] = tsVector4f;
tsVector4f.finalizer = new FinalizationRegistry((self) => { _tsVector4f_delete(self); });
tsVector4f.prototype = Object.create(tsVector4f.prototype);
tsVector4f.prototype.constructor = tsVector4f;

tsVector4f.prototype['toBytes'] = tsVector4f.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 16); };
tsVector4f.prototype['toArray'] = tsVector4f.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 4); };
tsVector4f.prototype['toString'] = tsVector4f.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' ' + this.z + ' ' + this.w + ')'; };

/*
 */
tsVector4f.prototype['set'] = tsVector4f.prototype.set = function(index, s) { _tsVector4f_set_index(this.self, index, s); };
tsVector4f.prototype['get'] = tsVector4f.prototype.get = function(index) { return _tsVector4f_get_index(this.self, index); };

tsVector4f.prototype['set_x'] = tsVector4f.prototype.set_x = function(x) { _tsVector4f_set_x(this.self, x); };
tsVector4f.prototype['set_y'] = tsVector4f.prototype.set_y = function(y) { _tsVector4f_set_y(this.self, y); };
tsVector4f.prototype['set_z'] = tsVector4f.prototype.set_z = function(z) { _tsVector4f_set_z(this.self, z); };
tsVector4f.prototype['set_w'] = tsVector4f.prototype.set_w = function(w) { _tsVector4f_set_w(this.self, w); };

tsVector4f.prototype['get_x'] = tsVector4f.prototype.get_x = function() { return _tsVector4f_get_x(this.self); };
tsVector4f.prototype['get_y'] = tsVector4f.prototype.get_y = function() { return _tsVector4f_get_y(this.self); };
tsVector4f.prototype['get_z'] = tsVector4f.prototype.get_z = function() { return _tsVector4f_get_z(this.self); };
tsVector4f.prototype['get_w'] = tsVector4f.prototype.get_w = function() { return _tsVector4f_get_w(this.self); };

Object.defineProperty(tsVector4f.prototype, 'x', { get: tsVector4f.prototype.get_x, set: tsVector4f.prototype.set_x });
Object.defineProperty(tsVector4f.prototype, 'y', { get: tsVector4f.prototype.get_y, set: tsVector4f.prototype.set_y });
Object.defineProperty(tsVector4f.prototype, 'z', { get: tsVector4f.prototype.get_z, set: tsVector4f.prototype.set_z });
Object.defineProperty(tsVector4f.prototype, 'w', { get: tsVector4f.prototype.get_w, set: tsVector4f.prototype.set_w });

/*
 */
tsVector4f.prototype['neg'] = tsVector4f.prototype.neg = function() { return ts_new(tsVector4f, _tsVector4f_neg(this.self)); };

tsVector4f.prototype['mul'] = tsVector4f.prototype.mul = function(v) {
	if(v instanceof tsVector4f) return ts_new(tsVector4f, _tsVector4f_mul(this.self, v.self));
	if(v instanceof tsMatrix4x3f) return ts_new(tsVector4f, _tsMatrix4x3f_mul4t(this.self, v.self));
	if(v instanceof tsMatrix4x4f) return ts_new(tsVector4f, _tsMatrix4x4f_mul4t(this.self, v.self));
	if(v instanceof tsQuaternionf) return ts_new(tsVector4f, _tsQuaternionf_mul4t(this.self, v.self));
	return ts_new(tsVector4f, _tsVector4f_mul1(this.self, v));
};
tsVector4f.prototype['div'] = tsVector4f.prototype.div = function(v) {
	if(v instanceof tsVector4f) return ts_new(tsVector4f, _tsVector4f_div(this.self, v.self));
	return ts_new(tsVector4f, _tsVector4f_div1(this.self, v));
};
tsVector4f.prototype['add'] = tsVector4f.prototype.add = function(v) {
	if(v instanceof tsVector4f) return ts_new(tsVector4f, _tsVector4f_add(this.self, v.self));
	return ts_new(tsVector4f, _tsVector4f_add1(this.self, v));
};
tsVector4f.prototype['sub'] = tsVector4f.prototype.sub = function(v) {
	if(v instanceof tsVector4f) return ts_new(tsVector4f, _tsVector4f_sub(this.self, v.self));
	return ts_new(tsVector4f, _tsVector4f_sub1(this.self, v));
};

tsVector4f.prototype['abs'] = tsVector4f.prototype.abs = function() { return ts_new(tsVector4f, _tsVector4f_abs(this.self)); };

tsVector4f['min'] = tsVector4f.min = function(v0, v1) { return ts_new(tsVector4f, _tsVector4f_min(v0.self, v1.self)); };
tsVector4f['max'] = tsVector4f.max = function(v0, v1) { return ts_new(tsVector4f, _tsVector4f_max(v0.self, v1.self)); };

tsVector4f.prototype['clamp'] = tsVector4f.prototype.clamp = function(v0, v1) { return ts_new(tsVector4f, _tsVector4f_clamp(this.self, v0.self, v1.self)); };
tsVector4f.prototype['saturate'] = tsVector4f.prototype.saturate = function() { return ts_new(tsVector4f, _tsVector4f_saturate(this.self)); };

tsVector4f['dot'] = tsVector4f.dot = function(v0, v1) { return _tsVector4f_dot(v0.self, v1.self); };
tsVector4f['dot33'] = tsVector4f.dot33 = function(v0, v1) { return _tsVector4f_dot33(v0.self, v1.self); };
tsVector4f['dot43'] = tsVector4f.dot43 = function(v0, v1) { return _tsVector4f_dot43(v0.self, v1.self); };
tsVector4f['dot34'] = tsVector4f.dot34 = function(v0, v1) { return _tsVector4f_dot34(v0.self, v1.self); };
tsVector4f['cross'] = tsVector4f.cross = function(v0, v1) { return ts_new(tsVector4f, _tsVector4f_cross(v0.self, v1.self)); };

tsVector4f.prototype['length'] = tsVector4f.prototype.length = function() { return _tsVector4f_length(this.self); };
tsVector4f.prototype['length3'] = tsVector4f.prototype.length3 = function() { return _tsVector4f_length3(this.self); };

tsVector4f.prototype['normalize'] = tsVector4f.prototype.normalize = function() { return ts_new(tsVector4f, _tsVector4f_normalize(this.self)); };
tsVector4f.prototype['normalize3'] = tsVector4f.prototype.normalize3 = function() { return ts_new(tsVector4f, _tsVector4f_normalize3(this.self)); };

tsVector4f['lerp'] = tsVector4f.lerp = function(v0, v1, k) { return ts_new(tsVector4f, _tsVector4f_lerp(v0.self, v1.self, k)); };

tsVector4f['zero'] = tsVector4f.zero = function() { return ts_new(tsVector4f, _tsVector4f_new_v(0.0)); };
tsVector4f['one'] = tsVector4f.one = function() { return ts_new(tsVector4f, _tsVector4f_new_v(1.0)); };

/*****************************************************************************\
 *
 * Vector4d
 *
\*****************************************************************************/

/*
 */
function tsVector4d(x, y, z, w) {
	if(x instanceof tsVector4d && y === undefined && z === undefined) return ts_bind(tsVector4d, this, _tsVector4d_copy(x.self));
	if(x instanceof tsVector2d && y !== undefined && z !== undefined) return ts_bind(tsVector4d, this, _tsVector4d_new_v2d(x.self, y, z));
	if(x instanceof tsVector3d && y !== undefined && z === undefined) return ts_bind(tsVector4d, this, _tsVector4d_new_v3d(x.self, y));
	if(x instanceof tsVector4i && y !== undefined && z !== undefined) return ts_bind(tsVector4d, this, _tsVector4d_new_v4i(x.self, y, z));
	if(x instanceof tsVector4f && y !== undefined && z !== undefined) return ts_bind(tsVector4d, this, _tsVector4d_new_v4f(x.self, y, z));
	if(x instanceof Array && x.length === 4) return ts_bind(tsVector4d, this, _tsVector4d_new_ad(ts_f64(x, true)));
	if(x !== undefined && y !== undefined && z !== undefined && w !== undefined) return ts_bind(tsVector4d, this, _tsVector4d_new_xyzw(x, y, z, w));
	if(x !== undefined && y === undefined) return ts_bind(tsVector4d, this, _tsVector4d_new_v(x));
	if(x === undefined && y === undefined) return ts_bind(tsVector4d, this, _tsVector4d_new());
	throw 'invalid Vector4d() arguments';
}
Module['Vector4d'] = tsVector4d;
tsVector4d.finalizer = new FinalizationRegistry((self) => { _tsVector4d_delete(self); });
tsVector4d.prototype = Object.create(tsVector4d.prototype);
tsVector4d.prototype.constructor = tsVector4d;

tsVector4d.prototype['toBytes'] = tsVector4d.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 32); };
tsVector4d.prototype['toArray'] = tsVector4d.prototype.getArray = function() { return new Float64Array(HEAPF64.buffer, this.self, 4); };
tsVector4d.prototype['toString'] = tsVector4d.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' ' + this.z + ' ' + this.w + ')'; };

/*
 */
tsVector4d.prototype['set'] = tsVector4d.prototype.set = function(index, s) { _tsVector4d_set_index(this.self, index, s); };
tsVector4d.prototype['get'] = tsVector4d.prototype.get = function(index) { return _tsVector4d_get_index(this.self, index); };

tsVector4d.prototype['set_x'] = tsVector4d.prototype.set_x = function(x) { _tsVector4d_set_x(this.self, x); };
tsVector4d.prototype['set_y'] = tsVector4d.prototype.set_y = function(y) { _tsVector4d_set_y(this.self, y); };
tsVector4d.prototype['set_z'] = tsVector4d.prototype.set_z = function(z) { _tsVector4d_set_z(this.self, z); };
tsVector4d.prototype['set_w'] = tsVector4d.prototype.set_w = function(w) { _tsVector4d_set_w(this.self, w); };

tsVector4d.prototype['get_x'] = tsVector4d.prototype.get_x = function() { return _tsVector4d_get_x(this.self); };
tsVector4d.prototype['get_y'] = tsVector4d.prototype.get_y = function() { return _tsVector4d_get_y(this.self); };
tsVector4d.prototype['get_z'] = tsVector4d.prototype.get_z = function() { return _tsVector4d_get_z(this.self); };
tsVector4d.prototype['get_w'] = tsVector4d.prototype.get_w = function() { return _tsVector4d_get_w(this.self); };

Object.defineProperty(tsVector4d.prototype, 'x', { get: tsVector4d.prototype.get_x, set: tsVector4d.prototype.set_x });
Object.defineProperty(tsVector4d.prototype, 'y', { get: tsVector4d.prototype.get_y, set: tsVector4d.prototype.set_y });
Object.defineProperty(tsVector4d.prototype, 'z', { get: tsVector4d.prototype.get_z, set: tsVector4d.prototype.set_z });
Object.defineProperty(tsVector4d.prototype, 'w', { get: tsVector4d.prototype.get_w, set: tsVector4d.prototype.set_w });

/*
 */
tsVector4d.prototype['neg'] = tsVector4d.prototype.neg = function() { return ts_new(tsVector4d, _tsVector4d_neg(this.self)); };

tsVector4d.prototype['mul'] = tsVector4d.prototype.mul = function(v) {
	if(v instanceof tsVector4d) return ts_new(tsVector4d, _tsVector4d_mul(this.self, v.self));
	if(v instanceof tsMatrix4x3d) return ts_new(tsVector4d, _tsMatrix4x3d_mul4t(this.self, v.self));
	if(v instanceof tsMatrix4x4d) return ts_new(tsVector4d, _tsMatrix4x4d_mul4t(this.self, v.self));
	if(v instanceof tsQuaterniond) return ts_new(tsVector4d, _tsQuaterniond_mul4t(this.self, v.self));
	return ts_new(tsVector4d, _tsVector4d_mul1(this.self, v));
};
tsVector4d.prototype['div'] = tsVector4d.prototype.div = function(v) {
	if(v instanceof tsVector4d) return ts_new(tsVector4d, _tsVector4d_div(this.self, v.self));
	return ts_new(tsVector4d, _tsVector4d_div1(this.self, v));
};
tsVector4d.prototype['add'] = tsVector4d.prototype.add = function(v) {
	if(v instanceof tsVector4d) return ts_new(tsVector4d, _tsVector4d_add(this.self, v.self));
	return ts_new(tsVector4d, _tsVector4d_add1(this.self, v));
};
tsVector4d.prototype['sub'] = tsVector4d.prototype.sub = function(v) {
	if(v instanceof tsVector4d) return ts_new(tsVector4d, _tsVector4d_sub(this.self, v.self));
	return ts_new(tsVector4d, _tsVector4d_sub1(this.self, v));
};

tsVector4d.prototype['abs'] = tsVector4d.prototype.abs = function() { return ts_new(tsVector4d, _tsVector4d_abs(this.self)); };

tsVector4d['min'] = tsVector4d.min = function(v0, v1) { return ts_new(tsVector4d, _tsVector4d_min(v0.self, v1.self)); };
tsVector4d['max'] = tsVector4d.max = function(v0, v1) { return ts_new(tsVector4d, _tsVector4d_max(v0.self, v1.self)); };

tsVector4d.prototype['clamp'] = tsVector4d.prototype.clamp = function(v0, v1) { return ts_new(tsVector4d, _tsVector4d_clamp(this.self, v0.self, v1.self)); };
tsVector4d.prototype['saturate'] = tsVector4d.prototype.saturate = function() { return ts_new(tsVector4d, _tsVector4d_saturate(this.self)); };

tsVector4d['dot'] = tsVector4d.dot = function(v0, v1) { return _tsVector4d_dot(v0.self, v1.self); };
tsVector4d['dot33'] = tsVector4d.dot33 = function(v0, v1) { return _tsVector4d_dot33(v0.self, v1.self); };
tsVector4d['dot43'] = tsVector4d.dot43 = function(v0, v1) { return _tsVector4d_dot43(v0.self, v1.self); };
tsVector4d['dot34'] = tsVector4d.dot34 = function(v0, v1) { return _tsVector4d_dot34(v0.self, v1.self); };
tsVector4d['cross'] = tsVector4d.cross = function(v0, v1) { return ts_new(tsVector4d, _tsVector4d_cross(v0.self, v1.self)); };

tsVector4d.prototype['length'] = tsVector4d.prototype.length = function() { return _tsVector4d_length(this.self); };
tsVector4d.prototype['length3'] = tsVector4d.prototype.length3 = function() { return _tsVector4d_length3(this.self); };

tsVector4d.prototype['normalize'] = tsVector4d.prototype.normalize = function() { return ts_new(tsVector4d, _tsVector4d_normalize(this.self)); };
tsVector4d.prototype['normalize3'] = tsVector4d.prototype.normalize3 = function() { return ts_new(tsVector4d, _tsVector4d_normalize3(this.self)); };

tsVector4d['lerp'] = tsVector4d.lerp = function(v0, v1, k) { return ts_new(tsVector4d, _tsVector4d_lerp(v0.self, v1.self, k)); };

tsVector4d['zero'] = tsVector4d.zero = function() { return ts_new(tsVector4d, _tsVector4d_new_v(0.0)); };
tsVector4d['one'] = tsVector4d.one = function() { return ts_new(tsVector4d, _tsVector4d_new_v(1.0)); };

/*****************************************************************************\
 *
 * Matrix3x2f
 *
\*****************************************************************************/

/*
 */
function tsMatrix3x2f(r0, r1, row_major) {
	if(r0 instanceof tsMatrix3x2f) return ts_bind(tsMatrix3x2f, this, _tsMatrix3x2f_copy(r0.self));
	if(r0 instanceof tsMatrix3x2d) return ts_bind(tsMatrix3x2f, this, _tsMatrix3x2f_new_m3x2d(r0.self));
	if(r0 instanceof Array && r1 !== undefined && row_major !== undefined) return ts_bind(tsMatrix3x2f, this, _tsMatrix3x2f_new_af(ts_f32(r0, true), r1, row_major));
	if(r0 instanceof Array && r1 !== undefined) return ts_bind(tsMatrix3x2f, this, _tsMatrix3x2f_new_af(ts_f32(r0, true), r1, true));
	if(r0 instanceof Array) return ts_bind(tsMatrix3x2f, this, _tsMatrix3x2f_new_af(ts_f32(r0, true), r0.length, true));
	if(r0 !== undefined && r1 !== undefined) return ts_bind(tsMatrix3x2f, this, _tsMatrix3x2f_new_r(r0.self, r1.self));
	if(r0 === undefined && r1 === undefined) return ts_bind(tsMatrix3x2f, this, _tsMatrix3x2f_new());
	throw 'invalid Matrix3x2f() arguments';
}
Module['Matrix3x2f'] = tsMatrix3x2f;
tsMatrix3x2f.finalizer = new FinalizationRegistry((self) => { _tsMatrix3x2f_delete(self); });
tsMatrix3x2f.prototype = Object.create(tsMatrix3x2f.prototype);
tsMatrix3x2f.prototype.constructor = tsMatrix3x2f;

tsMatrix3x2f.prototype['toBytes'] = tsMatrix3x2f.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 24); };
tsMatrix3x2f.prototype['toArray'] = tsMatrix3x2f.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 6); };
tsMatrix3x2f.prototype['toString'] = tsMatrix3x2f.prototype.toString = function() { return this.row_0 + ' : ' + this.row_1; };

/*
 */
tsMatrix3x2f.prototype['set'] = tsMatrix3x2f.prototype.set = function(index, v) { _tsMatrix3x2f_set_index(this.self, index, v.self); };
tsMatrix3x2f.prototype['get'] = tsMatrix3x2f.prototype.get = function(index) { return ts_new(tsVector3f, _tsMatrix3x2f_get_index(this.self, index)); };

tsMatrix3x2f.prototype['set_row_0'] = tsMatrix3x2f.prototype.set_row_0 = function(r0) { _tsMatrix3x2f_set_row_0(this.self, r0); };
tsMatrix3x2f.prototype['set_row_1'] = tsMatrix3x2f.prototype.set_row_1 = function(r1) { _tsMatrix3x2f_set_row_1(this.self, r1); };

tsMatrix3x2f.prototype['get_row_0'] = tsMatrix3x2f.prototype.get_row_0 = function() { return ts_new(tsVector3f, _tsMatrix3x2f_get_row_0(this.self)); };
tsMatrix3x2f.prototype['get_row_1'] = tsMatrix3x2f.prototype.get_row_1 = function() { return ts_new(tsVector3f, _tsMatrix3x2f_get_row_1(this.self)); };

Object.defineProperty(tsMatrix3x2f.prototype, 'row_0', { get: tsMatrix3x2f.prototype.get_row_0, set: tsMatrix3x2f.prototype.set_row_0 });
Object.defineProperty(tsMatrix3x2f.prototype, 'row_1', { get: tsMatrix3x2f.prototype.get_row_1, set: tsMatrix3x2f.prototype.set_row_1 });

/*
 */
tsMatrix3x2f['scale'] = tsMatrix3x2f.scale = function(x, y) { return ts_new(tsMatrix3x2f, _tsMatrix3x2f_scale(x, y)); };
tsMatrix3x2f['translate'] = tsMatrix3x2f.translate = function(x, y) { return ts_new(tsMatrix3x2f, _tsMatrix3x2f_translate(x, y)); };
tsMatrix3x2f['rotate'] = tsMatrix3x2f.rotate = function(angle) { return ts_new(tsMatrix3x2f, _tsMatrix3x2f_rotate(angle)); };

tsMatrix3x2f.prototype['mul'] = tsMatrix3x2f.prototype.mul = function(v) {
	if(v instanceof tsMatrix3x2f) return ts_new(tsMatrix3x2f, _tsMatrix3x2f_mul(this.self, v.self));
	if(v instanceof tsVector2f) return ts_new(tsVector2f, _tsMatrix3x2f_mul2(this.self, v.self));
	throw 'invalid Matrix3x2f() arguments';
};

tsMatrix3x2f.prototype['transpose'] = tsMatrix3x2f.prototype.transpose = function() { return ts_new(tsMatrix3x2f, _tsMatrix3x2f_transpose(this.self)); };
tsMatrix3x2f.prototype['inverse'] = tsMatrix3x2f.prototype.inverse = function() { return ts_new(tsMatrix3x2f, _tsMatrix3x2f_inverse(this.self)); };

tsMatrix3x2f['identity'] = tsMatrix3x2f.identity = function() { return ts_new(tsMatrix3x2f, _tsMatrix3x2f_identity()); };

/*****************************************************************************\
 *
 * Matrix3x2d
 *
\*****************************************************************************/

/*
 */
function tsMatrix3x2d(r0, r1, row_major) {
	if(r0 instanceof tsMatrix3x2d) return ts_bind(tsMatrix3x2d, this, _tsMatrix3x2d_copy(r0.self));
	if(r0 instanceof tsMatrix3x2f) return ts_bind(tsMatrix3x2d, this, _tsMatrix3x2d_new_m3x2f(r0.self));
	if(r0 instanceof Array && r1 !== undefined && row_major !== undefined) return ts_bind(tsMatrix3x2d, this, _tsMatrix3x2d_new_ad(ts_f64(r0, true), r1, row_major));
	if(r0 instanceof Array && r1 !== undefined) return ts_bind(tsMatrix3x2d, this, _tsMatrix3x2d_new_ad(ts_f64(r0, true), r1, true));
	if(r0 instanceof Array) return ts_bind(tsMatrix3x2d, this, _tsMatrix3x2d_new_ad(ts_f64(r0, true), r0.length, true));
	if(r0 !== undefined && r1 !== undefined) return ts_bind(tsMatrix3x2d, this, _tsMatrix3x2d_new_r(r0.self, r1.self));
	if(r0 === undefined && r1 === undefined) return ts_bind(tsMatrix3x2d, this, _tsMatrix3x2d_new());
	throw 'invalid Matrix3x2d() arguments';
}
Module['Matrix3x2d'] = tsMatrix3x2d;
tsMatrix3x2d.finalizer = new FinalizationRegistry((self) => { _tsMatrix3x2d_delete(self); });
tsMatrix3x2d.prototype = Object.create(tsMatrix3x2d.prototype);
tsMatrix3x2d.prototype.constructor = tsMatrix3x2d;

tsMatrix3x2d.prototype['toBytes'] = tsMatrix3x2d.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 48); };
tsMatrix3x2d.prototype['toArray'] = tsMatrix3x2d.prototype.getArray = function() { return new Float64Array(HEAPF64.buffer, this.self, 6); };
tsMatrix3x2d.prototype['toString'] = tsMatrix3x2d.prototype.toString = function() { return this.row_0 + ' : ' + this.row_1; };

/*
 */
tsMatrix3x2d.prototype['set'] = tsMatrix3x2d.prototype.set = function(index, v) { _tsMatrix3x2d_set_index(this.self, index, v.self); };
tsMatrix3x2d.prototype['get'] = tsMatrix3x2d.prototype.get = function(index) { return ts_new(tsVector3d, _tsMatrix3x2d_get_index(this.self, index)); };

tsMatrix3x2d.prototype['set_row_0'] = tsMatrix3x2d.prototype.set_row_0 = function(r0) { _tsMatrix3x2d_set_row_0(this.self, r0); };
tsMatrix3x2d.prototype['set_row_1'] = tsMatrix3x2d.prototype.set_row_1 = function(r1) { _tsMatrix3x2d_set_row_1(this.self, r1); };

tsMatrix3x2d.prototype['get_row_0'] = tsMatrix3x2d.prototype.get_row_0 = function() { return ts_new(tsVector3d, _tsMatrix3x2d_get_row_0(this.self)); };
tsMatrix3x2d.prototype['get_row_1'] = tsMatrix3x2d.prototype.get_row_1 = function() { return ts_new(tsVector3d, _tsMatrix3x2d_get_row_1(this.self)); };

Object.defineProperty(tsMatrix3x2d.prototype, 'row_0', { get: tsMatrix3x2d.prototype.get_row_0, set: tsMatrix3x2d.prototype.set_row_0 });
Object.defineProperty(tsMatrix3x2d.prototype, 'row_1', { get: tsMatrix3x2d.prototype.get_row_1, set: tsMatrix3x2d.prototype.set_row_1 });

/*
 */
tsMatrix3x2d['scale'] = tsMatrix3x2d.scale = function(x, y) { return ts_new(tsMatrix3x2d, _tsMatrix3x2d_scale(x, y)); };
tsMatrix3x2d['translate'] = tsMatrix3x2d.translate = function(x, y) { return ts_new(tsMatrix3x2d, _tsMatrix3x2d_translate(x, y)); };
tsMatrix3x2d['rotate'] = tsMatrix3x2d.rotate = function(angle) { return ts_new(tsMatrix3x2d, _tsMatrix3x2d_rotate(angle)); };

tsMatrix3x2d.prototype['mul'] = tsMatrix3x2d.prototype.mul = function(v) {
	if(v instanceof tsMatrix3x2d) return ts_new(tsMatrix3x2d, _tsMatrix3x2d_mul(this.self, v.self));
	if(v instanceof tsVector2d) return ts_new(tsVector2d, _tsMatrix3x2d_mul2(this.self, v.self));
	throw 'invalid Matrix3x2d() arguments';
};

tsMatrix3x2d.prototype['transpose'] = tsMatrix3x2d.prototype.transpose = function() { return ts_new(tsMatrix3x2d, _tsMatrix3x2d_transpose(this.self)); };
tsMatrix3x2d.prototype['inverse'] = tsMatrix3x2d.prototype.inverse = function() { return ts_new(tsMatrix3x2d, _tsMatrix3x2d_inverse(this.self)); };

tsMatrix3x2d['identity'] = tsMatrix3x2d.identity = function() { return ts_new(tsMatrix3x2d, _tsMatrix3x2d_identity()); };

/*****************************************************************************\
 *
 * Matrix4x3f
 *
\*****************************************************************************/

/*
 */
function tsMatrix4x3f(r0, r1, r2) {
	if(r0 instanceof tsMatrix4x3f) return ts_bind(tsMatrix4x3f, this, _tsMatrix4x3f_copy(r0.self));
	if(r0 instanceof tsMatrix4x3d) return ts_bind(tsMatrix4x3f, this, _tsMatrix4x3f_new_m4x3d(r0.self));
	if(r0 instanceof tsMatrix4x4f) return ts_bind(tsMatrix4x3f, this, _tsMatrix4x3f_new_m4x4f(r0.self));
	if(r0 instanceof tsQuaternionf) return ts_bind(tsMatrix4x3f, this, _tsMatrix4x3f_new_qf(r0.self));
	if(r0 instanceof Array && r1 !== undefined && r2 !== undefined) return ts_bind(tsMatrix4x3f, this, _tsMatrix4x3f_new_af(ts_f32(r0, true), r1, r2));
	if(r0 instanceof Array && r1 !== undefined) return ts_bind(tsMatrix4x3f, this, _tsMatrix4x3f_new_af(ts_f32(r0, true), r1, true));
	if(r0 instanceof Array) return ts_bind(tsMatrix4x3f, this, _tsMatrix4x3f_new_af(ts_f32(r0, true), r0.length, true));
	if(r0 !== undefined && r1 !== undefined && r2 !== undefined) return ts_bind(tsMatrix4x3f, this, _tsMatrix4x3f_new_r(r0.self, r1.self, r2.self));
	if(r0 === undefined && r1 === undefined && r2 === undefined) return ts_bind(tsMatrix4x3f, this, _tsMatrix4x3f_new());
	throw 'invalid Matrix4x3f() arguments';
}
Module['Matrix4x3f'] = tsMatrix4x3f;
tsMatrix4x3f.finalizer = new FinalizationRegistry((self) => { _tsMatrix4x3f_delete(self); });
tsMatrix4x3f.prototype = Object.create(tsMatrix4x3f.prototype);
tsMatrix4x3f.prototype.constructor = tsMatrix4x3f;

tsMatrix4x3f.prototype['toBytes'] = tsMatrix4x3f.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 48); };
tsMatrix4x3f.prototype['toArray'] = tsMatrix4x3f.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 12); };
tsMatrix4x3f.prototype['toString'] = tsMatrix4x3f.prototype.toString = function() { return this.row_0 + ' : ' + this.row_1 + ' : ' + this.row_2; };

/*
 */
tsMatrix4x3f.prototype['set'] = tsMatrix4x3f.prototype.set = function(index, v) { _tsMatrix4x3f_set_index(this.self, index, v.self); };
tsMatrix4x3f.prototype['get'] = tsMatrix4x3f.prototype.get = function(index) { return ts_new(tsVector4f, _tsMatrix4x3f_get_index(this.self, index)); };

tsMatrix4x3f.prototype['set_row_0'] = tsMatrix4x3f.prototype.set_row_0 = function(v) { _tsMatrix4x3f_set_row_0(this.self, v.self); };
tsMatrix4x3f.prototype['set_row_1'] = tsMatrix4x3f.prototype.set_row_1 = function(v) { _tsMatrix4x3f_set_row_1(this.self, v.self); };
tsMatrix4x3f.prototype['set_row_2'] = tsMatrix4x3f.prototype.set_row_2 = function(v) { _tsMatrix4x3f_set_row_2(this.self, v.self); };

tsMatrix4x3f.prototype['get_row_0'] = tsMatrix4x3f.prototype.get_row_0 = function() { return ts_new(tsVector4f, _tsMatrix4x3f_get_row_0(this.self)); };
tsMatrix4x3f.prototype['get_row_1'] = tsMatrix4x3f.prototype.get_row_1 = function() { return ts_new(tsVector4f, _tsMatrix4x3f_get_row_1(this.self)); };
tsMatrix4x3f.prototype['get_row_2'] = tsMatrix4x3f.prototype.get_row_2 = function() { return ts_new(tsVector4f, _tsMatrix4x3f_get_row_2(this.self)); };

Object.defineProperty(tsMatrix4x3f.prototype, 'row_0', { get: tsMatrix4x3f.prototype.get_row_0, set: tsMatrix4x3f.prototype.set_row_0 });
Object.defineProperty(tsMatrix4x3f.prototype, 'row_1', { get: tsMatrix4x3f.prototype.get_row_1, set: tsMatrix4x3f.prototype.set_row_1 });
Object.defineProperty(tsMatrix4x3f.prototype, 'row_2', { get: tsMatrix4x3f.prototype.get_row_2, set: tsMatrix4x3f.prototype.set_row_2 });

/*
 */
tsMatrix4x3f['scale'] = tsMatrix4x3f.scale = function(x, y, z) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_scale(x, y, z)); };
tsMatrix4x3f['translate'] = tsMatrix4x3f.translate = function(x, y, z) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_translate(x, y, z)); };
tsMatrix4x3f['rotateX'] = tsMatrix4x3f.rotateX = function(angle) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_rotateX(angle)); };
tsMatrix4x3f['rotateY'] = tsMatrix4x3f.rotateY = function(angle) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_rotateY(angle)); };
tsMatrix4x3f['rotateZ'] = tsMatrix4x3f.rotateZ = function(angle) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_rotateZ(angle)); };
tsMatrix4x3f['rotateXYZ'] = tsMatrix4x3f.rotateXYZ = function(angles) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_rotateXYZ(angles.self)); };
tsMatrix4x3f['rotateZYX'] = tsMatrix4x3f.rotateZYX = function(angles) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_rotateZYX(angles.self)); };
tsMatrix4x3f['rotate'] = tsMatrix4x3f.rotate = function(axis, angle) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_rotate(axis.self, angle)); };

tsMatrix4x3f['lookAt'] = tsMatrix4x3f.lookAt = function(from, to, up) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_lookAt(from.self, to.self, up.self)); };
tsMatrix4x3f['placeTo'] = tsMatrix4x3f.placeTo = function(to, from, up) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_placeTo(to.self, from.self, up.self)); };
tsMatrix4x3f['compose'] = tsMatrix4x3f.compose = function(t, r, s) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_compose(t.self, r.self, s.self)); };
tsMatrix4x3f['basis'] = tsMatrix4x3f.basis = function(normal, t) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_basis(normal.self, t.self)); };

tsMatrix4x3f.prototype['mul'] = tsMatrix4x3f.prototype.mul = function(v) {
	if(v instanceof tsMatrix4x3f) return ts_new(tsMatrix4x3f, _tsMatrix4x3f_mul(this.self, v.self));
	if(v instanceof tsVector2f) return ts_new(tsVector2f, _tsMatrix4x3f_mul2(this.self, v.self));
	if(v instanceof tsVector3f) return ts_new(tsVector3f, _tsMatrix4x3f_mul3(this.self, v.self));
	if(v instanceof tsVector4f) return ts_new(tsVector4f, _tsMatrix4x3f_mul4(this.self, v.self));
	if(v instanceof tsBoundRectf) return ts_new(tsBoundRectf, _tsMatrix4x3f_mul_br(this.self, v.self));
	if(v instanceof tsBoundCirclef) return ts_new(tsBoundCirclef, _tsMatrix4x3f_mul_bc(this.self, v.self));
	if(v instanceof tsBoundBoxf) return ts_new(tsBoundBoxf, _tsMatrix4x3f_mul_bb(this.self, v.self));
	if(v instanceof tsBoundSpheref) return ts_new(tsBoundSpheref, _tsMatrix4x3f_mul_bs(this.self, v.self));
	throw 'invalid Matrix4x3f() arguments';
};

tsMatrix4x3f.prototype['normalize'] = tsMatrix4x3f.prototype.normalize = function() { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_normalize(this.self)); };
tsMatrix4x3f.prototype['transpose'] = tsMatrix4x3f.prototype.transpose = function() { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_transpose(this.self)); };
tsMatrix4x3f.prototype['inverse'] = tsMatrix4x3f.prototype.inverse = function() { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_inverse(this.self)); };
tsMatrix4x3f.prototype['inverse43'] = tsMatrix4x3f.prototype.inverse43 = function() { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_inverse43(this.self)); };

tsMatrix4x3f['lerp'] = tsMatrix4x3f.lerp = function(q0, q1, k) { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_lerp(q0.self, q1.self, k)); };

tsMatrix4x3f['identity'] = tsMatrix4x3f.identity = function() { return ts_new(tsMatrix4x3f, _tsMatrix4x3f_identity()); };

/*****************************************************************************\
 *
 * Matrix4x3d
 *
\*****************************************************************************/

/*
 */
function tsMatrix4x3d(r0, r1, r2) {
	if(r0 instanceof tsMatrix4x3d) return ts_bind(tsMatrix4x3d, this, _tsMatrix4x3d_copy(r0.self));
	if(r0 instanceof tsMatrix4x3f) return ts_bind(tsMatrix4x3d, this, _tsMatrix4x3d_new_m4x3f(r0.self));
	if(r0 instanceof tsMatrix4x4d) return ts_bind(tsMatrix4x3d, this, _tsMatrix4x3d_new_m4x4d(r0.self));
	if(r0 instanceof tsQuaterniond) return ts_bind(tsMatrix4x3d, this, _tsMatrix4x3d_new_qd(r0.self));
	if(r0 instanceof Array && r1 !== undefined && r2 !== undefined) return ts_bind(tsMatrix4x3d, this, _tsMatrix4x3d_new_ad(ts_f64(r0, true), r1, r2));
	if(r0 instanceof Array && r1 !== undefined) return ts_bind(tsMatrix4x3d, this, _tsMatrix4x3d_new_ad(ts_f64(r0, true), r1, true));
	if(r0 instanceof Array) return ts_bind(tsMatrix4x3d, this, _tsMatrix4x3d_new_ad(ts_f64(r0, true), r0.length, true));
	if(r0 !== undefined && r1 !== undefined && r2 !== undefined) return ts_bind(tsMatrix4x3d, this, _tsMatrix4x3d_new_r(r0.self, r1.self, r2.self));
	if(r0 === undefined && r1 === undefined && r2 === undefined) return ts_bind(tsMatrix4x3d, this, _tsMatrix4x3d_new());
	throw 'invalid Matrix4x3d() arguments';
}
Module['Matrix4x3d'] = tsMatrix4x3d;
tsMatrix4x3d.finalizer = new FinalizationRegistry((self) => { _tsMatrix4x3d_delete(self); });
tsMatrix4x3d.prototype = Object.create(tsMatrix4x3d.prototype);
tsMatrix4x3d.prototype.constructor = tsMatrix4x3d;

tsMatrix4x3d.prototype['toBytes'] = tsMatrix4x3d.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 96); };
tsMatrix4x3d.prototype['toArray'] = tsMatrix4x3d.prototype.getArray = function() { return new Float64Array(HEAPF64.buffer, this.self, 12); };
tsMatrix4x3d.prototype['toString'] = tsMatrix4x3d.prototype.toString = function() { return this.row_0 + ' : ' + this.row_1 + ' : ' + this.row_2; };

/*
 */
tsMatrix4x3d.prototype['set'] = tsMatrix4x3d.prototype.set = function(index, v) { _tsMatrix4x3d_set_index(this.self, index, v.self); };
tsMatrix4x3d.prototype['get'] = tsMatrix4x3d.prototype.get = function(index) { return ts_new(tsVector4d, _tsMatrix4x3d_get_index(this.self, index)); };

tsMatrix4x3d.prototype['set_row_0'] = tsMatrix4x3d.prototype.set_row_0 = function(v) { _tsMatrix4x3d_set_row_0(this.self, v.self); };
tsMatrix4x3d.prototype['set_row_1'] = tsMatrix4x3d.prototype.set_row_1 = function(v) { _tsMatrix4x3d_set_row_1(this.self, v.self); };
tsMatrix4x3d.prototype['set_row_2'] = tsMatrix4x3d.prototype.set_row_2 = function(v) { _tsMatrix4x3d_set_row_2(this.self, v.self); };

tsMatrix4x3d.prototype['get_row_0'] = tsMatrix4x3d.prototype.get_row_0 = function() { return ts_new(tsVector4d, _tsMatrix4x3d_get_row_0(this.self)); };
tsMatrix4x3d.prototype['get_row_1'] = tsMatrix4x3d.prototype.get_row_1 = function() { return ts_new(tsVector4d, _tsMatrix4x3d_get_row_1(this.self)); };
tsMatrix4x3d.prototype['get_row_2'] = tsMatrix4x3d.prototype.get_row_2 = function() { return ts_new(tsVector4d, _tsMatrix4x3d_get_row_2(this.self)); };

Object.defineProperty(tsMatrix4x3d.prototype, 'row_0', { get: tsMatrix4x3d.prototype.get_row_0, set: tsMatrix4x3d.prototype.set_row_0 });
Object.defineProperty(tsMatrix4x3d.prototype, 'row_1', { get: tsMatrix4x3d.prototype.get_row_1, set: tsMatrix4x3d.prototype.set_row_1 });
Object.defineProperty(tsMatrix4x3d.prototype, 'row_2', { get: tsMatrix4x3d.prototype.get_row_2, set: tsMatrix4x3d.prototype.set_row_2 });

/*
 */
tsMatrix4x3d['scale'] = tsMatrix4x3d.scale = function(x, y, z) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_scale(x, y, z)); };
tsMatrix4x3d['translate'] = tsMatrix4x3d.translate = function(x, y, z) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_translate(x, y, z)); };
tsMatrix4x3d['rotateX'] = tsMatrix4x3d.rotateX = function(angle) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_rotateX(angle)); };
tsMatrix4x3d['rotateY'] = tsMatrix4x3d.rotateY = function(angle) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_rotateY(angle)); };
tsMatrix4x3d['rotateZ'] = tsMatrix4x3d.rotateZ = function(angle) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_rotateZ(angle)); };
tsMatrix4x3d['rotateXYZ'] = tsMatrix4x3d.rotateXYZ = function(angles) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_rotateXYZ(angles.self)); };
tsMatrix4x3d['rotateZYX'] = tsMatrix4x3d.rotateZYX = function(angles) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_rotateZYX(angles.self)); };
tsMatrix4x3d['rotate'] = tsMatrix4x3d.rotate = function(axis, angle) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_rotate(axis.self, angle)); };

tsMatrix4x3d['lookAt'] = tsMatrix4x3d.lookAt = function(from, to, up) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_lookAt(from.self, to.self, up.self)); };
tsMatrix4x3d['placeTo'] = tsMatrix4x3d.placeTo = function(to, from, up) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_placeTo(to.self, from.self, up.self)); };
tsMatrix4x3d['compose'] = tsMatrix4x3d.compose = function(t, r, s) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_compose(t.self, r.self, s.self)); };
tsMatrix4x3d['basis'] = tsMatrix4x3d.basis = function(normal, t) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_basis(normal.self, t.self)); };

tsMatrix4x3d.prototype['mul'] = tsMatrix4x3d.prototype.mul = function(v) {
	if(v instanceof tsMatrix4x3d) return ts_new(tsMatrix4x3d, _tsMatrix4x3d_mul(this.self, v.self));
	if(v instanceof tsVector2d) return ts_new(tsVector2d, _tsMatrix4x3d_mul2(this.self, v.self));
	if(v instanceof tsVector3d) return ts_new(tsVector3d, _tsMatrix4x3d_mul3(this.self, v.self));
	if(v instanceof tsVector4d) return ts_new(tsVector4d, _tsMatrix4x3d_mul4(this.self, v.self));
	if(v instanceof tsBoundRectd) return ts_new(tsBoundRectd, _tsMatrix4x3d_mul_br(this.self, v.self));
	if(v instanceof tsBoundCircled) return ts_new(tsBoundCircled, _tsMatrix4x3d_mul_bc(this.self, v.self));
	if(v instanceof tsBoundBoxd) return ts_new(tsBoundBoxd, _tsMatrix4x3d_mul_bb(this.self, v.self));
	if(v instanceof tsBoundSphered) return ts_new(tsBoundSphered, _tsMatrix4x3d_mul_bs(this.self, v.self));
	throw 'invalid Matrix4x3d() arguments';
};

tsMatrix4x3d.prototype['normalize'] = tsMatrix4x3d.prototype.normalize = function() { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_normalize(this.self)); };
tsMatrix4x3d.prototype['transpose'] = tsMatrix4x3d.prototype.transpose = function() { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_transpose(this.self)); };
tsMatrix4x3d.prototype['inverse'] = tsMatrix4x3d.prototype.inverse = function() { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_inverse(this.self)); };
tsMatrix4x3d.prototype['inverse43'] = tsMatrix4x3d.prototype.inverse43 = function() { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_inverse43(this.self)); };

tsMatrix4x3d['lerp'] = tsMatrix4x3d.lerp = function(q0, q1, k) { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_lerp(q0.self, q1.self, k)); };

tsMatrix4x3d['identity'] = tsMatrix4x3d.identity = function() { return ts_new(tsMatrix4x3d, _tsMatrix4x3d_identity()); };

/*****************************************************************************\
 *
 * Matrix4x4f
 *
\*****************************************************************************/

/*
 */
function tsMatrix4x4f(r0, r1, r2, r3) {
	if(r0 instanceof tsMatrix4x4f) return ts_bind(tsMatrix4x4f, this, _tsMatrix4x4f_copy(r0.self));
	if(r0 instanceof tsMatrix4x4d) return ts_bind(tsMatrix4x4f, this, _tsMatrix4x4f_new_m4x4d(r0.self));
	if(r0 instanceof tsMatrix4x3f) return ts_bind(tsMatrix4x4f, this, _tsMatrix4x4f_new_m4x3f(r0.self));
	if(r0 instanceof tsQuaternionf) return ts_bind(tsMatrix4x4f, this, _tsMatrix4x4f_new_qf(r0.self));
	if(r0 instanceof Array && r1 !== undefined && r2 !== undefined) return ts_bind(tsMatrix4x4f, this, _tsMatrix4x4f_new_af(ts_f32(r0, true), r1, r2));
	if(r0 instanceof Array && r1 !== undefined) return ts_bind(tsMatrix4x4f, this, _tsMatrix4x4f_new_af(ts_f32(r0, true), r1, true));
	if(r0 instanceof Array) return ts_bind(tsMatrix4x4f, this, _tsMatrix4x4f_new_af(ts_f32(r0, true), r0.length, true));
	if(r0 !== undefined && r1 !== undefined && r2 !== undefined && r3 !== undefined) return ts_bind(tsMatrix4x4f, this, _tsMatrix4x4f_new_r(r0.self, r1.self, r2.self, r3.self));
	if(r0 === undefined && r1 === undefined && r2 === undefined && r3 === undefined) return ts_bind(tsMatrix4x4f, this, _tsMatrix4x4f_new());
	throw 'invalid Matrix4x4f() arguments';
}
Module['Matrix4x4f'] = tsMatrix4x4f;
tsMatrix4x4f.finalizer = new FinalizationRegistry((self) => { _tsMatrix4x4f_delete(self); });
tsMatrix4x4f.prototype = Object.create(tsMatrix4x4f.prototype);
tsMatrix4x4f.prototype.constructor = tsMatrix4x4f;

tsMatrix4x4f.prototype['toBytes'] = tsMatrix4x4f.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 64); };
tsMatrix4x4f.prototype['toArray'] = tsMatrix4x4f.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 16); };
tsMatrix4x4f.prototype['toString'] = tsMatrix4x4f.prototype.toString = function() { return this.row_0 + ' : ' + this.row_1 + ' : ' + this.row_2 + ' : ' + this.row_3; };

/*
 */
tsMatrix4x4f.prototype['set'] = tsMatrix4x4f.prototype.set = function(index, v) { _tsMatrix4x4f_set_index(this.self, index, v.self); };
tsMatrix4x4f.prototype['get'] = tsMatrix4x4f.prototype.get = function(index) { return ts_new(tsVector4f, _tsMatrix4x4f_get_index(this.self, index)); };

tsMatrix4x4f.prototype['set_row_0'] = tsMatrix4x4f.prototype.set_row_0 = function(v) { _tsMatrix4x4f_set_row_0(this.self, v.self); };
tsMatrix4x4f.prototype['set_row_1'] = tsMatrix4x4f.prototype.set_row_1 = function(v) { _tsMatrix4x4f_set_row_1(this.self, v.self); };
tsMatrix4x4f.prototype['set_row_2'] = tsMatrix4x4f.prototype.set_row_2 = function(v) { _tsMatrix4x4f_set_row_2(this.self, v.self); };
tsMatrix4x4f.prototype['set_row_3'] = tsMatrix4x4f.prototype.set_row_3 = function(v) { _tsMatrix4x4f_set_row_3(this.self, v.self); };

tsMatrix4x4f.prototype['get_row_0'] = tsMatrix4x4f.prototype.get_row_0 = function() { return ts_new(tsVector4f, _tsMatrix4x4f_get_row_0(this.self)); };
tsMatrix4x4f.prototype['get_row_1'] = tsMatrix4x4f.prototype.get_row_1 = function() { return ts_new(tsVector4f, _tsMatrix4x4f_get_row_1(this.self)); };
tsMatrix4x4f.prototype['get_row_2'] = tsMatrix4x4f.prototype.get_row_2 = function() { return ts_new(tsVector4f, _tsMatrix4x4f_get_row_2(this.self)); };
tsMatrix4x4f.prototype['get_row_3'] = tsMatrix4x4f.prototype.get_row_3 = function() { return ts_new(tsVector4f, _tsMatrix4x4f_get_row_3(this.self)); };

Object.defineProperty(tsMatrix4x4f.prototype, 'row_0', { get: tsMatrix4x4f.prototype.get_row_0, set: tsMatrix4x4f.prototype.set_row_0 });
Object.defineProperty(tsMatrix4x4f.prototype, 'row_1', { get: tsMatrix4x4f.prototype.get_row_1, set: tsMatrix4x4f.prototype.set_row_1 });
Object.defineProperty(tsMatrix4x4f.prototype, 'row_2', { get: tsMatrix4x4f.prototype.get_row_2, set: tsMatrix4x4f.prototype.set_row_2 });
Object.defineProperty(tsMatrix4x4f.prototype, 'row_3', { get: tsMatrix4x4f.prototype.get_row_3, set: tsMatrix4x4f.prototype.set_row_3 });

/*
 */
tsMatrix4x4f['scale'] = tsMatrix4x4f.scale = function(x, y, z) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_scale(x, y, z)); };
tsMatrix4x4f['translate'] = tsMatrix4x4f.translate = function(x, y, z) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_translate(x, y, z)); };
tsMatrix4x4f['rotateX'] = tsMatrix4x4f.rotateX = function(angle) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_rotateX(angle)); };
tsMatrix4x4f['rotateY'] = tsMatrix4x4f.rotateY = function(angle) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_rotateY(angle)); };
tsMatrix4x4f['rotateZ'] = tsMatrix4x4f.rotateZ = function(angle) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_rotateZ(angle)); };
tsMatrix4x4f['rotateXYZ'] = tsMatrix4x4f.rotateXYZ = function(angles) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_rotateXYZ(angles.self)); };
tsMatrix4x4f['rotateZYX'] = tsMatrix4x4f.rotateZYX = function(angles) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_rotateZYX(angles.self)); };
tsMatrix4x4f['rotate'] = tsMatrix4x4f.rotate = function(axis, angle) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_rotate(axis.self, angle)); };

tsMatrix4x4f['lookAt'] = tsMatrix4x4f.lookAt = function(from, to, up) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_lookAt(from.self, to.self, up.self)); };
tsMatrix4x4f['placeTo'] = tsMatrix4x4f.placeTo = function(to, from, up) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_placeTo(to.self, from.self, up.self)); };
tsMatrix4x4f['compose'] = tsMatrix4x4f.compose = function(t, r, s) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_compose(t.self, r.self, s.self)); };
tsMatrix4x4f['basis'] = tsMatrix4x4f.basis = function(normal, t) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_basis(normal.self, t.self)); };

tsMatrix4x4f['ortho'] = tsMatrix4x4f.ortho = function(left, right, bottom, top, znear, zfar) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_ortho(left, right, bottom, top, znear, zfar)); };

tsMatrix4x4f['frustum'] = tsMatrix4x4f.frustum = function(left, right, bottom, top, znear, zfar, reverse) {
	if(zfar === undefined) return ts_new(tsMatrix4x4f, _tsMatrix4x4f_frustumi(left, right, bottom, top, znear, false));
	if(typeof zfar === 'boolean') return ts_new(tsMatrix4x4f, _tsMatrix4x4f_frustumi(left, right, bottom, top, znear, zfar));
	if(reverse === undefined) return ts_new(tsMatrix4x4f, _tsMatrix4x4f_frustum(left, right, bottom, top, znear, zfar, false));
	return ts_new(tsMatrix4x4f, _tsMatrix4x4f_frustum(left, right, bottom, top, znear, zfar, reverse));
};

tsMatrix4x4f['perspective'] = tsMatrix4x4f.perspective = function(fov, aspect, znear, zfar, reverse) {
	if(zfar === undefined) return ts_new(tsMatrix4x4f, _tsMatrix4x4f_perspectivei(fov, aspect, znear, false));
	if(typeof zfar === 'boolean') return ts_new(tsMatrix4x4f, _tsMatrix4x4f_perspectivei(fov, aspect, znear, zfar));
	if(reverse === undefined) return ts_new(tsMatrix4x4f, _tsMatrix4x4f_perspective(fov, aspect, znear, zfar, false));
	return ts_new(tsMatrix4x4f, _tsMatrix4x4f_perspective(fov, aspect, znear, zfar, reverse));
};

tsMatrix4x4f.prototype['mul'] = tsMatrix4x4f.prototype.mul = function(v) {
	if(v instanceof tsMatrix4x4f) return ts_new(tsMatrix4x4f, _tsMatrix4x4f_mul(this.self, v.self));
	if(v instanceof tsVector2f) return ts_new(tsVector2f, _tsMatrix4x4f_mul2(this.self, v.self));
	if(v instanceof tsVector3f) return ts_new(tsVector3f, _tsMatrix4x4f_mul3(this.self, v.self));
	if(v instanceof tsVector4f) return ts_new(tsVector4f, _tsMatrix4x4f_mul4(this.self, v.self));
	if(v instanceof tsBoundRectf) return ts_new(tsBoundRectf, _tsMatrix4x4f_mul_br(this.self, v.self));
	if(v instanceof tsBoundCirclef) return ts_new(tsBoundCirclef, _tsMatrix4x4f_mul_bc(this.self, v.self));
	if(v instanceof tsBoundBoxf) return ts_new(tsBoundBoxf, _tsMatrix4x4f_mul_bb(this.self, v.self));
	if(v instanceof tsBoundSpheref) return ts_new(tsBoundSpheref, _tsMatrix4x4f_mul_bs(this.self, v.self));
	throw 'invalid Matrix4x4f() arguments';
};

tsMatrix4x4f.prototype['normalize'] = tsMatrix4x4f.prototype.normalize = function() { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_normalize(this.self)); };
tsMatrix4x4f.prototype['transpose'] = tsMatrix4x4f.prototype.transpose = function() { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_transpose(this.self)); };
tsMatrix4x4f.prototype['inverse'] = tsMatrix4x4f.prototype.inverse = function() { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_inverse(this.self)); };
tsMatrix4x4f.prototype['inverse43'] = tsMatrix4x4f.prototype.inverse43 = function() { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_inverse43(this.self)); };

tsMatrix4x4f['lerp'] = tsMatrix4x4f.lerp = function(q0, q1, k) { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_lerp(q0.self, q1.self, k)); };

tsMatrix4x4f['identity'] = tsMatrix4x4f.identity = function() { return ts_new(tsMatrix4x4f, _tsMatrix4x4f_identity()); };

/*****************************************************************************\
 *
 * Matrix4x4d
 *
\*****************************************************************************/

/*
 */
function tsMatrix4x4d(r0, r1, r2, r3) {
	if(r0 instanceof tsMatrix4x4d) return ts_bind(tsMatrix4x4d, this, _tsMatrix4x4d_copy(r0.self));
	if(r0 instanceof tsMatrix4x4f) return ts_bind(tsMatrix4x4d, this, _tsMatrix4x4d_new_m4x4f(r0.self));
	if(r0 instanceof tsMatrix4x3d) return ts_bind(tsMatrix4x4d, this, _tsMatrix4x4d_new_m4x3d(r0.self));
	if(r0 instanceof tsQuaterniond) return ts_bind(tsMatrix4x4d, this, _tsMatrix4x4d_new_qd(r0.self));
	if(r0 instanceof Array && r1 !== undefined && r2 !== undefined) return ts_bind(tsMatrix4x4d, this, _tsMatrix4x4d_new_ad(ts_f64(r0, true), r1, r2));
	if(r0 instanceof Array && r1 !== undefined) return ts_bind(tsMatrix4x4d, this, _tsMatrix4x4d_new_ad(ts_f64(r0, true), r1, true));
	if(r0 instanceof Array) return ts_bind(tsMatrix4x4d, this, _tsMatrix4x4d_new_ad(ts_f64(r0, true), r0.length, true));
	if(r0 !== undefined && r1 !== undefined && r2 !== undefined && r3 !== undefined) return ts_bind(tsMatrix4x4d, this, _tsMatrix4x4d_new_r(r0.self, r1.self, r2.self, r3.self));
	if(r0 === undefined && r1 === undefined && r2 === undefined && r3 === undefined) return ts_bind(tsMatrix4x4d, this, _tsMatrix4x4d_new());
	throw 'invalid Matrix4x4d() arguments';
}
Module['Matrix4x4d'] = tsMatrix4x4d;
tsMatrix4x4d.finalizer = new FinalizationRegistry((self) => { _tsMatrix4x4d_delete(self); });
tsMatrix4x4d.prototype = Object.create(tsMatrix4x4d.prototype);
tsMatrix4x4d.prototype.constructor = tsMatrix4x4d;

tsMatrix4x4d.prototype['toBytes'] = tsMatrix4x4d.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 128); };
tsMatrix4x4d.prototype['toArray'] = tsMatrix4x4d.prototype.getArray = function() { return new Float64Array(HEAPF64.buffer, this.self, 16); };
tsMatrix4x4d.prototype['toString'] = tsMatrix4x4d.prototype.toString = function() { return this.row_0 + ' : ' + this.row_1 + ' : ' + this.row_2 + ' : ' + this.row_3; };

/*
 */
tsMatrix4x4d.prototype['set'] = tsMatrix4x4d.prototype.set = function(index, v) { _tsMatrix4x4d_set_index(this.self, index, v.self); };
tsMatrix4x4d.prototype['get'] = tsMatrix4x4d.prototype.get = function(index) { return ts_new(tsVector4d, _tsMatrix4x4d_get_index(this.self, index)); };

tsMatrix4x4d.prototype['set_row_0'] = tsMatrix4x4d.prototype.set_row_0 = function(v) { _tsMatrix4x4d_set_row_0(this.self, v.self); };
tsMatrix4x4d.prototype['set_row_1'] = tsMatrix4x4d.prototype.set_row_1 = function(v) { _tsMatrix4x4d_set_row_1(this.self, v.self); };
tsMatrix4x4d.prototype['set_row_2'] = tsMatrix4x4d.prototype.set_row_2 = function(v) { _tsMatrix4x4d_set_row_2(this.self, v.self); };
tsMatrix4x4d.prototype['set_row_3'] = tsMatrix4x4d.prototype.set_row_3 = function(v) { _tsMatrix4x4d_set_row_3(this.self, v.self); };

tsMatrix4x4d.prototype['get_row_0'] = tsMatrix4x4d.prototype.get_row_0 = function() { return ts_new(tsVector4d, _tsMatrix4x4d_get_row_0(this.self)); };
tsMatrix4x4d.prototype['get_row_1'] = tsMatrix4x4d.prototype.get_row_1 = function() { return ts_new(tsVector4d, _tsMatrix4x4d_get_row_1(this.self)); };
tsMatrix4x4d.prototype['get_row_2'] = tsMatrix4x4d.prototype.get_row_2 = function() { return ts_new(tsVector4d, _tsMatrix4x4d_get_row_2(this.self)); };
tsMatrix4x4d.prototype['get_row_3'] = tsMatrix4x4d.prototype.get_row_3 = function() { return ts_new(tsVector4d, _tsMatrix4x4d_get_row_3(this.self)); };

Object.defineProperty(tsMatrix4x4d.prototype, 'row_0', { get: tsMatrix4x4d.prototype.get_row_0, set: tsMatrix4x4d.prototype.set_row_0 });
Object.defineProperty(tsMatrix4x4d.prototype, 'row_1', { get: tsMatrix4x4d.prototype.get_row_1, set: tsMatrix4x4d.prototype.set_row_1 });
Object.defineProperty(tsMatrix4x4d.prototype, 'row_2', { get: tsMatrix4x4d.prototype.get_row_2, set: tsMatrix4x4d.prototype.set_row_2 });
Object.defineProperty(tsMatrix4x4d.prototype, 'row_3', { get: tsMatrix4x4d.prototype.get_row_3, set: tsMatrix4x4d.prototype.set_row_3 });

/*
 */
tsMatrix4x4d['scale'] = tsMatrix4x4d.scale = function(x, y, z) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_scale(x, y, z)); };
tsMatrix4x4d['translate'] = tsMatrix4x4d.translate = function(x, y, z) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_translate(x, y, z)); };
tsMatrix4x4d['rotateX'] = tsMatrix4x4d.rotateX = function(angle) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_rotateX(angle)); };
tsMatrix4x4d['rotateY'] = tsMatrix4x4d.rotateY = function(angle) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_rotateY(angle)); };
tsMatrix4x4d['rotateZ'] = tsMatrix4x4d.rotateZ = function(angle) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_rotateZ(angle)); };
tsMatrix4x4d['rotateXYZ'] = tsMatrix4x4d.rotateXYZ = function(angles) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_rotateXYZ(angles.self)); };
tsMatrix4x4d['rotateZYX'] = tsMatrix4x4d.rotateZYX = function(angles) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_rotateZYX(angles.self)); };
tsMatrix4x4d['rotate'] = tsMatrix4x4d.rotate = function(axis, angle) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_rotate(axis.self, angle)); };

tsMatrix4x4d['lookAt'] = tsMatrix4x4d.lookAt = function(from, to, up) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_lookAt(from.self, to.self, up.self)); };
tsMatrix4x4d['placeTo'] = tsMatrix4x4d.placeTo = function(to, from, up) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_placeTo(to.self, from.self, up.self)); };
tsMatrix4x4d['compose'] = tsMatrix4x4d.compose = function(t, r, s) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_compose(t.self, r.self, s.self)); };
tsMatrix4x4d['basis'] = tsMatrix4x4d.basis = function(normal, t) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_basis(normal.self, t.self)); };

tsMatrix4x4d['ortho'] = tsMatrix4x4d.ortho = function(left, right, bottom, top, znear, zfar) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_ortho(left, right, bottom, top, znear, zfar)); };

tsMatrix4x4d['frustum'] = tsMatrix4x4d.frustum = function(left, right, bottom, top, znear, zfar, reverse) {
	if(zfar === undefined) return ts_new(tsMatrix4x4d, _tsMatrix4x4d_frustumi(left, right, bottom, top, znear, false));
	if(typeof zfar === 'boolean') return ts_new(tsMatrix4x4d, _tsMatrix4x4d_frustumi(left, right, bottom, top, znear, zfar));
	if(reverse === undefined) return ts_new(tsMatrix4x4d, _tsMatrix4x4d_frustum(left, right, bottom, top, znear, zfar, false));
	return ts_new(tsMatrix4x4d, _tsMatrix4x4d_frustum(left, right, bottom, top, znear, zfar, reverse));
};

tsMatrix4x4d['perspective'] = tsMatrix4x4d.perspective = function(fov, aspect, znear, zfar, reverse) {
	if(zfar === undefined) return ts_new(tsMatrix4x4d, _tsMatrix4x4d_perspectivei(fov, aspect, znear, false));
	if(typeof zfar === 'boolean') return ts_new(tsMatrix4x4d, _tsMatrix4x4d_perspectivei(fov, aspect, znear, zfar));
	if(reverse === undefined) return ts_new(tsMatrix4x4d, _tsMatrix4x4d_perspective(fov, aspect, znear, zfar, false));
	return ts_new(tsMatrix4x4d, _tsMatrix4x4d_perspective(fov, aspect, znear, zfar, reverse));
};

tsMatrix4x4d.prototype['mul'] = tsMatrix4x4d.prototype.mul = function(v) {
	if(v instanceof tsMatrix4x4d) return ts_new(tsMatrix4x4d, _tsMatrix4x4d_mul(this.self, v.self));
	if(v instanceof tsVector2d) return ts_new(tsVector2d, _tsMatrix4x4d_mul2(this.self, v.self));
	if(v instanceof tsVector3d) return ts_new(tsVector3d, _tsMatrix4x4d_mul3(this.self, v.self));
	if(v instanceof tsVector4d) return ts_new(tsVector4d, _tsMatrix4x4d_mul4(this.self, v.self));
	if(v instanceof tsBoundRectd) return ts_new(tsBoundRectd, _tsMatrix4x4d_mul_br(this.self, v.self));
	if(v instanceof tsBoundCircled) return ts_new(tsBoundCircled, _tsMatrix4x4d_mul_bc(this.self, v.self));
	if(v instanceof tsBoundBoxd) return ts_new(tsBoundBoxd, _tsMatrix4x4d_mul_bb(this.self, v.self));
	if(v instanceof tsBoundSphered) return ts_new(tsBoundSphered, _tsMatrix4x4d_mul_bs(this.self, v.self));
	throw 'invalid Matrix4x4d() arguments';
};

tsMatrix4x4d.prototype['normalize'] = tsMatrix4x4d.prototype.normalize = function() { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_normalize(this.self)); };
tsMatrix4x4d.prototype['transpose'] = tsMatrix4x4d.prototype.transpose = function() { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_transpose(this.self)); };
tsMatrix4x4d.prototype['inverse'] = tsMatrix4x4d.prototype.inverse = function() { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_inverse(this.self)); };
tsMatrix4x4d.prototype['inverse43'] = tsMatrix4x4d.prototype.inverse43 = function() { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_inverse43(this.self)); };

tsMatrix4x4d['lerp'] = tsMatrix4x4d.lerp = function(q0, q1, k) { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_lerp(q0.self, q1.self, k)); };

tsMatrix4x4d['identity'] = tsMatrix4x4d.identity = function() { return ts_new(tsMatrix4x4d, _tsMatrix4x4d_identity()); };

/*****************************************************************************\
 *
 * Quaternionf
 *
\*****************************************************************************/

/*
 */
function tsQuaternionf(x, y, z, w) {
	if(x instanceof tsQuaternionf) return ts_bind(tsQuaternionf, this, _tsQuaternionf_copy(x.self));
	if(x instanceof tsQuaterniond) return ts_bind(tsQuaternionf, this, _tsQuaternionf_new_qd(x.self));
	if(x instanceof tsMatrix4x3f) return ts_bind(tsQuaternionf, this, _tsQuaternionf_new_m4x3f(x.self));
	if(x instanceof tsMatrix4x4f) return ts_bind(tsQuaternionf, this, _tsQuaternionf_new_m4x4f(x.self));
	if(x instanceof Array && x.length === 4) return ts_bind(tsQuaternionf, this, _tsQuaternionf_new_af(ts_f32(x, true)));
	if(x !== undefined && y !== undefined && z !== undefined && w !== undefined) return ts_bind(tsQuaternionf, this, _tsQuaternionf_new_xyzw(x, y, z, w));
	if(x === undefined && y === undefined && z === undefined && w === undefined) return ts_bind(tsQuaternionf, this, _tsQuaternionf_new());
	throw 'invalid Quaternionf() arguments';
}
Module['Quaternionf'] = tsQuaternionf;
tsQuaternionf.finalizer = new FinalizationRegistry((self) => { _tsQuaternionf_delete(self); });
tsQuaternionf.prototype = Object.create(tsQuaternionf.prototype);
tsQuaternionf.prototype.constructor = tsQuaternionf;

tsQuaternionf.prototype['toBytes'] = tsQuaternionf.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 16); };
tsQuaternionf.prototype['toArray'] = tsQuaternionf.prototype.getArray = function() { return new Float32Array(HEAPF32.buffer, this.self, 4); };
tsQuaternionf.prototype['toString'] = tsQuaternionf.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' ' + this.z + ' ' + this.w + ')'; };

/*
 */
tsQuaternionf.prototype['set'] = tsQuaternionf.prototype.set = function(index, s) { _tsQuaternionf_set_index(this.self, index, s); };
tsQuaternionf.prototype['get'] = tsQuaternionf.prototype.get = function(index) { return _tsQuaternionf_get_index(this.self, index); };

tsQuaternionf.prototype['set_x'] = tsQuaternionf.prototype.set_x = function(x) { _tsQuaternionf_set_x(this.self, x); };
tsQuaternionf.prototype['set_y'] = tsQuaternionf.prototype.set_y = function(y) { _tsQuaternionf_set_y(this.self, y); };
tsQuaternionf.prototype['set_z'] = tsQuaternionf.prototype.set_z = function(z) { _tsQuaternionf_set_z(this.self, z); };
tsQuaternionf.prototype['set_w'] = tsQuaternionf.prototype.set_w = function(w) { _tsQuaternionf_set_w(this.self, w); };

tsQuaternionf.prototype['get_x'] = tsQuaternionf.prototype.get_x = function() { return _tsQuaternionf_get_x(this.self); };
tsQuaternionf.prototype['get_y'] = tsQuaternionf.prototype.get_y = function() { return _tsQuaternionf_get_y(this.self); };
tsQuaternionf.prototype['get_z'] = tsQuaternionf.prototype.get_z = function() { return _tsQuaternionf_get_z(this.self); };
tsQuaternionf.prototype['get_w'] = tsQuaternionf.prototype.get_w = function() { return _tsQuaternionf_get_w(this.self); };

Object.defineProperty(tsQuaternionf.prototype, 'x', { get: tsQuaternionf.prototype.get_x, set: tsQuaternionf.prototype.set_x });
Object.defineProperty(tsQuaternionf.prototype, 'y', { get: tsQuaternionf.prototype.get_y, set: tsQuaternionf.prototype.set_y });
Object.defineProperty(tsQuaternionf.prototype, 'z', { get: tsQuaternionf.prototype.get_z, set: tsQuaternionf.prototype.set_z });
Object.defineProperty(tsQuaternionf.prototype, 'w', { get: tsQuaternionf.prototype.get_w, set: tsQuaternionf.prototype.set_w });

/*
 */
tsQuaternionf['rotateX'] = tsQuaternionf.rotateX = function(angle) { return ts_new(tsQuaternionf, _tsQuaternionf_rotateX(angle)); };
tsQuaternionf['rotateY'] = tsQuaternionf.rotateY = function(angle) { return ts_new(tsQuaternionf, _tsQuaternionf_rotateY(angle)); };
tsQuaternionf['rotateZ'] = tsQuaternionf.rotateZ = function(angle) { return ts_new(tsQuaternionf, _tsQuaternionf_rotateZ(angle)); };
tsQuaternionf['rotateXYZ'] = tsQuaternionf.rotateXYZ = function(angles) { return ts_new(tsQuaternionf, _tsQuaternionf_rotateXYZ(angles.self)); };
tsQuaternionf['rotateZYX'] = tsQuaternionf.rotateZYX = function(angles) { return ts_new(tsQuaternionf, _tsQuaternionf_rotateZYX(angles.self)); };
tsQuaternionf['rotate'] = tsQuaternionf.rotate = function(axis, angle) { return ts_new(tsQuaternionf, _tsQuaternionf_rotate(axis.self, angle)); };

tsQuaternionf.prototype['mul'] = tsQuaternionf.prototype.mul = function(v) {
	if(v instanceof tsQuaternionf) return ts_new(tsQuaternionf, _tsQuaternionf_mul(this.self, v.self));
	if(v instanceof tsVector2f) return ts_new(tsVector2f, _tsQuaternionf_mul2(this.self, v.self));
	if(v instanceof tsVector3f) return ts_new(tsVector3f, _tsQuaternionf_mul3(this.self, v.self));
	if(v instanceof tsVector4f) return ts_new(tsVector4f, _tsQuaternionf_mul4(this.self, v.self));
	return ts_new(tsQuaternionf, _tsQuaternionf_mul1(this.self, v));
};

tsQuaternionf.prototype['normalize'] = tsQuaternionf.prototype.normalize = function() { return ts_new(tsQuaternionf, _tsQuaternionf_normalize(this.self)); };
tsQuaternionf.prototype['inverse'] = tsQuaternionf.prototype.inverse = function() { return ts_new(tsQuaternionf, _tsQuaternionf_inverse(this.self)); };

tsQuaternionf['lerp'] = tsQuaternionf.lerp = function(q0, q1, k) { return ts_new(tsQuaternionf, _tsQuaternionf_lerp(q0.self, q1.self, k)); };
tsQuaternionf['slerp'] = tsQuaternionf.slerp = function(q0, q1, k) { return ts_new(tsQuaternionf, _tsQuaternionf_slerp(q0.self, q1.self, k)); };

tsQuaternionf['identity'] = tsQuaternionf.identity = function() { return ts_new(tsQuaternionf, _tsQuaternionf_identity()); };

/*****************************************************************************\
 *
 * Quaterniond
 *
\*****************************************************************************/

/*
 */
function tsQuaterniond(x, y, z, w) {
	if(x instanceof tsQuaterniond) return ts_bind(tsQuaterniond, this, _tsQuaterniond_copy(x.self));
	if(x instanceof tsQuaternionf) return ts_bind(tsQuaterniond, this, _tsQuaterniond_new_qf(x.self));
	if(x instanceof tsMatrix4x3d) return ts_bind(tsQuaterniond, this, _tsQuaterniond_new_m4x3d(x.self));
	if(x instanceof tsMatrix4x4d) return ts_bind(tsQuaterniond, this, _tsQuaterniond_new_m4x4d(x.self));
	if(x instanceof Array && x.length === 4) return ts_bind(tsQuaterniond, this, _tsQuaterniond_new_ad(ts_f64(x, true)));
	if(x !== undefined && y !== undefined && z !== undefined && w !== undefined) return ts_bind(tsQuaterniond, this, _tsQuaterniond_new_xyzw(x, y, z, w));
	if(x === undefined && y === undefined && z === undefined && w === undefined) return ts_bind(tsQuaterniond, this, _tsQuaterniond_new());
	throw 'invalid Quaterniond() arguments';
}
Module['Quaterniond'] = tsQuaterniond;
tsQuaterniond.finalizer = new FinalizationRegistry((self) => { _tsQuaterniond_delete(self); });
tsQuaterniond.prototype = Object.create(tsQuaterniond.prototype);
tsQuaterniond.prototype.constructor = tsQuaterniond;

tsQuaterniond.prototype['toBytes'] = tsQuaterniond.prototype.getBytes = function() { return new Uint8Array(HEAP8.buffer, this.self, 32); };
tsQuaterniond.prototype['toArray'] = tsQuaterniond.prototype.getArray = function() { return new Float64Array(HEAPF64.buffer, this.self, 4); };
tsQuaterniond.prototype['toString'] = tsQuaterniond.prototype.toString = function() { return '(' + this.x + ' ' + this.y + ' ' + this.z + ' ' + this.w + ')'; };

/*
 */
tsQuaterniond.prototype['set'] = tsQuaterniond.prototype.set = function(index, s) { _tsQuaterniond_set_index(this.self, index, s); };
tsQuaterniond.prototype['get'] = tsQuaterniond.prototype.get = function(index) { return _tsQuaterniond_get_index(this.self, index); };

tsQuaterniond.prototype['set_x'] = tsQuaterniond.prototype.set_x = function(x) { _tsQuaterniond_set_x(this.self, x); };
tsQuaterniond.prototype['set_y'] = tsQuaterniond.prototype.set_y = function(y) { _tsQuaterniond_set_y(this.self, y); };
tsQuaterniond.prototype['set_z'] = tsQuaterniond.prototype.set_z = function(z) { _tsQuaterniond_set_z(this.self, z); };
tsQuaterniond.prototype['set_w'] = tsQuaterniond.prototype.set_w = function(w) { _tsQuaterniond_set_w(this.self, w); };

tsQuaterniond.prototype['get_x'] = tsQuaterniond.prototype.get_x = function() { return _tsQuaterniond_get_x(this.self); };
tsQuaterniond.prototype['get_y'] = tsQuaterniond.prototype.get_y = function() { return _tsQuaterniond_get_y(this.self); };
tsQuaterniond.prototype['get_z'] = tsQuaterniond.prototype.get_z = function() { return _tsQuaterniond_get_z(this.self); };
tsQuaterniond.prototype['get_w'] = tsQuaterniond.prototype.get_w = function() { return _tsQuaterniond_get_w(this.self); };

Object.defineProperty(tsQuaterniond.prototype, 'x', { get: tsQuaterniond.prototype.get_x, set: tsQuaterniond.prototype.set_x });
Object.defineProperty(tsQuaterniond.prototype, 'y', { get: tsQuaterniond.prototype.get_y, set: tsQuaterniond.prototype.set_y });
Object.defineProperty(tsQuaterniond.prototype, 'z', { get: tsQuaterniond.prototype.get_z, set: tsQuaterniond.prototype.set_z });
Object.defineProperty(tsQuaterniond.prototype, 'w', { get: tsQuaterniond.prototype.get_w, set: tsQuaterniond.prototype.set_w });

/*
 */
tsQuaterniond['rotateX'] = tsQuaterniond.rotateX = function(angle) { return ts_new(tsQuaterniond, _tsQuaterniond_rotateX(angle)); };
tsQuaterniond['rotateY'] = tsQuaterniond.rotateY = function(angle) { return ts_new(tsQuaterniond, _tsQuaterniond_rotateY(angle)); };
tsQuaterniond['rotateZ'] = tsQuaterniond.rotateZ = function(angle) { return ts_new(tsQuaterniond, _tsQuaterniond_rotateZ(angle)); };
tsQuaterniond['rotateXYZ'] = tsQuaterniond.rotateXYZ = function(angles) { return ts_new(tsQuaterniond, _tsQuaterniond_rotateXYZ(angles.self)); };
tsQuaterniond['rotateZYX'] = tsQuaterniond.rotateZYX = function(angles) { return ts_new(tsQuaterniond, _tsQuaterniond_rotateZYX(angles.self)); };
tsQuaterniond['rotate'] = tsQuaterniond.rotate = function(axis, angle) { return ts_new(tsQuaterniond, _tsQuaterniond_rotate(axis.self, angle)); };

tsQuaterniond.prototype['mul'] = tsQuaterniond.prototype.mul = function(v) {
	if(v instanceof tsQuaterniond) return ts_new(tsQuaterniond, _tsQuaterniond_mul(this.self, v.self));
	if(v instanceof tsVector2d) return ts_new(tsVector2d, _tsQuaterniond_mul2(this.self, v.self));
	if(v instanceof tsVector3d) return ts_new(tsVector3d, _tsQuaterniond_mul3(this.self, v.self));
	if(v instanceof tsVector4d) return ts_new(tsVector4d, _tsQuaterniond_mul4(this.self, v.self));
	return ts_new(tsQuaterniond, _tsQuaterniond_mul1(this.self, v));
};

tsQuaterniond.prototype['normalize'] = tsQuaterniond.prototype.normalize = function() { return ts_new(tsQuaterniond, _tsQuaterniond_normalize(this.self)); };
tsQuaterniond.prototype['inverse'] = tsQuaterniond.prototype.inverse = function() { return ts_new(tsQuaterniond, _tsQuaterniond_inverse(this.self)); };

tsQuaterniond['lerp'] = tsQuaterniond.lerp = function(q0, q1, k) { return ts_new(tsQuaterniond, _tsQuaterniond_lerp(q0.self, q1.self, k)); };
tsQuaterniond['slerp'] = tsQuaterniond.slerp = function(q0, q1, k) { return ts_new(tsQuaterniond, _tsQuaterniond_slerp(q0.self, q1.self, k)); };

tsQuaterniond['identity'] = tsQuaterniond.identity = function() { return ts_new(tsQuaterniond, _tsQuaterniond_identity()); };
