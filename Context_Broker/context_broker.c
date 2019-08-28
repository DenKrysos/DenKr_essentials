/*
 * context_broker.c
 *
 * Authored by
 * Dennis Krummacker (17.07.2018 - 25.07.2018)
 */



#define DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER__C
#define NO__DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER__C__FUNCTIONS



//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//--------  Preamble, Inclusions  ------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//==================================================================================================//
// At first include this ----------------------------------------------------------
//---------------------------------------------------------------------------------
#include "./global/global_settings.h"
#include "./global/global_variables.h"
// Need this for e.g. some really fundamental Program Basics (if any)  ------------
//---------------------------------------------------------------------------------
//#include "DenKrement_base.h"
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
#include <stdlib.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
//#include ""
//---------------------------------------------------------------------------------
#include "DenKr_essentials/auxiliary.h"
#include "DenKr_essentials/multi_threading.h"
#include "DenKr_essentials/Context_Broker/context_broker.h"
#include "DenKr_essentials/Context_Broker/context_broker_thread.h"
#include "DenKr_essentials/Context_Broker/context_broker_interface.h"
#define DenKr_HASHTAB__PRIME_NUM_LARGER_THAN_ALPHABET_1 149
#define DenKr_HASHTAB__PRIME_NUM_LARGER_THAN_ALPHABET_2 211
#define DenKr_HASHTAB__INIT_SIZE 53
#include "DenKr_essentials/DataStructures/hash_table.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//


//NOTE: You may wonder, why I did this crazy Function-Name-Creation Stuff to compile two instances of the Context-Broker.
//	For the Debugging-Mode of the Context-Broker, it is done like following:
//		Some of the functions (including the central 'DenKr_ContextBroker' itself) are compiled two times. One time with Debugging-Mode and one time without. This is done via some Macro construct, you see it down below.
//		At Thread startup, via the passed Variable (read-out from config-File in DenKrement) it decides which Version to instantiate.
//And now you ask: Why not just checking the variable at the corresponding Debug-Output occurrences.
//Because: This module is pretty performance critical. I don't want these checks constantly the whole time, on every message, even if it does not run in Debugging-Mode.
//	In the current implementation a run without Debugging-Mode is nice and clean and performant and is not influenced by any Debugging-Stuff at all.




//TODO: include escape sign in msg-format (CSV)
//
//TODO: Handle a close of the socket for sending to Consumer
//  If one side of the socketpair becomes closed, for what reason ever, both sides has to be closed in order to avoid memory leaks and enables the descriptor to gets reused
//  Also: Mind 'socket-shutdowns'
//
//TODO: Own Context that is used for when the ContextBroker has to send something "aus Eigeninitiative"
//  Bei jeder Registrierung auch in diesem Context nachsehen.
//  Better would be, if the Consumer registrate themselves for this Context, to make them able to decide over the method of Msg-Receiving by themselves.
//
//TODO: Request are currently only allowed for single context at a time.
//  Future Extension: Send a request for a whole battery of contexts inside one msg.
//
//TODO: Extension für Interface: Non-Blocking socket-recv function. Unter anderem anwendbar, um einfach mal zu prüfen ob was zum Auslesen vorliegt.
//
//TODO: Gegenwärtig kann jeder Client pro Consumer oder Producer mit nur jeweils einem Socket und einer Callback pro context registriert sein.
//		-> Ggf. Erweiterung auf beliebig viele Sockets / Callbacks auch pro context
//		(See this first comment-block inside 'context_broker_interface.h'. Its related with this.)
//
//TODO: Terminierungs Methodik über Context-Broker
//
//TODO: Remove-Methoden
//      - Wenn Remove-Anforderung kommt: Schicke nach Ausführung ACK zurück.
//  CAUTION: Performance Bottleneck: Currently the remove methods do NOT remove the whole entry for the Thread_ID from the context-entry inside the HashTab, if the whole entry is empty.
//           - They only set the Callback or Socket to Invalid/Zero.
// DONE: Functional Alpha for "RemoveCallback"
// NOT DONE: "RemoveSocket"
//
//TODO: A Method for directly and only sending to a specific target.
//      Sure, if it follows a continuous working, it is planned and both, sender and receiver know of this, than the receiver could just register for some "unique context" and the sender sends about this context.
//      But hell yeah, it would be a nice extension.
//
//TODO: When detecting invalid socket while sending: Remove Entry
//
//TODO: Remove the Context-Broker as central bottleneck
//		Currently every message transmission goes over the Context-Broker as a central handler.
//		I plan to create a second version of the Context-Broker which functions differently. There will be no central Context-Broker, or better said: No central one for message-passing-handling, but only for "existing at all"
//		In this version, very much will be done via an "interface". For every message to pass, an own 'handler' will be spawned, that takes care of passing this message to appropriate receivers.
//		This for sure requires detailed care of mutex handling for every Data (i.e. the Hash-Tables for modifications and 'read while write'; and also the receiving sockets of receivers to prevent mixing messages due to concurrent handlers sending to that socket; in some cases it could maybe also raise synchronization problems with callback-functions, when they are called concurrently, i.e. several instances are actively running at the time)

#define DEB_OR_NOT_NoDebug 0
#define DEB_OR_NOT_DoDebug 1


#ifdef DEBUG
//	#define DEBUG_INFBROKER

#define DEBUG_CHECK_test_VS_test_consumer_callback \
{\
	int i;\
	struct DenKr_InfBroker_HashTab_Entry_Val_t* ht_ent1;\
	DenKr_ContextBroker_get_ent_from_HashTab(&ht_ent1,hashtab,"test");\
	if(ht_ent1){\
		printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Checked Context in Hash-Table: %s\n","test");\
		printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Number of Entries for this: %d\n",ht_ent1->num);\
		for(i=0;i<ht_ent1->num;i++){\
			int nothing_to_print=1;\
			printf("\tID: %d",htEnt_arr(ht_ent1,i).threadID);\
			if(htEnt_arr(ht_ent1,i).iface){\
				nothing_to_print=0;\
				printf(" |  via Interface-Storage: %d\n",(htEnt_arr(ht_ent1,i).iface->hidden).ownID);\
			}\
			if(htEnt_arr(ht_ent1,i).callback){\
				nothing_to_print=0;\
				printf(" |  Callback-Addr: %llu\n",(htEnt_arr(ht_ent1,i).callback));\
			}\
			if(nothing_to_print){puts("");}\
		}\
	}\
	struct DenKr_InfBroker_HashTab_Entry_Val_t* ht_ent2;\
	DenKr_ContextBroker_get_ent_from_HashTab(&ht_ent2,hashtab,"test_consumer_callback");\
	if(ht_ent2){\
		printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Number of Entries for test_consumer_callback: %d\n",ht_ent2->num);\
		for(i=0;i<ht_ent2->num;i++){\
			int nothing_to_print=1;\
			printf("\tID: %d",htEnt_arr(ht_ent2,i).threadID);\
			if(htEnt_arr(ht_ent2,i).iface){\
				nothing_to_print=0;\
				printf(" |  via Interface-Storage: %d\n",(htEnt_arr(ht_ent2,i).iface->hidden).ownID);\
			}\
			if(htEnt_arr(ht_ent2,i).callback){\
				nothing_to_print=0;\
				printf(" |  Callback-Addr: %llu\n",(htEnt_arr(ht_ent2,i).callback));\
			}\
			if(nothing_to_print){puts("");}\
		}\
	}\
	printf("\nBoth Addresses:\n%llu\n%llu\n\n\n",ht_ent1,ht_ent2);\
}
#endif





#define htEnt_arr(HashTabEntry,ArrayIndex) ((&(HashTabEntry->entries))[ArrayIndex])


//At latest after this, following has to be finished:
// - receiving socket inclusive mutex
// - Database initialized (something like a Hash-Table for registered Consumers)
static int DenKr_ContextBroker_init(DenKr_InfBroker_SockToBrok* SockToBrok, DenKr_HashTab_hash_table** hashtab_consumer, DenKr_HashTab_hash_table** hashtab_producer){
	sem_init(&((SockToBrok->hidden).mutex),0,1);
	sem_wait(&((SockToBrok->hidden).mutex));
	int sockpair[2];
	if(-1==socketpair(AF_LOCAL, SOCK_STREAM, 0, sockpair)) {
	  printfc(red,"ERROR:");printf(" ContextBroker-Initialization: Could not create socketpair.\n");
	  exit(EXIT_FAILURE);
	}
	SockToBrok->sock=sockpair[0];
	(SockToBrok->hidden).sock_inside_broker=sockpair[1];
	sem_post(&((SockToBrok->hidden).mutex));
	DenKr_HashTab_htInit(hashtab_consumer);
	DenKr_HashTab_htInit(hashtab_producer);

	return 0;
}

static void DenKr_ContextBroker_init_ent_for_HashTab(struct DenKr_InfBroker_HashTab_Entry_Val_t** ht_ent, int* ht_ent_size, int num_entries){
	*ht_ent_size=sizeof(**ht_ent)-sizeof((*ht_ent)->entries)+num_entries*sizeof((*ht_ent)->entries);
//	printf("!!!! %d | %d \n\n\n\n",sizeof(*((*ht_ent)->entries)),sizeof(struct DenKr_InfBroker_HashTab_Entry_Val_Consumer_t));exit(1);
	*ht_ent=malloc(*ht_ent_size);
	memset(*ht_ent,0,*ht_ent_size);
	(*ht_ent)->num=num_entries;
//	(*ht_ent)->entries=(void*)((size_t)(&((*ht_ent)->entries))+sizeof((*ht_ent)->entries));
//	printf("\n\nTEST: %llu | %llu\n\n",&((*ht_ent)->entries),(*ht_ent)->entries);exit(1);
}

static void DenKr_ContextBroker_get_ent_from_HashTab(struct DenKr_InfBroker_HashTab_Entry_Val_t** ht_ent, DenKr_HashTab_hash_table* hashtab, char* context){
	DenKr_HashTab_ht_item* ht_it;
	ht_it = DenKr_HashTab_search(hashtab,context);
	if(ht_it){
		(*ht_ent)=ht_it->value;
	}else{
		*ht_ent=NULL;
	}
}


//Kommando zurück! There is no need for sorting, just insert new Entries right onto the matching position...
//static int DenKr_ContextBroker_htEntry_HeapSort(){
//static __inline void HEAP_SIFT_DOWN(DENKR_SORT_TYPE *dst, const size_t start, const size_t end) {
//  size_t root = start;
//
//  while ((root << 1) <= end) {
//    size_t child = root << 1;
//
//    if ((child < end) && (SORT_CMP(dst[child], dst[child + 1]) < 0)) {
//      child++;
//    }
//
//    if (SORT_CMP(dst[root], dst[child]) < 0) {
//      SORT_SWAP(dst[root], dst[child]);
//      root = child;
//    } else {
//      return;
//    }
//  }
//}
//
//static __inline void HEAPIFY(DENKR_SORT_TYPE *dst, const size_t size) {
//  size_t start = size >> 1;
//
//  while (1) {
//    HEAP_SIFT_DOWN(dst, start, size - 1);
//
//    if (start == 0) {
//      break;
//    }
//
//    start--;
//  }
//}
//
//static __inline void HEAP_SORT(DENKR_SORT_TYPE *dst, const size_t size) {
//  /* don't bother sorting an array of size <= 1 */
//  if (size <= 1) {
//    return;
//  }
//
//  size_t end = size - 1;
//  HEAPIFY(dst, size);
//
//  while (end > 0) {
//    SORT_SWAP(dst[end], dst[0]);
//    HEAP_SIFT_DOWN(dst, 0, end - 1);
//    end--;
//  }
//}
//}


//Only for Sorted Arrays!
// Return 0, if Value wasn't found, i.e. isn't present in Array.
// Return 1, if Value was found.
// 'Actual Result' is returned in int* res:
// If Value was found: Index of the searched Value:
// If Value wasn't found: Index of the smallest element greater than the Searched Value.
//      - if Value is smaller than the smallest element in the array: '0'
//      - if Value is greater than the highest element in the array: 'array-size' (i.e. 'highest-index + 1')
static int DenKr_ContextBroker_htEntry_BinSearch(const struct DenKr_InfBroker_HashTab_Entry_Val_t* list, DenKr_essentials_ThreadID key, unsigned int* res){
	#define SEARCH_VALUE_FOUND       1
	#define SEARCH_VALUE_NOT_FOUND   0
	#define size (list->num)
	int low, high, mid;
	low=0;
	high=size-1;
	int geq=size;

	while(high>=low){
		mid=(low+high)>>1; //(low+high)/2;
		if(key<htEnt_arr(list,mid).threadID){
			high=mid-1;
			geq=mid;
		}else if(key>htEnt_arr(list,mid).threadID){
			low=mid+1;
		}else{
			*res=mid;
			return SEARCH_VALUE_FOUND;
		}
	}
	*res = geq;
	return SEARCH_VALUE_NOT_FOUND;
	#undef size
	#undef SEARCH_VALUE_FOUND
	#undef SEARCH_VALUE_NOT_FOUND
}




//Be careful, this function is not save for mutual access. See comments inside.
//		static int DenKr_ContextBroker_reg_socket(DenKr_HashTab_hash_table* hashtab, DenKr_InfBroker_Iface_Client* src_iface, char* contexts){
#define _CREATE__DenKr_ContextBroker_reg_socket__FUNCNAME(APPENDIX)     DenKr_ContextBroker_reg_socket ## APPENDIX
#define CREATE__DenKr_ContextBroker_reg_socket__FUNCNAME(APPENDIX)      static int _CREATE__DenKr_ContextBroker_reg_socket__FUNCNAME(APPENDIX)(DenKr_HashTab_hash_table* hashtab, DenKr_InfBroker_Iface_Client* src_iface, char* contexts)
// - - - - - - -
#define CREATE__DenKr_ContextBroker_reg_socket(APPENDIX,DEB_OR_NOT) CREATE__DenKr_ContextBroker_reg_socket__FUNCNAME(APPENDIX){\
	int err=0;\
	char* context;\
	int ht_ent_size=0;\
	struct DenKr_InfBroker_HashTab_Entry_Val_t* ht_ent;\
	unsigned int ht_arr_index;\
\
	context=contexts;\
			/**/\
			/*printf("\ncontext: \n",context);*/\
			/*int i;*/\
			/*for(i=0;i<16;i++){*/\
			/*	printf("%c",*(context+i));*/\
			/*}*/\
			/*puts("");*/\
			/**/\
	while('\0'!=*context){\
		SWITCH( \
			EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
				, \
			EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
				printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Registering Socket for context: %s\n",context);\
				, \
			/* Default: */ \
				; \
		) \
		DenKr_ContextBroker_get_ent_from_HashTab(&ht_ent,hashtab,context);\
		if(ht_ent){\
			/*Entry already existent -> search for presence of current source*/\
			if(DenKr_ContextBroker_htEntry_BinSearch(ht_ent,(src_iface->hidden).ownID,&ht_arr_index)){\
				/*printf("searched ID: %d | found in Index: %d | Value on this index: %d\n",(src_iface->hidden).ownID,ht_arr_index,htEnt_arr(ht_ent,ht_arr_index).threadID);*/\
				/**/\
				/*Already registered in some way: Override the socket-part*/\
				/*NOTE: Be careful, this is not thread-save! This is only deterministic, if only one Entity accesses the Hash-Table.*/\
				/*NOTE: This method here is also depending on how the data is stored inside (or rather 'behind') the hash-table. So be careful,*/\
				/*       since this here directly modifies the malloced object to which is pointed.*/\
				/* Alternatively you could create a whole new Hash-Table Entry and call the HashTab to insert this (newly), which would result in deleting, and recreating the whole entry.*/\
				/**/\
				htEnt_arr(ht_ent,ht_arr_index).iface = src_iface;\
			}else{\
				/**/\
				/*Thread-ID not yet included: Insert.*/\
				/* -> new ht_ent, with array size+1. Copy up to and including the delivered 'ht_arr_index', insert new Consumer to register currently, copy rest afterwards.*/\
				/* -> insert new ht_ent into hashTab, this frees the old and newly inserts this one.*/\
				/**/\
				int ht_ent_size_new;\
				struct DenKr_InfBroker_HashTab_Entry_Val_t* ht_ent_new;\
				DenKr_ContextBroker_init_ent_for_HashTab(&ht_ent_new,&ht_ent_size_new,(ht_ent->num)+1);\
				if(0>=ht_arr_index){/*New Entry has to be first in the list*/\
					htEnt_arr(ht_ent_new,0).threadID=(src_iface->hidden).ownID;\
					htEnt_arr(ht_ent_new,0).iface=src_iface;\
					memcpy(&htEnt_arr(ht_ent_new,1),&htEnt_arr(ht_ent,0),(ht_ent->num)*sizeof(ht_ent->entries));\
				}else if(ht_arr_index>=(ht_ent->num)){/*New Entry has to be the last in the list*/\
					memcpy(&htEnt_arr(ht_ent_new,0),&htEnt_arr(ht_ent,0),(ht_ent->num)*sizeof(ht_ent->entries));\
					htEnt_arr(ht_ent_new,(ht_ent->num)).threadID=(src_iface->hidden).ownID;/* (ht_ent->num) is equal to '(ht_ent_new->num)-1', which is the highest Index of the new Array*/\
					htEnt_arr(ht_ent_new,(ht_ent->num)).iface=src_iface;\
				}else{/*New Entry has to be inserted somewhere between.*/\
					memcpy(&htEnt_arr(ht_ent_new,0),&htEnt_arr(ht_ent,0),ht_arr_index*sizeof(ht_ent->entries));\
					memcpy(&htEnt_arr(ht_ent_new,ht_arr_index+1),&htEnt_arr(ht_ent,ht_arr_index),((ht_ent->num)-ht_arr_index)*sizeof(ht_ent->entries));\
					htEnt_arr(ht_ent_new,ht_arr_index).threadID=(src_iface->hidden).ownID;/* (ht_ent->num) is equal to '(ht_ent_new->num)-1', which is the highest Index of the new Array*/\
					htEnt_arr(ht_ent_new,ht_arr_index).iface=src_iface;\
				}\
				DenKr_HashTab_insert(hashtab,context,ht_ent_new,ht_ent_size_new);\
				free(ht_ent_new);\
			}\
		}else{\
			/*No Entry in Hash-Table at all. Create completely new, with source as first and only Consumer*/\
			DenKr_ContextBroker_init_ent_for_HashTab(&ht_ent,&ht_ent_size,1);\
			htEnt_arr(ht_ent,0).threadID=(src_iface->hidden).ownID;\
			htEnt_arr(ht_ent,0).iface=src_iface;\
			DenKr_HashTab_insert(hashtab,context,ht_ent,ht_ent_size);\
			free(ht_ent);\
		}\
		for(;*context!='\0';context++){}context++;\
	}\
\
	return err;\
}
CREATE__DenKr_ContextBroker_reg_socket(,DEB_OR_NOT_NoDebug)
CREATE__DenKr_ContextBroker_reg_socket(_DEBUG,DEB_OR_NOT_DoDebug)

//Be careful, this function is not save for mutual access. See comments inside.
//		static int DenKr_ContextBroker_reg_callback(DenKr_HashTab_hash_table* hashtab, struct DenKr_InfBroker_Msg_Header* msgh, InfBrok_Func_Callback callback, char* contexts){
#define _CREATE__DenKr_ContextBroker_reg_callback__FUNCNAME(APPENDIX)      DenKr_ContextBroker_reg_callback ## APPENDIX
#define CREATE__DenKr_ContextBroker_reg_callback__FUNCNAME(APPENDIX)       static int _CREATE__DenKr_ContextBroker_reg_callback__FUNCNAME(APPENDIX)(DenKr_HashTab_hash_table* hashtab, struct DenKr_InfBroker_Msg_Header* msgh, InfBrok_Func_Callback callback, char* contexts)
// - - - - - - -
#define CREATE__DenKr_ContextBroker_reg_callback(APPENDIX,DEB_OR_NOT) CREATE__DenKr_ContextBroker_reg_callback__FUNCNAME(APPENDIX){\
	int err=0;\
	char* context;\
	int ht_ent_size=0;\
	struct DenKr_InfBroker_HashTab_Entry_Val_t* ht_ent;\
	unsigned int ht_arr_index;\
\
	context=contexts;\
	while('\0'!=*context){\
		SWITCH( \
			EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
				, \
			EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
				printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Registering Callback for context: %s\n",context);\
				, \
			/* Default: */ \
				; \
		) \
		DenKr_ContextBroker_get_ent_from_HashTab(&ht_ent,hashtab,context);\
		if(ht_ent){\
			/*Entry already existent -> search for presence of current source*/\
			if(DenKr_ContextBroker_htEntry_BinSearch(ht_ent,msgh->src,&ht_arr_index)){\
				/**/\
				/*Already registered in some way: Override the socket-part*/\
				/*NOTE: Be careful, this is not thread-save! This is only deterministic, if only one Entity accesses the Hash-Table.*/\
				/*NOTE: This method here is also depending on how the data is stored inside (or rather 'behind') the hash-table. So be careful,*/\
				/*       since this here directly modifies the malloced object to which is pointed.*/\
				/* Alternatively you could create a whole new Hash-Table Entry and call the HashTab to insert this (newly), which would result in deleting, and recreating the whole entry.*/\
				/**/\
				htEnt_arr(ht_ent,ht_arr_index).callback = callback;\
			}else{\
				/**/\
				/*Thread-ID not yet included: Insert.*/\
				/* -> new ht_ent, with array size+1. Copy up to and including the delivered 'ht_arr_index', insert new Consumer to register currently, copy rest afterwards.*/\
				/* -> insert new ht_ent into hashTab, this frees the old and newly inserts this one.*/\
				/**/\
				int ht_ent_size_new;\
				struct DenKr_InfBroker_HashTab_Entry_Val_t* ht_ent_new;\
				DenKr_ContextBroker_init_ent_for_HashTab(&ht_ent_new,&ht_ent_size_new,(ht_ent->num)+1);\
				if(0>=ht_arr_index){/*New Entry has to be first in the list*/\
					htEnt_arr(ht_ent_new,0).threadID=msgh->src;\
					htEnt_arr(ht_ent_new,0).callback=callback;\
					memcpy(&htEnt_arr(ht_ent_new,1),&htEnt_arr(ht_ent,0),(ht_ent->num)*sizeof(ht_ent->entries));\
				}else if(ht_arr_index>=(ht_ent->num)){/*New Entry has to be the last in the list*/\
					memcpy(&htEnt_arr(ht_ent_new,0),&htEnt_arr(ht_ent,0),(ht_ent->num)*sizeof(ht_ent->entries));\
					htEnt_arr(ht_ent_new,(ht_ent->num)).threadID=msgh->src;/* (ht_ent->num) is equal to '(ht_ent_new->num)-1', which is the highest Index of the new Array*/\
					htEnt_arr(ht_ent_new,(ht_ent->num)).callback=callback;\
				}else{/*New Entry has to be inserted somewhere between.*/\
					memcpy(&htEnt_arr(ht_ent_new,0),&htEnt_arr(ht_ent,0),ht_arr_index*sizeof(ht_ent->entries));\
					memcpy(&htEnt_arr(ht_ent_new,ht_arr_index+1),&htEnt_arr(ht_ent,ht_arr_index),((ht_ent->num)-ht_arr_index)*sizeof(ht_ent->entries));\
					htEnt_arr(ht_ent_new,ht_arr_index).threadID=msgh->src;/* (ht_ent->num) is equal to '(ht_ent_new->num)-1', which is the highest Index of the new Array*/\
					htEnt_arr(ht_ent_new,ht_arr_index).callback=callback;\
				}\
				DenKr_HashTab_insert(hashtab,context,ht_ent_new,ht_ent_size_new);\
				free(ht_ent_new);\
			}\
		}else{\
			/*No Entry in Hash-Table at all. Create completely new, with source as first and only Consumer*/\
			SWITCH( \
				EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
					, \
				EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
					/*printf("\n Putting in Callback-Address: %llu\n\n",callback);*/\
					, \
				/* Default: */ \
					/*;*/ \
			) \
			DenKr_ContextBroker_init_ent_for_HashTab(&ht_ent,&ht_ent_size,1);\
			htEnt_arr(ht_ent,0).threadID=msgh->src;\
			htEnt_arr(ht_ent,0).callback=callback;\
			SWITCH( \
				EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
					, \
				EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
				/*printf("\n Filling in Hash-Table with Callback wrote into: Context: %s  |  Entry-Count: %d\n\n",context,ht_ent->num);*/\
					, \
				/* Default: */ \
					/*;*/ \
			) \
			DenKr_HashTab_insert(hashtab,context,ht_ent,ht_ent_size);\
			free(ht_ent);\
		}\
		for(;*context!='\0';context++){}context++;\
	}\
\
	return err;\
}
CREATE__DenKr_ContextBroker_reg_callback(,DEB_OR_NOT_NoDebug)
CREATE__DenKr_ContextBroker_reg_callback(_DEBUG,DEB_OR_NOT_DoDebug)

//		static int DenKr_ContextBroker_dispenseInfo(DenKr_HashTab_hash_table* hashtab, struct DenKr_InfBroker_Msg_Header* msgh, char* msg){
	/**/
	/*Sieht in beiden Übermittlungs-Methoden nach und sendet unter Umständen auch auf beiden Methoden an denselben Clienten.*/
	/*Sollte ein Client während seines Betriebes die Methode WECHSELN wollen (d.h. von einer auf die andere umsteigen) obliegt es dem Clienten sich bei einer Methode mittels der Remove-Methode auszutragen.*/
	/*msg is supposed to look like (after the header):    [context] '\0' [otherStuff]*/
	/*                                            i.e.    'char1' 'char2' ... 'charN' '\0' 'SomeByte1' ... 'SomeByteM'*/
	/**/
#define _CREATE__DenKr_ContextBroker_dispenseInfo__FUNCNAME(APPENDIX)      DenKr_ContextBroker_dispenseInfo ## APPENDIX
#define CREATE__DenKr_ContextBroker_dispenseInfo__FUNCNAME(APPENDIX)       static int _CREATE__DenKr_ContextBroker_dispenseInfo__FUNCNAME(APPENDIX)(DenKr_HashTab_hash_table* hashtab, struct DenKr_InfBroker_Msg_Header* msgh, char* msg)
// - - - - - - -
#define CREATE__DenKr_ContextBroker_dispenseInfo(APPENDIX,DEB_OR_NOT) CREATE__DenKr_ContextBroker_dispenseInfo__FUNCNAME(APPENDIX){\
	int err=0, i;\
	struct DenKr_InfBroker_HashTab_Entry_Val_t* ht_ent;\
	DenKr_ContextBroker_get_ent_from_HashTab(&ht_ent,hashtab,msg);\
	if(ht_ent){\
		SWITCH( \
			EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
				, \
			EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
				/*DEBUG_CHECK_test_VS_test_consumer_callback*/\
				, \
			/* Default: */ \
				; \
		) \
		if(FLAG_CHECK(msgh->flags,DenKr_InfBroker_Msg_FLAG__SendDuplicate)){\
			for(i=0;i<ht_ent->num;i++){\
				if((htEnt_arr(ht_ent,i).iface) && (FLAG_CHECK(((htEnt_arr(ht_ent,i).iface)->hidden).flags,DenKr_InfBroker_Iface_Client__FLAG__SOCK_FROM_BROKER_VALID))){\
					/*NOTE: This sequential sending needs 'assistance' from the "receiver-side". But, it should be handled by my receiving implementation anyways, where i anyhow secure a proper socket-read at any rate; because... you know... socket-stuff can suck at times... (if i won't forget it ;oP)*/\
					/*printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" msgh.size: %d\n",msgh->len);*/\
					senddetermined(((htEnt_arr(ht_ent,i).iface)->hidden).recv_from_Broker.BrokerSock,(char*)msgh,sizeof(*msgh));\
					senddetermined(((htEnt_arr(ht_ent,i).iface)->hidden).recv_from_Broker.BrokerSock,msg,msgh->len);\
				}\
				if(htEnt_arr(ht_ent,i).callback){\
					/*Do an own malloc&copy for every callback-func that gets the msg. The callbacks have to free this.*/\
					char* msgcpy;\
					msgcpy=malloc(sizeof(*msgh)+(msgh->len));\
					memcpy(msgcpy,msgh,sizeof(*msgh));\
					memcpy(msgcpy+sizeof(*msgh),msg,msgh->len);\
					(htEnt_arr(ht_ent,i).callback)((void*)msgcpy);\
				}\
			}\
		}else{\
			/*The Sending itself and the surrounding for-loop is just the same as above, but extended by the check for the src to avoid duplicates (delivering msg back to sender).*/\
			for(i=0;i<ht_ent->num;i++){\
				if(htEnt_arr(ht_ent,i).threadID!=msgh->src){\
					if((htEnt_arr(ht_ent,i).iface) && (FLAG_CHECK(((htEnt_arr(ht_ent,i).iface)->hidden).flags,DenKr_InfBroker_Iface_Client__FLAG__SOCK_FROM_BROKER_VALID))){\
						senddetermined(((htEnt_arr(ht_ent,i).iface)->hidden).recv_from_Broker.BrokerSock,(char*)msgh,sizeof(*msgh));\
						senddetermined(((htEnt_arr(ht_ent,i).iface)->hidden).recv_from_Broker.BrokerSock,msg,msgh->len);\
					}\
					if(htEnt_arr(ht_ent,i).callback){\
						char* msgcpy;\
						msgcpy=malloc(sizeof(*msgh)+(msgh->len));\
						memcpy(msgcpy,msgh,sizeof(*msgh));\
						memcpy(msgcpy+sizeof(*msgh),msg,msgh->len);\
						(htEnt_arr(ht_ent,i).callback)((void*)msgcpy);\
					}\
				}\
			}\
		}\
	}else{\
		/*No Entry in Hash-Table*/\
		SWITCH( \
			EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
				, \
			EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
				printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" No Consumer-Entry for this Context present: %s\n",msg);\
				, \
			/* Default: */ \
				; \
		) \
	}\
	return err;\
}
CREATE__DenKr_ContextBroker_dispenseInfo(,DEB_OR_NOT_NoDebug)
CREATE__DenKr_ContextBroker_dispenseInfo(_DEBUG,DEB_OR_NOT_DoDebug)


//TODO
//		static int DenKr_ContextBroker_rem_socket(DenKr_HashTab_hash_table* hashtab, DenKr_InfBroker_Iface_Client* src_iface, char* contexts){
#define _CREATE__DenKr_ContextBroker_rem_socket__FUNCNAME(APPENDIX)      DenKr_ContextBroker_rem_socket ## APPENDIX
#define CREATE__DenKr_ContextBroker_rem_socket__FUNCNAME(APPENDIX)       static int _CREATE__DenKr_ContextBroker_rem_socket__FUNCNAME(APPENDIX)(DenKr_HashTab_hash_table* hashtab, DenKr_InfBroker_Iface_Client* src_iface, char* contexts)
// - - - - - - -
#define CREATE__DenKr_ContextBroker_rem_socket(APPENDIX,DEB_OR_NOT) CREATE__DenKr_ContextBroker_rem_socket__FUNCNAME(APPENDIX){\
	int err=0;\
\
	return err;\
}
CREATE__DenKr_ContextBroker_rem_socket(,DEB_OR_NOT_NoDebug)
CREATE__DenKr_ContextBroker_rem_socket(_DEBUG,DEB_OR_NOT_DoDebug)


//		static int DenKr_ContextBroker_rem_callback(DenKr_HashTab_hash_table* hashtab, struct DenKr_InfBroker_Msg_Header* msgh, InfBrok_Func_Callback callback, char* contexts){
#define _CREATE__DenKr_ContextBroker_rem_callback__FUNCNAME(APPENDIX)      DenKr_ContextBroker_rem_callback ## APPENDIX
#define CREATE__DenKr_ContextBroker_rem_callback__FUNCNAME(APPENDIX)       static int _CREATE__DenKr_ContextBroker_rem_callback__FUNCNAME(APPENDIX)(DenKr_HashTab_hash_table* hashtab, struct DenKr_InfBroker_Msg_Header* msgh, InfBrok_Func_Callback callback, char* contexts)
// - - - - - - -
#define CREATE__DenKr_ContextBroker_rem_callback(APPENDIX,DEB_OR_NOT) CREATE__DenKr_ContextBroker_rem_callback__FUNCNAME(APPENDIX){\
	int err=0;\
	char* context;\
	/*int ht_ent_size=0;*/\
	struct DenKr_InfBroker_HashTab_Entry_Val_t* ht_ent;\
	unsigned int ht_arr_index;\
\
	context=contexts;\
	while('\0'!=*context){\
		SWITCH( \
			EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
				, \
			EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
				printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Removing Callback from context: %s\n",context);\
				, \
			/* Default: */ \
				; \
		) \
		DenKr_ContextBroker_get_ent_from_HashTab(&ht_ent,hashtab,context);\
		if(ht_ent){\
			/*Entry already existent -> search for presence of current source*/\
			if(DenKr_ContextBroker_htEntry_BinSearch(ht_ent,msgh->src,&ht_arr_index)){\
				/**/\
				/*Callback for this Thread-ID inside this Context registered: Set Callback to NULL*/\
				/*Additional Notes: See inside the Register Functions.*/\
				/*TODO: Future extension: Check also if Socket is valid: YES: only set Callback to NULL. NO: Remove whole entry.*/\
				/**/\
				htEnt_arr(ht_ent,ht_arr_index).callback = NULL;\
			}else{\
				/**/\
				/*Thread-ID not included: Nothing to remove*/\
				/*No Entry FOR THIS THREAD in Hash-Table*/\
				/**/\
				SWITCH( \
					EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
						, \
					EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
						printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" No Entry for removing this Thread-ID from Context present: %s\n",context);\
						, \
					/* Default: */ \
						; \
				) \
			}\
		}else{\
			/*No Entry in Hash-Table*/\
			SWITCH( \
				EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
					, \
				EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
					printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" No Entry for this Context present at all (While Removing): %s\n",context);\
					, \
				/* Default: */ \
					; \
			) \
		}\
		for(;*context!='\0';context++){}context++;\
	}\
\
	return err;\
}
CREATE__DenKr_ContextBroker_rem_callback(,DEB_OR_NOT_NoDebug)
CREATE__DenKr_ContextBroker_rem_callback(_DEBUG,DEB_OR_NOT_DoDebug)

//TODO:
//		int DenKr_ContextBroker(DenKr_InfBroker_SockToBrok* SockToBrok, DenKr_HashTab_hash_table* hashtab_consumer, DenKr_HashTab_hash_table* hashtab_producer, DenKr_essentials_ThreadID ownID,DenKr_essentials_ThreadID mainThreadID){
#define _CREATE__DenKr_ContextBroker__FUNCNAME(APPENDIX)      DenKr_ContextBroker ## APPENDIX
#define CREATE__DenKr_ContextBroker__FUNCNAME(APPENDIX)       static int _CREATE__DenKr_ContextBroker__FUNCNAME(APPENDIX)(DenKr_InfBroker_SockToBrok* SockToBrok, DenKr_HashTab_hash_table* hashtab_consumer, DenKr_HashTab_hash_table* hashtab_producer, DenKr_essentials_ThreadID ownID,DenKr_essentials_ThreadID mainThreadID)
// - - - - - - -
#define CREATE__DenKr_ContextBroker(APPENDIX,DEB_OR_NOT) CREATE__DenKr_ContextBroker__FUNCNAME(APPENDIX){\
	int err;\
	int b_recvd;/*bytes received from socket*/\
	struct DenKr_InfBroker_Msg_Header msgh;\
	char* msg=NULL;\
	/*First a 'PEEK' read, just for blocking and reawakening, for the sake of performance and afterwards the Mutex-Handling and than only doing the real socket-read*/\
	while(recv((SockToBrok->hidden).sock_inside_broker,&msgh,1, MSG_PEEK) != 0){\
		/*ContextBrokerReadSocketStart:*/\
		sem_wait(&((SockToBrok->hidden).mutex));\
		/*TODO: Use function "recvdetermined"*/\
		b_recvd=recv((SockToBrok->hidden).sock_inside_broker,&msgh,sizeof(msgh),0);\
		if(0<b_recvd){/*proper operation*/\
			/*Header is received. Now use the 'len' to get the actual msg and Mux the Types.*/\
			if(msgh.len){\
				msg=malloc(msgh.len);\
				b_recvd=recv((SockToBrok->hidden).sock_inside_broker,msg,msgh.len,0);\
				while(b_recvd<msgh.len){\
					int b_recvd_temp;\
					b_recvd_temp=recv((SockToBrok->hidden).sock_inside_broker,msg+b_recvd,(msgh.len)-b_recvd,0);\
					if(0>b_recvd_temp){\
						/*TODO*/\
						printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at receiving inside Context-Broker 1.\n");\
					}else if(0==b_recvd_temp){\
						/*TODO*/\
						printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at receiving inside Context-Broker 2.\n");\
					}\
					b_recvd+=b_recvd_temp;\
				}\
			}\
			sem_post(&((SockToBrok->hidden).mutex));\
			switch(msgh.type){\
			case DenKr_InfBroker_Msg_Type__Management:\
				switch(msgh.subtype){\
				case DenKr_InfBroker_Msg_SubType__Management_Restricted__Termination:\
					if(msgh.src==mainThreadID){\
						/*Valid: Termination*/\
						printfc(DENKR__COLOR_ANSI__THREAD_BASIC,"<ContextBroker:>");printfc(gray," NOTE:");printf(" Received Termination Command.\n");\
						err=THREAD__OP__TERMINATION;\
						sem_wait(&((SockToBrok->hidden).mutex));\
						if(shutdown((SockToBrok->hidden).sock_inside_broker,1)==-1){\
							fprintf(stderr, "unable to shutdown socket\n");\
							exit(1);\
						}\
						if(close((SockToBrok->hidden).sock_inside_broker)==-1){\
							fprintf(stderr, "unable to close socket\n");\
							exit(1);\
						}\
						if(shutdown(SockToBrok->sock,1)==-1){\
							fprintf(stderr, "unable to shutdown socket\n");\
							exit(1);\
						}\
						if(close(SockToBrok->sock)==-1){\
							fprintf(stderr, "unable to close socket\n");\
							exit(1);\
						}\
						sem_post(&((SockToBrok->hidden).mutex));\
						sem_destroy(&((SockToBrok->hidden).mutex));\
						/*TODO: Still much todo here...*/\
						goto ContextBrokerTermination;\
					}else{\
						printfc(red,"WARNING:");printf(" Context-Broker recvd Termination Command from Thread different from Main. Ignoring...\n");\
					}\
					break;\
				case DenKr_InfBroker_Msg_SubType__Management__RegConsumerSocket:\
					SWITCH( \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
							, \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
							printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Context-Broker - Registering ConsumerSocket for ID: %d\n", msgh.src);\
							/**/\
							/*printfc(gray,"DEBUG:");printf(" Msg: size: %llu | src: %hu | type: %hu | subtype: %hu |\n\tmsg (after Iface-Pointer, First Null-terminated) %s\n",(unsigned long long)msgh.len,msgh.src,msgh.type,msgh.subtype,msg+sizeof(DenKr_InfBroker_Iface_Client*));*/\
							/*DenKr_InfBroker_Iface_Client* temptestp;*/\
							/*temptestp=*((DenKr_InfBroker_Iface_Client**)msg);*/\
							/*printfc(gray,"DEBUG:");printf(" From the Interface-Pointer: ID: %d\n",(temptestp->hidden).ownID);*/\
							/**/\
							, \
						/* Default: */ \
							; \
					) \
					SWITCH( \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
							DenKr_ContextBroker_reg_socket(hashtab_consumer,*((DenKr_InfBroker_Iface_Client**)msg),msg+sizeof(DenKr_InfBroker_Iface_Client*));\
							, \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
							DenKr_ContextBroker_reg_socket_DEBUG(hashtab_consumer,*((DenKr_InfBroker_Iface_Client**)msg),msg+sizeof(DenKr_InfBroker_Iface_Client*));\
							, \
						/* Default: */ \
							; \
					) \
					break;\
				case DenKr_InfBroker_Msg_SubType__Management__RegConsumerCallback:\
					SWITCH( \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
							, \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
							printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Context-Broker - Registering ConsumerCallback for ID: %d\n", msgh.src);\
							, \
						/* Default: */ \
							; \
					) \
						/**/\
						/*;*/\
						/*int i;*/\
						/*puts("");*/\
						/*for(i=0;i<msgh.len;i++){*/\
						/*	printf("%d | ",msg[i]);*/\
						/*}*/\
						/*puts("");*/\
						/**/\
						SWITCH( \
							EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
								DenKr_ContextBroker_reg_callback(hashtab_consumer, &msgh, *((InfBrok_Func_Callback*)msg), msg+sizeof(InfBrok_Func_Callback));\
								, \
							EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
								DenKr_ContextBroker_reg_callback_DEBUG(hashtab_consumer, &msgh, *((InfBrok_Func_Callback*)msg), msg+sizeof(InfBrok_Func_Callback));\
								, \
							/* Default: */ \
								; \
						) \
					break;\
				case DenKr_InfBroker_Msg_SubType__Management__RegProducerSocket:\
					SWITCH( \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
							, \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
							printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Context-Broker - Registering ProducerSocket for ID: %d\n", msgh.src);\
							, \
						/* Default: */ \
							; \
					) \
					SWITCH( \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
							DenKr_ContextBroker_reg_socket(hashtab_producer,*((DenKr_InfBroker_Iface_Client**)msg),msg+sizeof(DenKr_InfBroker_Iface_Client*));\
							, \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
							DenKr_ContextBroker_reg_socket_DEBUG(hashtab_producer,*((DenKr_InfBroker_Iface_Client**)msg),msg+sizeof(DenKr_InfBroker_Iface_Client*));\
							, \
						/* Default: */ \
							; \
					) \
					break;\
				case DenKr_InfBroker_Msg_SubType__Management__RegProducerCallback:\
					SWITCH( \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
							, \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
							printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Context-Broker - Registering ProducerCallback for ID: %d\n", msgh.src);\
							/*printfc(gray,"DEBUG:");printf(" Msg: size: %llu | src: %hu | type: %hu | subtype: %hu |\n\tCallback-Address: %llu | msg (after CB-Pointer, First Null-terminated) %s\n",(unsigned long long)msgh.len,msgh.src,msgh.type,msgh.subtype,*((InfBrok_Func_Callback*)msg),msg+sizeof(InfBrok_Func_Callback));*/\
							, \
						/* Default: */ \
							; \
					) \
					SWITCH( \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
							DenKr_ContextBroker_reg_callback(hashtab_producer, &msgh, *((InfBrok_Func_Callback*)msg), msg+sizeof(InfBrok_Func_Callback));\
							, \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
							DenKr_ContextBroker_reg_callback_DEBUG(hashtab_producer, &msgh, *((InfBrok_Func_Callback*)msg), msg+sizeof(InfBrok_Func_Callback));\
							, \
						/* Default: */ \
							; \
					) \
					break;\
				case DenKr_InfBroker_Msg_SubType__Management__RemoveConsumerSocket:\
					SWITCH( \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
							DenKr_ContextBroker_rem_socket(hashtab_producer,*((DenKr_InfBroker_Iface_Client**)msg),msg+sizeof(DenKr_InfBroker_Iface_Client*));\
							, \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
							DenKr_ContextBroker_rem_socket_DEBUG(hashtab_producer,*((DenKr_InfBroker_Iface_Client**)msg),msg+sizeof(DenKr_InfBroker_Iface_Client*));\
							, \
						/* Default: */ \
							; \
					) \
					break;\
				case DenKr_InfBroker_Msg_SubType__Management__RemoveConsumerCallback:\
					SWITCH( \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
							DenKr_ContextBroker_rem_callback(hashtab_consumer, &msgh, *((InfBrok_Func_Callback*)msg), msg+sizeof(InfBrok_Func_Callback));\
							, \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
							DenKr_ContextBroker_rem_callback_DEBUG(hashtab_consumer, &msgh, *((InfBrok_Func_Callback*)msg), msg+sizeof(InfBrok_Func_Callback));\
							, \
						/* Default: */ \
							; \
					) \
					break;\
				case DenKr_InfBroker_Msg_SubType__Management__RemoveProducerSocket:\
					SWITCH( \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
							DenKr_ContextBroker_rem_socket(hashtab_producer,*((DenKr_InfBroker_Iface_Client**)msg),msg+sizeof(DenKr_InfBroker_Iface_Client*));\
							, \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
							DenKr_ContextBroker_rem_socket_DEBUG(hashtab_producer,*((DenKr_InfBroker_Iface_Client**)msg),msg+sizeof(DenKr_InfBroker_Iface_Client*));\
							, \
						/* Default: */ \
							; \
					) \
					break;\
				case DenKr_InfBroker_Msg_SubType__Management__RemoveProducerCallback:\
					SWITCH( \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
							DenKr_ContextBroker_rem_callback(hashtab_producer, &msgh, *((InfBrok_Func_Callback*)msg), msg+sizeof(InfBrok_Func_Callback));\
							, \
						EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
							DenKr_ContextBroker_rem_callback_DEBUG(hashtab_producer, &msgh, *((InfBrok_Func_Callback*)msg), msg+sizeof(InfBrok_Func_Callback));\
							, \
						/* Default: */ \
							; \
					) \
					break;\
				}\
				break;\
			case DenKr_InfBroker_Msg_Type__Request:\
				SWITCH( \
					EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
						, \
					EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
						printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Request for Context: size: %llu | src: %hu | type: %hu | subtype: %hu |\n\tmsg (First Null-terminated): %s\n",(unsigned long long)msgh.len,msgh.src,msgh.type,msgh.subtype,msg);\
						, \
					/* Default: */ \
						; \
				) \
				SWITCH( \
					EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
						DenKr_ContextBroker_dispenseInfo(hashtab_producer,&msgh,msg);\
						, \
					EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
						DenKr_ContextBroker_dispenseInfo_DEBUG(hashtab_producer,&msgh,msg);\
						, \
					/* Default: */ \
						; \
				) \
				/*TODO*/\
				break;\
			/*case DenKr_InfBroker_Msg_Type__Generic:*/\
				/*break;*/\
			case DenKr_InfBroker_Msg_Type__Raw:\
				/*break;*/\
			case DenKr_InfBroker_Msg_Type__KeyEqualValue_CSV:\
				/*break;*/\
			default:\
				SWITCH( \
					EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
						, \
					EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
						printfc(gray,"DEBUG");printfc(DENKR__COLOR_ANSI__CONTEXT_BROKER," (InfBrok):");printf(" Msg to dispense: size: %llu | src: %hu | type: %hu | subtype: %hu |\n\tmsg (First Null-terminated): %s | (Second Null-terminated) %s\n",(unsigned long long)msgh.len,msgh.src,msgh.type,msgh.subtype,msg,msg+strlen(msg)+1);\
						, \
					/* Default: */ \
						; \
				) \
				SWITCH( \
					EQUAL(DEB_OR_NOT,DEB_OR_NOT_NoDebug), \
						DenKr_ContextBroker_dispenseInfo(hashtab_consumer,&msgh,msg);\
						, \
					EQUAL(DEB_OR_NOT,DEB_OR_NOT_DoDebug), \
						DenKr_ContextBroker_dispenseInfo_DEBUG(hashtab_consumer,&msgh,msg);\
						, \
					/* Default: */ \
						; \
				) \
				break;\
			}\
			if(msg){\
				free(msg);\
				msg=NULL;\
			}\
		}else if(0>b_recvd){/*error returned, check ERRNO*/\
			/*TODO*/\
			/*ContextBrokerReadSocketError:*/\
			sem_post(&((SockToBrok->hidden).mutex));\
			printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at receiving inside Context-Broker 3.\n");\
			goto ContextBrokerTermination;\
		}else{/*only '0==b_recvd' left, normal socket shutdown at counterside*/\
			/*TODO*/\
			/*ContextBrokerReadSocketShutdown:*/\
			sem_post(&((SockToBrok->hidden).mutex));\
			printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at receiving inside Context-Broker 4.\n");\
			goto ContextBrokerTermination;\
		}\
	}/*TODO: handle here a socket-shutdown (caused by the other side) as well as at the inside-reader socket*/\
\
	ContextBrokerTermination:\
	return err;\
}
CREATE__DenKr_ContextBroker(,DEB_OR_NOT_NoDebug)
CREATE__DenKr_ContextBroker(_DEBUG,DEB_OR_NOT_DoDebug)


void* DenKr_ContextBroker_thread(void* arg){
	#define shmem_recv_start_self ShMem_recv_start(&(shmem_headers[DENKREMENT_THREAD__CONTEXT_BROKER]))
	#define shmem_recv_finish_self ShMem_recv_finish(&(shmem_headers[DENKREMENT_THREAD__CONTEXT_BROKER]))
	#define shmem_self (shmem_headers[DENKREMENT_THREAD__CONTEXT_BROKER])
	ThreadManager* thrall = (((struct DenKr_ContextBroker_ThreadArgPassing *)arg)->thrall);
	PluginManager* plugman = (((struct DenKr_ContextBroker_ThreadArgPassing *)arg)->plugman);
	struct ShMemHeader *shmem_headers = (((struct DenKr_ContextBroker_ThreadArgPassing *)arg)->shmem_headers);
	DenKr_InfBroker_SockToBrok* SockToBrok = ((struct DenKr_ContextBroker_ThreadArgPassing *)arg)->SockToBrok;
	DenKr_essentials_ThreadID ownID = (((struct DenKr_ContextBroker_ThreadArgPassing *)arg)->ownID);
	DenKr_essentials_ThreadID mainThreadID = (((struct DenKr_ContextBroker_ThreadArgPassing *)arg)->mainThreadID);
	char debmode=(((struct DenKr_ContextBroker_ThreadArgPassing *)arg)->contbrok_debug);
	free(arg);
//	int err;

	printf("\n");printfc(DENKR__COLOR_ANSI__THREAD_BASIC,"Thread <");printf("Context-Broker");printfc(DENKR__COLOR_ANSI__THREAD_BASIC,">:")
	printf(" Starting...  (Debug-Mode: '%s')\n", debmode?"enabled":"disabled");

	// Initialization of earliest required stuff
	DenKr_HashTab_hash_table* hashtab_consumer;
	DenKr_HashTab_hash_table* hashtab_producer;
	DenKr_ContextBroker_init(SockToBrok, &hashtab_consumer, &hashtab_producer);

	printfc(DENKR__COLOR_ANSI__THREAD_BASIC,"Thread <");printf(" Context-Broker");printfc(DENKR__COLOR_ANSI__THREAD_BASIC,">:")
	printf(" Entirely initialized.\n\n");
	// Send main() via ShMem that Initialization is finished.
	ShMem_send_start(&(shmem_headers[mainThreadID]), 0, SHMEM_MSG_TYPE__READY);
	FLAG_SET(shmem_headers[mainThreadID].flags,SHMEM_MSG_FLAG__SRC_VALID);
	shmem_headers[mainThreadID].src = ownID;
	ShMem_send_finish(&(shmem_headers[mainThreadID]));

	//Tell Main, that i am Ready and than wait for Main, to tell me, that everyone is Ready.
	// Kind of this is done beforehand anyhow, nonetheless participate on this wholly Program-wide, across all Threads Method just for thoroughness.
	DenKr_Thread_Ready_Init(shmem_headers, mainThreadID, ownID)


	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------//
	//----  Context-Broker / Information-Dispenser  ----------------------------------------------------//
	//----  used as central Unit, enables nice and easy Inter-Thread/Module/Program-Communication  -----//
	//----  uses a Unix-Socket as Msg-Buffer & something like a Hash-Table as DataBase for  ------------//
	//----     Clients, registered for certain Information/Context-Roles  ------------------------------//
	//----  Loops over socket & when recv a msg: checks for registered Clients for the  ----------------//
	//----     corresponding role and sends it to all.  ------------------------------------------------//
	//--------------------------------------------------------------------------------------------------//
	//==================================================================================================//
	//----------------------------------------------------------------------------------------------
	switch(debmode){
	case 0:
		DenKr_ContextBroker(SockToBrok, hashtab_consumer, hashtab_producer, ownID, mainThreadID);
		break;
	case 1:
		DenKr_ContextBroker_DEBUG(SockToBrok, hashtab_consumer, hashtab_producer, ownID, mainThreadID);
		break;
	default:
		break;
	}




	//TODO: Maybe add some valid Program-Termination / CANCEL_THREAD via the Context-Broker. If, then look also into main()
//	ShMem_send_start(&(shmem_headers[mainThreadID]), 0, SHMEM_MSG_TYPE__CANCEL_THREAD);
//	FLAG_SET(shmem_headers[mainThreadID].flags,SHMEM_MSG_FLAG__SRC_VALID);
//	shmem_headers[mainThreadID].src = ownID;
//	ShMem_send_finish(&(shmem_headers[mainThreadID]));


	DenKr_HashTab_htFree(hashtab_consumer);
	DenKr_HashTab_htFree(hashtab_producer);
	printfc(yellow,"IMPORTANT:");
	printf(" ");printfc(DENKR__COLOR_ANSI__THREAD_BASIC,"<");printf("Context-Broker");printfc(DENKR__COLOR_ANSI__THREAD_BASIC,">-Thread");printf(" is closing.\n");

	#undef shmem_recv_start_self
	#undef shmem_recv_finish_self
	#undef shmem_self
	return NULL;
}




#undef htEnt_arr





#undef DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER__C
#undef NO__DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER__C__FUNCTIONS
