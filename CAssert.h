#ifndef DENKR_ESSENTIALS_CASSERT_H
#define DENKR_ESSENTIALS_CASSERT_H








// ===========================================================================
// ===========================================================================
//  For checking the sizeof(something) at Compile Time
// ===========================================================================
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))
// ===========================================================================
// Example Usage:
//   BUILD_BUG_ON( sizeof(something) != PAGE_SIZE );
//  --------------------------------------------------------------------------
//   This will produce no code if
//             sizeof(someThing) != PAGE_SIZE
//   Otherwise you will get a Compile-Error.
// ===========================================================================
// ===========================================================================
// ===========================================================================
// ===========================================================================












// ===========================================================================
// ===========================================================================
// Could be extracted as "CAssert.h":
//
//		C Assert - CAssert - CASSERT
//			Compile Time Assertions for C
//
/** A compile time assertion check.
 *
 *  Validate at compile time that the predicate is true without
 *  generating code. This can be used at any point in a source file
 *  where typedef is legal.
 *
 *  On success, compilation proceeds normally.
 *
 *  On failure, attempts to typedef an array type of negative size. The
 *  offending line will look like
 *      typedef assertion_failed_file_h_42[-1]
 *  where file is the content of the second parameter which should
 *  typically be related in some obvious way to the containing file
 *  name, 42 is the line number in the file on which the assertion
 *  appears, and -1 is the result of a calculation based on the
 *  predicate failing.
 *
 *  \param predicate The predicate to test. It must evaluate to
 *  something that can be coerced to a normal C boolean.
 *
 *  \param file A sequence of legal identifier characters that should
 *  uniquely identify the source file in which this condition appears.
 */
#define CASSERT(predicate, file) _impl_CASSERT_LINE(predicate,__LINE__,file)

#define _impl_PASTE(a,b) a##b
#define _impl_CASSERT_LINE(predicate, line, file) \
	typedef char _impl_PASTE(assertion_failed_##file##_,line)[2*!!(predicate)-1];
// ===========================================================================
// ===========================================================================
//				Notices
// ===========================================================================
	//		Typical usage like this
// ===========================================================================
		//	#include "CAssert.h"
		//	...
		//	struct foo {
		//	    ...  /* 76 bytes of members */
		//	};
		//	CASSERT(sizeof(struct foo) == 76, demo_c);
// ===========================================================================
	//		In GCC a Assertion-Failure would look like
// ===========================================================================
		//	$ gcc -c demo.c
		//	demo.c:32: error: size of array `assertion_failed_demo_c_32' is negative
		//	$
// ===========================================================================
// ===========================================================================
//				CAssert.h End
// ===========================================================================
// ===========================================================================
// ===========================================================================
// ===========================================================================



#endif /* DENKR_ESSENTIALS_CASSERT_H */
