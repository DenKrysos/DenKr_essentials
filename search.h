/*
 * sort.h
 *
 *  Created on: 06.10.2017
 *      Author: Dennis Krummacker
 */

//#ifndef DENKR_ESSENTIALS__ALGORITHM__SEARCH__H
//#define DENKR_ESSENTIALS__ALGORITHM__SEARCH__H




//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//--------  Preamble, Inclusions  ------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//==================================================================================================//
// At first include this ----------------------------------------------------------
//---------------------------------------------------------------------------------
//#include "./global/global_settings.h"
//#include "./global/global_variables.h"
// Need this for e.g. some really fundamental Program Basics (if any)  ------------
//---------------------------------------------------------------------------------
//#include "DenKrement_base.h"
// Then better start with this  ---------------------------------------------------
//---------------------------------------------------------------------------------
//#include "DenKrement.h"
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Just to nicely keep order:  -----------------------------------------------------
//   First include the System / Third-Party Headers  ------------------------------
//   Format: Use <NAME> for them  -------------------------------------------------
//---------------------------------------------------------------------------------
//#include <stdio.h>
//#include <stdlib.h>
//#include <limits.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
//#include "DenKr_essentials/auxiliary.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//







//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Some Informations  -------------------------------------------------------------------------//
//----      Just nice to know.  --------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////



















//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  The actual "search.h"  ---------------------------------------------------------------------//
//----      Utilizable without any .c-File  --------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
/////////////////////////////////////
////////// Usage:
/////////////////////////////////////
// Inclusion and therewith actual Creation of Function works analogous to "sort.h" For Instructions look there.
//
// Additionally: #define DENKR_SEARCH_STATIC static to create the functions static (e.g., when including in a .c-File and want the functions only there)
//				#define it empty or not at all, to let the functions be non-static. (e.g., when including inside a Function or when you want to create a .c-File for Search-Functions, that you want to use at several places inside your code (and in various Files))
//
// For Example, if you would like to keep it simple: Create one File, called search_int.c. There include this File
//   using Method to create int Functions, write a appropriate Header-File for it and use this.
//
//
///////////////////////////////////////
//
//----------------------------------------------------------------------------------------------------
/////////////////////////////////////
////////// Overview:
/////////////////////////////////////
//
//
///////////////////////////////////////////
//
//----------------------------------------------------------------------------------------------------
/////////////////////////////////////
////////// Speed of Routines:
/////////////////////////////////////
// Some Notes about this can be found at the Functions itself.
//
//
///////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef DENKR_SEARCH_STATIC
#define DENKR_SEARCH_STATIC
#endif

#ifndef DENKR_SEARCH_NAME
#error "Must declare SORT_NAME"
#endif

#ifndef DENKR_SEARCH_TYPE
#error "Must declare SORT_TYPE"
#endif




#define DENKR_SEARCH_CRUDECONCAT(x, y) x ## _ ## y
#define DENKR_SEARCH_CONCAT(x, y) DENKR_SEARCH_CRUDECONCAT(x,y)



//Only for Sorted Arrays!
// Return 0, if Value wasn't found, i.e. isn't present in Array.
// Return 1, if Value was found.
// 'Actual Result' is returned in int* res:
// If Value was found: Index of the searched Value:
// If Value wasn't found: Index of the smallest element greater than the Searched Value.
//      - if Value is smaller than the smallest element in the array: '0'
//      - if Value is greater than the highest element in the array: 'array-size' (i.e. 'highest-index + 1')
#if ( !defined(DENKR_SEARCH_SELECTIVE) || ( defined(DENKR_SEARCH_SELECTIVE) && defined(DENKR_SEARCH_BINARY) ) )
#define BINARY_SEARCH_SIGNATURE_NAME          DENKR_SEARCH_CONCAT(DENKR_SEARCH_NAME, BinarySearch)
#define BINARY_SEARCH_SIGNATURE               char BINARY_SEARCH_SIGNATURE_NAME(const DENKR_SEARCH_TYPE* list, size_t size, DENKR_SEARCH_TYPE key, unsigned int* res)
DENKR_SEARCH_STATIC __inline BINARY_SEARCH_SIGNATURE
{
	#define SEARCH_VALUE_FOUND       1
	#define SEARCH_VALUE_NOT_FOUND   0
	int low, high, mid;
	low=0;
	high=size-1;
	int geq=size;

	while(high>=low){
		mid=(low+high)>>1; //(low+high)/2;
		if(key<list[mid]){
			high=mid-1;
			geq=mid;
		}else if(key>list[mid]){
			low=mid+1;
		}else{
			*res=mid;
			return SEARCH_VALUE_FOUND;
		}
	}
	*res = geq;
	return SEARCH_VALUE_NOT_FOUND;
	#undef SEARCH_VALUE_FOUND
	#undef SEARCH_VALUE_NOT_FOUND
}
#endif


//int BinarySearch_variant1 (int key)
//{
//    int start = 0;
//    int end = max - 1;
//    int mid;
//    while (start <= end)
//    {
//        mid = (start + end) / 2;
//        if (key == a[mid])
//            return mid;
//        else if (key < a[mid])
//            end = mid - 1;
//        else start = mid + 1;
//    }
//    return -1;
//}


//Same Output as BinarySearch
//Only for Sorted Arrays!
//Improvement of BinarySearch, that adapts "Human Thinking", for
//   obtaining a better Starting-Point. (If you search for a Person in the Telephone-Book, whose Name starts with 'B', you won't start in the Middle...)
//A lot faster, but only with large Data-Sets.
//   With small Data-Sets, BinarySearch wins.
#if ( !defined(DENKR_SEARCH_SELECTIVE) || ( defined(DENKR_SEARCH_SELECTIVE) && defined(DENKR_SEARCH_INTERPOLATION) ) )
#define INTERPOLATION_SEARCH_SIGNATURE_NAME          DENKR_SEARCH_CONCAT(DENKR_SEARCH_NAME, InterpolationSearch)
#define INTERPOLATION_SEARCH_SIGNATURE               char INTERPOLATION_SEARCH_SIGNATURE_NAME(const DENKR_SEARCH_TYPE* list, size_t size, DENKR_SEARCH_TYPE key, unsigned int* res)
DENKR_SEARCH_STATIC __inline INTERPOLATION_SEARCH_SIGNATURE
{
	#define SEARCH_VALUE_FOUND       1
	#define SEARCH_VALUE_NOT_FOUND   0
	// Interpolation search
	int low = 0, high = size - 1;

	while(list[high] >= key && key>list[low]){
		double low_diff = (double)key-list[low];
		double range_diff=(double)list[high]-list[low];
		double count_diff=(double)high-low;
		int range = (int)(low_diff/range_diff*count_diff+low);
		if(key>list[range]){
			low = range+1;
		}else if(key<list[range]){
			high=range-1;
		}else{
			low=range;
		}
	}
	*res=low;
	if(key==list[low]){
		return SEARCH_VALUE_FOUND;
	}else
		return SEARCH_VALUE_NOT_FOUND;

	#undef SEARCH_VALUE_FOUND
	#undef SEARCH_VALUE_NOT_FOUND
}
#endif







/*
  Fibonaccian search for locating the index of "val" in an array "arr" of size "n"
  that is sorted in ascending order. See http://doi.acm.org/10.1145/367487.367496

  Algorithm description
  -----------------------------------------------------------------------------
  Let Fk represent the k-th Fibonacci number where Fk+2=Fk+1 + Fk for k>=0 and
  F0 = 0, F1 = 1. To test whether an item is in a list of n = Fm ordered numbers,
  proceed as follows:
  a) Set k = m.
  b) If k = 0, finish - no match.
  c) Test item against entry in position Fk-1.
  d) If match, finish.
  e) If item is less than entry Fk-1, discard entries from positions Fk-1 + 1 to n.
     Set k = k - 1 and go to b).
  f) If item is greater than entry Fk-1, discard entries from positions 1 to Fk-1.
     Renumber remaining entries from 1 to Fk-2, set k = k - 2 and go to b)

  If Fm>n then the original array is augmented with Fm-n numbers larger
  than val and the above algorithm is applied.
 */

#if ( !defined(DENKR_SEARCH_SELECTIVE) || ( defined(DENKR_SEARCH_SELECTIVE) && defined(DENKR_SEARCH_FIBONACCIAN) ) || ( defined(DENKR_SEARCH_SELECTIVE) && defined(DENKR_SEARCH_FIBONACCI) ) )
#define FIBONACCIAN_SEARCH_SIGNATURE_NAME          DENKR_SEARCH_CONCAT(DENKR_SEARCH_NAME, FibonaccianSearch)
#define FIBONACCIAN_SEARCH_SIGNATURE               char FIBONACCIAN_SEARCH_SIGNATURE_NAME(const DENKR_SEARCH_TYPE* arr, int n, DENKR_SEARCH_TYPE val)
DENKR_SEARCH_STATIC __inline FIBONACCIAN_SEARCH_SIGNATURE
{
	//------------------------------------------------------------------------
	/*
	 * If val is found in arr, return the index of its location in arr.
	 * Otherwise, return the index of the smallest element greater than val
	 */
	__inline int binsrch_geq(const int *arr, int n, int val){
		register int low, high, mid;
		int geq;
		low=0; high=n-1; geq=-1;
		/* binary search for finding the element with value val */
		while(low<=high){
			mid=(low+high)>>1; //(low+high)/2;
			if(val<arr[mid]){
				high=mid-1;
				geq=mid;
			}else if(val>arr[mid]){
				low=mid+1;
			}else{
				return mid; /* found */
			}
		}
		return geq; /* not found */
	}
	//------------------------------------------------------------------------

	register int k, idx, offs;
	static int prevn=-1, prevk=-1;

	/*  Precomputed Fibonacci numbers F0 up to F46. This implementation assumes that the size n
	 *  of the input array fits in 4 bytes. Note that F46=1836311903 is the largest Fibonacci
	 *  number that is less or equal to the 4-byte INT_MAX (=2147483647). The next Fibonacci
	 *  number, i.e. F47, is 2971215073 and is larger than INT_MAX, implying that it does not
	 *  fit in a 4 byte integer. Note also that the last array element is INT_MAX rather than
	 *  F47. This ensures correct operation for n>F46.
	 */
	const static int Fib[47+1]={0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765,
				 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578,
				 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296,
				 433494437, 701408733, 1134903170, 1836311903, INT_MAX};

	/* find the smallest fibonacci number that is greater or equal to n. Store this
	* number to avoid recomputing it in the case of repetitive searches with identical n.
	*/
	if(n!=prevn){
		#if 1
			k=(n>1)? binsrch_geq(Fib, sizeof(Fib)/sizeof(int), n) : 1;
		#else /* the above binary search call can be substituted by the following code fragment: */
			{
				register int f0, f1, t;
				for(f0=0, f1=1, k=1; f1<n; t=f1, f1+=f0, f0=t, ++k){}
			}
		#endif
		prevk=k;
		prevn=n;
	}
	else k=prevk;

	/* If the sought value is larger than the largest Fibonacci number less than n,
	* care must be taken top ensure that we do not attempt to read beyond the end
	* of the array. If we do need to do this, we pretend that the array is padded
	* with elements larger than the sought value.
	*/
	for(offs=0; k>0;  ){
		idx=offs+Fib[--k];

		/* note that at this point k  has already been decremented once */
		if(idx>=n || val<arr[idx]){ // index out of bounds or val in 1st part
			continue;
		}else if (val>arr[idx]){ // val in 2nd part
			offs=idx;
			--k;
		}else{ // val==arr[idx], found
			return idx;
		}
	}

	return -1; // not found
}
#endif



#undef BINARY_SEARCH_SIGNATURE_NAME
#undef BINARY_SEARCH_SIGNATURE
#undef INTERPOLATION_SEARCH_SIGNATURE_NAME
#undef INTERPOLATION_SEARCH_SIGNATURE
#undef FIBONACCIAN_SEARCH_SIGNATURE_NAME
#undef FIBONACCIAN_SEARCH_SIGNATURE

#undef DENKR_SEARCH_CRUDECONCAT
#undef DENKR_SEARCH_CONCAT

#undef DENKR_SEARCH_STATIC




//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


























//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Functions to be visible outside  -----------------------------------------------------------//
//----      (external)  ----------------------------------------------------------------------------//
//----      (from "sort.c")  -----------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
#ifndef NO__DENKR_ESSENTIALS__ALGORITHM__SEARCH__C__FUNCTIONS

#endif
//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////







//#endif /* DENKR_ESSENTIALS__ALGORITHM__SEARCH__H */
