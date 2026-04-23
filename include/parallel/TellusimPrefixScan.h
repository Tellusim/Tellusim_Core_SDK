// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PARALLEL_PREFIX_SCAN_H__
#define __TELLUSIM_PARALLEL_PREFIX_SCAN_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Async;
	class Buffer;
	class Compute;
	class Device;
	
	/**
	 * The PrefixScan class provides an efficient implementation of the prefix scan (sum) algorithm, supporting both single and multiple array scanning.
	 * It is highly configurable and optimized for parallel computing, commonly used in tasks such as data aggregation and parallel processing.
	 * The class supports various modes and flags, allowing for flexible control over the scanning process, including the ability to perform indirect scans using dispatch buffers.
	 * Its methods enable in-place scanning for both single and multiple datasets, with support for large-scale data processing across multiple regions.
	 */
	class TS_API PrefixScan {
			
			TS_DECLARE_PTR(PrefixScan, 0)
			
		public:
			
			/// Scan modes
			enum Mode {
				ModeSingle = 0,		// single array scan
				ModeMultiple,		// multiple arrays scan
				NumModes,
			};
			
			/// Scan flags
			enum Flags {
				FlagNone = 0,
				FlagSingle		= (1 << ModeSingle),		// enable Single array prefix mode
				FlagMultiple	= (1 << ModeMultiple),		// enable Multi array prefix mode
				FlagIndirect	= (1 << (NumModes + 0)),	// enable Dispatch Indirect mode
				FlagStride		= (1 << (NumModes + 1)),	// enable elements stride mode
				FlagRepeat		= (1 << (NumModes + 2)),	// repeat Dispatch Indirect prefix scan with the same parameters
				FlagsAll		= (FlagSingle | FlagMultiple | FlagIndirect | FlagStride),
			};
			
			PrefixScan();
			
			/// clear scan
			void clear();
			
			/// check scan
			bool isCreated(Flags flags) const;
			
			/// scan parameters
			uint32_t getGroupSize() const;
			uint32_t getScanElements() const;
			uint32_t getMaxElements() const;
			uint32_t getMaxRegions() const;
			
			/// create prefix scan
			/// \param groups Prefix scan group size.
			/// \param regions Maximum number of multiple regions.
			bool create(const Device &device, Mode mode, uint32_t groups = 256, uint32_t regions = 1, Async *async = nullptr);
			bool create(const Device &device, Flags flags, uint32_t groups = 256, uint32_t regions = 1, Async *async = nullptr);
			
			/// dispatch single in-place prefix scan
			/// \param data Buffer of uint32_t elements to scan.
			/// \param offset Elements offset index (4 aligned).
			/// \param size Number of uint32_t elements to scan.
			/// \param stride Element stride in uint32_t elements.
			bool dispatch(Compute &compute, Buffer &data, uint32_t offset, uint32_t size, uint32_t stride = 1);
			
			/// dispatch multiple in-place prefix scans
			/// \param data Buffer of uint32_t elements to scan.
			/// \param count Number of regions to scan.
			/// \param offsets Elements offset index (4 aligned).
			/// \param sizes Number of uint32_t elements to scan.
			/// \param stride Element stride in uint32_t elements.
			bool dispatch(Compute &compute, Buffer &data, uint32_t count, const uint32_t *offsets, const uint32_t *sizes, Flags flags = FlagNone, uint32_t stride = 1);
			
			/// dispatch single in-place indirect prefix scan
			/// \param data Buffer of uint32_t elements to scan.
			/// \param dispatch Dispatch indirect buffer.
			/// \param offset Dispatch indirect buffer offset.
			/// \param max_size Maximum number of elements to scan.
			/// \param stride Element stride in uint32_t elements.
			bool dispatchIndirect(Compute &compute, Buffer &data, Buffer &dispatch, uint32_t offset, Flags flags = FlagNone, uint32_t max_size = Maxu32, uint32_t stride = 1);
			
			/// dispatch multiple in-place indirect prefix scans
			/// \param data Buffer of uint32_t elements to scan.
			/// \param count Number of regions to scan.
			/// \param dispatch Dispatch indirect buffer.
			/// \param offset Dispatch indirect buffer offset.
			/// \param max_size Maximum number of elements to scan.
			/// \param stride Element stride in uint32_t elements.
			bool dispatchIndirect(Compute &compute, Buffer &data, uint32_t count, Buffer &dispatch, uint32_t offset, Flags flags = FlagNone, uint32_t max_size = Maxu32, uint32_t stride = 1);
			
			/// dispatch multiple in-place indirect prefix scans
			/// \param data Buffer of uint32_t elements to scan.
			/// \param count Count indirect buffer.
			/// \param dispatch Dispatch indirect buffer.
			/// \param count_offset Count indirect buffer offset.
			/// \param dispatch_offset Dispatch indirect buffer offset.
			/// \param max_size Maximum number of elements to scan.
			/// \param stride Element stride in uint32_t elements.
			bool dispatchIndirect(Compute &compute, Buffer &data, Buffer &count, Buffer &dispatch, uint32_t count_offset, uint32_t dispatch_offset, Flags flags = FlagNone, uint32_t max_size = Maxu32, uint32_t stride = 1);
			
			struct DispatchParameters {
				uint32_t offset;			// elements offset index (4 aligned)
				uint32_t size;				// number of elements to scan
				uint32_t padding_0;
				uint32_t padding_1;
			};
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(PrefixScan::Flags)
}

#endif /* __TELLUSIM_PARALLEL_PREFIX_SCAN_H__ */
