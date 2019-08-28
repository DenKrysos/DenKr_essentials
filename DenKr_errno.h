#ifndef DENKR_ESSENTIALS_DENKR_ERRNO_H
#define DENKR_ESSENTIALS_DENKR_ERRNO_H

/*
 * Authored by
 * Dennis Krummacker (03.06.14-)
 */


/*
 * Definition of return-error-codes
 */
#define MAIN_ERR_NONE 100
#define MAIN_ERR_STD 101
#define MAIN_ERR_WARNING 102
#define MAIN_ERR_CLEARED 103
#define MAIN_ERR_FEW_CMDS 104
#define MAIN_ERR_BAD_CMDLINE 105
#define MAIN_ERR_FUNC_INCOMPLETE 106
#define MAIN_ERR_TIMEOUT 107
#define MAIN_ERR_BAD_RUN 109
#define MAIN_ERR_CANCELED 110
#define MAIN_ERR_BUG 199
//-----------------------------------------------
#define OPERATION_ERR_STD 10
#define OPERATION_ERR_NOTHING_TO_DO 11
#define OPERATION_ERR_NEVER_HAPPEN 12
#define OPERATION_ERR_NOT_SUPPORTED 13
#define OPERATION_ERR_UNSUCCESSFUL 14
//-----------------------------------------------
#define STRUCT_ERR_STD 20
#define STRUCT_ERR_DMG 21
#define STRUCT_ERR_NOT_EXIST 22
#define STRUCT_ERR_INCOMPLETE 23
//-----------------------------------------------
#define FILE_ERR_NOT_OPENED 31
#define FILE_ERR_NOT_CLOSED 32
#define FILE_ERR_PERMISSION_DENIED 33
#define FILE_ERR_ALREADY_EXISTS 34
#define FILE_ERR_NOT_EXISTING 35
#define FILE_CFG_ERR_VALUE_INVALID 38
#define FILE_CFG_ERR_KEYS_INCOMPLETE 39
//-----------------------------------------------
#define FUNC_ERR_TRY_AGAIN 41
#define FUNC_ERR_BAD_CALL 42
#define FUNC_ERR_BAD_ARG 43
//-----------------------------------------------
#define VALUE_ERR_STD 50
//-----------------------------------------------
#define ARG_ERR_STD 60
//-----------------------------------------------
#define NETWORK_ERR_CONNECTION_CLOSED 1000
#define NETWORK_ERR_NO_CONNECTION 1001
#define NETWORK_ERR_RARE_INTERFACES 1002
//-----------------------------------------------
#define DL_LIBS__ERR__NOT_LOADED 1101
#define DL_LIBS__ERR__NO_INIT_FUNC 1102
#define DL_LIBS__ERR__NO_INIT_ERR 1103
#define DL_LIBS__ERR__NO_REGISTER_FUNC 1104
//-----------------------------------------------
#define THREAD__ERR__CREATION__ATTR_INIT 1201
#define THREAD__ERR__CREATION__ATTR_MODIFY 1202
#define THREAD__ERR__CREATION__ATTR_DESTROY 1203
#define THREAD__ERR__CREATION__CREATE 1204
#define THREAD__OP__TERMINATION 1250
//-----------------------------------------------
#define CONTEXT_BROKER__WARN__NO_CONTEXT 3001
//-----------------------------------------------
#define ERR_OVER_9000 9000
//-----------------------------------------------
//===============================================
//===============================================








#endif /* DENKR_ESSENTIALS_DENKR_ERRNO_H */
