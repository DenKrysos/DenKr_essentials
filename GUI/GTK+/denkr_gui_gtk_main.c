/*
 * denkr_gui_gtk_main.c
 *
 *  Created on: 02.10.2017
 *      Author: Dennis Krummacker
 */


#define DENKR_ESSENTIALS__GUI__GTKP__DENKR_GUI_GTK_MAIN__C
#define NO__DENKR_ESSENTIALS__GUI__GTKP__DENKR_GUI_GTK_MAIN__C__FUNCTIONS



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
#include <stdlib.h>
// GUI: GTK+
//			Hints to compile a GTK+ Program:
//			1. Add the Paths from the Console-Output of
//					pkg-config --cflags gtk+-3.0
//			   in the Project-Properties under
//			      C/C++ Build -> Settings -> Tool Settings -> GCC C Compiler -> Includes -> Include Paths (-I)
//			2. Adjust the 'Command Line Pattern'
//			   under GCC C Compiler as well as under GCC C Linker to
//			      ${COMMAND} `pkg-config --cflags gtk+-3.0` ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS} `pkg-config --libs gtk+-3.0`
//			   i.e. add the parts `pkg-config --cflags gtk+-3.0` & `pkg-config --libs gtk+-3.0`
#include <gtk/gtk.h>//In use was gtk+-3.0
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#include "GUI/GTK+/gui_functions.h"
//---------------------------------------------------------------------------------
#include "DenKr_essentials/auxiliary.h"
#include "DenKr_essentials/GUI/GTK+/denkr_gui_gtk_main.h"
#include "DenKr_essentials/GUI/GTK+/gui_functions.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//






void DenKr_essentials_GUI_gtk_main(int argc, char** argv){
//	int err=0;
	//GTK+
    GtkBuilder *gtkbuilder;
    GtkWidget *gtkwindow;
    // - - - - - - - - - - - - - - - - - - - - - // init thread-capability within GTK & GDK
    // - - - - - - - - - - - - - - - - - - - - - //    g_thread_init(NULL); // deprecated
    // - - - - - - - - - - - - - - - - - - - - - //    gdk_threads_init(); // deprecated
    // init GTK
    gtk_init(&argc, &argv);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    gtkbuilder = gtk_builder_new();
    //Get the GUI-File to build GUI at Runtime. (Inside scope to get rid of temporary needed variables after Loading)
    {
		int GUIFilePath_length;
		GUIFilePath_length = ProgPath_length+sizeof(GUIFilePathPrefix)-1+sizeof(GUIFileName);
		char GUIFilePath[GUIFilePath_length];
		snprintf(GUIFilePath,GUIFilePath_length,"%s%s%s",ProgPath,GUIFilePathPrefix,GUIFileName);
		gtk_builder_add_from_file (gtkbuilder, GUIFilePath, NULL);
    }
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    gtkwindow = GTK_WIDGET(gtk_builder_get_object(gtkbuilder, "window_main"));
    gtk_builder_connect_signals(gtkbuilder, NULL);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    g_object_unref(gtkbuilder);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    gtk_widget_show(gtkwindow);
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // GTK main loop
    // - - - - - - - - - - - - - - - - - - - - - //    gdk_threads_enter(); //deprecated
    gtk_main();
    // - - - - - - - - - - - - - - - - - - - - - //    gdk_threads_leave(); //deprecated
    //---------------------------------------------------------------------------------------------------------------//
}








#undef DENKR_ESSENTIALS__GUI__GTKP__DENKR_GUI_GTK_MAIN__C
#undef NO__DENKR_ESSENTIALS__GUI__GTKP__DENKR_GUI_GTK_MAIN__C__FUNCTIONS
