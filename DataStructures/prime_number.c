/*
 * prime_number.c
 *
 * Authored by
 * Dennis Krummacker (19.07.2018 - )
 */

#define DENKR_ESSENTIALS__PRIME_NUMBER__C
#define NO__DENKR_ESSENTIALS__PRIME_NUMBER__C__FUNCTIONS


#include <math.h>

#include "prime_number.h"


/*
 * Return whether x is prime or not
 *
 * Returns:
 *   1  - prime
 *   0  - not prime
 *   -1 - undefined (i.e. x < 2)
 */
int DenKr_is_prime(const int x){
	int i;
	if(x < 2)
		return -1;
	if(x < 4)
		return 1;
	if((x % 2) == 0)
		return 0;
	for(i=3;i<=floor(sqrt((double) x));i+=2){
		if((x % i) == 0){
			return 0;
		}
	}
	return 1;
}


/*
 * Return the next prime after x, or x if x is prime
 */
int DenKr_next_prime(int x){
	while(DenKr_is_prime(x) != 1){
		x++;
	}
	return x;
}




#undef DENKR_ESSENTIALS__PRIME_NUMBER__C
#undef NO__DENKR_ESSENTIALS__PRIME_NUMBER__C__FUNCTIONS
