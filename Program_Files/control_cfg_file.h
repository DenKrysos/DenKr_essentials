/*
 * control_cfg_file.h
 *
 *  Created on: 20.07.2017
 *      Author: Dennis Krummacker
 */

#ifndef DENKR_ESSENTIALS_PROGRAM_FILES_CONTROL_CFG_FILE_H
#define DENKR_ESSENTIALS_PROGRAM_FILES_CONTROL_CFG_FILE_H




//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//--------  Preamble, Inclusions  ------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//==================================================================================================//
// At first include this ----------------------------------------------------------
//---------------------------------------------------------------------------------
//#include "./global/global_settings.h"
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
#include <string.h>
#include <arpa/inet.h>//inet_pton()
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
//#include ""
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include "DenKr_essentials/PreC/DenKr_PreC.h"
#include "DenKr_essentials/auxiliary.h"
//#include "DenKr_essentials/DenKr_errno.h"
//#include "nl80211.h"
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
//----------------------------------------------------------------------------------------------------
//#define DENKR_ESSENTIALS_CFG_FILES_PATH_PREFIX "cfg/"

#ifndef INET_ADDRSTRLEN
	#define INET_ADDRSTRLEN (16)
#endif
#ifndef INET6_ADDRSTRLEN
	#define INET6_ADDRSTRLEN (48)
#endif
//----------------------------------------------------------------------------------------------------
//// Types
enum DenKr_essentials_config_file_types{
	DKess_cfg_type_INT = 0,
	DKess_cfg_type_STR,
	DKess_cfg_type_BUF,
	DKess_cfg_type_INET_ADDR,
	DKess_cfg_type_INET_ADDR_IP4,
	DKess_cfg_type_INET_ADDR_IP6
};
//  Only use the DKess_cfg_type_STR, when you pass an already allocated memory space
//     (Like a malloced buffer, a char-array, a predefined string) For sure, when you know the size
//      of the delivered value
//  Otherwise use the DKess_cfg_type_BUF and pass a (empty) char*
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
//----------------------------------------------------------------------------------------------------
#ifndef NO_DENKR_ESSENTIALS_PROGRAM_FILES_CONTROL_CFG_FILES_C_FUNCTIONS
//extern int check_cfg_files_presence(char **filesv, int filesc);
extern int config_file_read_variadic_(char *cfgf_path, int argc, enum DenKr_essentials_config_file_types *types, char **keys, void** targets);
#endif
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
//----  Wrapping Macros  ---------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
// If you want to create the passed data-structures and call the function manually look at the macro
// CREATE_argv()/CREATE_argv_CONST() inside auxiliary.h and think about using this.
//----------------------------------------------------------------------------------------------------
#define _config_file_read_variadic_TYPES_loopbody(i, ARRAY, ...) \
		ARRAY[i] = ARRAY_ENTRY(i,(__VA_ARGS__));
#define _config_file_read_variadic_VARADDRS_loopbody(i, ARRAY, ...) \
		ARRAY[i] = (void*)ARRAY_ENTRY(i,(__VA_ARGS__));

#define config_file_read_variadic(cfgf_path,...) \
	{ \
		enum DenKr_essentials_config_file_types config_file_read_variadic_pass_types[COUNT_VARARGS(SPLIT_ARGS_3s_1(__VA_ARGS__))]; \
		EVAL_SMALL(REPEAT(COUNT_VARARGS(SPLIT_ARGS_3s_1(__VA_ARGS__)), _config_file_read_variadic_TYPES_loopbody, config_file_read_variadic_pass_types, SPLIT_ARGS_3s_1(DEMUX_ARGS_3TUPEL(__VA_ARGS__)))) \
		CREATE_argv_CONST(config_file_read_variadic_pass_keys,SPLIT_ARGS_3s_2(DEMUX_ARGS_3TUPEL(__VA_ARGS__))) \
		void* config_file_read_variadic_pass_variables[COUNT_VARARGS(SPLIT_ARGS_3s_1(__VA_ARGS__))]; \
		EVAL_SMALL(REPEAT(COUNT_VARARGS(SPLIT_ARGS_3s_3(__VA_ARGS__)), _config_file_read_variadic_VARADDRS_loopbody, config_file_read_variadic_pass_variables, SPLIT_ARGS_3s_3(DEMUX_ARGS_3TUPEL(__VA_ARGS__)))) \
		err=config_file_read_variadic_(cfgf_path, COUNT_VARARGS(SPLIT_ARGS_3s_3(__VA_ARGS__)), config_file_read_variadic_pass_types,config_file_read_variadic_pass_keys,config_file_read_variadic_pass_variables); \
	}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Old Version, not liked. Current Implementation is done more straight on the function side.
// But put more effort onto the macro-part
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// For a Usage-Description look at function itself, config_file_read_variadic_(), inside the DenKr_essentials control_cfg_file.h
/*
  #define config_file_read_variadic(cfgf_path,...) \
 		config_file_read_variadic_(cfgf_path, \
 				COUNT_VARARGS(__VA_ARGS__), \
 				__VA_ARGS__ \
			)
*/
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
//----  Macros for String-Processing inside Files  -------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
////////////////////////
////// BASIC
////////////////////////
//----------------------------------------------------------------------------------------------------
#define DENKR_ESSENTIALS_CFG_FILE_READ_PROCESSING_ATTACH_ELSE_(ARG) else ARG

#define DENKR_ESSENTIALS_CFG_FILE_READ_PROCESSING_BRACES(...) DENKR_ESSENTIALS_CFG_FILE_READ_PROCESSING_BRACES_(__VA_ARGS__)
#define DENKR_ESSENTIALS_CFG_FILE_READ_PROCESSING_BRACES_(PROCESSING1,...) { \
			char buf[256]; \
			memset(buf,0,sizeof(buf)); \
			int loopcnt; \
			while(1) { \
				while(1){ \
					buf[0] = (char)getc(cfgf); \
					switch(buf[0]){ \
					case EOF: \
						printf("\t...Read completely through config-file.\n"); \
						goto CompletelyReadThrough; \
					case '#': \
						for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
							if (((buf[loopcnt] = getc(cfgf)) == '=') || (buf[loopcnt] == EOF)) { \
								buf[loopcnt]='\0'; \
								break; \
							} \
						} \
						goto GotKey; \
					default: \
						continue; \
					} \
				} \
				GotKey: \
				PROCESSING1 \
				IF(NOT_EQUAL(COUNT_VARARGS(__VA_ARGS__),0))( \
					CALL_MACRO_X_FOR_EACH(DENKR_ESSENTIALS_CFG_FILE_READ_PROCESSING_ATTACH_ELSE_,__VA_ARGS__) \
				) \
			} \
			CompletelyReadThrough: \
			; \
		}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
////////////////////////
////// READ
////////////////////////
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_INT(...) DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_INT_VAR(__VA_ARGS__)

#define DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_INT_VAR(KEY_AS_STR, INT_VAR,...) \
				if(strcmp(buf,KEY_AS_STR)==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					char *endpoint; \
					INT_VAR = strtol(buf, &endpoint, 10); \
					if (*endpoint) { \
						printf("ERROR: Unsupported Format in cfg-File at:\n\t%s\n",KEY_AS_STR); \
						return MAIN_ERR_BAD_CMDLINE; \
					} \
					__VA_ARGS__ \
				}

#define DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_INT_PTR(KEY_AS_STR, INT_POINTER,...) \
				if(strcmp(buf,KEY_AS_STR)==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					char *endpoint; \
					*INT_POINTER = strtol(buf, &endpoint, 10); \
					if (*endpoint) { \
						printf("ERROR: Unsupported Format in cfg-File at:\n\t%s\n",KEY_AS_STR); \
						return MAIN_ERR_BAD_CMDLINE; \
					} \
					__VA_ARGS__ \
				}

//Either create a string/char-Array (or even a allocated buffer) beforehand and pass it to this macro, if you know the length of the read string
//or us the Buffer-Macro and afterwards create a string from that's content and free the buffer or
//just work with that buffer.
#define DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_STR(KEY_AS_STR, STR_VAR,...) \
				if(strcmp(buf,KEY_AS_STR)==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					memcpy(STR_VAR,buf,loopcnt+1); \
					__VA_ARGS__ \
				}

#define DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_BUF(KEY_AS_STR, BUF_POINTER,...) \
				if(strcmp(buf,KEY_AS_STR)==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					if(BUF_POINTER){ \
						free(BUF_POINTER); \
					} \
					BUF_POINTER=malloc(loopcnt+1); \
					memcpy(BUF_POINTER,buf,loopcnt+1); \
					__VA_ARGS__ \
				}

#define DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_INET_ADDR(KEY_AS_STR, in_addr_POINTER, AF_FAM,...) \
				if(strcmp(buf,KEY_AS_STR)==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					inet_pton(AF_FAM,buf,in_addr_POINTER); \
					__VA_ARGS__ \
				}
#define DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_IP4_ADDR(KEY_AS_STR, in_addr_POINTER,...) DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_INET_ADDR(KEY_AS_STR, in_addr_POINTER, AF_INET,__VA_ARGS__)
#define DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_IP6_ADDR(KEY_AS_STR, in6_addr_POINTER,...) DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_INET_ADDR(KEY_AS_STR, in6_addr_POINTER, AF_INET6,__VA_ARGS__)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
////////////////////////
////// WRITE
////////////////////////
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define DENKR_ESSENTIALS_CFG_FILE_VALUE_WRITE_DEFAULT_INT(KEY_AS_STR, INT_VAL) \
				fprintf(cfgf, "\n#"KEY_AS_STR"=%d",INT_VAL);

#define DENKR_ESSENTIALS_CFG_FILE_VALUE_WRITE_DEFAULT_STR(KEY_AS_STR, STR_VAR) \
				fprintf(cfgf, "\n#"KEY_AS_STR"=%s",STR_VAR);

#define DENKR_ESSENTIALS_CFG_FILE_VALUE_WRITE_DEFAULT_INET_ADDR(KEY_AS_STR, in_addr_POINTER, AF_FAM,...) \
				{ \
				char convert_buf[INET6_ADDRSTRLEN]; \
				inet_ntop(AF_FAM,in_addr_POINTER,convert_buf,INET6_ADDRSTRLEN); \
				fprintf(cfgf, "\n#"KEY_AS_STR"=%s",convert_buf); \
				__VA_ARGS__ \
				}

#define DENKR_ESSENTIALS_CFG_FILE_VALUE_WRITE_DEFAULT_IP4_ADDR(KEY_AS_STR, in_addr_POINTER,...) \
				{ \
				char convert_buf[INET_ADDRSTRLEN]; \
				inet_ntop(AF_INET,in_addr_POINTER,convert_buf,INET_ADDRSTRLEN); \
				fprintf(cfgf, "\n#"KEY_AS_STR"=%s",convert_buf); \
				__VA_ARGS__ \
				}

#define DENKR_ESSENTIALS_CFG_FILE_VALUE_WRITE_DEFAULT_IP6_ADDR(KEY_AS_STR, in_addr6_POINTER,...) \
				{ \
				char convert_buf[INET6_ADDRSTRLEN]; \
				inet_ntop(AF_INET6,in_addr_POINTER,convert_buf,INET6_ADDRSTRLEN); \
				fprintf(cfgf, "\n#"KEY_AS_STR"=%s",convert_buf); \
				__VA_ARGS__ \
				}

//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////






#endif /* DENKR_ESSENTIALS_PROGRAM_FILES_CONTROL_CFG_FILE_H */
