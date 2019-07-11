#ifndef DENKR_ESSENTIALS_FUNCTION_CREATOR_FUNCNAME_H
#define DENKR_ESSENTIALS_FUNCTION_CREATOR_FUNCNAME_H

/*
 * Authored by
 * Dennis Krummacker (06.03.2017-)
 */




#include "PreC/DenKr_PreC.h"





//////////////////////////////////////////////////////////////////////////////////////////////////////
// ***		auxiliary.c		***
//====================================================================================================
//----------------------------------------------------------------------------------------------------
// #ifdef REMAINDER_C
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CREATE_PRINT_DAYTIME_FUNCNAME(APPENDIX)                     print_daytime ## APPENDIX
#define CREATE_PRINT_DAYTIME_FUNCNAME(APPENDIX,ARGUMENT)             _CREATE_PRINT_DAYTIME_FUNCNAME(APPENDIX)(ARGUMENT)
#define CREATE_PRINT_DAYTIME_FUNCNAME_DECLARE(APPENDIX,ARGUMENT)     char CREATE_PRINT_DAYTIME_FUNCNAME(APPENDIX,ARGUMENT)
//////////////////////////////////////////////////////////////////////////////////////////////////////
// #endif
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////






#endif /* DENKR_ESSENTIALS_FUNCTION_CREATOR_FUNCNAME_H */
