// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_FENCE_H__
#define __TELLUSIM_PLATFORM_FENCE_H__

#include <core/TellusimArray.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class String;
	
	/**
	 * The Fence class provides functionality for managing synchronization fences within a graphics or computing pipeline.
	 * It includes methods for querying platform and device-specific information, as well as creating and managing the state of a fence.
	 * Fences can be used to synchronize operations across different parts of the pipeline, ensuring that specific tasks are completed before others are initiated.
	 */
	class TS_API Fence {
			
			TS_DECLARE_PTR_0(Fence, 0)
			
		public:
			
			/// Fence flags
			enum Flags {
				FlagNone = 0,
				FlagSemaphore	= (1 << 0),		// semaphore fence
				FlagSignaled	= (1 << 1),		// signaled state
				FlagShared		= (1 << 2),		// shared fence
				FlagExtern		= (1 << 3),		// extern fence
				DefaultFlags	= FlagNone,
				NumFlags = 4,
			};
			
			Fence();
			
			/// fence platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// fence device index
			uint32_t getIndex() const;
			
			/// clear fence
			void clear();
			
			/// check fence
			bool isCreated() const;
			
			/// create fence
			bool create(Flags flags = DefaultFlags);
			
			/// fence flags
			Flags getFlags() const;
			
			TS_INLINE bool hasFlag(Flags flags) const { return ((getFlags() & flags) != FlagNone); }
			TS_INLINE bool hasFlags(Flags flags) const { return ((getFlags() & flags) == flags); }
			
			String getFlagsName() const;
			
			/// fence description
			String getDescription() const;
	};
	
	/**
	 * The VKFence class is a Vulkan-specific implementation of the Fence class, providing access to Vulkan fence and semaphore objects for synchronization in Vulkan applications.
	 * It allows interaction with Vulkan native synchronization mechanisms, enabling the management of fence states and ensuring proper synchronization between operations.
	 * The class provides access to the VkFence and VkSemaphore objects, which are essential for signaling and waiting on events in Vulkan pipelines.
	 */
	class TS_API VKFence : public Fence {
			
			TS_DECLARE_PTR_1(VKFence, Fence, 0)
			
		public:
			
			VKFence();
			
			/// native fence
			VkFence getVKFence() const;
			VkSemaphore getSemaphore() const;
			
			void *getSharedHandle() const;
	};
	
	/**
	 * The FUFence class extends the Fence class to manage a fusion of multiple fences from different devices.
	 * It provides methods to set and retrieve a device mask, track the number of fusion fences, and access individual fences within the fusion.
	 * This functionality is particularly useful for high-performance computing scenarios where synchronization across multiple devices is required.
	 */
	class TS_API FUFence : public Fence {
			
			TS_DECLARE_PTR_1(FUFence, Fence, 0)
			
		public:
			
			FUFence();
			explicit FUFence(const Array<Fence> &fences, bool owner = false);
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion fences
			uint32_t getNumFences() const;
			const Fence getFence(uint32_t index) const;
			Fence getFence(uint32_t index);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Fence::Flags)
}

#endif /* __TELLUSIM_PLATFORM_FENCE_H__ */
