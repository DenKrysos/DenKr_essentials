/*
 * ansi.c
 *
 *  Created on: 30.08.2017
 *      Author: Dennis Krummacker
 */




#define DENKR_ESSENTIALS_TERMINAL_ANSI_C
#define NO_DENKR_ESSENTIALS_TERMINAL_ANSI_C_FUNCTIONS





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
#include <stdlib.h>
#include <stdio.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------

//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//





void print_ANSI_Pokemon_Starter_1st_Gen_8Bit(){
	#define ANSI_Poke_escape "\033"
	//----------------------------------------------
	#define ANSI_Poke_Bf ANSI_Poke_escape"[22;30m"
	#define ANSI_Poke_rf ANSI_Poke_escape"[31m"
	#define ANSI_Poke_gf ANSI_Poke_escape"[32m"
	#define ANSI_Poke_yf ANSI_Poke_escape"[33m"
	#define ANSI_Poke_bf ANSI_Poke_escape"[34m"
	#define ANSI_Poke_pf ANSI_Poke_escape"[35m"
	#define ANSI_Poke_cf ANSI_Poke_escape"[36m"
	#define ANSI_Poke_wf ANSI_Poke_escape"[37m"
	//----------------------------------------------
	#define ANSI_Poke_Bp ANSI_Poke_escape"[40m"
	#define ANSI_Poke_rb ANSI_Poke_escape"[41m"
	#define ANSI_Poke_gb ANSI_Poke_escape"[42m"
	#define ANSI_Poke_yb ANSI_Poke_escape"[43m"
	#define ANSI_Poke_bb ANSI_Poke_escape"[44m"
	#define ANSI_Poke_pb ANSI_Poke_escape"[45m"
	#define ANSI_Poke_cb ANSI_Poke_escape"[46m"
	#define ANSI_Poke_wb ANSI_Poke_escape"[47m"
	//----------------------------------------------
	#define ANSI_Poke_LIGHT_COL ANSI_Poke_escape"[1m"
	#define ANSI_Poke_DARK_COL ANSI_Poke_escape"[22m"
		#define ANSI_Poke_ON ANSI_Poke_LIGHT_COL
		#define ANSI_Poke_OFF ANSI_Poke_DARK_COL
	#define ANSI_Poke_italicson ANSI_Poke_escape"[3m"
	#define ANSI_Poke_italicsoff ANSI_Poke_escape"[23m"
	#define ANSI_Poke_ulon ANSI_Poke_escape"[4m"
	#define ANSI_Poke_uloff ANSI_Poke_escape"[24m"
	#define ANSI_Poke_invon ANSI_Poke_escape"[7m"
	#define ANSI_Poke_invoff ANSI_Poke_escape"[27m"
	//----------------------------------------------
	#define ANSI_Poke_reset "\x1b[0m"
	//----------------------------------------------
	//----------------------------------------------
	printf("\n");
	printf("                        "ANSI_Poke_Bf"██████                    "ANSI_Poke_Bf"████████                  ██              "ANSI_Poke_Bf"████████                  ████████\n");
	printf("                      "ANSI_Poke_Bf"██"ANSI_Poke_gf""ANSI_Poke_ON"██████"ANSI_Poke_OFF""ANSI_Poke_Bf"██                "ANSI_Poke_Bf"██"ANSI_Poke_rf""ANSI_Poke_ON"██████"ANSI_Poke_OFF"██"ANSI_Poke_Bf"██              ██"ANSI_Poke_rf"██"ANSI_Poke_Bf"██          "ANSI_Poke_Bf"██"ANSI_Poke_bf""ANSI_Poke_ON"██████"ANSI_Poke_OFF"██"ANSI_Poke_Bf"████            ██"ANSI_Poke_bf""ANSI_Poke_ON"████████"ANSI_Poke_OFF""ANSI_Poke_Bf"██\n");
	printf("                  "ANSI_Poke_Bf"██████"ANSI_Poke_gf""ANSI_Poke_ON"██████"ANSI_Poke_OFF""ANSI_Poke_Bf"██              "ANSI_Poke_Bf"██"ANSI_Poke_rf""ANSI_Poke_ON"██████████"ANSI_Poke_OFF"██"ANSI_Poke_Bf"██            ██"ANSI_Poke_rf"████"ANSI_Poke_Bf"██      "ANSI_Poke_Bf"██"ANSI_Poke_bf""ANSI_Poke_ON"████████████"ANSI_Poke_OFF"██"ANSI_Poke_Bf"████      ████"ANSI_Poke_bf""ANSI_Poke_ON"██████"ANSI_Poke_OFF"████"ANSI_Poke_Bf"██\n");
	printf("              "ANSI_Poke_Bf"████"ANSI_Poke_gf""ANSI_Poke_ON"████"ANSI_Poke_OFF"██"ANSI_Poke_ON"████"ANSI_Poke_OFF"██"ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"████          "ANSI_Poke_Bf"██"ANSI_Poke_rf""ANSI_Poke_ON"████████████"ANSI_Poke_OFF""ANSI_Poke_Bf"██            ██"ANSI_Poke_rf"████"ANSI_Poke_Bf"██      "ANSI_Poke_Bf"██"ANSI_Poke_bf""ANSI_Poke_ON"██████████████"ANSI_Poke_OFF""ANSI_Poke_Bf"██"ANSI_Poke_pf"██"ANSI_Poke_Bf"████  ██"ANSI_Poke_bf""ANSI_Poke_ON"████"ANSI_Poke_OFF"██"ANSI_Poke_Bf"██"ANSI_Poke_bf"████"ANSI_Poke_Bf"██\n");
	printf("      "ANSI_Poke_Bf"██    ██"ANSI_Poke_gf""ANSI_Poke_ON"██████"ANSI_Poke_OFF"████"ANSI_Poke_ON"████"ANSI_Poke_OFF"██"ANSI_Poke_ON"██████"ANSI_Poke_OFF""ANSI_Poke_Bf"██      "ANSI_Poke_Bf"██"ANSI_Poke_rf""ANSI_Poke_ON"██████████████"ANSI_Poke_OFF"██"ANSI_Poke_Bf"██        ██"ANSI_Poke_rf"████"ANSI_Poke_yf"██"ANSI_Poke_rf"██"ANSI_Poke_Bf"██  "ANSI_Poke_Bf"██"ANSI_Poke_bf""ANSI_Poke_ON"████████████████"ANSI_Poke_OFF"██"ANSI_Poke_pf"██"ANSI_Poke_ON"██"ANSI_Poke_OFF"██"ANSI_Poke_Bf"██"ANSI_Poke_bf"██"ANSI_Poke_ON"██"ANSI_Poke_OFF"██"ANSI_Poke_Bf"██"ANSI_Poke_bf"██████"ANSI_Poke_Bf"██\n");
	printf("    "ANSI_Poke_Bf"██"ANSI_Poke_cf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██████"ANSI_Poke_gf""ANSI_Poke_ON"████"ANSI_Poke_OFF"██"ANSI_Poke_ON"██"ANSI_Poke_OFF"██"ANSI_Poke_ON"██████"ANSI_Poke_OFF"██"ANSI_Poke_ON"██████"ANSI_Poke_OFF""ANSI_Poke_Bf"██  "ANSI_Poke_Bf"██"ANSI_Poke_rf""ANSI_Poke_ON"████████"ANSI_Poke_wf"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██"ANSI_Poke_rf""ANSI_Poke_ON"████"ANSI_Poke_OFF"██"ANSI_Poke_Bf"██        ██"ANSI_Poke_rf"██"ANSI_Poke_yf"██"ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_rf"██"ANSI_Poke_Bf"██  "ANSI_Poke_Bf"██"ANSI_Poke_bf""ANSI_Poke_ON"████████"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██"ANSI_Poke_bf""ANSI_Poke_ON"████"ANSI_Poke_OFF"██"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_pf""ANSI_Poke_ON"████"ANSI_Poke_OFF"██"ANSI_Poke_Bf"██"ANSI_Poke_bf"████"ANSI_Poke_Bf"██"ANSI_Poke_bf"████"ANSI_Poke_Bf"██\n");
	printf("    "ANSI_Poke_Bf"██"ANSI_Poke_cf""ANSI_Poke_ON"██████"ANSI_Poke_OFF""ANSI_Poke_Bf"████"ANSI_Poke_gf"██"ANSI_Poke_ON"██"ANSI_Poke_OFF"██"ANSI_Poke_ON"██████████"ANSI_Poke_OFF"██"ANSI_Poke_ON"████"ANSI_Poke_OFF""ANSI_Poke_Bf"██  "ANSI_Poke_Bf"██"ANSI_Poke_rf""ANSI_Poke_ON"████████"ANSI_Poke_OFF""ANSI_Poke_Bf"████"ANSI_Poke_rf""ANSI_Poke_ON"██"ANSI_Poke_OFF"██████"ANSI_Poke_Bf"██      ██"ANSI_Poke_rf"██"ANSI_Poke_yf""ANSI_Poke_ON"████"ANSI_Poke_OFF""ANSI_Poke_rf"██"ANSI_Poke_Bf"██  "ANSI_Poke_Bf"██"ANSI_Poke_bf"██"ANSI_Poke_ON"██████"ANSI_Poke_OFF""ANSI_Poke_Bf"████"ANSI_Poke_bf""ANSI_Poke_ON"██"ANSI_Poke_OFF"████"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_pf"██████"ANSI_Poke_OFF""ANSI_Poke_Bf"██"ANSI_Poke_bf"██"ANSI_Poke_Bf"████████\n");
	printf("    "ANSI_Poke_Bf"██"ANSI_Poke_cf""ANSI_Poke_ON"████████"ANSI_Poke_OFF"██"ANSI_Poke_Bf"██"ANSI_Poke_gf""ANSI_Poke_ON"██"ANSI_Poke_OFF"██"ANSI_Poke_ON"██████████"ANSI_Poke_OFF"██"ANSI_Poke_ON"████"ANSI_Poke_OFF""ANSI_Poke_Bf"██  "ANSI_Poke_Bf"██"ANSI_Poke_rf""ANSI_Poke_ON"████████"ANSI_Poke_OFF""ANSI_Poke_Bf"████"ANSI_Poke_rf""ANSI_Poke_ON"██"ANSI_Poke_OFF"██████"ANSI_Poke_Bf"██        ██"ANSI_Poke_yf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"████      "ANSI_Poke_Bf"██"ANSI_Poke_bf"████"ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"████"ANSI_Poke_bf"██████"ANSI_Poke_Bf"██"ANSI_Poke_wf""ANSI_Poke_ON"████"ANSI_Poke_pf"██"ANSI_Poke_OFF"██"ANSI_Poke_Bf"████\n");
	printf("  "ANSI_Poke_Bf"██"ANSI_Poke_cf""ANSI_Poke_ON"████"ANSI_Poke_OFF"██"ANSI_Poke_ON"██"ANSI_Poke_OFF"████"ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██████"ANSI_Poke_gf""ANSI_Poke_ON"████████"ANSI_Poke_OFF"██"ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██      "ANSI_Poke_Bf"██"ANSI_Poke_rf"██"ANSI_Poke_ON"████████"ANSI_Poke_OFF"██████████"ANSI_Poke_Bf"██      ██"ANSI_Poke_rf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██          "ANSI_Poke_Bf"████"ANSI_Poke_bf"████████"ANSI_Poke_Bf"████"ANSI_Poke_bf""ANSI_Poke_ON"████"ANSI_Poke_wf"██"ANSI_Poke_OFF""ANSI_Poke_pf"████"ANSI_Poke_Bf"██\n");
	printf(""ANSI_Poke_Bf"████"ANSI_Poke_cf"██"ANSI_Poke_ON"████████████████"ANSI_Poke_OFF""ANSI_Poke_Bf"██"ANSI_Poke_gf"██████"ANSI_Poke_Bf"████████        "ANSI_Poke_Bf"████"ANSI_Poke_rf"██████████████████"ANSI_Poke_Bf"██  ██"ANSI_Poke_rf""ANSI_Poke_ON"████"ANSI_Poke_OFF""ANSI_Poke_Bf"██          "ANSI_Poke_Bf"██"ANSI_Poke_bf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"████████"ANSI_Poke_bf""ANSI_Poke_ON"██████"ANSI_Poke_OFF"██"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_pf"████"ANSI_Poke_Bf"██\n");
	printf(""ANSI_Poke_Bf"██"ANSI_Poke_cf"████"ANSI_Poke_ON"██████"ANSI_Poke_OFF"██"ANSI_Poke_ON"██████"ANSI_Poke_OFF""ANSI_Poke_Bf"██"ANSI_Poke_cf"██"ANSI_Poke_Bf"██████"ANSI_Poke_cf"██████"ANSI_Poke_Bf"██            "ANSI_Poke_Bf"██████"ANSI_Poke_rf"████"ANSI_Poke_Bf"██"ANSI_Poke_rf"██████"ANSI_Poke_Bf"████"ANSI_Poke_rf"██"ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██              "ANSI_Poke_Bf"████"ANSI_Poke_yf""ANSI_Poke_ON"████"ANSI_Poke_OFF""ANSI_Poke_Bf"██"ANSI_Poke_bf""ANSI_Poke_ON"████"ANSI_Poke_OFF"██"ANSI_Poke_Bf"██"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_pf"████"ANSI_Poke_Bf"██\n");
	printf(""ANSI_Poke_Bf"██"ANSI_Poke_cf""ANSI_Poke_ON"████████"ANSI_Poke_OFF"██"ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"████"ANSI_Poke_cf""ANSI_Poke_ON"██"ANSI_Poke_OFF"██████████"ANSI_Poke_Bf"██"ANSI_Poke_cf"██"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██              "ANSI_Poke_Bf"██"ANSI_Poke_yf""ANSI_Poke_ON"████"ANSI_Poke_OFF""ANSI_Poke_Bf"██"ANSI_Poke_rf""ANSI_Poke_ON"████"ANSI_Poke_OFF""ANSI_Poke_rf"██████"ANSI_Poke_Bf"██"ANSI_Poke_rf"██"ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██                  "ANSI_Poke_Bf"██"ANSI_Poke_yf"████"ANSI_Poke_Bf"████████"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_pf"████"ANSI_Poke_Bf"██\n");
	printf(""ANSI_Poke_Bf"██"ANSI_Poke_cf"██"ANSI_Poke_ON"████████"ANSI_Poke_OFF""ANSI_Poke_Bf"██"ANSI_Poke_rf""ANSI_Poke_ON"██"ANSI_Poke_wf"████"ANSI_Poke_OFF""ANSI_Poke_cf"████"ANSI_Poke_Bf"██"ANSI_Poke_cf"████"ANSI_Poke_Bf"██████                "ANSI_Poke_Bf"██"ANSI_Poke_yf""ANSI_Poke_ON"██████"ANSI_Poke_OFF""ANSI_Poke_Bf"████"ANSI_Poke_rf"██████"ANSI_Poke_Bf"██"ANSI_Poke_rf"██"ANSI_Poke_Bf"██                  "ANSI_Poke_Bf"██"ANSI_Poke_bf"██"ANSI_Poke_Bf"██"ANSI_Poke_pf"██"ANSI_Poke_yf"██████"ANSI_Poke_pf"██"ANSI_Poke_Bf"██"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██\n");
	printf("  "ANSI_Poke_Bf"██"ANSI_Poke_cf"██"ANSI_Poke_ON"██████"ANSI_Poke_OFF""ANSI_Poke_Bf"██"ANSI_Poke_rf""ANSI_Poke_ON"██"ANSI_Poke_wf"██"ANSI_Poke_cf"██"ANSI_Poke_OFF"██"ANSI_Poke_Bf"██"ANSI_Poke_cf"████"ANSI_Poke_Bf"██                    "ANSI_Poke_Bf"██"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██"ANSI_Poke_yf""ANSI_Poke_ON"██████"ANSI_Poke_OFF""ANSI_Poke_rf"████████"ANSI_Poke_Bf"████                      "ANSI_Poke_Bf"████████"ANSI_Poke_pf"████"ANSI_Poke_bf"██"ANSI_Poke_Bf"██"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██\n");
	printf("    "ANSI_Poke_Bf"████"ANSI_Poke_cf"████████████"ANSI_Poke_Bf"██"ANSI_Poke_cf"██████"ANSI_Poke_Bf"██                      "ANSI_Poke_Bf"██████"ANSI_Poke_yf"████"ANSI_Poke_rf"██████"ANSI_Poke_Bf"████                              "ANSI_Poke_Bf"██████"ANSI_Poke_bf"██"ANSI_Poke_Bf"████\n");
	printf("        "ANSI_Poke_Bf"██████████████"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_cf"██"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██                            "ANSI_Poke_Bf"██████"ANSI_Poke_rf"██"ANSI_Poke_Bf"████                                  "ANSI_Poke_Bf"██"ANSI_Poke_bf"██████"ANSI_Poke_Bf"██\n");
	printf("                      "ANSI_Poke_Bf"██████                                "ANSI_Poke_Bf"██"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_rf"██"ANSI_Poke_wf""ANSI_Poke_ON"██"ANSI_Poke_OFF""ANSI_Poke_Bf"██                                    "ANSI_Poke_Bf"██████\n");
	printf("                                                              "ANSI_Poke_Bf"██████\n");
	printf(ANSI_Poke_reset"\n");
	//----------------------------------------------
	//----------------------------------------------
	#undef ANSI_Poke_escape
	//----------------------------------------------
	#undef ANSI_Poke_Bf
	#undef ANSI_Poke_rf
	#undef ANSI_Poke_gf
	#undef ANSI_Poke_yf
	#undef ANSI_Poke_bf
	#undef ANSI_Poke_pf
	#undef ANSI_Poke_cf
	#undef ANSI_Poke_wf
	//----------------------------------------------
	#undef ANSI_Poke_Bp
	#undef ANSI_Poke_rb
	#undef ANSI_Poke_gb
	#undef ANSI_Poke_yb
	#undef ANSI_Poke_bb
	#undef ANSI_Poke_pb
	#undef ANSI_Poke_cb
	#undef ANSI_Poke_wb
	//----------------------------------------------
	#undef ANSI_Poke_LIGHT_COL
	#undef ANSI_Poke_DARK_COL
		#undef ANSI_Poke_ON
		#undef ANSI_Poke_OFF
	#undef ANSI_Poke_italicson
	#undef ANSI_Poke_italicsoff
	#undef ANSI_Poke_ulon
	#undef ANSI_Poke_uloff
	#undef ANSI_Poke_invon
	#undef ANSI_Poke_invoff
	//----------------------------------------------
	#undef ANSI_Poke_reset
}




void print_ANSI_Pokemon_Bulbasaur(){
	#define ANSI_poke_ESC "\033"
	//256-color mode:
	#define ANSI_Poke_escape_fg ANSI_poke_ESC"[38;5;"
	#define ANSI_Poke_escape_bg ANSI_poke_ESC"[48;5;"
	//----------------------------------------------
	#define ANSI_Bf ANSI_Poke_escape_fg"0m"
	#define ANSI_wh ANSI_Poke_escape_fg"15m"
	//Der Samen
	#define ANSI_green ANSI_Poke_escape_fg"34m"
	#define ANSI_green_d ANSI_Poke_escape_fg"28m"//Oder "22m"
	//Der Körper
	#define ANSI_cyan ANSI_Poke_escape_fg"109m"
	#define ANSI_cyan_d ANSI_Poke_escape_fg"67m"
	//Die Augen
	#define ANSI_red ANSI_Poke_escape_fg"9m"
	#define ANSI_red_d ANSI_Poke_escape_fg"1m"
	//Die Flecken:
	#define ANSI_dcyan ANSI_Poke_escape_fg"23m"
	#define ANSI_dcyan_d ANSI_Poke_escape_fg"24m"
	//Graustufen
	#define ANSI_gray_1 ANSI_Poke_escape_fg"240m"
	#define ANSI_gray_2 ANSI_Poke_escape_fg"250m"
	//----------------------------------------------
	//Background-Colors (for use together with the partly Blocks
	#define ANSI_bg_Bf ANSI_Poke_escape_bg"0m"
	#define ANSI_bg_wh ANSI_Poke_escape_bg"15m"
	#define ANSI_bg_green ANSI_Poke_escape_bg"34m"
	#define ANSI_bg_green_d ANSI_Poke_escape_bg"28m"//Oder "22m"

	#define ANSI_bg_cyan ANSI_Poke_escape_bg"109m"
	#define ANSI_bg_cyan_d ANSI_Poke_escape_bg"67m"

	#define ANSI_bg_red ANSI_Poke_escape_bg"9m"
	#define ANSI_bg_red_d ANSI_Poke_escape_bg"1m"

	#define ANSI_bg_dcyan ANSI_Poke_escape_bg"23m"
	#define ANSI_bg_dcyan_d ANSI_Poke_escape_bg"24m"

	#define ANSI_bg_gray_1 ANSI_Poke_escape_bg"240m"
	#define ANSI_bg_gray_2 ANSI_Poke_escape_bg"250m"
	//----------------------------------------------
	#define ANSI_Poke_reset "\x1b[0m"
	//----------------------------------------------
	//----------------------------------------------
	printf("\n");//58 Lines of Picture, Pixel Signs: █ ▄ ▀ ■
	printf(" 1                         "ANSI_Bf"▄██▄"ANSI_Poke_reset"\n");//1
	printf(" 2                         "ANSI_Bf"█"ANSI_green"██"ANSI_Bf"█"ANSI_Poke_reset"\n");//2
	printf(" 3                    "ANSI_Bf"▄▄▄▄"ANSI_Bf"██"ANSI_green"██"ANSI_Bf"██"ANSI_Poke_reset"\n");//3
	printf(" 4                    "ANSI_Bf"█"ANSI_green_d"██"ANSI_Bf"██"ANSI_green"████"ANSI_Bf"██"ANSI_gray_1"▄"ANSI_Poke_reset"\n");//4
	printf(" 5            "ANSI_Bf"███████"ANSI_gray_1" "ANSI_Bf"█"ANSI_green_d"█"ANSI_Bf"██"ANSI_green"██████"ANSI_Bf"██████▄"ANSI_gray_1"▄▄▄\n"ANSI_Poke_reset);//5
	printf(" 6             "ANSI_Bf"██"ANSI_green"███"ANSI_green_d""ANSI_Bf"█████"ANSI_green"████████████"ANSI_Bf"██████████"ANSI_Bf"████████▄"ANSI_gray_1"▄▄▄"ANSI_Poke_reset"\n");//6
	printf(" 7              "ANSI_Bf"██"ANSI_green"██████"ANSI_Bf"███"ANSI_green"███████████████████████████"ANSI_Bf"████"ANSI_Bf"██████"ANSI_Poke_reset"\n");//7
	printf(" 8             "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"████████"ANSI_Bf"███"ANSI_green"██████████████████████████████"ANSI_Bf"██"ANSI_green"██"ANSI_Bf"███"ANSI_Poke_reset"\n");//8
	printf(" 9             "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"██████████"ANSI_Bf"██"ANSI_green"██████████████████████████████"ANSI_Bf"██"ANSI_green"███"ANSI_Bf"███"ANSI_Poke_reset"\n");//9
	printf("10             "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"███████████"ANSI_Bf"██"ANSI_green"██████████████████████████████"ANSI_Bf"██"ANSI_green"█"ANSI_green"███"ANSI_Bf"██"ANSI_Poke_reset"\n");//10
	printf("11             "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"████████████"ANSI_Bf"██"ANSI_green"██████████████████████████████"ANSI_Bf"██"ANSI_green"████"ANSI_Bf"██                 █████"ANSI_Poke_reset"\n");//11
	printf("12            "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"██████████████"ANSI_Bf"██"ANSI_green"█████████████"ANSI_Bf ANSI_bg_green"▄"ANSI_Bf"████"ANSI_green"████████████"ANSI_Bf"██"ANSI_green"████"ANSI_Poke_reset ANSI_Bf"██          ███████"ANSI_cyan"███"ANSI_Bf"██"ANSI_Poke_reset"\n");//12
	printf("13           "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"███████████████"ANSI_Bf"██"ANSI_green"████████████"ANSI_Bf"██"ANSI_cyan"███"ANSI_Bf"████"ANSI_green"█████████"ANSI_Bf"██"ANSI_green"██"ANSI_Bf ANSI_bg_green"▄▄"ANSI_Poke_reset ANSI_Bf"██"ANSI_Bf"▄▄▄▄▄▄  "ANSI_Bf"███"ANSI_cyan"██"ANSI_cyan"████████"ANSI_Bf"██"ANSI_Poke_reset"\n");//13
	printf("14           "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"████████████████"ANSI_Bf"██"ANSI_green"███████████"ANSI_Bf"██"ANSI_cyan"██████"ANSI_Bf ANSI_bg_cyan"███████████████▀▀▀▀▀▀▀▀████████"ANSI_cyan"████████"ANSI_cyan_d ANSI_bg_cyan"▄"ANSI_Bf"█"ANSI_Poke_reset"\n");//14
	printf("15          "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"██"ANSI_green"████████████████"ANSI_Bf"██"ANSI_green"██████████"ANSI_Bf"██"ANSI_cyan"██████████"ANSI_Bf"███"ANSI_cyan"████████████████████████████████"ANSI_cyan_d ANSI_bg_cyan"▄█"ANSI_Bf"██"ANSI_Poke_reset"\n");//15
	printf("16         "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"██"ANSI_green"██████████████████"ANSI_Bf"██"ANSI_green"█████████"ANSI_Bf"██"ANSI_cyan"████████████"ANSI_Bf"██"ANSI_cyan"███████████████████"ANSI_Bf"██████"ANSI_cyan"█████"ANSI_Bf ANSI_bg_cyan"▀"ANSI_Bf"█"ANSI_cyan_d"██"ANSI_Bf"█"ANSI_Poke_reset"\n");//16
	printf("17        "ANSI_Bf"█"ANSI_green"██"ANSI_Bf"█"ANSI_green"███████████████████"ANSI_Bf"██"ANSI_green"████████"ANSI_Bf"██"ANSI_cyan"███████████████████████████████"ANSI_Bf"████"ANSI_dcyan"███"ANSI_Bf"██"ANSI_cyan"██████"ANSI_Bf ANSI_bg_cyan"▀"ANSI_Bf"███"ANSI_Poke_reset"\n");//17
	printf("18       "ANSI_Bf"█"ANSI_green"██"ANSI_Bf"██"ANSI_green"███████████████████"ANSI_Bf"██"ANSI_green"███████"ANSI_Bf"██"ANSI_cyan_d"█"ANSI_cyan"████████████████████████████"ANSI_cyan"█"ANSI_Bf"███"ANSI_dcyan"█████"ANSI_Bf"██"ANSI_cyan"████████"ANSI_cyan"█"ANSI_Bf"██"ANSI_Poke_reset"\n");//18
	printf("19      "ANSI_Bf"█"ANSI_green"██"ANSI_Bf"██"ANSI_green"█████████████████████"ANSI_Bf"██"ANSI_green"██████"ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"███████████████████████████"ANSI_Bf"██"ANSI_dcyan"███████"ANSI_Bf"██"ANSI_cyan"██████████"ANSI_Bf"██"ANSI_Poke_reset"\n");//19
	printf("20     "ANSI_Bf"█"ANSI_green"██"ANSI_Bf"██"ANSI_green"███████████████████████"ANSI_Bf"██"ANSI_green"█████"ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"██████████████████████████"ANSI_Bf"██"ANSI_dcyan"███████"ANSI_Bf"██"ANSI_cyan"████████████"ANSI_Bf"██"ANSI_Poke_reset"\n");//20
	printf("21    "ANSI_Bf"██"ANSI_green"██"ANSI_Bf"██"ANSI_green"████████████████████████"ANSI_Bf"██"ANSI_green"████"ANSI_Bf"██"ANSI_cyan_d"███"ANSI_cyan"██████████████████████████"ANSI_Bf"████"ANSI_dcyan"███"ANSI_Bf"██"ANSI_cyan"██████████████"ANSI_Bf"██"ANSI_Poke_reset"\n");//21
	printf("22   "ANSI_Bf"██"ANSI_green"██"ANSI_Bf"██"ANSI_green"██████████████████████████"ANSI_Bf"██"ANSI_green"██"ANSI_Bf"██"ANSI_cyan_d"████"ANSI_cyan"███████████████████████"ANSI_Bf ANSI_bg_cyan"▄▄▄"ANSI_Poke_reset ANSI_cyan"███"ANSI_Bf"█████"ANSI_cyan"████████"ANSI_cyan"█"ANSI_Bf"██"ANSI_cyan"██"ANSI_cyan ANSI_bg_cyan"▄"ANSI_cyan"██"ANSI_Bf"██"ANSI_Poke_reset"\n");//22
	printf("23   "ANSI_Bf"█"ANSI_green"███"ANSI_Bf"██"ANSI_green"███████████████████████████"ANSI_Bf"█████"ANSI_cyan_d"████"ANSI_cyan"█████████████"ANSI_cyan"████"ANSI_Bf"███"ANSI_cyan"██"ANSI_Bf"█"ANSI_dcyan"███"ANSI_Bf"█"ANSI_cyan"████████████████"ANSI_Bf"█"ANSI_cyan"█"ANSI_cyan"█"ANSI_Bf ANSI_bg_cyan"▄██▄"ANSI_cyan"█"ANSI_Bf"██"ANSI_Poke_reset"\n");//23
	printf("24  "ANSI_Bf"██"ANSI_green"███"ANSI_Bf"██"ANSI_green"█████████████████████████████"ANSI_Bf"███"ANSI_cyan_d"████"ANSI_cyan"█████████"ANSI_Bf"███████"ANSI_cyan"███"ANSI_Bf"██"ANSI_cyan"██"ANSI_Bf"█"ANSI_dcyan"███"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"█████"ANSI_cyan"█"ANSI_Bf"██"ANSI_cyan"█"ANSI_Bf"█"ANSI_red"██"ANSI_Bf"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"██"ANSI_Poke_reset"\n");//24
	printf("25  "ANSI_Bf"██"ANSI_green"███"ANSI_Bf"██"ANSI_green"████████████████████████████"ANSI_Bf"███"ANSI_cyan_d"█████"ANSI_cyan"████████"ANSI_Bf"██"ANSI_wh"█"ANSI_Bf"██"ANSI_red"██"ANSI_Bf"██"ANSI_cyan"███"ANSI_Bf"██"ANSI_cyan"██"ANSI_Bf ANSI_bg_cyan"▀▀▀"ANSI_Poke_reset ANSI_cyan"████████"ANSI_Bf"██"ANSI_dcyan"██"ANSI_Bf"██"ANSI_cyan"████"ANSI_Bf"█"ANSI_wh"█"ANSI_red"█"ANSI_red_d"█"ANSI_Bf"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"█"ANSI_Poke_reset"\n");//25
	printf("26 "ANSI_Bf"██"ANSI_green_d"█"ANSI_green"███"ANSI_Bf"██"ANSI_green"██████████████████████████"ANSI_Bf"███"ANSI_cyan"█"ANSI_Bf"█"ANSI_cyan_d"█████"ANSI_cyan"███████"ANSI_Bf"██"ANSI_wh"█"ANSI_Bf"██"ANSI_red ANSI_bg_wh"█▀"ANSI_wh"█"ANSI_red"▀"ANSI_Poke_reset ANSI_Bf ANSI_bg_red"▀█"ANSI_Bf ANSI_bg_cyan"▄"ANSI_Poke_reset ANSI_cyan"███████████████"ANSI_Bf"██"ANSI_dcyan"████"ANSI_Bf"█"ANSI_cyan"█"ANSI_cyan"██"ANSI_Bf"█"ANSI_wh"█"ANSI_wh"██"ANSI_red"█"ANSI_Bf"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"██"ANSI_Poke_reset"\n");//26
	printf("27 "ANSI_Bf"██"ANSI_green_d"██"ANSI_green"██"ANSI_Bf"██"ANSI_green"█████████████████████████"ANSI_Bf"██"ANSI_cyan"██"ANSI_cyan"█"ANSI_Bf"█"ANSI_cyan_d"█████"ANSI_cyan"██████"ANSI_Bf"██"ANSI_wh"██"ANSI_Bf"█"ANSI_red"██"ANSI_wh"███"ANSI_red"██"ANSI_Bf"██"ANSI_cyan"██████████████"ANSI_Bf"██"ANSI_dcyan"████"ANSI_Bf"██"ANSI_cyan"██"ANSI_Bf"█"ANSI_wh"█"ANSI_wh"██"ANSI_red"█"ANSI_Bf"█"ANSI_wh"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"█"ANSI_Poke_reset"\n");//27
	printf("28 "ANSI_Bf"██"ANSI_green_d"███"ANSI_green"██"ANSI_Bf"██"ANSI_green"██████████████████████"ANSI_Bf"██"ANSI_cyan"█████"ANSI_Bf"█"ANSI_cyan_d"████"ANSI_cyan"██████"ANSI_Bf"██"ANSI_wh"██"ANSI_Bf"██"ANSI_red"██"ANSI_wh"███"ANSI_red"██"ANSI_red_d"█"ANSI_Bf"█"ANSI_cyan"███████████████"ANSI_Bf"███████"ANSI_cyan"██"ANSI_Bf"█"ANSI_red_d"█"ANSI_wh"█"ANSI_red"██"ANSI_red_d"█"ANSI_Bf"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"█"ANSI_Poke_reset"\n");//28
	printf("29 "ANSI_Bf"██"ANSI_green_d"█████"ANSI_Bf"██"ANSI_green"████████████████████"ANSI_Bf"███"ANSI_Bf ANSI_bg_cyan"▄"ANSI_Poke_reset ANSI_cyan"██████"ANSI_cyan_d"███"ANSI_cyan"███████"ANSI_Bf"██"ANSI_wh"██"ANSI_Bf"██"ANSI_red"██"ANSI_wh"███"ANSI_red"███"ANSI_Bf"██"ANSI_cyan"██████████████████"ANSI_cyan"██"ANSI_cyan"███"ANSI_Bf"█"ANSI_red_d"█"ANSI_red"███"ANSI_red_d"█"ANSI_Bf"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"██"ANSI_Poke_reset"\n");//29
	printf("30 "ANSI_Bf"██"ANSI_green_d"██████"ANSI_Bf"██"ANSI_green_d"██"ANSI_green"███████████████"ANSI_Bf"██"ANSI_dcyan"███"ANSI_Bf"███"ANSI_Bf ANSI_bg_cyan"▄"ANSI_Poke_reset ANSI_cyan"████████████"ANSI_Bf"██"ANSI_wh"███"ANSI_Bf"██"ANSI_red ANSI_bg_wh"██▄"ANSI_wh"█"ANSI_red"▄███"ANSI_Poke_reset ANSI_red_d"█"ANSI_Bf"██"ANSI_cyan"██████████████████████"ANSI_Bf"█"ANSI_red_d"█"ANSI_red"███"ANSI_Bf"█"ANSI_wh"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"██"ANSI_Bf"█"ANSI_Poke_reset"\n");//30
	printf("31  "ANSI_Bf"██"ANSI_green_d"██████"ANSI_Bf"██"ANSI_green_d"███"ANSI_green"██████████"ANSI_Bf"███"ANSI_dcyan"███████"ANSI_Bf"██"ANSI_cyan"████████████"ANSI_Bf"██"ANSI_wh"███"ANSI_Bf"██"ANSI_red"█████████"ANSI_Bf"██"ANSI_cyan"███████████████████████"ANSI_Bf"█"ANSI_red"███"ANSI_Bf"█"ANSI_Bf"██"ANSI_Bf"█"ANSI_cyan"██"ANSI_Bf"█"ANSI_Poke_reset"\n");//31
	printf("32   "ANSI_Bf"██"ANSI_green_d"██████"ANSI_Bf"██"ANSI_green_d"██████"ANSI_green"████"ANSI_Bf"███"ANSI_dcyan"████████"ANSI_Bf"██"ANSI_cyan"█████████████"ANSI_Bf"██"ANSI_wh"████"ANSI_Bf"█"ANSI_red_d"█"ANSI_red"████████"ANSI_Bf"██"ANSI_cyan"███████████████████████"ANSI_cyan"█"ANSI_Bf"████"ANSI_cyan"█████"ANSI_Bf"█"ANSI_Poke_reset"\n");//32
	printf("33   "ANSI_Bf"██"ANSI_green_d"███████"ANSI_Bf"███"ANSI_green_d"██████"ANSI_Bf"███"ANSI_dcyan"██████████"ANSI_Bf"██"ANSI_cyan"██████████████"ANSI_Bf"███"ANSI_wh"███"ANSI_Bf"██"ANSI_red"██████"ANSI_Bf"██"ANSI_cyan"█████████████████████████████████"ANSI_Bf"██"ANSI_Poke_reset"\n");//33
	printf("34    "ANSI_Bf"███"ANSI_green_d"██████"ANSI_Bf"█████"ANSI_green_d"█"ANSI_Bf"██"ANSI_cyan"██"ANSI_Bf"█"ANSI_dcyan"█████████"ANSI_Bf"██"ANSI_cyan"█████████████████"ANSI_Bf"█████████████"ANSI_cyan"█████████████████████████████"ANSI_Bf"█"ANSI_cyan"███"ANSI_Bf"██"ANSI_Poke_reset"\n");//34
	printf("35     "ANSI_Bf"███"ANSI_green_d"████████"ANSI_Bf"███"ANSI_cyan"████"ANSI_Bf"████"ANSI_dcyan"█████"ANSI_Bf"██"ANSI_cyan"███████████████"ANSI_Bf"██"ANSI_cyan"████████████████████████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"█"ANSI_cyan"██████"ANSI_Bf"████"ANSI_cyan"███"ANSI_Bf"█"ANSI_Poke_reset"\n");//35
	printf("36       "ANSI_Bf"████"ANSI_green_d"████"ANSI_Bf"███"ANSI_cyan"████████"ANSI_Bf ANSI_bg_cyan"██████▀"ANSI_Poke_reset ANSI_cyan"█████████████████"ANSI_Bf"████"ANSI_cyan"██████████████████████"ANSI_Bf"█"ANSI_cyan"██████"ANSI_Bf"█"ANSI_cyan"█████"ANSI_Bf"███"ANSI_cyan"████"ANSI_Bf"███"ANSI_Poke_reset"\n");//36
	printf("37          "ANSI_Bf"██"ANSI_green_d"██"ANSI_Bf"██"ANSI_cyan"███████████████████████████████████"ANSI_cyan"█"ANSI_Bf"█████████"ANSI_cyan"███"ANSI_cyan"█████████████████████"ANSI_Bf"█████"ANSI_cyan"████"ANSI_Bf"███"ANSI_Poke_reset"\n");//37
	printf("38            "ANSI_Bf"███"ANSI_cyan"██████████████████████████████"ANSI_Bf"█"ANSI_cyan"██████████"ANSI_cyan"███"ANSI_Bf"████████████"ANSI_Bf ANSI_bg_cyan"▄▄▄▄▄▄▄▄▄▄▄"ANSI_Bf"████"ANSI_cyan"█████"ANSI_Bf"████"ANSI_Poke_reset"\n");//38
	printf("39           "ANSI_Bf"██"ANSI_cyan"██████████████████"ANSI_Bf"██"ANSI_cyan"████████████"ANSI_Bf"████"ANSI_cyan"████████████████████"ANSI_Bf ANSI_bg_cyan"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"ANSI_cyan"█████"ANSI_Bf"███"ANSI_Poke_reset"\n");//39
	printf("40          "ANSI_Bf"██"ANSI_cyan"█████████████"ANSI_Bf"██"ANSI_cyan"███"ANSI_Bf"██"ANSI_cyan"███████████████"ANSI_Bf"██████"ANSI_cyan"████████████████████████████████"ANSI_Bf"█████"ANSI_Poke_reset"\n");//40
	printf("41         "ANSI_Bf"██"ANSI_cyan"███"ANSI_cyan"██████"ANSI_cyan"██████"ANSI_Bf"██"ANSI_cyan"█"ANSI_Bf"██"ANSI_cyan"█████████████████"ANSI_cyan_d ANSI_bg_cyan"▀███"ANSI_Poke_reset ANSI_Bf"██████"ANSI_cyan"███████████████████████"ANSI_Bf"█████"ANSI_cyan"███"ANSI_Bf"██"ANSI_Poke_reset"\n");//41
	printf("42        "ANSI_Bf"███"ANSI_cyan"███"ANSI_Bf ANSI_bg_cyan"█████▄▄▄"ANSI_Poke_reset ANSI_cyan"█████"ANSI_Bf"███"ANSI_cyan"██████████████████"ANSI_Bf"██"ANSI_cyan_d"██████"ANSI_Bf"██████████████████████████"ANSI_cyan_d ANSI_bg_cyan"██▀"ANSI_cyan"█████"ANSI_Bf"███"ANSI_Poke_reset"\n");//42
	printf("43        "ANSI_Bf"██"ANSI_cyan"██"ANSI_Bf"███"ANSI_dcyan"██████"ANSI_Bf"█"ANSI_cyan"██████"ANSI_Bf"██"ANSI_cyan"███████"ANSI_Bf"████"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"██████████"ANSI_cyan_d ANSI_bg_cyan"█████████████████████▀"ANSI_Poke_reset ANSI_cyan"█████████"ANSI_Bf"██"ANSI_Poke_reset"\n");//43
	printf("44        "ANSI_Bf"██"ANSI_cyan"█"ANSI_Bf"██"ANSI_dcyan"███████"ANSI_Bf"██"ANSI_cyan"█████"ANSI_Bf"██"ANSI_cyan"█████"ANSI_Bf"████"ANSI_dcyan"██"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"██████████████████████████████"ANSI_cyan"████████████"ANSI_Bf"██"ANSI_Poke_reset"\n");//44
	printf("45       "ANSI_Bf"██"ANSI_cyan"███"ANSI_Bf"███"ANSI_dcyan"████"ANSI_Bf"██"ANSI_cyan"██████"ANSI_Bf"██"ANSI_cyan"████"ANSI_Bf"██"ANSI_dcyan"█████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"█████████████████████████████"ANSI_cyan"█████████"ANSI_Bf ANSI_bg_cyan"▄▄▄"ANSI_cyan"█"ANSI_Bf"██"ANSI_Poke_reset"\n");//45
	printf("46       "ANSI_Bf"██"ANSI_cyan"█████"ANSI_Bf"███"ANSI_dcyan"█"ANSI_Bf"██"ANSI_cyan"███████"ANSI_Bf"██"ANSI_cyan"███"ANSI_Bf"█"ANSI_dcyan"███████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d ANSI_bg_cyan"█████████████████████████████"ANSI_Poke_reset ANSI_cyan"████████"ANSI_Bf"██"ANSI_dcyan"█"ANSI_Bf ANSI_bg_cyan"█▄"ANSI_cyan"█"ANSI_Bf"██"ANSI_Poke_reset"\n");//46
	printf("47       "ANSI_Bf"██"ANSI_cyan"███████"ANSI_Bf"███"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan"███"ANSI_Bf"█"ANSI_dcyan"███████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"█████████████████████████"ANSI_Bf"██"ANSI_cyan_d"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_dcyan"███"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"██"ANSI_Poke_reset"\n");//47
	printf("48       "ANSI_Bf"██"ANSI_cyan"██████████████████"ANSI_Bf"██"ANSI_cyan"████"ANSI_Bf"█"ANSI_dcyan"██████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"███████████████████████"ANSI_Bf"███"ANSI_cyan_d"██"ANSI_cyan"███████"ANSI_Bf"██"ANSI_dcyan"████"ANSI_Bf"█"ANSI_cyan"██"ANSI_Bf"██"ANSI_Poke_reset"\n");//48
	printf("49       "ANSI_Bf"███"ANSI_cyan_d ANSI_bg_cyan"▄"ANSI_Poke_reset ANSI_cyan"████████████████"ANSI_Bf"██"ANSI_cyan_d"█"ANSI_cyan"████"ANSI_Bf"█"ANSI_dcyan"█████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"███████████████████"ANSI_Bf"█████"ANSI_cyan_d"████"ANSI_cyan"███████"ANSI_Bf"█"ANSI_dcyan"█████"ANSI_Bf"█"ANSI_cyan"██"ANSI_Bf"██"ANSI_Poke_reset"\n");//49
	printf("50        "ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"███████████████"ANSI_Bf"██"ANSI_cyan_d"█"ANSI_cyan"█████"ANSI_Bf"█"ANSI_dcyan"███"ANSI_Bf"██"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"████████████████"ANSI_Bf"█████ "ANSI_Bf"██"ANSI_cyan_d"████"ANSI_cyan"███████"ANSI_Bf"███"ANSI_dcyan"██"ANSI_Bf"██"ANSI_cyan"██"ANSI_Bf"██"ANSI_Poke_reset"\n");//50
	printf("51        "ANSI_Bf"██"ANSI_cyan_d"███"ANSI_cyan_d ANSI_bg_cyan"▄"ANSI_Poke_reset ANSI_cyan"████████████"ANSI_cyan_d ANSI_bg_cyan"▄"ANSI_Poke_reset ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"█████"ANSI_Bf"████"ANSI_cyan"█████████"ANSI_Bf"████"ANSI_cyan_d"██████"ANSI_Bf"██████████     "ANSI_Bf"██"ANSI_cyan_d"████"ANSI_cyan"████████"ANSI_Bf"████"ANSI_cyan"███"ANSI_Bf"██"ANSI_Poke_reset"\n");//51
	printf("52         "ANSI_Bf"██"ANSI_cyan_d"███████"ANSI_cyan_d ANSI_bg_cyan"▄▄▄▄▄▄"ANSI_Poke_reset ANSI_cyan_d"████"ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"███████"ANSI_cyan"█████████"ANSI_Bf"██"ANSI_cyan_d"██"ANSI_Bf"████████"ANSI_cyan"█████"ANSI_Bf ANSI_bg_cyan"▄"ANSI_Poke_reset ANSI_Bf"█""        "ANSI_Bf"██"ANSI_cyan_d"███"ANSI_cyan"██████████████"ANSI_Bf"██"ANSI_Poke_reset"\n");//52
	printf("53         "ANSI_Bf"██"ANSI_cyan_d"█████████████████"ANSI_Bf"██"ANSI_cyan_d"███"ANSI_cyan"███████████████"ANSI_Bf"█"ANSI_cyan_d"███"ANSI_cyan_d ANSI_bg_cyan"▄"ANSI_Poke_reset ANSI_cyan"███████████"ANSI_Bf"██         "ANSI_Bf"██"ANSI_cyan_d"████"ANSI_cyan"███████████"ANSI_Bf ANSI_bg_cyan"▄▄"ANSI_Poke_reset ANSI_Bf"██"ANSI_Poke_reset"\n");//53
	printf("54          "ANSI_Bf"██"ANSI_cyan_d"██"ANSI_Bf ANSI_bg_cyan_d"▄▄▄▄▄"ANSI_Poke_reset ANSI_cyan_d"█████"ANSI_Bf ANSI_bg_cyan_d"▄▄▄▄"ANSI_Poke_reset ANSI_Bf"███"ANSI_cyan_d"███"ANSI_cyan"█████████████"ANSI_Bf"███"ANSI_cyan_d"█"ANSI_Bf ANSI_bg_cyan_d"▄▄▄"ANSI_bg_cyan"▄▄▄▄▄▄▄"ANSI_Poke_reset ANSI_cyan"█"ANSI_Bf ANSI_bg_cyan"▄"ANSI_Poke_reset ANSI_Bf"█▀           "ANSI_Bf"███"ANSI_cyan_d"██"ANSI_cyan"███████"ANSI_Bf ANSI_bg_cyan"▄▄▄▄█"ANSI_Poke_reset ANSI_wh ANSI_bg_Bf"██▄"ANSI_Bf"█"ANSI_Poke_reset"\n");//54
	printf("55           "ANSI_Bf"████"ANSI_wh ANSI_bg_Bf"██▄"ANSI_Poke_reset ANSI_Bf"█"ANSI_Bf ANSI_bg_cyan_d"▄▄▄▄▄"ANSI_Poke_reset ANSI_Bf"█"ANSI_wh ANSI_bg_Bf"██▄"ANSI_Poke_reset ANSI_Bf"█"ANSI_gray_1" "ANSI_Bf"█"ANSI_cyan_d"████"ANSI_cyan"████████"ANSI_Bf ANSI_bg_cyan"▄▄▄▄"ANSI_Bf"█"ANSI_Poke_reset" "ANSI_Poke_reset ANSI_Bf"▀▀"ANSI_Bf"█"ANSI_wh ANSI_bg_Bf"█▄"ANSI_Poke_reset ANSI_Bf"█"ANSI_wh ANSI_bg_Bf"█▄"ANSI_Poke_reset ANSI_Bf"█" ANSI_wh ANSI_bg_Bf"█▄"ANSI_Poke_reset ANSI_Bf"██"ANSI_Poke_reset ANSI_Bf"▀"ANSI_Poke_reset"               "ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"██"ANSI_Bf ANSI_bg_cyan"▄▄▄▄"ANSI_Poke_reset ANSI_Bf"█"ANSI_wh ANSI_bg_Bf"██▄"ANSI_Poke_reset ANSI_Bf"█▀▀▀▀"ANSI_Poke_reset"\n");//55
	printf("56             "ANSI_Bf" ▀▀▀▀▀█"ANSI_wh ANSI_bg_Bf"██▄"ANSI_Poke_reset ANSI_Bf"█▀▀▀▀▀ "ANSI_Bf"█"ANSI_Bf"█"ANSI_cyan_d"██"ANSI_Bf ANSI_bg_cyan_d"▄▄▄"ANSI_Bf ANSI_bg_cyan"▄▄▄▄▄▄"ANSI_Poke_reset ANSI_Bf"█"ANSI_wh ANSI_bg_Bf"██▄"ANSI_Bf"█"ANSI_Poke_reset"   "ANSI_Poke_reset ANSI_Bf"▀▀▀▀▀▀▀▀▀▀"ANSI_Poke_reset"                  "ANSI_Bf"██████"ANSI_wh ANSI_bg_Bf"██▄"ANSI_Poke_reset ANSI_Bf"█▀▀▀▀"ANSI_Poke_reset"\n");//56
	printf("57                "ANSI_Bf"   ▀▀▀▀▀       "ANSI_Bf"▀██"ANSI_Bf"█"ANSI_wh ANSI_bg_Bf"██▄"ANSI_Bf"██"ANSI_wh ANSI_bg_Bf"██▄"ANSI_Poke_reset ANSI_Bf"█▀▀▀▀"ANSI_Poke_reset"                                    "ANSI_Bf"▀▀▀▀▀"ANSI_Poke_reset"\n");//57
	printf("58                                  "ANSI_Poke_reset ANSI_Bf"▀▀▀▀▀▀▀▀▀▀"ANSI_Poke_reset"\n");//58
	printf(ANSI_Poke_reset"\n");
	//----------------------------------------------
	//----------------------------------------------
	#undef ANSI_poke_ESC
	//256-color mode:
	#undef ANSI_Poke_escape
	//----------------------------------------------
	#undef ANSI_Bf
	#undef ANSI_wh
	//Der Samen
	#undef ANSI_green
	#undef ANSI_green_d
	//Der Körper
	#undef ANSI_cyan
	#undef ANSI_cyan_d
	//Die Augen
	#undef ANSI_red
	#undef ANSI_red_d
	//Die Flecken:
	#undef ANSI_dcyan
	#undef ANSI_dcyan_d
	//----------------------------------------------
	#undef ANSI_gray_1
	#undef ANSI_gray_2
	//----------------------------------------------
#undef ANSI_Poke_reset
}







void print_ASCII_ANSI_Pokemon_Bulbasaur(){
	#define ANSI_poke_ESC "\033"
	//256-color mode:
	#define ANSI_Poke_escape ANSI_poke_ESC"[38;5;"
	//----------------------------------------------
	#define ANSI_Bf ANSI_Poke_escape"0m"
	#define ANSI_wh ANSI_Poke_escape"15m"
	//Der Samen
	#define ANSI_green ANSI_Poke_escape"34m"
	#define ANSI_green_d ANSI_Poke_escape"22m"
	//Der Körper
	#define ANSI_cyan ANSI_Poke_escape"109m"
	#define ANSI_cyan_d ANSI_Poke_escape"67m"
	//Die Augen
	#define ANSI_red ANSI_Poke_escape"9m"
	#define ANSI_red_d ANSI_Poke_escape"1m"
	//Die Flecken:
	#define ANSI_dcyan ANSI_Poke_escape"23m"
	#define ANSI_dcyan_d ANSI_Poke_escape"24m"
	//----------------------------------------------
	#define ANSI_gray_1 ANSI_Poke_escape"240m"
	#define ANSI_gray_2 ANSI_Poke_escape"250m"
	//----------------------------------------------
	#define ANSI_Poke_reset "\x1b[0m"
	//----------------------------------------------
	//----------------------------------------------
	printf("\n");//58 Lines of Picture
	printf(" 1                          "ANSI_Bf"B;\n");//1
	printf(" 2                        "ANSI_Bf".B"ANSI_green_d"B"ANSI_Bf"B""\n");//2
	printf(" 3                        "ANSI_Bf"B"ANSI_green_d"u,G"ANSI_Bf"B.\n");//3
	printf(" 4                      "ANSI_Bf"rO"ANSI_green_d"E"ANSI_green":r:5"ANSI_green_d"8"ANSI_Bf"P"ANSI_gray_1":\n");//4
	printf(" 5            "ANSI_Bf".GB8OON"ANSI_gray_1"u,S"ANSI_Bf"BG"ANSI_green"rirrir2OO"ANSI_Bf"MZq"ANSI_gray_1"52LLrr"ANSI_gray_2"ii::.\n"ANSI_Bf);//5
	printf(" 6             "ANSI_Bf".Q"ANSI_green"7ir"ANSI_green_d"LUPOE"ANSI_Bf"QF"ANSI_green":rr7rrirr"ANSI_green_d"LJ15PqZE88OOBMBM"ANSI_Bf"Gur:,\n");//6
	printf(" 7              "ANSI_Bf"LG"ANSI_green":rrriiiu"ANSI_Bf"BZ"ANSI_green":ir7r7r7rr:ririii;i:irrvug"ANSI_green_d"OßB@"ANSI_Bf"BOX5r\n");//7
	printf(" 8             "ANSI_Bf"G"ANSI_green"8"ANSI_Bf"B"ANSI_green"rirr7rr:i"ANSI_Bf"8@"ANSI_green"rir777r7r7r7r7r7r7rrr7rrii:r"ANSI_green_d"YM@OJN"ANSI_Bf"BMv\n");//8
	printf(" 9             "ANSI_Bf"q"ANSI_green"k"ANSI_Bf"@"ANSI_green"rrr777r7i."ANSI_Bf"F@"ANSI_green"7ir7r777r7r7r77777r7r7r7rrii:v"ANSI_Bf"M@"ANSI_green"r:"ANSI_Bf"LBBu\n");//9
	printf("10             "ANSI_Bf"Z"ANSI_green"Z"ANSI_Bf"@"ANSI_green"i;7r777r7r:"ANSI_Bf"1@"ANSI_green"iir7r7r7r7r7r7r7r7r7r7r7r7rri:"ANSI_Bf"2@"ANSI_green_d"U"ANSI_green":;"ANSI_Bf"7B@\n");//10
	printf("11             "ANSI_Bf"G"ANSI_green"E"ANSI_Bf"O"ANSI_green":rr7r7r7r7;:"ANSI_Bf"B@"ANSI_green":rr7r777r7r7r7riiiirr7r777r7i:"ANSI_green_d"v"ANSI_Bf"@Y"ANSI_green":i:"ANSI_Bf"B@                 .,ii.\n");//11
	printf("12            "ANSI_Bf"F"ANSI_green"8"ANSI_Bf"@"ANSI_green"vir777r7r7r7i7"ANSI_Bf"Bj"ANSI_green":rr777r7r7r7ii"ANSI_Bf"v5uL"ANSI_green"ri:;r7r7rri,"ANSI_Bf"5G"ANSI_green"::::"ANSI_Bf"G7           .rXMG"ANSI_cyan_d"BBOM"ANSI_Bf"BB\n");//12
	printf("13           "ANSI_Bf".B"ANSI_green"O"ANSI_Bf"M"ANSI_green":r7r7r7r7r7rr:"ANSI_Bf"MB"ANSI_green":i7r7r777r7ii"ANSI_Bf"MG"ANSI_cyan_d"ZOBQ"ANSI_Bf"BZL"ANSI_green"i:i:iirru"ANSI_Bf"B"ANSI_green_d"Z5O"ANSI_Bf"PGB"ANSI_gray_1"LYujY7r::"ANSI_Bf"OGM"ANSI_cyan_d"Pv"ANSI_cyan"i::.,.,"ANSI_Bf"BQ\n");//13
	printf("14           "ANSI_Bf"B"ANSI_green"5"ANSI_Bf"B"ANSI_green"7i7r777r7r777ri7"ANSI_Bf"Gv"ANSI_green"ir7r7r7rri:"ANSI_Bf"BG"ANSI_cyan",..,:v"ANSI_Bf"kGBOUPOGBMEP55uj7L2S5kkqOG8G8kJ"ANSI_cyan"vi::i::,."ANSI_Bf"BJ\n");//14
	printf("15          "ANSI_Bf"B"ANSI_green"P"ANSI_Bf"8P"ANSI_green":7r777r7r777r7r:"ANSI_Bf"BG"ANSI_green":rr7r7r7r:"ANSI_Bf"FG"ANSI_cyan":.::::..."ANSI_cyan_d"i"ANSI_Bf"FGB"ANSI_cyan_d"7"ANSI_cyan"::.......,.,,,,,.,.    ,:::iii:i,"ANSI_Bf"vB\n");//15
	printf("16         "ANSI_Bf"O"ANSI_green"O"ANSI_Bf"kG"ANSI_green":rr7r7r7r7r7r7r7:j"ANSI_Bf"G7"ANSI_green"i7r7r7rii"ANSI_Bf"GN"ANSI_cyan",:i:i:i::,.."ANSI_cyan_d"v:"ANSI_cyan",:::::i:::i:i:::,..:"ANSI_cyan_d"L"ANSI_Bf"5GOGu"ANSI_cyan",:i:i::."ANSI_Bf"GY\n");//16
	printf("17        "ANSI_Bf"Z"ANSI_green"Gv"ANSI_Bf"G"ANSI_green"iir777r7r7r7r777rr:"ANSI_Bf"GM"ANSI_green":;7r7rr:"ANSI_Bf"OB"ANSI_cyan_d"i"ANSI_cyan":::i:i:i:l::,::i:i:i:i:i:i::.."ANSI_cyan_d"i2"ANSI_Bf"OGB"ANSI_dcyan"ONP"ANSI_Bf"BL"ANSI_cyan".iii::i"ANSI_cyan_d"G"ANSI_Bf"XG\n");//17
	printf("18       "ANSI_Bf"G"ANSI_green"Q:"ANSI_Bf"Gu"ANSI_green":r7r7r7r7r7r7r777r:"ANSI_Bf"jG"ANSI_green"7:r7r7ii"ANSI_Bf"BP"ANSI_cyan":::i:i:i:iii:i:i:i:i:i:i:i::."ANSI_cyan_d"v"ANSI_Bf"OGM"ANSI_dcyan"ESFFF"ANSI_Bf"GB"ANSI_cyan".::i:i:,"ANSI_cyan_d"L"ANSI_Bf"GB\n");//18
	printf("19      "ANSI_Bf"O"ANSI_green"G."ANSI_Bf"GO"ANSI_green":r7r7r777r7r7r7r7r7;:"ANSI_Bf"BG"ANSI_green":ir7r:"ANSI_Bf"UG"ANSI_cyan_d"i"ANSI_cyan"i:::i:i:i:i:iii:i:iiiii:i::."ANSI_Bf"MB"ANSI_dcyan"ZFkFkFF"ANSI_Bf"GG"ANSI_cyan":,:i:i:i:,"ANSI_Bf"rG:\n");//19
	printf("20     "ANSI_Bf"G"ANSI_green"Q."ANSI_Bf"JB"ANSI_green";ir77r7r7r7r7r7r7r7r7ir"ANSI_Bf"BB"ANSI_green":irr:"ANSI_Bf"GO"ANSI_cyan_d":r"ANSI_cyan"i:i:i:iii:i:i:i:i:i:i:i::,."ANSI_Bf"7G"ANSI_dcyan"B8kkFF"ANSI_Bf"8Gi"ANSI_cyan".:i:i:i:::."ANSI_Bf"rG\n");//20
	printf("21    "ANSI_Bf"uG"ANSI_green"::"ANSI_Bf"BG"ANSI_green":rr7r7r7r7r7r7r7r7r7rr:v"ANSI_Bf"BG"ANSI_green":::r"ANSI_Bf"BL"ANSI_cyan_d":7i"ANSI_cyan"::i:iii:i:i:i:i:i,::i::.i:.."ANSI_Bf"7qG"ANSI_dcyan_d"BB"ANSI_Bf"GGi"ANSI_cyan".:::i:i,:::, "ANSI_Bf"YG\n");//21
	printf("22   "ANSI_Bf".G"ANSI_green"7:"ANSI_Bf"7G"ANSI_green"7ir7r7r7r7r7r7r777r7r7rr:r"ANSI_Bf"BG"ANSI_green"u."ANSI_Bf"uG"ANSI_cyan_d":;rr"ANSI_cyan":iiiii:i::::::::"ANSI_cyan"i"ANSI_cyan"O"ANSI_cyan_d"r"ANSI_cyan".:::"ANSI_cyan"EGG"ANSI_cyan":...,"ANSI_cyan_d"7"ANSI_Bf"u"ANSI_cyan_d"J"ANSI_cyan",.:,.,:i"ANSI_cyan_d","ANSI_Bf"jU"ANSI_cyan"."ANSI_cyan_d","ANSI_Bf"i"ANSI_cyan_d":"ANSI_cyan","ANSI_Bf"kG\n");//22
	printf("23   "ANSI_Bf"G"ANSI_green"O::"ANSI_Bf"SG"ANSI_green"ii7r7r7r7r777r7r7r7r7r7rri:"ANSI_Bf"uGZGZ"ANSI_cyan_d":;7r"ANSI_cyan"::i:i:i::.:"ANSI_cyan_d"7i"ANSI_cyan",..,"ANSI_Bf"7GD"ANSI_cyan".."ANSI_Bf"u"ANSI_dcyan"BqMG"ANSI_cyan",:::...:,."ANSI_cyan_d"r"ANSI_cyan"Z"ANSI_cyan_d"7"ANSI_cyan".,:"ANSI_Bf"B"ANSI_cyan_d"i"ANSI_cyan":"ANSI_Bf"GBU"ANSI_cyan_d"k"ANSI_cyan"."ANSI_Bf"Gq\n");//23
	printf("24  "ANSI_Bf";B"ANSI_green"7i:"ANSI_Bf"8G"ANSI_green":rr7r7r7r7r7r7r7r7r7r7r7rri:."ANSI_Bf"ZGY"ANSI_cyan_d":rrr"ANSI_cyan":i:i:i:,:"ANSI_Bf"MO"ANSI_gray_1"u"ANSI_Bf"GGBJ"ANSI_cyan"..,"ANSI_Bf"GB"ANSI_cyan",."ANSI_Bf"u"ANSI_dcyan"GGG"ANSI_cyan"::i:i::,."ANSI_Bf"1GGGr"ANSI_cyan":"ANSI_Bf"uG"ANSI_cyan_d"."ANSI_Bf"G"ANSI_red"qG"ANSI_gray_1"7:"ANSI_Bf"M"ANSI_cyan":"ANSI_Bf"G.\n");//24
	printf("25  "ANSI_Bf"QG"ANSI_green"rr:"ANSI_Bf"OB"ANSI_green":r7r7r7r7r7r777r7r7r7r7rr;:i"ANSI_Bf"MGG"ANSI_cyan_d"iir77"ANSI_cyan"i:i:i:."ANSI_cyan_d"r"ANSI_Bf"GJ"ANSI_wh" "ANSI_Bf"7G"ANSI_red"Ok"ANSI_Bf"BQ"ANSI_cyan";.,"ANSI_Bf"G2"ANSI_cyan".."ANSI_cyan_d"r"ANSI_Bf"k"ANSI_cyan"i,i:i:::."ANSI_Bf"XG"ANSI_dcyan"S1"ANSI_Bf"OG"ANSI_cyan":i:r"ANSI_Bf"B"ANSI_wh" "ANSI_red":"ANSI_red_d"G"ANSI_gray_2".:"ANSI_Bf"G"ANSI_cyan"F"ANSI_Bf"Q\n");//25
	printf("26 "ANSI_Bf"iG"ANSI_green"vv7:"ANSI_Bf"qG"ANSI_green":rr7r7r7r777r7r7r7r7r7rrii"ANSI_Bf"PGk"ANSI_cyan_d"r"ANSI_Bf"B"ANSI_cyan_d"ii777"ANSI_cyan":iii:,"ANSI_cyan_d"i"ANSI_Bf"G:"ANSI_wh" "ANSI_Bf"iG"ANSI_red"8"ANSI_wh"   "ANSI_Bf"BG"ANSI_cyan";.,i::,.,::i:i:,"ANSI_Bf"1G"ANSI_dcyan"SSFk"ANSI_Bf"B"ANSI_cyan_d"i"ANSI_cyan".."ANSI_cyan_d"F"ANSI_Bf"G"ANSI_wh"  "ANSI_red"M"ANSI_Bf"G"ANSI_wh" "ANSI_Bf"8"ANSI_cyan"u"ANSI_Bf"G:\n");//26
	printf("27 "ANSI_Bf"MG"ANSI_green"r7Ji"ANSI_Bf"YG"ANSI_green":irr7r7r7r7r7r7r7r7rr;i:1"ANSI_Bf"BG"ANSI_cyan"i."ANSI_cyan_d"v"ANSI_Bf"G"ANSI_cyan_d":rr7;"ANSI_cyan"::i::,"ANSI_Bf"GL"ANSI_wh"  "ANSI_Bf"G"ANSI_red"BJ"ANSI_wh"   "ANSI_red"1B"ANSI_Bf"Gi"ANSI_cyan".:::i:i:i:i:::"ANSI_Bf"GB"ANSI_dcyan"EkX2"ANSI_Bf"Gu"ANSI_cyan".."ANSI_cyan_d"O"ANSI_Bf"N"ANSI_wh"  "ANSI_red"G"ANSI_Bf"Q"ANSI_gray_2","ANSI_wh" "ANSI_Bf"G"ANSI_cyan"P"ANSI_Bf"G\n");//27
	printf("28 "ANSI_Bf"BB"ANSI_green"rLvLi"ANSI_Bf"Gk"ANSI_green":r777r7r7r7r777r7rr::v"ANSI_Bf"MG"ANSI_cyan"i:.."ANSI_Bf"FG"ANSI_cyan_d":rvr"ANSI_cyan"::i::."ANSI_Bf"OB"ANSI_wh"  "ANSI_Bf".B"ANSI_red"Or"ANSI_wh"   "ANSI_red"LP"ANSI_red_d"B"ANSI_Bf"G"ANSI_cyan",,:i:i:i:i:i::;"ANSI_Bf"1EMBGBu"ANSI_cyan".."ANSI_cyan_d"M"ANSI_gray_1"U"ANSI_wh" "ANSI_red",N"ANSI_red_d"G"ANSI_gray_1"1"ANSI_wh" "ANSI_Bf"B"ANSI_cyan"Y"ANSI_Bf"B\n");//28
	printf("29 "ANSI_Bf"MB"ANSI_green"77LLr"ANSI_Bf"PG"ANSI_green"iir7r7r777r7r7rri::j"ANSI_Bf"MGE"ANSI_cyan"r;r:,i"ANSI_cyan_d"Jr7r"ANSI_cyan"i:ii:,:"ANSI_Bf"Bi"ANSI_wh"  "ANSI_Bf"rG"ANSI_red"OJ"ANSI_wh"   "ANSI_red"Uq5"ANSI_Bf"BG"ANSI_cyan".::i:i:i:i:i:,..,:"ANSI_cyan_d"rr"ANSI_cyan",:."ANSI_cyan_d"O"ANSI_red_d"B"ANSI_red":kP"ANSI_red_d"8"ANSI_gray_1"X"ANSI_wh" "ANSI_Bf"G"ANSI_cyan"r"ANSI_Bf"G"ANSI_gray_1",\n");//29
	printf("30 "ANSI_Bf":G"ANSI_green"u7vL77"ANSI_Bf"BG"ANSI_green":i:rrrr7r7r7rr:iU"ANSI_Bf"GG"ANSI_dcyan"8XZ"ANSI_Bf"OMBG"ANSI_cyan":,,i:::i:i:,"ANSI_Bf"LG"ANSI_wh"   "ANSI_Bf"7B"ANSI_red"q0"ANSI_wh"   "ANSI_red"GNU"ANSI_red_d"Z"ANSI_Bf"B"ANSI_cyan_d"i"ANSI_cyan".I:i:i:i:i:i:i::,,,::."ANSI_cyan_d"J"ANSI_gray_1"g"ANSI_red"kP5"ANSI_red_d"G"ANSI_gray_1"i"ANSI_wh" "ANSI_Bf"B"ANSI_cyan":"ANSI_Bf"P2\n");//30
	printf("31  "ANSI_Bf"OG"ANSI_green"rvvLrL"ANSI_Bf"BG"ANSI_green"rr77r7rriri:i"ANSI_Bf"FBG"ANSI_dcyan"051S15U"ANSI_Bf"GB"ANSI_cyan",:::::i:i::."ANSI_Bf"SG"ANSI_wh"   "ANSI_Bf".G"ANSI_red"q0SiXZkS1"ANSI_Bf"G2"ANSI_cyan".:i:i:iii:i:i:i:i:i:i,i"ANSI_Bf"B"ANSI_red"PFX"ANSI_red_d"G"ANSI_gray_1"r2"ANSI_Bf"G"ANSI_cyan".u"ANSI_Bf"8\n");//31
	printf("32   "ANSI_Bf"BZ"ANSI_green"iLvLrL"ANSI_Bf"GG"ANSI_green"Yr7LvLv7;v"ANSI_Bf"kGM"ANSI_dcyan"q1FFkSS2"ANSI_Bf"0B"ANSI_cyan":.::i:i:i:i:,"ANSI_Bf"YG"ANSI_wh"    "ANSI_Bf"B"ANSI_red_d"G"ANSI_red"2NN0kk51"ANSI_Bf"BO"ANSI_cyan".::i:i:iii:i:i:i:i:i::."ANSI_cyan_d"k"ANSI_Bf"BBO"ANSI_cyan_d"O"ANSI_cyan"ur.."ANSI_Bf"LB\n");//32
	printf("33   "ANSI_Bf"vG"ANSI_green"qivvLr7"ANSI_Bf"GGO"ANSI_green"Yr777u"ANSI_Bf"BBG"ANSI_dcyan"q11kSXFk1G"ANSI_Bf"G"ANSI_cyan_d"r"ANSI_cyan".::i:i:i:i:i:,"ANSI_Bf"88r"ANSI_gray_1","ANSI_wh" "ANSI_Bf".B"ANSI_red"8FXSSFk5"ANSI_Bf"Gk"ANSI_cyan".:i:i:i:iii:i:i:i:i:i::.::,..."ANSI_cyan_d"X"ANSI_cyan":"ANSI_Bf"1M\n");//33
	printf("34    "ANSI_Bf"7BG"ANSI_green"777L7r"ANSI_Bf"LOGM1"ANSI_green"2"ANSI_Bf"BG"ANSI_cyan_d"rq"ANSI_Bf"B"ANSI_dcyan"N5FSkSk1G"ANSI_Bf"G"ANSI_cyan_d"v"ANSI_cyan".::i:iii:i:i::i::"ANSI_Bf"1EOSMBBBGBBMMX"ANSI_cyan"::i:i:i:i:i:::i:i:i:::i::::..."ANSI_cyan_d"L"ANSI_Bf"B"ANSI_cyan"."ANSI_Bf"GL\n");//34
	printf("35     "ANSI_Bf".BG"ANSI_green"ZLr777ii"ANSI_Bf"1GB"ANSI_cyan"j..:"ANSI_Bf"XBGB"ANSI_dcyan"ONPSM"ANSI_Bf"G7"ANSI_cyan".::iii:iii:i:i,"ANSI_Bf"vB"ANSI_cyan":,,....,::::,..,::i:i:i:i"ANSI_Bf"1"ANSI_cyan":::i:i::"ANSI_Bf"UL"ANSI_cyan":,:..,"ANSI_Bf"r50k"ANSI_cyan":"ANSI_Bf"BG\n");//35
	printf("36       "ANSI_Bf"iQBQ"ANSI_green"Xjrr"ANSI_Bf"EGu"ANSI_cyan"..:::.,i"ANSI_Bf"JNMBGM"ANSI_cyan"i.::iii:i:i:i:i::."ANSI_Bf"PBq7i"ANSI_cyan",...,....,,::::::::::,"ANSI_Bf"uO"ANSI_cyan"i::::"ANSI_Bf"1"ANSI_cyan":,:.i"ANSI_Bf"uqMZY"ANSI_cyan":L"ANSI_Bf"GM\n");//36
	printf("37          "ANSI_Bf"vq"ANSI_green"XM"ANSI_Bf"BM"ANSI_cyan":.:::i:::,...::..::i:i:i:i:i::,:::."ANSI_cyan_d"rk"ANSI_Bf"MBGBMZEF2"ANSI_cyan_d"Lvr"ANSI_cyan"rii:::,,..,.,.i,::ir"ANSI_cyan_d"L"ANSI_Bf"jEMMX7"ANSI_cyan"..j"ANSI_Bf"GB:\n");//37
	printf("38            "ANSI_Bf":Bu"ANSI_cyan".,:i:i:i:i::::,..::iii:i:i:i:r"ANSI_Bf"Mr"ANSI_cyan",,::,..,:i"ANSI_cyan_d"7j2"ANSI_Bf"kq8OMMBMBMBMMOM8OGOZOMMOONl"ANSI_cyan"r,..r"ANSI_Bf"MBZ.\n");//38
	printf("39           "ANSI_Bf"FB"ANSI_cyan"i.::::i:i:i::,::,:"ANSI_Bf"Gr"ANSI_cyan"::i:i:i:i:i,"ANSI_Bf"uBMr"ANSI_cyan",..,:::,:.......,,::::"ANSI_cyan_d"ii;iririi"ANSI_cyan"::,....,r"ANSI_Bf"OBSi\n");//39
	printf("40          "ANSI_Bf"ZB"ANSI_cyan":.......::::i"ANSI_Bf"Gj"ANSI_cyan"..,"ANSI_Bf"Gk"ANSI_cyan",:i:i:i:i:i:i.:"ANSI_Bf"2GBELi"ANSI_cyan",....,,:::::::::::,:,,,,....,.:"ANSI_cyan_d"75M"ANSI_Bf"BGSG.\n");//40
	printf("41         "ANSI_Bf"UQ"ANSI_cyan":.i"ANSI_cyan_d"52uuY7"ANSI_cyan":,,::r"ANSI_Bf"B8"ANSI_cyan"."ANSI_Bf"GO"ANSI_cyan".:i:i:::::i:i:i:.,"ANSI_cyan_d"7FM"ANSI_Bf"GBOquL"ANSI_cyan";i,,.,...........,,:"ANSI_cyan_d"ivu"ANSI_Bf"EMGO"ANSI_cyan_d"k7"ANSI_cyan":,."ANSI_Bf"LG.\n");//41
	printf("42        "ANSI_Bf".B7"ANSI_cyan"."ANSI_Bf"LBG8MMGBGB"ANSI_cyan"i::,."ANSI_Bf"FGB"ANSI_cyan".,i:i::....:i:i:i,"ANSI_Bf"r8"ANSI_cyan_d"::irj"ANSI_Bf"FGOBBBMM8GNOPqXNqZZOOBBBOEF"ANSI_cyan_d"v"ANSI_cyan":..::::."ANSI_Bf"xG\n");//42
	printf("43        "ANSI_Bf"BQ"ANSI_cyan"."ANSI_Bf"7B"ANSI_dcyan"E1SFk55Z"ANSI_Bf"G"ANSI_cyan"::::.."ANSI_Bf"BL"ANSI_cyan".:::..:"ANSI_Bf"j8GJ"ANSI_cyan".:i:i::,"ANSI_Bf"GY"ANSI_cyan_d":iiii:::i;"ANSI_cyan_d"77JJU251F11uuY"ANSI_cyan"vr;:ii:,::i:i:::."ANSI_Bf"BG\n");//43
	printf("44        "ANSI_Bf"Q7"ANSI_cyan"."ANSI_Bf"EG"ANSI_dcyan"k55SFS5"ANSI_Bf"GY"ANSI_cyan".:i:."ANSI_Bf"jG"ANSI_cyan",,:.."ANSI_Bf"rGGB"ANSI_dcyan"OB"ANSI_Bf"G"ANSI_cyan".::i:i:."ANSI_Bf"ZB"ANSI_cyan_d":rrrrrrri;i;iiii:i:iiiiii;:rrr"ANSI_cyan":::i:i::,..:"ANSI_Bf"Gi\n");//44
	printf("45       "ANSI_Bf";B"ANSI_cyan":.,"ANSI_Bf"1GB"ANSI_dcyan"GFFF"ANSI_Bf"GE"ANSI_cyan".::::."ANSI_Bf"GB"ANSI_cyan".:,i"ANSI_Bf"BB"ANSI_dcyan"BkF2E"ANSI_Bf"B"ANSI_cyan",:i:ii:."ANSI_Bf"uG"ANSI_cyan_d":irr7rrrrrrr7;r;rrrrrrrrr;rr7"ANSI_cyan"i::i:i::."ANSI_cyan_d"i"ANSI_Bf"G"ANSI_cyan_d"U"ANSI_cyan"."ANSI_Bf"SB\n");//45
	printf("46       "ANSI_Bf"YG"ANSI_cyan",::.,"ANSI_Bf"uMG"ANSI_dcyan"B"ANSI_Bf"G8"ANSI_cyan".,::i:."ANSI_Bf"B8"ANSI_cyan".::"ANSI_Bf"G"ANSI_dcyan"Gk1kFFZ"ANSI_Bf"G"ANSI_cyan".::i:i:,"ANSI_Bf"rG"ANSI_cyan_d"iirrr7r7r7r7rrr7rrrrrrrr;ii7r"ANSI_cyan"i:i:i::."ANSI_Bf"uB"ANSI_dcyan"G"ANSI_Bf"Br"ANSI_cyan"."ANSI_Bf"G:\n");//46
	printf("47       "ANSI_Bf"uB"ANSI_cyan",,:::.."ANSI_Bf"i1Y"ANSI_cyan".,i:i::,"ANSI_Bf"GN"ANSI_cyan".,:"ANSI_Bf"G"ANSI_dcyan"B2kSk2M"ANSI_Bf"B"ANSI_cyan".:i:i::."ANSI_Bf"7B"ANSI_cyan_d"rirrrr7rrrrr7r7rrr7rrri:i"ANSI_Bf"Lq"ANSI_cyan_d"7r"ANSI_cyan":iii::."ANSI_Bf"2B"ANSI_dcyan"qUB"ANSI_Bf"N"ANSI_cyan"."ANSI_Bf"OM\n");//47
	printf("48       "ANSI_Bf"rQ"ANSI_cyan":,:i:::,.,:::i:i,,"ANSI_Bf"BG"ANSI_cyan".:.:"ANSI_Bf"B"ANSI_dcyan"B1XFSB"ANSI_Bf"M"ANSI_cyan".::i:i:."ANSI_Bf"LG"ANSI_cyan_d"iir7r7rrr7rrrrrrrr;i:ii"ANSI_Bf"1MM"ANSI_cyan_d"Jrr"ANSI_cyan"::i:i."ANSI_cyan_d"v"ANSI_Bf"B"ANSI_dcyan"q1FE"ANSI_Bf"M"ANSI_cyan".v"ANSI_Bf"G\n");//48
	printf("49       "ANSI_Bf".BU"ANSI_cyan",::i:i:i:i:i:i::."ANSI_Bf"GO"ANSI_cyan":::.:"ANSI_Bf"B"ANSI_dcyan"G5k1G"ANSI_Bf"5"ANSI_cyan".:i:i::."ANSI_Bf"NG"ANSI_cyan_d":irrrrrrrrr;rii::ir"ANSI_Bf"uOMGB"ANSI_cyan_d";:ir7"ANSI_cyan":::i:."ANSI_Bf"G"ANSI_dcyan"G1k5G"ANSI_Bf"B"ANSI_cyan".,"ANSI_Bf"G\n");//49
	printf("50        "ANSI_Bf"QB"ANSI_cyan_d"::"ANSI_cyan"i:::::i:i:i:i:."ANSI_Bf"GG"ANSI_cyan":i::.."ANSI_Bf"E"ANSI_dcyan"GXX"ANSI_Bf"Br"ANSI_cyan".::i:i:."ANSI_Bf"BX"ANSI_cyan_d".::i:iii:::::iiJ"ANSI_Bf"8GGO7 "ANSI_Bf"LG"ANSI_cyan_d":i;77"ANSI_cyan"i:ii:,i"ANSI_Bf"BG"ANSI_dcyan"OG"ANSI_Bf"BG"ANSI_cyan".."ANSI_Bf"G:\n");//50
	printf("51        "ANSI_Bf"JG"ANSI_cyan_d"ii77r"ANSI_cyan";:i::::::::."ANSI_Bf"NB"ANSI_cyan_d":i"ANSI_cyan":::,."ANSI_Bf"LGBO"ANSI_cyan".::i:i:.i"ANSI_Bf"GOF5"ANSI_cyan_d"5uuuU"ANSI_Bf"UkPG8OZGGJ.     "ANSI_Bf"BB"ANSI_cyan_d",:r7r"ANSI_cyan"::i::,."ANSI_cyan_d"r"ANSI_Bf"1X8r"ANSI_cyan".."ANSI_Bf"Gi\n");//51
	printf("52         "ANSI_Bf"BM"ANSI_cyan_d",rr7r7rrrrrrr7riv"ANSI_Bf"Gr"ANSI_cyan_d"i;"ANSI_cyan"::::.:L"ANSI_cyan":::i:i::."ANSI_Bf"GB"ANSI_cyan_d"LP"ANSI_Bf"PP8ZZPN"ANSI_cyan_d"5"ANSI_cyan"uv:i"ANSI_Bf"GB.        "ANSI_Bf"BO"ANSI_cyan_d":rr7"ANSI_cyan"i::i:::,...,,."ANSI_Bf"B;\n");//52
	printf("53         "ANSI_Bf";B"ANSI_cyan_d"u:ri:iir7riirr;:,"ANSI_Bf"BO"ANSI_cyan_d",7;"ANSI_cyan":::::.::i:i::."ANSI_cyan_d"u"ANSI_Bf"B"ANSI_cyan_d":.::"ANSI_cyan",..,i..7Lk"ANSI_Bf"GY          "ANSI_Bf",B"ANSI_cyan_d"q:;r7"ANSI_cyan"::::::::,,.."ANSI_Bf"uGU\n");//53
	printf("54          "ANSI_Bf"UB"ANSI_cyan_d"X"ANSI_cyan"::"ANSI_cyan_d"vESi"ANSI_cyan":"ANSI_cyan_d"rXS"ANSI_cyan"::"ANSI_cyan_d"j"ANSI_Bf"OPFBL"ANSI_cyan_d":7r"ANSI_cyan"i,:::::::,,."ANSI_cyan_d"r"ANSI_Bf"BGZZZ"ANSI_cyan_d"iqYUYr"ANSI_cyan"PBv:"ANSI_Bf"Oi            "ANSI_Bf",BM"ANSI_cyan_d":ir7"ANSI_cyan"::,:r,.i"ANSI_Bf"OZPO"ANSI_wh"█"ANSI_Bf"P1\n");//54
	printf("55           "ANSI_Bf"iGGB"ANSI_gray_1"M"ANSI_wh"█"ANSI_gray_1"u"ANSI_Bf"OLG"ANSI_gray_1":Y"ANSI_Bf"EkG"ANSI_wh"█"ANSI_gray_1"."ANSI_Bf"B"ANSI_gray_1"L"ANSI_Bf"BF"ANSI_cyan_d"::rur"ANSI_cyan",.i7:."ANSI_cyan_d"uOP"ANSI_Bf"B: "ANSI_gray_2"i"ANSI_Bf"ZM"ANSI_wh"█"ANSI_gray_2":"ANSI_Bf"BG"ANSI_gray_2"i"ANSI_wh"█"ANSI_Bf"GX"ANSI_gray_1"r7"ANSI_gray_2"05              "ANSI_Bf"BG"ANSI_cyan_d"Ui"ANSI_cyan":i:"ANSI_cyan_d"r"ANSI_Bf"OSX"ANSI_cyan_d":"ANSI_Bf"G"ANSI_wh"██"ANSI_Bf"Gu"ANSI_gray_2"i7S\n");//55
	printf("56             "ANSI_Bf".kE:.GG"ANSI_gray_1"G"ANSI_wh"██"ANSI_Bf"GGqr,G "ANSI_gray_2":"ANSI_Bf"BGEG"ANSI_gray_1"Lk"ANSI_cyan_d"SJquSZ"ANSI_Bf"X"ANSI_wh"█"ANSI_Bf"q"ANSI_gray_1"u     "ANSI_gray_2"r"ANSI_Bf"5,"ANSI_wh"█"ANSI_Bf",r"ANSI_gray_1"u                    "ANSI_Bf"vGBGOOBr"ANSI_wh"█"ANSI_gray_1"Y"ANSI_Bf"B"ANSI_gray_1"Z"ANSI_gray_2"r;"ANSI_Bf"M"ANSI_gray_1"r\n");//56
	printf("57                "ANSI_Bf":Jr  :Yk  .:,   "ANSI_gray_1":M"ANSI_Bf"B"ANSI_wh"██"ANSI_Bf"GG"ANSI_gray_2"."ANSI_wh"█"ANSI_Bf"uB"ANSI_gray_1"k."ANSI_gray_2":O        "ANSI_gray_1"r                          "ANSI_gray_1":iii"ANSI_Bf"r7i"ANSI_gray_1"5\n");//57
	printf("58                                  "ANSI_gray_2":"ANSI_Bf"uX  "ANSI_gray_1"urk\n");//58
	printf(ANSI_Poke_reset"\n");
	//----------------------------------------------
	//----------------------------------------------
	#undef ANSI_poke_ESC
	//256-color mode:
	#undef ANSI_Poke_escape
	//----------------------------------------------
	#undef ANSI_Bf
	#undef ANSI_wh
	//Der Samen
	#undef ANSI_green
	#undef ANSI_green_d
	//Der Körper
	#undef ANSI_cyan
	#undef ANSI_cyan_d
	//Die Augen
	#undef ANSI_red
	#undef ANSI_red_d
	//Die Flecken:
	#undef ANSI_dcyan
	#undef ANSI_dcyan_d
	//----------------------------------------------
	#undef ANSI_gray_1
	#undef ANSI_gray_2
	//----------------------------------------------
	#undef ANSI_Poke_reset
}







void print_ANSI_Pokemon_Bulbasaur_BETA(){
	#define ANSI_poke_ESC "\033"
	//256-color mode:
	#define ANSI_Poke_escape ANSI_poke_ESC"[38;5;"
	//----------------------------------------------
	#define ANSI_Bf ANSI_Poke_escape"0m"
	#define ANSI_wh ANSI_Poke_escape"15m"
	//Der Samen
	#define ANSI_green ANSI_Poke_escape"34m"
	#define ANSI_green_d ANSI_Poke_escape"22m"
	//Der Körper
	#define ANSI_cyan ANSI_Poke_escape"109m"
	#define ANSI_cyan_d ANSI_Poke_escape"67m"
	//Die Augen
	#define ANSI_red ANSI_Poke_escape"9m"
	#define ANSI_red_d ANSI_Poke_escape"1m"
	//Die Flecken:
	#define ANSI_dcyan ANSI_Poke_escape"23m"
	#define ANSI_dcyan_d ANSI_Poke_escape"24m"
	//----------------------------------------------
	#define ANSI_gray_1 ANSI_Poke_escape"240m"
	#define ANSI_gray_2 ANSI_Poke_escape"250m"
	//----------------------------------------------
	#define ANSI_Poke_reset "\x1b[0m"
	//----------------------------------------------
	//----------------------------------------------
	printf("\n");//58 Lines of Picture
	printf(" 1                          "ANSI_Bf"██\n");//1
	printf(" 2                        "ANSI_Bf"██"ANSI_green_d"█"ANSI_Bf"█""\n");//2
	printf(" 3                        "ANSI_Bf"█"ANSI_green_d"███"ANSI_Bf"██\n");//3
	printf(" 4                      "ANSI_Bf"██"ANSI_green_d"█"ANSI_green"████"ANSI_green_d"█"ANSI_Bf"█"ANSI_gray_1"█\n");//4
	printf(" 5            "ANSI_Bf"███████"ANSI_gray_1"███"ANSI_Bf"██"ANSI_green"█████████"ANSI_Bf"███"ANSI_gray_1"██████"ANSI_gray_2"█████\n"ANSI_Poke_reset);//5
	printf(" 6             "ANSI_Bf"██"ANSI_green"██"ANSI_green_d"█████"ANSI_Bf"█"ANSI_green"█████████"ANSI_green_d"████████████████"ANSI_Bf"█████\n");//6
	printf(" 7              "ANSI_Bf"██"ANSI_green"████████"ANSI_Bf"██"ANSI_green"██████████████████████████"ANSI_green_d"████"ANSI_Bf"█████\n");//7
	printf(" 8             "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"█████████"ANSI_Bf"██"ANSI_green"████████████████████████████"ANSI_green_d"██████"ANSI_Bf"███\n");//8
	printf(" 9             "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"██████████"ANSI_Bf"██"ANSI_green"██████████████████████████████"ANSI_Bf"██"ANSI_green"██"ANSI_Bf"████\n");//9
	printf("10             "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"███████████"ANSI_Bf"██"ANSI_green"██████████████████████████████"ANSI_Bf"██"ANSI_green_d"█"ANSI_green"██"ANSI_Bf"███\n");//10
	printf("11             "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"████████████"ANSI_Bf"██"ANSI_green"██████████████████████████████"ANSI_green_d"█"ANSI_Bf"██"ANSI_green"███"ANSI_Bf"██                 █████\n");//11
	printf("12            "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"██████████████"ANSI_Bf"██"ANSI_green"██████████████"ANSI_Bf"████"ANSI_green"████████████"ANSI_Bf"██"ANSI_green"████"ANSI_Bf"██           █████"ANSI_cyan_d"████"ANSI_Bf"██\n");//12
	printf("13           "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"██████████████"ANSI_Bf"██"ANSI_green"█████████████"ANSI_Bf"██"ANSI_cyan_d"████"ANSI_Bf"███"ANSI_green"█████████"ANSI_Bf"█"ANSI_green_d"███"ANSI_Bf"███"ANSI_gray_1"█████████"ANSI_Bf"███"ANSI_cyan_d"██"ANSI_cyan"███████"ANSI_Bf"██\n");//13
	printf("14           "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"█"ANSI_green"████████████████"ANSI_Bf"██"ANSI_green"███████████"ANSI_Bf"██"ANSI_cyan"██████"ANSI_Bf"███████████████████████████████"ANSI_cyan"█████████"ANSI_Bf"██\n");//14
	printf("15          "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"██"ANSI_green"████████████████"ANSI_Bf"██"ANSI_green"██████████"ANSI_Bf"██"ANSI_cyan"█████████"ANSI_cyan_d"█"ANSI_Bf"███"ANSI_cyan_d"█"ANSI_cyan"█████████████████████████████████"ANSI_Bf"██\n");//15
	printf("16         "ANSI_Bf"█"ANSI_green"█"ANSI_Bf"██"ANSI_green"██████████████████"ANSI_Bf"██"ANSI_green"█████████"ANSI_Bf"██"ANSI_cyan"████████████"ANSI_cyan_d"██"ANSI_cyan"████████████████████"ANSI_cyan_d"█"ANSI_Bf"█████"ANSI_cyan"████████"ANSI_Bf"██\n");//16
	printf("17        "ANSI_Bf"█"ANSI_green"██"ANSI_Bf"█"ANSI_green"███████████████████"ANSI_Bf"█"ANSI_green"████████"ANSI_Bf"██"ANSI_cyan_d"█"ANSI_cyan"██████████████████████████████"ANSI_cyan_d"██"ANSI_Bf"███"ANSI_dcyan"███"ANSI_Bf"██"ANSI_cyan"███████"ANSI_cyan_d"█"ANSI_Bf"██\n");//17
	printf("18       "ANSI_Bf"█"ANSI_green"██"ANSI_Bf"██"ANSI_green"███████████████████"ANSI_Bf"█"ANSI_green"████████"ANSI_Bf"██"ANSI_cyan"█████████████████████████████"ANSI_cyan_d"█"ANSI_Bf"███"ANSI_dcyan"█████"ANSI_Bf"██"ANSI_cyan"████████"ANSI_cyan_d"█"ANSI_Bf"██\n");//18
	printf("19      "ANSI_Bf"█"ANSI_green"██"ANSI_Bf"██"ANSI_green"█████████████████████"ANSI_Bf"██"ANSI_green"██████"ANSI_Bf"██"ANSI_cyan_d"█"ANSI_cyan"████████████████████████████"ANSI_Bf"██"ANSI_dcyan"███████"ANSI_Bf"██"ANSI_cyan"██████████"ANSI_Bf"███\n");//19
	printf("20     "ANSI_Bf"█"ANSI_green"██"ANSI_Bf"██"ANSI_green"███████████████████████"ANSI_Bf"██"ANSI_green"█████"ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"███████████████████████████"ANSI_Bf"██"ANSI_dcyan"██████"ANSI_Bf"███"ANSI_cyan"███████████"ANSI_Bf"██\n");//20
	printf("21    "ANSI_Bf"██"ANSI_green"██"ANSI_Bf"██"ANSI_green"████████████████████████"ANSI_Bf"██"ANSI_green"████"ANSI_Bf"██"ANSI_cyan_d"███"ANSI_cyan"████████████████████████████"ANSI_Bf"███"ANSI_dcyan_d"██"ANSI_Bf"███"ANSI_cyan"█████████████"ANSI_Bf"██\n");//21
	printf("22   "ANSI_Bf"██"ANSI_green"██"ANSI_Bf"██"ANSI_green"██████████████████████████"ANSI_Bf"██"ANSI_green"██"ANSI_Bf"██"ANSI_cyan_d"████"ANSI_cyan"████████████████"ANSI_cyan"█"ANSI_cyan"█"ANSI_cyan_d"█"ANSI_cyan"████"ANSI_cyan"███"ANSI_cyan"█████"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_cyan_d"█"ANSI_cyan"████████"ANSI_cyan_d"█"ANSI_Bf"██"ANSI_cyan"█"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_cyan_d"█"ANSI_cyan"█"ANSI_Bf"██\n");//22
	printf("23   "ANSI_Bf"█"ANSI_green"███"ANSI_Bf"██"ANSI_green"███████████████████████████"ANSI_Bf"█████"ANSI_cyan_d"████"ANSI_cyan"███████████"ANSI_cyan_d"██"ANSI_cyan"████"ANSI_Bf"███"ANSI_cyan"██"ANSI_Bf"█"ANSI_dcyan"████"ANSI_cyan"██████████"ANSI_cyan_d"█"ANSI_cyan"█"ANSI_cyan_d"█"ANSI_cyan"███"ANSI_Bf"█"ANSI_cyan_d"█"ANSI_cyan"█"ANSI_Bf"███"ANSI_cyan_d"█"ANSI_cyan"█"ANSI_Bf"██\n");//23
	printf("24  "ANSI_Bf"██"ANSI_green"███"ANSI_Bf"██"ANSI_green"█████████████████████████████"ANSI_Bf"███"ANSI_cyan_d"████"ANSI_cyan"█████████"ANSI_Bf"██"ANSI_gray_1"█"ANSI_Bf"████"ANSI_cyan"███"ANSI_Bf"██"ANSI_cyan"██"ANSI_Bf"█"ANSI_dcyan"███"ANSI_cyan"█████████"ANSI_Bf"█████"ANSI_cyan"█"ANSI_Bf"██"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_red"██"ANSI_gray_1"██"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"██\n");//24
	printf("25  "ANSI_Bf"██"ANSI_green"███"ANSI_Bf"██"ANSI_green"████████████████████████████"ANSI_Bf"███"ANSI_cyan_d"█████"ANSI_cyan"███████"ANSI_cyan_d"█"ANSI_Bf"██"ANSI_wh"█"ANSI_Bf"██"ANSI_red"██"ANSI_Bf"██"ANSI_cyan"███"ANSI_Bf"██"ANSI_cyan"██"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_cyan"█████████"ANSI_Bf"██"ANSI_dcyan"██"ANSI_Bf"██"ANSI_cyan"████"ANSI_Bf"█"ANSI_wh"█"ANSI_red"█"ANSI_red_d"█"ANSI_gray_2"██"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"█\n");//25
	printf("26 "ANSI_Bf"██"ANSI_green"████"ANSI_Bf"██"ANSI_green"██████████████████████████"ANSI_Bf"███"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_cyan_d"█████"ANSI_cyan"██████"ANSI_cyan_d"█"ANSI_Bf"██"ANSI_wh"█"ANSI_Bf"██"ANSI_red"█"ANSI_wh"███"ANSI_Bf"██"ANSI_cyan"████████████████"ANSI_Bf"██"ANSI_dcyan"████"ANSI_Bf"█"ANSI_cyan_d"█"ANSI_cyan"██"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_wh"██"ANSI_red"█"ANSI_Bf"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"██\n");//26
	printf("27 "ANSI_Bf"██"ANSI_green"████"ANSI_Bf"██"ANSI_green"█████████████████████████"ANSI_Bf"██"ANSI_cyan"██"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_cyan_d"█████"ANSI_cyan"██████"ANSI_Bf"██"ANSI_wh"██"ANSI_Bf"█"ANSI_red"██"ANSI_wh"███"ANSI_red"██"ANSI_Bf"██"ANSI_cyan"██████████████"ANSI_Bf"██"ANSI_dcyan"████"ANSI_Bf"██"ANSI_cyan"██"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_wh"██"ANSI_red"█"ANSI_Bf"█"ANSI_gray_2"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"█\n");//27
	printf("28 "ANSI_Bf"██"ANSI_green"█████"ANSI_Bf"██"ANSI_green"██████████████████████"ANSI_Bf"██"ANSI_cyan"████"ANSI_Bf"██"ANSI_cyan_d"████"ANSI_cyan"██████"ANSI_Bf"██"ANSI_wh"██"ANSI_Bf"██"ANSI_red"██"ANSI_wh"███"ANSI_red"██"ANSI_red_d"█"ANSI_Bf"█"ANSI_cyan"███████████████"ANSI_Bf"███████"ANSI_cyan"██"ANSI_cyan_d"█"ANSI_gray_1"█"ANSI_wh"█"ANSI_red"██"ANSI_red_d"█"ANSI_gray_1"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"█\n");//28
	printf("29 "ANSI_Bf"██"ANSI_green"█████"ANSI_Bf"██"ANSI_green"████████████████████"ANSI_Bf"███"ANSI_cyan"██████"ANSI_cyan_d"████"ANSI_cyan"███████"ANSI_Bf"██"ANSI_wh"██"ANSI_Bf"██"ANSI_red"██"ANSI_wh"███"ANSI_red"███"ANSI_Bf"██"ANSI_cyan"██████████████████"ANSI_cyan_d"██"ANSI_cyan"███"ANSI_cyan_d"█"ANSI_red_d"█"ANSI_red"███"ANSI_red_d"█"ANSI_gray_1"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"█"ANSI_gray_1"█\n");//29
	printf("30 "ANSI_Bf"██"ANSI_green"██████"ANSI_Bf"██"ANSI_green"█████████████████"ANSI_Bf"██"ANSI_dcyan"███"ANSI_Bf"████"ANSI_cyan"████████████"ANSI_Bf"██"ANSI_wh"███"ANSI_Bf"██"ANSI_red"██"ANSI_wh"███"ANSI_red"███"ANSI_red_d"█"ANSI_Bf"█"ANSI_cyan_d"█"ANSI_cyan"██████████████████████"ANSI_cyan_d"█"ANSI_gray_1"█"ANSI_red"███"ANSI_red_d"█"ANSI_gray_1"█"ANSI_wh"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"██\n");//30
	printf("31  "ANSI_Bf"██"ANSI_green"██████"ANSI_Bf"██"ANSI_green"█████████████"ANSI_Bf"███"ANSI_dcyan"███████"ANSI_Bf"██"ANSI_cyan"████████████"ANSI_Bf"██"ANSI_wh"███"ANSI_Bf"██"ANSI_red"█████████"ANSI_Bf"██"ANSI_cyan"███████████████████████"ANSI_Bf"█"ANSI_red"███"ANSI_red_d"█"ANSI_gray_1"██"ANSI_Bf"█"ANSI_cyan"██"ANSI_Bf"█\n");//31
	printf("32   "ANSI_Bf"██"ANSI_green"██████"ANSI_Bf"██"ANSI_green"██████████"ANSI_Bf"███"ANSI_dcyan"████████"ANSI_Bf"██"ANSI_cyan"█████████████"ANSI_Bf"██"ANSI_wh"████"ANSI_Bf"█"ANSI_red_d"█"ANSI_red"████████"ANSI_Bf"██"ANSI_cyan"███████████████████████"ANSI_cyan_d"█"ANSI_Bf"███"ANSI_cyan_d"█"ANSI_cyan"████"ANSI_Bf"██\n");//32
	printf("33   "ANSI_Bf"██"ANSI_green"███████"ANSI_Bf"███"ANSI_green"██████"ANSI_Bf"███"ANSI_dcyan"██████████"ANSI_Bf"██"ANSI_cyan_d"█"ANSI_cyan"██████████████"ANSI_Bf"███"ANSI_gray_1"█"ANSI_wh"█"ANSI_Bf"██"ANSI_red"████████"ANSI_Bf"██"ANSI_cyan"██████████████████████████████"ANSI_cyan_d"█"ANSI_cyan"█"ANSI_Bf"██\n");//33
	printf("34    "ANSI_Bf"███"ANSI_green"██████"ANSI_Bf"█████"ANSI_green"█"ANSI_Bf"██"ANSI_cyan_d"██"ANSI_Bf"█"ANSI_dcyan"█████████"ANSI_Bf"█"ANSI_cyan_d"█"ANSI_cyan"█████████████████"ANSI_Bf"█████████████"ANSI_cyan"██████████████████████████████"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"██\n");//34
	printf("35     "ANSI_Bf"███"ANSI_green"████████"ANSI_Bf"███"ANSI_cyan"████"ANSI_Bf"████"ANSI_dcyan"█████"ANSI_Bf"██"ANSI_cyan"███████████████"ANSI_Bf"██"ANSI_cyan"█████████████████████████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"█"ANSI_cyan"██████"ANSI_Bf"████"ANSI_cyan"█"ANSI_Bf"██\n");//35
	printf("36       "ANSI_Bf"████"ANSI_green"████"ANSI_Bf"███"ANSI_cyan"████████"ANSI_Bf"██████"ANSI_cyan"██████████████████"ANSI_Bf"█████"ANSI_cyan"██████████████████████"ANSI_Bf"██"ANSI_cyan"█████"ANSI_Bf"█"ANSI_cyan"█████"ANSI_Bf"█████"ANSI_cyan"██"ANSI_Bf"██\n");//36
	printf("37          "ANSI_Bf"██"ANSI_green"██"ANSI_Bf"██"ANSI_cyan"███████████████████████████████████"ANSI_cyan_d"█"ANSI_Bf"█████████"ANSI_cyan_d"███"ANSI_cyan"████████████████████"ANSI_cyan_d"█"ANSI_Bf"██████"ANSI_cyan"███"ANSI_Bf"███\n");//37
	printf("38            "ANSI_Bf"███"ANSI_cyan"██████████████████████████████"ANSI_Bf"█"ANSI_cyan"██████████"ANSI_cyan_d"███"ANSI_Bf"███████████████████████████"ANSI_cyan"█████"ANSI_Bf"████\n");//38
	printf("39           "ANSI_Bf"██"ANSI_cyan"██████████████████"ANSI_Bf"██"ANSI_cyan"████████████"ANSI_Bf"████"ANSI_cyan"██████████████████████"ANSI_cyan_d"█████████"ANSI_cyan"█████████"ANSI_Bf"████\n");//39
	printf("40          "ANSI_Bf"██"ANSI_cyan"█████████████"ANSI_Bf"██"ANSI_cyan"███"ANSI_Bf"██"ANSI_cyan"███████████████"ANSI_Bf"██████"ANSI_cyan"███████████████████████████████"ANSI_cyan_d"███"ANSI_Bf"█████\n");//40
	printf("41         "ANSI_Bf"██"ANSI_cyan"███"ANSI_cyan_d"██████"ANSI_cyan"██████"ANSI_Bf"██"ANSI_cyan"█"ANSI_Bf"██"ANSI_cyan"██████████████████"ANSI_cyan_d"███"ANSI_Bf"██████"ANSI_cyan"████████████████████"ANSI_cyan_d"███"ANSI_Bf"████"ANSI_cyan_d"██"ANSI_cyan"███"ANSI_Bf"███\n");//41
	printf("42        "ANSI_Bf"███"ANSI_cyan"█"ANSI_Bf"██████████"ANSI_cyan"█████"ANSI_Bf"███"ANSI_cyan"██████████████████"ANSI_Bf"██"ANSI_cyan_d"█████"ANSI_Bf"███████████████████████████"ANSI_cyan_d"█"ANSI_cyan"████████"ANSI_Bf"██\n");//42
	printf("43        "ANSI_Bf"██"ANSI_cyan"█"ANSI_Bf"██"ANSI_dcyan"████████"ANSI_Bf"█"ANSI_cyan"██████"ANSI_Bf"██"ANSI_cyan"███████"ANSI_Bf"████"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"██████████"ANSI_cyan_d"██████████████"ANSI_cyan"███████████████"ANSI_Bf"██\n");//43
	printf("44        "ANSI_Bf"██"ANSI_cyan"█"ANSI_Bf"██"ANSI_dcyan"███████"ANSI_Bf"██"ANSI_cyan"█████"ANSI_Bf"██"ANSI_cyan"█████"ANSI_Bf"████"ANSI_dcyan"██"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"██████████████████████████████"ANSI_cyan"████████████"ANSI_Bf"██\n");//44
	printf("45       "ANSI_Bf"██"ANSI_cyan"███"ANSI_Bf"███"ANSI_dcyan"████"ANSI_Bf"██"ANSI_cyan"██████"ANSI_Bf"██"ANSI_cyan"████"ANSI_Bf"██"ANSI_dcyan"█████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"█████████████████████████████"ANSI_cyan"█████████"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_cyan_d"█"ANSI_cyan"█"ANSI_Bf"██\n");//45
	printf("46       "ANSI_Bf"██"ANSI_cyan"█████"ANSI_Bf"███"ANSI_dcyan"█"ANSI_Bf"██"ANSI_cyan"███████"ANSI_Bf"██"ANSI_cyan"███"ANSI_Bf"█"ANSI_dcyan"███████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"█████████████████████████████"ANSI_cyan"████████"ANSI_Bf"██"ANSI_dcyan"█"ANSI_Bf"██"ANSI_cyan"█"ANSI_Bf"██\n");//46
	printf("47       "ANSI_Bf"██"ANSI_cyan"███████"ANSI_Bf"███"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan"███"ANSI_Bf"█"ANSI_dcyan"███████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"█████████████████████████"ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"███████"ANSI_Bf"██"ANSI_dcyan"███"ANSI_Bf"█"ANSI_cyan"█"ANSI_Bf"██\n");//47
	printf("48       "ANSI_Bf"██"ANSI_cyan"██████████████████"ANSI_Bf"██"ANSI_cyan"████"ANSI_Bf"█"ANSI_dcyan"██████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"███████████████████████"ANSI_Bf"███"ANSI_cyan_d"███"ANSI_cyan"██████"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_dcyan"████"ANSI_Bf"█"ANSI_cyan"██"ANSI_Bf"█\n");//48
	printf("49       "ANSI_Bf"███"ANSI_cyan"█████████████████"ANSI_Bf"██"ANSI_cyan"█████"ANSI_Bf"█"ANSI_dcyan"█████"ANSI_Bf"█"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"███████████████████"ANSI_Bf"█████"ANSI_cyan_d"█████"ANSI_cyan"██████"ANSI_Bf"█"ANSI_dcyan"█████"ANSI_Bf"█"ANSI_cyan"██"ANSI_Bf"█\n");//49
	printf("50        "ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"███████████████"ANSI_Bf"██"ANSI_cyan"██████"ANSI_Bf"█"ANSI_dcyan"███"ANSI_Bf"██"ANSI_cyan"████████"ANSI_Bf"██"ANSI_cyan_d"████████████████"ANSI_Bf"█████ "ANSI_Bf"██"ANSI_cyan_d"█████"ANSI_cyan"███████"ANSI_Bf"██"ANSI_dcyan"██"ANSI_Bf"██"ANSI_cyan"██"ANSI_Bf"██\n");//50
	printf("51        "ANSI_Bf"██"ANSI_cyan_d"█████"ANSI_cyan"████████████"ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"█████"ANSI_Bf"████"ANSI_cyan"█████████"ANSI_Bf"████"ANSI_cyan_d"█████"ANSI_Bf"███████████     "ANSI_Bf"██"ANSI_cyan_d"█████"ANSI_cyan"███████"ANSI_cyan_d"█"ANSI_Bf"████"ANSI_cyan"██"ANSI_Bf"██\n");//51
	printf("52         "ANSI_Bf"██"ANSI_cyan_d"█████████████████"ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"███████"ANSI_cyan"█████████"ANSI_Bf"██"ANSI_cyan_d"██"ANSI_Bf"███████"ANSI_cyan_d"█"ANSI_cyan"████"ANSI_Bf"███        "ANSI_Bf"██"ANSI_cyan_d"████"ANSI_cyan"██████████████"ANSI_Bf"██\n");//52
	printf("53         "ANSI_Bf"██"ANSI_cyan_d"█████████████████"ANSI_Bf"██"ANSI_cyan_d"███"ANSI_cyan"██████████████"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_cyan_d"████"ANSI_cyan"██████████"ANSI_Bf"██          "ANSI_Bf"██"ANSI_cyan_d"█████"ANSI_cyan"████████████"ANSI_Bf"███\n");//53
	printf("54          "ANSI_Bf"██"ANSI_cyan_d"█"ANSI_cyan"██"ANSI_cyan_d"████"ANSI_cyan"█"ANSI_cyan_d"███"ANSI_cyan"██"ANSI_cyan_d"█"ANSI_Bf"█████"ANSI_cyan_d"███"ANSI_cyan"████████████"ANSI_cyan_d"█"ANSI_Bf"█████"ANSI_cyan_d"██████"ANSI_cyan"██"ANSI_Bf"██            "ANSI_Bf"███"ANSI_cyan_d"████"ANSI_cyan"████████"ANSI_Bf"████"ANSI_wh"█"ANSI_Bf"██\n");//54
	printf("55           "ANSI_Bf"████"ANSI_gray_1"█"ANSI_wh"█"ANSI_gray_1"█"ANSI_Bf"███"ANSI_gray_1"██"ANSI_Bf"███"ANSI_wh"█"ANSI_gray_1"█"ANSI_Bf"█"ANSI_gray_1"█"ANSI_Bf"██"ANSI_cyan_d"█████"ANSI_cyan"██████"ANSI_cyan_d"███"ANSI_Bf"██ "ANSI_gray_2"█"ANSI_Bf"██"ANSI_wh"█"ANSI_gray_2"█"ANSI_Bf"██"ANSI_gray_2"█"ANSI_wh"█"ANSI_Bf"██"ANSI_gray_1"██"ANSI_gray_2"██              "ANSI_Bf"██"ANSI_cyan_d"██"ANSI_cyan"███"ANSI_cyan_d"█"ANSI_Bf"███"ANSI_cyan_d"█"ANSI_Bf"█"ANSI_wh"██"ANSI_Bf"██"ANSI_gray_2"███\n");//55
	printf("56             "ANSI_Bf"███████"ANSI_gray_1"█"ANSI_wh"██"ANSI_Bf"██████ "ANSI_gray_2"█"ANSI_Bf"████"ANSI_gray_1"██"ANSI_cyan_d"██████"ANSI_Bf"█"ANSI_wh"█"ANSI_Bf"█"ANSI_gray_1"█     "ANSI_gray_2"█"ANSI_Bf"██"ANSI_wh"█"ANSI_Bf"██"ANSI_gray_1"█                    "ANSI_Bf"████████"ANSI_wh"█"ANSI_gray_1"█"ANSI_Bf"█"ANSI_gray_1"█"ANSI_gray_2"██"ANSI_Bf"█"ANSI_gray_1"█\n");//56
	printf("57                "ANSI_Bf"███  ███  ███   "ANSI_gray_1"██"ANSI_Bf"█"ANSI_wh"██"ANSI_Bf"██"ANSI_gray_2"█"ANSI_wh"█"ANSI_Bf"██"ANSI_gray_1"██"ANSI_gray_2"██        "ANSI_gray_1"█                          "ANSI_gray_1"████"ANSI_Bf"███"ANSI_gray_1"█\n");//57
	printf("58                                  "ANSI_gray_2"█"ANSI_Bf"██  "ANSI_gray_1"███\n");//58
	printf(ANSI_Poke_reset"\n");
	//----------------------------------------------
	//----------------------------------------------
	#undef ANSI_poke_ESC
	//256-color mode:
	#undef ANSI_Poke_escape
	//----------------------------------------------
	#undef ANSI_Bf
	#undef ANSI_wh
	//Der Samen
	#undef ANSI_green
	#undef ANSI_green_d
	//Der Körper
	#undef ANSI_cyan
	#undef ANSI_cyan_d
	//Die Augen
	#undef ANSI_red
	#undef ANSI_red_d
	//Die Flecken:
	#undef ANSI_dcyan
	#undef ANSI_dcyan_d
	//----------------------------------------------
	#undef ANSI_gray_1
	#undef ANSI_gray_2
	//----------------------------------------------
#undef ANSI_Poke_reset
}









#undef DENKR_ESSENTIALS_TERMINAL_ANSI_C
#undef NO_DENKR_ESSENTIALS_TERMINAL_ANSI_C_FUNCTIONS
