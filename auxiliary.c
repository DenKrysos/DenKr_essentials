/*
 * Authored by
 * Dennis Krummacker (03.06.14-)
 */

#define DENKR_ESSENTIALS_AUXILIARY_C
#define NO_DENKR_ESSENTIALS_AUIXILIARY_C_FUNCTIONS


//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//--------  Preamble, Inclusions  ------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//==================================================================================================//
// At first include this ----------------------------------------------------------
//---------------------------------------------------------------------------------
#include <global/global_settings.h>
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
#include <sys/socket.h>
#include </usr/include/linux/wireless.h>
#include </usr/include/linux/if_arp.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <pwd.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#include "PreC/DenKr_PreC.h"
#include "auxiliary.h"
#include "function_creator.h"
#include "DenKr_errno.h"
#include "getRealTime.h"
#include "Program_Files/P_Files_Path.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//



/*
 * Just a bunch of helpful functions/makros
 * Especially some used for debugging/developing
 * Or something nice like the ansi_escape_use setting
 */










//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================
//----------------------------------------------------------------------------------------------------
//----  Few Global Variables  ------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//====================================================================================================
#if (PROGRAM_ARGUMENTS_GLOBAL_AVAILABILITY == PROGRAM_ARGUMENTS_GLOBAL_AVAILABILITY___AVAILABLE)
	int argcg;
	char **argvg;
#endif
char ansi_escape_use;
char system_endianess=ENDIANESS_UNKNOWN;
//NOTE: These lengths are really "length" and NOT "sizeof" ;o)
#if (PROGRAM_NAME_VAR_AVAILABILITY == PROGRAM_NAME_VAR_AVAILABILITY___GLOBAL)
	int ProgramName_length;
	char *ProgramName;
#endif
#if (STORAGE_FILES_PATH_VAR_AVAILABILITY == STORAGE_FILES_PATH_VAR_AVAILABILITY___GLOBAL)
	int StorageFilesPath_length;
	char *StorageFilesPath;
#endif
#if (PROGRAM_PATH_VAR_AVAILABILITY == PROGRAM_PATH_VAR_AVAILABILITY___GLOBAL)
	int ProgPath_length;
	char *ProgPath;
#endif

//----------------------------------------------------------------------------------------------------
//====================================================================================================
////////////////////////////////
//////// Used within the depr(...) Macro
////////////////////////////////
#ifdef DEBUG
	int DebugPrintCount=0;
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////












//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================
//----------------------------------------------------------------------------------------------------
//----  To Initialize the DenKr_essentials Capabilities. Just call at Program Start  -----------------
//----------------------------------------------------------------------------------------------------
//====================================================================================================
/* Enables:
 * - System Endianess
 *   -> Available in global Variable "system_endianess"
 *   -> Use of Conversion Functions
 * - ANSI
 *   -> Use of Function for colorized Terminal Output
 *      --> printfc(...);
 * - argc, argv
 *   -> permanent storage
 *   -> global availability
 *      --> int argcg
 *      --> char **argvg
 * Usage:
 *   Call it before !any! modification on argc, argv
 */
int DenKr_essentials_Init(int argc, char **argv){
	#if (PROGRAM_ARGUMENTS_GLOBAL_AVAILABILITY == PROGRAM_ARGUMENTS_GLOBAL_AVAILABILITY___AVAILABLE)
		argcg=argc;
		argvg=argv;
	#endif
	// Get the System-Endianess
	check_system_endianess(&system_endianess);

	//Just to set up, if Ollerus should use ANSI Escape on the Output Console. For Things like Colored Output...
	//defined as a macro in remainder.h
	SET_ansi_escape_use;


	//For now, the two STORAGE_FILES_PATH related actually do the very same and the differing Magic is done inside the macro.
	//   But nevertheless it's called to create the StorageFiles Folder Path, if it isn't already existent.
	//What happens differently, if chosen between GLOBAL or SINGLE?
	//GLOBAL: The global Variable is created and the Path to store/load Files from is globally available from then on.
	//        Additionally the Folder Tree is created, if not already present
	//SINGLE: The Path-Variable is locally created. This is used to create the Folder-Path, if not already present.
	//        After Function Termination the local Variable is freed, like common.
	//Thus it is still important to run something even when chosen SINGLE, to create the Folder-Path
	//   The complete Path has to be present or future uses inside the Program would fail (like Log-File creations or such).
	#if (PROGRAM_NAME_VAR_AVAILABILITY == PROGRAM_NAME_VAR_AVAILABILITY___GLOBAL)
		CREATE_PROGRAM_NAME(*argv);
	#endif
	#if (STORAGE_FILES_PATH_VAR_AVAILABILITY == STORAGE_FILES_PATH_VAR_AVAILABILITY___GLOBAL)
		CREATE_STORAGE_FILES_PATH(*argv);
		CREATE_COMPLETE_FOLDER_PATH(StorageFilesPath);
	#endif
	#if (STORAGE_FILES_PATH_VAR_AVAILABILITY == STORAGE_FILES_PATH_VAR_AVAILABILITY___SINGLE)
		CREATE_PROGRAM_NAME(*argv);
		CREATE_STORAGE_FILES_PATH(*argv);
		CREATE_COMPLETE_FOLDER_PATH(StorageFilesPath);
	#endif
	#if (PROGRAM_PATH_VAR_AVAILABILITY == PROGRAM_PATH_VAR_AVAILABILITY___GLOBAL)
		CREATE_PROGRAM_PATH(*argv);
	#endif
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////












int senddetermined (int socket, char *msg, int msglen){
	int bytes_sent;
//	msglen = strlen(msg);
	SendAgain:
	bytes_sent = send(socket, msg, msglen, 0);
	switch(bytes_sent) {
	case -1:
		//Something gone wrong. Read out errno for further detail
		return errno;
		break;
	default:
		if(bytes_sent==msglen) {
			//Everything sent, everything done. Just fine and we are finished.
		} else if(bytes_sent<msglen) {
			//Not everything sent, but the beginning. Go on and send the rest.
			msg=msg+bytes_sent;
			msglen=msglen-bytes_sent;
			goto SendAgain;
		} else {
			//How could this happen o.O ?
			//SHUTDOWN!!!
			//SHUTDOWN!!!
			//Just kidding. Should never occur...
			return OPERATION_ERR_NEVER_HAPPEN;
		}
		break;
	}
	return 0;
}

int recvdetermined(int* bytes_received, int socket, void *buffer, size_t size, int flags){
//	int err;
	(*bytes_received)=recv(socket,buffer,size,flags);
	if(0<(*bytes_received)){//proper operation
		while((*bytes_received)<size){
			int b_recvd_temp;
			b_recvd_temp=recv(socket,buffer+(*bytes_received),size-(*bytes_received),0);
			if(0<b_recvd_temp){//proper operation
				(*bytes_received)+=b_recvd_temp;
			}else if(0>b_recvd_temp){//error returned, check ERRNO
//				printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at recvdetermined 1.\n");
				return b_recvd_temp;
			}else{//only '0==b_recvd' left, normal socket shutdown at counterside
//				printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at recvdetermined 2.\n");
				return b_recvd_temp;
			}
		}
	}else if(0>(*bytes_received)){//error returned, check ERRNO
//		printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at recvdetermined 1.\n");
		return (*bytes_received);
	}else{//only '0==b_recvd' left, normal socket shutdown at counterside
//		printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at recvdetermined 2.\n");
		return (*bytes_received);
	}
	return 1;
}


void printMAC_fromStr (unsigned char *MAC, int length){
	int i;
	length--;
	// Find the real length of the String
	for(; MAC[length] == '\0'; length--) {
		if (length < 0)
			goto NothingToPrint;
	}
	// length now holds the max index
	// And now we are able to properly print it.
	for(i=0; i<length; i++) {
		printf("%02X:", MAC[i]);
	}

	printf("%02X", MAC[length]);

	NothingToPrint:
//	printf("\nDebug-Stringlength: %d\n", length);
	;
}
void printMAC (unsigned char *MAC, int len, ...){
	//Only if len!=6 are optional arguments taken into account.
	//Just pass 'anything' but '0' as optional argument to make the function force to print MAC-like formated Data with any length and suppress the warnings.
	int i;
	va_list variadics;

	va_start(variadics,len);
	char option = (char)va_arg(variadics,int);

	if(!len){
		len=sizeof(MAC);
	}

	if((len<6) && (0==option)){
		printf("\nWARNING: You gave me an Array shorter than 6 Byte.Has: %d.\nI'll print the few you gave me, to help you debug ;o)\n",len);
	} else if((len>6) && (0==option)){
		printf("\nWARNING: You gave me an Array bigger than 6 Byte.Has: %d.\nI use the first six Byte.\n",len);
		len=6;
	}

	len--;
	for(i=0; i<len; i++) {
		printf("%02X:", MAC[i]);
	}

	printf("%02X", MAC[len]);

//	NothingToPrint:
//	printf("\nDebug-Stringlength: %d\n", length);
	;
}


int print_argv(char** argv, int argc){
	int i=0;
	printf("[ < < < < < < < < < < < < < < < <\n");
	for(;i<argc;i++){
		printf("%s\n",argv[i]);
	}
	printf(" > > > > > > > > > > > > > > > > ]\n");
	return 0;
}







//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//----  Time related Stuff  --------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================
//----  GET_REAL_TIME()  -----------------------------------------------------------------------------
//====================================================================================================
CREATE_PRINT_DAYTIME(,,stdout)
CREATE_PRINT_DAYTIME(_file,FILE *file,file)
//The Buffer needs at least 31 Bytes (the Null-Terminating-Character included)
CREATE_PRINT_DAYTIME(_buffer,char *buffer,buffer)

int GetRealDayTime(struct timespec *ts, struct tm *tim){
	GetRealTimeM(nano,ts,CLOCK_REALTIME);
	localtime_r(&(ts->tv_sec), tim);
	tim->tm_mon+=1;
	tim->tm_year+=1900;
	return 0;
}
//====================================================================================================
//----  Time Format Conversion  ----------------------------------------------------------------------
//====================================================================================================
time_t tmToSeconds(struct tm *tim){
	//Give this Function the "Real Numbers", not the "adjusted since Epoch" ones.
	//I.e. The month value has to match "Real Numbers", like 1-12, not 0-11
	//The Year value has to represent the actual year instead of beeing subtracted by 1900, i.e. 2017, not 117


    // Month-to-day offset for non-leap-years.
    static const int month_day[12] =
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

    // Calculation is actually very easy. There is only one difficulty: Leap Years.
    time_t month = (tim->tm_mon - 1) % 12;
    time_t year = (tim->tm_year - 1900) + (tim->tm_mon - 1) / 12;
    if (month < 0) {   // Negative values % 12 are still negative.
        month += 12;
        --year;
    }

    // This is the number of Februaries since 1900.
    const int year_for_leap = (month > 1) ? year + 1 : year;

	tzset();
    time_t res = tim->tm_sec                         // Seconds
        + 60 * (tim->tm_min                          // Minute = 60 seconds
        + 60 * (tim->tm_hour                         // Hour = 60 minutes
        + 24 * (month_day[month] + tim->tm_mday - 1  // Day = 24 hours
        + 365 * (year - 70)                          // Year = 365 days
        + (year_for_leap - 69) / 4                   // Every 4 years is     leap...
        - (year_for_leap - 1) / 100                  // Except centuries...
        + (year_for_leap + 299) / 400)))             // Except 400s.
		+ timezone;                                  // Adjust the timezone. This is a global variable from <time.h>, set by tzset();
    return res < 0 ? -1 : res;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////














//By calculation it would be something like
//   (int)((ceil(log10(num))+1)*sizeof(char))
// e.g. for printing a number to a string
int getDigitCountofInt(long long n){
    if (n < 0) n = (n == LLONG_MIN) ? LLONG_MAX : -n;
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    if (n < 10000000000) return 10;
    if (n < 100000000000) return 11;
    if (n < 1000000000000) return 12;
    if (n < 10000000000000) return 13;
    if (n < 100000000000000) return 14;
    if (n < 1000000000000000) return 15;
    if (n < 10000000000000000) return 16;
    if (n < 100000000000000000) return 17;
    if (n < 1000000000000000000) return 18;
    if (n < 10000000000000000000) return 19;
    if (n < 100000000000000000000) return 20;
    if (n < 1000000000000000000000) return 21;
    if (n < 10000000000000000000000) return 22;
    /*      2147483647 is 2^31-1 - add more ifs as needed
       and adjust this final return as well. */
    return 0; //Tells: Out of range.
}






char check_system_endianess(char *endianess){
#define ENDIAN_CHECK_VALUE ((char)(0x11))
	int n = ENDIAN_CHECK_VALUE;
	// TRUE: little endian
	if(*((char *)(&n)) == ENDIAN_CHECK_VALUE){
		*endianess = ENDIANESS_LITTLE;
		printfc(gray,"Info: ");printf("System is Little Endian.\n");
		return ENDIANESS_LITTLE;
	} else if(*(((char *)(&n))+sizeof(int)-1) == ENDIAN_CHECK_VALUE){
		printfc(gray,"Info: ");printf("System is Big Endian.\n");
		*endianess = ENDIANESS_BIG;
		return ENDIANESS_BIG;
	} else{
		printfc(yellow,"WARNING: ");printf("Couldn't get the System Endianess. Thus using Little Endian.\n");
		printf("This may cause some Operations like Network-Communication to not work properly...\n");
		*endianess = ENDIANESS_LITTLE;
		return ENDIANESS_LITTLE;
	}
#undef ENDIAN_CHECK_VALUE
}



uint64_t byte_swap(uint64_t value){
#define SHIFT_FROM_MID_1 8
#define SHIFT_FROM_MID_2 24
#define SHIFT_FROM_MID_3 40
#define SHIFT_FROM_MID_4 56
#define BITMASK_BYTE_0 0xff00000000000000
#define BITMASK_BYTE_1 0xff000000000000
#define BITMASK_BYTE_2 0xff0000000000
#define BITMASK_BYTE_3 0xff00000000
#define BITMASK_BYTE_4 0xff000000
#define BITMASK_BYTE_5 0xff0000
#define BITMASK_BYTE_6 0xff00
#define BITMASK_BYTE_7 0xff

	uint64_t swapped;

	swapped =	((value>>SHIFT_FROM_MID_4)&BITMASK_BYTE_7) |
				((value>>SHIFT_FROM_MID_3)&BITMASK_BYTE_6) |
				((value>>SHIFT_FROM_MID_2)&BITMASK_BYTE_5) |
				((value>>SHIFT_FROM_MID_1)&BITMASK_BYTE_4) |
				((value<<SHIFT_FROM_MID_1)&BITMASK_BYTE_3) |
				((value<<SHIFT_FROM_MID_2)&BITMASK_BYTE_2) |
				((value<<SHIFT_FROM_MID_3)&BITMASK_BYTE_1) |
				((value<<SHIFT_FROM_MID_4)&BITMASK_BYTE_0);

	return swapped;

#undef SHIFT_FROM_MID_1
#undef SHIFT_FROM_MID_2
#undef SHIFT_FROM_MID_3
#undef SHIFT_FROM_MID_4
#undef BITMASK_BYTE_0
#undef BITMASK_BYTE_1
#undef BITMASK_BYTE_2
#undef BITMASK_BYTE_3
#undef BITMASK_BYTE_4
#undef BITMASK_BYTE_5
#undef BITMASK_BYTE_6
#undef BITMASK_BYTE_7
}



//Valid Input-Bitwidths:
//  8-Bit, 16-Bit, 32-Bit, 64-Bit
//Example-Call:
//           uint32_t varToPrint = 1597;
//           print_Bin(&varToPrint, 4);
// (or:)     print_Bin(&varToPrint, sizeof(varToPrint));
void print_Bin(void* varAddr, int numBytes){
	int i;
	long long int passedVar;
	uint8_t* bytes=NULL;
	switch(numBytes){
	case 1:
		passedVar=*((int8_t*)varAddr);
		break;
	case 2:
		passedVar=*((int16_t*)varAddr);
		break;
	case 4:
		passedVar=*((int32_t*)varAddr);
		break;
	case 8:
		passedVar=*((int64_t*)varAddr);
		break;
	case 0:
		printf("Argument \'numBytes\' cannot be \'0\'.\n");
		return;
		break;
	case 3:
	case 5:
	case 6:
	case 7:
		printf("Invalid Argument. \'numBytes\' must be a \'2^x\'.\n");
		return;
		break;
	default:
		printf("Invalid Argument. \'numBytes\' is too high. Cannot be \'>8\'.\n");
		return;
		break;
	}
	printf("Binary (Base-2) Representation of \"[B10-Signed] %lli\", \"[B10-Unsigned] %llu\" (Decimal, Base-10):\n\t", (long long int)passedVar, (long long unsigned int)passedVar);
	bytes=malloc(numBytes);
	for(i=0;i<numBytes;i++){
		bytes[i]=(uint8_t)(passedVar%256);
		passedVar=passedVar>>8;
	}
	int maxIndex=numBytes-1;
	printf(BYTETOBINPATTERN_SPACE, BYTETOBIN(bytes[maxIndex]));
	for(i=1;i<numBytes;i++){
		printf(" | "BYTETOBINPATTERN_SPACE,BYTETOBIN(bytes[maxIndex-i]));
	}
	puts("");
	if(bytes)
		free(bytes);
}


//This Variant uses Pointer-Arithmetic to Split the Bytes.
//Thus the Output is depending on the Main-Memory-Endianess.
//Preferably use the other Variant.
void print_Bin_by_point(void* varAddr, int numBytes){
	int i;
	int64_t passedVar;
	switch(numBytes){
	case 1:
		passedVar=*((int8_t*)((int8_t*)varAddr));
		break;
	case 2:
		passedVar=*((int16_t*)((int8_t*)varAddr));
		break;
	case 4:
		passedVar=*((int32_t*)((int8_t*)varAddr));
		break;
	case 8:
		passedVar=*((int64_t*)((int8_t*)varAddr));
		break;
	case 0:
		printf("Argument \'numBytes\' cannot be \'0\'.\n");
		return;
		break;
	case 3:
	case 5:
	case 6:
	case 7:
		printf("Invalid Argument. \'numBytes\' must be a \'2^x\'.\n");
		return;
		break;
	default:
		printf("Invalid Argument. \'numBytes\' is too high. Cannot be \'>8\'.\n");
		return;
		break;
	}
	printf("Binary (Base-2) Representation of \"[B10-Signed]%lli\", \"[B10-Unsigned]%llu\" (Decimal, Base-10):\n\t", (int64_t)passedVar, (uint64_t)passedVar);
	printf(BYTETOBINPATTERN_SPACE, BYTETOBIN(*((uint8_t*)varAddr)));
	for(i=1;i<numBytes;i++){
		printf(" | "BYTETOBINPATTERN_SPACE,BYTETOBIN(*(((uint8_t*)varAddr)+i)));
	}
	puts("");
}













#undef NO_DENKR_ESSENTIALS_AUXILIARY_C_FUNCTIONS
#undef DENKR_ESSENTIALS_AUXILIARY_C
