#ifndef DENKR_ESSENTIALS_AUXILIARY_H
#define DENKR_ESSENTIALS_AUXILIARY_H
/*
 * Authored by
 * Dennis Krummacker (03.06.14-)
 */

#include <global/global_settings.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "PreC/DenKr_PreC.h"
#include "Program_Files/P_Files_Path.h"
#include "getRealTime.h"
#include"DenKr_essentials/Terminal/Terminal_Colors.h"





//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  The few Global Variables from the Beginning in "auxiliary.c"  ------------------------------//
//----  And the Functions to be visible outside  ---------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
#ifndef NO_DENKR_ESSENTIALS_AUXILIARY_C_FUNCTIONS
#if (PROGRAM_ARGUMENTS_GLOBAL_AVAILABILITY == PROGRAM_ARGUMENTS_GLOBAL_AVAILABILITY___AVAILABLE)
	extern int argcg;
	extern char **argvg;
#endif
extern char system_endianess;
extern char ansi_escape_use;
//NOTE: These lengths are really "length" and NOT "sizeof" ;o)
#if (PROGRAM_NAME_VAR_AVAILABILITY == PROGRAM_NAME_VAR_AVAILABILITY___GLOBAL)
	extern int ProgramName_length;
	extern char *ProgramName;
#endif
#if (STORAGE_FILES_PATH_VAR_AVAILABILITY == STORAGE_FILES_PATH_VAR_AVAILABILITY___GLOBAL)
	extern int StorageFilesPath_length;
	extern char *StorageFilesPath;
#endif
#if (PROGRAM_PATH_VAR_AVAILABILITY == PROGRAM_PATH_VAR_AVAILABILITY___GLOBAL)
	extern int ProgPath_length;
	extern char *ProgPath;
#endif
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#include "function_creator_funcname.h"
extern int DenKr_essentials_Init(int argc, char **argv);
extern int senddetermined (int socket, char *msg, int msglen);
extern int recvdetermined(int* bytes_received, int socket, void *buffer, size_t size, int flags);
extern void printMAC_fromStr (unsigned char *MAC, int length);
extern void printMAC (unsigned char *MAC, int len,...);
extern int print_argv(char** argv, int argc);
extern CREATE_PRINT_DAYTIME_FUNCNAME_DECLARE(,);
extern CREATE_PRINT_DAYTIME_FUNCNAME_DECLARE(_file,FILE *file);
//The Buffer needs at least 31 Bytes (the Null-Terminating-Character included)
extern CREATE_PRINT_DAYTIME_FUNCNAME_DECLARE(_buffer,char *buffer);
extern int GetRealDayTime(struct timespec *ts, struct tm *tim);
extern time_t tmToSeconds(struct tm *tim);
extern int getDigitCountofInt(long long n);
extern char check_system_endianess(char *endianess);
extern uint64_t byte_swap(uint64_t value);
extern void print_Bin(void* varAddr, int numBytes);
extern void print_Bin_by_point(void* varAddr, int numBytes);
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////












//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  ANSI Terminal Color Stuff  -----------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
#define ANSI_COLOR_BLACK "\033[22;30m"
#define ANSI_COLOR_RED "\033[22;31m"
#define ANSI_COLOR_GREEN "\033[22;32m"
#define ANSI_COLOR_BROWN "\033[22;33m"
#define ANSI_COLOR_BLUE "\033[22;34m"
#define ANSI_COLOR_MAGENTA "\033[22;35m"
#define ANSI_COLOR_CYAN "\033[22;36m"
#define ANSI_COLOR_GRAY "\033[22;37m"
#define ANSI_COLOR_DARK_GRAY "\033[01;30m"
#define ANSI_COLOR_LIGHT_RED "\033[01;31m"
#define ANSI_COLOR_LIGHT_GREEN "\033[01;32m"
#define ANSI_COLOR_YELLOW "\033[01;33m"
#define ANSI_COLOR_LIGHT_BLUE "\033[01;34m"
#define ANSI_COLOR_LIGHT_MAGENTA "\033[01;35m"
#define ANSI_COLOR_LIGHT_CYAN "\033[01;36m"
#define ANSI_COLOR_WHITE "\033[01;37m"
#define ANSI_COLOR_RESET "\x1b[0m"
//------------------------------------------------------
#define ANSI_COLOR_black ANSI_COLOR_BLACK
#define ANSI_COLOR_red ANSI_COLOR_RED
#define ANSI_COLOR_green ANSI_COLOR_GREEN
#define ANSI_COLOR_brown ANSI_COLOR_BROWN
#define ANSI_COLOR_blue ANSI_COLOR_BLUE
#define ANSI_COLOR_magenta ANSI_COLOR_MAGENTA
#define ANSI_COLOR_cyan ANSI_COLOR_CYAN
#define ANSI_COLOR_gray ANSI_COLOR_GRAY
#define ANSI_COLOR_dark_gray ANSI_COLOR_DARK_GRAY
#define ANSI_COLOR_light_red ANSI_COLOR_LIGHT_RED
#define ANSI_COLOR_light_green ANSI_COLOR_LIGHT_GREEN
#define ANSI_COLOR_yellow ANSI_COLOR_YELLOW
#define ANSI_COLOR_light_blue ANSI_COLOR_LIGHT_BLUE
#define ANSI_COLOR_light_magenta ANSI_COLOR_LIGHT_MAGENTA
#define ANSI_COLOR_light_cyan ANSI_COLOR_LIGHT_CYAN
#define ANSI_COLOR_white ANSI_COLOR_WHITE
#define ANSI_COLOR_reset ANSI_COLOR_RESET
//------------------------------------------------------
#define ANSI_COLOR_Black ANSI_COLOR_BLACK
#define ANSI_COLOR_Red ANSI_COLOR_RED
#define ANSI_COLOR_Green ANSI_COLOR_GREEN
#define ANSI_COLOR_Brown ANSI_COLOR_BROWN
#define ANSI_COLOR_Blue ANSI_COLOR_BLUE
#define ANSI_COLOR_Magenta ANSI_COLOR_MAGENTA
#define ANSI_COLOR_Cyan ANSI_COLOR_CYAN
#define ANSI_COLOR_Gray ANSI_COLOR_GRAY
#define ANSI_COLOR_Dark_gray ANSI_COLOR_DARK_GRAY
#define ANSI_COLOR_Light_Red ANSI_COLOR_LIGHT_RED
#define ANSI_COLOR_Light_Green ANSI_COLOR_LIGHT_GREEN
#define ANSI_COLOR_Yellow ANSI_COLOR_YELLOW
#define ANSI_COLOR_Light_Blue ANSI_COLOR_LIGHT_BLUE
#define ANSI_COLOR_Light_Magenta ANSI_COLOR_LIGHT_MAGENTA
#define ANSI_COLOR_Light_Cyan ANSI_COLOR_LIGHT_CYAN
#define ANSI_COLOR_White ANSI_COLOR_WHITE
#define ANSI_COLOR_Reset ANSI_COLOR_RESET
//
//For now just hardcoded and use ANSI Escape on the Output Console
//Later on maybe something like a config File Read-In with possible Values:
// on, off, auto
//and than with the auto something like the crazy Lookup-Table Stuff, that ncurses does.
#define SET_ansi_escape_use ansi_escape_use = 1;
//
//And a macro for the quick programming use of changing the Console Color
#define ANSICOLORSET(ANSIcolorToSet) if(ansi_escape_use==1){ \
		printf(ANSIcolorToSet); \
	}
//
#define ANSICOLORRESET if(ansi_escape_use==1){ \
		printf(ANSI_COLOR_RESET); \
	}
//And to make it still shorter:
#define printfc(color,...) _printfc(ANSI_COLOR_##color,__VA_ARGS__)
#define _printfc(color,...) if(ansi_escape_use==1){ \
		printf(color); \
		printf(__VA_ARGS__); \
		printf(ANSI_COLOR_RESET); \
	}else{ \
		printf(__VA_ARGS__); \
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////




















//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  GET_REAL_TIME()  ---------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
/*Macro to let you choose, which kind of data format you
 *want to get returned, depending on the number of passed arguments
 *
 * double time;
 * time = GET_REAL_TIME();
 *		returns you back a double-float in seconds, with micro/nano-seconds as decimals.
 *		This one is portable over different Operating Systems.
 *		It delivers you best available precision. But it doesn't guarentee a "Time since Epoch",
 *		i.e. maybe, or rather very probably you can't use the result to calculate Date and Time.
 *		So only use this for purposes like Application Runtime, Point-in-Time comparisons and
 *		stuff like that.
 *
 * struct timespec ts;
 * char precision;
 * precision = GET_REAL_TIME(&ts);
 *		Edits the passed timespec-elements, seconds and nano-seconds
 *
 * struct timeval tm;
 * char precision;
 * precision = GET_REAL_TIME(&tm,NULL);
 *		Edits the passed timeval-elements, seconds and micro-seconds. Eventually in system available nano-second information is lost.
 *
 *	precision:
 *		see #defines below
 *
 * The 'NULL' can be anything, really ANYTHING. It just has to be ONE argument.
 * It isn't really used. It is just misused to split the macro by the argument count
 * So let us use 'NULL' to show this and particularly to make it pretty to watch. We programmers all love this NULL ^^
 */////////////////////////////////////////////////////////////////////////////////////////////////
#define GetRealTimeM(...) macro_overloader(_GET_REAL_TIME_OVERRIDE, __VA_ARGS__)(__VA_ARGS__)
#define _GET_REAL_TIME_OVERRIDE0(...) getRealTime_double()
#define _GET_REAL_TIME_OVERRIDE1(...) getRealTime_double_clock(__VA_ARGS__)
#define _GET_REAL_TIME_OVERRIDE2(precision,variable,...) GetRealTime_SPLIT(precision,variable)
#define _GET_REAL_TIME_OVERRIDE3(format,variable,clock,...) GetRealTime_SPLIT_Clock(format,variable,clock)
#define _GET_REAL_TIME_OVERRIDE4(...) "ERROR. To many variadic arguments in overloaded macro"ERROR
#define _GET_REAL_TIME_OVERRIDE5(...) _GET_REAL_TIME_OVERRIDE4(__VA_ARGS__)
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////
//  Necessary Macros for the PreC Function-Split
////////////////////////////
//#define COMPARE_(x) x
#define COMPARE_timespec(x) x
#define COMPARE_timeval(x) x
#define COMPARE_micro(x) x
#define COMPARE_nano(x) x
#define COMPARE_double(x) x
#define COMPARE_realtime(x) x
#define COMPARE_monotonic_precise(x) x
#define COMPARE_monotonic_raw(x) x
#define COMPARE_monotonic(x) x
#define COMPARE_highres(x) x
#define COMPARE_process_cputime_id(x) x
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define GetRealTime_SPLIT(PRECISION,VARIABLE) \
		SWITCH( \
			EQUAL(PRECISION,nano), \
				getRealTime_nanoseconds(VARIABLE) \
				, \
			EQUAL(PRECISION,micro), \
				getRealTime_microseconds(VARIABLE) \
				, \
			EQUAL(PRECISION,timespec), \
				getRealTime_nanoseconds(VARIABLE) \
				, \
			EQUAL(PRECISION,timeval), \
				getRealTime_microseconds(VARIABLE) \
				, \
			EQUAL(PRECISION,double), \
			getRealTime_double_clock(VARIABLE) \
				, \
			getRealTime_double() \
		)
	// In the double case, the VARIABLE is actually the CLOCK
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define GetRealTime_SPLIT_Clock(FORMAT,VARIABLE,CLOCK) \
		SWITCH( \
			EQUAL(FORMAT,nano), \
				getRealTime_nanoseconds_clock(VARIABLE,CLOCK) \
				, \
			EQUAL(FORMAT,micro), \
				getRealTime_microseconds_clock(VARIABLE,CLOCK) \
				, \
			EQUAL(FORMAT,timespec), \
				getRealTime_nanoseconds_clock(VARIABLE,CLOCK) \
				, \
			EQUAL(FORMAT,timeval), \
				getRealTime_microseconds_clock(VARIABLE,CLOCK) \
				, \
			EQUAL(FORMAT,double), \
				getRealTime_double_clock(CLOCK) \
				, \
			getRealTime_double(); \
		)

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define GET_REAL_TIME_PREC_UNKNOWN 0
#define GET_REAL_TIME_PREC_SECONDS INC(GET_REAL_TIME_PREC_UNKNOWN)
#define GET_REAL_TIME_PREC_MILLI_SECONDS INC(GET_REAL_TIME_PREC_SECONDS)
#define GET_REAL_TIME_PREC_MICRO_SECONDS INC(GET_REAL_TIME_PREC_MILLI_SECONDS)
#define GET_REAL_TIME_PREC_NANO_SECONDS INC(GET_REAL_TIME_PREC_MICRO_SECONDS)
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


















//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  depr(...) aka Debug Print with variable Arguments  -----------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//  Look at this awesome little helper!
//  You really want to use this. It can help you a lot with debugging.
//----------------------------------------------------------------------------------------------------
// Debug Print
// Works differently, with a differing Number of delivered Arguments
// Could be anything from 0 to gratuitous amounts of Arguments
/* Use like this:
 * The Arguments:
 * depr(); Prints Line Number of Makro Usage and an incrementing Counter
 * depr(Index); Additionally the delivered Index
 * depr(Index,String); Additionally a String, like basic printf
 * depr(Index,String,StringArgs); Additionally Arguments for the preceding String, like with printf
 * Full Command Example:
 * depr(1,"Test float: %lf",floatvariable);
 * Simple Examples for the different Usage Methods:
 * depr()
 * depr(1)
 * depr(2,"test")
 * depr(3,"test2 :%d",5)
 *////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG
	extern int DebugPrintCount;
#endif
#ifdef DEBUG
	#define deprColorPrefix blue
	#define deprColorDebug green
	#define deprColorIndex magenta
	#define deprColorIndexNumber red
	#define deprColorLine cyan
	#define deprColorFile cyan
	#define deprColorCounter brown
	#define deprExpandprintfc(color,...) printfc(color,__VA_ARGS__)

	//The MacroOverloader is specified inside "remainder.h" (I think I refactored this into "DenKr_PreC.h", but I am not completely sure...)

	#define depr(...) macro_overloader(_depr, __VA_ARGS__)(__VA_ARGS__)
	#define _depr0(...) deprExpandprintfc(deprColorPrefix,"\n==> "); \
		deprExpandprintfc(deprColorDebug,"Debug "); \
		deprExpandprintfc(deprColorLine,"Line "); \
		deprExpandprintfc(deprColorIndexNumber,"%d ",__LINE__); \
		deprExpandprintfc(deprColorFile,"File "); \
		deprExpandprintfc(deprColorIndexNumber,"%s",__FILE__); \
		deprExpandprintfc(deprColorCounter," (#%d)",DebugPrintCount); \
		puts(""); \
		DebugPrintCount++;
	#define _depr1(idx) deprExpandprintfc(deprColorPrefix,"\n==> "); \
		deprExpandprintfc(deprColorDebug,"Debug "); \
		deprExpandprintfc(deprColorIndex,"Idx "); \
		deprExpandprintfc(deprColorIndexNumber,#idx); \
		deprExpandprintfc(deprColorLine," Line "); \
		deprExpandprintfc(deprColorIndexNumber,"%d ",__LINE__); \
		deprExpandprintfc(deprColorFile,"File "); \
		deprExpandprintfc(deprColorIndexNumber,"%s",__FILE__); \
		deprExpandprintfc(deprColorCounter," (#%d)",DebugPrintCount); \
		puts(""); \
		DebugPrintCount++;
	#define _depr2(idx,...) deprExpandprintfc(deprColorPrefix,"\n==> "); \
		deprExpandprintfc(deprColorDebug,"Debug "); \
		deprExpandprintfc(deprColorIndex,"Idx "); \
		deprExpandprintfc(deprColorIndexNumber,#idx); \
		deprExpandprintfc(deprColorLine," Line "); \
		deprExpandprintfc(deprColorIndexNumber,"%d ",__LINE__); \
		deprExpandprintfc(deprColorFile,"File "); \
		deprExpandprintfc(deprColorIndexNumber,"%s",__FILE__); \
		deprExpandprintfc(deprColorCounter," (#%d)",DebugPrintCount); \
		printf(" | "__VA_ARGS__); \
		puts(""); \
		DebugPrintCount++;
	#define _depr3(idx,...) deprExpandprintfc(deprColorPrefix,"\n==> "); \
		deprExpandprintfc(deprColorDebug,"Debug "); \
		deprExpandprintfc(deprColorIndex,"Idx "); \
		deprExpandprintfc(deprColorIndexNumber,#idx); \
		deprExpandprintfc(deprColorLine," Line "); \
		deprExpandprintfc(deprColorIndexNumber,"%d ",__LINE__); \
		deprExpandprintfc(deprColorFile,"File "); \
		deprExpandprintfc(deprColorIndexNumber,"%s",__FILE__); \
		deprExpandprintfc(deprColorCounter," (#%d)",DebugPrintCount); \
		printf(" | "__VA_ARGS__); \
		puts(""); \
		DebugPrintCount++;
	#define _depr4(idx,...) _depr3(idx,__VA_ARGS__)
	#define _depr5(idx,...) _depr3(idx,__VA_ARGS__)
	#define _depr6(idx,...) _depr3(idx,__VA_ARGS__)
	#define _depr7(idx,...) _depr3(idx,__VA_ARGS__)
	#define _depr8(idx,...) _depr3(idx,__VA_ARGS__)
	#define _depr9(idx,...) _depr3(idx,__VA_ARGS__)
#else
	#define depr(...)
#endif
//NOTE:
// - depr2(idx,...) could be depr2(idx, str) instead
// - depr3(idx,...) could be depr3(idx, str, format) instead
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////














//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Residual Collection  -----------------------------------------------------------------------//
//----    OK, to be honest... I organized all this not completely pursuing one holistic track...  --//
//----    Soooo... be sure to also check the "DenKr_PreC.h" of "DenKr_essentials"...  --------------//
//----       especially the section "Some further, fine, helpful Macros".  -------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//
//----------------------------------------------------------------------------------------------------
//----  Flag Handling  -------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//Macros to Set or Unset a flag
#define FLAG_SET(FlagHolder,Flag) (FlagHolder)=(FlagHolder) | (Flag)
//------------------------------------------------------------------------
#define FLAG_UNSET(FlagHolder,Flag) (FlagHolder)=(FlagHolder) & (~(Flag))
//------------------------------------------------------------------------
#define FLAG_CHECK(FlagHolder,Flag) ((FlagHolder) & (Flag))
//
//----------------------------------------------------------------------------------------------------
//----  Some Utils  -------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//    Obviously better avoid arguments with side-effects (e.g. ++i) in use with these
#ifndef MAX
	#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
	#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
//----------------------------------------------------------------------------------------------------
//----    -------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//Use this to specify Mili-Seconds from Nano-Seconds
#define MS_TO_US(MS) MS ## 000
#define US_TO_NS(US) US ## 000
#define MS_TO_NS(MS) MS ## 000000
//
#define WAITNS(SEC,NSEC) { \
	struct timespec remainingdelay; \
	remainingdelay.tv_sec = SEC; \
	remainingdelay.tv_nsec = NSEC; \
	while (nanosleep(&remainingdelay, &remainingdelay)<0){} \
}
//
#define BYTETOBINPATTERN_SPACE "%d%d%d%d %d%d%d%d"
#define BYTETOBINPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBIN(byte)  \
  ((byte) & 0x80 ? 1 : 0), \
  ((byte) & 0x40 ? 1 : 0), \
  ((byte) & 0x20 ? 1 : 0), \
  ((byte) & 0x10 ? 1 : 0), \
  ((byte) & 0x08 ? 1 : 0), \
  ((byte) & 0x04 ? 1 : 0), \
  ((byte) & 0x02 ? 1 : 0), \
  ((byte) & 0x01 ? 1 : 0)
//-------------------------------------------------------------------------------
/* Use like:
char testchar=0x02;
printf("Bsp Convert Hex: %02X to Bin "BYTETOBINPATTERN"\n",testchar, BYTETOBIN(testchar));
*/
//
//----------------------------------------------------------------------------------------------------------
//----  Something 'close' to boolean  ----------------------------------------------------------------------
//----  Handling similiar, Hardware-Representation not really...  ------------------------------------------
//----     Use it, if you like. I personally don't really like this.  --------------------------------------
//----     In most cases i prefer using Flags. But to use a whole Byte sometimes also has its moments.  ----
//----     Mostly from the Access-Performance Point of View...  --------------------------------------------
//----------------------------------------------------------------------------------------------------------
typedef uint8_t BOOL;
//
#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif
//
//----------------------------------------------------------------------------------------------------------
//----  Memory Allocation  ---------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
#define print_malloc_size(voidpoint) { \
	size_t mallocsize=malloc_usable_size(voidpoint); \
	ANSICOLORSET(ANSI_COLOR_BLUE); \
	printf("Allocated size: %d",(int)mallocsize); \
	ANSICOLORRESET; \
	printf("\n"); \
}
//
//----------------------------------------------------------------------------------------------------
//----  System Endianess, Check & Conversion  --------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#define ENDIANESS_LITTLE 0
#define ENDIANESS_BIG 1
#define ENDIANESS_UNKNOWN 2
//
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----  Creates a char [][], or char ** if you want so, containing the passed strings,  --------------
//----  available from the passed variable name.  ----------------------------------------------------
//----  USAGE: CREATE_argv(variable_name, List_of_strings)  ------------------------------------------
//----        Example: CREATE_argv(cfg_file_v, "cfg/SDN/Ctrl.cfg", "Program.cfg")  -------------------
//----  Constant Strings are working just as well as runtime or any Null-terminated String/char*  ----
//----------------------------------------------------------------------------------------------------
//----  Two Versions available:  ---------------------------------------------------------------------
//----    1. The "General One". Like mentioned above, works with every passed string, but bit worse  -
//----       Performance. Most Operations are done at runtime  ---------------------------------------
//----    2. The "Constant One". Works ONLY with constant strings. Thus brings better Performance  ---
//----       and Operations are done at Compile-Time.  -----------------------------------------------
//----------------------------------------------------------------------------------------------------
// sizeof would provide better performance, but strlen is failsafe. Mind a case, where you pass a string from which the storage size isn't known, for example a malloced char*, created during runtime, instead of a static string
#define __CREATE_argv_sizeof_append(STR) \
	+ strlen(STR)
#define _CREATE_argv_sizeof(STR1,...) \
	strlen(STR1) CALL_MACRO_X_FOR_EACH(__CREATE_argv_sizeof_append,__VA_ARGS__)

#define _CREATE_argv_loopbody(i, VAR, VAR_, ...) \
	IF(EQUAL(i,0))( \
		VAR[i]=VAR_; \
		snprintf(VAR[i],strlen(ARRAY_ENTRY(i,(__VA_ARGS__)))+1,ARRAY_ENTRY(i,(__VA_ARGS__))); \
	)IF(NOT_EQUAL(i,0))( \
		VAR[i]=VAR[DEC(i)]+strlen(VAR[DEC(i)])+1; \
		snprintf(VAR[i],strlen(ARRAY_ENTRY(i,(__VA_ARGS__)))+1,ARRAY_ENTRY(i,(__VA_ARGS__))); \
	)

#define CREATE_argv(VAR,...) \
	char *VAR[COUNT_VARARGS(__VA_ARGS__)]; \
	char CONCAT(VAR,_)[COUNT_VARARGS(__VA_ARGS__) + _CREATE_argv_sizeof(__VA_ARGS__)]; \
	EVAL_SMALL(REPEAT(COUNT_VARARGS(__VA_ARGS__), _CREATE_argv_loopbody, VAR, CONCAT(VAR,_), __VA_ARGS__))
//----------------------------------------------------------------------------------------------------
#define __CREATE_argv_CONST_sizeof_append(STR) \
	+ sizeof(STR)
#define _CREATE_argv_CONST_sizeof(STR1,...) \
	sizeof(STR1) CALL_MACRO_X_FOR_EACH(__CREATE_argv_CONST_sizeof_append,__VA_ARGS__)

#define _CREATE_argv_CONST_loopbody(i, VAR, VAR_, ...) \
	IF(EQUAL(i,0))( \
		VAR[i]=VAR_; \
		memcpy(VAR[i],ARRAY_ENTRY(i,(__VA_ARGS__)),sizeof(ARRAY_ENTRY(i,(__VA_ARGS__)))); \
	)IF(NOT_EQUAL(i,0))( \
		VAR[i]=VAR[DEC(i)]+sizeof(ARRAY_ENTRY(DEC(i),(__VA_ARGS__))); \
		memcpy(VAR[i],ARRAY_ENTRY(i,(__VA_ARGS__)),sizeof(ARRAY_ENTRY(i,(__VA_ARGS__)))); \
	)

#define CREATE_argv_CONST(VAR,...) \
	char *VAR[COUNT_VARARGS(__VA_ARGS__)]; \
	char CONCAT(VAR,_)[_CREATE_argv_CONST_sizeof(__VA_ARGS__)]; \
	EVAL_SMALL(REPEAT(COUNT_VARARGS(__VA_ARGS__), _CREATE_argv_CONST_loopbody, VAR, CONCAT(VAR,_), __VA_ARGS__))
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////








#endif /* DENKR_ESSENTIALS_AUXILIARY_H */
