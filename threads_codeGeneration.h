/*
 * threads_codeGeneration.h
 *
 *  Created on: 13.08.2019
 *      Author: Dennis Krummacker
 */

#ifndef DENKR_ESSENTIALS__THREADS_CODEGENERATION_H
#define DENKR_ESSENTIALS__THREADS_CODEGENERATION_H


#if defined(DENKR_ESSENTIALS__DL_LIBS__NONE)
#elif defined(DENKR_ESSENTIALS__DL_LIBS__MAIN_APP)

#include "DenKr_essentials/PreC/DenKr_PreC.h"
#include "DenKr_essentials/Plugins/plugin_codeGeneration.h"
//#include "DenKr/DenKr_threads.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  For the predefined Plugin-Roles  -----------------------------------------------------------//
//----  This automatically generates Code, based on the defined Roles inside  ----------------------//
//----  <MainProgram>/src/plugins/export/plugins_DenKr_essentials__common.h  -----------------------//
//----  and fills them into the enumeration for Thread-IDs  ----------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//

//Append the Prefix
#define DENKR_THREAD_CONCAT_PREFIX_(ARG) DenKr_Thread__ ## ARG
#define DenKr_Thread_Plugin_ENTRIES_ CALL_MACRO_X_FOR_EACH__LIST(DENKR_THREAD_CONCAT_PREFIX_,DenKr_plugin_roles_ENTRIES)
//A little Trick, which automagically decides, if a trailing comma is necessary
#define DenKr_Thread_Plugin_ENTRIES__appendCOMMA DenKr_Thread_Plugin_ENTRIES_,
#define DenKr_Thread_Plugin_ENTRIES__ \
		IF(EQUAL(COUNT_VARARGS(DenKr_plugin_roles_ENTRIES),0))(\
		)IF(NOT_EQUAL(COUNT_VARARGS(DenKr_plugin_roles_ENTRIES),0))(\
			DenKr_Thread_Plugin_ENTRIES__appendCOMMA\
		)



//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  For the intrinsic Threads  -----------------------------------------------------------------//
//----  This automatically generates the partial List for the intrinsic Threads, which are running directly in the main App  --//
//----  <MainProgram>/src/DenKr_threads.h  ---------------------------------------------------------//
//----  and fills it into the enumeration for Thread-IDs  ------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//

#define DenKr_Thread_ENTRIES_CONCAT_PREFIX_EXPAND_(ARG1,ARG2) ARG1 ## __ ## ARG2
#define DenKr_Thread_ENTRIES_CONCAT_PREFIX_EXPAND(ARG1,ARG2) DenKr_Thread_ENTRIES_CONCAT_PREFIX_EXPAND_(ARG1,ARG2)
#define DenKr_Thread_ENTRIES_CONCAT_PREFIX_(ARG) \
	IF(EQUAL(COUNT_VARARGS(DenKr_Thread_ENTRIES_Prefix),0))(\
		ARG\
	)IF(NOT_EQUAL(COUNT_VARARGS(DenKr_Thread_ENTRIES_Prefix),0))(\
		DenKr_Thread_ENTRIES_CONCAT_PREFIX_EXPAND(DenKr_Thread_ENTRIES_Prefix,ARG)\
	)
#define DenKr_Thread_ENTRIES_ CALL_MACRO_X_FOR_EACH__LIST(DenKr_Thread_ENTRIES_CONCAT_PREFIX_,DenKr_Thread_ENTRIES)

#define DenKr_Thread_ENTRIES__appendCOMMA(...) __VA_ARGS__,
#define DenKr_Thread_ENTRIES__EXPAND(...) \
		IF(EQUAL(COUNT_VARARGS(DenKr_Thread_ENTRIES),0))(\
		)IF(NOT_EQUAL(COUNT_VARARGS(DenKr_Thread_ENTRIES),0))(\
				DenKr_Thread_ENTRIES__appendCOMMA(__VA_ARGS__)\
		)
#define DenKr_Thread_ENTRIES__ DenKr_Thread_ENTRIES__EXPAND(DenKr_Thread_ENTRIES_)



//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  The Enumeration  ---------------------------------------------------------------------------//
//----    which is then finally in Use  ------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//

//Thread Indices
typedef enum DenKrement_Thread_IDC_t{
	//Own Threads of DenKrement. Fixed. Straightly included in DenKrement itself
	DENKREMENT_THREAD__MAIN=0,
	//===================================================================
	//additional Threads are automatically filled in here
	DenKr_Thread_ENTRIES__
	//===================================================================
	//predefined Plugin Roles are automatically filled in here
	DenKr_Thread_Plugin_ENTRIES__
	//===================================================================
	//Use this at initialization of the Array: (This is a quantity, the above are IDs)
	DENKR_THREADS__MAX_PREDEF,
	//===================================================================
	DENKR_THREADS__SHMEM_MAX = DENKR_THREADS__MAX_PREDEF
}DenKrement_Thread_IDC;




#elif defined(DENKR_ESSENTIALS__DL_LIBS__PLUGIN_PREDEFINED)
#elif defined(DENKR_ESSENTIALS__DL_LIBS__PLUGIN_GENERIC)
#else
	#pragma error "ERROR: Define either DENKR_ESSENTIALS__DL_LIBS__MAIN_APP or DENKR_ESSENTIALS__DL_LIBS__PLUGIN inside <global/global_settings.h>"
	ERROR"ERROR: Define either DENKR_ESSENTIALS__DL_LIBS__MAIN_APP or DENKR_ESSENTIALS__DL_LIBS__PLUGIN inside <global/global_settings.h>"
#endif


#endif /* DENKR_ESSENTIALS__THREADS_CODEGENERATION_H */
