/*
 * Authored by
 * Dennis Krummacker (03.06.14-25.07.2018)
 */

#define DENKR_ESSENTIALS_MULTI_THREADING_C
#define NO_DENKR_ESSENTIALS_MULTI_THREADING_C_FUNCTIONS


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
#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <limits.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#include "PreC/DenKr_PreC.h"
#include "DenKr_errno.h"
#include "auxiliary.h"
#include "DenKr_essentials/multi_threading.h"
//
#define DENKR_SORT_STATIC static
#define DENKR_SORT_NAME DenKr_essentials_ThreadID
#define DENKR_SORT_TYPE DenKr_essentials_ThreadID
#define DENKR_SORT_SELECTIVE
#define DENKR_SORT_HEAP
#include "DenKr_essentials/sort.h"
#undef DENKR_SORT_STATIC
#undef DENKR_SORT_NAME
#undef DENKR_SORT_TYPE
#undef DENKR_SORT_SELECTIVE
#undef DENKR_SORT_HEAP
//
#define DENKR_SEARCH_STATIC static
#define DENKR_SEARCH_NAME DenKr_essentials_ThreadID
#define DENKR_SEARCH_TYPE DenKr_essentials_ThreadID
#define DENKR_SEARCH_SELECTIVE
#define DENKR_SEARCH_BINARY
#include "DenKr_essentials/search.h"
#undef DENKR_SEARCH_STATIC
#undef DENKR_SEARCH_NAME
#undef DENKR_SEARCH_TYPE
#undef DENKR_SEARCH_SELECTIVE
#undef DENKR_SEARCH_BINARY
//
//#include "function_creator.h"
//#include "getRealTime.h"
//#include "Program_Files/P_Files_Path.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//











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
//After the function is totally indifferent which socket you use where. They both are totally functional equivalent.
//   In other words: It doesn't matter in which order you pass the to sockets, i.e. the two 'int', which you want to transform into sockets
//   and use further on.
										// Yar, screw this, i won't finish this -.- I wanted to temporary start a thread or handle a bit with non-blocking
										// to connect two sockets...
										// But i don't have to finish it. There already exists something like that...
										// Just use that and that's it...
										//     int socketpair(int domain, int type, int protocol, int sv[2]);
										//     Example:
										//  	int sockets_SDN_Ctrl_Com_InterThread[2];
										//  	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets_SDN_Ctrl_Com_InterThread) < 0) {
										//  		ANSICOLORSET(ANSI_COLOR_RED);
										//  		fprintf(stderr,"Error:");
										//  		ANSICOLORRESET;
										//  		fprintf(stderr, "unable to create stream socket pair.\n");
										//  		exit(1);
										//  	}
										//int create_local_socket_pair(int *unSockServ,int *unSockClient){//disregard the socket names, they are just choosen for naming, no deeper meaning, except the obvious technical justification from their usage at following implementation
										//	int err=0;
										//
										//	print_daytime();
										//	struct timespec timestamp;
										//	char tempBuf[64]; //Used as a intermediate helper. Since both Values of timespec 'shall' be long, they have 64 Bit. Accordingly their 'theoretically' maximum (unsigned) Value would be 18446744073709551615 -> 20 Digits. I set a Dot between. Plus the Null-terminater this Value shouldn't ever be reached, while the definition of timespec isn't changed. Notice, that we he talk about digits here, not Bits. While 42 Bytes (Digits) already should bring us on the save side: Who wants to use 42 Byte? Say, we take 64 Byte: Nice padding, reeeeeaaaally enough space and who cares about few more Bytes? After Operations are finished this space is freed anyways.
										//	GetRealTimeM(nano,&timestamp,CLOCK_REALTIME);
										//	depr(1,"%d.%d",timestamp.tv_sec,timestamp.tv_nsec);
										//	int sockTempListen;
										//	struct sockaddr_un servaddr = {AF_UNIX, 0}; /* AF_LOCAL would also do the job, since PF_UNIX is just the POSIX Name for PF_LOCAL... */
										//	depr(0-2,"port: %d",*((int *)(servaddr.sun_path)));
										//    if((sockTempListen = socket(AF_UNIX,SOCK_STREAM,0)) == -1){
										//		ANSICOLORSET(ANSI_COLOR_RED);
										//		fprintf(stderr,"Error:");
										//		ANSICOLORRESET;
										//		fprintf(stderr," unable to create listen-socket.\n");
										//        exit(1);
										//    }
										//	if (bind(sockTempListen, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_un)) == -1) {
										//		ANSICOLORSET(ANSI_COLOR_RED);
										//		fprintf(stderr,"Error:");
										//		ANSICOLORRESET;
										//		fprintf(stderr, "unable to bind listen-socket.\n");
										//		exit(1);
										//	}
										//	if (listen(sockTempListen, 1) == -1) {
										//		ANSICOLORSET(ANSI_COLOR_RED);
										//		fprintf(stderr,"Error:");
										//		ANSICOLORRESET;
										//		fprintf(stderr, "unable to listen on socket.\n");
										//		exit(1);
										//	}
										//	exit(1);
										//
										//	return err;
										//}

//----------------------------------------------------------------------------------------------------
//====================================================================================================
////////////////////////////////
//////// Shared Memory (ShMem)
////////////////////////////////
// Note: When talk about ThreadIDs here, i don't mean the IDs with which phtread handles
//   it's thread-instances. I mean own defined Numbers, used for nice own Handling while
//   developing the Application, such as Array-Positions, like in the ShMemHeader-Array.
// Usage: Example (half pseudo) code snippet
//   General Setup:
//     [#define IDs for your threads, inclusive a value like #define THREADS_QUANTITY_MAX XX]
//     [#define ShMemM Msg Types. E.g. #define SHMEM_MSGTYPE_NEW_CTRL_MSG 1]
//   Before Thread-spawning (in main for example):
//     struct ShMemHeader ShMemArray[threads_quantity];
//     [loop over the Array to sem_init the Semaphores.]
//         -> [To do so, use the function below, if you use an Array, like suggested]
//         -> []
//     [Pass the start-address of the array to the spawning threads]
//   Data-Source-Thread:
//     [Prepare your message. E.g. write into a buffer or ready your variables]
//     ShMem_send_start(&ShMemArray[TargetThreadID], 24, SHMEM_MSGTYPE_NEW_CTRL_MSG)
//     [Fill in Flags (if any)]
//     [Write - i.e. memcpy, snprintf, Variable-pointer-based-write or whatever - into the space after "ShMemArray[TargetThreadID]->ShMem"]
//     ShMem_send_finish(&(ShMemArray[TargetThreadID]));
//   Data-Sink-Thread (Target) (TargetThreadID is its own ID):
//     ShMem_recv_start(&(ShMemArray[TargetThreadID]));
//     [Read out the Message from the Pointer "ShMemArray[TargetThreadID]->ShMem"]
//     ShMem_recv_finish(&ShMemArray[TargetThreadID]);
//     [Do the Operations you have to do after the Message (if any)]
//     [Then should most probably come a jump, loop or whatever back up to the sem_wait]
//

void ShMem_send_start(struct ShMemHeader *shmemh, ShMemMsgSize size, ShMemMsgType type){
	sem_wait(&(shmemh->sem_src));
//	printfc(blue,"send_start: ");printf("\n");
	shmemh->size=size;
	shmemh->type=type;
	if(size>0)
		shmemh->ShMem=malloc(size);
//	printf("AFter-Start: Ptr: 0x%lX\n",(intptr_t)(shmemh->ShMem));
}
void ShMem_send_finish(struct ShMemHeader *shmemh){
//	printfc(blue,"Debug-Send-finish:");printf(" Type: %d, Src: %d\n",shmemh->type, shmemh->src);
    sem_post(&(shmemh->sem_dest));
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ShMem_recv_start(struct ShMemHeader *shmemh){
    sem_wait(&(shmemh->sem_dest));
}
void ShMem_recv_finish(struct ShMemHeader *shmemh){
//	printfc(blue,"recv_finish: ");printf(" Before-Check: Ptr: 0x%lX\n",(intptr_t)(shmemh->ShMem));
	if((shmemh->ShMem) != NULL){
		free(shmemh->ShMem);
		shmemh->ShMem=NULL;
	}
	shmemh->size=0;
	shmemh->type=0;
	shmemh->flags=0;
	shmemh->src=0;
//	memset(shmemh,0,sizeof(struct ShMemHeader));
//	printf("Ptr after recv_finish: 0x%lX\n",(intptr_t)(shmemh->ShMem));
	sem_post(&(shmemh->sem_src));
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ShMem_Array_Sem_init(struct ShMemHeader *shmemh, int arraysize){
//	printf("sizeof struct: %lu, size: %lu, type: %lu, char *: %lu, sem_t: %lu\n",sizeof(struct ShMemHeader), sizeof(ShMemMsgSize), sizeof(ShMemMsgType), sizeof(char *), sizeof(sem_t));
	memset(shmemh,0,arraysize*sizeof(struct ShMemHeader));
	for(arraysize--;arraysize>=0;arraysize--){
		sem_init(&(shmemh[arraysize].sem_dest),0,0);
		sem_init(&(shmemh[arraysize].sem_src),0,1);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////










//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Thread Management  -------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
////////////////////////////////
//////// Initialization. A Synchronization Method, to get sure, that every desired Thread is Ready
////////    until the "Real-Work" begins.
////////////////////////////////
// Look for the
//#define DenKr_Thread_Ready_Init(ShMemHeaderPtr_main, ShMemHeaderPtr_self, ThreadID_main)
//     Inside the multi_threading.h

void DenKr_Thread_send_Ready_ShMem(struct ShMemHeader *shmem_headers, DenKr_essentials_ThreadID mainID, DenKr_essentials_ThreadID selfID){
	ShMem_send_start(&(shmem_headers[mainID]),0,SHMEM_MSG_TYPE__READY);
	FLAG_SET(shmem_headers[mainID].flags,SHMEM_MSG_FLAG__SRC_VALID);
	shmem_headers[mainID].src = selfID;
	ShMem_send_finish(&(shmem_headers[mainID]));
}

void DenKr_Thread_await_AllReady_ShMem(struct ShMemHeader *shmem_headers, DenKr_essentials_ThreadID mainID, DenKr_essentials_ThreadID selfID){
#define shmem_recv_start_self ShMem_recv_start(&shmem_self)
#define shmem_recv_finish_self ShMem_recv_finish(&shmem_self)
#define shmem_self (shmem_headers[selfID])

	shmem_recv_start_self;
	switch(shmem_self.type){
	case SHMEM_MSG_TYPE__READY:
		if(shmem_self.src != mainID){
			printfc(red,"Bug:");printf(" Received a Ready-Msg from someone else but Main, where a \"Everyone-is-ready\" from Main was awaited: sdn_ctrl_com_thread_RYU.\n");
			shmem_recv_finish_self;
			exit(MAIN_ERR_BUG);
		}else{
			shmem_recv_finish_self;
		}
		break;
	default:
		shmem_recv_finish_self;
		//This shouldn't occur. Until after this "Ready-Procedure" not any other ShMem-Msg should be sent.
		//So this switch is just for safety. And while we do this procedure just one time, at Program-Start
		//we can spent this bit Time without getting any guilty conscience
		printfc(red,"Bug:");printf(" Received a different ShMem-Msg Type from \"Ready\" at the Initialization-of sdn_ctrl_com_thread_RYU.\n");
		exit(MAIN_ERR_BUG);
		break;
	}

#undef shmem_recv_start_self
#undef shmem_recv_finish_self
#undef shmem_self
}

//free(*rthreads) manually after this
int DenKr_ThreadManager_ExtractCompress_running_Threads(ThreadManager* thrall, DenKr_essentials_ThreadID** rthreads, int* rthreads_c){
	int i,j;
	int running_basics=0;

	for(i=0;i<thrall->count;i++){
		if( (thrall->runningThreads)[i] )
			running_basics++;
	}
	(*rthreads_c)=running_basics+(thrall->runningThreads_generic)->count;
	*rthreads=malloc((*rthreads_c)*sizeof(**rthreads));

	DenKr_essentials_ThreadID last_thr=0;
	for(i=0;i<running_basics;i++){
		for(j=last_thr;j<thrall->count;j++){
			if( (thrall->runningThreads)[j] ){
				(*rthreads)[i]=j;
				last_thr=j+1;
				break;
			}
		}
	}
	if((thrall->runningThreads_generic)->count){
		DenKr_Threads_GenericEntry* curentr=(thrall->runningThreads_generic)->first;
		for(;i<(*rthreads_c);i++){
			if(curentr->spawned){
				(*rthreads)[i]=curentr->ID;
				curentr=curentr->next;
			}
		}
	}

	return 0;
}


void DenKr_Threads_Main_Ready_Init(ThreadManager* thrall, struct ShMemHeader *shmem_headers, DenKr_essentials_ThreadID mainID){
#define shmem_self (shmem_headers[mainID])
	//Sorting-Algorithm Choice:
	//  We don't care about Stability here
	//  Memory Consumption is not important
	//  Memory Accesses should be few. In other Words: Better more Comparisons, but fewer Memory Moves.
	// -> Heap Sort
	//     Quicksort could also be a reasonable Choice here, since we can assume, that the Sorting-Data will be very nearly sorted

	int i;
	int threadc;
	int not_yet_ready;
	DenKr_essentials_ThreadID* thrIDs;
	//Attend that multiple Entries with the same DenKr_Thread_ID in the generic LinkedList will lead to a Deadlock
	//Thus i wanted to get to the save side and spend a bit Time checking for them and eventually exclude them.
	DenKr_ThreadManager_ExtractCompress_running_Threads(thrall,&thrIDs,&threadc);
	//Sort
	DenKr_essentials_ThreadID_heap_sort(thrIDs,threadc);
	//Exclude Duplications (Works only, when sorted)
	{
		int doubles=0;
		DenKr_essentials_ThreadID* thrIDs_temp;
		thrIDs_temp=thrIDs;
		for(i=1;i<threadc;i++){
			if(thrIDs_temp[i] == thrIDs_temp[i-1]){
				doubles++;
			}
		}
		if(doubles && (0<threadc)){
			threadc-=doubles;
			thrIDs=malloc(threadc*sizeof(*thrIDs));
			thrIDs[0]=thrIDs_temp[0];
			for(i=1;i<threadc;i++){
				if(thrIDs_temp[i]!=thrIDs_temp[i-1])
					thrIDs[i]=thrIDs_temp[i];
			}
		}
	}

	//Now we just have !automated! and !generic! (safely) prepared, what we need: What Threads have been started (Basic Ones and Generics) and excluded duplicated IDs.
	//  We can start the "real" Work, what we really want to do here.
	//The actual Ready-Init-Routine
	not_yet_ready=threadc;
	char already_ready[not_yet_ready];
	memset(already_ready,0,not_yet_ready);

	while(not_yet_ready){
		unsigned int curIdx;
		ShMem_recv_start(&shmem_self);
		switch(shmem_self.type){
		case SHMEM_MSG_TYPE__READY:
			if(FLAG_CHECK(shmem_self.flags,SHMEM_MSG_FLAG__SRC_VALID)){
				if(DenKr_essentials_ThreadID_BinarySearch(thrIDs,threadc,shmem_self.src,&curIdx)){
					if(!(already_ready[curIdx])){
						already_ready[curIdx]=1;
						not_yet_ready--;
					}
				}else{
					//Shouldn't ever occur
					printfc(red,"Bug:");printf(" Data-Error during Initialization-Ready-Routine: Ready-Msg received with src, which isn't inside these, that wait to get Ready.\n");
					exit(MAIN_ERR_BUG);
				}
			}else{
				printfc(red,"Bug:");printf(" Received ShMem-Msg with invalid src (Flag unset) at the Initialization-Ready-Routine.\n");
				exit(MAIN_ERR_BUG);
			}
			break;
		default:
			//This shouldn't occur. Until after this "Ready-Procedure" shouldn't any other ShMem-Msg be sent.
			//So this switch is just for safety. And while we do this procedure just one time, at Program-Start
			//we can spent this bit Time without getting any guilty conscience
			printfc(red,"Bug:");printf(" Received a different ShMem-Msg Type from \"Ready\" at the Initialization-Ready-Routine.\n");
			exit(MAIN_ERR_BUG);
			break;
		}
		ShMem_recv_finish(&shmem_self);
	}
	for(i=0;i<threadc;i++){
		ShMem_send_start(&(shmem_headers[thrIDs[i]]),0,SHMEM_MSG_TYPE__READY);
		FLAG_SET(shmem_headers[thrIDs[i]].flags,SHMEM_MSG_FLAG__SRC_VALID);
		shmem_headers[thrIDs[i]].src = mainID;
		ShMem_send_finish(&(shmem_headers[thrIDs[i]]));
	}
#undef shmem_self
}

					//void DenKr_Threads_Main_Ready_Init_Basic_Backup(DenKr_essentials_ThreadID threadc, struct ShMemHeader *shmem_headers, DenKr_essentials_ThreadID mainID){
					//#define shmem_self (shmem_headers[mainID])
					//	int not_yet_ready=threadc;
					//	char already_ready[threadc];
					//	memset(already_ready,0,sizeof(already_ready));
					//	while(not_yet_ready){
					//		ShMem_recv_start(&shmem_self);
					//		switch(shmem_self.type){
					//		case SHMEM_MSG_TYPE__READY:
					//			if(!(already_ready[shmem_self.src])){
					//				already_ready[shmem_self.src]=1;
					//				not_yet_ready--;
					//			}
					//			break;
					//		default:
					//			//This shouldn't occur. Until after this "Ready-Procedure" shouldn't any other ShMem-Msg be sent.
					//			//So this switch is just for safety. And while we do this procedure just one time, at Program-Start
					//			//we can spent this bit Time without getting any guilty conscience
					//			printfc(red,"Bug:");printf(" Received a different ShMem-Msg Type from \"Ready\" at the Initialization-Ready-Routine.\n");
					//			exit(MAIN_ERR_BUG);
					//			break;
					//		}
					//		ShMem_recv_finish(&shmem_self);
					//	}
					//	int i;
					//	for(i=0;i<threadc;i++){
					//		ShMem_send_start(&(shmem_headers[i]),0,SHMEM_MSG_TYPE__READY);
					//		FLAG_SET(shmem_headers[i].flags,SHMEM_MSG_FLAG__SRC_VALID);
					//		shmem_headers[i].src = mainID;
					//		ShMem_send_finish(&(shmem_headers[i]));
					//	}
					//#undef shmem_self
					//}


//--------------------------------------------------------------------------------------------------//
////////////////////////////////
//////// Thread Spawning, Tracking, Existence, Still-running
////////////////////////////////
int DenKr_ThreadSpawn_Tracking_Generic_Init(DenKr_Threads_Generic** threadsll, DenKr_essentials_ThreadID startID){
	*threadsll=malloc(sizeof(*threadsll));
	memset(*threadsll,0,sizeof(**threadsll));
	(*threadsll)->generic_startID=startID;
	return 0;
}


DenKr_Threads_GenericEntry* DenKr_ThreadSpawn_Tracking_Generic_AddEntry(DenKr_Threads_Generic* threadsll, DenKr_essentials_ThreadID idx){
	int i;
	DenKr_Threads_GenericEntry* tempp;

	if(!(threadsll->count)){
		threadsll->first=malloc(sizeof(*(threadsll->first)));
		tempp=threadsll->first;
	}else{
		tempp=threadsll->first;
		for(i=1;i<threadsll->count;i++){
			tempp=tempp->next;
		}
		tempp->next=malloc(sizeof(*tempp));
		tempp=tempp->next;
	}

	threadsll->count++;
	tempp->ID=idx;
	tempp->spawned=1;
	tempp->next=NULL;

	return tempp;
}


//This function removes an Entry from the LinkedList, if one with the passed Index exists.
// If there is no Entry with this Index it just does nothing, except wasting CPU-Time while traversing the list xD.
// To save CPU-Time the function only removes the FIRST FOUND ENTRY and then returns. Don't add several Entries with the same Idx.
int DenKr_ThreadSpawn_Tracking_Generic_RemoveEntry(DenKr_Threads_Generic* threadsll, DenKr_essentials_ThreadID idx){
	int i;

	if(!(threadsll)){
		return 0;
	}else{
		if(!(threadsll->count)){
			return 0;
		}else{
			DenKr_Threads_GenericEntry** tempp_prev=&(threadsll->first);
			DenKr_Threads_GenericEntry* tempp=threadsll->first;
			for(i=0;i<threadsll->count;i++){
				if( (tempp->ID) == idx ){
					tempp=tempp->next;
					free(*tempp_prev);
					*tempp_prev=tempp;
					threadsll->count--;
					return 0;
				}
				tempp_prev=&((*tempp_prev)->next);
				tempp=tempp->next;
			}
		}
	}

	return 0;
}


DenKr_Threads_GenericEntry* DenKr_ThreadSpawn_Tracking_Generic_GetEntry(DenKr_Threads_Generic* threadsll, DenKr_essentials_ThreadID idx){
	int i;

	if(!(threadsll)){
		return NULL;
	}else{
		if(!(threadsll->count)){
			return NULL;
		}else{
			DenKr_Threads_GenericEntry** tempp_prev=&(threadsll->first);
			DenKr_Threads_GenericEntry* tempp=threadsll->first;
			for(i=0;i<threadsll->count;i++){
				if( (tempp->ID) == idx ){
					return *tempp_prev;
				}
				tempp_prev=&((*tempp_prev)->next);
				tempp=tempp->next;
			}
		}
	}

	return 0;
}


int DenKr_ThreadSpawn_Tracking_Generic_free(DenKr_Threads_Generic** threadsll){
	int i;
	if(!(*threadsll)){
		return FUNC_ERR_BAD_ARG;
	}else{
		DenKr_Threads_GenericEntry* tempp=(*threadsll)->first;
		DenKr_Threads_GenericEntry* tempp_n=NULL;
		for(i=0;i<((*threadsll)->count);i++){
			tempp_n=tempp->next;
			if(tempp){
				free(tempp);
			}else{
				//LinkedList is broken
				return STRUCT_ERR_DMG;
			}
			tempp=tempp_n;
		}

		free(*threadsll);
		*threadsll=NULL;
	}
	return 0;
}


//See this for Debugging-Purpose.
int DenKr_ThreadSpawn_Tracking_Generic_printAllEntries(DenKr_Threads_Generic* threadsll){
	int i;

	if(!(threadsll)){
		return 0;
	}else{
		printf("Number of Linked-List Entries: %d",threadsll->count);
		if(!(threadsll->count)){
			printf(".\n");
			return 0;
		}else{
			printf(":\n");
			DenKr_Threads_GenericEntry* tempp=threadsll->first;
			for(i=0;i<threadsll->count;i++){
				printf("Entry #%d: %d\n",i,tempp->ID);
				tempp=tempp->next;
			}
		}
	}
	return 0;
}

//--------------------------------------------------------------------------------------------------//
////////////////////////////////
//////// Thread Manager
////////////////////////////////
void DenKr_ThreadManager_init(ThreadManager** thrall,int basicThreads_c){
	*thrall=malloc(sizeof(**thrall));
	(*thrall)->count=basicThreads_c;
	(*thrall)->allThreads=malloc(basicThreads_c*sizeof(*((*thrall)->allThreads)));
	(*thrall)->runningThreads=malloc(basicThreads_c*sizeof(*((*thrall)->runningThreads)));
//	memset(&(thrall->runningThreads_generic),0,sizeof(thrall->runningThreads_generic));
	DenKr_ThreadSpawn_Tracking_Generic_Init(&((*thrall)->runningThreads_generic),basicThreads_c+1);
	memset((*thrall)->allThreads,0,basicThreads_c*sizeof(*((*thrall)->allThreads)));
	memset((*thrall)->runningThreads,0,basicThreads_c*sizeof(*((*thrall)->runningThreads)));
}


int DenKr_ThreadManager_free(ThreadManager** thrall){
	DenKr_ThreadSpawn_Tracking_Generic_free(&((*thrall)->runningThreads_generic));
	if((*thrall)->allThreads)
		free((*thrall)->allThreads);
	if((*thrall)->runningThreads)
		free((*thrall)->runningThreads);
	*thrall=NULL;
	return 0;
}
//--------------------------------------------------------------------------------------------------//
////////////////////////////////
//////// Generic/Dynamic DLL-Threads
////////////////////////////////
int DenKr_Thread_startThread_generic(ThreadManager* thrall, struct PluginRoleGeneric* generic_plugin, DenKr_essentials_ThreadID mainThreadID, PluginManager* plugman, struct ShMemHeader *shmem_headers, DenKr_InfBroker_SockToBrok* SockToBrok, void* additional_passed_arg, int addarg_siz){
	int i,err;
	int new_thID;
	DenKr_Threads_GenericEntry* newEnt;
	if(!((thrall->runningThreads_generic)->count)){
		(thrall->runningThreads_generic)->first=malloc(sizeof(DenKr_Threads_GenericEntry));
		newEnt = (thrall->runningThreads_generic)->first;
		new_thID=(thrall->runningThreads_generic)->generic_startID;
	}else{
		newEnt=(thrall->runningThreads_generic)->first;
		for(i=1;i<(thrall->runningThreads_generic)->count;i++){
			newEnt=newEnt->next;
		}
		newEnt->next=malloc(sizeof(*newEnt));
		newEnt=newEnt->next;
		new_thID=((thrall->runningThreads_generic)->generic_startID)+((thrall->runningThreads_generic)->count);
	}
	((thrall->runningThreads_generic)->count)++;
	memset(newEnt,0,sizeof(*newEnt));
	newEnt->ID=new_thID;
	generic_plugin->ThreadID=new_thID;
	if(generic_plugin->work_type != DenKr_plugin_working_type__thread){
//		CREATE_argv_CONST(print_roles, CALL_MACRO_X_FOR_EACH__LIST(STRINGIFY,DenKr_plugin_roles_ENTRIES) )
//		printfc(yellow,"WARNING:");printf(" Loaded Module for Role \""TODO"\" is not of Working-Type \"Thread\" (%d), but of \"%s\" (%d).\n",DenKr_plugin_role__SDN_link_monitoring,print_roles[((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).work_type],((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).work_type);
	}else{
		struct thread_generic_module_start_ThreadArgPassing *ThreadArgPass;
		ThreadArgPass = malloc(sizeof(*ThreadArgPass));
		memset(ThreadArgPass,0,sizeof(*ThreadArgPass));
		ThreadArgPass->mainThreadID=mainThreadID;
		ThreadArgPass->ownID=new_thID;
		ThreadArgPass->plugman=plugman;
		ThreadArgPass->shmem_headers=shmem_headers;
		ThreadArgPass->thrall=thrall;
		ThreadArgPass->ContextBrokerInterface=NULL;
		if (additional_passed_arg){
			ThreadArgPass->additional=malloc(addarg_siz);
			ThreadArgPass->additional_size=addarg_siz;
			memcpy(ThreadArgPass->additional,additional_passed_arg,addarg_siz);
		}
//		else{
//			ThreadArgPass->additional=NULL;
//			ThreadArgPass->additional_size=0;
//		}

		switch(generic_plugin->interComm_method){
		case DenKr_plugin_interComm_method__infBroker:
			ThreadArgPass->ContextBrokerInterface=malloc(sizeof(DenKr_InfBroker_Iface_Client));
			memset(ThreadArgPass->ContextBrokerInterface,0,sizeof(DenKr_InfBroker_Iface_Client));
			(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->hidden).send_to_Broker=SockToBrok;
			(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->hidden).ownID=new_thID;
			(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->FuncSend).sendStr=(InfBrok_FuncSendStr)DenKr_ContextBroker_sendInfo_Str;
			(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->FuncRegConsumer).regSocket=(InfBrok_FuncRegListenMethod)DenKr_ContextBroker_register_Consumer_socket;
			(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->FuncRegConsumer).regCallback=(InfBrok_FuncRegCallback)DenKr_ContextBroker_register_Consumer_callback;
			(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->FuncRegProducer).regSocket=(InfBrok_FuncRegListenMethod)DenKr_ContextBroker_register_Producer_socket;
			(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->FuncRegProducer).regCallback=(InfBrok_FuncRegCallback)DenKr_ContextBroker_register_Producer_callback;
			break;
		case DenKr_plugin_interComm_method__ShMem:
			//Basically passed anyway and thus alternatively usable...
			break;
		case DenKr_plugin_interComm_method__socket:
			//TODO
			break;
		}

		pthread_attr_t tattr;
		if((err=pthread_attr_init(&tattr)) < 0) {
			perror("could not create thread-attribute");
			return THREAD__ERR__CREATION__ATTR_INIT;
		}
		if((err=pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_JOINABLE)) < 0){//PTHREAD_CREATE_JOINABLE, PTHREAD_CREATE_DETACHED
			perror("could not modify thread-attribute");
			if( (err=pthread_attr_destroy(&tattr)) != 0 ) {
				perror("could not destroy thread-attribute");
				return THREAD__ERR__CREATION__ATTR_DESTROY;
			}
			return THREAD__ERR__CREATION__ATTR_MODIFY;
		}
		if( (err=pthread_create(&(newEnt->pt_Object), &tattr, generic_plugin->hook, (void*)ThreadArgPass)) < 0) {
			perror("could not create thread");
			if( (err=pthread_attr_destroy(&tattr)) != 0 ) {
				perror("could not destroy thread-attribute");
				return THREAD__ERR__CREATION__ATTR_DESTROY;
			}
			return THREAD__ERR__CREATION__CREATE;
		}else{
			newEnt->spawned=1;
		}
		if( (err=pthread_attr_destroy(&tattr)) != 0 ) {
			perror("could not destroy thread-attribute");
			return THREAD__ERR__CREATION__ATTR_DESTROY;
		}
	}

	return new_thID;//Return the set threadID;
}

// Traverses the registered modules from the PluginManager
//   looks into the generic Linked-List, searches for the ones with
//   working-type 'Thread'.
//   Then starts them appropriately
//   -> start with the first Thread-ID after the predefined/basic Threads
//   -> accordingly sets the Thread-ID Value in the corresponding PluginManager-Entry
// Passed to this Threads are only basic Informations, that can be known beforehand:
//  - ThreadManager
//  - PluginManager
//  - ShMemHeaders
//  - ContextBroker
//  - OwnID ("who am I self?")
int DenKr_Thread_start_generics(PluginManager* plugman, ThreadManager* thrall, DenKr_essentials_ThreadID mainThreadID, struct ShMemHeader *shmem_headers, DenKr_InfBroker_SockToBrok* SockToBrok){
	int i;
	if(!(plugman->generic_c)){

	}else{
		struct PluginRoleGeneric* plugin;
		plugin=plugman->generic;
		DenKr_Thread_startThread_generic(thrall, plugin, mainThreadID, plugman, shmem_headers, SockToBrok, NULL, 0);
		for(i=1;i<plugman->generic_c;i++){
			plugin=plugin->next;
			DenKr_Thread_startThread_generic(thrall, plugin, mainThreadID, plugman, shmem_headers, SockToBrok, NULL, 0);
		}
	}
	return 0;
}
//--------------------------------------------------------------------------------------------------//

//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

















#undef NO_DENKR_ESSENTIALS_MULTI_THREADING_C_FUNCTIONS
#undef DENKR_ESSENTIALS_MULTI_THREADING_C
