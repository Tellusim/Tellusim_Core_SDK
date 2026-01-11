// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <cstdlib>
#include <algorithm>

#include <core/TellusimLog.h>
#include <core/TellusimSort.h>
#include <core/TellusimTime.h>
#include <math/TellusimRandom.h>

/*
 */
using namespace Tellusim;

/*
 */
TS_INLINE int32_t qsort_compare(const void *p0, const void *p1) {
	return *(int32_t*)p0 - *(int32_t*)p1;
}

/*
 */
template <class Type> bool check(const char *str, Type *data, const Type *ref, uint32_t size) {
	if(ref != nullptr) {
		for(uint32_t i = 0; i < size; i++) {
			if(data[i] != ref[i]) {
				TS_LOGF(Error, "%serror at %u of %u\n", str, i, size);
				return false;
			}
		}
	} else {
		for(uint32_t i = 1; i < size; i++) {
			if(data[i - 1] > data[i]) {
				TS_LOGF(Error, "%serror at %u of %u\n", str, i, size);
				return false;
			}
		}
	}
	return true;
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	{
		constexpr uint32_t threshold = 8192;
		constexpr uint32_t size = 1024 * 1024 * 8;
		
		Random<> random;
		Array<int32_t> src(size);
		for(uint32_t i = 0; i < size; i++) {
			src[i] = random.geti32();
		}
		
		for(uint32_t s = 2; s < size; s = s * 3 / 2) {
			
			TS_LOG(Message, "\n");
			
			Array<int32_t> ref(s, src.get());
			Array<int32_t> sort(s, src.get());
			
			uint64_t begin = Time::current();
			qsort(ref.get(), s, sizeof(int32_t), qsort_compare);
			if(s > threshold) TS_LOGF(Message, "qsort:     %u %s\n", s, String::fromTime(Time::current() - begin).get());
			if(!check("qsort: ", ref.get(), (const int32_t*)nullptr, s)) break;
			
			sort.copy(src.get(), s);
			begin = Time::current();
			std::sort(sort.get(), sort.get() + s);
			if(s > threshold) TS_LOGF(Message, "std::sort: %u %s\n", s, String::fromTime(Time::current() - begin).get());
			if(!check("std::sort: ", sort.get(), ref.get(), s)) break;
			
			sort.copy(src.get(), s);
			begin = Time::current();
			quickSort(sort.get(), s);
			if(s > threshold) TS_LOGF(Message, "quickSort: %u %s\n", s, String::fromTime(Time::current() - begin).get());
			if(!check("quickSort: ", sort.get(), ref.get(), s)) break;
			
			sort.copy(src.get(), s);
			begin = Time::current();
			radixSort(sort.get(), s);
			if(s > threshold) TS_LOGF(Message, "radixSort: %u %s\n", s, String::fromTime(Time::current() - begin).get());
			if(!check("radixSort: ", sort.get(), ref.get(), s)) break;
		}
	}
	
	return 0;
}
