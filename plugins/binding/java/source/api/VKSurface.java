// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class VKSurface extends Surface {
	
	public VKSurface() { init_(new_()); }
	public VKSurface(VKContext context) { init_(new_1(context.self)); }
	public VKSurface[] ref() { return new VKSurface[] { this }; }
	public VKSurface(Surface base) { init_(cast_surface_ptr(base.self)); }
	public Surface toSurface() { return new Surface(base_surface_ptr(self)); }
	public long getInstance() { return get_instance(self); }
	public long getAdapter() { return get_adapter(self); }
	public long getDevice() { return get_device(self); }
	public long getQueue() { return get_queue(self); }
	public long getCommand() { return get_command(self); }
	public int getFamily() { return get_family(self); }
	public void setSwapChain(long swap_chain) { set_swap_chain(self, swap_chain); }
	public long getSwapChain() { return get_swap_chain(self); }
	public void setColorImage(long image) { set_color_image(self, image); }
	public void setDepthImage(long image) { set_depth_image(self, image); }
	public long getColorImage() { return get_color_image(self); }
	public long getDepthImage() { return get_depth_image(self); }
	public void setColorImageView(long image_view) { set_color_image_view(self, image_view); }
	public void setDepthImageView(long image_view) { set_depth_image_view(self, image_view); }
	public long getColorImageView() { return get_color_image_view(self); }
	public long getDepthImageView() { return get_depth_image_view(self); }
	public void setRenderPass(long render_pass) { set_render_pass(self, render_pass); }
	public void setFramebuffer(long framebuffer) { set_framebuffer(self, framebuffer); }
	public long getRenderPass() { return get_render_pass(self); }
	public long getFramebuffer() { return get_framebuffer(self); }
	public int getColorPixelFormat() { return get_color_pixel_format(self); }
	public int getDepthPixelFormat() { return get_depth_pixel_format(self); }
	
	private static native long new_();
	private static native long new_1(long context);
	private static native void delete_(long self);
	private static native boolean equal_surface_ptr(long self, long base);
	private static native long cast_surface_ptr(long self);
	private static native long base_surface_ptr(long self);
	private static native long get_instance(long self);
	private static native long get_adapter(long self);
	private static native long get_device(long self);
	private static native long get_queue(long self);
	private static native long get_command(long self);
	private static native int get_family(long self);
	private static native void set_swap_chain(long self, long swap_chain);
	private static native long get_swap_chain(long self);
	private static native void set_color_image(long self, long image);
	private static native void set_depth_image(long self, long image);
	private static native long get_color_image(long self);
	private static native long get_depth_image(long self);
	private static native void set_color_image_view(long self, long image_view);
	private static native void set_depth_image_view(long self, long image_view);
	private static native long get_color_image_view(long self);
	private static native long get_depth_image_view(long self);
	private static native void set_render_pass(long self, long render_pass);
	private static native void set_framebuffer(long self, long framebuffer);
	private static native long get_render_pass(long self);
	private static native long get_framebuffer(long self);
	private static native int get_color_pixel_format(long self);
	private static native int get_depth_pixel_format(long self);
	
	protected VKSurface(long self) {
		init_(self);
	}
	public static VKSurface Null() {
		return new VKSurface((long)0);
	}
}
