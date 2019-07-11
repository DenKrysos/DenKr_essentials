/*
 * DL_Libs.h
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
 *      : through nice implementations of Application Hooks (aka "mount points") and an extension API (aka "Exposing App capabilities back to Plugins")
 *   Or just do it straight and closed (if you don't want others to extend your Suite):
 *      Write your own Plugins, load and bind them. So there would be no need for generic Hooks and APIs.
 *
 *
 *
 * Some Basic Usage Information about the DenKr_essentials Plugin Mechanism (for Developers)
 *    - A Plugin has a Name: This is the Filename without the Extension.
 *    - A Plugin has to implement a 'init' Function.
 *           - Signature: int init_<PluginName>(PluginManager *plugman)
 *      This Function get's called by the Plugin Discoverer, registers it and maybe does
 *      other stuff, which might be done.
 *      The init_ Function shall return the Role-number on success or negative Value on Error.
 *    - Mighty Important for Plugin-supporting-Main-Application-Developers:
 *      Some Values/Resources have to be declared/defined/whatever inside the Main-Application
 *      Look inside DenKrement as a Template (DenKrement/src/plugins/export)
 *       - One File "./plugins/export/plugins_DenKr_essentials__common.h"
 *            -> This shall contain some Values shared between your Main-App and the DenKr_essentials
 *            -> Just create the File in the right Location and fill it with proper Values (see DenKrement as Example)
 *            -> The DL_Libs Part of DenKr_essentials will then use it.
 *         This File is also relevant for the developed Plugins. They will most probably link/include this File to
 *           use the Plugin-Roles. Even if only to get sure to use the right 'Generic'-Number.
 *       - One File "./plugins/export/plugins_export.h"
 *            -> Only to be linked/included by the Plugins. (Not used by DenKr_essentials)
 *            -> Works as some Kind of a "Information Passing Interface".
 *            -> You can use this, for example, to define a struct, that describes how Arguments get passed to
 *                 a Thread, started by a Plugin.
 *                 So the Main App can prepare the struct and the Plugin can use the description to read it out inside the Thread.
 *
 *
 * There will be two types of plugins:
 *   1. Predefined/specific Roles:
 *     Roles to be fulfilled by Plugins, defined beforehand by the Application itself.
 *     A Plugin can register for that Role and do what has to be done for this.
 *        These are loaded from Plugins, the first found becomes registered and used.
 *        If no Plugin for a specific Role is present, the App should provide an own solution
 *        (or at least a Dummy)
 *     Define your specific Roles somewhere in your Program, like:
 *       //TODO
 *   2. 'General' Roles. Call it 'not known beforehand'. Something like an Extension-Interface for Mods
 *     No predefined Roles, no special Tasks to handle. Offer an open API, by which new Plugins
 *     can dynamically extend the capabilities of the Application.
 *
 * Provided are different "Working-Types":
 *   - Thread:
 *       The Plugin just hands it's actual 'Thread-Function' ( void* xx(void* arg) ) to the App - done
 *       from inside it's init_ function. Using the actual Thread, ascertained as hook, the Main-App
 *       spawns a Thread for the Plugin. The Plugin/Thread itself and assisted by the Main-App, providing
 *       something like a specified API (structures...) has to take care of Argument-Passing and connecting
 *       it to the ShMem and Stuff like that.
 *       Some Steps can be assisted by the DL_Libs Library.
 *       The Plugin following does it's stuff basically by itself.
 *   - Library:
 *       The Plugin provides a collection of procedures. Just like a common Library.
 *       Current Intent (maybe just one Implementation-Variation):
 *          Implement a 'Hub-Function' inside the Plugin. This is used as Hook and this
 *          multiplexes the other functions.
 *          To use a specific function, pass the Hub some 'Decision-Argument' (like as an enum
 *          or string and done like Command-Line) together with the actual Arguments for the
 *          actual called Function (variadic).
 *       Other Variant:
 *          Allocate a Linked-List behind the hook, providing a Row of Functions, where every
 *          single Function declares an own role for itself.
 *          Maybe such a method can be used as the basic generic Plugin-Type.
 *
 *
 * About the Plugin-Manager:
 *   An Entity, that Handles the loaded Plugins, Roles, Hooks. Accessible global or passed.
 *
 * About the Discovery-Mechanism:
 *   There are different Levels of "Plugin-Definitions", i.e. of "What Plugins are there and
 *   what should be there"
 *   1. The Plugins, that are wanted by the Program: The App provides predefined Roles and Hooks,
 *      than search for present Plugins to fulfill them and loads them.
 *      (Some or all of this Plugins can be optional, i.e. the Roles and Hooks are provided, the
 *      Tasks have to be handled, but they aren't essential for the Application. If no Plugins
 *      are present, these Tasks just won't get processed and the Application restricts itself to
 *      other Tasks.)
 *   2. The Plugins, that are allowed by the bought License of the End-Consumer. You could implement
 *      some Licensing Mechanism, where Customer can pay for specific Functionalities of your Program.
 *      So there could be the Roles/Functionalities of which your App is capable of and even the Plugins
 *      are present, but the License of the Customer doesn't allow the use of it.
 *   3. The Plugins, i.e. the additional .so-Files, that are present. This finally can be Plugins for
 *      predefined Roles, that are inquired, or generic Extensions.
 *   - - - - - - - - - - - - - - - - - - - - - - - -
 *   The Discovery-Mechanism checks, what is inquired by the App, i.e. what predefined Roles exist (these are
 *   defined by the Program like explained above). Then the Discovery-Function looks inside the given Folders
 *   for present Files. It loads the appropriate Files and registers the corresponding Plugins for
 *   the predefined Roles inside the Plugin-Manager.
 *   FUTURE-TODO: The Licensing Mechanism restricts not payed Functions or even prevents from loading.
 *   It also loads additional Extension-Plugins.
 *   It annotates about Roles, that are predefined, but not fulfilled by present Plugins.
 *   TODO: Maybe some Roles can be defined as ESSENTIAL, INDISPENSABLE
 *
 *
 * TODO: The Generic Plugins (Linked Lists and all this stuff)
 */

#ifndef DENKR_ESSENTIALS__PLUGINS__DL_LIBS_H
#define DENKR_ESSENTIALS__PLUGINS__DL_LIBS_H

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
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#include "DenKr_essentials/Plugins/plugin_discovery.h"
#include "DenKr_essentials/Plugins/plugin_management.h"
#include "DenKr_essentials/Plugins/plugin_database.h"
//---------------------------------------------------------------------------------
//#include "../PreC/DenKr_PreC.h"
//#include "../DenKr_errno.h"
//#include "../auxiliary.h"
//#include "function_creator.h"
//#include "getRealTime.h"
//#include "Program_Files/P_Files_Path.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//













#endif
#endif /* DENKR_ESSENTIALS__PLUGINS__DL_LIBS_H */
