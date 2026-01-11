// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PARALLEL_BITONIC_SORT_H__
#define __TELLUSIM_PARALLEL_BITONIC_SORT_H__

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
	 * The BitonicSort class implements an efficient parallel bitonic sorting algorithm designed for sorting large datasets on GPUs.
	 * It supports both single and multiple array sorting, and provides flexible configurations through various modes and flags.
	 * The class can handle sorting tasks that involve both direct and indirect dispatching, making it suitable for complex scenarios such as sorting multiple regions or handling different element alignments.
	 */
	class TS_API BitonicSort {
			
			TS_DECLARE_PTR(BitonicSort, 0)
			
		public:
			
			/// Sort modes
			enum Mode {
				ModeSingle = 0,		// single array sort
				ModeMultiple,		// multiple arrays sort
				NumModes,
			};
			
			/// Sort flags
			enum Flags {
				FlagNone = 0,
				FlagSingle			= (1 << ModeSingle),
				FlagMultiple		= (1 << ModeMultiple),
				FlagIndirect		= (1 << (NumModes + 0)),
				FlagOrder			= (1 << (NumModes + 1)),
				FlagsAll			= (FlagSingle | FlagMultiple | FlagIndirect | FlagOrder),
			};
			
			BitonicSort();
			
			/// clear sort
			void clear();
			
			/// check sort
			bool isCreated(Flags flags) const;
			
			/// sort parameters
			uint32_t getDataSize() const;
			uint32_t getGroupSize() const;
			uint32_t getSortElements() const;
			uint32_t getMaxRegions() const;
			
			/// create bitonic sort
			/// \param size Maximum number of sorted elements.
			/// \param groups Bitonic sort group size.
			/// \param regions Maximum number of multiple regions.
			bool create(const Device &device, Mode mode, uint32_t size, uint32_t groups = 256, uint32_t regions = 1, Async *async = nullptr);
			bool create(const Device &device, Flags flags, uint32_t size, uint32_t groups = 256, uint32_t regions = 1, Async *async = nullptr);
			
			/// dispatch single in-place bitonic sort
			/// \param data Buffer of uint32_t data elements to sort.
			/// \param keys_offset Keys elements offset index (2 aligned).
			/// \param data_offset Data elements offset index (2 aligned).
			/// \param size Number of uint32_t elements to sort.
			bool dispatch(Compute &compute, Buffer &data, uint32_t keys_offset, uint32_t data_offset, uint32_t size, Flags flags = FlagNone);
			
			/// dispatch multiple in-place bitonic sorts
			/// \param data Buffer of uint32_t data elements to sort.
			/// \param count Number of regions to sort.
			/// \param keys_offsets Keys elements offset index (2 aligned).
			/// \param data_offsets Data elements offset index (2 aligned).
			/// \param sizes Number of uint32_t elements to sort.
			bool dispatch(Compute &compute, Buffer &data, uint32_t count, const uint32_t *keys_offsets, const uint32_t *data_offsets, const uint32_t *sizes, Flags flags = FlagNone);
			
			/// dispatch single in-place indirect local bitonic sort
			/// \param data Buffer of uint32_t data elements to sort.
			/// \param dispatch Dispatch indirect buffer.
			/// \param offset Dispatch indirect buffer offset.
			bool dispatchIndirect(Compute &compute, Buffer &data, Buffer &dispatch, uint32_t offset, Flags flags = FlagNone);
			
			/// dispatch multiple in-place indirect local bitonic sorts
			/// \param data Buffer of uint32_t data elements to sort.
			/// \param count Number of regions to sort.
			/// \param dispatch Dispatch indirect buffer.
			/// \param offset Dispatch indirect buffer offset.
			bool dispatchIndirect(Compute &compute, Buffer &data, uint32_t count, Buffer &dispatch, uint32_t offset, Flags flags = FlagNone);
			
			/// dispatch multiple in-place indirect local bitonic sorts
			/// \param data Buffer of uint32_t data elements to sort.
			/// \param count Count indirect buffer.
			/// \param dispatch Dispatch indirect buffer.
			/// \param count_offset Count indirect buffer offset.
			/// \param dispatch_offset Dispatch indirect buffer offset.
			bool dispatchIndirect(Compute &compute, Buffer &data, Buffer &count, Buffer &dispatch, uint32_t count_offset, uint32_t dispatch_offset, Flags flags = FlagNone);
			
			struct DispatchParameters {
				uint32_t keys_offset;		// keys elements offset index (2 aligned)
				uint32_t data_offset;		// data elements offset index (2 aligned)
				uint32_t size;				// number of elements to sort
				uint32_t padding;
			};
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(BitonicSort::Flags)
}

#endif /* __TELLUSIM_PARALLEL_BITONIC_SORT_H__ */
