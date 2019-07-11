/*
 * global_settings_values.h
 *
 *  Created on: 25.07.2017
 *      Author: Dennis Krummacker
 */

#ifndef DENKR_ESSENTIALS_GLOBAL_SETTINGS_VALUES_H
#define DENKR_ESSENTIALS_GLOBAL_SETTINGS_VALUES_H







//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Global Variables  --------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
#define PROGRAM_ARGUMENTS_GLOBAL_AVAILABILITY___UNDEFINED 0
#define PROGRAM_ARGUMENTS_GLOBAL_AVAILABILITY___NOT_AVAILABLE 1
#define PROGRAM_ARGUMENTS_GLOBAL_AVAILABILITY___AVAILABLE 2

//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////









//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Paths for Program/Storage Files  -----------------------------------------------------------//
//----  See: "DenKr_essentials/Program_Files/P_Files_Path.h"  ----------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
    ///////////////////////////////////////////////////////////////
	//----  Parameters  -------------------------------------------
	//----  Define these inside './global/global_settings.h'  -----
///////////////////////////////////////////////////////////////////
//											//		#define PROGRAM_NAME "ProgramName"
//											//					--> As a string. Not used anymore. The Program-Name is read out from the Executable-Name after startup
//		#define STORAGE_FILES_PATH_LOCATION PROG_PATH_LOCATION___UNDEFINED
//					--> As one Value from below
//		#define STORAGE_FILES_PATH_VAR_AVAILABILITY
//					--> As one Value from below
//		#define STORAGE_FILES_PATH_ABSOLUTE_MANUAL_PATH
//					--> If chosen MANUAL as PATH_LOCATION, you define here your wished Path as a string, including the succeeding '/' (more Info see below)
//----------------------------------------------------------------------------------------------------------------------------------//
//		#define PROGRAM_NAME_VAR_AVAILABILITY
//					--> As one Value from below
//----------------------------------------------------------------------------------------------------------------------------------//
//		#define PROGRAM_PATH_VAR_AVAILABILITY
//					--> As one Value from below

	///////////////////////////////////////////////////////////////
	//----  Values  -----------------------------------------------
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
#define STORAGE_FILES_PATH_LOCATION___UNDEFINED 0
#define STORAGE_FILES_PATH_LOCATION___PROJECT 1
	//--> Stores Files where the Executable is stored
#define STORAGE_FILES_PATH_LOCATION___PROGRAM_LOC PROG_PATH_LOCATION___PROJECT
	//--> Same as PROJECT
#define STORAGE_FILES_PATH_LOCATION___SYSTEM 2
	//--> it looks inside some special specified locations, like $XDG_CONFIG_HOME or just $HOME for their presence on the system.
	//		then stores for example inside the Home Folder of your Linux Machine -> <ProgramName>/...
#define STORAGE_FILES_PATH_LOCATION___LOCAL_USER_SPECIFIC 3
	//--> This stores the Folder/File-Tree in user-specific Folders. With this you have to be careful
	//		because with this, for sure, it chooses to store inside /root, if you call it as Sudo...
	//		which could be not what you want.
#define STORAGE_FILES_PATH_LOCATION___LOCAL_ALL_USERS 4
	//--> This makes it simple. It just stores everything inside /etc/<ProgramName>/...
#define STORAGE_FILES_PATH_LOCATION___MANUAL 5
	//--> You specify the Path by yourself. The used Absolute Path is then created as a concatenation of
	//		PROG_PATH_ABSOLUTE_MANUAL_PATH & PROGRAM_NAME
#define STORAGE_FILES_PATH_LOCATION___MANUAL_FUNCTION 6
	//--> You specify the Path by yourself via a creating Function with the Prototype
	//      int storage_files_path_location_manual_function(char* argv);
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
#define STORAGE_FILES_PATH_VAR_AVAILABILITY___UNDEFINED 0
#define STORAGE_FILES_PATH_VAR_AVAILABILITY___GLOBAL 1
	//--> The Routine DenKr_essentials_Init(); creates a globally available Variable.
#define STORAGE_FILES_PATH_VAR_AVAILABILITY___SINGLE 2
	//--> The ProgPath Variable is everytime created new, when the macro is called.
	//		It creates a local and thus maybe temporary variable.
  // In every Case the Variable is available as a char *ProgPath; pointing to a Null-terminated String.
//----------------------------------------------------------------------------------------------------
#define PROGRAM_NAME_VAR_AVAILABILITY___UNDEFINED 0
#define PROGRAM_NAME_VAR_AVAILABILITY___GLOBAL 1
#define PROGRAM_NAME_VAR_AVAILABILITY___SINGLE 2
//----------------------------------------------------------------------------------------------------
#define PROGRAM_PATH_VAR_AVAILABILITY___UNDEFINED 0
#define PROGRAM_PATH_VAR_AVAILABILITY___GLOBAL 1
#define PROGRAM_PATH_VAR_AVAILABILITY___SINGLE 2
//----------------------------------------------------------------------------------------------------
// Mind, that some Macros might use Variables from other Macros (e.g. most will need the Program-Name.
// This becomes important, in some cases of combined different GLOBAL & SINGLE Usages.
//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////





#endif /* DENKR_ESSENTIALS_GLOBAL_SETTINGS_VALUES_H */
