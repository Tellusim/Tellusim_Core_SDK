// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class CanvasMesh extends CanvasElement {
	
	public CanvasMesh() { init_(new_()); }
	public CanvasMesh(Canvas canvas) { init_(new_1(canvas.self)); }
	public CanvasMesh(Canvas canvas, Mode mode) { init_(new_2(canvas.self, mode.value)); }
	public CanvasMesh(Canvas canvas, Mode.Enum mode) { init_(new_2(canvas.self, mode.value)); }
	public CanvasMesh[] ref() { return new CanvasMesh[] { this }; }
	public CanvasMesh(CanvasElement base) { init_(cast_canvas_element_ptr(base.self)); }
	public CanvasElement toCanvasElement() { return new CanvasElement(base_canvas_element_ptr(self)); }
	public void setTextureName(String name) { set_texture_name(self, name); }
	public void setTextureName(TSString name) { set_texture_name_1(self, name.self); }
	public String getTextureName() { return get_texture_name(self); }
	public void setGradientStyle(GradientStyle style) { set_gradient_style(self, style.self); }
	public GradientStyle getGradientStyleConst() { return new GradientStyle(get_gradient_style_const(self)); }
	public GradientStyle getGradientStyle() { return new GradientStyle(get_gradient_style(self)); }
	public void clearVertices() { clear_vertices(self); }
	public void setNumVertices(int num_vertices) { set_num_vertices(self, num_vertices); }
	public void reserveVertices(int num_vertices) { reserve_vertices(self, num_vertices); }
	public int getNumVertices() { return get_num_vertices(self); }
	public void setVertices(CanvasVertex[] vertices) { set_vertices(self, CanvasVertex.self_(vertices)); }
	public void addVertices(CanvasVertex[] vertices) { add_vertices(self, CanvasVertex.self_(vertices)); }
	public CanvasVertex getVertices() { return new CanvasVertex(get_vertices(self)); }
	public void setVertex(int index, CanvasVertex vertex) { set_vertex(self, index, vertex.self); }
	public CanvasVertex getVertex(int index) { return new CanvasVertex(get_vertex(self, index)); }
	public void setVertexPosition(int index, Vector3f position) { set_vertex_position(self, index, position.self); }
	public void setVertexPosition(int index, float x, float y) { set_vertex_position_1(self, index, x, y, 0.0f); }
	public void setVertexPosition(int index, float x, float y, float z) { set_vertex_position_1(self, index, x, y, z); }
	public Vector3f getVertexPosition(int index) { return new Vector3f(get_vertex_position(self, index)); }
	public void setVertexTexCoord(int index, Vector2f texcoord) { set_vertex_tex_coord(self, index, texcoord.self); }
	public void setVertexTexCoord(int index, float s, float t) { set_vertex_tex_coord_1(self, index, s, t); }
	public Vector2f getVertexTexCoord(int index) { return new Vector2f(get_vertex_tex_coord(self, index)); }
	public void setVertexColor(int index, Color color) { set_vertex_color(self, index, color.self); }
	public void setVertexColor(int index, int color) { set_vertex_color_1(self, index, color); }
	public int getVertexColor(int index) { return get_vertex_color(self, index); }
	public int addVertex(Vector3f position) { return add_vertex(self, position.self); }
	public int addVertex(Vector3f position, int color) { return add_vertex_1(self, position.self, color); }
	public int addVertex(Vector3f position, Vector2f texcoord) { return add_vertex_2(self, position.self, texcoord.self); }
	public int addVertex(Vector3f position, Vector2f texcoord, int color) { return add_vertex_3(self, position.self, texcoord.self, color); }
	public int addVertex(float x, float y, float z, float s, float t) { return add_vertex_4(self, x, y, z, s, t, 0xffffffff); }
	public int addVertex(float x, float y, float z, float s, float t, int color) { return add_vertex_4(self, x, y, z, s, t, color); }
	public int addVertex(float x, float y, float z) { return add_vertex_5(self, x, y, z, 0xffffffff); }
	public int addVertex(float x, float y, float z, int color) { return add_vertex_5(self, x, y, z, color); }
	public int addVertex(float x, float y) { return add_vertex_6(self, x, y, 0xffffffff); }
	public int addVertex(float x, float y, int color) { return add_vertex_6(self, x, y, color); }
	public void clearIndices() { clear_indices(self); }
	public void setNumIndices(int num_indices) { set_num_indices(self, num_indices); }
	public void reserveIndices(int num_indices) { reserve_indices(self, num_indices); }
	public int getNumIndices() { return get_num_indices(self); }
	public void setIndices(int[] indices) { set_indices(self, indices); }
	public void addIndices(int[] indices) { add_indices(self, indices); }
	public long getIndices() { return get_indices(self); }
	public void setIndex(int index, int value) { set_index(self, index, value); }
	public int getIndex(int index) { return get_index(self, index); }
	public void addIndex(int i0) { add_index(self, i0); }
	public void addIndices(int i0, int i1) { add_indices_1(self, i0, i1); }
	public void addIndices(int i0, int i1, int i2) { add_indices_2(self, i0, i1, i2); }
	public void addIndices(int i0, int i1, int i2, int i3) { add_indices_3(self, i0, i1, i2, i3); }
	public void setRect(Rect rect) { set_rect(self, rect.self); }
	
	private static native long new_();
	private static native long new_1(long canvas);
	private static native long new_2(long canvas, int mode);
	private static native void delete_(long self);
	private static native boolean equal_canvas_element_ptr(long self, long base);
	private static native long cast_canvas_element_ptr(long self);
	private static native long base_canvas_element_ptr(long self);
	private static native void set_texture_name(long self, String name);
	private static native void set_texture_name_1(long self, long name);
	private static native String get_texture_name(long self);
	private static native void set_gradient_style(long self, long style);
	private static native long get_gradient_style_const(long self);
	private static native long get_gradient_style(long self);
	private static native long get_gradient_style_1(long self);
	private static native void clear_vertices(long self);
	private static native void set_num_vertices(long self, int num_vertices);
	private static native void reserve_vertices(long self, int num_vertices);
	private static native int get_num_vertices(long self);
	private static native void set_vertices(long self, long[] vertices);
	private static native void add_vertices(long self, long[] vertices);
	private static native long get_vertices(long self);
	private static native long get_vertices_1(long self);
	private static native void set_vertex(long self, int index, long vertex);
	private static native long get_vertex(long self, int index);
	private static native long get_vertex_1(long self, int index);
	private static native void set_vertex_position(long self, int index, long position);
	private static native void set_vertex_position_1(long self, int index, float x, float y, float z);
	private static native long get_vertex_position(long self, int index);
	private static native void set_vertex_tex_coord(long self, int index, long texcoord);
	private static native void set_vertex_tex_coord_1(long self, int index, float s, float t);
	private static native long get_vertex_tex_coord(long self, int index);
	private static native void set_vertex_color(long self, int index, long color);
	private static native void set_vertex_color_1(long self, int index, int color);
	private static native int get_vertex_color(long self, int index);
	private static native int add_vertex(long self, long position);
	private static native int add_vertex_1(long self, long position, int color);
	private static native int add_vertex_2(long self, long position, long texcoord);
	private static native int add_vertex_3(long self, long position, long texcoord, int color);
	private static native int add_vertex_4(long self, float x, float y, float z, float s, float t, int color);
	private static native int add_vertex_5(long self, float x, float y, float z, int color);
	private static native int add_vertex_6(long self, float x, float y, int color);
	private static native void clear_indices(long self);
	private static native void set_num_indices(long self, int num_indices);
	private static native void reserve_indices(long self, int num_indices);
	private static native int get_num_indices(long self);
	private static native void set_indices(long self, int[] indices);
	private static native void add_indices(long self, int[] indices);
	private static native long get_indices(long self);
	private static native long get_indices_1(long self);
	private static native void set_index(long self, int index, int value);
	private static native int get_index(long self, int index);
	private static native void add_index(long self, int i0);
	private static native void add_indices_1(long self, int i0, int i1);
	private static native void add_indices_2(long self, int i0, int i1, int i2);
	private static native void add_indices_3(long self, int i0, int i1, int i2, int i3);
	private static native void set_rect(long self, long rect);
	
	protected CanvasMesh(long self) {
		init_(self);
	}
	public static CanvasMesh Null() {
		return new CanvasMesh((long)0);
	}
}
