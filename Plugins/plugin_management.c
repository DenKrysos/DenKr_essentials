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
#include "plugin_management.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//


#define WRITE_PLUGMAN_ERR(ERR,PLUGNUM) \
	if(plugman->err){\
		((PluginManager_err*)(plugman->err))->err=ERR;\
		((PluginManager_err*)(plugman->err))->last_registered=PLUGNUM;\
	}else{\
		printfc(red,"ERROR:");printf(" Intended to write into Plugman.err, but that wasn't initialized, which it should be in that place... (File: %s | Line: %d) Please fix it. Exiting...\n",__FILE__,__LINE__);\
		exit(STRUCT_ERR_DMG);\
	}


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
	(*plugman)->err=NULL;
	PluginHandler_init(&((*plugman)->PluginHandler));
}


//TODO: DoubleCheck. Did I forget to free the malloced "role"&"work_type_generic" for generic plugins? I think so...
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


DENKR_PLUGIN_MANAGER_REM_LAST_GENERIC
{
	int i;
	if(1<plugman->generic_c){
		struct PluginRoleGeneric* oneBeforeLast;
		oneBeforeLast=plugman->generic;
		for(i=2;i<plugman->generic_c;i++){
			oneBeforeLast=oneBeforeLast->next;
		}
		if((oneBeforeLast->next)->role)
			free((oneBeforeLast->next)->role);
		if((oneBeforeLast->next)->work_type_generic)
			free((oneBeforeLast->next)->work_type_generic);
		free((oneBeforeLast->next));
		oneBeforeLast->next=NULL;
		plugman->generic_c--;
	}else if(0<plugman->generic_c){//Here it is exactly 1. We have to restore the "Initial Case", i.e. empty linked list and thus handle the "first" entry
		struct PluginRoleGeneric* last;
		last=plugman->generic;
		if(last->role)
			free(last->role);
		if(last->work_type_generic)
			free(last->work_type_generic);
		free(plugman->generic);
		plugman->generic_c=0;
	}else if(-1<plugman->generic_c){//Exactly 0. Nothing to do
	}else{//Lower than 0. Must be an error.
		printfc(red,"ERROR:");printf(" Bug detected. During Removing of an entry from the generic plugins Linked List. Malformed Data-Structure detected. Nothing to do about it. Exit...\n");
		exit(STRUCT_ERR_DMG);
	}
}




DENKR_PLUGIN_MANAGER_REG_ROLE_PREDEF
{
#define ROLEENTRIES_FIRST ARRAY_ENTRY(0,(DenKr_plugin_roles_ENTRIES_))
#define ROLEENTRIES_LAST ARRAY_ENTRY(DEC(COUNT_VARARGS(DenKr_plugin_roles_ENTRIES_)),(DenKr_plugin_roles_ENTRIES_))
	//Plausibility Checks
	//Check if role is generic
	if(role==DenKr_plugin_role__generic){
		WRITE_PLUGMAN_ERR(DENKR_PLUGMAN_ERR__REGPREDEF_BUTIS_GEN,DenKr_plugin_role__MAX)
		return;
	}else if(ROLEENTRIES_FIRST>role || ROLEENTRIES_LAST<role){
		WRITE_PLUGMAN_ERR(DENKR_PLUGMAN_ERR__INVALID_ROLENUM,DenKr_plugin_role__MAX)
		return;
	}
	WRITE_PLUGMAN_ERR(DENKR_PLUGMAN_ERR__NO_ERROR,role)

	//Actual Registration
	FLAG_SET((plugman->predef)[role].flags,DENKR_PLUGINS_ROLE_FLAG__ROLE_DEFINED);
	(plugman->predef)[role].work_type=work_type;
	(plugman->predef)[role].hook=hook;
#undef ROLEENTRIES_FIRST
#undef ROLEENTRIES_LAST
}




//ToDo: Pass back the number of the registered Plugin (i.e. the position inside the linked list)
DENKR_PLUGIN_MANAGER_REG_ROLE_GENERIC
{
	int i;

	//First, check if the Role Number is 'generic'. That's all we have to check here. If that is not true, everything else is of no significance, since that just is the error. If it's generic, it is fine, since this only one valid value.
	if(roletype!=DenKr_plugin_role__generic){
		WRITE_PLUGMAN_ERR(DENKR_PLUGMAN_ERR__REGGEN_BUTIS_PREDEF,DenKr_plugin_role__MAX)
		return;
	}
	WRITE_PLUGMAN_ERR(DENKR_PLUGMAN_ERR__NO_ERROR,roletype)

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
