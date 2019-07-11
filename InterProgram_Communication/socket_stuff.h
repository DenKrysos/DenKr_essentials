#ifndef DENKR_ESSENTIALS_INTERPROGRAM_COMMUNICATION_SOCKET_STUFF_H
#define DENKR_ESSENTIALS_INTERPROGRAM_COMMUNICATION_SOCKET_STUFF_H



//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//--------  Preamble, Inclusions  --------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//====================================================================================================
// At first include this ----------------------------------------------------------
//---------------------------------------------------------------------------------
//#include "DenKrement_globalsettings.h"
// Then better start with this  ---------------------------------------------------
//---------------------------------------------------------------------------------
//#include "DenKrement.h"
//====================================================================================================
//====================================================================================================
//====================================================================================================
//Just to nicely keep order:  -----------------------------------------------------
//   First include the System / Third-Party Headers  ------------------------------
//   Format: Use <NAME> for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#include <sys/stat.h>
//#include <resolv.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
//====================================================================================================
//====================================================================================================
//====================================================================================================
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#include "../auxiliary.h"
#include "../DenKr_errno.h"
#include "communication_types.h"
#include "InterProgram_Communication.h"
//#include "nl80211.h"
//====================================================================================================
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================










#define SOCKET_C_PYTHON "\0DennKrement_SOCKET_Python_C"

/* Ensures that the locally handled msgsize and the sent over Network matches in Byte-Order
 * Please use after Reception of a msg and also before sending of one */
#define MSGSIZE_PY_ENDIAN(Type_msgsizePy) \
	{ \
	NET_ENDIAN_CONVERT_GENERAL(Type_msgsizePy,sizeof(msgsizePy)) \
	}



/* A general Macro to convert between the Endianess used for Network Transmissions
 * (maybe we communicate with a Platform of other Endianess).
 * It converts between local Endian and the designated one, i.e. every Time swaps the
 * passed Value, if the Endianesses doesn't match.
 * It also get's passed the Bitwidth of the passed Value as its Number of Bytes. */
#define NET_ENDIAN_CONVERT_GENERAL(Value,ByteWidth) \
	{ \
	if(system_endianess!=ENDIANESS_SEND){ \
		uint64_t temp; \
		temp = Send_Endian_Convert((uint64_t)(Value)); \
		memcpy(&(Value),((char *)&temp)+sizeof(uint64_t)-ByteWidth,ByteWidth); \
	} \
	}








#define UNIX_SOCKET_C_PYTHON_CLIENT_CONNECT \
	printfc(green,"-->"); \
	printf(" Setting up local Connection to Python-Part (DennTris)\n"); \
    int socket_Python; \
    { \
	socklen_t remote_Python_addrlen; \
    struct sockaddr_un remote_Python = {AF_UNIX, SOCKET_C_PYTHON}; \
    \
    if((socket_Python = socket(AF_UNIX,SOCK_STREAM,0)) == -1){ \
		ANSICOLORSET(ANSI_COLOR_GREEN); \
		fprintf(stderr,"DennTrisC-Error:"); \
		ANSICOLORRESET; \
		fprintf(stderr," unable to create socket\n"); \
        exit(1); \
    } \
	 \
	printfc(green,"--> "); \
    printf("Trying to connect...\n"); \
     \
    remote_Python_addrlen = sizeof(SOCKET_C_PYTHON)-1+sizeof(remote_Python.sun_family); \
	PythonDennTrisNotRunning: \
    if(connect(socket_Python,(struct sockaddr *)&remote_Python,remote_Python_addrlen) == -1){ \
		ANSICOLORSET(ANSI_COLOR_GREEN); \
		printf("--> ERROR:"); \
		ANSICOLORRESET; \
		printf(" Couldn't connect to Python-Program. | ERRNO: %d\n\tstrerror: %s\n",errno,strerror(errno)); \
		if(errno==ECONNREFUSED){ \
			printfc(yellow,"WARNING:"); \
			printf(" The local Connection to the Python-Program was refused. Is it running?\n"); \
			printf("\tI'll wait a bit and try again. So do your Part and start the Python-DennTris (or kill me -.-)\n"); \
			WAITNS(1,MS_TO_NS(500)); \
			goto PythonDennTrisNotRunning; \
		} \
		return NETWORK_ERR_NO_CONNECTION; \
    } \
	 \
	printfc(green,"-->"); \
    printf(" Connected to DennTris.\n"); \
    }












#endif /* DENKR_ESSENTIALS_INTERPROGRAM_COMMUNICATION_SOCKET_STUFF_H */
