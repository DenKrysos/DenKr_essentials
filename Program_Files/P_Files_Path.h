#ifndef DENKR_ESSENTIALS_PROGRAM_FILES_P_FILES_PATH_H
#define DENKR_ESSENTIALS_PROGRAM_FILES_P_FILES_PATH_H




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
//#include "./global/global_variables.h"
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
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
//#include "DenKr_essentials/auxiliary.h"
#include "../DenKr_errno.h"
//#include "nl80211.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//


//TODO:
// In the last case (i.e. when the called parameter argv[0] is a plain word -> Search $PATH for the executable
// - Do char* PATH = getenv("PATH");  <-- gives you a string containing all systems paths seperated by ':'
// - Take every single path, do the <DIR *dir=NULL;struct dirent *direntry;struct stat  ent_stat;> stuff to search in every folder for the exe



//Convention in all of my Programs:
// A String HAS a trailing '/', if and only if it is a path
// A String HAS a preceding '/', if and only if it is a Full-Path (Absolute Path)
// A String has NO preceding '/', if it is a Sub-Path
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// This declares implicit:
// A Sub-Path has NO preceding '/', but a trailing '/'
// A File has NO trailing '/'
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Used for Accessing Files or Paths are almost always Full/Absolute Paths
//      e.g. /etc/ProgramName/SubFolderA/cfg/config.conf
//           /home/User/Storage/SubFolder/Screenshot/scrsht001.png
//           /home/root/documents/SubFolder/
// This makes it nearly Fail-safe and avoids relative Addressing-Failures

//Example for a Full-Path
//        /DirA/DirB/
//Example for a Sub-Path
//        DirA/DirB/
//Example for a File with a Full-Path
//        /DirA/DirB/FileName (an Extension is optional)

//Further Path Notation Rules:
// If it starts with a '/', i.e. does not start with a './', it is still a Lookup-Name
// If it starts with './', than it is an actual Filesystem-Path.






//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Parameters & Values  -----------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
// These can be found inside "DenKr_essentials/global_settings_values.h"
// There it also covers some Information about Format and Usage (additionally to the ones given here).
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
//----  Program Path  ------------------------------------------------------------------------------//
//----  	The Path to the actual Program ---------------------------------------------------------//
//----  	(where the executable and other Program-Files, like DLLs are saved  --------------------//
//----  Storage Files Path  ------------------------------------------------------------------------//
//----  	Config-File(s), etc.  ------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
			#define __PROGRAM_NAME_SOMETHING_MISSING_OR_WRONG_ERROR ;ERROR;"ERROR at COMPILATION/Macro-Expansion: Set the Parameters 'PROGRAM_NAME_VAR_AVAILABILITY' inside a File './global/global_settings.h' with Values from './DenKr_essentials/Program_Files/P_Files_Path.h'"
			#define __STORAGE_FILES_PATH_LOCATION_SOMETHING_MISSING_OR_WRONG_ERROR ;ERROR;"ERROR at COMPILATION/Macro-Expansion: Set the Parameters 'STORAGE_FILES_PATH_LOCATION' & 'STORAGE_FILES_PATH_VAR_AVAILABILITY' inside a File './global/global_settings.h' with Values from './DenKr_essentials/Program_Files/P_Files_Path.h'"
			#define __PROGRAM_FILES_PATH_LOCATION_SOMETHING_MISSING_OR_WRONG_ERROR ;ERROR;"ERROR at COMPILATION/Macro-Expansion: Set the Parameter 'PROGRAM_PATH_VAR_AVAILABILITY' inside a File './global/global_settings.h' with Values from './DenKr_essentials/Program_Files/P_Files_Path.h'"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//NOTE: The initial arguments, that are given to the program at Terminal-Call should be
//globally stored in "argvg". (This is done, if you call DenKr_essentials_Init(argc,argv); at Program-Start.
//This means, you are able to call this Macro everywhere like "CREATE_PROGRAM_PATH(*argvg);"
//So a Usage-Example:
//		CREATE_PROGRAM_NAME(*argvg);
//		CREATE_PROGRAM_PATH(*argvg);
//		CREATE_STORAGE_FILES_PATH(*argvg);
//		CREATE_COMPLETE_FOLDER_PATH(StorageFilesPath);
// (If you decide to let the Program Arguments (argc, argv) not beeing available globally,
// (you obviously have to take care off carrying it over somehow)
// (Not a big Deal, but remember, that you have to...)
// ----------------
// Steps to create the Program-Path
// - If argv[0] starts with "/" (absolute path) this is the path.
// - Otherwise if argv[0] contains "/" (relative path) append it to cwd (assuming it hasn't been changed yet).
// - Otherwise search directories in $PATH for executable argv[0].
// Afterwards it may be reasonable to check whether the executable isn't actually a symlink. If it is resolve it relative to the symlink directory.
// This step is not necessary in /proc method (at least for Linux). There the proc symlink points directly to executable.
// Note that it is up to the calling process to set argv[0] correctly. It is right most of the times however there are occasions when the calling process cannot be trusted (ex. setuid executable).
//  -  -  -  -  -  -  -
// Alternative approach: (You could try to do this and if this fails, go over to the previous one)
//  On Unixes with /proc really straight and realiable way is to:
//  - readlink("/proc/self/exe", buf, bufsize) (Linux)
//  - readlink("/proc/curproc/file", buf, bufsize) (FreeBSD)
//  - readlink("/proc/self/path/a.out", buf, bufsize) (Solaris)
//  -  -  -  -  -  -  -
// NOTE: The cwd (Current Working Dir) returned by 'getcwd()' does not come with a trailing '/'
///////////////////////////////////////////////////////////////////
	//----  Program Name  -----------------------------------------
///////////////////////////////////////////////////////////////////
#if (PROGRAM_NAME_VAR_AVAILABILITY == PROGRAM_NAME_VAR_AVAILABILITY___GLOBAL)
			#define CREATE_PROGRAM_NAME(arg) \
				{ \
				char *posb, *pose; \
				for(pose=arg;*pose!='\0';pose++){} \
				for(posb=pose;*posb!='/';posb--){} \
				posb++; \
				ProgramName_length = pose-posb; \
				ProgramName=malloc(ProgramName_length+1); \
				memcpy(ProgramName,posb,ProgramName_length); \
				} \
				ProgramName[ProgramName_length]='\0';
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif (PROGRAM_NAME_VAR_AVAILABILITY == PROGRAM_NAME_VAR_AVAILABILITY___SINGLE)
			#define CREATE_PROGRAM_NAME(arg) \
				int ProgramName_length; \
				{ \
				char *posb, *pose; \
				for(pose=arg;*pose!='\0';pose++){} \
				for(posb=pose;*posb!='/';posb--){} \
				ProgramName_length = pose-posb-1; \
				} \
				char ProgramName[ProgramName_length+1]; \
				{ \
				char *posb, *pose; \
				for(pose=arg;*pose!='\0';pose++){} \
				for(posb=pose;*posb!='/';posb--){} \
				posb++; \
				memcpy(ProgramName,posb,ProgramName_length); \
				} \
				ProgramName[ProgramName_length]='\0';
#else
	#define CREATE_PROGRAM_NAME(...) \
		__PROGRAM_NAME_SOMETHING_MISSING_OR_WRONG_ERROR
#endif
//----------------------------------------------------------------------------------------------------------------------------------------
	//----  Program Name  ----------------------------------------------------------------------------------------------------------------
	//----     (For Reusing the Macro, no matter if global or single and getting sure, that the variable is available at this point  -----
//----------------------------------------------------------------------------------------------------------------------------------------
#if (PROGRAM_NAME_VAR_AVAILABILITY == PROGRAM_NAME_VAR_AVAILABILITY___GLOBAL)
			#define CREATE_PROGRAM_NAME_REUSE(arg)
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif (PROGRAM_NAME_VAR_AVAILABILITY == PROGRAM_NAME_VAR_AVAILABILITY___SINGLE)
			#define CREATE_PROGRAM_NAME_REUSE(arg) CREATE_PROGRAM_NAME(arg)
#else
	#define CREATE_PROGRAM_NAME_REUSE(...) \
		__PROGRAM_NAME_SOMETHING_MISSING_OR_WRONG_ERROR
#endif
///////////////////////////////////////////////////////////////////
	//----  Program Path  -----------------------------------------
///////////////////////////////////////////////////////////////////
#if (PROGRAM_PATH_VAR_AVAILABILITY == PROGRAM_PATH_VAR_AVAILABILITY___GLOBAL)
			#define CREATE_PROGRAM_PATH(arg) \
				if(*arg == '/'){ \
					{ \
					char *pos; \
					for(pos=arg;*pos!='\0';pos++){} \
					for(;*pos!='/';pos--){} \
					ProgPath_length = pos-arg+1; \
					} \
					ProgPath=malloc(ProgPath_length+1); \
					memcpy(ProgPath,arg,ProgPath_length); \
					ProgPath[ProgPath_length]='\0'; \
				}else if(strstr(arg,"/")){ \
					char cwd[PATH_MAX]; \
					if(getcwd(cwd, sizeof(cwd)) != NULL) { \
						printfc(yellow,"Current working dir:\n");printf("%s\n",cwd); \
					} else { \
						perror("getcwd() error"); \
						exit(MAIN_ERR_BAD_RUN); \
					} \
					int cwdlen=strlen(cwd); \
					char* callp=arg; \
					if(*arg == '.'){ \
						callp++; \
					} \
					char *endPos; \
					for(endPos=callp;*endPos!='\0';endPos++){} \
					for(;*endPos!='/';endPos--){} \
					int calllen=0; \
					if(callp!=endPos){ \
						calllen=endPos-callp+1; \
					} \
					ProgPath_length=cwdlen+1+calllen; \
					ProgPath=malloc(ProgPath_length+1); \
					memcpy(ProgPath,cwd,cwdlen); \
					ProgPath[cwdlen]='/'; \
					if(callp!=endPos){ \
						memcpy(ProgPath+cwdlen+1,callp,calllen); \
					} \
					ProgPath[ProgPath_length]='\0'; \
				}else{ \
					printfc(red,"Error");printf("(while ascertaining ProgramPath): Case not implemented yet. I should examine $PATH here. Exiting...\n"); \
					exit(MAIN_ERR_BAD_RUN); \
				}
						//Old Version:
								//#define CREATE_PROGRAM_PATH(arg) \
								//	{ \
								//	char *pos; \
								//	for(pos=arg;*pos!='\0';pos++){} \
								//	for(;*pos!='/';pos--){} \
								//	ProgPath_length = pos-arg+1; \
								//	} \
								//	ProgPath=malloc(ProgPath_length+1); \
								//	memcpy(ProgPath,arg,ProgPath_length); \
								//	ProgPath[ProgPath_length]='\0';
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif (PROGRAM_PATH_VAR_AVAILABILITY == PROGRAM_PATH_VAR_AVAILABILITY___SINGLE)
			#define CREATE_PROGRAM_PATH(arg) \
				int ProgPath_length; \
				char ProgPath[ProgPath_length+1]; \
				if(*arg == '/'){ \
					{ \
					char *pos; \
					for(pos=arg;*pos!='\0';pos++){} \
					for(;*pos!='/';pos--){} \
					ProgPath_length = pos-arg+1; \
					} \
				}else if(strstr(arg,"/")){ \
					char cwd[PATH_MAX]; \
					if(getcwd(cwd, sizeof(cwd)) != NULL) { \
						printfc(yellow,"Current working dir:\n");printf("%s\n",cwd); \
					} else { \
						perror("getcwd() error"); \
						exit(MAIN_ERR_BAD_RUN); \
					} \
					int cwdlen=strlen(cwd); \
					char* callp=arg; \
					if(*arg == '.'){ \
						callp++; \
					} \
					char *endPos; \
					for(endPos=callp;*endPos!='\0';endPos++){} \
					for(;*endPos!='/';endPos--){} \
					int calllen=endPos-callp+1; \
					ProgPath_length=cwdlen+1+calllen; \
				}else{ \
					printfc(red,"Error");printf("(while ascertaining ProgramPath): Case not implemented yet. I should examine $PATH here. Exiting...\n"); \
					exit(MAIN_ERR_BAD_RUN); \
				} \
				char ProgPath[ProgPath_length+1]; \
				if(*arg == '/'){ \
					memcpy(ProgPath,arg,ProgPath_length); \
					ProgPath[ProgPath_length]='\0'; \
				}else if(strstr(arg,"/")){ \
					memcpy(ProgPath,cwd,cwdlen); \
					ProgPath[cwdlen]='/'; \
					if(callp!=endPos){ \
						memcpy(ProgPath+cwdlen+1,callp,calllen); \
					} \
					ProgPath[ProgPath_length]='\0'; \
				}
						//Old Version:
								//#define CREATE_PROGRAM_PATH(arg) \
								//	int ProgPath_length; \
								//	{ \
								//	char *pos; \
								//	for(pos=arg;*pos!='\0';pos++){} \
								//	for(;*pos!='/';pos--){} \
								//	ProgPath_length = pos-arg+1; \
								//	} \
								//	char ProgPath[ProgPath_length+1]; \
								//	memcpy(ProgPath,arg,ProgPath_length); \
								//	ProgPath[ProgPath_length]='\0';
#else
	#define CREATE_PROGRAM_PATH(...) \
		__PROGRAM_PATH_SOMETHING_MISSING_OR_WRONG_ERROR
#endif
//----------------------------------------------------------------------------------------------------------------------------------------
	//----  Program Path  ----------------------------------------------------------------------------------------------------------------
	//----     (For Reusing the Macro, no matter if global or single and getting sure, that the variable is available at this point  -----
//----------------------------------------------------------------------------------------------------------------------------------------
#if (PROGRAM_PATH_VAR_AVAILABILITY == PROGRAM_PATH_VAR_AVAILABILITY___GLOBAL)
			#define CREATE_PROGRAM_PATH_REUSE(arg)
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif (PROGRAM_PATH_VAR_AVAILABILITY == PROGRAM_PATH_VAR_AVAILABILITY___SINGLE)
			#define CREATE_PROGRAM_PATH_REUSE(arg) CREATE_PROGRAM_PATH(arg)
#else
	#define CREATE_PROGRAM_PATH_REUSE(...) \
		__PROGRAM_PATH_SOMETHING_MISSING_OR_WRONG_ERROR
#endif
///////////////////////////////////////////////////////////////////
	//----  Storage Files Path  -----------------------------------
///////////////////////////////////////////////////////////////////
#if (STORAGE_FILES_PATH_VAR_AVAILABILITY == STORAGE_FILES_PATH_VAR_AVAILABILITY___GLOBAL)
			#if(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___PROJECT)
				#define CREATE_STORAGE_FILES_PATH(arg) \
					{ \
					/* int StorageFilesPath_length; */ \
					char *pos; \
					for(pos=arg;*pos!='\0';pos++){} \
					for(;*pos!='/';pos--){} \
					StorageFilesPath_length = pos-arg+1; \
					StorageFilesPath=malloc(StorageFilesPath_length+1); \
					memcpy(StorageFilesPath,arg,StorageFilesPath_length); \
					StorageFilesPath[StorageFilesPath_length]='\0'; \
					}
			#elif(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___SYSTEM)
				/* TODO: Check this, maybe it could be buggy. I changed it a lot, totally without testing it even a single time */
				/* And to be honest, i didn't do the changes very attentive xD. I invested more effort into this comment here... xP */
				#define CREATE_STORAGE_FILES_PATH(arg) \
					{ \
						char *tmppath; \
						if ((tmppath = getenv("XDG_CONFIG_HOME")) == NULL) { \
							if ((tmppath = getenv("HOME")) == NULL) { \
								tmppath = getpwuid(getuid())->pw_dir; \
							} \
						} \
						/* len=strlen(Ascertained_Path)+strlen("\ollerus\")+'\0' */ \
						StorageFilesPath_length=(strlen(tmppath)+strlen(ProgramName)+1); \
						StorageFilesPath=malloc(StorageFilesPath_length+1); \
						memcpy(StorageFilesPath,tmppath,strlen(tmppath)+1); \
						snprintf(StorageFilesPath+strlen(tmppath),ProgramName_length+3,"%s%s%s","/",ProgramName,"/"); \
						StorageFilesPath[sizeof(StorageFilesPath)]='\0'; \
					}
			#elif(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___LOCAL_USER_SPECIFIC)
				/* TODO */
			#elif(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___LOCAL_ALL_USERS)
				#define CREATE_STORAGE_FILES_PATH(arg) \
					StorageFilesPath=malloc((StorageFilesPath_length=(ProgramName_length+sizeof("/etc//")))); \
					snprintf(StorageFilesPath,StorageFilesPath_length,"/etc/%s/",ProgramName); \
					StorageFilesPath_length--;
			#elif(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___MANUAL)
				#define CREATE_STORAGE_FILES_PATH(arg) \
					if(STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH[sizeof(STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH)-2] == '/'){ \
						StorageFilesPath_length = ProgramName_length+sizeof(STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH); \
						StorageFilesPath = (char*)malloc(StorageFilesPath_length); \
						snprintf(StorageFilesPath,StorageFilesPath_length,"%s%s/",STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH,ProgramName); \
					} else{\
						StorageFilesPath_length = ProgramName_length+sizeof(STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH)+1; \
						StorageFilesPath = (char*)malloc(StorageFilesPath_length); \
						snprintf(StorageFilesPath,StorageFilesPath_length+1,"%s/%s/",STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH,ProgramName); \
					}
			#elif(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___MANUAL_FUNCTION)
				#define CREATE_STORAGE_FILES_PATH(arg) \
					int storage_files_path_location_manual_function(arg);
			#else
				#define CREATE_STORAGE_FILES_PATH(...) \
					__STORAGE_FILES_PATH_LOCATION_SOMETHING_MISSING_OR_WRONG_ERROR
			#endif //The 'STORAGE_FILES_PATH_LOCATION___UNDEFINED' is intentionally not performed, so that it drops into the '#else' case
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif (STORAGE_FILES_PATH_VAR_AVAILABILITY == STORAGE_FILES_PATH_VAR_AVAILABILITY___SINGLE)
			#if(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___PROJECT)
				#define CREATE_STORAGE_FILES_PATH(arg) \
					int StorageFilesPath_length; \
					{ \
					char *pos; \
					for(pos=arg;*pos!='\0';pos++){} \
					for(;*pos!='/';pos--){} \
					StorageFilesPath_length = pos-arg+1; \
					} \
					char StorageFilesPath[StorageFilesPath_length+1]; \
					memcpy(StorageFilesPath,arg,StorageFilesPath_length); \
					StorageFilesPath[StorageFilesPath_length]='\0';
			#elif(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___SYSTEM)
				#define CREATE_STORAGE_FILES_PATH(arg) \
					int StorageFilesPath_length; \
					{ \
						char *tmppath; \
						if ((tmppath = getenv("XDG_CONFIG_HOME")) == NULL) { \
							if ((tmppath = getenv("HOME")) == NULL) { \
								tmppath = getpwuid(getuid())->pw_dir; \
							} \
						} \
						/* len=strlen(Ascertained_Path)+strlen("\ollerus\")+'\0' */ \
						StorageFilesPath_length=(strlen(tmppath)+10); \
					} \
					char StorageFilesPath[StorageFilesPath_length]; \
					{ \
						char *tmppath; \
						if ((tmppath = getenv("XDG_CONFIG_HOME")) == NULL) { \
							if ((tmppath = getenv("HOME")) == NULL) { \
								tmppath = getpwuid(getuid())->pw_dir; \
							} \
						} \
						memcpy(StorageFilesPath,tmppath,strlen(tmppath)+1); \
						snprintf(StorageFilesPath+strlen(tmppath),ProgramName_length+3,"%s%s%s","/",ProgramName,"/"); \
						StorageFilesPath[sizeof(StorageFilesPath)]='\0'; \
					}
			#elif(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___LOCAL_USER_SPECIFIC)
				/* TODO */
			#elif(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___LOCAL_ALL_USERS)
				#define CREATE_STORAGE_FILES_PATH(arg) \
					/* char StorageFilesPath[]="/etc/"PROGRAM_NAME"/"; */ \
					int StorageFilesPath_length; \
					StorageFilesPath_length = ProgramName_length+sizeof("/etc//"); \
					char StorageFilesPath[StorageFilesPath_length]; \
					snprintf(StorageFilesPath,StorageFilesPath_length,"/etc/%s/",ProgramName); \
					StorageFilesPath_length--;
			#elif(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___MANUAL)
				#define CREATE_STORAGE_FILES_PATH(arg) \
					int StorageFilesPath_length; \
					if(STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH[sizeof(STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH)-2] == '/'){ \
						StorageFilesPath_length = ProgramName_length+sizeof(STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH); \
					} else{\
						StorageFilesPath_length = ProgramName_length+sizeof(STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH)+1; /* aggregate +2 (see below) for the second "/" in this case */ \
					} \
					char StorageFilesPath[StorageFilesPath_length+1]; /* +1 for the "/" */ \
					if(STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH[sizeof(STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH)-2] == '/'){ \
						snprintf(StorageFilesPath,StorageFilesPath_length+1,"%s%s%s",STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH,ProgramName,"/"); \
					} else{\
						snprintf(StorageFilesPath,StorageFilesPath_length+1,"%s%s%s%s",STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH,"/",ProgramName,"/"); \
					}
			#elif(STORAGE_FILES_PATH_LOCATION == STORAGE_FILES_PATH_LOCATION___MANUAL_FUNCTION)
				#define CREATE_STORAGE_FILES_PATH(arg) \
					//TODO
			#else
				#define CREATE_STORAGE_FILES_PATH(...) \
					__STORAGE_FILES_PATH_LOCATION_SOMETHING_MISSING_OR_WRONG_ERROR
			#endif //The 'PROG_PATH_LOCATION___UNDEFINED' is intentionally not performed, so that it drops into the '#else' case
#else
	#define CREATE_STORAGE_FILES_PATH(...) \
		__STORAGE_FILES_PATH_LOCATION_SOMETHING_MISSING_OR_WRONG_ERROR
#endif
//----------------------------------------------------------------------------------------------------------------------------------------
	//----  Storage Files Path  ----------------------------------------------------------------------------------------------------------
	//----     (For Reusing the Macro, no matter if global or single and getting sure, that the variable is available at this point  -----
//----------------------------------------------------------------------------------------------------------------------------------------
#if (STORAGE_FILES_PATH_VAR_AVAILABILITY == STORAGE_FILES_PATH_VAR_AVAILABILITY___GLOBAL)
			#define CREATE_STORAGE_FILES_PATH_REUSE(arg)
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#elif (STORAGE_FILES_PATH_VAR_AVAILABILITY == STORAGE_FILES_PATH_VAR_AVAILABILITY___SINGLE)
			#define CREATE_STORAGE_FILES_PATH_REUSE(arg) CREATE_STORAGE_FILES_PATH(arg)
#else
	#define CREATE_STORAGE_FILES_PATH_REUSE(...) \
		__STORAGE_FILES_PATH_LOCATION_SOMETHING_MISSING_OR_WRONG_ERROR
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//
/*Everything is in a scope*/
/*Give this Macro a string with the preceding '/' after the last folder*/
/*This is IMPORTANT or the last folder isn't created*/
/*Example: "/folderA/folderB/folderC/"  */
#define CREATE_COMPLETE_FOLDER_PATH(path) { \
	int pathloop; \
	struct stat st = {0}; \
	char temppath[strlen(path)]; \
	memset(temppath,0,sizeof(temppath)); \
	for(pathloop=1;pathloop<strlen(path);pathloop++){ \
		if(path[pathloop]=='/'){ \
			memcpy(temppath,path,pathloop); \
			/*temppath[pathloop]='\0';*/ \
			if (stat(temppath, &st) == -1) { \
				mkdir(temppath,S_IRWXU|S_IRWXG|S_IRWXO); \
			} \
		} \
	} \
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////








#endif /* DENKR_ESSENTIALS_PROGRAM_FILES_P_FILES_PATH_H */
