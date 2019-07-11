#ifndef DENKR_ESSENTIALS_NETWORK_LINK_MONITORING_H
#define DENKR_ESSENTIALS_NETWORK_LINK_MONITORING_H
/*
 * Authored by
 * Dennis Krummacker (03.06.14-)
 */

#include <limits.h>//For maximum limits of Data-Types
#include <float.h>//Same for floats
#include "../auxiliary.h"
#include "global/global_settings.h"



/*
 * Some Functions like the Bandwidth-Measurement and Connection Continuity Check
 */


#define DEBUG_SERVER 0
#define DEBUG_CLIENT 1

#define PORTBWMEASURE 24289

#define RECVBUFFSIZEBWMEASURE 524288//0.5 MB (512k * 1024)
#define BWMEASURETIMEINTERVALL 1//In seconds
#define BWNUMAVERAGEINTERVALLS 10//Number of Intervalls to do a moving average over




#ifndef NO_DENKR_ESSENTIALS_NETWORK_LINK_MONITORING_C_FUNCTIONS
//int monitorbandwidth(char mode, char **dest);
//
//int monitorBandwidthAndContinuityCheck(char mode, char **dest);
//
//int continuityCheck(char mode, char **dest);


extern int handleLinkMonitoring(int argc, char **argstart);
#endif



#endif /* DENKR_ESSENTIALS_NETWORK_LINK_MONITORING_H */
