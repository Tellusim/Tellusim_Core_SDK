// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Pipeline {
	
	public static class Primitive {
		public enum Enum {
			Point(0),
			PointPatch(1),
			Line(2),
			LineAdj(3),
			LineStrip(4),
			LinePatch(5),
			Triangle(6),
			TriangleAdj(7),
			TriangleStrip(8),
			TrianglePatch(9),
			QuadrilateralPatch(10),
			NumPrimitiveTypes(11);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Point = Enum.Point;
		public static final Enum PointPatch = Enum.PointPatch;
		public static final Enum Line = Enum.Line;
		public static final Enum LineAdj = Enum.LineAdj;
		public static final Enum LineStrip = Enum.LineStrip;
		public static final Enum LinePatch = Enum.LinePatch;
		public static final Enum Triangle = Enum.Triangle;
		public static final Enum TriangleAdj = Enum.TriangleAdj;
		public static final Enum TriangleStrip = Enum.TriangleStrip;
		public static final Enum TrianglePatch = Enum.TrianglePatch;
		public static final Enum QuadrilateralPatch = Enum.QuadrilateralPatch;
		public static final Enum NumPrimitiveTypes = Enum.NumPrimitiveTypes;
		public Primitive(int value) { this.value = value; }
		public Primitive(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Attribute {
		public enum Enum {
			Position(0),
			Basis(1),
			Normal(2),
			Tangent(3),
			Binormal(4),
			TexCoord(5),
			Weights(6),
			Joints(7),
			Color(8),
			Index(9),
			NumAttributeTypes(10);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Position = Enum.Position;
		public static final Enum Basis = Enum.Basis;
		public static final Enum Normal = Enum.Normal;
		public static final Enum Tangent = Enum.Tangent;
		public static final Enum Binormal = Enum.Binormal;
		public static final Enum TexCoord = Enum.TexCoord;
		public static final Enum Weights = Enum.Weights;
		public static final Enum Joints = Enum.Joints;
		public static final Enum Color = Enum.Color;
		public static final Enum Index = Enum.Index;
		public static final Enum NumAttributeTypes = Enum.NumAttributeTypes;
		public Attribute(int value) { this.value = value; }
		public Attribute(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class FillMode {
		public enum Enum {
			Line(0),
			Solid(1),
			NumFillModes(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Line = Enum.Line;
		public static final Enum Solid = Enum.Solid;
		public static final Enum NumFillModes = Enum.NumFillModes;
		public FillMode(int value) { this.value = value; }
		public FillMode(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class CullMode {
		public enum Enum {
			None(0),
			Back(1),
			Front(2),
			NumCullModes(3);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Back = Enum.Back;
		public static final Enum Front = Enum.Front;
		public static final Enum NumCullModes = Enum.NumCullModes;
		public CullMode(int value) { this.value = value; }
		public CullMode(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class FrontMode {
		public enum Enum {
			CCW(0),
			CW(1),
			NumFrontModes(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum CCW = Enum.CCW;
		public static final Enum CW = Enum.CW;
		public static final Enum NumFrontModes = Enum.NumFrontModes;
		public FrontMode(int value) { this.value = value; }
		public FrontMode(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class BlendOp {
		public enum Enum {
			Add(0),
			Sub(1),
			Min(2),
			Max(3),
			NumBlendOperations(4);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Add = Enum.Add;
		public static final Enum Sub = Enum.Sub;
		public static final Enum Min = Enum.Min;
		public static final Enum Max = Enum.Max;
		public static final Enum NumBlendOperations = Enum.NumBlendOperations;
		public BlendOp(int value) { this.value = value; }
		public BlendOp(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class BlendFunc {
		public enum Enum {
			None(0),
			Zero(1),
			One(2),
			SrcColor(3),
			SrcAlpha(4),
			Src1Color(5),
			Src1Alpha(6),
			DestColor(7),
			DestAlpha(8),
			FactorColor(9),
			FactorAlpha(10),
			InvSrcColor(11),
			InvSrcAlpha(12),
			InvSrc1Color(13),
			InvSrc1Alpha(14),
			InvDestColor(15),
			InvDestAlpha(16),
			InvFactorColor(17),
			InvFactorAlpha(18),
			NumBlendFunctions(19);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Zero = Enum.Zero;
		public static final Enum One = Enum.One;
		public static final Enum SrcColor = Enum.SrcColor;
		public static final Enum SrcAlpha = Enum.SrcAlpha;
		public static final Enum Src1Color = Enum.Src1Color;
		public static final Enum Src1Alpha = Enum.Src1Alpha;
		public static final Enum DestColor = Enum.DestColor;
		public static final Enum DestAlpha = Enum.DestAlpha;
		public static final Enum FactorColor = Enum.FactorColor;
		public static final Enum FactorAlpha = Enum.FactorAlpha;
		public static final Enum InvSrcColor = Enum.InvSrcColor;
		public static final Enum InvSrcAlpha = Enum.InvSrcAlpha;
		public static final Enum InvSrc1Color = Enum.InvSrc1Color;
		public static final Enum InvSrc1Alpha = Enum.InvSrc1Alpha;
		public static final Enum InvDestColor = Enum.InvDestColor;
		public static final Enum InvDestAlpha = Enum.InvDestAlpha;
		public static final Enum InvFactorColor = Enum.InvFactorColor;
		public static final Enum InvFactorAlpha = Enum.InvFactorAlpha;
		public static final Enum NumBlendFunctions = Enum.NumBlendFunctions;
		public BlendFunc(int value) { this.value = value; }
		public BlendFunc(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class ColorMask {
		public enum Enum {
			None(0),
			R(1),
			G(2),
			B(4),
			A(8),
			Unknown(16),
			RGB(7),
			All(15);
			Enum(int value) { this.value = value; }
			public ColorMask and(ColorMask e) { return new ColorMask(value & e.value); }
			public ColorMask and(Enum e) { return new ColorMask(value & e.value); }
			public ColorMask or(ColorMask e) { return new ColorMask(value | e.value); }
			public ColorMask or(Enum e) { return new ColorMask(value | e.value); }
			public boolean has(ColorMask e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum R = Enum.R;
		public static final Enum G = Enum.G;
		public static final Enum B = Enum.B;
		public static final Enum A = Enum.A;
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum RGB = Enum.RGB;
		public static final Enum All = Enum.All;
		public ColorMask(int value) { this.value = value; }
		public ColorMask(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public ColorMask(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public ColorMask(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public ColorMask(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public ColorMask not() { return new ColorMask(~value); }
		public ColorMask and(ColorMask e) { return new ColorMask(value & e.value); }
		public ColorMask and(Enum e) { return new ColorMask(value & e.value); }
		public ColorMask or(ColorMask e) { return new ColorMask(value | e.value); }
		public ColorMask or(Enum e) { return new ColorMask(value | e.value); }
		public boolean has(ColorMask e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public static class DepthMask {
		public enum Enum {
			None(0),
			Read(1),
			Write(2),
			NumDepthMasks(3);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Read = Enum.Read;
		public static final Enum Write = Enum.Write;
		public static final Enum NumDepthMasks = Enum.NumDepthMasks;
		public DepthMask(int value) { this.value = value; }
		public DepthMask(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class DepthFunc {
		public enum Enum {
			None(0),
			Never(1),
			Always(2),
			Equal(3),
			Less(4),
			Greater(5),
			NotEqual(6),
			LessEqual(7),
			GreaterEqual(8),
			NumDepthFunctions(9);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Never = Enum.Never;
		public static final Enum Always = Enum.Always;
		public static final Enum Equal = Enum.Equal;
		public static final Enum Less = Enum.Less;
		public static final Enum Greater = Enum.Greater;
		public static final Enum NotEqual = Enum.NotEqual;
		public static final Enum LessEqual = Enum.LessEqual;
		public static final Enum GreaterEqual = Enum.GreaterEqual;
		public static final Enum NumDepthFunctions = Enum.NumDepthFunctions;
		public DepthFunc(int value) { this.value = value; }
		public DepthFunc(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class StencilOp {
		public enum Enum {
			Keep(0),
			Invert(1),
			Replace(2),
			IncrWrap(3),
			DecrWrap(4),
			IncrSat(5),
			DecrSat(6),
			NumStencilOperations(7);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Keep = Enum.Keep;
		public static final Enum Invert = Enum.Invert;
		public static final Enum Replace = Enum.Replace;
		public static final Enum IncrWrap = Enum.IncrWrap;
		public static final Enum DecrWrap = Enum.DecrWrap;
		public static final Enum IncrSat = Enum.IncrSat;
		public static final Enum DecrSat = Enum.DecrSat;
		public static final Enum NumStencilOperations = Enum.NumStencilOperations;
		public StencilOp(int value) { this.value = value; }
		public StencilOp(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class StencilFunc {
		public enum Enum {
			None(0),
			Never(1),
			Always(2),
			Equal(3),
			Less(4),
			Greater(5),
			NotEqual(6),
			LessEqual(7),
			GreaterEqual(8),
			NumStencilFunctions(9);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Never = Enum.Never;
		public static final Enum Always = Enum.Always;
		public static final Enum Equal = Enum.Equal;
		public static final Enum Less = Enum.Less;
		public static final Enum Greater = Enum.Greater;
		public static final Enum NotEqual = Enum.NotEqual;
		public static final Enum LessEqual = Enum.LessEqual;
		public static final Enum GreaterEqual = Enum.GreaterEqual;
		public static final Enum NumStencilFunctions = Enum.NumStencilFunctions;
		public StencilFunc(int value) { this.value = value; }
		public StencilFunc(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public Pipeline() { init_(new_()); }
	public Pipeline[] ref() { return new Pipeline[] { this }; }
	public boolean equalPtr(Pipeline ptr) { return equal_ptr(self, ptr.self); }
	public Pipeline clonePtr() { return new Pipeline(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public Platform getPlatform() { return new Platform(get_platform(self)); }
	public String getPlatformName() { return get_platform_name(self); }
	public int getIndex() { return get_index(self); }
	public void clear() { clear_(self); }
	public boolean isCreated() { return is_created(self); }
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public boolean create() { return create_(self); }
	public void setParameters(Pipeline pipeline) { set_parameters(self, pipeline.self); }
	public boolean saveState(Stream stream) { return save_state(self, stream.self); }
	public void addShader(Shader shader) { add_shader(self, shader.self, false); }
	public void addShader(Shader shader, boolean owner) { add_shader(self, shader.self, owner); }
	public Shader getVertexShader() { return new Shader(get_vertex_shader(self)); }
	public Shader getControlShader() { return new Shader(get_control_shader(self)); }
	public Shader getEvaluateShader() { return new Shader(get_evaluate_shader(self)); }
	public Shader getGeometryShader() { return new Shader(get_geometry_shader(self)); }
	public Shader getFragmentShader() { return new Shader(get_fragment_shader(self)); }
	public Shader getTaskShader() { return new Shader(get_task_shader(self)); }
	public Shader getMeshShader() { return new Shader(get_mesh_shader(self)); }
	public boolean loadShader(Shader.Type type, String name, String format) { return load_shader(self, type.value, name, format); }
	public boolean loadShader(Shader.Type.Enum type, String name, String format) { return load_shader(self, type.value, name, format); }
	public boolean loadShaderGLSL(Shader.Type type, String name, String format) { return load_shader_glsl(self, type.value, name, format); }
	public boolean loadShaderGLSL(Shader.Type.Enum type, String name, String format) { return load_shader_glsl(self, type.value, name, format); }
	public boolean loadShader(Shader.Type type, String name) { return load_shader_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean loadShader(Shader.Type.Enum type, String name) { return load_shader_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean loadShader(Shader.Type type, String name, TSString macros) { return load_shader_1(self, type.value, name, macros.self, null, 0); }
	public boolean loadShader(Shader.Type.Enum type, String name, TSString macros) { return load_shader_1(self, type.value, name, macros.self, null, 0); }
	public boolean loadShader(Shader.Type type, String name, TSString macros, String[] includes) { return load_shader_1(self, type.value, name, macros.self, includes, 0); }
	public boolean loadShader(Shader.Type.Enum type, String name, TSString macros, String[] includes) { return load_shader_1(self, type.value, name, macros.self, includes, 0); }
	public boolean loadShader(Shader.Type type, String name, TSString macros, String[] includes, int size) { return load_shader_1(self, type.value, name, macros.self, includes, size); }
	public boolean loadShader(Shader.Type.Enum type, String name, TSString macros, String[] includes, int size) { return load_shader_1(self, type.value, name, macros.self, includes, size); }
	public boolean loadShaderGLSL(Shader.Type type, String name) { return load_shader_glsl_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean loadShaderGLSL(Shader.Type.Enum type, String name) { return load_shader_glsl_1(self, type.value, name, (new TSString()).self, null, 0); }
	public boolean loadShaderGLSL(Shader.Type type, String name, TSString macros) { return load_shader_glsl_1(self, type.value, name, macros.self, null, 0); }
	public boolean loadShaderGLSL(Shader.Type.Enum type, String name, TSString macros) { return load_shader_glsl_1(self, type.value, name, macros.self, null, 0); }
	public boolean loadShaderGLSL(Shader.Type type, String name, TSString macros, String[] includes) { return load_shader_glsl_1(self, type.value, name, macros.self, includes, 0); }
	public boolean loadShaderGLSL(Shader.Type.Enum type, String name, TSString macros, String[] includes) { return load_shader_glsl_1(self, type.value, name, macros.self, includes, 0); }
	public boolean loadShaderGLSL(Shader.Type type, String name, TSString macros, String[] includes, int size) { return load_shader_glsl_1(self, type.value, name, macros.self, includes, size); }
	public boolean loadShaderGLSL(Shader.Type.Enum type, String name, TSString macros, String[] includes, int size) { return load_shader_glsl_1(self, type.value, name, macros.self, includes, size); }
	public boolean loadShaderSPIRV(Shader.Type type, String name) { return load_shader_spirv(self, type.value, name); }
	public boolean loadShaderSPIRV(Shader.Type.Enum type, String name) { return load_shader_spirv(self, type.value, name); }
	public boolean createShader(Shader.Type type, String src, String format) { return create_shader(self, type.value, src, format); }
	public boolean createShader(Shader.Type.Enum type, String src, String format) { return create_shader(self, type.value, src, format); }
	public boolean createShaderGLSL(Shader.Type type, String src, String format) { return create_shader_glsl(self, type.value, src, format); }
	public boolean createShaderGLSL(Shader.Type.Enum type, String src, String format) { return create_shader_glsl(self, type.value, src, format); }
	public boolean createShader(Shader.Type type, String src) { return create_shader_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean createShader(Shader.Type.Enum type, String src) { return create_shader_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean createShader(Shader.Type type, String src, TSString macros) { return create_shader_1(self, type.value, src, macros.self, null, 0); }
	public boolean createShader(Shader.Type.Enum type, String src, TSString macros) { return create_shader_1(self, type.value, src, macros.self, null, 0); }
	public boolean createShader(Shader.Type type, String src, TSString macros, String[] includes) { return create_shader_1(self, type.value, src, macros.self, includes, 0); }
	public boolean createShader(Shader.Type.Enum type, String src, TSString macros, String[] includes) { return create_shader_1(self, type.value, src, macros.self, includes, 0); }
	public boolean createShader(Shader.Type type, String src, TSString macros, String[] includes, int size) { return create_shader_1(self, type.value, src, macros.self, includes, size); }
	public boolean createShader(Shader.Type.Enum type, String src, TSString macros, String[] includes, int size) { return create_shader_1(self, type.value, src, macros.self, includes, size); }
	public boolean createShaderGLSL(Shader.Type type, String src) { return create_shader_glsl_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean createShaderGLSL(Shader.Type.Enum type, String src) { return create_shader_glsl_1(self, type.value, src, (new TSString()).self, null, 0); }
	public boolean createShaderGLSL(Shader.Type type, String src, TSString macros) { return create_shader_glsl_1(self, type.value, src, macros.self, null, 0); }
	public boolean createShaderGLSL(Shader.Type.Enum type, String src, TSString macros) { return create_shader_glsl_1(self, type.value, src, macros.self, null, 0); }
	public boolean createShaderGLSL(Shader.Type type, String src, TSString macros, String[] includes) { return create_shader_glsl_1(self, type.value, src, macros.self, includes, 0); }
	public boolean createShaderGLSL(Shader.Type.Enum type, String src, TSString macros, String[] includes) { return create_shader_glsl_1(self, type.value, src, macros.self, includes, 0); }
	public boolean createShaderGLSL(Shader.Type type, String src, TSString macros, String[] includes, int size) { return create_shader_glsl_1(self, type.value, src, macros.self, includes, size); }
	public boolean createShaderGLSL(Shader.Type.Enum type, String src, TSString macros, String[] includes, int size) { return create_shader_glsl_1(self, type.value, src, macros.self, includes, size); }
	public boolean createShaderSPIRV(Shader.Type type, int[] data) { return create_shader_spirv(self, type.value, data); }
	public boolean createShaderSPIRV(Shader.Type.Enum type, int[] data) { return create_shader_spirv(self, type.value, data); }
	public int addSampler(Shader.Mask mask) { return add_sampler(self, mask.value); }
	public int addSampler(Shader.Mask.Enum mask) { return add_sampler(self, mask.value); }
	public int getNumSamplers() { return get_num_samplers(self); }
	public Pipeline setSamplerOffset(int offset) { set_sampler_offset(self, offset); return this; }
	public int getSamplerOffset() { return get_sampler_offset(self); }
	public Pipeline setSamplerMask(int index, Shader.Mask mask) { set_sampler_mask(self, index, mask.value); return this; }
	public Pipeline setSamplerMask(int index, Shader.Mask.Enum mask) { set_sampler_mask(self, index, mask.value); return this; }
	public Shader.Mask getSamplerMask(int index) { return new Shader.Mask(get_sampler_mask(self, index)); }
	public Pipeline setSamplerMasks(int index, int num, Shader.Mask mask) { set_sampler_masks(self, index, num, mask.value, false); return this; }
	public Pipeline setSamplerMasks(int index, int num, Shader.Mask.Enum mask) { set_sampler_masks(self, index, num, mask.value, false); return this; }
	public Pipeline setSamplerMasks(int index, int num, Shader.Mask mask, boolean array) { set_sampler_masks(self, index, num, mask.value, array); return this; }
	public Pipeline setSamplerMasks(int index, int num, Shader.Mask.Enum mask, boolean array) { set_sampler_masks(self, index, num, mask.value, array); return this; }
	public Shader.Mask getSamplerMasks(int index, int num) { return new Shader.Mask(get_sampler_masks(self, index, num)); }
	public Pipeline setSamplerArray(int index, int num, boolean array) { set_sampler_array(self, index, num, array); return this; }
	public int getSamplerArray(int index) { return get_sampler_array(self, index); }
	public int addTexture(Shader.Mask mask) { return add_texture(self, mask.value); }
	public int addTexture(Shader.Mask.Enum mask) { return add_texture(self, mask.value); }
	public int getNumTextures() { return get_num_textures(self); }
	public Pipeline setTextureOffset(int offset) { set_texture_offset(self, offset); return this; }
	public int getTextureOffset() { return get_texture_offset(self); }
	public Pipeline setTextureMask(int index, Shader.Mask mask) { set_texture_mask(self, index, mask.value); return this; }
	public Pipeline setTextureMask(int index, Shader.Mask.Enum mask) { set_texture_mask(self, index, mask.value); return this; }
	public Shader.Mask getTextureMask(int index) { return new Shader.Mask(get_texture_mask(self, index)); }
	public Pipeline setTextureMasks(int index, int num, Shader.Mask mask) { set_texture_masks(self, index, num, mask.value, false); return this; }
	public Pipeline setTextureMasks(int index, int num, Shader.Mask.Enum mask) { set_texture_masks(self, index, num, mask.value, false); return this; }
	public Pipeline setTextureMasks(int index, int num, Shader.Mask mask, boolean array) { set_texture_masks(self, index, num, mask.value, array); return this; }
	public Pipeline setTextureMasks(int index, int num, Shader.Mask.Enum mask, boolean array) { set_texture_masks(self, index, num, mask.value, array); return this; }
	public Shader.Mask getTextureMasks(int index, int num) { return new Shader.Mask(get_texture_masks(self, index, num)); }
	public Pipeline setTextureArray(int index, int num, boolean array) { set_texture_array(self, index, num, array); return this; }
	public int getTextureArray(int index) { return get_texture_array(self, index); }
	public int addSurface(Shader.Mask mask) { return add_surface(self, mask.value); }
	public int addSurface(Shader.Mask.Enum mask) { return add_surface(self, mask.value); }
	public int getNumSurfaces() { return get_num_surfaces(self); }
	public Pipeline setSurfaceOffset(int offset) { set_surface_offset(self, offset); return this; }
	public int getSurfaceOffset() { return get_surface_offset(self); }
	public Pipeline setSurfaceMask(int index, Shader.Mask mask) { set_surface_mask(self, index, mask.value); return this; }
	public Pipeline setSurfaceMask(int index, Shader.Mask.Enum mask) { set_surface_mask(self, index, mask.value); return this; }
	public Shader.Mask getSurfaceMask(int index) { return new Shader.Mask(get_surface_mask(self, index)); }
	public Pipeline setSurfaceMasks(int index, int num, Shader.Mask mask) { set_surface_masks(self, index, num, mask.value, false); return this; }
	public Pipeline setSurfaceMasks(int index, int num, Shader.Mask.Enum mask) { set_surface_masks(self, index, num, mask.value, false); return this; }
	public Pipeline setSurfaceMasks(int index, int num, Shader.Mask mask, boolean array) { set_surface_masks(self, index, num, mask.value, array); return this; }
	public Pipeline setSurfaceMasks(int index, int num, Shader.Mask.Enum mask, boolean array) { set_surface_masks(self, index, num, mask.value, array); return this; }
	public Shader.Mask getSurfaceMasks(int index, int num) { return new Shader.Mask(get_surface_masks(self, index, num)); }
	public Pipeline setSurfaceArray(int index, int num, boolean array) { set_surface_array(self, index, num, array); return this; }
	public int getSurfaceArray(int index) { return get_surface_array(self, index); }
	public int addUniform(Shader.Mask mask) { return add_uniform(self, mask.value, BindFlags.BindFlagNone.value); }
	public int addUniform(Shader.Mask.Enum mask) { return add_uniform(self, mask.value, BindFlags.BindFlagNone.value); }
	public int addUniform(Shader.Mask mask, BindFlags flags) { return add_uniform(self, mask.value, flags.value); }
	public int addUniform(Shader.Mask.Enum mask, BindFlags flags) { return add_uniform(self, mask.value, flags.value); }
	public int addUniform(Shader.Mask.Enum mask, BindFlags.Enum flags) { return add_uniform(self, mask.value, flags.value); }
	public int addUniform(Shader.Mask mask, BindFlags.Enum flags) { return add_uniform(self, mask.value, flags.value); }
	public int getNumUniforms() { return get_num_uniforms(self); }
	public Pipeline setUniformOffset(int offset) { set_uniform_offset(self, offset); return this; }
	public int getUniformOffset() { return get_uniform_offset(self); }
	public Pipeline setUniformMask(int index, Shader.Mask mask) { set_uniform_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setUniformMask(int index, Shader.Mask.Enum mask) { set_uniform_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setUniformMask(int index, Shader.Mask mask, BindFlags flags) { set_uniform_mask(self, index, mask.value, flags.value); return this; }
	public Pipeline setUniformMask(int index, Shader.Mask.Enum mask, BindFlags flags) { set_uniform_mask(self, index, mask.value, flags.value); return this; }
	public Pipeline setUniformMask(int index, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_uniform_mask(self, index, mask.value, flags.value); return this; }
	public Pipeline setUniformMask(int index, Shader.Mask mask, BindFlags.Enum flags) { set_uniform_mask(self, index, mask.value, flags.value); return this; }
	public Shader.Mask getUniformMask(int index) { return new Shader.Mask(get_uniform_mask(self, index)); }
	public Pipeline setUniformMasks(int index, int num, Shader.Mask mask) { set_uniform_masks(self, index, num, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setUniformMasks(int index, int num, Shader.Mask.Enum mask) { set_uniform_masks(self, index, num, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setUniformMasks(int index, int num, Shader.Mask mask, BindFlags flags) { set_uniform_masks(self, index, num, mask.value, flags.value); return this; }
	public Pipeline setUniformMasks(int index, int num, Shader.Mask.Enum mask, BindFlags flags) { set_uniform_masks(self, index, num, mask.value, flags.value); return this; }
	public Pipeline setUniformMasks(int index, int num, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_uniform_masks(self, index, num, mask.value, flags.value); return this; }
	public Pipeline setUniformMasks(int index, int num, Shader.Mask mask, BindFlags.Enum flags) { set_uniform_masks(self, index, num, mask.value, flags.value); return this; }
	public Shader.Mask getUniformMasks(int index, int num) { return new Shader.Mask(get_uniform_masks(self, index, num)); }
	public Pipeline setUniformFlags(int index, BindFlags flags) { set_uniform_flags(self, index, flags.value); return this; }
	public Pipeline setUniformFlags(int index, BindFlags.Enum flags) { set_uniform_flags(self, index, flags.value); return this; }
	public BindFlags getUniformFlags(int index) { return new BindFlags(get_uniform_flags(self, index)); }
	public int addStorage(Shader.Mask mask) { return add_storage(self, mask.value, BindFlags.BindFlagNone.value); }
	public int addStorage(Shader.Mask.Enum mask) { return add_storage(self, mask.value, BindFlags.BindFlagNone.value); }
	public int addStorage(Shader.Mask mask, BindFlags flags) { return add_storage(self, mask.value, flags.value); }
	public int addStorage(Shader.Mask.Enum mask, BindFlags flags) { return add_storage(self, mask.value, flags.value); }
	public int addStorage(Shader.Mask.Enum mask, BindFlags.Enum flags) { return add_storage(self, mask.value, flags.value); }
	public int addStorage(Shader.Mask mask, BindFlags.Enum flags) { return add_storage(self, mask.value, flags.value); }
	public int getNumStorages() { return get_num_storages(self); }
	public Pipeline setStorageOffset(int offset) { set_storage_offset(self, offset); return this; }
	public int getStorageOffset() { return get_storage_offset(self); }
	public Pipeline setStorageMask(int index, Shader.Mask mask) { set_storage_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setStorageMask(int index, Shader.Mask.Enum mask) { set_storage_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setStorageMask(int index, Shader.Mask mask, BindFlags flags) { set_storage_mask(self, index, mask.value, flags.value); return this; }
	public Pipeline setStorageMask(int index, Shader.Mask.Enum mask, BindFlags flags) { set_storage_mask(self, index, mask.value, flags.value); return this; }
	public Pipeline setStorageMask(int index, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_storage_mask(self, index, mask.value, flags.value); return this; }
	public Pipeline setStorageMask(int index, Shader.Mask mask, BindFlags.Enum flags) { set_storage_mask(self, index, mask.value, flags.value); return this; }
	public Shader.Mask getStorageMask(int index) { return new Shader.Mask(get_storage_mask(self, index)); }
	public Pipeline setStorageMasks(int index, int num, Shader.Mask mask) { set_storage_masks(self, index, num, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setStorageMasks(int index, int num, Shader.Mask.Enum mask) { set_storage_masks(self, index, num, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setStorageMasks(int index, int num, Shader.Mask mask, BindFlags flags) { set_storage_masks(self, index, num, mask.value, flags.value); return this; }
	public Pipeline setStorageMasks(int index, int num, Shader.Mask.Enum mask, BindFlags flags) { set_storage_masks(self, index, num, mask.value, flags.value); return this; }
	public Pipeline setStorageMasks(int index, int num, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_storage_masks(self, index, num, mask.value, flags.value); return this; }
	public Pipeline setStorageMasks(int index, int num, Shader.Mask mask, BindFlags.Enum flags) { set_storage_masks(self, index, num, mask.value, flags.value); return this; }
	public Shader.Mask getStorageMasks(int index, int num) { return new Shader.Mask(get_storage_masks(self, index, num)); }
	public Pipeline setStorageFlags(int index, BindFlags flags) { set_storage_flags(self, index, flags.value); return this; }
	public Pipeline setStorageFlags(int index, BindFlags.Enum flags) { set_storage_flags(self, index, flags.value); return this; }
	public BindFlags getStorageFlags(int index) { return new BindFlags(get_storage_flags(self, index)); }
	public int addTracing(Shader.Mask mask) { return add_tracing(self, mask.value); }
	public int addTracing(Shader.Mask.Enum mask) { return add_tracing(self, mask.value); }
	public int getNumTracings() { return get_num_tracings(self); }
	public Pipeline setTracingOffset(int offset) { set_tracing_offset(self, offset); return this; }
	public int getTracingOffset() { return get_tracing_offset(self); }
	public Pipeline setTracingMask(int index, Shader.Mask mask) { set_tracing_mask(self, index, mask.value); return this; }
	public Pipeline setTracingMask(int index, Shader.Mask.Enum mask) { set_tracing_mask(self, index, mask.value); return this; }
	public Shader.Mask getTracingMask(int index) { return new Shader.Mask(get_tracing_mask(self, index)); }
	public Pipeline setTracingMasks(int index, int num, Shader.Mask mask) { set_tracing_masks(self, index, num, mask.value); return this; }
	public Pipeline setTracingMasks(int index, int num, Shader.Mask.Enum mask) { set_tracing_masks(self, index, num, mask.value); return this; }
	public Shader.Mask getTracingMasks(int index, int num) { return new Shader.Mask(get_tracing_masks(self, index, num)); }
	public int addTexel(Shader.Mask mask) { return add_texel(self, mask.value); }
	public int addTexel(Shader.Mask.Enum mask) { return add_texel(self, mask.value); }
	public int getNumTexels() { return get_num_texels(self); }
	public Pipeline setTexelOffset(int offset) { set_texel_offset(self, offset); return this; }
	public int getTexelOffset() { return get_texel_offset(self); }
	public Pipeline setTexelMask(int index, Shader.Mask mask) { set_texel_mask(self, index, mask.value); return this; }
	public Pipeline setTexelMask(int index, Shader.Mask.Enum mask) { set_texel_mask(self, index, mask.value); return this; }
	public Shader.Mask getTexelMask(int index) { return new Shader.Mask(get_texel_mask(self, index)); }
	public Pipeline setTexelMasks(int index, int num, Shader.Mask mask) { set_texel_masks(self, index, num, mask.value); return this; }
	public Pipeline setTexelMasks(int index, int num, Shader.Mask.Enum mask) { set_texel_masks(self, index, num, mask.value); return this; }
	public Shader.Mask getTexelMasks(int index, int num) { return new Shader.Mask(get_texel_masks(self, index, num)); }
	public int addTable(TableType type, int size, Shader.Mask mask) { return add_table(self, type.value, size, mask.value, BindFlags.BindFlagNone.value); }
	public int addTable(TableType.Enum type, int size, Shader.Mask mask) { return add_table(self, type.value, size, mask.value, BindFlags.BindFlagNone.value); }
	public int addTable(TableType.Enum type, int size, Shader.Mask.Enum mask) { return add_table(self, type.value, size, mask.value, BindFlags.BindFlagNone.value); }
	public int addTable(TableType type, int size, Shader.Mask.Enum mask) { return add_table(self, type.value, size, mask.value, BindFlags.BindFlagNone.value); }
	public int addTable(TableType type, int size, Shader.Mask mask, BindFlags flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType.Enum type, int size, Shader.Mask mask, BindFlags flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType.Enum type, int size, Shader.Mask.Enum mask, BindFlags flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType.Enum type, int size, Shader.Mask mask, BindFlags.Enum flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType type, int size, Shader.Mask.Enum mask, BindFlags flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType type, int size, Shader.Mask.Enum mask, BindFlags.Enum flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int addTable(TableType type, int size, Shader.Mask mask, BindFlags.Enum flags) { return add_table(self, type.value, size, mask.value, flags.value); }
	public int getNumTables() { return get_num_tables(self); }
	public Pipeline setTableOffset(int offset) { set_table_offset(self, offset); return this; }
	public int getTableOffset() { return get_table_offset(self); }
	public Pipeline setTableType(int index, TableType type, int size, Shader.Mask mask) { set_table_type(self, index, type.value, size, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setTableType(int index, TableType.Enum type, int size, Shader.Mask mask) { set_table_type(self, index, type.value, size, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setTableType(int index, TableType.Enum type, int size, Shader.Mask.Enum mask) { set_table_type(self, index, type.value, size, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setTableType(int index, TableType type, int size, Shader.Mask.Enum mask) { set_table_type(self, index, type.value, size, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setTableType(int index, TableType type, int size, Shader.Mask mask, BindFlags flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Pipeline setTableType(int index, TableType.Enum type, int size, Shader.Mask mask, BindFlags flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Pipeline setTableType(int index, TableType.Enum type, int size, Shader.Mask.Enum mask, BindFlags flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Pipeline setTableType(int index, TableType.Enum type, int size, Shader.Mask mask, BindFlags.Enum flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Pipeline setTableType(int index, TableType type, int size, Shader.Mask.Enum mask, BindFlags flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Pipeline setTableType(int index, TableType type, int size, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public Pipeline setTableType(int index, TableType type, int size, Shader.Mask mask, BindFlags.Enum flags) { set_table_type(self, index, type.value, size, mask.value, flags.value); return this; }
	public TableType getTableType(int index) { return new TableType(get_table_type(self, index)); }
	public int getTableSize(int index) { return get_table_size(self, index); }
	public Pipeline setTableMask(int index, Shader.Mask mask) { set_table_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setTableMask(int index, Shader.Mask.Enum mask) { set_table_mask(self, index, mask.value, BindFlags.BindFlagNone.value); return this; }
	public Pipeline setTableMask(int index, Shader.Mask mask, BindFlags flags) { set_table_mask(self, index, mask.value, flags.value); return this; }
	public Pipeline setTableMask(int index, Shader.Mask.Enum mask, BindFlags flags) { set_table_mask(self, index, mask.value, flags.value); return this; }
	public Pipeline setTableMask(int index, Shader.Mask.Enum mask, BindFlags.Enum flags) { set_table_mask(self, index, mask.value, flags.value); return this; }
	public Pipeline setTableMask(int index, Shader.Mask mask, BindFlags.Enum flags) { set_table_mask(self, index, mask.value, flags.value); return this; }
	public Shader.Mask getTableMask(int index) { return new Shader.Mask(get_table_mask(self, index)); }
	public Pipeline setTableFlags(int index, BindFlags flags) { set_table_flags(self, index, flags.value); return this; }
	public Pipeline setTableFlags(int index, BindFlags.Enum flags) { set_table_flags(self, index, flags.value); return this; }
	public BindFlags getTableFlags(int index) { return new BindFlags(get_table_flags(self, index)); }
	public int getNumVertices() { return get_num_vertices(self); }
	public int getVertexStride(int index) { return get_vertex_stride(self, index); }
	public int getVertexRate(int index) { return get_vertex_rate(self, index); }
	public int addAttribute(Attribute attribute, Format format, int vertex, long offset, long stride) { return add_attribute(self, attribute.value, format.value, vertex, offset, stride, 0); }
	public int addAttribute(Attribute.Enum attribute, Format format, int vertex, long offset, long stride) { return add_attribute(self, attribute.value, format.value, vertex, offset, stride, 0); }
	public int addAttribute(Attribute.Enum attribute, Format.Enum format, int vertex, long offset, long stride) { return add_attribute(self, attribute.value, format.value, vertex, offset, stride, 0); }
	public int addAttribute(Attribute attribute, Format.Enum format, int vertex, long offset, long stride) { return add_attribute(self, attribute.value, format.value, vertex, offset, stride, 0); }
	public int addAttribute(Attribute attribute, Format format, int vertex, long offset, long stride, int rate) { return add_attribute(self, attribute.value, format.value, vertex, offset, stride, rate); }
	public int addAttribute(Attribute.Enum attribute, Format format, int vertex, long offset, long stride, int rate) { return add_attribute(self, attribute.value, format.value, vertex, offset, stride, rate); }
	public int addAttribute(Attribute.Enum attribute, Format.Enum format, int vertex, long offset, long stride, int rate) { return add_attribute(self, attribute.value, format.value, vertex, offset, stride, rate); }
	public int addAttribute(Attribute attribute, Format.Enum format, int vertex, long offset, long stride, int rate) { return add_attribute(self, attribute.value, format.value, vertex, offset, stride, rate); }
	public Pipeline setAttribute(int index, Attribute attribute, Format format, int vertex, long offset, long stride) { set_attribute(self, index, attribute.value, format.value, vertex, offset, stride, 0); return this; }
	public Pipeline setAttribute(int index, Attribute.Enum attribute, Format format, int vertex, long offset, long stride) { set_attribute(self, index, attribute.value, format.value, vertex, offset, stride, 0); return this; }
	public Pipeline setAttribute(int index, Attribute.Enum attribute, Format.Enum format, int vertex, long offset, long stride) { set_attribute(self, index, attribute.value, format.value, vertex, offset, stride, 0); return this; }
	public Pipeline setAttribute(int index, Attribute attribute, Format.Enum format, int vertex, long offset, long stride) { set_attribute(self, index, attribute.value, format.value, vertex, offset, stride, 0); return this; }
	public Pipeline setAttribute(int index, Attribute attribute, Format format, int vertex, long offset, long stride, int rate) { set_attribute(self, index, attribute.value, format.value, vertex, offset, stride, rate); return this; }
	public Pipeline setAttribute(int index, Attribute.Enum attribute, Format format, int vertex, long offset, long stride, int rate) { set_attribute(self, index, attribute.value, format.value, vertex, offset, stride, rate); return this; }
	public Pipeline setAttribute(int index, Attribute.Enum attribute, Format.Enum format, int vertex, long offset, long stride, int rate) { set_attribute(self, index, attribute.value, format.value, vertex, offset, stride, rate); return this; }
	public Pipeline setAttribute(int index, Attribute attribute, Format.Enum format, int vertex, long offset, long stride, int rate) { set_attribute(self, index, attribute.value, format.value, vertex, offset, stride, rate); return this; }
	public Pipeline setAttributeType(int index, Attribute attribute) { set_attribute_type(self, index, attribute.value); return this; }
	public Pipeline setAttributeType(int index, Attribute.Enum attribute) { set_attribute_type(self, index, attribute.value); return this; }
	public Pipeline setAttributeFormat(int index, Format format) { set_attribute_format(self, index, format.value); return this; }
	public Pipeline setAttributeFormat(int index, Format.Enum format) { set_attribute_format(self, index, format.value); return this; }
	public Pipeline setAttributeVertex(int index, int vertex) { set_attribute_vertex(self, index, vertex); return this; }
	public Pipeline setAttributeOffset(int index, long offset) { set_attribute_offset(self, index, offset); return this; }
	public Pipeline setAttributeStride(int index, long stride) { set_attribute_stride(self, index, stride); return this; }
	public Pipeline setAttributeRate(int index, int rate) { set_attribute_rate(self, index, rate); return this; }
	public int getNumAttributes() { return get_num_attributes(self); }
	public Attribute getAttributeType(int index) { return new Attribute(get_attribute_type(self, index)); }
	public Format getAttributeFormat(int index) { return new Format(get_attribute_format(self, index)); }
	public int getAttributeVertex(int index) { return get_attribute_vertex(self, index); }
	public int getAttributeOffset(int index) { return get_attribute_offset(self, index); }
	public int getAttributeStride(int index) { return get_attribute_stride(self, index); }
	public int getAttributeRate(int index) { return get_attribute_rate(self, index); }
	public void setPrimitive(Primitive primitive) { set_primitive(self, primitive.value); }
	public void setPrimitive(Primitive.Enum primitive) { set_primitive(self, primitive.value); }
	public Primitive getPrimitive() { return new Primitive(get_primitive(self)); }
	public void setFillMode(FillMode mode) { set_fill_mode(self, mode.value); }
	public void setFillMode(FillMode.Enum mode) { set_fill_mode(self, mode.value); }
	public FillMode getFillMode() { return new FillMode(get_fill_mode(self)); }
	public void setCullMode(CullMode mode) { set_cull_mode(self, mode.value); }
	public void setCullMode(CullMode.Enum mode) { set_cull_mode(self, mode.value); }
	public CullMode getCullMode() { return new CullMode(get_cull_mode(self)); }
	public void setFrontMode(FrontMode mode) { set_front_mode(self, mode.value); }
	public void setFrontMode(FrontMode.Enum mode) { set_front_mode(self, mode.value); }
	public FrontMode getFrontMode() { return new FrontMode(get_front_mode(self)); }
	public void setDepthBias(float bias, float slope) { set_depth_bias(self, bias, slope, 0.0f); }
	public void setDepthBias(float bias, float slope, float clamp) { set_depth_bias(self, bias, slope, clamp); }
	public float getDepthBias() { return get_depth_bias(self); }
	public float getDepthSlope() { return get_depth_slope(self); }
	public float getDepthClamp() { return get_depth_clamp(self); }
	public void setMultisample(int multisample) { set_multisample(self, multisample); }
	public int getMultisample() { return get_multisample(self); }
	public void setSampleMask(int sample_mask) { set_sample_mask(self, sample_mask); }
	public int getSampleMask() { return get_sample_mask(self); }
	public void setDepthClip(boolean enabled) { set_depth_clip(self, enabled); }
	public boolean getDepthClip() { return get_depth_clip(self); }
	public void setDepthReplace(boolean enabled) { set_depth_replace(self, enabled); }
	public boolean getDepthReplace() { return get_depth_replace(self); }
	public void setScissorTest(boolean enabled) { set_scissor_test(self, enabled); }
	public boolean getScissorTest() { return get_scissor_test(self); }
	public void setRasterDiscard(boolean enabled) { set_raster_discard(self, enabled); }
	public boolean getRasterDiscard() { return get_raster_discard(self); }
	public void setSampleShading(boolean enabled) { set_sample_shading(self, enabled); }
	public boolean getSampleShading() { return get_sample_shading(self); }
	public void setAlphaToCoverage(boolean enabled) { set_alpha_to_coverage(self, enabled); }
	public boolean getAlphaToCoverage() { return get_alpha_to_coverage(self); }
	public void setMultisampleRaster(boolean enabled) { set_multisample_raster(self, enabled); }
	public boolean getMultisampleRaster() { return get_multisample_raster(self); }
	public void setConservativeRaster(boolean enabled) { set_conservative_raster(self, enabled); }
	public boolean getConservativeRaster() { return get_conservative_raster(self); }
	public void setNumViewports(int num_viewports) { set_num_viewports(self, num_viewports); }
	public int getNumTargets() { return get_num_targets(self); }
	public int getNumViewports() { return get_num_viewports(self); }
	public void setNumClipDistances(int num_distances) { set_num_clip_distances(self, num_distances); }
	public int getNumClipDistances() { return get_num_clip_distances(self); }
	public void setBlend(BlendOp op, BlendFunc src, BlendFunc dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(BlendOp.Enum op, BlendFunc src, BlendFunc dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(BlendOp.Enum op, BlendFunc.Enum src, BlendFunc dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(BlendOp.Enum op, BlendFunc src, BlendFunc.Enum dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(BlendOp op, BlendFunc.Enum src, BlendFunc dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(BlendOp op, BlendFunc.Enum src, BlendFunc.Enum dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlend(BlendOp op, BlendFunc src, BlendFunc.Enum dest) { set_blend(self, op.value, src.value, dest.value); }
	public void setBlendColor(BlendOp op, BlendFunc src, BlendFunc dest) { set_blend_color(self, op.value, src.value, dest.value); }
	public void setBlendColor(BlendOp.Enum op, BlendFunc src, BlendFunc dest) { set_blend_color(self, op.value, src.value, dest.value); }
	public void setBlendColor(BlendOp.Enum op, BlendFunc.Enum src, BlendFunc dest) { set_blend_color(self, op.value, src.value, dest.value); }
	public void setBlendColor(BlendOp.Enum op, BlendFunc src, BlendFunc.Enum dest) { set_blend_color(self, op.value, src.value, dest.value); }
	public void setBlendColor(BlendOp op, BlendFunc.Enum src, BlendFunc dest) { set_blend_color(self, op.value, src.value, dest.value); }
	public void setBlendColor(BlendOp op, BlendFunc.Enum src, BlendFunc.Enum dest) { set_blend_color(self, op.value, src.value, dest.value); }
	public void setBlendColor(BlendOp op, BlendFunc src, BlendFunc.Enum dest) { set_blend_color(self, op.value, src.value, dest.value); }
	public void setBlendAlpha(BlendOp op, BlendFunc src, BlendFunc dest) { set_blend_alpha(self, op.value, src.value, dest.value); }
	public void setBlendAlpha(BlendOp.Enum op, BlendFunc src, BlendFunc dest) { set_blend_alpha(self, op.value, src.value, dest.value); }
	public void setBlendAlpha(BlendOp.Enum op, BlendFunc.Enum src, BlendFunc dest) { set_blend_alpha(self, op.value, src.value, dest.value); }
	public void setBlendAlpha(BlendOp.Enum op, BlendFunc src, BlendFunc.Enum dest) { set_blend_alpha(self, op.value, src.value, dest.value); }
	public void setBlendAlpha(BlendOp op, BlendFunc.Enum src, BlendFunc dest) { set_blend_alpha(self, op.value, src.value, dest.value); }
	public void setBlendAlpha(BlendOp op, BlendFunc.Enum src, BlendFunc.Enum dest) { set_blend_alpha(self, op.value, src.value, dest.value); }
	public void setBlendAlpha(BlendOp op, BlendFunc src, BlendFunc.Enum dest) { set_blend_alpha(self, op.value, src.value, dest.value); }
	public void setBlend(int index, BlendOp op, BlendFunc src, BlendFunc dest) { set_blend_1(self, index, op.value, src.value, dest.value); }
	public void setBlend(int index, BlendOp.Enum op, BlendFunc src, BlendFunc dest) { set_blend_1(self, index, op.value, src.value, dest.value); }
	public void setBlend(int index, BlendOp.Enum op, BlendFunc.Enum src, BlendFunc dest) { set_blend_1(self, index, op.value, src.value, dest.value); }
	public void setBlend(int index, BlendOp.Enum op, BlendFunc src, BlendFunc.Enum dest) { set_blend_1(self, index, op.value, src.value, dest.value); }
	public void setBlend(int index, BlendOp op, BlendFunc.Enum src, BlendFunc dest) { set_blend_1(self, index, op.value, src.value, dest.value); }
	public void setBlend(int index, BlendOp op, BlendFunc.Enum src, BlendFunc.Enum dest) { set_blend_1(self, index, op.value, src.value, dest.value); }
	public void setBlend(int index, BlendOp op, BlendFunc src, BlendFunc.Enum dest) { set_blend_1(self, index, op.value, src.value, dest.value); }
	public void setBlendColor(int index, BlendOp op, BlendFunc src, BlendFunc dest) { set_blend_color_1(self, index, op.value, src.value, dest.value); }
	public void setBlendColor(int index, BlendOp.Enum op, BlendFunc src, BlendFunc dest) { set_blend_color_1(self, index, op.value, src.value, dest.value); }
	public void setBlendColor(int index, BlendOp.Enum op, BlendFunc.Enum src, BlendFunc dest) { set_blend_color_1(self, index, op.value, src.value, dest.value); }
	public void setBlendColor(int index, BlendOp.Enum op, BlendFunc src, BlendFunc.Enum dest) { set_blend_color_1(self, index, op.value, src.value, dest.value); }
	public void setBlendColor(int index, BlendOp op, BlendFunc.Enum src, BlendFunc dest) { set_blend_color_1(self, index, op.value, src.value, dest.value); }
	public void setBlendColor(int index, BlendOp op, BlendFunc.Enum src, BlendFunc.Enum dest) { set_blend_color_1(self, index, op.value, src.value, dest.value); }
	public void setBlendColor(int index, BlendOp op, BlendFunc src, BlendFunc.Enum dest) { set_blend_color_1(self, index, op.value, src.value, dest.value); }
	public void setBlendAlpha(int index, BlendOp op, BlendFunc src, BlendFunc dest) { set_blend_alpha_1(self, index, op.value, src.value, dest.value); }
	public void setBlendAlpha(int index, BlendOp.Enum op, BlendFunc src, BlendFunc dest) { set_blend_alpha_1(self, index, op.value, src.value, dest.value); }
	public void setBlendAlpha(int index, BlendOp.Enum op, BlendFunc.Enum src, BlendFunc dest) { set_blend_alpha_1(self, index, op.value, src.value, dest.value); }
	public void setBlendAlpha(int index, BlendOp.Enum op, BlendFunc src, BlendFunc.Enum dest) { set_blend_alpha_1(self, index, op.value, src.value, dest.value); }
	public void setBlendAlpha(int index, BlendOp op, BlendFunc.Enum src, BlendFunc dest) { set_blend_alpha_1(self, index, op.value, src.value, dest.value); }
	public void setBlendAlpha(int index, BlendOp op, BlendFunc.Enum src, BlendFunc.Enum dest) { set_blend_alpha_1(self, index, op.value, src.value, dest.value); }
	public void setBlendAlpha(int index, BlendOp op, BlendFunc src, BlendFunc.Enum dest) { set_blend_alpha_1(self, index, op.value, src.value, dest.value); }
	public BlendOp getBlendColorOp(int index) { return new BlendOp(get_blend_color_op(self, index)); }
	public BlendOp getBlendAlphaOp(int index) { return new BlendOp(get_blend_alpha_op(self, index)); }
	public BlendFunc getBlendSrcColorFunc(int index) { return new BlendFunc(get_blend_src_color_func(self, index)); }
	public BlendFunc getBlendSrcAlphaFunc(int index) { return new BlendFunc(get_blend_src_alpha_func(self, index)); }
	public BlendFunc getBlendDestColorFunc(int index) { return new BlendFunc(get_blend_dest_color_func(self, index)); }
	public BlendFunc getBlendDestAlphaFunc(int index) { return new BlendFunc(get_blend_dest_alpha_func(self, index)); }
	public void setColorMask(ColorMask mask) { set_color_mask(self, mask.value); }
	public void setColorMask(ColorMask.Enum mask) { set_color_mask(self, mask.value); }
	public void setColorMask(int index, ColorMask mask) { set_color_mask_1(self, index, mask.value); }
	public void setColorMask(int index, ColorMask.Enum mask) { set_color_mask_1(self, index, mask.value); }
	public void setColorFormat(int index, Format format) { set_color_format(self, index, format.value); }
	public void setColorFormat(int index, Format.Enum format) { set_color_format(self, index, format.value); }
	public void setColorFormat(Format format) { set_color_format_1(self, format.value, 1); }
	public void setColorFormat(Format.Enum format) { set_color_format_1(self, format.value, 1); }
	public void setColorFormat(Format format, int num) { set_color_format_1(self, format.value, num); }
	public void setColorFormat(Format.Enum format, int num) { set_color_format_1(self, format.value, num); }
	public ColorMask getColorMask(int index) { return new ColorMask(get_color_mask(self, index)); }
	public Format getColorFormat(int index) { return new Format(get_color_format(self, index)); }
	public void setDepthMask(DepthMask mask) { set_depth_mask(self, mask.value); }
	public void setDepthMask(DepthMask.Enum mask) { set_depth_mask(self, mask.value); }
	public void setDepthFunc(DepthFunc func) { set_depth_func(self, func.value); }
	public void setDepthFunc(DepthFunc.Enum func) { set_depth_func(self, func.value); }
	public void setDepthFormat(Format format) { set_depth_format(self, format.value); }
	public void setDepthFormat(Format.Enum format) { set_depth_format(self, format.value); }
	public DepthMask getDepthMask() { return new DepthMask(get_depth_mask(self)); }
	public DepthFunc getDepthFunc() { return new DepthFunc(get_depth_func(self)); }
	public Format getDepthFormat() { return new Format(get_depth_format(self)); }
	public void setStencilMask(int mask) { set_stencil_mask(self, mask); }
	public void setStencilBackMask(int mask) { set_stencil_back_mask(self, mask); }
	public void setStencilFrontMask(int mask) { set_stencil_front_mask(self, mask); }
	public void setStencilFunc(StencilFunc func, StencilOp dpass_op) { set_stencil_func(self, func.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc.Enum func, StencilOp dpass_op) { set_stencil_func(self, func.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc.Enum func, StencilOp.Enum dpass_op) { set_stencil_func(self, func.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc func, StencilOp.Enum dpass_op) { set_stencil_func(self, func.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc func, StencilOp dpass_op) { set_stencil_back_func(self, func.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc.Enum func, StencilOp dpass_op) { set_stencil_back_func(self, func.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc.Enum func, StencilOp.Enum dpass_op) { set_stencil_back_func(self, func.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc func, StencilOp.Enum dpass_op) { set_stencil_back_func(self, func.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc func, StencilOp dpass_op) { set_stencil_front_func(self, func.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc.Enum func, StencilOp dpass_op) { set_stencil_front_func(self, func.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc.Enum func, StencilOp.Enum dpass_op) { set_stencil_front_func(self, func.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc func, StencilOp.Enum dpass_op) { set_stencil_front_func(self, func.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc func, StencilOp fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc.Enum func, StencilOp fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc.Enum func, StencilOp.Enum fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc.Enum func, StencilOp fail_op, StencilOp.Enum dfail_op, StencilOp dpass_op) { set_stencil_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc.Enum func, StencilOp fail_op, StencilOp dfail_op, StencilOp.Enum dpass_op) { set_stencil_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc func, StencilOp.Enum fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc func, StencilOp.Enum fail_op, StencilOp.Enum dfail_op, StencilOp dpass_op) { set_stencil_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc func, StencilOp.Enum fail_op, StencilOp dfail_op, StencilOp.Enum dpass_op) { set_stencil_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc func, StencilOp fail_op, StencilOp.Enum dfail_op, StencilOp dpass_op) { set_stencil_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc func, StencilOp fail_op, StencilOp.Enum dfail_op, StencilOp.Enum dpass_op) { set_stencil_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFunc(StencilFunc func, StencilOp fail_op, StencilOp dfail_op, StencilOp.Enum dpass_op) { set_stencil_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc func, StencilOp fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_back_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc.Enum func, StencilOp fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_back_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc.Enum func, StencilOp.Enum fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_back_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc.Enum func, StencilOp fail_op, StencilOp.Enum dfail_op, StencilOp dpass_op) { set_stencil_back_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc.Enum func, StencilOp fail_op, StencilOp dfail_op, StencilOp.Enum dpass_op) { set_stencil_back_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc func, StencilOp.Enum fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_back_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc func, StencilOp.Enum fail_op, StencilOp.Enum dfail_op, StencilOp dpass_op) { set_stencil_back_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc func, StencilOp.Enum fail_op, StencilOp dfail_op, StencilOp.Enum dpass_op) { set_stencil_back_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc func, StencilOp fail_op, StencilOp.Enum dfail_op, StencilOp dpass_op) { set_stencil_back_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc func, StencilOp fail_op, StencilOp.Enum dfail_op, StencilOp.Enum dpass_op) { set_stencil_back_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilBackFunc(StencilFunc func, StencilOp fail_op, StencilOp dfail_op, StencilOp.Enum dpass_op) { set_stencil_back_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc func, StencilOp fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_front_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc.Enum func, StencilOp fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_front_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc.Enum func, StencilOp.Enum fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_front_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc.Enum func, StencilOp fail_op, StencilOp.Enum dfail_op, StencilOp dpass_op) { set_stencil_front_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc.Enum func, StencilOp fail_op, StencilOp dfail_op, StencilOp.Enum dpass_op) { set_stencil_front_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc func, StencilOp.Enum fail_op, StencilOp dfail_op, StencilOp dpass_op) { set_stencil_front_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc func, StencilOp.Enum fail_op, StencilOp.Enum dfail_op, StencilOp dpass_op) { set_stencil_front_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc func, StencilOp.Enum fail_op, StencilOp dfail_op, StencilOp.Enum dpass_op) { set_stencil_front_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc func, StencilOp fail_op, StencilOp.Enum dfail_op, StencilOp dpass_op) { set_stencil_front_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc func, StencilOp fail_op, StencilOp.Enum dfail_op, StencilOp.Enum dpass_op) { set_stencil_front_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public void setStencilFrontFunc(StencilFunc func, StencilOp fail_op, StencilOp dfail_op, StencilOp.Enum dpass_op) { set_stencil_front_func_1(self, func.value, fail_op.value, dfail_op.value, dpass_op.value); }
	public int getStencilBackMask() { return get_stencil_back_mask(self); }
	public StencilFunc getStencilBackFunc() { return new StencilFunc(get_stencil_back_func(self)); }
	public StencilOp getStencilBackFailOp() { return new StencilOp(get_stencil_back_fail_op(self)); }
	public StencilOp getStencilBackDepthFailOp() { return new StencilOp(get_stencil_back_depth_fail_op(self)); }
	public StencilOp getStencilBackDepthPassOp() { return new StencilOp(get_stencil_back_depth_pass_op(self)); }
	public int getStencilFrontMask() { return get_stencil_front_mask(self); }
	public StencilFunc getStencilFrontFunc() { return new StencilFunc(get_stencil_front_func(self)); }
	public StencilOp getStencilFrontFailOp() { return new StencilOp(get_stencil_front_fail_op(self)); }
	public StencilOp getStencilFrontDepthFailOp() { return new StencilOp(get_stencil_front_depth_fail_op(self)); }
	public StencilOp getStencilFrontDepthPassOp() { return new StencilOp(get_stencil_front_depth_pass_op(self)); }
	
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
	private static native int get_platform(long self);
	private static native String get_platform_name(long self);
	private static native int get_index(long self);
	private static native void clear_(long self);
	private static native boolean is_created(long self);
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native boolean create_(long self);
	private static native void set_parameters(long self, long pipeline);
	private static native boolean save_state(long self, long stream);
	private static native void add_shader(long self, long shader, boolean owner);
	private static native long get_vertex_shader(long self);
	private static native long get_control_shader(long self);
	private static native long get_evaluate_shader(long self);
	private static native long get_geometry_shader(long self);
	private static native long get_fragment_shader(long self);
	private static native long get_task_shader(long self);
	private static native long get_mesh_shader(long self);
	private static native boolean load_shader(long self, int type, String name, String format);
	private static native boolean load_shader_glsl(long self, int type, String name, String format);
	private static native boolean load_shader_1(long self, int type, String name, long macros, String[] includes, int size);
	private static native boolean load_shader_glsl_1(long self, int type, String name, long macros, String[] includes, int size);
	private static native boolean load_shader_spirv(long self, int type, String name);
	private static native boolean create_shader(long self, int type, String src, String format);
	private static native boolean create_shader_glsl(long self, int type, String src, String format);
	private static native boolean create_shader_1(long self, int type, String src, long macros, String[] includes, int size);
	private static native boolean create_shader_glsl_1(long self, int type, String src, long macros, String[] includes, int size);
	private static native boolean create_shader_spirv(long self, int type, int[] data);
	private static native int add_sampler(long self, int mask);
	private static native int get_num_samplers(long self);
	private static native long set_sampler_offset(long self, int offset);
	private static native int get_sampler_offset(long self);
	private static native long set_sampler_mask(long self, int index, int mask);
	private static native int get_sampler_mask(long self, int index);
	private static native long set_sampler_masks(long self, int index, int num, int mask, boolean array);
	private static native int get_sampler_masks(long self, int index, int num);
	private static native long set_sampler_array(long self, int index, int num, boolean array);
	private static native int get_sampler_array(long self, int index);
	private static native int add_texture(long self, int mask);
	private static native int get_num_textures(long self);
	private static native long set_texture_offset(long self, int offset);
	private static native int get_texture_offset(long self);
	private static native long set_texture_mask(long self, int index, int mask);
	private static native int get_texture_mask(long self, int index);
	private static native long set_texture_masks(long self, int index, int num, int mask, boolean array);
	private static native int get_texture_masks(long self, int index, int num);
	private static native long set_texture_array(long self, int index, int num, boolean array);
	private static native int get_texture_array(long self, int index);
	private static native int add_surface(long self, int mask);
	private static native int get_num_surfaces(long self);
	private static native long set_surface_offset(long self, int offset);
	private static native int get_surface_offset(long self);
	private static native long set_surface_mask(long self, int index, int mask);
	private static native int get_surface_mask(long self, int index);
	private static native long set_surface_masks(long self, int index, int num, int mask, boolean array);
	private static native int get_surface_masks(long self, int index, int num);
	private static native long set_surface_array(long self, int index, int num, boolean array);
	private static native int get_surface_array(long self, int index);
	private static native int add_uniform(long self, int mask, int flags);
	private static native int get_num_uniforms(long self);
	private static native long set_uniform_offset(long self, int offset);
	private static native int get_uniform_offset(long self);
	private static native long set_uniform_mask(long self, int index, int mask, int flags);
	private static native int get_uniform_mask(long self, int index);
	private static native long set_uniform_masks(long self, int index, int num, int mask, int flags);
	private static native int get_uniform_masks(long self, int index, int num);
	private static native long set_uniform_flags(long self, int index, int flags);
	private static native int get_uniform_flags(long self, int index);
	private static native int add_storage(long self, int mask, int flags);
	private static native int get_num_storages(long self);
	private static native long set_storage_offset(long self, int offset);
	private static native int get_storage_offset(long self);
	private static native long set_storage_mask(long self, int index, int mask, int flags);
	private static native int get_storage_mask(long self, int index);
	private static native long set_storage_masks(long self, int index, int num, int mask, int flags);
	private static native int get_storage_masks(long self, int index, int num);
	private static native long set_storage_flags(long self, int index, int flags);
	private static native int get_storage_flags(long self, int index);
	private static native int add_tracing(long self, int mask);
	private static native int get_num_tracings(long self);
	private static native long set_tracing_offset(long self, int offset);
	private static native int get_tracing_offset(long self);
	private static native long set_tracing_mask(long self, int index, int mask);
	private static native int get_tracing_mask(long self, int index);
	private static native long set_tracing_masks(long self, int index, int num, int mask);
	private static native int get_tracing_masks(long self, int index, int num);
	private static native int add_texel(long self, int mask);
	private static native int get_num_texels(long self);
	private static native long set_texel_offset(long self, int offset);
	private static native int get_texel_offset(long self);
	private static native long set_texel_mask(long self, int index, int mask);
	private static native int get_texel_mask(long self, int index);
	private static native long set_texel_masks(long self, int index, int num, int mask);
	private static native int get_texel_masks(long self, int index, int num);
	private static native int add_table(long self, int type, int size, int mask, int flags);
	private static native int get_num_tables(long self);
	private static native long set_table_offset(long self, int offset);
	private static native int get_table_offset(long self);
	private static native long set_table_type(long self, int index, int type, int size, int mask, int flags);
	private static native int get_table_type(long self, int index);
	private static native int get_table_size(long self, int index);
	private static native long set_table_mask(long self, int index, int mask, int flags);
	private static native int get_table_mask(long self, int index);
	private static native long set_table_flags(long self, int index, int flags);
	private static native int get_table_flags(long self, int index);
	private static native int get_num_vertices(long self);
	private static native int get_vertex_stride(long self, int index);
	private static native int get_vertex_rate(long self, int index);
	private static native int add_attribute(long self, int attribute, int format, int vertex, long offset, long stride, int rate);
	private static native long set_attribute(long self, int index, int attribute, int format, int vertex, long offset, long stride, int rate);
	private static native long set_attribute_type(long self, int index, int attribute);
	private static native long set_attribute_format(long self, int index, int format);
	private static native long set_attribute_vertex(long self, int index, int vertex);
	private static native long set_attribute_offset(long self, int index, long offset);
	private static native long set_attribute_stride(long self, int index, long stride);
	private static native long set_attribute_rate(long self, int index, int rate);
	private static native int get_num_attributes(long self);
	private static native int get_attribute_type(long self, int index);
	private static native int get_attribute_format(long self, int index);
	private static native int get_attribute_vertex(long self, int index);
	private static native int get_attribute_offset(long self, int index);
	private static native int get_attribute_stride(long self, int index);
	private static native int get_attribute_rate(long self, int index);
	private static native void set_primitive(long self, int primitive);
	private static native int get_primitive(long self);
	private static native void set_fill_mode(long self, int mode);
	private static native int get_fill_mode(long self);
	private static native void set_cull_mode(long self, int mode);
	private static native int get_cull_mode(long self);
	private static native void set_front_mode(long self, int mode);
	private static native int get_front_mode(long self);
	private static native void set_depth_bias(long self, float bias, float slope, float clamp);
	private static native float get_depth_bias(long self);
	private static native float get_depth_slope(long self);
	private static native float get_depth_clamp(long self);
	private static native void set_multisample(long self, int multisample);
	private static native int get_multisample(long self);
	private static native void set_sample_mask(long self, int sample_mask);
	private static native int get_sample_mask(long self);
	private static native void set_depth_clip(long self, boolean enabled);
	private static native boolean get_depth_clip(long self);
	private static native void set_depth_replace(long self, boolean enabled);
	private static native boolean get_depth_replace(long self);
	private static native void set_scissor_test(long self, boolean enabled);
	private static native boolean get_scissor_test(long self);
	private static native void set_raster_discard(long self, boolean enabled);
	private static native boolean get_raster_discard(long self);
	private static native void set_sample_shading(long self, boolean enabled);
	private static native boolean get_sample_shading(long self);
	private static native void set_alpha_to_coverage(long self, boolean enabled);
	private static native boolean get_alpha_to_coverage(long self);
	private static native void set_multisample_raster(long self, boolean enabled);
	private static native boolean get_multisample_raster(long self);
	private static native void set_conservative_raster(long self, boolean enabled);
	private static native boolean get_conservative_raster(long self);
	private static native void set_num_viewports(long self, int num_viewports);
	private static native int get_num_targets(long self);
	private static native int get_num_viewports(long self);
	private static native void set_num_clip_distances(long self, int num_distances);
	private static native int get_num_clip_distances(long self);
	private static native void set_blend(long self, int op, int src, int dest);
	private static native void set_blend_color(long self, int op, int src, int dest);
	private static native void set_blend_alpha(long self, int op, int src, int dest);
	private static native void set_blend_1(long self, int index, int op, int src, int dest);
	private static native void set_blend_color_1(long self, int index, int op, int src, int dest);
	private static native void set_blend_alpha_1(long self, int index, int op, int src, int dest);
	private static native int get_blend_color_op(long self, int index);
	private static native int get_blend_alpha_op(long self, int index);
	private static native int get_blend_src_color_func(long self, int index);
	private static native int get_blend_src_alpha_func(long self, int index);
	private static native int get_blend_dest_color_func(long self, int index);
	private static native int get_blend_dest_alpha_func(long self, int index);
	private static native void set_color_mask(long self, int mask);
	private static native void set_color_mask_1(long self, int index, int mask);
	private static native void set_color_format(long self, int index, int format);
	private static native void set_color_format_1(long self, int format, int num);
	private static native int get_color_mask(long self, int index);
	private static native int get_color_format(long self, int index);
	private static native void set_depth_mask(long self, int mask);
	private static native void set_depth_func(long self, int func);
	private static native void set_depth_format(long self, int format);
	private static native int get_depth_mask(long self);
	private static native int get_depth_func(long self);
	private static native int get_depth_format(long self);
	private static native void set_stencil_mask(long self, int mask);
	private static native void set_stencil_back_mask(long self, int mask);
	private static native void set_stencil_front_mask(long self, int mask);
	private static native void set_stencil_func(long self, int func, int dpass_op);
	private static native void set_stencil_back_func(long self, int func, int dpass_op);
	private static native void set_stencil_front_func(long self, int func, int dpass_op);
	private static native void set_stencil_func_1(long self, int func, int fail_op, int dfail_op, int dpass_op);
	private static native void set_stencil_back_func_1(long self, int func, int fail_op, int dfail_op, int dpass_op);
	private static native void set_stencil_front_func_1(long self, int func, int fail_op, int dfail_op, int dpass_op);
	private static native int get_stencil_back_mask(long self);
	private static native int get_stencil_back_func(long self);
	private static native int get_stencil_back_fail_op(long self);
	private static native int get_stencil_back_depth_fail_op(long self);
	private static native int get_stencil_back_depth_pass_op(long self);
	private static native int get_stencil_front_mask(long self);
	private static native int get_stencil_front_func(long self);
	private static native int get_stencil_front_fail_op(long self);
	private static native int get_stencil_front_depth_fail_op(long self);
	private static native int get_stencil_front_depth_pass_op(long self);
	
	protected Pipeline(long self) {
		init_(self);
	}
	public static Pipeline Null() {
		return new Pipeline((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Pipeline[] ptr) {
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
