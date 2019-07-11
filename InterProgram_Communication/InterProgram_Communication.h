#ifndef DENKR_ESSENTIALS_INTERPROGRAM_COMMUNICATION_INTERPROGRAM_COMMUNICATION_H
#define DENKR_ESSENTIALS_INTERPROGRAM_COMMUNICATION_INTERPROGRAM_COMMUNICATION_H



//################################################################################################################################
//################################################################################################################################
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//				Inter-Program Communication
//________________________________________________________________________________________________________________________________
//################################################################################################################################
//################################################################################################################################
//################################################################################################################################



//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  The few Global Variables (if any)  ---------------------------------------------------------//
//----  And the Functions to be visible outside (extern)  ------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
#ifndef NO_DENKR_ESSENTIALS_INTERPROGRAM_COMMUNICATION_INTERPROGRAM_COMMUNICATION_C_FUNCTIONS
#include <stdarg.h>
#include <stdint.h>
#include "DenKr_essentials/InterProgram_Communication/communication_types.h"
extern uint64_t Send_Endian_Convert(uint64_t value);
extern int recvPyMsgContentString(int sock, char **msg, msgsizePy msgsiz);
extern int recvPyMsgContent(int sock, struct MsgPython **msg, msgsizePy msgsiz);
extern int recvPyMsg(int sock, struct MsgPython **msg);
extern int sendPyMsg(int sock, struct MsgPython *msg, int sendbytes);
extern int createPyMsg(int *msgsize, struct MsgPython **msg, msgtypePy msgtyp, ...);
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////










//################################################################################################################################
//================================================================================================================================
//		General Settings
//================================================================================================================================
//################################################################################################################################
/* --------------------------------------------------------------------- */
/* Use this as Network Byte-Order: I.e. e.g. for the msgsize.
 * Example: A msgsize of 12 (0x0C) would be sent as uint_16 like 0x00 0C, instead of 0x0C 00 */
#define ENDIANESS_SEND ENDIANESS_BIG
/* --------------------------------------------------------------------- */
//________________________________________________________________________________________________________________________________
//################################################################################################################################
//################################################################################################################################










//################################################################################################################################
//================================================================================================================================
//		Extern Functions
//================================================================================================================================
//################################################################################################################################

extern uint64_t Send_Endian_Convert(uint64_t value);

//________________________________________________________________________________________________________________________________
//################################################################################################################################
//################################################################################################################################













//################################################################################################################################
//================================================================================================================================
//		Python
//================================================================================================================================
//################################################################################################################################


#define MSG_TYPE_PY_C_MISC 0x0000
#define MSG_TYPE_PY_C_GOT_BLOCK 0x0001
#define MSG_TYPE_PY_C_WANT_BLOCK 0x0002
//---------------------------------------------------
#define MSG_TYPE_PY_C_DUMMY 0xFFFE
#define MSG_TYPE_PY_C_ERR 0xFFFF

//________________________________________________________________________________________________________________________________
//################################################################################################################################
//################################################################################################################################









#endif /* DENKR_ESSENTIALS_INTERPROGRAM_COMMUNICATION_INTERPROGRAM_COMMUNICATION_H */
