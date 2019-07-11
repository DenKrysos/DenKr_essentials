/*
 * plugin_management.c
 *
 *  Created on: 26.07.2017 - 25.07.2018
 *      Author: Dennis Krummacker
 */





#define DENKR_ESSENTIALS__PLUGINS__PLUGIN_MANAGEMENT_C
#define NO_DENKR_ESSENTIALS__PLUGINS__PLUGIN_MANAGEMENT_C_FUNCTIONS

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
//#include <global/global_settings.h>
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
#include <stdlib.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#include "../PreC/DenKr_PreC.h"
//#include "../DenKr_errno.h"
#include "../auxiliary.h"
//#include "function_creator.h"
//#include "getRealTime.h"
//#include "Program_Files/P_Files_Path.h"
#include "DenKr_essentials/Plugins/plugin_management.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//



static void PluginHandler_init(PluginHandler** plughan) {
	*plughan = malloc(sizeof(**plughan));
	int temp_mem_size=DenKr_plugin_role__MAX*sizeof(*((*plughan)->handles));
	(*plughan)->handles=malloc(temp_mem_size);
	memset((*plughan)->handles,0,temp_mem_size);
	(*plughan)->generic_c=0;
	(*plughan)->generic=NULL;
}


static void PluginHandler_free(PluginHandler** plughan) {
	int i;

	if((*plughan)->handles){
		free((*plughan)->handles);
	}

	struct PluginHandleGeneric* tempp=(*plughan)->generic;
	struct PluginHandleGeneric* tempp_n=NULL;
	for(i=0;i<(*plughan)->generic_c;i++){
		tempp_n=tempp->next;
		free(tempp);
		tempp=tempp_n;
	}

	free(*plughan);
	*plughan=NULL;
}





DENKR_PLUGIN_MANAGER_INIT_SIGNATURE {
	*plugman = malloc(sizeof(**plugman));
	int temp_mem_size=DenKr_plugin_role__MAX*sizeof(*((*plugman)->predef));
	(*plugman)->predef=malloc(temp_mem_size);
	memset((*plugman)->predef,0,temp_mem_size);
	(*plugman)->generic_c=0;
	(*plugman)->generic=NULL;
	PluginHandler_init(&((*plugman)->PluginHandler));
}


DENKR_PLUGIN_MANAGER_FREE_SIGNATURE {
	PluginHandler_free(&((*plugman)->PluginHandler));
	if((*plugman)->predef){
		free((*plugman)->predef);
	}

	struct PluginRoleGeneric* tempp=(*plugman)->generic;
	struct PluginRoleGeneric* tempp_n=NULL;
	while(tempp){
		tempp_n=tempp->next;
		free(tempp);
		tempp=tempp_n;
	}

	free(*plugman);
	*plugman=NULL;
}




DENKR_PLUGIN_MANAGER_REG_ROLE_PREDEF
{
	FLAG_SET((plugman->predef)[role].flags,DENKR_PLUGINS_ROLE_FLAG__ROLE_DEFINED);
	(plugman->predef)[role].work_type=work_type;
	(plugman->predef)[role].hook=hook;
}




DENKR_PLUGIN_MANAGER_REG_ROLE_GENERIC
{
	int i;
	struct PluginRoleGeneric* current;
	if(plugman->generic_c > 0){
		struct PluginRoleGeneric* last;
		last=plugman->generic;
		for(i=1;i<plugman->generic_c;i++){
			last=last->next;
		}
		last->next=malloc(sizeof(struct PluginRoleGeneric));
		plugman->generic_c++;
		current = last->next;
	}else{
		plugman->generic = malloc(sizeof(struct PluginRoleGeneric));
		plugman->generic_c = 1;
		current = plugman->generic;
	}
	memset(current,0,sizeof(struct PluginRoleGeneric));
	//
	FLAG_SET(current->flags,DENKR_PLUGINS_ROLE_FLAG__ROLE_GENERIC);
	int templen;
	if(role){
//		templen=strlen(role);
//		current->role=malloc(templen);
//		memcpy(current->role,role,templen);
//		(current->role)[templen]='\0';
		current->role=malloc(role_size);
		memcpy(current->role,role,role_size);
	}
	current->work_type=work_type;
	if(work_type_generic){
		templen=strlen(work_type_generic);
		current->work_type_generic=malloc(templen);
		memcpy(current->work_type_generic,work_type_generic,templen);
		((char*)(current->work_type_generic))[templen]='\0';
	}
	current->interComm_method=interComm_method;
//	current->ThreadID=-1;
	current->hook=hook;
}








#endif
#undef DENKR_ESSENTIALS__PLUGINS__PLUGIN_MANAGEMENT_C
#undef NO_DENKR_ESSENTIALS__PLUGINS__PLUGIN_MANAGEMENT_C_FUNCTIONS
