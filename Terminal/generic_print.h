/*
 * generic_print.h
 *
 *  Created on: 06.10.2017
 *      Author: Dennis Krummacker
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>



#ifndef GENERIC_PRINT_NAME
#error "Must declare GENERIC_PRINT_NAME"
#endif


#ifndef GENERIC_PRINT_TYPE
#error "Must declare GENERIC_PRINT_TYPE"
#endif



#define print_array print_Array





#define GENERIC_PRINT_CRUDECONCAT(x, y) x ## _ ## y
#define GENERIC_PRINT_CONCAT(x, y) GENERIC_PRINT_CRUDECONCAT(x,y)


#define PRINT_ARRAY_SIGNATURE_NAME          GENERIC_PRINT_CONCAT(GENERIC_PRINT_NAME, print_Array)
#define PRINT_ARRAY_SIGNATURE               void PRINT_ARRAY_SIGNATURE_NAME(GENERIC_PRINT_TYPE* arr, size_t size)
static __inline PRINT_ARRAY_SIGNATURE{
	int i;
	printf(" [\n");
	for(i=0;i<size;i++){
		printf("   %lli\n",(long long)(arr[i]));
	}
	printf(" ]\n");
}


#undef PRINT_ARRAY_SIGNATURE_NAME
#undef PRINT_ARRAY_SIGNATURE


#undef GENERIC_PRINT_CRUDECONCAT
#undef GENERIC_PRINT_CONCAT








#ifndef DENKR_ESSENTIALS__TERMINAL__GENERIC_PRINT_H
#define DENKR_ESSENTIALS__TERMINAL__GENERIC_PRINT_H






#endif /* DENKR_ESSENTIALS__TERMINAL__GENERIC_PRINT_H */
