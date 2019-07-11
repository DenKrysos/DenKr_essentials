/*
 * plugin_management.h
 *
 *  Created on: 26.07.2017 - 25.07.2018
 *      Author: Dennis Krummacker
 */

#ifndef DENKR_ESSENTIALS__PLUGINS__PLUGIN_MANAGEMENT_H
#define DENKR_ESSENTIALS__PLUGINS__PLUGIN_MANAGEMENT_H

#if !defined(DENKR_ESSENTIALS__DL_LIBS__NONE)


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
//#include <dlfcn.h>
//#include <stdint.h>
//#include <errno.h>
#include <stdint.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#if defined(DENKR_ESSENTIALS__DL_LIBS__NONE)
#elif defined(DENKR_ESSENTIALS__DL_LIBS__MAIN_APP)
	#include "plugins/export/plugins_DenKr_essentials__common.h"
#elif defined(DENKR_ESSENTIALS__DL_LIBS__PLUGIN_PREDEFINED)
	//Be cautious with the Resource-Linking (Eclipse) and include-paths (compiler arguments), when compiling a Plugin with set global Value
	#include "plugins_DenKr_essentials__common.h"
#elif defined(DENKR_ESSENTIALS__DL_LIBS__PLUGIN_GENERIC)
	//Generic Plugins/Modules at least need to know the "generic"-role and stuff like the working-modes
	#include "plugins_DenKr_essentials__common.h"
#else
	#pragma error "ERROR: Define either DENKR_ESSENTIALS__DL_LIBS__MAIN_APP or DENKR_ESSENTIALS__DL_LIBS__PLUGIN inside <global/global_settings.h>"
	ERROR"ERROR: Define either DENKR_ESSENTIALS__DL_LIBS__MAIN_APP or DENKR_ESSENTIALS__DL_LIBS__PLUGIN inside <global/global_settings.h>"
#endif
//---------------------------------------------------------------------------------
//#include "../PreC/DenKr_PreC.h"
//#include "../DenKr_errno.h"
//#include "../auxiliary.h"
//#include "function_creator.h"
//#include "getRealTime.h"
//#include "Program_Files/P_Files_Path.h"
#include "DenKr_essentials/Types/multi_threading_basicTypes.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//





//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Definitions  -------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
typedef enum DenKr_plugins_working_type_t{
		DenKr_plugin_working_type__undefined,
		DenKr_plugin_working_type__generic,
		DenKr_plugin_working_type__thread,
		DenKr_plugin_working_type__library
}DenKr_plugins_working_type;
typedef enum DenKr_plugins_interComm_method_t{
	DenKr_plugin_interComm_method__infBroker,
	DenKr_plugin_interComm_method__ShMem,
	DenKr_plugin_interComm_method__socket
}DenKr_plugins_interComm_method;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - -   Signatures   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//Basic/General Hook Signature
typedef void* (*PluginRoleHook)(void*);

//Hook Signature for Plugins of working-type 'Thread'
//    Adjust and use for Cast
typedef void* (*PluginRoleHookThread)(void*);

typedef int (*PluginRoleHookLibrary)(void*);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - -   Structures   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// Forward Declaration. Actual Definition of struct/type is in "plugin_discovery.h"
	//typedef struct PluginHandler_t PluginHandler;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef void* PluginHandle;

struct PluginHandleGeneric{
	PluginHandle handle;
	struct PluginHandleGeneric* next;
};

typedef struct PluginHandler_t{
	PluginHandle* handles;
	struct PluginHandleGeneric* generic;
	unsigned int generic_c;
}PluginHandler;

typedef uint8_t DenKr_Plugin_Role_Flags;

struct PluginRolePredefined{
	DenKr_Plugin_Role_Flags flags;
	DenKr_plugins_working_type work_type;
	PluginRoleHook hook;
};

//For Usage of the "Generic Role" (char* role, inside struct PluginRoleGeneric) a pretty nice example is done inside
//  the Module "DenKrement_plugin_predefined__connect_external_Python"
struct PluginRoleGeneric{
	DenKr_Plugin_Role_Flags flags;
	char* role;
	DenKr_plugins_working_type work_type;
	void* work_type_generic;//Used for further specification, if even the working-type follows no defined convention, i.e. is of generic type (and further spec is needed).
	DenKr_plugins_interComm_method interComm_method;
	DenKr_essentials_ThreadID ThreadID;
	PluginRoleHook hook;
	struct PluginRoleGeneric* next;
};

//Behind the predef Pointer accrues an Array, containing the predefined Roles.
//     (If no serving Plugin is found and thus can't be loaded, the corresponding 'role_defined'-Flag
//      in it's struct at its Array-Position becomes (or better said, stays at) '0')
//  As Array-Index, just the role-Number from the "enum DenKr_plugin_roles" is used.
//Behind the generic Pointer obviously a Linked List is used to register the generic Plugins
//  (which generally come at an unknown Number and with generic, Plugin-Developer-thought roles.)
//  (They will most probably be Functional-Extensions or modifications)
typedef struct PluginManager_t{
	struct PluginRolePredefined* predef;
	struct PluginRoleGeneric* generic;
	unsigned int generic_c;
	PluginHandler* PluginHandler;
}PluginManager;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - -   Flags   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define DENKR_PLUGINS_ROLE_FLAG__ROLE_DEFINED 0x01//Read: ROLE_UNDEFINED, If Flag is '0'. Flag is used 'Active 1'. To make it absolutely clear: This Flag tells us, if a serving Plugin, for this Role was found and could be loaded, i.e. this Role is fulfilled by a Plugin. At PluginManager Initialization the whole Array-Entries and hence this Flag are set to '0'. When Plugin is loaded, the Flag is set to '1'. So this Flag is an inverted ROLE_UNDEFINED.
#define DENKR_PLUGINS_ROLE_FLAG__ROLE_GENERIC 0x02
		// If another ROLE-specific Flags comes in use, we could code this Bits together, to ascertain 4 States like
		//    If( (flags & 0x03) == 0x00 )
//#define DENKR_PLUGINS_ROLE_FLAG__ 0x04
//#define DENKR_PLUGINS_ROLE_FLAG__ 0x08
//#define DENKR_PLUGINS_ROLE_FLAG__ 0x10
//#define DENKR_PLUGINS_ROLE_FLAG__ 0x20
//#define DENKR_PLUGINS_ROLE_FLAG__ 0x40
//#define DENKR_PLUGINS_ROLE_FLAG__ 0x80
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
#define DENKR_PLUGIN_MANAGER_INIT_SIGNATURE void PluginManager_init(PluginManager** plugman)
#define DENKR_PLUGIN_MANAGER_FREE_SIGNATURE void PluginManager_free(PluginManager** plugman)
#define DENKR_PLUGIN_MANAGER_REG_ROLE_PREDEF void PluginManager_register_role_predefined(PluginManager* plugman, DenKr_plugin_roles role, DenKr_plugins_working_type work_type, void* hook)
#define DENKR_PLUGIN_MANAGER_REG_ROLE_GENERIC void PluginManager_register_role_generic(PluginManager* plugman, char* role, int role_size, DenKr_plugins_working_type work_type, void* work_type_generic, DenKr_plugins_interComm_method interComm_method, void* hook)
//----------------------------------------------------------------------------------------------------
#ifndef NO_DENKR_ESSENTIALS__PLUGINS__PLUGIN_MANAGEMENT_C_FUNCTIONS
extern DENKR_PLUGIN_MANAGER_INIT_SIGNATURE;
extern DENKR_PLUGIN_MANAGER_FREE_SIGNATURE;
extern DENKR_PLUGIN_MANAGER_REG_ROLE_PREDEF;
extern DENKR_PLUGIN_MANAGER_REG_ROLE_GENERIC;
#endif
//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////







#endif
#endif /* DENKR_ESSENTIALS__PLUGINS__PLUGIN_MANAGEMENT_H */
