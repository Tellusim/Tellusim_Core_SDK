// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUQuery extends Query {
	
	public FUQuery() { init_(new_()); }
	public FUQuery(Query[] queries) { init_(new_1(Query.self_(queries), false)); }
	public FUQuery(Query[] queries, boolean owner) { init_(new_1(Query.self_(queries), owner)); }
	public FUQuery[] ref() { return new FUQuery[] { this }; }
	public FUQuery(Query base) { init_(cast_query_ptr(base.self)); }
	public Query toQuery() { return new Query(base_query_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumQueries() { return get_num_queries(self); }
	public Query getQuery(int index) { return new Query(get_query(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] queries, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_query_ptr(long self, long base);
	private static native long cast_query_ptr(long self);
	private static native long base_query_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_queries(long self);
	private static native long get_query(long self, int index);
	private static native long get_query_1(long self, int index);
	
	protected FUQuery(long self) {
		init_(self);
	}
	public static FUQuery Null() {
		return new FUQuery((long)0);
	}
}
