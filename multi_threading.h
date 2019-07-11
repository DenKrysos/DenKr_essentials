#ifndef DENKR_ESSENTIALS_MULTI_THREADING_H
#define DENKR_ESSENTIALS_MULTI_THREADING_H
/*
 * Authored by
 * Dennis Krummacker (03.06.14-25.07.2018)
 */

#include <global/global_settings.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#include "DenKr_essentials/PreC/DenKr_PreC.h"
#include "DenKr_essentials/Program_Files/P_Files_Path.h"
#include "DenKr_essentials/Plugins/DL_Libs.h"

#include "DenKr_essentials/Context_Broker/context_broker.h"
#include "DenKr_essentials/Context_Broker/context_broker_interface.h"


#include "DenKr_essentials/Types/multi_threading_basicTypes.h"












//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================
//----------------------------------------------------------------------------------------------------
//----  Inter-Thread Communication  ------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//====================================================================================================
////////////////////////////////
//////// Use UNIX (Local) Sockets between Threads
////////////////////////////////

//----------------------------------------------------------------------------------------------------
//====================================================================================================
////////////////////////////////
//////// Shared Memory (ShMem)
////////////////////////////////
//Usage: Declare an Array of this structs, with one for every "Data-Sink", i.e. for every Thread
// that gets Data. That Thread blocks at "sem_dest".
//A Data source, i.e. a Thread that wants to transmit Data to the destination sem_waits for sem_src.
//  Than fills in Data ShMem=malloc() -> sem_post(sem_dest)
//The receiving Thread reads out -> free(ShMem), ShMem=NULL -> sem_post(src)
// ------> You can use the according functions from the c-file
//
//You have to define in your Program (maybe an own multi_threading.h):
//    - msgtype,
//       -> Hereafter are provided some basic Types
//       -> Begin your Definitions after (excluding) 128
//           -> Lower Values are reserved for future implementations
//    - flags
//       -> Hereafter are provided some basic Types
//       -> Feel free ignore them and define/use your owns or define your ones for the unused
struct ShMemHeader {
	ShMemMsgSize size;
	ShMemMsgType type;
	ShMemMsgSrcThread src;
	ShMemMsgFlags flags;
	sem_t sem_dest;
	sem_t sem_src;
	char *ShMem;
};
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - -  Msg Types  - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define SHMEM_MSG_TYPE__UNDEFINED                    0
#define SHMEM_MSG_TYPE__EMPTY                        0
#define SHMEM_MSG_TYPE__NO_MSG                       0
#define SHMEM_MSG_TYPE__GENERIC                      INC(SHMEM_MSG_TYPE__UNDEFINED)
#define SHMEM_MSG_TYPE__DUMP                         INC(SHMEM_MSG_TYPE__GENERIC)
#define SHMEM_MSG_TYPE__READY                        INC(SHMEM_MSG_TYPE__DUMP)
#define SHMEM_MSG_TYPE__CANCEL_THREAD                INC(SHMEM_MSG_TYPE__READY)

#define SHMEM_MSG_TYPE__DEBUGGING_1                  DEC(SHMEM_MSG_TYPE__DEBUGGING_0)
#define SHMEM_MSG_TYPE__DEBUGGING_0                  DEC(SHMEM_MSG_TYPE__RESERVED_END)
// The Debugging is mainly for Development/Debugging Purpose. Shouldn't occur in 'final' Code (at least beyond object-code-level)
#define SHMEM_MSG_TYPE__RESERVED_END                 128
//// Begin additional Definitions after SHMEM_MSG_TYPE__RESERVED_END
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - -  Msg Flags  - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define SHMEM_MSG_FLAG__NEW_MSG                      0x00000001
#define SHMEM_MSG_FLAG__SRC_VALID                    0x00000002 //Used when the ID of the src-Thread of a message matters and is set. (E.g. inside the Initialization-Ready-Procedure)
//#define SHMEM_MSG_FLAG__                      0x00000004
//#define SHMEM_MSG_FLAG__                      0x00000008
//#define SHMEM_MSG_FLAG__                      0x00000010
//#define SHMEM_MSG_FLAG__                      0x00000020
//#define SHMEM_MSG_FLAG__                      0x00000040
//#define SHMEM_MSG_FLAG__                      0x00000080
//#define SHMEM_MSG_FLAG__                      0x00000100
//#define SHMEM_MSG_FLAG__                      0x00000200
//#define SHMEM_MSG_FLAG__                      0x00000400
//#define SHMEM_MSG_FLAG__                      0x00000800
//#define SHMEM_MSG_FLAG__                      0x00001000
//#define SHMEM_MSG_FLAG__                      0x00002000
//#define SHMEM_MSG_FLAG__                      0x00004000
//#define SHMEM_MSG_FLAG__                      0x00008000
//#define SHMEM_MSG_FLAG__                      0x00010000
//#define SHMEM_MSG_FLAG__                      0x00020000
//#define SHMEM_MSG_FLAG__                      0x00040000
//#define SHMEM_MSG_FLAG__                      0x00080000
//#define SHMEM_MSG_FLAG__                      0x00100000
//#define SHMEM_MSG_FLAG__                      0x00200000
//#define SHMEM_MSG_FLAG__                      0x00400000
//#define SHMEM_MSG_FLAG__                      0x00800000
//#define SHMEM_MSG_FLAG__                      0x01000000
//#define SHMEM_MSG_FLAG__                      0x02000000
//#define SHMEM_MSG_FLAG__                      0x04000000
//#define SHMEM_MSG_FLAG__                      0x08000000
//#define SHMEM_MSG_FLAG__                      0x10000000
//#define SHMEM_MSG_FLAG__                      0x20000000
//#define SHMEM_MSG_FLAG__                      0x40000000
//#define SHMEM_MSG_FLAG__                      0x80000000
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////











//TODO: For the Generic Linked List
//   Some Method to determine which Thread-IDs after the reserved ones for the Basic-Threads are currently in use
//     and vice versa, which ones are free. Consider the circumstance, that Threads could spawn and terminate and
//     a Fragmentation of the Number-Space can occur, i.e. number below the currently used 'Highest Value' are getting
//     free, before or without the Highest Value in use is getting free.
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Thread Management  -------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
////////////////////////////////
//////// Thread Manager
////////////////////////////////
//TODO: I have to write a new Macro / Code-Sequence for spawning Generic-Threads
//     This has to handle the different Managing-Data-Structure otherwise, than the
//     Basic-Thread-One.
typedef uint8_t DenKr_ThreadSpawned; //Use this as a 'ExistenceFlag' for a Thread (You could also group several / up-to-8 Threads into one Variable).
										//Use it to keep Track, if a Thread was (successfully) spawned and is still running.
										//Usage-Suggestion:
										//Define Indices for your 'Base-Threads. Allocate an Array of 'DenKr_ThreadSpawned'. Set the indexed Values for spawned Thread.
										//For 'Generic Threads', if you have to keep Track of them use the following structure and related functions.
typedef struct DenKr_Threads_GenericEntry_t DenKr_Threads_GenericEntry;
struct DenKr_Threads_GenericEntry_t{
	pthread_t pt_Object;
	DenKr_essentials_ThreadID ID;
	DenKr_ThreadSpawned spawned;// We could load a Plugin-Thread, which will be prepared, but not yet started. Or a Thread could start and terminate temporal.
	DenKr_Threads_GenericEntry* next;
};
typedef struct DenKr_Threads_Generic_t{
	unsigned int count;
	DenKr_essentials_ThreadID generic_startID;
	DenKr_Threads_GenericEntry* first;
}DenKr_Threads_Generic;
		//Usage of the Generic-structs:
			// Create a 'DenKr_ThreadSpawned_Generic*' (Pointer) -> Use the Init-Function on it.
			// To add or remove a Thread-Entries from the LinkedList use the functions.
			// To read the whole LL, just traverse it.
			// To get an Entry from the LL with a specific Index, use the getEntry-Function.
			// After all, call the Free-Function on the 'DenKr_ThreadSpawned_Generic*'.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - -   The actual Manager    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef struct ThreadManager_t{
	unsigned int count;//Number of Basic Threads -> Sizeof the two following Arrays.
	pthread_t* allThreads;//An Array. For Basic, Predefined, known from the outset Threads. Holds the pthread_t Objects
	DenKr_ThreadSpawned* runningThreads;//An Array. For Basic, Predefined, known from the outset Threads.
										//Indexed Entry is '1' (or, better said, not '0'), if Thread is running, i.e. Thread was (successfully) spawned.
										//Ensure to set the according Entry to '1', when spawning a Thread.
										//This is for "Base" or "Predefined" Threads. For Generic Threads or Threads, whose Presence/Number is not known beforehand, use the Linked-List.
	DenKr_Threads_Generic* runningThreads_generic;
}ThreadManager;
	// Usage:
	//   - Declare a Pointer of the ThreadManager and pass its Address to the init-Function.
	//   - Use the "DenKr_ThreadSpawn_Tracking_Generic_XX" Functions to handle the Generics.
	//   - Access the Basic-Arrays directly.


////////////////////////////////
//////// Initialization. A Synchronization Method, to get sure, that every desired Thread is Ready
////////    until the "Real-Work" begins.
////////////////////////////////
#define DenKr_Thread_Ready_Init(ShMemHeadersPtr, ThreadID_main, ThreadID_self) \
	DenKr_Thread_send_Ready_ShMem(ShMemHeadersPtr, ThreadID_main, ThreadID_self); \
	DenKr_Thread_await_AllReady_ShMem(ShMemHeadersPtr, ThreadID_main, ThreadID_self);
//
//
//
////////////////////////////////
//////// Thread Creation
////////    A Template / Supplement Macro for Creation of Threads
////////////////////////////////
#define DENKR_START_THREAD_PATTERN(RETURN_BOOL, THREAD_FUNC, THREAD_ID, JOINABLE_DETACHED, ARG_PASSING) \
		/*Use "struct <SomeStructure>* ThreadArgPass;" for Argument Passing.*/\
		/* Macro creates a 'return-Variable'. Usage-Proposal: Encapsulate Macro in Brackets and between Macro and Scope-Close check for it.*/\
		IF(EQUAL(RETURN_BOOL,true))(int CAT(return_macro_denkr_start_thread_,THREAD_ID);)\
		{ \
		ARG_PASSING \
		\
		pthread_attr_t tattr; \
		if((err=pthread_attr_init(&tattr)) < 0) { \
			perror("could not create thread-attribute"); \
			IF(EQUAL(RETURN_BOOL,true))(CAT(return_macro_denkr_start_thread_,THREAD_ID)=THREAD__ERR__CREATION__ATTR_INIT;)\
			goto CAT(DENKR_START_THREAD_MACRO_END_,THREAD_ID);\
		} \
		if((err=pthread_attr_setdetachstate(&tattr,JOINABLE_DETACHED)) < 0){ \
			perror("could not modify thread-attribute"); \
			if( (err=pthread_attr_destroy(&tattr)) != 0 ) { \
				perror("could not destroy thread-attribute"); \
				IF(EQUAL(RETURN_BOOL,true))(CAT(return_macro_denkr_start_thread_,THREAD_ID)=THREAD__ERR__CREATION__ATTR_DESTROY;)\
				goto CAT(DENKR_START_THREAD_MACRO_END_,THREAD_ID);\
			} \
			IF(EQUAL(RETURN_BOOL,true))(CAT(return_macro_denkr_start_thread_,THREAD_ID)=THREAD__ERR__CREATION__ATTR_MODIFY;)\
			goto CAT(DENKR_START_THREAD_MACRO_END_,THREAD_ID);\
		} \
		if( (err=pthread_create(&((thrall->allThreads)[THREAD_ID]), &tattr, THREAD_FUNC, (void*)ThreadArgPass)) < 0) { \
			perror("could not create thread"); \
			if( (err=pthread_attr_destroy(&tattr)) != 0 ) { \
				perror("could not destroy thread-attribute"); \
				IF(EQUAL(RETURN_BOOL,true))(CAT(return_macro_denkr_start_thread_,THREAD_ID)=THREAD__ERR__CREATION__ATTR_DESTROY;)\
				goto CAT(DENKR_START_THREAD_MACRO_END_,THREAD_ID);\
			} \
			IF(EQUAL(RETURN_BOOL,true))(CAT(return_macro_denkr_start_thread_,THREAD_ID)=THREAD__ERR__CREATION__CREATE;)\
			goto CAT(DENKR_START_THREAD_MACRO_END_,THREAD_ID);\
		}else{ \
			(thrall->runningThreads)[THREAD_ID]=1; \
		} \
		if( (err=pthread_attr_destroy(&tattr)) != 0 ) { \
			perror("could not destroy thread-attribute"); \
			IF(EQUAL(RETURN_BOOL,true))(CAT(return_macro_denkr_start_thread_,THREAD_ID)=THREAD__ERR__CREATION__ATTR_DESTROY;)\
			goto CAT(DENKR_START_THREAD_MACRO_END_,THREAD_ID);\
		} \
		CAT(DENKR_START_THREAD_MACRO_END_,THREAD_ID): \
		;\
	}
// Possibilites for "setdetachstate":
//   - PTHREAD_CREATE_JOINABLE
//   - PTHREAD_CREATE_DETACHED
//
//
//
//
//--------------------------------------------------------------------------------------------------//
////////////////////////////////
//////// Generic/Dynamic DLL-Threads
////////////////////////////////
//
// Generic DLL-Threads are always started with this:
struct thread_generic_module_start_ThreadArgPassing {
	ThreadManager* thrall;//The ThreadManager. Contains the two Arrays: pthread* allThreads: Mainly to start the listen thread inside. DenKr_ThreadSpawned* runningThreads: Passed to record the Listening-Thread as running;
	PluginManager* plugman;
	struct ShMemHeader *shmem_headers;//An Array, own ShMem-Header. Communication Alternative to the Context-Broker
	DenKr_essentials_ThreadID ownID;
	DenKr_essentials_ThreadID mainThreadID;
	void* ContextBrokerInterface;
	void* additional;//Can be used for individual stuff. To read it out: Just do it before my "__startPreamble" Macro (if used). TODO: Adjust my Plugin-Start-Thread routine to pass something to it.
	int additional_size;
};
//
//
#define DenKr_generic_module_thread__startPreamble_noPrint \
	ThreadManager* thrall = (((struct thread_generic_module_start_ThreadArgPassing *)arg)->thrall);\
	PluginManager* plugman = (((struct thread_generic_module_start_ThreadArgPassing *)arg)->plugman);\
	struct ShMemHeader *shmem_headers = (((struct thread_generic_module_start_ThreadArgPassing *)arg)->shmem_headers);\
	DenKr_essentials_ThreadID ownID = (((struct thread_generic_module_start_ThreadArgPassing *)arg)->ownID);\
	DenKr_essentials_ThreadID mainThreadID = (((struct thread_generic_module_start_ThreadArgPassing *)arg)->mainThreadID);\
	DenKr_InfBroker_Iface_Client* InfBrokerIface = (DenKr_InfBroker_Iface_Client*)(((struct thread_generic_module_start_ThreadArgPassing *)arg)->ContextBrokerInterface);\
	if(((struct thread_generic_module_start_ThreadArgPassing *)arg)->additional){\
		free(((struct thread_generic_module_start_ThreadArgPassing *)arg)->additional);\
	}\
	free(arg);
#define DenKr_generic_module_thread__startPreamble \
	DenKr_generic_module_thread__startPreamble_noPrint \
	printfc(DENKR__COLOR_ANSI__THREAD_BASIC,"Thread:");printf(" "STRINGIFY(C_PREF)" started.\n");
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

















//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  The Functions to be visible outside  -------------------------------------------------------//
//----     (external)  -----------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
#ifndef NO_DENKR_ESSENTIALS_MULTI_THREADING_C_FUNCTIONS
extern void ShMem_send_start(struct ShMemHeader *shmemh, ShMemMsgSize size, ShMemMsgType type);
extern void ShMem_send_finish(struct ShMemHeader *shmemh);
extern void ShMem_recv_start(struct ShMemHeader *shmemh);
extern void ShMem_recv_finish(struct ShMemHeader *shmemh);
extern void ShMem_Array_Sem_init(struct ShMemHeader *shmemh, int arraysize);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
extern void DenKr_Thread_send_Ready_ShMem(struct ShMemHeader *shmem_headers, DenKr_essentials_ThreadID mainID, DenKr_essentials_ThreadID selfID);
extern void DenKr_Thread_await_AllReady_ShMem(struct ShMemHeader *shmem_headers, DenKr_essentials_ThreadID mainID, DenKr_essentials_ThreadID selfID);
extern void DenKr_Threads_Main_Ready_Init(ThreadManager* thrall, struct ShMemHeader *shmem_headers, DenKr_essentials_ThreadID mainID);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// I recommend to not using the LinkedList Methods on to many entries, due to performance issues. You know, LinkedList Traversing...
extern int DenKr_ThreadSpawn_Tracking_Generic_Init(DenKr_Threads_Generic** threadsll);
extern int DenKr_ThreadSpawn_Tracking_Generic_AddEntry(DenKr_Threads_Generic* threadsll, DenKr_essentials_ThreadID idx);
extern int DenKr_ThreadSpawn_Tracking_Generic_RemoveEntry(DenKr_Threads_Generic* threadsll, DenKr_essentials_ThreadID idx);
extern int DenKr_ThreadSpawn_Tracking_Generic_free(DenKr_Threads_Generic** threadsll);
extern int DenKr_ThreadSpawn_Tracking_Generic_printAllEntries(DenKr_Threads_Generic* threadsll);
extern DenKr_Threads_GenericEntry* DenKr_ThreadSpawn_Tracking_Generic_GetEntry(DenKr_Threads_Generic* threadsll, DenKr_essentials_ThreadID idx);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
extern void DenKr_ThreadManager_init(ThreadManager** thrall,int basicThreads_c);
extern int DenKr_ThreadManager_free(ThreadManager** thrall);
extern int DenKr_ThreadManager_ExtractCompress_running_Threads(ThreadManager* thrall, DenKr_essentials_ThreadID** rthreads, int* rthreads_c);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
extern int DenKr_Thread_startThread_generic(ThreadManager* thrall, struct PluginRoleGeneric* generic_plugin, DenKr_essentials_ThreadID mainThreadID, PluginManager* plugman, struct ShMemHeader *shmem_headers, DenKr_InfBroker_SockToBrok* SockToBrok, void* additional_passed_arg, int addarg_siz);
extern int DenKr_Thread_start_generics(PluginManager* plugman, ThreadManager* thrall, DenKr_essentials_ThreadID mainThreadID, struct ShMemHeader *shmem_headers, DenKr_InfBroker_SockToBrok* SockToBrok);
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////







#endif /* DENKR_ESSENTIALS_MULTI_THREADING_H */
