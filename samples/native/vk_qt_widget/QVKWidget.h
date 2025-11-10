// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_QT_VK_WIDGET_H__
#define __TELLUSIM_QT_VK_WIDGET_H__

#include <vulkan/vulkan.h>

#include <QtCore/QTimer>
#include <QtWidgets/QWidget>

#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimSurface.h>

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
			
			VkImage depth_image = VK_NULL_HANDLE;
			VkImageView depth_image_view = VK_NULL_HANDLE;
			VkFormat depth_image_format = VK_FORMAT_UNDEFINED;
			VkDeviceMemory depth_image_memory = VK_NULL_HANDLE;
			
			VKContext vk_context;
			VKSurface surface;
			Device device;
			
			Pipeline pipeline;
			Buffer vertex_buffer;
			Buffer index_buffer;
			
			QTimer timer;
	};
}

#endif /* __TELLUSIM_QT_VK_WIDGET_H__ */
