/*
 * Context_Broker_Interface.h
 *
 * Authored by
 * Dennis Krummacker (20.07.2018 - 25.07.2018)
 */

#ifndef DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER_INTERFACE__H
#define DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER_INTERFACE__H


#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <stdarg.h>



//Using 'partly' the Comma-seperated Key-Value Pair (CSV) Functions:
// the sign '/' is used as an escape Sign. (Actually a '\' had been preferred, but, you know, using a backslash in C for such stuff would only obfuscate it. I mean you would have to escape the escape-character first for C, even before we consider my Format... We would end up with an uncountable amount of Backslashes xD )
//The Send function adds escape signs where necessary and the parse functions removes them.
//So be careful if either "pack the msg by yourself and the receiver uses the parse-method" or you "parse your recvd msg by yourself"
//e.g.
// If you want to use the '/' itself inside a Key or Value:
//  -> just escape itself, i.e.: You want to transmit a '/' (one single '/'), then write "//"
//There is nothing more to consider. If you pass the function a formatting sign like '=' or ',' the function takes care of them.
//YOU do just have to take care of the escape sign itself.

//Sending Messages using the "Key Value Pair CSV" format:
//  Empty Keys are NOT allowed
//  Empty Values (using strings) ARE allowed
//  Empty Values (using numeric) are already NOT POSSIBLE at all
//  -> you know, in the case of using strings/arrays you could pass an empty-string (just null-termination as content)
//        but for numerics you have to pass anything (the location in the series of tupels cannot be left out) and that is in fact interpreted as a number...





//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Some helpful Usage-Macros  -----------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
#define InfBrokMsgCSV(DenKr_InfBroker_msg_Point) ((DenKr_InfBroker_msg_CSV*)(DenKr_InfBroker_msg_Point->msg))
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
//----  Information Passing (from and to Broker)  --------------------------------------------------//
//----      Interface, Msg-Format...  --------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
typedef void* (*InfBrok_Func_Callback)(void*);//Prototype of the Callback-Function for Information-Registration.
//							Callback Functions have to free the passed msg inside. They get the msg passed via a point behind which space is malloced that isn't freed anywhere else.
//----------------------------------------------------------------------------------------------------
typedef struct DenKr_InfBroker_Iface_Client_t DenKr_InfBroker_Iface_Client;
typedef void* (*InfBrok_FuncSendStr)(DenKr_InfBroker_Iface_Client, uint8_t, uint8_t, char*, char*);//(the Iface itself "self", msg-type, msg-subtype, context (Str, Null-terminated, msg (Str, Null-terminated)
typedef void* (*InfBrok_FuncRegCallback)(DenKr_InfBroker_Iface_Client*, InfBrok_Func_Callback, ...);//(the Iface itself "self" (Pointer), the Callback-Func to register, A list of context-strings, NULL) Example: (InfBrokerIface,"test","cake","Feuer","jikan",NULL);
typedef void* (*InfBrok_FuncRegListenMethod)(DenKr_InfBroker_Iface_Client*, ...);//(the Iface itself "self" (Pointer), A list of context-strings, NULL) Example: (InfBrokerIface,"test","cake","Feuer","jikan",NULL);
//----------------------------------------------------------------------------------------------------
typedef struct DenKr_InfBroker_SocketToBrok_t{
	int sock;//Write to this to send a msg to the broker
	struct{//As a Developer, using the Broker and its Interface, just stay away from this.
		int sock_inside_broker;//The Broker reads from this socket
		sem_t mutex;//Used by the accessing functions to mutex the sock which is written to.
	}hidden;
}DenKr_InfBroker_SockToBrok;
//
//Context-Broker Interface struct enthält:
//  - Broker Thread-ID
// Listen Thread/Socket Registration:
//   - just call the 'InfBrok_FuncRegListenMethod func_regListen;' and pass it the Interface-Item itself, together with the wanted Contexts. The function takes care of everything and fills in the fields.
// Callback Registration:
//   - call the 'InfBrok_FuncRegCallback func_regCallback;' and pass it the Interface-Item itself and the desired callback-function, together with the wanted Contexts.
// Want to register both Methods?
//   - Just call them succeedingly
//  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
// Callbacks are stored by the Broker itself, individual per Context.
//  - So you can register different callback-function for different Contexts without any harm.
// If you want different sockets/Listen-Threads/whatever via the socket-method for differing Contexts you need to create several 'DenKr_InfBroker_Iface_Client' instances.
//    - Make sure you init the flags with '0' and copy the 'SockToBrok' & 'Funcs' over and then call the 'InfBrok_FuncRegListenMethod func_regListen;'
struct DenKr_InfBroker_Iface_Client_t{
	struct{
		InfBrok_FuncSendStr sendStr;
	}FuncSend;
	struct{
		InfBrok_FuncRegCallback regCallback;
		InfBrok_FuncRegListenMethod regSocket;
	}FuncRegProducer;
	struct{
		InfBrok_FuncRegCallback regCallback;
		InfBrok_FuncRegListenMethod regSocket;
	}FuncRegConsumer;
	struct{
		DenKr_InfBroker_SockToBrok* send_to_Broker;
		struct{
			int socket;
			int BrokerSock;//This one is used by the InfBroker
//			sem_t sock_sem;
		}recv_from_Broker;
		uint8_t flags;
		DenKr_essentials_ThreadID ownID;
	}hidden;
};

// Flags: DenKr_InfBroker_Iface_Client_t
#define DenKr_InfBroker_Iface_Client__FLAG__SOCK_FROM_BROKER_VALID       0x01
//#define DenKr_InfBroker_Iface_Client__FLAG__       0x02
//#define DenKr_InfBroker_Iface_Client__FLAG__       0x04
//#define DenKr_InfBroker_Iface_Client__FLAG__       0x08
//#define DenKr_InfBroker_Iface_Client__FLAG__       0x10
//#define DenKr_InfBroker_Iface_Client__FLAG__       0x20
//#define DenKr_InfBroker_Iface_Client__FLAG__       0x40
//#define DenKr_InfBroker_Iface_Client__FLAG__       0x80


typedef uint8_t DenKr_InfBroker_Msg_Header__type;
typedef uint8_t DenKr_InfBroker_Msg_Header__subtype;
typedef uint64_t DenKr_InfBroker_Msg_Header__msglen;
typedef uint8_t DenKr_InfBroker_Msg_Header__flags;
//TODO: Sometime, even the Bitwidth for the length dynamic
struct DenKr_InfBroker_Msg_Header{
	DenKr_InfBroker_Msg_Header__type type;
	DenKr_InfBroker_Msg_Header__subtype subtype;
	DenKr_essentials_ThreadID src;
	DenKr_InfBroker_Msg_Header__msglen len;
	DenKr_InfBroker_Msg_Header__flags flags;
};

// An Information Producer Registration might not be necessary in every use-case. This can be used for 'requesting' Information instead of 'sending-when-available-anyhow'.
//   Otherwise it can become in Handy for Debugging or some kind of back notification like: To the Consumers that currently is no Producer registered.
// In some operation it should suffice to only register Consumers and every time a Producer has Data it just sends to
//   the Broker and that dispenses them to the registered Consumers.
// But a 'Information-request' functionality will very probably be desired in many applications too.
//Msg-Types:
#define DenKr_InfBroker_Msg_Type__Generic                          0
#define DenKr_InfBroker_Msg_Type__Request                          INC(DenKr_InfBroker_Msg_Type__Generic)
#define DenKr_InfBroker_Msg_Type__Management                       INC(DenKr_InfBroker_Msg_Type__Request)
#define DenKr_InfBroker_Msg_Type__Raw                              INC(DenKr_InfBroker_Msg_Type__Management)
#define DenKr_InfBroker_Msg_Type__KeyEqualValue_CSV                INC(DenKr_InfBroker_Msg_Type__Raw)
//Msg-Subtypes:
#define DenKr_InfBroker_Msg_SubType__Management__General                      0
#define DenKr_InfBroker_Msg_SubType__Management__RegConsumerSocket            INC(DenKr_InfBroker_Msg_SubType__Management__General)
#define DenKr_InfBroker_Msg_SubType__Management__RegConsumerCallback          INC(DenKr_InfBroker_Msg_SubType__Management__RegConsumerSocket)
#define DenKr_InfBroker_Msg_SubType__Management__RegProducerSocket            INC(DenKr_InfBroker_Msg_SubType__Management__RegConsumerCallback)
#define DenKr_InfBroker_Msg_SubType__Management__RegProducerCallback          INC(DenKr_InfBroker_Msg_SubType__Management__RegProducerSocket)
#define DenKr_InfBroker_Msg_SubType__Management__RemoveConsumerSocket         INC(DenKr_InfBroker_Msg_SubType__Management__RegProducerCallback)
#define DenKr_InfBroker_Msg_SubType__Management__RemoveConsumerCallback       INC(DenKr_InfBroker_Msg_SubType__Management__RemoveConsumerSocket)
#define DenKr_InfBroker_Msg_SubType__Management__RemoveProducerSocket         INC(DenKr_InfBroker_Msg_SubType__Management__RemoveConsumerCallback)
#define DenKr_InfBroker_Msg_SubType__Management__RemoveProducerCallback       INC(DenKr_InfBroker_Msg_SubType__Management__RemoveProducerSocket)
//  -  - Subtype 'Management_Restricted': Only the 'Main-Application' is supposed to us them  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
#define DenKr_InfBroker_Msg_SubType__Management_Restricted                     INC(DenKr_InfBroker_Msg_SubType__Management__RemoveProducerCallback)
#define DenKr_InfBroker_Msg_SubType__Management_Restricted__Termination        INC(DenKr_InfBroker_Msg_SubType__Management_Restricted)
//  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
//  -  - CSV-Subtypes  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
#define DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__General                      0
#define DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int                          INC(DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__General)
#define DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str                          INC(DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int)
//
// DenKr_InfBroker_Msg_Header Flags
#define DenKr_InfBroker_Msg_FLAG__Request             0x01//Read: Send or Request Information. Flag is NOT Set: Msg sends Information (-> Dispense Info to Consumer). Flag IS Set: Msg requests Information (-> Dispense Request to Producer).
		//TODO: Future Extension. If a msg of specific Msg-Type and Request Flag is set, than the Consumer requests Information, formatted in the specific Msg-Type.
		// Has for sure also to be handled by the Broker, but is currently not.
//#define DenKr_InfBroker_Msg_FLAG__       0x02
//#define DenKr_InfBroker_Msg_FLAG__       0x04
//#define DenKr_InfBroker_Msg_FLAG__       0x08
#define DenKr_InfBroker_Msg_FLAG__SendDuplicate       0x10//By default a sender does not get his own sent message back. If this flag inside a msg is set, duplicates ARE sent back.
//#define DenKr_InfBroker_Msg_FLAG__       0x20
//#define DenKr_InfBroker_Msg_FLAG__       0x40
//#define DenKr_InfBroker_Msg_FLAG__       0x80
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
//----  Information Passing (from and to Broker)  --------------------------------------------------//
//----      Interface, Msg-Format...  --------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
typedef struct DenKr_InfBroker_msg_t{
	struct DenKr_InfBroker_Msg_Header* head;
	char* context;
	void* msg;
}DenKr_InfBroker_msg;
//////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct DenKr_InfBroker_msg_CSV_KeyVal_Str_t{
	char* key;
	char* val;
}DenKr_InfBroker_msg_CSV_KeyVal_Str;
typedef long long DenKr_InfBroker_msg_CSV_numeric;
typedef struct DenKr_InfBroker_msg_CSV_KeyVal_Int_t{
	char* key;
	DenKr_InfBroker_msg_CSV_numeric val;
}DenKr_InfBroker_msg_CSV_KeyVal_Int;
typedef struct DenKr_InfBroker_msg_CSV_t{
	int count;
	union{
		DenKr_InfBroker_msg_CSV_KeyVal_Int* numeric;
		DenKr_InfBroker_msg_CSV_KeyVal_Str* string;
	} pairs;
}DenKr_InfBroker_msg_CSV;
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
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
#ifndef NO__DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER_BROKER_INTERFACE__C__FUNCTIONS
int DenKr_ContextBroker_send_onlyHeader(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__type type, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags);
int DenKr_ContextBroker_send_noPayload(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__type type, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags, char* context);

//send (DenKr_InfBroker_Iface_Client, type, context_as-null-terminated-string, msg_as-null-terminated-string)
//  Sure, you could add some method to ensure that at least the context really is Null-terminated, but that would cost performance.
//  So just assume no malicious intrusion for now...
int DenKr_ContextBroker_sendInfo_Str(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__type type, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags, char* context, char* msg);

// Arguments:
//  The 'subtype' decides of which type the 'Values' are. This divides the variadic arguments after 'context' into two Alternatives:
//  The variadic arguments after 'context' are passed as a sequence of Pairs, succeeded by NULL
//  - subtype 'DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int': "Numeric Values"
//      Pair, Alternative 1: (string(/char*) key, long long value)
//  - subtype 'DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str': "Array-alike / Interpretation-dependend Values". Could be 'misused' for every Array-alike data-structure. As 'Key1=Value1' use something like 'Type=uint16_t' or 'sizeof=2', extend the sent array(s) with a Null-termination, accordingly interpret the recvd msg and your good to go...
//      Pair, Alternative 2: (string(/char*) key, string(/char*) value)
//     -> Example:
//          A1: DenKr_ContextBroker_register_Consumer_socket(InfBrokerIface,DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int,0,"Key1",12,"Key2",38,NULL);
//          A2: DenKr_ContextBroker_register_Consumer_socket(InfBrokerIface,DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str,0,"Key1","ValueString1","Key2","ValueString2",NULL);
//  You can only send Values of one Type at a time. If you want to send both, numeric and str/array send them separated in two succeeding Function-Calls
//
// Be extra careful with the passed arguments. It isn't save against "missing last value after key"
//TODO: Possible Future Extension: Mixed msg. (But keep in mind, such a solution would be much more inefficient.
int DenKr_ContextBroker_sendInfo_CSV(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags, char* context, ...);
int DenKr_ContextBroker_sendInfo_withSize(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__type type, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags, char* context, void* msg, int msgsize);
int DenKr_ContextBroker_send_noContext(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__type type, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags, void* msg, int msgsize);
int DenKr_ContextBroker_requestInfo(DenKr_InfBroker_Iface_Client* iface, char* context);

//register permanent Listener (target_socket, thread-id, number_of_contexts, contexts_as-pointer-to-argv)
//		Sends to Broker: msg-type,
//                       thread-id,
//                       socket_to_send_infos_to,
//                       (optional) number_of_contexts (makes processing easier),
//                       contexts as directly succeeding, null-terminated strings

//It checks, if the socket-variable inside the Interface-Object is already a valid one.
//  If: Just use this one and send it to the Broker
//  If not: Create new socketpair.
// Arguments:
//    Pass it a sequence of strings, succeeded by NULL
//     -> Example: DenKr_ContextBroker_register_Consumer_socket(InfBrokerIface,"test","Hurz","SDN","Schedule",NULL);
int DenKr_ContextBroker_register_Consumer_socket(DenKr_InfBroker_Iface_Client* iface, ...);
int DenKr_ContextBroker_register_Producer_socket(DenKr_InfBroker_Iface_Client* iface, ...);

//register Callback
//		Callback Functions have to free the passed msg inside. They get the msg passed via a point behind which space is malloced that isn't freed anywhere else.
//      -> Consider using "int DenKr_ContextBroker_parsemsg_callback(void* parse, DenKr_InfBroker_msg** msg)"
int DenKr_ContextBroker_register_Consumer_callback(DenKr_InfBroker_Iface_Client* iface, InfBrok_Func_Callback callback, ...);
int DenKr_ContextBroker_register_Producer_callback(DenKr_InfBroker_Iface_Client* iface, InfBrok_Func_Callback callback, ...);

//Hm, just if you like to know: The return value is, if positive, the length of the context string. Not that this is a really desirable Information... But hey, it's a byproduct.
//REMEMBER to use "int DenKr_ContextBroker_free_msg(DenKr_InfBroker_msg* msg)" after you are done with the message!
int DenKr_ContextBroker_recvmsg_socket(DenKr_InfBroker_Iface_Client* iface,DenKr_InfBroker_msg** msg);

//Just gets the message and fills in the 'DenKr_InfBroker_msg' struct. Extracts context, header and stuff. Just for a bit comfort.
// This frees the passed msg.
//REMEMBER to use "int DenKr_ContextBroker_free_msg(DenKr_InfBroker_msg* msg)" after you are done with the parsed message-struct created by this!
int DenKr_ContextBroker_parsemsg_callback(void* parse, DenKr_InfBroker_msg** msg);

//It replaces the original "msg-Pointer" inside the 'DenKr_InfBroker_msg' with a "DenKr_InfBroker_msg_CSV", i.e. frees the old content behind the pointer and creates the new one with the new format
//TO USE it: cast the 'void* msg' inside the 'DenKr_InfBroker_msg' to a 'DenKr_InfBroker_msg_CSV*' or use the macro
//     -> InfBrokMsgCSV(DenKr_InfBroker_msg_Point)
//REMEMBER to use "int DenKr_ContextBroker_free_msg(DenKr_InfBroker_msg* msg)" after you are done with the parsed message-struct created by this!
int DenKr_ContextBroker_parsemsg_CSV(DenKr_InfBroker_msg* msg);
void DenKr_ContextBroker_free_msg(DenKr_InfBroker_msg* msg);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//--------------------------------------------------------------------------------------------------//
//----  Data-Structure Grasp  ----------------------------------------------------------------------//
//----      Some Stuff, helpful to access Information inside Structures (like msgs)  ---------------//
//--------------------------------------------------------------------------------------------------//
//RECOGNIZE that the same key could occur multiple times!
//  -  -  -  -  -
//Return Values:
// 0  - Successful run. Number of found Key occurrences returned in "int* res"
// FUNC_ERR_BAD_ARG  - A "DenKr_essentials Error". Passed Pointer was no valid "DenKr_InfBroker_msg*"
int DenKr_ContextBroker_CSV_countKeyTimes(DenKr_InfBroker_msg* msg, char* search, int* res);
//Return Values:
// 0  - Successful run. Index returned in "int* resIndex"
// 1  - Key not found / Not that many Key occurrences present
// FUNC_ERR_BAD_ARG  - A "DenKr_essentials Error". Passed Pointer was no valid "DenKr_InfBroker_msg*"
int DenKr_ContextBroker_CSV_getNthIndex(DenKr_InfBroker_msg* msg, char* search, int nthIndex, int* resIndex);
//Return Values:
// 0  - Index not found (requested Index higher than number of elements)
// 1  - msgType & Result are of Type "Numeric". Returns Pointer to Value inside "void** res". As a User cast the past pointer afterwards to appropriate Type, according to function return Value.
// 2  - msgType & Result are of Type "String"
// FUNC_ERR_BAD_ARG  - A "DenKr_essentials Error". Passed Pointer was no valid "DenKr_InfBroker_msg*"
// Behind keyReturn, the Key of the requested Index is returned (In case you want to check it...)
int DenKr_ContextBroker_CSV_getValbyIndex(DenKr_InfBroker_msg* msg, int index, void** res, char** keyReturn);
//--------------------------------------------------------------------------------------------------//
//----  Debugging  ---------------------------------------------------------------------------------//
//----      Some Stuff, helpful at Debugging  ------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
int DenKr_ContextBroker_Debug_printmsg(DenKr_InfBroker_msg* msg);
int DenKr_ContextBroker_Debug_printmsg_CSV(DenKr_InfBroker_msg* msg);
#endif
//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////






#endif /* DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER_INTERFACE__H */
