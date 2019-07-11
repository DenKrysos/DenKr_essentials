/*
 * DenKr_essentials.h
 *
 *  Created on: 20.07.2017
 *      Author: Dennis Krummacker
 *
 *  A Collection of all available Headers from DenKr_essentials.
 *  You can simply either include this one here and get everything or
 *  you can look into here to see, what is available and choose specific ones.
 *  Every Topic/Header should work by it's own. If Cross-references are needed,
 *  i should have mentioned them inside the concerning one, i.e. you don't have
 *  to care for this.
 */

#ifndef DENKR_ESSENTIALS_DENKR_ESSENTIALS_H
#define DENKR_ESSENTIALS_DENKR_ESSENTIALS_H


//A great PreProcessor Extension.
//   Exposes nice basic useful PreProcessor Routines
//   and for example allows you to write dynamic Macros / overloaded functions
//   which are already switched or even partly executed during Compilation.
#include "PreC/DenKr_PreC.h"

//Kind of General/Basic

//Recommended to include the "auxiliary.h", at least if you define
//   the global_settings Values such that Variables like
//   ProgramName, ProgPath or StorageFilesPath are created as global Variables.
//   Because than, the global Variables are declared inside "auxiliary.c" and
//   included as 'extern' in "auxiliary.h"
#include "auxiliary.h"
#include "CAssert.h"
#include "DenKr_errno.h"
#include "getRealTime.h"
#include "linked_list.h"

//Live Inter-Program Communication
//Use this to give Programs of different Programming Languages
//   the capabilities to communicate with each other live during runtime
#include "InterProgram_Communication/InterProgram_Communication.h"
#include "InterProgram_Communication/socket_stuff.h"
#include "InterProgram_Communication/communication_types.h"

//Some Network Programming specific Stuff
//   Look deeper inside, to check if it's interesting for you
#include "network/auxiliary_wlan.h"
#include "network/link_monitoring.h"

//Plugins: Dynamic Loading of Program Parts during Runtime
//    Dynamically Loaded Libraries (DLLs)
//  You know the purpose: Distribute Software-Suites with different functionality coverage,
//  respectively give your Program the capability to be extendible.
//  You can do this completely generic, so that everyone can extend your Program with new
//  functionality, without Changes at the base Program being necessary.
//     : through nice implementations of Application Hooks (aka "mount points") and an extension API (aka "Exposing App capabilities back to Plugins)
//  Or just do it straight and closed (if you don't want others to extend your Suite):
//     Write your own Plugins, load and bind them. So there would be no need for generic Hooks and APIs.
#include "DL_Libs.h"

//Program File Handling
//   e.g. determining the Path, where Files of the Program should be stored
//        like Config-Files or Logging-Files.
//   or also the Handling of cfg-Files.
#include "Program_Files/P_Files_Path.h"



//You shouldn't have a need for them
//   They are just used by myself (mainly inside "auxiliary")
//      So their results are always available for you, without you have to care about them.
//   Pretty cool construct, but somewhat useless for you at their own ;oP
#include "function_creator.h"
#include "function_creator_func.h"
#include "function_creator_funcname.h"



#endif /* DENKR_ESSENTIALS_DENKR_ESSENTIALS_H */
