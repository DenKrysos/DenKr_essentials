/*
 * context_broker.h
 *
 * Authored by
 * Dennis Krummacker (17.07.2018 - 25.07.2018)
 */

#ifndef DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER_THREAD__H
#define DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER_THREAD__H






//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Thread Spawning  ---------------------------------------------------------------------------//
//----      Macro to do so  ------------------------------------------------------------------------//
//----      Structure for Argument-Passing  --------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
struct DenKr_ContextBroker_ThreadArgPassing {
	ThreadManager* thrall;//The ThreadManager. Contains the two Arrays: pthread* allThreads: Mainly to start the listen thread inside. DenKr_ThreadSpawned* runningThreads: Passed to record the Listening-Thread as running;
	PluginManager* plugman;
	struct ShMemHeader *shmem_headers;//An Array, own ShMem-Header. Communication Alternative to the Context-Broker
	DenKr_InfBroker_SockToBrok* SockToBrok;
	DenKr_essentials_ThreadID ownID;
	DenKr_essentials_ThreadID mainThreadID;
};

#define DENKR_CONTEXTBROKER_START_THREAD \
	DenKr_InfBroker_SockToBrok SockToBrok;\
	{\
	DENKR_START_THREAD_PATTERN(false,\
								DenKr_ContextBroker_thread,\
								TO_DEFINE__DENKR_CONTEXTBROKER_THREAD_ID,\
								PTHREAD_CREATE_JOINABLE,\
									struct DenKr_ContextBroker_ThreadArgPassing *ThreadArgPass;\
									\
									ThreadArgPass = malloc(sizeof(*ThreadArgPass));\
									ThreadArgPass->thrall=thrall;\
									ThreadArgPass->plugman=plugman;\
									ThreadArgPass->shmem_headers=shmem_headers;\
									ThreadArgPass->SockToBrok=&SockToBrok;\
									ThreadArgPass->mainThreadID=TO_DEFINE__DENKR_MAIN_THREAD_ID;\
									ThreadArgPass->ownID=TO_DEFINE__DENKR_CONTEXTBROKER_THREAD_ID;\
							)\
	/*switch(return_macro_denkr_start_thread_0){}//Currently don't care about "Return" of the Macro*/\
	}
// Possibilites for "setdetachstate":
//   - PTHREAD_CREATE_JOINABLE
//   - PTHREAD_CREATE_DETACHED
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
//----  Functions to be visible outside  -----------------------------------------------------------//
//----      (external)  ----------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
#ifndef NO__DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER__C__FUNCTIONS
extern void* DenKr_ContextBroker_thread(void* arg);
#endif
//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////





#endif /* DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER_THREAD__H */
