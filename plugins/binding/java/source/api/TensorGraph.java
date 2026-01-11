// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class TensorGraph {
	
	public static class Operation {
		public enum Enum {
			Clear(0),
			Range(1),
			Copy(2),
			Cat(3),
			Transpose(4),
			MatMul(5),
			Mul(6),
			Mad(7),
			Div(8),
			Add(9),
			Conv(10),
			DeConv(11),
			BatchNorm(12),
			BatchMad(13),
			SoftMin(14),
			SoftMax(15),
			MaxPool(16),
			AvgPool(17),
			GELU(18),
			ReLU(19),
			SiLU(20),
			Sigm(21),
			Tanh(22),
			Sin(23),
			Cos(24),
			Exp(25),
			NumOperations(26);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Clear = Enum.Clear;
		public static final Enum Range = Enum.Range;
		public static final Enum Copy = Enum.Copy;
		public static final Enum Cat = Enum.Cat;
		public static final Enum Transpose = Enum.Transpose;
		public static final Enum MatMul = Enum.MatMul;
		public static final Enum Mul = Enum.Mul;
		public static final Enum Mad = Enum.Mad;
		public static final Enum Div = Enum.Div;
		public static final Enum Add = Enum.Add;
		public static final Enum Conv = Enum.Conv;
		public static final Enum DeConv = Enum.DeConv;
		public static final Enum BatchNorm = Enum.BatchNorm;
		public static final Enum BatchMad = Enum.BatchMad;
		public static final Enum SoftMin = Enum.SoftMin;
		public static final Enum SoftMax = Enum.SoftMax;
		public static final Enum MaxPool = Enum.MaxPool;
		public static final Enum AvgPool = Enum.AvgPool;
		public static final Enum GELU = Enum.GELU;
		public static final Enum ReLU = Enum.ReLU;
		public static final Enum SiLU = Enum.SiLU;
		public static final Enum Sigm = Enum.Sigm;
		public static final Enum Tanh = Enum.Tanh;
		public static final Enum Sin = Enum.Sin;
		public static final Enum Cos = Enum.Cos;
		public static final Enum Exp = Enum.Exp;
		public static final Enum NumOperations = Enum.NumOperations;
		public Operation(int value) { this.value = value; }
		public Operation(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Flags {
		public enum Enum {
			None(0),
			SizeQuery(1),
			FormatRf32(2),
			FormatRf16(4),
			Transpose(8),
			WrapClamp(16),
			WrapRepeat(32),
			ReadScale(64),
			ReadBias(128),
			Convert(256),
			Kernel(512),
			GELU(1024),
			ReLU(2048),
			SiLU(4096),
			Sigm(8192),
			Tanh(16384),
			Sin(32768),
			Cos(65536),
			Exp(131072),
			Format(6),
			Wrap(48),
			Read(192),
			Unit(7168),
			Math(253952),
			All(262142);
			Enum(int value) { this.value = value; }
			public Flags and(Flags e) { return new Flags(value & e.value); }
			public Flags and(Enum e) { return new Flags(value & e.value); }
			public Flags or(Flags e) { return new Flags(value | e.value); }
			public Flags or(Enum e) { return new Flags(value | e.value); }
			public boolean has(Flags e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum SizeQuery = Enum.SizeQuery;
		public static final Enum FormatRf32 = Enum.FormatRf32;
		public static final Enum FormatRf16 = Enum.FormatRf16;
		public static final Enum Transpose = Enum.Transpose;
		public static final Enum WrapClamp = Enum.WrapClamp;
		public static final Enum WrapRepeat = Enum.WrapRepeat;
		public static final Enum ReadScale = Enum.ReadScale;
		public static final Enum ReadBias = Enum.ReadBias;
		public static final Enum Convert = Enum.Convert;
		public static final Enum Kernel = Enum.Kernel;
		public static final Enum GELU = Enum.GELU;
		public static final Enum ReLU = Enum.ReLU;
		public static final Enum SiLU = Enum.SiLU;
		public static final Enum Sigm = Enum.Sigm;
		public static final Enum Tanh = Enum.Tanh;
		public static final Enum Sin = Enum.Sin;
		public static final Enum Cos = Enum.Cos;
		public static final Enum Exp = Enum.Exp;
		public static final Enum Format = Enum.Format;
		public static final Enum Wrap = Enum.Wrap;
		public static final Enum Read = Enum.Read;
		public static final Enum Unit = Enum.Unit;
		public static final Enum Math = Enum.Math;
		public static final Enum All = Enum.All;
		public Flags(int value) { this.value = value; }
		public Flags(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Flags(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Flags(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Flags(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Flags not() { return new Flags(~value); }
		public Flags and(Flags e) { return new Flags(value & e.value); }
		public Flags and(Enum e) { return new Flags(value & e.value); }
		public Flags or(Flags e) { return new Flags(value | e.value); }
		public Flags or(Enum e) { return new Flags(value | e.value); }
		public boolean has(Flags e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public static class Masks {
		public enum Enum {
			MaskNone(0),
			MaskClear(1),
			MaskRange(2),
			MaskCopy(4),
			MaskCat(8),
			MaskTranspose(16),
			MaskMatMul(32),
			MaskMul(64),
			MaskMad(128),
			MaskDiv(256),
			MaskAdd(512),
			MaskConv(1024),
			MaskDeConv(2048),
			MaskBatchNorm(4096),
			MaskBatchMad(8192),
			MaskSoftMin(16384),
			MaskSoftMax(32768),
			MaskMaxPool(65536),
			MaskAvgPool(131072),
			MaskGELU(262144),
			MaskReLU(524288),
			MaskSiLU(1048576),
			MaskSigm(2097152),
			MaskTanh(4194304),
			MaskSin(8388608),
			MaskCos(16777216),
			MaskExp(33554432),
			All(67108863);
			Enum(int value) { this.value = value; }
			public Masks and(Masks e) { return new Masks(value & e.value); }
			public Masks and(Enum e) { return new Masks(value & e.value); }
			public Masks or(Masks e) { return new Masks(value | e.value); }
			public Masks or(Enum e) { return new Masks(value | e.value); }
			public boolean has(Masks e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum MaskNone = Enum.MaskNone;
		public static final Enum MaskClear = Enum.MaskClear;
		public static final Enum MaskRange = Enum.MaskRange;
		public static final Enum MaskCopy = Enum.MaskCopy;
		public static final Enum MaskCat = Enum.MaskCat;
		public static final Enum MaskTranspose = Enum.MaskTranspose;
		public static final Enum MaskMatMul = Enum.MaskMatMul;
		public static final Enum MaskMul = Enum.MaskMul;
		public static final Enum MaskMad = Enum.MaskMad;
		public static final Enum MaskDiv = Enum.MaskDiv;
		public static final Enum MaskAdd = Enum.MaskAdd;
		public static final Enum MaskConv = Enum.MaskConv;
		public static final Enum MaskDeConv = Enum.MaskDeConv;
		public static final Enum MaskBatchNorm = Enum.MaskBatchNorm;
		public static final Enum MaskBatchMad = Enum.MaskBatchMad;
		public static final Enum MaskSoftMin = Enum.MaskSoftMin;
		public static final Enum MaskSoftMax = Enum.MaskSoftMax;
		public static final Enum MaskMaxPool = Enum.MaskMaxPool;
		public static final Enum MaskAvgPool = Enum.MaskAvgPool;
		public static final Enum MaskGELU = Enum.MaskGELU;
		public static final Enum MaskReLU = Enum.MaskReLU;
		public static final Enum MaskSiLU = Enum.MaskSiLU;
		public static final Enum MaskSigm = Enum.MaskSigm;
		public static final Enum MaskTanh = Enum.MaskTanh;
		public static final Enum MaskSin = Enum.MaskSin;
		public static final Enum MaskCos = Enum.MaskCos;
		public static final Enum MaskExp = Enum.MaskExp;
		public static final Enum All = Enum.All;
		public Masks(int value) { this.value = value; }
		public Masks(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Masks(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Masks(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Masks(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Masks not() { return new Masks(~value); }
		public Masks and(Masks e) { return new Masks(value & e.value); }
		public Masks and(Enum e) { return new Masks(value & e.value); }
		public Masks or(Masks e) { return new Masks(value | e.value); }
		public Masks or(Enum e) { return new Masks(value | e.value); }
		public boolean has(Masks e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public TensorGraph() { init_(new_()); }
	public TensorGraph[] ref() { return new TensorGraph[] { this }; }
	public boolean equalPtr(TensorGraph ptr) { return equal_ptr(self, ptr.self); }
	public TensorGraph clonePtr() { return new TensorGraph(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public void clear() { clear_(self); }
	public boolean isCreated() { return is_created(self); }
	public boolean create(Device device) { return create_(self, device.self, Flags.All.value, Masks.All.value, 0); }
	public boolean create(Device device, Flags flags) { return create_(self, device.self, flags.value, Masks.All.value, 0); }
	public boolean create(Device device, Flags.Enum flags) { return create_(self, device.self, flags.value, Masks.All.value, 0); }
	public boolean create(Device device, Flags flags, Masks masks) { return create_(self, device.self, flags.value, masks.value, 0); }
	public boolean create(Device device, Flags.Enum flags, Masks masks) { return create_(self, device.self, flags.value, masks.value, 0); }
	public boolean create(Device device, Flags.Enum flags, Masks.Enum masks) { return create_(self, device.self, flags.value, masks.value, 0); }
	public boolean create(Device device, Flags flags, Masks.Enum masks) { return create_(self, device.self, flags.value, masks.value, 0); }
	public boolean create(Device device, Flags flags, Masks masks, Async async) { return create_(self, device.self, flags.value, masks.value, async.self); }
	public boolean create(Device device, Flags.Enum flags, Masks masks, Async async) { return create_(self, device.self, flags.value, masks.value, async.self); }
	public boolean create(Device device, Flags.Enum flags, Masks.Enum masks, Async async) { return create_(self, device.self, flags.value, masks.value, async.self); }
	public boolean create(Device device, Flags flags, Masks.Enum masks, Async async) { return create_(self, device.self, flags.value, masks.value, async.self); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest) { return dispatch_(self, compute.self, op.value, dest.self, Flags.None.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest) { return dispatch_(self, compute.self, op.value, dest.self, Flags.None.value); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest, Flags flags) { return dispatch_(self, compute.self, op.value, dest.self, flags.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest, Flags flags) { return dispatch_(self, compute.self, op.value, dest.self, flags.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest, Flags.Enum flags) { return dispatch_(self, compute.self, op.value, dest.self, flags.value); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest, Flags.Enum flags) { return dispatch_(self, compute.self, op.value, dest.self, flags.value); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest, Tensor src_0) { return dispatch_1(self, compute.self, op.value, dest.self, src_0.self, Flags.None.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest, Tensor src_0) { return dispatch_1(self, compute.self, op.value, dest.self, src_0.self, Flags.None.value); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest, Tensor src_0, Flags flags) { return dispatch_1(self, compute.self, op.value, dest.self, src_0.self, flags.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest, Tensor src_0, Flags flags) { return dispatch_1(self, compute.self, op.value, dest.self, src_0.self, flags.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest, Tensor src_0, Flags.Enum flags) { return dispatch_1(self, compute.self, op.value, dest.self, src_0.self, flags.value); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest, Tensor src_0, Flags.Enum flags) { return dispatch_1(self, compute.self, op.value, dest.self, src_0.self, flags.value); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest, Tensor src_0, Tensor src_1) { return dispatch_2(self, compute.self, op.value, dest.self, src_0.self, src_1.self, Flags.None.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest, Tensor src_0, Tensor src_1) { return dispatch_2(self, compute.self, op.value, dest.self, src_0.self, src_1.self, Flags.None.value); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest, Tensor src_0, Tensor src_1, Flags flags) { return dispatch_2(self, compute.self, op.value, dest.self, src_0.self, src_1.self, flags.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest, Tensor src_0, Tensor src_1, Flags flags) { return dispatch_2(self, compute.self, op.value, dest.self, src_0.self, src_1.self, flags.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest, Tensor src_0, Tensor src_1, Flags.Enum flags) { return dispatch_2(self, compute.self, op.value, dest.self, src_0.self, src_1.self, flags.value); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest, Tensor src_0, Tensor src_1, Flags.Enum flags) { return dispatch_2(self, compute.self, op.value, dest.self, src_0.self, src_1.self, flags.value); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest, Tensor src_0, Tensor src_1, Tensor src_2) { return dispatch_3(self, compute.self, op.value, dest.self, src_0.self, src_1.self, src_2.self, Flags.None.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest, Tensor src_0, Tensor src_1, Tensor src_2) { return dispatch_3(self, compute.self, op.value, dest.self, src_0.self, src_1.self, src_2.self, Flags.None.value); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest, Tensor src_0, Tensor src_1, Tensor src_2, Flags flags) { return dispatch_3(self, compute.self, op.value, dest.self, src_0.self, src_1.self, src_2.self, flags.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest, Tensor src_0, Tensor src_1, Tensor src_2, Flags flags) { return dispatch_3(self, compute.self, op.value, dest.self, src_0.self, src_1.self, src_2.self, flags.value); }
	public boolean dispatch(Compute compute, Operation.Enum op, Tensor dest, Tensor src_0, Tensor src_1, Tensor src_2, Flags.Enum flags) { return dispatch_3(self, compute.self, op.value, dest.self, src_0.self, src_1.self, src_2.self, flags.value); }
	public boolean dispatch(Compute compute, Operation op, Tensor dest, Tensor src_0, Tensor src_1, Tensor src_2, Flags.Enum flags) { return dispatch_3(self, compute.self, op.value, dest.self, src_0.self, src_1.self, src_2.self, flags.value); }
	public boolean dispatch(Compute compute, Tensor dest, Texture src, Region region) { return dispatch_4(self, compute.self, dest.self, src.self, region.self, (new Slice()).self); }
	public boolean dispatch(Compute compute, Tensor dest, Texture src, Region region, Slice slice) { return dispatch_4(self, compute.self, dest.self, src.self, region.self, slice.self); }
	public boolean dispatch(Compute compute, Tensor dest, Texture src) { return dispatch_5(self, compute.self, dest.self, src.self, (new Slice()).self); }
	public boolean dispatch(Compute compute, Tensor dest, Texture src, Slice slice) { return dispatch_5(self, compute.self, dest.self, src.self, slice.self); }
	public boolean dispatch(Compute compute, Texture dest, Tensor src, Region region) { return dispatch_6(self, compute.self, dest.self, src.self, region.self, (new Slice()).self); }
	public boolean dispatch(Compute compute, Texture dest, Tensor src, Region region, Slice slice) { return dispatch_6(self, compute.self, dest.self, src.self, region.self, slice.self); }
	public boolean dispatch(Compute compute, Texture dest, Tensor src) { return dispatch_7(self, compute.self, dest.self, src.self, (new Slice()).self); }
	public boolean dispatch(Compute compute, Texture dest, Tensor src, Slice slice) { return dispatch_7(self, compute.self, dest.self, src.self, slice.self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_ptr(long self, long ptr);
	private static native long clone_ptr(long self);
	private static native void clear_ptr(long self);
	private static native void destroy_ptr(long self);
	private static native void acquire_ptr(long self);
	private static native void unacquire_ptr(long self);
	private static native boolean is_valid_ptr(long self);
	private static native boolean is_owner_ptr(long self);
	private static native boolean is_const_ptr(long self);
	private static native int get_count_ptr(long self);
	private static native long get_internal_ptr(long self);
	private static native void clear_(long self);
	private static native boolean is_created(long self);
	private static native boolean create_(long self, long device, int flags, int masks, long async);
	private static native boolean dispatch_(long self, long compute, int op, long dest, int flags);
	private static native boolean dispatch_1(long self, long compute, int op, long dest, long src_0, int flags);
	private static native boolean dispatch_2(long self, long compute, int op, long dest, long src_0, long src_1, int flags);
	private static native boolean dispatch_3(long self, long compute, int op, long dest, long src_0, long src_1, long src_2, int flags);
	private static native boolean dispatch_4(long self, long compute, long dest, long src, long region, long slice);
	private static native boolean dispatch_5(long self, long compute, long dest, long src, long slice);
	private static native boolean dispatch_6(long self, long compute, long dest, long src, long region, long slice);
	private static native boolean dispatch_7(long self, long compute, long dest, long src, long slice);
	
	protected TensorGraph(long self) {
		init_(self);
	}
	public static TensorGraph Null() {
		return new TensorGraph((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(TensorGraph[] ptr) {
		long[] self = new long[ptr.length];
		for(int i = 0; i < ptr.length; i++) self[i] = ptr[i].self;
		return self;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}
