// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_QT_VK_WIDGET_H__
#define __TELLUSIM_QT_VK_WIDGET_H__

#if _WIN32
	#include <windows.h>
	#define VK_USE_PLATFORM_WIN32_KHR	1
#else
	#include <X11/Xlib.h>
	#define VK_USE_PLATFORM_XLIB_KHR	1
	#define VK_USE_PLATFORM_WAYLAND_KHR	1
	#undef KeyPress
	#undef KeyRelease
	#undef FocusIn
	#undef FocusOut
	#undef FontChange
	#undef CursorShape
	#undef Expose
	#undef Status
	#undef None
	#undef Bool
	#undef Ok
#endif

#include <vulkan/vulkan.h>

#include <QtCore/QTimer>
#include <QtWidgets/QWidget>

#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimSurface.h>

/*
 */
#define EXTERNAL_DEVICE		1

/*
 */
namespace Tellusim {
	
	/*
	 */
	class QVKWidget : public QWidget {
			
			Q_OBJECT
			
		public:
			
			QVKWidget(QWidget *parent = nullptr);
			~QVKWidget();
			
			virtual QSize sizeHint() const;
			
		protected:
			
			virtual QPaintEngine *paintEngine() const { return nullptr; }
			
			virtual void paintEvent(QPaintEvent *event);
			
		private:
			
			/// create context
			bool create_context();
			void release_context();
			
			/// create swap chain
			bool create_swap_chain();
			void release_swap_chain();
			
			/// create buffers
			bool create_buffers();
			void release_buffers();
			
			/// image barrier
			VkPipelineStageFlags get_stage_mask(VkAccessFlags access_mask) const;
			void barrier(VkImage image, VkAccessFlags src_mask, VkAccessFlags dest_mask, VkImageLayout old_layout, VkImageLayout new_layout, VkImageAspectFlags aspect_mask);
			
			/// rendering loop
			bool create_vk();
			void release_vk();
			void render_vk();
			
			enum {
				NumFrames = 3,
			};
			
			struct Frame {
				VkImage color_image = VK_NULL_HANDLE;
				VkImageView color_image_view = VK_NULL_HANDLE;
				VkSemaphore acquire_semaphore = VK_NULL_HANDLE;
				VkSemaphore present_semaphore = VK_NULL_HANDLE;
				VkSemaphore wait_semaphore = VK_NULL_HANDLE;
				VkFramebuffer framebuffer = VK_NULL_HANDLE;
			};
			
			bool failed = false;
			bool initialized = false;
			
			uint32_t widget_width = 0;
			uint32_t widget_height = 0;
			
			VkInstance vk_instance = VK_NULL_HANDLE;
			VkPhysicalDevice vk_adapter = VK_NULL_HANDLE;
			VkDevice vk_device = VK_NULL_HANDLE;
			uint32_t vk_family = Maxu32;
			
			VkSurfaceKHR vk_surface = VK_NULL_HANDLE;
			VkRenderPass render_pass = VK_NULL_HANDLE;
			VkSwapchainKHR swap_chain = VK_NULL_HANDLE;
			
			Array<Frame> frames;
			uint32_t frame_index = 0;
			VkSurfaceFormatKHR color_format = {};
			
			VkFormat depth_image_format = VK_FORMAT_UNDEFINED;
			VKTexture depth_stencil_texture;
			
			VKContext vk_context;
			VKSurface surface;
			Device device;
			
			Pipeline pipeline;
			Buffer vertex_buffer;
			Buffer index_buffer;
			
			QTimer timer;
			
			#if EXTERNAL_DEVICE
				PFN_vkCreateInstance vkCreateInstance = nullptr;
				PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices = nullptr;
				PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties = nullptr;
				PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties = nullptr;
				PFN_vkCreateDevice vkCreateDevice = nullptr;
				PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = nullptr;
			#endif
			PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR = nullptr;
			PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR = nullptr;
			PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR = nullptr;
			PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR = nullptr;
			PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties = nullptr;
			#if _WIN32
				PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR = nullptr;
			#else
				PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR = nullptr;
				PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR = nullptr;
			#endif
			PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR = nullptr;
			PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR = nullptr;
			PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR = nullptr;
			PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR = nullptr;
			PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR = nullptr;
			PFN_vkQueuePresentKHR vkQueuePresentKHR = nullptr;
			PFN_vkQueueSubmit vkQueueSubmit = nullptr;
			PFN_vkCreateSemaphore vkCreateSemaphore = nullptr;
			PFN_vkDestroySemaphore vkDestroySemaphore = nullptr;
			PFN_vkCreateImageView vkCreateImageView = nullptr;
			PFN_vkDestroyImageView vkDestroyImageView = nullptr;
			PFN_vkCreateRenderPass vkCreateRenderPass = nullptr;
			PFN_vkDestroyRenderPass vkDestroyRenderPass = nullptr;
			PFN_vkCreateFramebuffer vkCreateFramebuffer = nullptr;
			PFN_vkDestroyFramebuffer vkDestroyFramebuffer = nullptr;
			PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier = nullptr;
	};
}

#endif /* __TELLUSIM_QT_VK_WIDGET_H__ */
