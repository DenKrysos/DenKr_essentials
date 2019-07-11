/*
 * Authored by
 * Dennis Krummacker (03.06.14-)
 */



#define DENKR_ESSENTIALS_PROGRAM_FILES_CONTROL_CFG_FILES_C
#define NO_DENKR_ESSENTIALS_PROGRAM_FILES_CONTROL_CFG_FILES_C_FUNCTIONS




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
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------

//---------------------------------------------------------------------------------
#include "control_cfg_file.h"
#include "DenKr_essentials/PreC/DenKr_PreC.h"
#include "DenKr_essentials/DenKr_errno.h"
#include "DenKr_essentials/Program_Files/P_Files_Path.h"
#include "DenKr_essentials/Program_Files/control_cfg_file.h"
#include "DenKr_essentials/auxiliary.h"
//#include "function_creator.h"
//#include "getRealTime.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//






/*
 * Cfg-File:
 * Contains some runtime-stuff like:
 * Runs this Platform as Server (Access Point) or Client?
 * The Ollerus loads the settings on startup.
 * You can set the stored values directly in the cfg-File or
 * the Ollerus itself is capable of setting some values on runtime.
 *
 * Use of Config-File:
 * Try to open:
 * Doesn't exist? -> createcfgfile (does it with some default-values)
 * Otherwise read through the file and setup the actual instantiation of the process
 * validatecfgfile: could someday be implemented and checks the file for correct syntax
 * and tells you where a error lies (if any)
 * Syntax of cfg-file isn't correct? (You, any program or maybe the Program itself damaged the file...):
 * repaircfgfile tries to extract some left valid settings from
 * the damaged file and pastes them in a new one.
 * (Old, damaged file will be saved as .bkp-[counter])
 */
/*
 * Config-File Values:
 */
/*
 * Initial thoughts of author:
 * Make the Program run once (best without commandline prompts)
 * to force him to make a default cfg-file.
 * The Program checks for the presence of the needed cfg-files at startup.
 * If anyone is missing, this is created - maybe with default values - than
 * the program exits and tells in the terminal, which files where created, to tell
 * the user, what files need to be adjusted with desired values.
 * If you implement a GUI: Recommended would be a settings section, linked with the config files.
 */
//TODO: Was allgemeingültiges und integrierbares.
//int check_cfg_files_presence(char **filesv, int filesc){
//	// Pass the files as a char filesv[][], like the common argv, argc
//	int err=0;
//
//	return err;
//}
//
//static int validate_cfg_file(){
//	int err=0;
//
//	return err;
//}
//
//static int repair_cfg_file(){
//	int err=0;
//
//	return err;
//}
//
//static int create_cfg_file(){
//	int err=0;
//
//	return err;
//}
//
//static int read_cfg_file(char *attribute, char *value){
//	int err=0;
//
//	return err;
//}
//
//static int read_cfg_file_whole(){
//	int err=0;
//
//	return err;
//}
//
//static int write_cfg_file(char *attribute, char *value){
//	int err=0;
//
//	return err;
//}
//
//static int listen_to_console_commands(){
//	int err=0;
//
//	return err;
//}





//config_file_read_linkedList_entry
struct cfgf_rd_ll_e{
	int index;
	struct cfgf_rd_ll_e *next;
};
//config_file_read_linkedList_start
struct cfgf_rd_ll_st{
	int to_check_c;
	struct cfgf_rd_ll_e *first;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================
//----  cfg_file_read_variadic()  -----------------------------------------------------------------------------
//====================================================================================================
// This function has a wrapper-macro inside the DenKre_essentials control_cfg_file.h
// Use this instead, to make the use a little bity easier. The macro determines the number
// of passed arguments automatically and thus spares you to pass this explicitly. Additionally
// it prepares the data-structures used to pass the arguments.
// Admittedly this is limited - like universally known - by the PreProcessor 64 Args Limit.
// If you should EVER need more Arguments, you have to use this function here or the one provided below (if finished) and not the wrapper-macro
//   But then you have to - boo hoo - fill in the number of passed (variadic) arguments
//USAGE:
// You pass the variadic arguments every time as a triple:
//     type (of DenKr_essentials_config_file_types), key (as string, the identifier inside the file), variable_pointer (where to store the read value, obviously as a pointer, i.e. the address of the storage variable)
//     short: type, key, variable_addr
// Example: config_file_read_variadic_(path,
//										2,
//										DKess_cfg_type_INT, "TargetPort", &tport,
//										DKess_cfg_type_INET_ADDR_IP4, "CtrlAddrIP4",  &in_addr_ctrl
//									)
// While using the wrapper macro you drop the argument count.
// The path is a string. Constant String, Array, Char Pointer - how you like it.
//
// Some Kind of Error-Checking for wrong passed Amount of Arguments (i.e. like incomplete Triples)
//   should be implicit given, when using the wrapper-macro. Because than you should get a Compile-Error
//   if you wont pass Tuples as multiples of 3.
// Interchanging "Triple-Entries (Swapping Type & Key for example) would compile, but give a Warning
//   caused from unmatching types. So be careful.
//
//  Only use the Type DKess_cfg_type_STR, when you pass an already allocated memory space
//     (Like a malloced buffer, a char-array, a predefined string) For sure, when you know the size
//      of the delivered value
//  Otherwise use the DKess_cfg_type_BUF and pass a (empty) char*
//
// See below for more Information
int config_file_read_variadic_(char *cfgf_path, int argc, enum DenKr_essentials_config_file_types *types, char **keys, void** targets){
		int err=0;
		int i;

		//To use a Data-Structure like this wouldn't be maximum nice in a
		// "long run function". But here it becomes cleaned after the function anyway.
		struct cfgf_rd_ll_e yet_not_found;//Just use a normal entry type as the starter, to make the handling easier. use the index as counter
		struct cfgf_rd_ll_e entries_[argc];
		struct cfgf_rd_ll_e *current_key;
		struct cfgf_rd_ll_e *previous_key;

		//Initialization.
		for(i=argc;i>0;i--){
			(entries_[i]).index = i;
			(entries_[i - 1]).next = &(entries_[i]);
		}
		entries_[argc-1].next = NULL;
		entries_[0].index = 0;
		entries_[0].next = &(entries_[1]);
		yet_not_found.index = argc;
		yet_not_found.next = entries_;

		FILE *cfgf=NULL;

		cfgf = fopen(cfgf_path, "r");
		if (!cfgf) {
			switch(errno){
				case EACCES:
					printfc(red,"ERROR:");printf(" Couldn't read cfg-File!:\n\t%s\n\t\tReason:Permission denied!\n",cfgf_path);
					return FILE_ERR_PERMISSION_DENIED;
				break;
				case ENOENT:
					//TODO: Ask to create default one.
					//Than wait for the user to adjust it. I.e. wait for event like keyboard input
					//or this two things inside GUI.
					//Than jump up and start over reading.
//					printfc(red,"TODO:");
//					depr(TODO);
//					exit(ERR_OVER_9000);
					printfc(yellow,"KEY-WARNING:");printf(" cfg-File to read not existing!:\n\t%s\n",cfgf_path);
					return FILE_ERR_NOT_EXISTING;
				break;
				default:
					printfc(red,"ERROR:");printf(" Ups, seems like we've encountered a case, which isn't caught yet :o( (config_file_read_variadic_)\n");
					printfc(red,"\tAdditional DEBUG:");printf(" errno: %d. File-Path: %s\n",errno,cfgf_path);
					depr(TODO);
					return MAIN_ERR_FUNC_INCOMPLETE;
				break;
			}
		}

		#define CFGF_RD_KEY_FOUND \
						yet_not_found.index--; \
						previous_key->next = current_key->next; \
						goto KeyProcessed;

		DENKR_ESSENTIALS_CFG_FILE_READ_PROCESSING_BRACES(
			current_key=yet_not_found.next;
			previous_key=&yet_not_found;
			for(i=0;i<yet_not_found.index;i++){
				switch(types[current_key->index]){
				case DKess_cfg_type_INT:
					DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_INT_PTR(keys[current_key->index],((int *)(targets[current_key->index])),
						CFGF_RD_KEY_FOUND
					)
					break;
				case DKess_cfg_type_STR:
					DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_STR(keys[current_key->index],((char *)(targets[current_key->index])),
						CFGF_RD_KEY_FOUND
					)
					break;
				case DKess_cfg_type_BUF:
					DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_BUF(keys[current_key->index],*((char **)(targets[current_key->index])),
						CFGF_RD_KEY_FOUND
					)
					break;
				case DKess_cfg_type_INET_ADDR:
					//Hem. Looks like TODO ;oP
					//Implement something like an automated determination of the
					//Type (IPv4 or IPv6) from the read string.
					//And than an according return value.
//					DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_INET_ADDR()
					break;
				case DKess_cfg_type_INET_ADDR_IP4:
					DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_IP4_ADDR(keys[current_key->index],((struct in_addr *)(targets[current_key->index])),
						CFGF_RD_KEY_FOUND
					)
					break;
				case DKess_cfg_type_INET_ADDR_IP6:
					DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_IP6_ADDR(keys[current_key->index],((struct in6_addr *)(targets[current_key->index])),
						CFGF_RD_KEY_FOUND
					)
					break;
				default:
					printfc(red,"ERROR:")printf(" Invalid Type for requested Key at cfg-file read-in: Usage of config_file_read_variadic_().\n");
					return FUNC_ERR_BAD_CALL;
					break;
				}
				previous_key=current_key;
				current_key=current_key->next;
			}
			KeyProcessed:
			if(!(yet_not_found.index)){//Spend a bit time, to save a bit time in some cases ;oP
				goto AllKeysFound;
			}
		);

		if(yet_not_found.index){
			err=FILE_CFG_ERR_KEYS_INCOMPLETE;
			printfc(yellow,"WARNING: ")printf("The following Keys (#%d) were not present inside the read cfg-File.\n",yet_not_found.index);
			current_key=yet_not_found.next;
			for(i=0;i<yet_not_found.index;i++){
				printf("\t%s\n",keys[current_key->index]);
				current_key=current_key->next;
			}
			printf(" <- Inquired File: %s\n\n",cfgf_path);
		}

		AllKeysFound:

		#undef CFGF_RD_KEY_FOUND
		return err;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Old Version, not liked. Current Implementation is done more straight on the function side.
// TODO: Finish also this approach, to offer an unlimited Function.
// The macro assisted Version
// is limited by the 64 PreProcessor Arguments. Subtracting one for the File Name and Floor(Divide())
// lefts over 21 Triples: You can this Macro-Function-Pair only to read at max 21 Entries from a File.
// You could bypass this limit a bit by doing the macro-side steps by yourself (look at config_file_read_variadic(cfgf_path,...) inside control_cfg_file.h)
// and than call the function. Hence you bypass the limitation came from the wrapper macro. This would still
// leave the limitation from e.g. CREATE_argv
// So, now you can think, if you want to read more than 64 File-Entries at once: Rather use my
// little helpers multiple times in succession (and thus going multiple times through the file)
// or look at my stuff, use it as a template and prepare the data-structure for the function manually.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// This function has a wrapper-macro inside the DenKre_essentials control_cfg_file.h
// Use this instead, to make the use a little bity easier. The macro determines the number
// of passed arguments automatically and thus spares you to pass this explicitly.
// Admittedly this is limited - like universally known - by the PreProcessor 64 Args Limit.
// If you should EVER need more Arguments, you have to use this function here and not the wrapper-macro
//   But then you have to - boo hoo - fill in the number of passed (variadic) arguments
//USAGE:
// You pass the variadic arguments every time as a triple:
//     type (of DenKr_essentials_config_file_types), key (as string, the identifier inside the file), variable_pointer (where to store the read value, obviously as a pointer, i.e. the address of the storage variable)
//     short: type, key, variable_addr
// Example: config_file_read_variadic_(path,
//										6,
//										DKess_cfg_type_INT, "TargetPort", &tport,
//										DKess_cfg_type_INET_ADDR_IP4, "CtrlAddrIP4",  &in_addr_ctrl
//									)
//int config_file_read_variadic_(char *cfgf_path, int argc, ...){
//		int err=0;
//		va_list variadics;
//		int argtype;
//		char found=0;
//		FILE *cfgf=NULL;
//
//		if(argc % 3){
//			printfc(red,"BUG:");printf(" Programming-Error. Wrong number of arguments passed to config_file_read_variadic_.\n");
//			return MAIN_ERR_FEW_CMDS;
//		}
//
//		cfgf = fopen(cfgf_path, "r");
//		if (!cfgf) {
//			switch(errno){
//				case EACCES:
//					printfc(red,"ERROR:");printf(" Couldn't read cfg-File!:\n\t%s\n\t\tReason:Permission denied!\n",cfgf_path);
//					return FILE_ERR_PERMISSION_DENIED;
//				break;
//				case ENOENT:
//					//TODO: Ask to create default one.
//					//Than wait for the user to adjust it. I.e. wait for event like keyboard input
//					//or this two things inside GUI.
//					//Than jump up and start over reading.
//					printfc(red,"TODO:");
//					depr(TODO);
//					exit(ERR_OVER_9000);
//				break;
//				default:
//					fprintf(stderr, "Ups, seems like we've encountered a case, which isn't caught yet :o(");
//					depr(TODO);
//					return MAIN_ERR_FUNC_INCOMPLETE;
//				break;
//			}
//		}
//
//		va_start(variadics,argc);
//		for(;argc>0;argc--){
//			found=0;
//			argtype=va_arg(variadics, enum DenKr_essentials_config_file_types);
//			DENKR_ESSENTIALS_CFG_FILE_READ_PROCESSING_BRACES(
//				DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_INT("test",err),
//				DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_BUF("test3",testpt),
//				DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_IP4_ADDR("test3",&sdn_ctrl_addr_ip4)
//			);
//		}
//
//
//		va_end(variadics);
//		return err;
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////













#undef DENKR_ESSENTIALS_PROGRAM_FILES_CONTROL_CFG_FILES_C
#undef NO_DENKR_ESSENTIALS_PROGRAM_FILES_CONTROL_CFG_FILES_C_FUNCTIONS
