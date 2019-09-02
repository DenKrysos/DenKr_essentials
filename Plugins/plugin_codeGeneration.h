/*
 * plugin_codeGeneration.h
 *
 *  Created on: 13.08.2019
 *      Author: Dennis Krummacker
 */

#ifndef DENKR_ESSENTIALS__PLUGINS__PLUGIN_CODEGENERATION_H
#define DENKR_ESSENTIALS__PLUGINS__PLUGIN_CODEGENERATION_H


#include "DenKr_essentials/PreC/DenKr_PreC.h"
#include "plugins/export/plugins_DenKr_essentials__common.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  For the predefined Plugin-Roles  -----------------------------------------------------------//
//----  This automatically generates Code, based on the defined Roles inside  ----------------------//
//----  <MainProgram>/src/plugins/export/plugins_DenKr_essentials__common.h  -----------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//



//This just concatenates the the ENTRIES with "DenKr_plugin_role__". In this way we can reuse the reduced names of the actual roles where else needed and nonetheless have them here nice in "seperated namespace" together with some prefix.
#define DENKR_PLUGIN_ROLES_CONCAT_PREFIX_(ARG) DenKr_plugin_role__ ## ARG
#define DenKr_plugin_roles_ENTRIES_ CALL_MACRO_X_FOR_EACH__LIST(DENKR_PLUGIN_ROLES_CONCAT_PREFIX_,DenKr_plugin_roles_ENTRIES)

//Just a stupid Fix to enable the possibility to keep the ENTRIES List without trailing "comma", but also have the enum down below without fixed trailing ","
#define DenKr_plugin_roles_ENTRIES__ADD_LIST_START_AT_ZERO_CASE2EXP(ARG1,...) ARG1=0,__VA_ARGS__
#define DenKr_plugin_roles_ENTRIES__ADD_LIST_START_AT_ZERO(ARG1,...) \
		IF(EQUAL(COUNT_VARARGS(__VA_ARGS__),0))(\
			ARG1=0\
		)IF(NOT_EQUAL(COUNT_VARARGS(__VA_ARGS__),0))(\
			DenKr_plugin_roles_ENTRIES__ADD_LIST_START_AT_ZERO_CASE2EXP(ARG1,__VA_ARGS__)\
		)
#define DenKr_plugin_roles_ENTRIES__appendCOMMA(...) DenKr_plugin_roles_ENTRIES__ADD_LIST_START_AT_ZERO(__VA_ARGS__),
#define DenKr_plugin_roles_ENTRIES__EXPAND(...) \
		IF(EQUAL(COUNT_VARARGS(DenKr_plugin_roles_ENTRIES),0))(\
		)IF(NOT_EQUAL(COUNT_VARARGS(DenKr_plugin_roles_ENTRIES),0))(\
			DenKr_plugin_roles_ENTRIES__appendCOMMA(__VA_ARGS__)\
		)
#define DenKr_plugin_roles_ENTRIES__ DenKr_plugin_roles_ENTRIES__EXPAND(DenKr_plugin_roles_ENTRIES_)

typedef enum DenKr_plugin_roles_t{
	DenKr_plugin_role__generic=-1,
	//===================================================
	//Your Roles are then included here by itself
	DenKr_plugin_roles_ENTRIES__
	//===================================================
	DenKr_plugin_role__MAX
	//---------------------------------------------------
			//Reworked: Don't need this anymore:
			//	DenKr_plugin_role__undefined,
			//	DenKr_plugin_role__generic,
			//		DenKr_plugin_role__general = DenKr_plugin_role__generic,
			//		DenKr_plugin_role__extension = DenKr_plugin_role__generic,
			//		DenKr_plugin_role__not_predefined = DenKr_plugin_role__generic,
			//	//-------------------------------------------------------------------
			//	DenKr_plugin_role__MAX,
			//	DenKr_plugin_role__MAX_Excluding_generic = DenKr_plugin_role__MAX - 1,
			//	DenKr_plugin_role__MAX_predefined = DenKr_plugin_role__MAX_Excluding_generic - 1,
			//	DenKr_plugin_role__MAX_Dummy //to restore the Highest Value
}DenKr_plugin_roles;



#endif /* DENKR_ESSENTIALS__PLUGINS_PLUGIN_CODEGENERATION_H */
