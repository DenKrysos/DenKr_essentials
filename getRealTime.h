#ifndef DENKR_ESSENTIALS_GETREALTIME_H
#define DENKR_ESSENTIALS_GETREALTIME_H

/*
 * Authored by
 * Dennis Krummacker (25.06.15-)
 */


#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>







#ifndef NO_DENKR_ESSENTIALS_GETREALTIME_C_FUNCTIONS
#define getRealTime() getRealTime_double()
extern double getRealTime_double();
extern char getRealTime_nanoseconds(struct timespec *ts);
extern char getRealTime_microseconds(struct timeval *tv);
extern uint16_t getRealTime_nanoseconds_clock(struct timespec *ts, clockid_t clockid);
extern uint16_t getRealTime_microseconds_clock(struct timeval *tv, clockid_t clockid);
extern double getRealTime_double_clock(clockid_t clockid);
#endif








#endif /* DENKR_ESSENTIALS_GETREALTIME_H */
