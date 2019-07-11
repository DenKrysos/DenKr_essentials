/*
 * DL_Libs.c
 *
 *  Created on: 20.07.2017 - 25.07.2018
 *      Author: Dennis Krummacker
 *
 *  Dynamically Loaded Libraries (DL Libs, DLLs)
 *
 * Used for Plugins: Dynamic Loading of Program Parts during Runtime
 *   You know the purpose: Distribute Software-Suites with different functionality coverage,
 *   respectively give your Program the capability to be extendible.
 *   You can do this completely generic, so that everyone can extend your Program with new
 *   functionality, without Changes at the base Program being necessary.
 *      : through nice implementations of Application Hooks (aka "mount points") and an extension API (aka "Exposing App capabilities back to Plugins)
 *   Or just do it straight and closed (if you don't want others to extend your Suite):
 *      Write your own Plugins, load and bind them. So there would be no need for generic Hooks and APIs.
 */

#define DENKR_ESSENTIALS__PLUGINS__DL_LIBS_C
#define NO_DENKR_ESSENTIALS__PLUGINS__DL_LIBS_C_FUNCTIONS

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
#include <dlfcn.h>
//#include <stdint.h>
//#include <errno.h>
//#include <limits.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#include "../PreC/DenKr_PreC.h"
#include "../DenKr_errno.h"
#include "../auxiliary.h"
//#include "function_creator.h"
//#include "getRealTime.h"
//#include "Program_Files/P_Files_Path.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//





// Functions:
//   Look into plugins Folder. Read in all Files with Extension ".so"
//   Check against desired Plugins.
//   Load them.










#endif
#undef DENKR_ESSENTIALS__PLUGINS__DL_LIBS_C
#undef NO_DENKR_ESSENTIALS__PLUGINS__DL_LIBS_C_FUNCTIONS
