/*
 * plugin_discovery.c
 *
 *  Created on: 26.07.2017 - 25.07.2018
 *      Author: Dennis Krummacker
 */


#define DENKR_ESSENTIALS__PLUGINS__PLUGIN_DISCOVERY_C
#define NO_DENKR_ESSENTIALS__PLUGINS__PLUGIN_DISCOVERY_C_FUNCTIONS

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
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/stat.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#include "../PreC/DenKr_PreC.h"
//#include "../DenKr_errno.h"
#include "DenKr_essentials/auxiliary.h"
#include "DenKr_essentials/Terminal/Terminal_Colors.h"
//#include "function_creator.h"
//#include "getRealTime.h"
//#include "Program_Files/P_Files_Path.h"
#include "plugin_management.h"
#include "plugin_discovery.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//






//static int DL_Libs_plugins_load_plugin(PluginManager* plugman, char* full_path, int full_path_len, char* plug_name, int plug_name_len){
static int DL_Libs_plugins_load_plugin(PluginManager* plugman, char* full_path, char* plug_name, int plug_name_len, char* testp){
	#define PRNT_INDENT printf("    ");
	int err=0;
	int i;

	void* libhandle = dlopen(full_path, RTLD_NOW);
	if(!libhandle){
		PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(red," ERROR:");printf(" Not able to load DSO:\n\t%s\n", dlerror());
        return DL_LIBS__ERR__NOT_LOADED;
	}

	int init_func_name_len = plug_name_len + sizeof(DENKR_PLUGIN_DISC_INIT_FUNC_PREFIX_STR);
	char init_func_name[init_func_name_len--];
	memcpy(init_func_name,DENKR_PLUGIN_DISC_INIT_FUNC_PREFIX_STR,sizeof(DENKR_PLUGIN_DISC_INIT_FUNC_PREFIX_STR)-1);
	memcpy(init_func_name+sizeof(DENKR_PLUGIN_DISC_INIT_FUNC_PREFIX_STR)-1,plug_name,plug_name_len);
	init_func_name[init_func_name_len]='\0';

	PluginInitFunc initfunc = (PluginInitFunc)(intptr_t) dlsym(libhandle, init_func_name);
	if(!initfunc){
		PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," ERROR:");printf(" While loading init function:\n\t%s\n", dlerror());
		dlclose(libhandle);
		return DL_LIBS__ERR__NO_INIT_FUNC;
	}

	plugman->err=malloc(sizeof(PluginManager_err));
	((PluginManager_err*)(plugman->err))->err=DENKR_PLUGMAN_ERR__NO_REGFUNC_CALLEDYET;//reset Plugman-Error. Check its value after Operation on the Plugman. See "plugin_management.h" for instructions
	int init_ret = initfunc(plugman);
	int returned_role=((PluginManager_err*)(plugman->err))->last_registered;
	err=((PluginManager_err*)(plugman->err))->err;
	free(plugman->err);
	plugman->err=NULL;
	//  Remark that 'dlfcn' returns a negative value if something went wrong.
	if(init_ret < 0){
		PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," ERROR:");printf(" Executing Plugin init_ function returned Error: %d  |  DenKr-Plugin-Manager Error-Code: %d\n", returned_role, ((PluginManager_err*)(plugman->err))->err);
		dlclose(libhandle);
		return DL_LIBS__ERR__NO_INIT_ERR;
	}
	//TODO: Here will then the Calls of the registration functions be inserted, after the rework mentioned in the Cloud-Textfile "DenKrement_ToDo.txt"
	//
	switch(err){
	case DENKR_PLUGMAN_ERR__NO_ERROR:
	case DENKR_PLUGMAN_ERR__GENERIC:
		err=0;
		break;
	case DENKR_PLUGMAN_ERR__REGPREDEF_BUTIS_GEN:
		PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," ERROR:");printf(" Tried to register as predefined Role, but with generic Role.\n");
		dlclose(libhandle);
		return DL_LIBS__ERR__NOT_LOADED;
		break;
	case DENKR_PLUGMAN_ERR__REGGEN_BUTIS_PREDEF:
		PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," ERROR:");printf(" Tried to register as generic Role Plugin, with a predefined Role Type.\n");
		dlclose(libhandle);
		return DL_LIBS__ERR__NOT_LOADED;
		break;
	case DENKR_PLUGMAN_ERR__INVALID_ROLENUM:
		PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," ERROR:");printf(" Library tried to register with an invalid (out of range) Role Number. I.e. not as generic and also out of domain-of-definition of the specified predefined Plugin Roles.\n");
		dlclose(libhandle);
		return DL_LIBS__ERR__NOT_LOADED;
		break;
	case DENKR_PLUGMAN_ERR__NO_REGFUNC_CALLEDYET:
		PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," ERROR:");printf(" While executing init function: No Registration called.\n");
		dlclose(libhandle);
		return DL_LIBS__ERR__NO_INIT_FUNC;
		break;
	case DENKR_PLUGMAN_ERR__UNDEFINED:
		PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(red," ERROR:");printf(" During Plugin Initialization (init_ function). Hmm, an explicitly stated \"UNDEFINED\" DenKr-PluginManager error was thrown. Very strange... OK, I just skip this file and we all hope that this was not caused by a general Framework Programming Bug...\n");
		dlclose(libhandle);
		return DL_LIBS__ERR__NOT_LOADED;
		break;
	default:
		PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(red," ERROR:");printf(" Plugin Initialization returned unknown DenKr-PluginManager-Error: %d\n", ((PluginManager_err*)(plugman->err))->err);
		dlclose(libhandle);
		return DL_LIBS__ERR__NO_INIT_ERR;
		break;
	}
	//- - - - - - - - - - - -
	//Now everything should be done correctly and initialized successfully.
	    //At last use the returned role, to record the generated Library-Handler into the PluginHandler inside the PluginManager
	if(returned_role==DenKr_plugin_role__generic){
		if(((plugman->PluginHandler)->generic_c)>0){
			struct PluginHandleGeneric* last;
			last=(plugman->PluginHandler)->generic;
			for(i=1;i<(plugman->PluginHandler)->generic_c;i++){
				last=last->next;
			}
			last->next=malloc(sizeof(struct PluginHandleGeneric));
			(last->next)->next=NULL;
			(last->next)->handle=libhandle;
			((plugman->PluginHandler)->generic_c)++;
		}else{
			(plugman->PluginHandler)->generic=malloc(sizeof(struct PluginHandleGeneric));
			((plugman->PluginHandler)->generic)->next=NULL;
			((plugman->PluginHandler)->generic)->handle=libhandle;
			((plugman->PluginHandler)->generic_c)++;
		}
	}else{
		((plugman->PluginHandler)->handles)[returned_role]=libhandle;
	}

	PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(green," Successfully");
	printf(" loaded Plugin-File:\n\t%s\n",full_path);
	return err;
	#undef PRNT_INDENT
}



//Pass it as Sub-Path (char *path_sub) a NULL and it uses just the Path-Prefix (char* path_pref)
//The lengths are really lengths, not sizeofs, i.e. without Null-Terminator (e.g. "abc" has a len of 3, not 4)
DENKR_DL_LIBS_PLUGIN_DISCOVER_FOLDER_SIGNATURE {
	#define PRNT_INDENT printf("    ");
	int err=0;
	int i;
	if(!path_pref){
		printfc(red,"ERROR:");printfc(DENKR__COLOR_ANSI__DL_LIBS," DL-Libs:");printf(" Bad Argument passed as path.\n");
		return FUNC_ERR_BAD_ARG;
	}

	char *dir_path;
	int dir_path_len;

	printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printf(" Loading Plugins (only considering \".so\"-Files)...\n");

	#define CREATE_PRINTABLE_ROLES_ARRAY		CREATE_argv_CONST(print_roles, CALL_MACRO_X_FOR_EACH__LIST(STRINGIFY,DenKr_plugin_roles_ENTRIES_) )
	CREATE_PRINTABLE_ROLES_ARRAY;
	#undef CREATE_PRINTABLE_ROLES_ARRAY
	printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printf(" Specific Roles provided by the Application:\n");
	for(i=0;i<DenKr_plugin_role__MAX;i++){
		printf("\t%s\n",print_roles[i]);
	}
	printf("  Specific Roles allowed by your License:\n");
	printf("\tTODO\n");
	puts("");

	PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printf(" Taking as Path-Prefix: %s\n",path_pref);

	DIR *dir=NULL;
	struct dirent *direntry;
	struct stat  ent_stat;

	if(path_sub){
		dir_path_len=path_pref_len+path_sub_len;
		dir_path=malloc(dir_path_len+1);
		memcpy(dir_path,path_pref,path_pref_len);
		memcpy(dir_path+path_pref_len,path_sub,path_sub_len);
		dir_path[dir_path_len]='\0';
	}else{
		dir_path_len=path_pref_len;
		dir_path=malloc(dir_path_len+1);
		memcpy(dir_path,path_pref,path_pref_len);
		dir_path[dir_path_len]='\0';
	}

	if((dir = opendir(dir_path)) == NULL){
		PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(red," ERROR:");printf(" Cannot open \"%s\".\n",path_pref);
		exit(1);
	}

	while( (direntry = readdir(dir)) != NULL ){
//		depr(1,"dir_path (%d) %s",dir_path_len,dir_path)
//		depr(1,"direntry->d_name (%d) %s",strlen(direntry->d_name),direntry->d_name)
		int ent_fullpath_len = dir_path_len+strlen(direntry->d_name);
		char ent_fullpath[ent_fullpath_len+1];
		memcpy(ent_fullpath,dir_path,dir_path_len);
		memcpy(ent_fullpath+dir_path_len,direntry->d_name,strlen(direntry->d_name));
		ent_fullpath[ent_fullpath_len]='\0';
//		depr(5,"%s",ent_fullpath)
	    if (stat(ent_fullpath, &ent_stat)) {
	    	PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(red," ERROR:");printf(" Couldn't get Dir-Entry stats: %s.\n",ent_fullpath);
	        exit(8);
	    }
	    if(ent_stat.st_mode & S_IFREG){
	    	// Directory Entry is a File
	    	// Now check, if it has a .so File-Extension
			char* lastdot;
//	    	for(lastdot=direntry->d_name;*lastdot!='\0';lastdot++){}//This isn't safe. Do it bounded
			lastdot=direntry->d_name;
			for(i=0;i<256;i++){
				if(*lastdot=='\0'){
					goto FileNameEndFound;
				}
				lastdot++;
			}
			PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," WARNING:");printf(" Malformed File-Name at Plugin-Loading. Skip File: %s.\n",direntry->d_name);
			goto SkipFile;
			FileNameEndFound:
			for(i=0;i<256;i++){
				lastdot--;
				if(lastdot<=(direntry->d_name)){//The '==' Case would represent a File with File-Extension but without Name, if than a dot where found. I.e. a File only named ".so". Won't accept such a File.
					PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," WARNING:");printf(" Malformed File-Name (only File-Extension or no File-Extension) at Plugin-Loading. Skip File: %s.\n",direntry->d_name);
					goto SkipFile;
				}
				if(*lastdot=='.')
					break;
			}
			if(strcmp(lastdot, ".so") != 0){
				PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(gray," Note:");printf(" File with Extension differing from \".so\" detected. Skip File: %s.\n",direntry->d_name);
				goto SkipFile;
			}
			int plug_name_len=lastdot-direntry->d_name;
			char plug_name[plug_name_len+1];
			memcpy(plug_name,direntry->d_name,plug_name_len);
			plug_name[plug_name_len]='\0';
//			err=DL_Libs_plugins_load_plugin(plugman,ent_fullpath,ent_fullpath_len,plug_name,plug_name_len);
			PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printf(" Tackling to load File as Module (Library/Thread): %s.\n",direntry->d_name);
			err=DL_Libs_plugins_load_plugin(plugman,ent_fullpath,plug_name,plug_name_len,dir_path);
			switch(err){
			case 0:
				//Successful, nothing further to do.
				break;
			case DL_LIBS__ERR__NOT_LOADED:
				PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," WARNING:");printf(" Tried, but couldn't load Library. Skip File: %s.\n",direntry->d_name);
				goto SkipFile;
				break;
			case DL_LIBS__ERR__NO_INIT_FUNC:
				PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," WARNING:");printf(" Library supplied no init_ function. Skip File: %s.\n",direntry->d_name);
				goto SkipFile;
				break;
			case DL_LIBS__ERR__NO_REGISTER_FUNC:
				PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," WARNING:");printf(" Library supplied no proper init_ function (Plugin-Registration Function missing). Skip File: %s.\n",direntry->d_name);
				goto SkipFile;
				break;
			case DL_LIBS__ERR__NO_INIT_ERR:
				PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(yellow," WARNING:");printf(" init_ function of Library has thrown an Error. Skip File: %s.\n",direntry->d_name);
				goto SkipFile;
				break;
			default:
				PRNT_INDENT printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printfc(red," BUG:");printf(" Strange... Encountered a not caught return-Value from plugin-loading...\n");
				break;
			}
	    }else if(ent_stat.st_mode & S_IFDIR){
	    	// Directory Entry is a Directory
	    	// Maybe add the option to go recursive over Subfolders.
	    }
	    SkipFile:
		;
	}

	puts("");
	printfc(DENKR__COLOR_ANSI__DL_LIBS,"DL-Libs:");printf(" Loaded following Plugin-Roles from Subfolder: %s\n",path_sub);
	for(i=0;i<DenKr_plugin_role__MAX;i++){
		if( FLAG_CHECK((plugman->predef)[i].flags,DENKR_PLUGINS_ROLE_FLAG__ROLE_DEFINED) ){
//			printf("\t%s -->  File: %s\n",print_roles[i], "TODO");
			printf("\t%s\n",print_roles[i]);
		}
	}

	if(dir_path)
//		free(dir_path);
	closedir(dir);
	return err;
	#undef PRNT_INDENT
}




#endif
#undef DENKR_ESSENTIALS__PLUGINS__PLUGIN_DISCOVERY_C
#undef NO_DENKR_ESSENTIALS__PLUGINS__PLUGIN_DISCOVERY_C_FUNCTIONS
