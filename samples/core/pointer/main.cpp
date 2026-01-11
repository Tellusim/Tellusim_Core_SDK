// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimString.h>
#include <format/TellusimImage.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		
		Image image;
		
		// image is an empty object
		TS_LOGPTR(Message, "create: ", image);
		
		// non-const methods create internal object
		image.create2D(FormatRGBAu8n, 128u, 128u);
		
		// now image pointer is initialized and created
		TS_LOGPTR(Message, " image: ", image);
		
		// the image is not copied here
		Image ref = image;
		
		// ref is a reference to the image, both image objects are equal to each other
		TS_LOGPTR(Message, "   ref: ", ref);
		
		TS_LOGF(Message, " image: %s\n", image.getDescription().get());
		
		// this method cleares the pointer
		image.clearPtr();
		
		// ref is only owner now
		TS_LOGPTR(Message, " image: ", image);
		TS_LOGPTR(Message, "   ref: ", ref);
		
		// move constructor clears the pointer
		image = move(ref);
		
		// now image is only owner
		TS_LOGPTR(Message, " image: ", image);
		TS_LOGPTR(Message, "   ref: ", ref);
		
		// clonePtr() method makes deep copy of the pointer
		Image copy = image.clonePtr();
		TS_LOGPTR(Message, " image: ", image);
		TS_LOGPTR(Message, "  copy: ", copy);
		
		// make two image pointers
		ref = image;
		
		// destroyPtr() method destroys the pointer
		ref.destroyPtr();
		
		// now both pointers are null, except copied pointer
		TS_LOGPTR(Message, " image: ", image);
		TS_LOGPTR(Message, "   ref: ", ref);
		TS_LOGPTR(Message, "  copy: ", copy);
		
		// copied image will be destroyed at the and of the scope
	}
	
	return 0;
}
