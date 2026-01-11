// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_QUERY_H__
#define __TELLUSIM_PLATFORM_QUERY_H__

#include <core/TellusimArray.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Buffer;
	
	/**
	 * The Query class provides functionality for querying various types of data, such as time, clock, sample counts, and statistics, in a platform-specific manner.
	 * It allows for creating and managing different types of queries, checking the state of the query, and retrieving the results of the query.
	 */
	class TS_API Query {
			
			TS_DECLARE_PTR_0(Query, 0)
			
		public:
			
			/// Query types
			enum Type {
				TypeUnknown = 0,
				TypeTime,
				TypeClock,
				TypeSamples,
				TypeSamples1,
				TypeStatistics,
				NumTypes,
			};
			
			Query();
			
			/// query platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// query device index
			uint32_t getIndex() const;
			
			/// clear query
			void clear();
			
			/// check query
			bool isCreated() const;
			bool isAvailable() const;
			bool isBegan() const;
			bool isEnded() const;
			
			/// create query
			bool create(Type type);
			
			/// query type
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			size_t getTypeSize() const;
			
			TS_INLINE bool isTime() const { return (getType() == TypeTime); }
			TS_INLINE bool isClock() const { return (getType() == TypeClock); }
			TS_INLINE bool isSamples() const { return (getType() == TypeSamples); }
			TS_INLINE bool isSamples1() const { return (getType() == TypeSamples1); }
			TS_INLINE bool isStatistics() const { return (getType() == TypeStatistics); }
			
			TS_INLINE bool isTimeType() const { return (getType() == TypeTime || getType() == TypeClock); }
			TS_INLINE bool isSamplesType() const { return (getType() == TypeSamples1 || getType() == TypeSamples); }
			
			/// get query data
			bool get(void *dest, size_t size, bool wait = true) const;
			
			uint64_t getTime(bool wait = true, bool *status = nullptr) const;
			uint32_t getSamples(bool wait = true, bool *status = nullptr) const;
			
			/// statistics query
			struct Statistics {
				uint64_t num_vertices;
				uint64_t num_primitives;
				uint64_t vertex_invocations;
				uint64_t control_invocations;
				uint64_t evaluate_invocations;
				uint64_t geometry_invocations;
				uint64_t geometry_primitives;
				uint64_t fragment_invocations;
				uint64_t compute_invocations;
				uint64_t clipping_invocations;
				uint64_t clipping_primitives;
			};
			
			Statistics getStatistics(bool wait = true, bool *status = nullptr) const;
	};
	
	/**
	 * The FUQuery class extends the Query class to manage a fusion of multiple queries from different devices.
	 * It provides methods to set and retrieve a device mask, track the number of fusion queries, and access individual queries within the fusion.
	 * This functionality is particularly useful for high-performance computing scenarios, where managing and interacting with queries across multiple devices in parallel workflows is required.
	 */
	class TS_API FUQuery : public Query {
			
			TS_DECLARE_PTR_1(FUQuery, Query, 0)
			
		public:
			
			FUQuery();
			explicit FUQuery(const Array<Query> &queries, bool owner = false);
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion queries
			uint32_t getNumQueries() const;
			const Query getQuery(uint32_t index) const;
			Query getQuery(uint32_t index);
	};
}

#endif /* __TELLUSIM_PLATFORM_QUERY_H__ */
