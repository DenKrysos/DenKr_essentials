
/*
 * Authored by
 * Dennis Krummacker (20.03.16)
 */

#define NO_DENKR_ESSENTIALS_GETREALTIME_C_FUNCTIONS

#ifdef _WIN32
#include <Windows.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>	/* POSIX flags */
#include <time.h>	/* clock_gettime(), time() */
#include <sys/time.h>	/* gethrtime(), gettimeofday() */
#include <stdlib.h>
#include <stdint.h>

#include "auxiliary.h"

#if defined(__MACH__) && defined(__APPLE__)
#include <mach/mach.h>
#include <mach/mach_time.h>
#endif

#else
#error "Unable to define getRealTime( ): Unknown Operating System."
#endif



/*
 * Some Info about the Clocks:
 *
   CLOCK_REALTIME
          System-wide real-time clock.  Setting this clock requires appro-
          priate privileges.

   CLOCK_MONOTONIC
          Clock that cannot be set and  represents  monotonic  time  since
          some unspecified starting point.

   CLOCK_MONOTONIC_RAW (since Linux 2.6.28; Linux-specific)
          Similar  to  CLOCK_MONOTONIC, but provides access to a raw hard-
          ware-based time that is not subject to NTP adjustments.
          It runs from System-Start on.

  CLOCK_MONOTONIC may be influenced by NTP adjustments, while CLOCK_MONOTONIC_RAW isn't.
  All these clocks typically have a resolution of one nanosecond (check that with clock_getres())


  Some rough Access Times (Time-Overhead) for accessing different Clocks on a reasonably modern system (as for 2016)
  clock_gettime(CLOCK_MONOTONIC_RAW)       100ns/call
  clock_gettime(CLOCK_MONOTONIC)           25ns/call
  clock_gettime(CLOCK_REALTIME)            25ns/call
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID)  400ns/call
  rdtsc (different inline assembly implementations)     300 - 600ns/call

  The modern Hardware Clocks may have a fine resolution of 1 Nanosecond. But...
  1. Without periodically synchronization the drift apart
  2. A Call to a Clock swollows an Overhead -> For Calculations / Comparisons and so on this results in respective inaccuracy
  	  	  -> Numerously Calls to Clocks slows down Application-/System Performance
*
*
*/








/**
 * Returns the real time, in seconds, or -1.0 if an error occurred.
 *
 * Time is measured since an arbitrary and OS-dependent start time.
 * The returned real time is only useful for computing an elapsed time
 * between two calls to this function.
 */
/*
 * Mind the Macro
 * GetRealTimeM(variable-args) from the source-File
 * remainder.h
 * This is a Overloaded Macro, which chooses the right function at compile time
 */



	//Everything other than the Linux part isn't adjusted yet.
#ifdef _WIN32
// Windows ==============================================================
	double getRealTime(){
		FILETIME tm;
		ULONGLONG t;
		#if defined(NTDDI_WIN8) && NTDDI_VERSION >= NTDDI_WIN8
		// Windows 8, Windows Server 2012 and later. ==============================================================
			GetSystemTimePreciseAsFileTime( &tm );
		#else
		// Windows 2000 and later ==============================================================
			GetSystemTimeAsFileTime( &tm );
		#endif
		t = ((ULONGLONG)tm.dwHighDateTime << 32) | (ULONGLONG)tm.dwLowDateTime;
		return (double)t / 10000000.0;
	}



#elif (defined(__hpux) || defined(hpux)) || ((defined(__sun__) || defined(__sun) || defined(sun)) && (defined(__SVR4) || defined(__svr4__)))
// HP-UX, Solaris ==============================================================
	double getRealTime(){
		return (double)gethrtime( ) / 1000000000.0;
	}



#elif defined(__MACH__) && defined(__APPLE__)
// OSX ==============================================================
	double getRealTime(){
		static double timeConvert = 0.0;
		if ( timeConvert == 0.0 )
		{
			mach_timebase_info_data_t timeBase;
			(void)mach_timebase_info( &timeBase );
			timeConvert = (double)timeBase.numer /
				(double)timeBase.denom /
				1000000000.0;
		}
		return (double)mach_absolute_time( ) * timeConvert;
	}



#elif defined(_POSIX_VERSION)
// POSIX ==============================================================
	double getRealTime_double(){
		#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
				struct timespec ts;
			#if defined(CLOCK_MONOTONIC_PRECISE)
			// BSD ==============================================================
				if ( clock_gettime( CLOCK_MONOTONIC_PRECISE, &ts ) != -1 ){
					return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
				}
			#elif defined(CLOCK_MONOTONIC_RAW)
			// Linux ==============================================================
				if ( clock_gettime( CLOCK_MONOTONIC_RAW, &ts ) != -1 ){
					return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
				}
			#elif defined(CLOCK_HIGHRES)
			// Solaris ==============================================================
				if ( clock_gettime( CLOCK_HIGHRES, &ts ) != -1 ){
					return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
				}
			#elif defined(CLOCK_MONOTONIC)
			// AIX, BSD, Linux, POSIX, Solaris ==============================================================
				if ( clock_gettime( CLOCK_MONOTONIC, &ts ) != -1 ){
					return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
				}
			#elif defined(CLOCK_REALTIME)
			// AIX, BSD, HP-UX, Linux, POSIX ==============================================================
				if ( clock_gettime( CLOCK_REALTIME, &ts ) != -1 ){
					return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
				}
			#else
			// Unknown ==============================================================
				//Direct Fallthrough
			#endif // CLOCK_
		#endif // _POSIX_TIMERS

		//Fall through
		// The "Good old method". AIX, BSD, Cygwin, HP-UX, Linux, OSX, POSIX, Solaris.
		struct timeval tv;
		gettimeofday( &tv, NULL );
		return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
	}





	char getRealTime_nanoseconds(struct timespec *ts){
		#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
			#if defined(CLOCK_MONOTONIC_PRECISE)
			// BSD ==============================================================
				if ( clock_gettime( CLOCK_MONOTONIC_PRECISE, ts ) != -1 ){
					return GET_REAL_TIME_PREC_NANO_SECONDS;
				}
			#elif defined(CLOCK_MONOTONIC_RAW)
			// Linux ==============================================================
				if ( clock_gettime( CLOCK_MONOTONIC_RAW, ts ) != -1 ){
					return GET_REAL_TIME_PREC_NANO_SECONDS;
				}
			#elif defined(CLOCK_HIGHRES)
			// Solaris ==============================================================
				if ( clock_gettime( CLOCK_HIGHRES, ts ) != -1 ){
					return GET_REAL_TIME_PREC_NANO_SECONDS;
				}
			#elif defined(CLOCK_MONOTONIC)
			// AIX, BSD, Linux, POSIX, Solaris ==============================================================
				if ( clock_gettime( CLOCK_MONOTONIC, ts ) != -1 ){
					return GET_REAL_TIME_PREC_NANO_SECONDS;
				}
			#elif defined(CLOCK_REALTIME)
			// AIX, BSD, HP-UX, Linux, POSIX ==============================================================
				if ( clock_gettime( CLOCK_REALTIME, ts ) != -1 ){
					return GET_REAL_TIME_PREC_NANO_SECONDS;
				}
			#else
			// Unknown ==============================================================
				//Direct Fallthrough
			#endif // CLOCK_
		#endif // _POSIX_TIMERS

		//Fall through
		// The "Good old method". AIX, BSD, Cygwin, HP-UX, Linux, OSX, POSIX, Solaris.
		struct timeval tv;
		gettimeofday( &tv, NULL );
		ts->tv_sec = tv.tv_sec;
		ts->tv_nsec = (tv.tv_usec) * 1000;
		return GET_REAL_TIME_PREC_MICRO_SECONDS;
	}




	char getRealTime_microseconds(struct timeval *tv){
		gettimeofday( tv, NULL );
		return GET_REAL_TIME_PREC_MICRO_SECONDS;
	}




//The uint16_t functions return back a 16 Bit value, wherein the leftmost 8 Bits are the id of
// the actually used Clock (if any) and the rightmost are the precision code.
//I.e.: return clockid | precision
//			XXXX XXXX | XXXX XXXX
	uint16_t getRealTime_nanoseconds_clock(struct timespec *ts, clockid_t clockid){
		if ( clock_gettime( clockid, ts ) != -1 ){
			return (((uint16_t)clockid)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
		}else{
			#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
				#if defined(CLOCK_MONOTONIC_PRECISE)
				// BSD ==============================================================
					if ( clock_gettime( CLOCK_MONOTONIC_PRECISE, ts ) != -1 ){
						return (((uint16_t)CLOCK_MONOTONIC_PRECISE)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
					}
				#elif defined(CLOCK_MONOTONIC_RAW)
				// Linux ==============================================================
					if ( clock_gettime( CLOCK_MONOTONIC_RAW, ts ) != -1 ){
						return (((uint16_t)CLOCK_MONOTONIC_RAW)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
					}
				#elif defined(CLOCK_HIGHRES)
				// Solaris ==============================================================
					if ( clock_gettime( CLOCK_HIGHRES, ts ) != -1 ){
						return (((uint16_t)CLOCK_HIGHRES)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
					}
				#elif defined(CLOCK_MONOTONIC)
				// AIX, BSD, Linux, POSIX, Solaris ==============================================================
					if ( clock_gettime( CLOCK_MONOTONIC, ts ) != -1 ){
						return (((uint16_t)CLOCK_MONOTONIC)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
					}
				#elif defined(CLOCK_REALTIME)
				// AIX, BSD, HP-UX, Linux, POSIX ==============================================================
					if ( clock_gettime( CLOCK_REALTIME, ts ) != -1 ){
						return (((uint16_t)CLOCK_REALTIME)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
					}
				#else
				// Unknown ==============================================================
					//Direct Fallthrough
				#endif // CLOCK_
			#endif // _POSIX_TIMERS

			//Fall through
			// The "Good old method". AIX, BSD, Cygwin, HP-UX, Linux, OSX, POSIX, Solaris.
			struct timeval tv;
			gettimeofday( &tv, NULL );
			ts->tv_sec = tv.tv_sec;
			ts->tv_nsec = (tv.tv_usec) * 1000;
			return ((uint16_t)0xFF)<<8 | (uint16_t)GET_REAL_TIME_PREC_MICRO_SECONDS;
		}
	}




	uint16_t getRealTime_microseconds_clock(struct timeval *tv, clockid_t clockid){
				#define TIME_MICRO_CALC tv->tv_sec=ts.tv_sec; \
					{ \
					div_t division; \
					division=div(ts.tv_nsec,1000); \
					tv->tv_usec=division.quot; \
					}

		struct timespec ts;
		if ( clock_gettime( clockid, &ts ) != -1 ){
			TIME_MICRO_CALC
			return (((uint16_t)clockid)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
		}else{
			#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
				#if defined(CLOCK_MONOTONIC_PRECISE)
				// BSD ==============================================================
					if ( clock_gettime( CLOCK_MONOTONIC_PRECISE, &ts ) != -1 ){
						TIME_MICRO_CALC
						return (((uint16_t)CLOCK_MONOTONIC_PRECISE)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
					}
				#elif defined(CLOCK_MONOTONIC_RAW)
				// Linux ==============================================================
					if ( clock_gettime( CLOCK_MONOTONIC_RAW, &ts ) != -1 ){
						TIME_MICRO_CALC
						return (((uint16_t)CLOCK_MONOTONIC_RAW)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
					}
				#elif defined(CLOCK_HIGHRES)
				// Solaris ==============================================================
					if ( clock_gettime( CLOCK_HIGHRES, &ts ) != -1 ){
						TIME_MICRO_CALC
						return (((uint16_t)CLOCK_HIGHRES)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
					}
				#elif defined(CLOCK_MONOTONIC)
				// AIX, BSD, Linux, POSIX, Solaris ==============================================================
					if ( clock_gettime( CLOCK_MONOTONIC, &ts ) != -1 ){
						TIME_MICRO_CALC
						return (((uint16_t)CLOCK_MONOTONIC)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
					}
				#elif defined(CLOCK_REALTIME)
				// AIX, BSD, HP-UX, Linux, POSIX ==============================================================
					if ( clock_gettime( CLOCK_REALTIME, &ts ) != -1 ){
						TIME_MICRO_CALC
						return (((uint16_t)CLOCK_REALTIME)<<8) | (uint16_t)GET_REAL_TIME_PREC_NANO_SECONDS;
					}
				#else
				// Unknown ==============================================================
					//Direct Fallthrough
				#endif // CLOCK_
			#endif // _POSIX_TIMERS

			gettimeofday( tv, NULL );
			return ((uint16_t)0xFF)<<8 | (uint16_t)GET_REAL_TIME_PREC_MICRO_SECONDS;;
		}

	#undef TIME_MICRO_CALC
	}




	double getRealTime_double_clock(clockid_t clockid){
		struct timespec ts;
		if ( clock_gettime( clockid, &ts ) != -1 ){
			return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
		}else{
			#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
				#if defined(CLOCK_MONOTONIC_PRECISE)
				// BSD ==============================================================
					if ( clock_gettime( CLOCK_MONOTONIC_PRECISE, &ts ) != -1 ){
						return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
					}
				#elif defined(CLOCK_MONOTONIC_RAW)
				// Linux ==============================================================
					if ( clock_gettime( CLOCK_MONOTONIC_RAW, &ts ) != -1 ){
						return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
					}
				#elif defined(CLOCK_HIGHRES)
				// Solaris ==============================================================
					if ( clock_gettime( CLOCK_HIGHRES, &ts ) != -1 ){
						return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
					}
				#elif defined(CLOCK_MONOTONIC)
				// AIX, BSD, Linux, POSIX, Solaris ==============================================================
					if ( clock_gettime( CLOCK_MONOTONIC, &ts ) != -1 ){
						return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
					}
				#elif defined(CLOCK_REALTIME)
				// AIX, BSD, HP-UX, Linux, POSIX ==============================================================
					if ( clock_gettime( CLOCK_REALTIME, &ts ) != -1 ){
						return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
					}
				#else
				// Unknown ==============================================================
					//Direct Fallthrough
				#endif // CLOCK_
			#endif // _POSIX_TIMERS

			//Fall through
			// The "Good old method". AIX, BSD, Cygwin, HP-UX, Linux, OSX, POSIX, Solaris.
			struct timeval tv;
			gettimeofday( &tv, NULL );
			return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
		}
	}







#else
	double getRealTime(){
		double returnval;
		return -1.0;		// Faaaaaiiil
	}

#endif








#undef NO_DENKR_ESSENTIALS_GETREALTIME_C_FUNCTIONS
