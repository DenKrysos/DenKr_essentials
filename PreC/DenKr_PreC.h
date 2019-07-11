#ifndef DENKR_ESSENTIALS_PREC_DENKR_PREC_H
#define DENKR_ESSENTIALS_PREC_DENKR_PREC_H
/*
 * Authored by
 * Dennis Krummacker (20.01.2017 - )
 */
/*
 *       Additional Programming-Language-Name: "PreC"
 *
 * Let me define a name for a collection of all this Preprocessor-Macro-Stuff,
 * that comes already before the actual C-Program and that's able to change
 * the behavior of the Program, even of the Programming-Language; that
 * implements whole new functionalities and Syntaxes/Semantics.
 * I've made a collection of a lot Stuff like that, like Macro-Overloading/Overriding,
 * PreProcessor-Functions / Automations (Macro- / Function Split, Comparison,
 * Boolean Operations at Compile-Time etc.)
 * So i take the Freedom to pack all this and future additions into a new
 * "Programming-Language-Extension" called "PreC"
 */









/*
 * Some absolutely Basic Macros
 *///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//=====================================================================
//
////////////////////////////////
//////// PATTERN MATCHING
////////////////////////////////
#define CONCAT(ARG, ...) CRUDE_CONCAT(ARG, __VA_ARGS__)
#define CRUDE_CONCAT(ARG, ...) ARG ## __VA_ARGS__
#define LATE_CONCAT(ARG,...) EVAL_SMALL(CONCAT(ARG,__VA_ARGS__))
	#define CONCAT_EXPAND_MORE(ARG,...)  CONCAT(ARG,__VA_ARGS__)	//My "CONCAT" is already evaluated one step. So these two here are just for completeness...
	#define CONCAT_EXPAND(ARG,...) CRUDE_CONCAT(ARG, __VA_ARGS__)		//And to provide additional Labels
//---------------------------------------------------------------------
// Best Way is to use the following Macro for Concatenations:
//		CAT(Variable Number of Arguments)
// It does some Magic for you and can handle different Numbers of Arguments.
////////////////
#define _macro_multi_CAT_0(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_multi_CAT_1(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_multi_CAT_2(ARG1, ARG2) LATE_CONCAT(ARG1, ARG2)
#define _macro_multi_CAT_3(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_2(__VA_ARGS__))
#define _macro_multi_CAT_4(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_3(__VA_ARGS__))
#define _macro_multi_CAT_5(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_4(__VA_ARGS__))
#define _macro_multi_CAT_6(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_5(__VA_ARGS__))
#define _macro_multi_CAT_7(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_6(__VA_ARGS__))
#define _macro_multi_CAT_8(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_7(__VA_ARGS__))
#define _macro_multi_CAT_9(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_8(__VA_ARGS__))
#define _macro_multi_CAT_10(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_9(__VA_ARGS__))
#define _macro_multi_CAT_11(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_10(__VA_ARGS__))
#define _macro_multi_CAT_12(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_11(__VA_ARGS__))
#define _macro_multi_CAT_13(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_12(__VA_ARGS__))
#define _macro_multi_CAT_14(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_13(__VA_ARGS__))
#define _macro_multi_CAT_15(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_14(__VA_ARGS__))
#define _macro_multi_CAT_16(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_15(__VA_ARGS__))
#define _macro_multi_CAT_17(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_16(__VA_ARGS__))
#define _macro_multi_CAT_18(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_17(__VA_ARGS__))
#define _macro_multi_CAT_19(ARG1, ...) LATE_CONCAT(ARG1, _macro_multi_CAT_18(__VA_ARGS__))
////
#define CAT(...) CAT_EVALUATED(__VA_ARGS__)
#define CAT_EVALUATED(...) \
		macro_overloader(_macro_multi_CAT_, __VA_ARGS__)(__VA_ARGS__)
////////////////
// Please mind: The Concatenation doesn't like preceding or succeeding Special Characters, like dots "." or "/" etc.
//		Example:	Doesn't work:		file ## .txt
//					Doesn't work:		file. ## txt
//				Works like a charm:		Version ## 1.0
// But we can use a workaround! :D
// Here you have an Example for that:
//					#define _LogPathAppendix_1 log/MonitorBW_
//					#define _LogPathAppendix_DateTemplate XXXX-XX-XX_XX:XX:XX
//	Look here -->	#define _LogPathAppendix_Suffix log
//
//	Look here -->	#define _LogPathAppendix_Template CAT(_LogPathAppendix_1, _LogPathAppendix_DateTemplate._LogPathAppendix_Suffix)
//					#define LogPathAppendix_1 STRING_EXP(_LogPathAppendix_1)
//					#define LogPathAppendix_DateTemplate STRING_EXP(_LogPathAppendix_DateTemplate)
//					#define LogPathAppendix_Suffix STRING_EXP(_LogPathAppendix_Suffix)
//
//					#define LogPathAppendix_Template STRING_EXP(_LogPathAppendix_Template)
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
  //Directly Stringificates the passed Argument, i.e. turns it into a string
#define STRINGIFICATE(ARG) #ARG
#define STRINGIFY(ARG) STRINGIFICATE(ARG)
  //Stringificates after Macro-Expansion, due to one more Macro Passing Stage (Scan)
#define STRING_EXP(ARG) STRINGIFICATE(ARG)
//---------------------------------------------------------------------
#define IIF(c) CRUDE_CONCAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t
//		#define A() 1
//		//This correctly expands to true
//		IIF(1)(true, false)
//		// And this will also correctly expand to true
//		IIF(A())(true, false)
//---------------------------------------------------------------------
#define COMPL(b) CRUDE_CONCAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0
////
#define BITAND(x) CRUDE_CONCAT(BITAND_, x)
#define BITAND_0(y) 0
#define BITAND_1(y) y
//---------------------------------------------------------------------
#define INC(x) CRUDE_CONCAT(INC_, x)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Needed supporting Values can be found at the Bottom
//     e.g. #define INC_0 1
//---------------------------------------------------------------------
#define DEC(x) CRUDE_CONCAT(DEC_, x)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Needed supporting Values can be found at the Bottom
//     e.g. #define DEC_2 1
//---------------------------------------------------------------------
////////////////////////////////
//////// ARRAY
////////////////////////////////
// Supplies you something like an Array-Behavior at PreProcessor-Level
// ><><>< Usage: ><><><
// Define your desired Array like:
//     #define ARRAY_SIZES (12, 45, 67) or maybe #define ARRAY_FILE_NAMES("main.cfg", "addresses.conf", "target.dat", "main.log")
// (Optional) You could also define corresponding Indices:
//     #define FILE_NAME_MAIN_CONFIG 0
//     #define FILE_NAME_ADDR_CONF 1
//  (Alternative) or define them like
//     #define FILE_NAME_MAIN_CONFIG 0
//     #define FILE_NAME_ADDR_CONF INC(FILE_NAME_MAIN_CONFIG)
//     #define FILE_NAME_DATE_GEN_PASS INC(FILE_NAME_ADDR_CONF)
//   Obiously with this concept you have to get sure, that the Indices and the Positions in the Array (which actually is a Arguments-List)
//     match together. With the alternative approach, it's much easier to insert additional entries between.
//   Meanwhile you have to take care, if you add entries later on, especially when you add them "between".
// Than you can use the Array in that way:
//     ARRAY_ENTRY(0, ARRAY_SIZES)
//         or
//     ARRAY_ENTRY(FILE_NAME_ADDR_CONF, ARRAY_FILE_NAMES)
// - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Consider the Limitations of the PreProcessor: It can handle at most 64 Macro Arguments.
// Because of the one more inside the Macro ARRAY_ENTRY/ARGN this lasts 63 Entries for the "Array/List"
///////////////////////////////
// Just two different Labels to do the same
#define ARRAY_ENTRY(N, LIST)	CONCAT_EXPAND(ARG_, N) LIST
#define ARGN(N, LIST)			CONCAT_EXPAND(ARG_, N) LIST
// - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define ARG_0(A0, ...)    A0
#define ARG_1(A0, A1, ...)    A1
#define ARG_2(A0, A1, A2, ...)    A2
#define ARG_3(A0, A1, A2, A3, ...)    A3
#define ARG_4(A0, A1, A2, A3, A4, ...)    A4
#define ARG_5(A0, A1, A2, A3, A4, A5, ...)    A5
#define ARG_6(A0, A1, A2, A3, A4, A5, A6, ...)    A6
#define ARG_7(A0, A1, A2, A3, A4, A5, A6, A7, ...)    A7
#define ARG_8(A0, A1, A2, A3, A4, A5, A6, A7, A8, ...)    A8
#define ARG_9(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, ...)    A9
#define ARG_10(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, ...)    A10
#define ARG_11(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, ...)    A11
#define ARG_12(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, ...)    A12
#define ARG_13(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, ...)    A13
#define ARG_14(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, ...)    A14
#define ARG_15(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, ...)    A15
#define ARG_16(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, ...)    A16
#define ARG_17(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, ...)    A17
#define ARG_18(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, ...)    A18
#define ARG_19(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, ...)    A19
#define ARG_20(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, ...)    A20
#define ARG_21(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, ...)    A21
#define ARG_22(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, ...)    A22
#define ARG_23(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, ...)    A23
#define ARG_24(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, ...)    A24
#define ARG_25(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, ...)    A25
#define ARG_26(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, ...)    A26
#define ARG_27(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, ...)    A27
#define ARG_28(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, ...)    A28
#define ARG_29(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, ...)    A29
#define ARG_30(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, ...)    A30
#define ARG_31(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, ...)    A31
#define ARG_32(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, ...)    A32
#define ARG_33(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, ...)    A33
#define ARG_34(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, ...)    A34
#define ARG_35(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, ...)    A35
#define ARG_36(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, ...)    A36
#define ARG_37(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, ...)    A37
#define ARG_38(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, ...)    A38
#define ARG_39(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, ...)    A39
#define ARG_40(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, ...)    A40
#define ARG_41(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, ...)    A41
#define ARG_42(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, ...)    A42
#define ARG_43(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, ...)    A43
#define ARG_44(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, ...)    A44
#define ARG_45(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, ...)    A45
#define ARG_46(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, ...)    A46
#define ARG_47(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, ...)    A47
#define ARG_48(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, ...)    A48
#define ARG_49(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, ...)    A49
#define ARG_50(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, ...)    A50
#define ARG_51(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, ...)    A51
#define ARG_52(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, ...)    A52
#define ARG_53(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, ...)    A53
#define ARG_54(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, ...)    A54
#define ARG_55(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, ...)    A55
#define ARG_56(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, ...)    A56
#define ARG_57(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, ...)    A57
#define ARG_58(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, A58, ...)    A58
#define ARG_59(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, A58, A59, ...)    A59
#define ARG_60(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, A58, A59, A60, ...)    A60
#define ARG_61(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, A58, A59, A60, A61, ...)    A61
#define ARG_62(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, A58, A59, A60, A61, A62, ...)    A62
#define ARG_63(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, A58, A59, A60, A61, A62, A63, ...)    A63
//---------------------------------------------------------------------
////////////////////////////////
//////// DETECTION
////////////////////////////////
#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)
#define PROBE(x) x, 1,
//		CHECK(PROBE(~)) // Expands to 1
//		CHECK(xxx) // Expands to 0
//---------------------------------------------------------------------
#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE(~)
//		IS_PAREN(()) // Expands to 1
//		IS_PAREN(xxx) // Expands to 0
//---------------------------------------------------------------------
#define NOT(x) CHECK(CRUDE_CONCAT(NOT_, x))
#define NOT_0 PROBE(~)
//---------------------------------------------------------------------
#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))
//---------------------------------------------------------------------
#define EAT(...)
#define EXPAND(...) __VA_ARGS__
#define WHEN(c) IF(c)(EXPAND, EAT)
//---------------------------------------------------------------------
////////////////////////////////
//////// RECURSION
////////////////////////////////
//#define EXPAND(...) __VA_ARGS__
#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
// You want an Example for Deferred Expression?
//  Think about this:
//		#define A() 123
//		A() // Expands to 123
//		DEFER(A)() // Expands to A () because it requires one more scan to fully expand
//		EXPAND(DEFER(A)()) // Expands to 123, because the EXPAND macro forces another scan
//---------------------------------------------------------------------
#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__
////
#define EVAL_SMALL(...)  EVAL_SMALL1(EVAL_SMALL1(EVAL_SMALL1(__VA_ARGS__)))
#define EVAL_SMALL1(...) EVAL_SMALL2(EVAL_SMALL2(EVAL_SMALL2(__VA_ARGS__)))
#define EVAL_SMALL2(...) EVAL_SMALL3(EVAL_SMALL3(EVAL_SMALL3(__VA_ARGS__)))
#define EVAL_SMALL3(...) EVAL_SMALL4(EVAL_SMALL4(EVAL_SMALL4(__VA_ARGS__)))
#define EVAL_SMALL4(...) __VA_ARGS__
//---------------------------------------------------------------------
#define REPEAT(count, macro, ...) \
    WHEN(count) \
    ( \
        OBSTRUCT(REPEAT_INDIRECT) () \
        ( \
            DEC(count), macro, __VA_ARGS__ \
        ) \
        OBSTRUCT(macro) \
        ( \
            DEC(count), __VA_ARGS__ \
        ) \
    )
#define REPEAT_INDIRECT() REPEAT
//		//An example of using this macro
//		#define M(i, _) i
//		STRINGIFY(EVAL(REPEAT(8, M, ~))) // 0 1 2 3 4 5 6 7
//		   You define the past macro every time as macro_name(i, _).
//		   This second argument '_' (and not used) "eats" expansion stuff away, if you don't need to pass
//		   additional arguments. Look, what happens if you define the macro without arguments (and without argument-braces).
//		   Otherwise, if your repeated macro needs more arguments define like this:
//		      #define M(i, Arg1) "do stuff, using Arg1 and maybe loop counter i"
//		      STRINGIFY(EVAL(REPEAT(8, M, PassArgument)))
//---------------------------------------------------------------------
#define WHILE(pred, op, ...) \
    IF(pred(__VA_ARGS__)) \
    ( \
        OBSTRUCT(WHILE_INDIRECT) () \
        ( \
            pred, op, op(__VA_ARGS__) \
        ), \
        __VA_ARGS__ \
    )
#define WHILE_INDIRECT() WHILE
//---------------------------------------------------------------------
////////////////////////////////
//////// COMPARISON
////////////////////////////////
#define PRIMITIVE_COMPARE(x, y) IS_PAREN \
( \
COMPARE_ ## x ( COMPARE_ ## y) (())  \
)
//---------------------------------------------------------------------
#define IS_COMPARABLE(x) IS_PAREN( CONCAT(COMPARE_, x) (()) )
////
#define NOT_EQUAL(x, y) \
IIF(BITAND(IS_COMPARABLE(x))(IS_COMPARABLE(y)) ) \
( \
   PRIMITIVE_COMPARE, \
   1 EAT \
)(x, y)
//---------------------------------------------------------------------
#define EQUAL(x, y) COMPL(NOT_EQUAL(x, y))
//---------------------------------------------------------------------
// The EQUAL Macro allows you to check, if two given tokens, i.e. simple text,
//   are equal.
//   Do not use PRIMITIVE_COMPARE standalone. It has a terrible behavior, if the
//   necessary COMPARE_ Macros of the given tokens aren't defined.
// To Use the EQUAL Macro you have to define a COMPARE_ Macro of the two
//   Tokens to be compared beforehand. For Example:
//		#define COMPARE_foo(x) x
//		#define COMPARE_bar(x) x
//   for a use like:
//		EQUAL(foo,bar);
//		EQUAL(foo,foo);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Some Basic Values (like for Numbers) can be found at the Bottom
//---------------------------------------------------------------------
//
//========================================================================
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////













// TODO - Based on the WHILE Loop
// #define _CREATE_NTH_ARG_LIST

//Macro "returns" the number of passed arguments
//Current Implementation: A Maximum of 63
//Easily extendible (in an obvious way...) to up to 63
//(which reaches the limit of preprocessor arguments anyway...)
#define _GET_NTH_ARG(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,N,...) N
#define COUNT_VARARGS_(...) _GET_NTH_ARG("ignored", ##__VA_ARGS__, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define COUNT_VARARGS(...) COUNT_VARARGS_(__VA_ARGS__)
//Ähnliche Funktion, kann aber nicht mit "leeren" variadic arguments umgehen
//		#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 10,9,8,7,6,5,4,3,2,1)
//		#define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) N



// A general MacroOverloader
// Use it the right way and the preprocessor chooses the right function/macro
// for you at compile time, depending on the number of passed arguments
//Example: "depr()", "GET_REAL_TIME()"
#define macro_overloader(func, ...) \
	macro_overloader_(func, COUNT_VARARGS(__VA_ARGS__))
#define macro_overloader_(func, nargs) \
	macro_overloader__(func, nargs)
#define macro_overloader__(func, nargs) \
	func ## nargs







/*////////////////////
 * A Framing for applying a macro over a list of args, like in
 * a for-each-loop.
 */////////////////////
/*////////////////////
 * Usage:
 * #define a macro to be used over many arguments
 * #define a macro with a comma seperated list of the wanted arguments, or pass the arg list directly
 * Use: CALL_MACRO_X_FOR_EACH(MACRO, Arg_List)
 */////////////////////
// Some chained override-macros, which are getting called cascaded,
// based on the n-arity of the passed arguments list.
// The cascading Call and throughpassing, nudged by the "coupled, gliding arg lists"
// creates a macro in a for-each like style.
#define _macro_foreach_0(_macroCall, ...)
#define _macro_foreach_1(_macroCall, x) _macroCall(x)
#define _macro_foreach_2(_macroCall, x, ...) _macroCall(x) _macro_foreach_1(_macroCall, __VA_ARGS__)
#define _macro_foreach_3(_macroCall, x, ...) _macroCall(x) _macro_foreach_2(_macroCall, __VA_ARGS__)
#define _macro_foreach_4(_macroCall, x, ...) _macroCall(x) _macro_foreach_3(_macroCall, __VA_ARGS__)
#define _macro_foreach_5(_macroCall, x, ...) _macroCall(x) _macro_foreach_4(_macroCall, __VA_ARGS__)
#define _macro_foreach_6(_macroCall, x, ...) _macroCall(x) _macro_foreach_5(_macroCall, __VA_ARGS__)
#define _macro_foreach_7(_macroCall, x, ...) _macroCall(x) _macro_foreach_6(_macroCall, __VA_ARGS__)
#define _macro_foreach_8(_macroCall, x, ...) _macroCall(x) _macro_foreach_7(_macroCall, __VA_ARGS__)
#define _macro_foreach_9(_macroCall, x, ...) _macroCall(x) _macro_foreach_8(_macroCall, __VA_ARGS__)
#define _macro_foreach_10(_macroCall, x, ...) _macroCall(x) _macro_foreach_9(_macroCall, __VA_ARGS__)
#define _macro_foreach_11(_macroCall, x, ...) _macroCall(x) _macro_foreach_10(_macroCall, __VA_ARGS__)
#define _macro_foreach_12(_macroCall, x, ...) _macroCall(x) _macro_foreach_11(_macroCall, __VA_ARGS__)
#define _macro_foreach_13(_macroCall, x, ...) _macroCall(x) _macro_foreach_12(_macroCall, __VA_ARGS__)
#define _macro_foreach_14(_macroCall, x, ...) _macroCall(x) _macro_foreach_13(_macroCall, __VA_ARGS__)
#define _macro_foreach_15(_macroCall, x, ...) _macroCall(x) _macro_foreach_14(_macroCall, __VA_ARGS__)
#define _macro_foreach_16(_macroCall, x, ...) _macroCall(x) _macro_foreach_15(_macroCall, __VA_ARGS__)
#define _macro_foreach_17(_macroCall, x, ...) _macroCall(x) _macro_foreach_16(_macroCall, __VA_ARGS__)
#define _macro_foreach_18(_macroCall, x, ...) _macroCall(x) _macro_foreach_17(_macroCall, __VA_ARGS__)
#define _macro_foreach_19(_macroCall, x, ...) _macroCall(x) _macro_foreach_18(_macroCall, __VA_ARGS__)
#define _macro_foreach_20(_macroCall, x, ...) _macroCall(x) _macro_foreach_19(_macroCall, __VA_ARGS__)
#define _macro_foreach_21(_macroCall, x, ...) _macroCall(x) _macro_foreach_20(_macroCall, __VA_ARGS__)
#define _macro_foreach_22(_macroCall, x, ...) _macroCall(x) _macro_foreach_21(_macroCall, __VA_ARGS__)
#define _macro_foreach_23(_macroCall, x, ...) _macroCall(x) _macro_foreach_22(_macroCall, __VA_ARGS__)
#define _macro_foreach_24(_macroCall, x, ...) _macroCall(x) _macro_foreach_23(_macroCall, __VA_ARGS__)
#define _macro_foreach_25(_macroCall, x, ...) _macroCall(x) _macro_foreach_24(_macroCall, __VA_ARGS__)
#define _macro_foreach_26(_macroCall, x, ...) _macroCall(x) _macro_foreach_25(_macroCall, __VA_ARGS__)
#define _macro_foreach_27(_macroCall, x, ...) _macroCall(x) _macro_foreach_26(_macroCall, __VA_ARGS__)
#define _macro_foreach_28(_macroCall, x, ...) _macroCall(x) _macro_foreach_27(_macroCall, __VA_ARGS__)
#define _macro_foreach_29(_macroCall, x, ...) _macroCall(x) _macro_foreach_28(_macroCall, __VA_ARGS__)
#define _macro_foreach_30(_macroCall, x, ...) _macroCall(x) _macro_foreach_29(_macroCall, __VA_ARGS__)
#define _macro_foreach_31(_macroCall, x, ...) _macroCall(x) _macro_foreach_30(_macroCall, __VA_ARGS__)
#define _macro_foreach_32(_macroCall, x, ...) _macroCall(x) _macro_foreach_31(_macroCall, __VA_ARGS__)
#define _macro_foreach_33(_macroCall, x, ...) _macroCall(x) _macro_foreach_32(_macroCall, __VA_ARGS__)
#define _macro_foreach_34(_macroCall, x, ...) _macroCall(x) _macro_foreach_33(_macroCall, __VA_ARGS__)
#define _macro_foreach_35(_macroCall, x, ...) _macroCall(x) _macro_foreach_34(_macroCall, __VA_ARGS__)
#define _macro_foreach_36(_macroCall, x, ...) _macroCall(x) _macro_foreach_35(_macroCall, __VA_ARGS__)
#define _macro_foreach_37(_macroCall, x, ...) _macroCall(x) _macro_foreach_36(_macroCall, __VA_ARGS__)
#define _macro_foreach_38(_macroCall, x, ...) _macroCall(x) _macro_foreach_37(_macroCall, __VA_ARGS__)
#define _macro_foreach_39(_macroCall, x, ...) _macroCall(x) _macro_foreach_38(_macroCall, __VA_ARGS__)
#define _macro_foreach_40(_macroCall, x, ...) _macroCall(x) _macro_foreach_39(_macroCall, __VA_ARGS__)
#define _macro_foreach_41(_macroCall, x, ...) _macroCall(x) _macro_foreach_40(_macroCall, __VA_ARGS__)
#define _macro_foreach_42(_macroCall, x, ...) _macroCall(x) _macro_foreach_41(_macroCall, __VA_ARGS__)
#define _macro_foreach_43(_macroCall, x, ...) _macroCall(x) _macro_foreach_42(_macroCall, __VA_ARGS__)
#define _macro_foreach_44(_macroCall, x, ...) _macroCall(x) _macro_foreach_43(_macroCall, __VA_ARGS__)
#define _macro_foreach_45(_macroCall, x, ...) _macroCall(x) _macro_foreach_44(_macroCall, __VA_ARGS__)
#define _macro_foreach_46(_macroCall, x, ...) _macroCall(x) _macro_foreach_45(_macroCall, __VA_ARGS__)
#define _macro_foreach_47(_macroCall, x, ...) _macroCall(x) _macro_foreach_46(_macroCall, __VA_ARGS__)
#define _macro_foreach_48(_macroCall, x, ...) _macroCall(x) _macro_foreach_47(_macroCall, __VA_ARGS__)
#define _macro_foreach_49(_macroCall, x, ...) _macroCall(x) _macro_foreach_48(_macroCall, __VA_ARGS__)
#define _macro_foreach_50(_macroCall, x, ...) _macroCall(x) _macro_foreach_49(_macroCall, __VA_ARGS__)
#define _macro_foreach_51(_macroCall, x, ...) _macroCall(x) _macro_foreach_50(_macroCall, __VA_ARGS__)
#define _macro_foreach_52(_macroCall, x, ...) _macroCall(x) _macro_foreach_51(_macroCall, __VA_ARGS__)
#define _macro_foreach_53(_macroCall, x, ...) _macroCall(x) _macro_foreach_52(_macroCall, __VA_ARGS__)
#define _macro_foreach_54(_macroCall, x, ...) _macroCall(x) _macro_foreach_53(_macroCall, __VA_ARGS__)
#define _macro_foreach_55(_macroCall, x, ...) _macroCall(x) _macro_foreach_54(_macroCall, __VA_ARGS__)
#define _macro_foreach_56(_macroCall, x, ...) _macroCall(x) _macro_foreach_55(_macroCall, __VA_ARGS__)
#define _macro_foreach_57(_macroCall, x, ...) _macroCall(x) _macro_foreach_56(_macroCall, __VA_ARGS__)
#define _macro_foreach_58(_macroCall, x, ...) _macroCall(x) _macro_foreach_57(_macroCall, __VA_ARGS__)
#define _macro_foreach_59(_macroCall, x, ...) _macroCall(x) _macro_foreach_58(_macroCall, __VA_ARGS__)
#define _macro_foreach_60(_macroCall, x, ...) _macroCall(x) _macro_foreach_59(_macroCall, __VA_ARGS__)
#define _macro_foreach_61(_macroCall, x, ...) _macroCall(x) _macro_foreach_60(_macroCall, __VA_ARGS__)
#define _macro_foreach_62(_macroCall, x, ...) _macroCall(x) _macro_foreach_61(_macroCall, __VA_ARGS__)
#define _macro_foreach_63(_macroCall, x, ...) _macroCall(x) _macro_foreach_62(_macroCall, __VA_ARGS__)
////////////////////
//The length of the defined _GET_NTH_ARG and the used inside the CALL_MACRO_X_FOR_EACH has to be the same
// So here he gets an own one to secure that.
#define _GET_NTH_ARG_FE(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, N, ...) N
////////////////////
//The actual Macro
// Supplies a for-each construct for Variadic Macros. Supports at most 63 args or less.
// You see, how you could expand it ;oP - Äh, i mean, PreProcessor Arguments Limit already reached... ;o/
//   To make it work both with directly passed many arguments and also with
//   predefined lists we need an additional Expansion-Step.
//   Therefore the two chained Macros
#define CALL_MACRO_X_FOR_EACH(x,...) CALL_MACRO_X_FOR_EACH_EVALUATED(x,__VA_ARGS__)
#define CALL_MACRO_X_FOR_EACH_EVALUATED(x, ...) \
    _GET_NTH_ARG_FE("ignored", ##__VA_ARGS__, \
    _macro_foreach_62, _macro_foreach_61, _macro_foreach_60, _macro_foreach_59, _macro_foreach_58, _macro_foreach_57, _macro_foreach_56, _macro_foreach_55, _macro_foreach_54, _macro_foreach_53, _macro_foreach_52, _macro_foreach_51, _macro_foreach_50, _macro_foreach_49, _macro_foreach_48, _macro_foreach_47, _macro_foreach_46, _macro_foreach_45, _macro_foreach_44, _macro_foreach_43, _macro_foreach_42, _macro_foreach_41, _macro_foreach_40, _macro_foreach_39, _macro_foreach_38, _macro_foreach_37, _macro_foreach_36, _macro_foreach_35, _macro_foreach_34, _macro_foreach_33, _macro_foreach_32, _macro_foreach_31, _macro_foreach_30, _macro_foreach_29, _macro_foreach_28, _macro_foreach_27, _macro_foreach_26, _macro_foreach_25, _macro_foreach_24, _macro_foreach_23, _macro_foreach_22, _macro_foreach_21, _macro_foreach_20, _macro_foreach_19, _macro_foreach_18, _macro_foreach_17, _macro_foreach_16, _macro_foreach_15, _macro_foreach_14, _macro_foreach_13, _macro_foreach_12, _macro_foreach_11, _macro_foreach_10, _macro_foreach_9, _macro_foreach_8, _macro_foreach_7, _macro_foreach_6, _macro_foreach_5, _macro_foreach_4, _macro_foreach_3, _macro_foreach_2, _macro_foreach_1, _macro_foreach_0)(x, ##__VA_ARGS__)
////////////////////
////////////////////
// Simple Example, albeit not very useful. Just to show how to use
//		#define ERRPrint_MAC(text) fprintf(stderr, text);
//		#define print_errors "error1\n", "error2\n"
//
//		CALL_MACRO_X_FOR_EACH(ERRPrint_MAC, "error1\n", "error2\n", "error3\n")
//		CALL_MACRO_X_FOR_EACH(ERRPrint_MAC, print_errors)
////////////////////
// Example usage1:
//     #define FWD_DECLARE_CLASS(cls) class cls;
//     CALL_MACRO_X_FOR_EACH(FWD_DECLARE_CLASS, Foo, Bar)
////////////////////
// Example usage 2:
//     #define START_NS(ns) namespace ns {
//     #define END_NS(ns) }
//     #define MY_NAMESPACES System, Net, Http
//     CALL_MACRO_X_FOR_EACH(START_NS, MY_NAMESPACES)
//     typedef foo int;
//     CALL_MACRO_X_FOR_EACH(END_NS, MY_NAMESPACES)
////////////////////
/*////////////////////
 * Similiar like the above one, but returns a comma-separated List
 * Above one: CALL_MACRO_X_FOR_EACH(STRINGIFY, a, b, c)  -->  "a" "b" "c"
 * Below one: CALL_MACRO_X_FOR_EACH__LIST(STRINGIFY, a, b, c)  -->  "a", "b", "c"
 */////////////////////
#define _macro_foreach_0__list(_macroCall, ...)
#define _macro_foreach_1__list(_macroCall, x) _macroCall(x)
#define _macro_foreach_2__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_1__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_3__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_2__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_4__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_3__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_5__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_4__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_6__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_5__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_7__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_6__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_8__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_7__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_9__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_8__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_10__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_9__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_11__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_10__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_12__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_11__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_13__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_12__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_14__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_13__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_15__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_14__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_16__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_15__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_17__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_16__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_18__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_17__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_19__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_18__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_20__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_19__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_21__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_20__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_22__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_21__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_23__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_22__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_24__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_23__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_25__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_24__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_26__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_25__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_27__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_26__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_28__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_27__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_29__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_28__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_30__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_29__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_31__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_30__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_32__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_31__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_33__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_32__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_34__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_33__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_35__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_34__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_36__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_35__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_37__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_36__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_38__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_37__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_39__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_38__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_40__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_39__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_41__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_40__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_42__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_41__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_43__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_42__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_44__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_43__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_45__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_44__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_46__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_45__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_47__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_46__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_48__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_47__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_49__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_48__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_50__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_49__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_51__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_50__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_52__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_51__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_53__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_52__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_54__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_53__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_55__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_54__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_56__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_55__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_57__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_56__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_58__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_57__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_59__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_58__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_60__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_59__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_61__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_60__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_62__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_61__list(_macroCall, __VA_ARGS__)
#define _macro_foreach_63__list(_macroCall, x, ...) _macroCall(x), _macro_foreach_62__list(_macroCall, __VA_ARGS__)
////////////////////
//The length of the defined _GET_NTH_ARG and the used inside the CALL_MACRO_X_FOR_EACH has to be the same
// So here he gets an own one to secure that.
#define _GET_NTH_ARG_FE__LIST(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, N, ...) N
////////////////////
//The actual Macro
// Supplies a for-each construct for Variadic Macros. Supports at most 63 args or less.
// You see, how you could expand it ;oP - Äh, i mean, PreProcessor Arguments Limit already reached... ;o/
//   To make it work both with directly passed many arguments and also with
//   predefined lists we need an additional Expansion-Step.
//   Therefore the two chained Macros
#define CALL_MACRO_X_FOR_EACH__LIST(x,...) CALL_MACRO_X_FOR_EACH__LIST_EVALUATED(x,__VA_ARGS__)
#define CALL_MACRO_X_FOR_EACH__LIST_EVALUATED(x, ...) \
    _GET_NTH_ARG_FE__LIST("ignored", ##__VA_ARGS__, \
    _macro_foreach_62__list, _macro_foreach_61__list, _macro_foreach_60__list, _macro_foreach_59__list, _macro_foreach_58__list, _macro_foreach_57__list, _macro_foreach_56__list, _macro_foreach_55__list, _macro_foreach_54__list, _macro_foreach_53__list, _macro_foreach_52__list, _macro_foreach_51__list, _macro_foreach_50__list, _macro_foreach_49__list, _macro_foreach_48__list, _macro_foreach_47__list, _macro_foreach_46__list, _macro_foreach_45__list, _macro_foreach_44__list, _macro_foreach_43__list, _macro_foreach_42__list, _macro_foreach_41__list, _macro_foreach_40__list, _macro_foreach_39__list, _macro_foreach_38__list, _macro_foreach_37__list, _macro_foreach_36__list, _macro_foreach_35__list, _macro_foreach_34__list, _macro_foreach_33__list, _macro_foreach_32__list, _macro_foreach_31__list, _macro_foreach_30__list, _macro_foreach_29__list, _macro_foreach_28__list, _macro_foreach_27__list, _macro_foreach_26__list, _macro_foreach_25__list, _macro_foreach_24__list, _macro_foreach_23__list, _macro_foreach_22__list, _macro_foreach_21__list, _macro_foreach_20__list, _macro_foreach_19__list, _macro_foreach_18__list, _macro_foreach_17__list, _macro_foreach_16__list, _macro_foreach_15__list, _macro_foreach_14__list, _macro_foreach_13__list, _macro_foreach_12__list, _macro_foreach_11__list, _macro_foreach_10__list, _macro_foreach_9__list, _macro_foreach_8__list, _macro_foreach_7__list, _macro_foreach_6__list, _macro_foreach_5__list, _macro_foreach_4__list, _macro_foreach_3__list, _macro_foreach_2__list, _macro_foreach_1__list, _macro_foreach_0__list)(x, ##__VA_ARGS__)
////////////////////
////////////////////
////////////////////
////////////////////
#define _macro_foreach_3tupel_0(_macroCall, ...)
#define _macro_foreach_3tupel_1(_macroCall, x) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_2(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_3(_macroCall, x, y, z, ...) _macroCall(x, y, z)
#define _macro_foreach_3tupel_4(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_5(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_6(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_3(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_7(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_8(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_9(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_6(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_10(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_11(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_12(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_9(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_13(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_14(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_15(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_12(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_16(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_17(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_18(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_15(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_19(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_20(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_21(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_18(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_22(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_23(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_24(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_21(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_25(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_26(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_27(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_24(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_28(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_29(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_30(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_27(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_31(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_32(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_33(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_30(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_34(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_35(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_36(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_33(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_37(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_38(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_39(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_36(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_40(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_41(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_42(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_39(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_43(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_44(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_45(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_42(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_46(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_47(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_48(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_45(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_49(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_50(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_51(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_48(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_52(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_53(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_54(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_51(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_55(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_56(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_57(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_54(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_58(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_59(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_60(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_57(_macroCall, __VA_ARGS__)
#define _macro_foreach_3tupel_61(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_62(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_foreach_3tupel_63(_macroCall, x, y, z, ...) _macroCall(x, y, z) _macro_foreach_3tupel_60(_macroCall, __VA_ARGS__)
////////////////////
//
#define CALL_MACRO_X_FOR_EACH_3TUPEL(x,...) CALL_MACRO_X_FOR_EACH_3TUPEL_EVALUATED(x,__VA_ARGS__)
#define CALL_MACRO_X_FOR_EACH_3TUPEL_EVALUATED(x, ...) \
    _GET_NTH_ARG_FE("ignored", ##__VA_ARGS__, \
    _macro_foreach_3tupel_62, _macro_foreach_3tupel_61, _macro_foreach_3tupel_60, _macro_foreach_3tupel_59, _macro_foreach_3tupel_58, _macro_foreach_3tupel_57, _macro_foreach_3tupel_56, _macro_foreach_3tupel_55, _macro_foreach_3tupel_54, _macro_foreach_3tupel_53, _macro_foreach_3tupel_52, _macro_foreach_3tupel_51, _macro_foreach_3tupel_50, _macro_foreach_3tupel_49, _macro_foreach_3tupel_48, _macro_foreach_3tupel_47, _macro_foreach_3tupel_46, _macro_foreach_3tupel_45, _macro_foreach_3tupel_44, _macro_foreach_3tupel_43, _macro_foreach_3tupel_42, _macro_foreach_3tupel_41, _macro_foreach_3tupel_40, _macro_foreach_3tupel_39, _macro_foreach_3tupel_38, _macro_foreach_3tupel_37, _macro_foreach_3tupel_36, _macro_foreach_3tupel_35, _macro_foreach_3tupel_34, _macro_foreach_3tupel_33, _macro_foreach_3tupel_32, _macro_foreach_3tupel_31, _macro_foreach_3tupel_30, _macro_foreach_3tupel_29, _macro_foreach_3tupel_28, _macro_foreach_3tupel_27, _macro_foreach_3tupel_26, _macro_foreach_3tupel_25, _macro_foreach_3tupel_24, _macro_foreach_3tupel_23, _macro_foreach_3tupel_22, _macro_foreach_3tupel_21, _macro_foreach_3tupel_20, _macro_foreach_3tupel_19, _macro_foreach_3tupel_18, _macro_foreach_3tupel_17, _macro_foreach_3tupel_16, _macro_foreach_3tupel_15, _macro_foreach_3tupel_14, _macro_foreach_3tupel_13, _macro_foreach_3tupel_12, _macro_foreach_3tupel_11, _macro_foreach_3tupel_10, _macro_foreach_3tupel_9, _macro_foreach_3tupel_8, _macro_foreach_3tupel_7, _macro_foreach_3tupel_6, _macro_foreach_3tupel_5, _macro_foreach_3tupel_4, _macro_foreach_3tupel_3, _macro_foreach_3tupel_2, _macro_foreach_3tupel_1, _macro_foreach_3tupel_0)(x, ##__VA_ARGS__)
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////









//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Exclude last Entry from List  --------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
#define _macro_exclude_last_from_list_0(...)
#define _macro_exclude_last_from_list_1(A1)
#define _macro_exclude_last_from_list_2(A1, ...) A1
#define _macro_exclude_last_from_list_3(A1, ...) A1, _macro_exclude_last_from_list_2(__VA_ARGS__)
#define _macro_exclude_last_from_list_4(A1, ...) A1, _macro_exclude_last_from_list_3(__VA_ARGS__)
#define _macro_exclude_last_from_list_5(A1, ...) A1, _macro_exclude_last_from_list_4(__VA_ARGS__)
#define _macro_exclude_last_from_list_6(A1, ...) A1, _macro_exclude_last_from_list_5(__VA_ARGS__)
#define _macro_exclude_last_from_list_7(A1, ...) A1, _macro_exclude_last_from_list_6(__VA_ARGS__)
#define _macro_exclude_last_from_list_8(A1, ...) A1, _macro_exclude_last_from_list_7(__VA_ARGS__)
#define _macro_exclude_last_from_list_9(A1, ...) A1, _macro_exclude_last_from_list_8(__VA_ARGS__)
#define _macro_exclude_last_from_list_10(A1, ...) A1, _macro_exclude_last_from_list_9(__VA_ARGS__)
#define _macro_exclude_last_from_list_11(A1, ...) A1, _macro_exclude_last_from_list_10(__VA_ARGS__)
#define _macro_exclude_last_from_list_12(A1, ...) A1, _macro_exclude_last_from_list_11(__VA_ARGS__)
#define _macro_exclude_last_from_list_13(A1, ...) A1, _macro_exclude_last_from_list_12(__VA_ARGS__)
#define _macro_exclude_last_from_list_14(A1, ...) A1, _macro_exclude_last_from_list_13(__VA_ARGS__)
#define _macro_exclude_last_from_list_15(A1, ...) A1, _macro_exclude_last_from_list_14(__VA_ARGS__)
#define _macro_exclude_last_from_list_16(A1, ...) A1, _macro_exclude_last_from_list_15(__VA_ARGS__)
#define _macro_exclude_last_from_list_17(A1, ...) A1, _macro_exclude_last_from_list_16(__VA_ARGS__)
#define _macro_exclude_last_from_list_18(A1, ...) A1, _macro_exclude_last_from_list_17(__VA_ARGS__)
#define _macro_exclude_last_from_list_19(A1, ...) A1, _macro_exclude_last_from_list_18(__VA_ARGS__)
#define _macro_exclude_last_from_list_20(A1, ...) A1, _macro_exclude_last_from_list_19(__VA_ARGS__)
#define _macro_exclude_last_from_list_21(A1, ...) A1, _macro_exclude_last_from_list_20(__VA_ARGS__)
#define _macro_exclude_last_from_list_22(A1, ...) A1, _macro_exclude_last_from_list_21(__VA_ARGS__)
#define _macro_exclude_last_from_list_23(A1, ...) A1, _macro_exclude_last_from_list_22(__VA_ARGS__)
#define _macro_exclude_last_from_list_24(A1, ...) A1, _macro_exclude_last_from_list_23(__VA_ARGS__)
#define _macro_exclude_last_from_list_25(A1, ...) A1, _macro_exclude_last_from_list_24(__VA_ARGS__)
#define _macro_exclude_last_from_list_26(A1, ...) A1, _macro_exclude_last_from_list_25(__VA_ARGS__)
#define _macro_exclude_last_from_list_27(A1, ...) A1, _macro_exclude_last_from_list_26(__VA_ARGS__)
#define _macro_exclude_last_from_list_28(A1, ...) A1, _macro_exclude_last_from_list_27(__VA_ARGS__)
#define _macro_exclude_last_from_list_29(A1, ...) A1, _macro_exclude_last_from_list_28(__VA_ARGS__)
#define _macro_exclude_last_from_list_30(A1, ...) A1, _macro_exclude_last_from_list_29(__VA_ARGS__)
#define _macro_exclude_last_from_list_31(A1, ...) A1, _macro_exclude_last_from_list_30(__VA_ARGS__)
#define _macro_exclude_last_from_list_32(A1, ...) A1, _macro_exclude_last_from_list_31(__VA_ARGS__)
#define _macro_exclude_last_from_list_33(A1, ...) A1, _macro_exclude_last_from_list_32(__VA_ARGS__)
#define _macro_exclude_last_from_list_34(A1, ...) A1, _macro_exclude_last_from_list_33(__VA_ARGS__)
#define _macro_exclude_last_from_list_35(A1, ...) A1, _macro_exclude_last_from_list_34(__VA_ARGS__)
#define _macro_exclude_last_from_list_36(A1, ...) A1, _macro_exclude_last_from_list_35(__VA_ARGS__)
#define _macro_exclude_last_from_list_37(A1, ...) A1, _macro_exclude_last_from_list_36(__VA_ARGS__)
#define _macro_exclude_last_from_list_38(A1, ...) A1, _macro_exclude_last_from_list_37(__VA_ARGS__)
#define _macro_exclude_last_from_list_39(A1, ...) A1, _macro_exclude_last_from_list_38(__VA_ARGS__)
#define _macro_exclude_last_from_list_40(A1, ...) A1, _macro_exclude_last_from_list_39(__VA_ARGS__)
#define _macro_exclude_last_from_list_41(A1, ...) A1, _macro_exclude_last_from_list_40(__VA_ARGS__)
#define _macro_exclude_last_from_list_42(A1, ...) A1, _macro_exclude_last_from_list_41(__VA_ARGS__)
#define _macro_exclude_last_from_list_43(A1, ...) A1, _macro_exclude_last_from_list_42(__VA_ARGS__)
#define _macro_exclude_last_from_list_44(A1, ...) A1, _macro_exclude_last_from_list_43(__VA_ARGS__)
#define _macro_exclude_last_from_list_45(A1, ...) A1, _macro_exclude_last_from_list_44(__VA_ARGS__)
#define _macro_exclude_last_from_list_46(A1, ...) A1, _macro_exclude_last_from_list_45(__VA_ARGS__)
#define _macro_exclude_last_from_list_47(A1, ...) A1, _macro_exclude_last_from_list_46(__VA_ARGS__)
#define _macro_exclude_last_from_list_48(A1, ...) A1, _macro_exclude_last_from_list_47(__VA_ARGS__)
#define _macro_exclude_last_from_list_49(A1, ...) A1, _macro_exclude_last_from_list_48(__VA_ARGS__)
#define _macro_exclude_last_from_list_50(A1, ...) A1, _macro_exclude_last_from_list_49(__VA_ARGS__)
#define _macro_exclude_last_from_list_51(A1, ...) A1, _macro_exclude_last_from_list_50(__VA_ARGS__)
#define _macro_exclude_last_from_list_52(A1, ...) A1, _macro_exclude_last_from_list_51(__VA_ARGS__)
#define _macro_exclude_last_from_list_53(A1, ...) A1, _macro_exclude_last_from_list_52(__VA_ARGS__)
#define _macro_exclude_last_from_list_54(A1, ...) A1, _macro_exclude_last_from_list_53(__VA_ARGS__)
#define _macro_exclude_last_from_list_55(A1, ...) A1, _macro_exclude_last_from_list_54(__VA_ARGS__)
#define _macro_exclude_last_from_list_56(A1, ...) A1, _macro_exclude_last_from_list_55(__VA_ARGS__)
#define _macro_exclude_last_from_list_57(A1, ...) A1, _macro_exclude_last_from_list_56(__VA_ARGS__)
#define _macro_exclude_last_from_list_58(A1, ...) A1, _macro_exclude_last_from_list_57(__VA_ARGS__)
#define _macro_exclude_last_from_list_59(A1, ...) A1, _macro_exclude_last_from_list_58(__VA_ARGS__)
#define _macro_exclude_last_from_list_60(A1, ...) A1, _macro_exclude_last_from_list_59(__VA_ARGS__)
#define _macro_exclude_last_from_list_61(A1, ...) A1, _macro_exclude_last_from_list_60(__VA_ARGS__)
#define _macro_exclude_last_from_list_62(A1, ...) A1, _macro_exclude_last_from_list_61(__VA_ARGS__)
#define _macro_exclude_last_from_list_63(A1, ...) A1, _macro_exclude_last_from_list_62(__VA_ARGS__)
////////////////////
//The length of the defined _GET_NTH_ARG and the used inside the EXCLUDE_LAST_ENTRY_FROM_LIST has to be the same
// So here he gets an own one to secure that.
#define _GET_NTH_ARG_EXCL_LAST_ENTR(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, N, ...) N
////////////////////
//The actual Macro
// Supplies a for-each construct for Variadic Macros. Supports at most 63 args or less.
// You see, how you could expand it ;oP - Äh, i mean, PreProcessor Arguments Limit already reached... ;o/
//   To make it work both with directly passed many arguments and also with
//   predefined lists we need an additional Expansion-Step.
//   Therefore the two chained Macros
#define EXCLUDE_LAST_ENTRY_FROM_LIST(...) EXCLUDE_LAST_ENTRY_FROM_LIST_EVALUATED(__VA_ARGS__)
#define EXCLUDE_LAST_ENTRY_FROM_LIST_EVALUATED(...) \
    _GET_NTH_ARG_EXCL_LAST_ENTR("ignored", ##__VA_ARGS__, \
    _macro_exclude_last_from_list_62, _macro_exclude_last_from_list_61, _macro_exclude_last_from_list_60, _macro_exclude_last_from_list_59, _macro_exclude_last_from_list_58, _macro_exclude_last_from_list_57, _macro_exclude_last_from_list_56, _macro_exclude_last_from_list_55, _macro_exclude_last_from_list_54, _macro_exclude_last_from_list_53, _macro_exclude_last_from_list_52, _macro_exclude_last_from_list_51, _macro_exclude_last_from_list_50, _macro_exclude_last_from_list_49, _macro_exclude_last_from_list_48, _macro_exclude_last_from_list_47, _macro_exclude_last_from_list_46, _macro_exclude_last_from_list_45, _macro_exclude_last_from_list_44, _macro_exclude_last_from_list_43, _macro_exclude_last_from_list_42, _macro_exclude_last_from_list_41, _macro_exclude_last_from_list_40, _macro_exclude_last_from_list_39, _macro_exclude_last_from_list_38, _macro_exclude_last_from_list_37, _macro_exclude_last_from_list_36, _macro_exclude_last_from_list_35, _macro_exclude_last_from_list_34, _macro_exclude_last_from_list_33, _macro_exclude_last_from_list_32, _macro_exclude_last_from_list_31, _macro_exclude_last_from_list_30, _macro_exclude_last_from_list_29, _macro_exclude_last_from_list_28, _macro_exclude_last_from_list_27, _macro_exclude_last_from_list_26, _macro_exclude_last_from_list_25, _macro_exclude_last_from_list_24, _macro_exclude_last_from_list_23, _macro_exclude_last_from_list_22, _macro_exclude_last_from_list_21, _macro_exclude_last_from_list_20, _macro_exclude_last_from_list_19, _macro_exclude_last_from_list_18, _macro_exclude_last_from_list_17, _macro_exclude_last_from_list_16, _macro_exclude_last_from_list_15, _macro_exclude_last_from_list_14, _macro_exclude_last_from_list_13, _macro_exclude_last_from_list_12, _macro_exclude_last_from_list_11, _macro_exclude_last_from_list_10, _macro_exclude_last_from_list_9, _macro_exclude_last_from_list_8, _macro_exclude_last_from_list_7, _macro_exclude_last_from_list_6, _macro_exclude_last_from_list_5, _macro_exclude_last_from_list_4, _macro_exclude_last_from_list_3, _macro_exclude_last_from_list_2, _macro_exclude_last_from_list_1, _macro_exclude_last_from_list_0)(__VA_ARGS__)
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////








//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Extract from Tupel  ------------------------------------------------------------------------//
//----  (Could come in handy inside "call_macro_x_for_each_NTupel or loops)  -----------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
#define EXTRACT_1_from_2(A, B) A
#define EXTRACT_2_from_2(A, B) B
//----------------------------------------------------------------------------------------------------
#define EXTRACT_1_from_3(A, B, C) A
#define EXTRACT_2_from_3(A, B, C) B
#define EXTRACT_3_from_3(A, B, C) C
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////








//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Demux Arguments  ---------------------------------------------------------------------------//
//----  (Demultiplexing of the Arguments-List to different Order)  ---------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
// 3 Tupel
//--------  (Turns Arguments like
//--------        A1, A2, A3, B1, B2, B3, C1, C2, C3
//--------  into
//--------        A1, B1, C1, A2, B2, C2, A3, B3, C3
//--------  It delivers back a "bare" Arguments-List, formatted like __VA_ARGS__
//--------  I.e. without braces. So you can put this for example inside another macros Arguments braces
//--------  Or surround it manually with braces for specific applications
//--------  Usage examples.
//--------       SOME_MACRO( DEMUX_ARGS_3TUPEL(LONG_ARGS_AS_MULTIPLE_OF_3) )
//--------       STRINGIFY( (DEMUX_ARGS_3TUPEL(__VA_ARGS__) )
//--------       ARRAY_ENTRY(4, ( DEMUX_ARGS_3TUPEL(LONG_ARGS_AS_MULTIPLE_OF_3) ))
////////////////
#define _macro_demux_args_3tupel_0(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_1(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_2(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_4(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_5(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_7(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_8(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_10(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_11(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_13(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_14(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_16(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_17(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_19(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_20(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_22(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_23(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_25(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_26(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_28(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_29(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_31(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_32(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_34(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_35(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_37(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_38(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_40(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_41(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_43(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_44(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_46(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_47(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_49(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_50(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_52(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_53(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_55(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_56(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_58(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_59(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_61(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
#define _macro_demux_args_3tupel_62(...) "ERROR. To few variadic arguments in overloaded macro"ERROR
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define _macro_demux_args_3tupel_3(A, B, C) \
	A, B, C
#define _macro_demux_args_3tupel_6(A1, A2, A3, B1, B2, B3) \
	A1, B1, A2, B2, A3, B3
#define _macro_demux_args_3tupel_9(A1, A2, A3, B1, B2, B3, C1, C2, C3) \
	A1, B1, C1, A2, B2, C2, A3, B3, C3
#define _macro_demux_args_3tupel_12(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3) \
	A1, B1, C1, D1, A2, B2, C2, D2, A3, B3, C3, D3
#define _macro_demux_args_3tupel_15(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3) \
	A1, B1, C1, D1, E1, A2, B2, C2, D2, E2, A3, B3, C3, D3, E3
#define _macro_demux_args_3tupel_18(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3) \
	A1, B1, C1, D1, E1, F1, A2, B2, C2, D2, E2, F2, A3, B3, C3, D3, E3, F3
#define _macro_demux_args_3tupel_21(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3) \
	A1, B1, C1, D1, E1, F1, G1, A2, B2, C2, D2, E2, F2, G2, A3, B3, C3, D3, E3, F3, G3
#define _macro_demux_args_3tupel_24(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3) \
	A1, B1, C1, D1, E1, F1, G1, H1, A2, B2, C2, D2, E2, F2, G2, H2, A3, B3, C3, D3, E3, F3, G3, H3
#define _macro_demux_args_3tupel_27(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, A2, B2, C2, D2, E2, F2, G2, H2, I2, A3, B3, C3, D3, E3, F3, G3, H3, I3
#define _macro_demux_args_3tupel_30(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3
#define _macro_demux_args_3tupel_33(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3, K1, K2, K3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, K1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3, K3
#define _macro_demux_args_3tupel_36(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3, K1, K2, K3, L1, L2, L3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, K1, L1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2, L2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3, K3, L3
#define _macro_demux_args_3tupel_39(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3, K1, K2, K3, L1, L2, L3, M1, M2, M3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, K1, L1, M1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2, L2, M2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3, K3, L3, M3
#define _macro_demux_args_3tupel_42(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3, K1, K2, K3, L1, L2, L3, M1, M2, M3, N1, N2, N3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, K1, L1, M1, N1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2, L2, M2, N2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3, K3, L3, M3, N3
#define _macro_demux_args_3tupel_45(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3, K1, K2, K3, L1, L2, L3, M1, M2, M3, N1, N2, N3, O1, O2, O3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, K1, L1, M1, N1, O1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2, L2, M2, N2, O2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3, K3, L3, M3, N3, O3
#define _macro_demux_args_3tupel_48(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3, K1, K2, K3, L1, L2, L3, M1, M2, M3, N1, N2, N3, O1, O2, O3, P1, P2, P3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, K1, L1, M1, N1, O1, P1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2, L2, M2, N2, O2, P2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3, K3, L3, M3, N3, O3, P3
#define _macro_demux_args_3tupel_51(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3, K1, K2, K3, L1, L2, L3, M1, M2, M3, N1, N2, N3, O1, O2, O3, P1, P2, P3, Q1, Q2, Q3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, K1, L1, M1, N1, O1, P1, Q1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2, L2, M2, N2, O2, P2, Q2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3, K3, L3, M3, N3, O3, P3, Q3
#define _macro_demux_args_3tupel_54(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3, K1, K2, K3, L1, L2, L3, M1, M2, M3, N1, N2, N3, O1, O2, O3, P1, P2, P3, Q1, Q2, Q3, R1, R2, R3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, K1, L1, M1, N1, O1, P1, Q1, R1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2, L2, M2, N2, O2, P2, Q2, R2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3, K3, L3, M3, N3, O3, P3, Q3, R3
#define _macro_demux_args_3tupel_57(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3, K1, K2, K3, L1, L2, L3, M1, M2, M3, N1, N2, N3, O1, O2, O3, P1, P2, P3, Q1, Q2, Q3, R1, R2, R3, S1, S2, S3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, K1, L1, M1, N1, O1, P1, Q1, R1, S1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2, L2, M2, N2, O2, P2, Q2, R2, S2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3, K3, L3, M3, N3, O3, P3, Q3, R3, S3
#define _macro_demux_args_3tupel_60(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3, K1, K2, K3, L1, L2, L3, M1, M2, M3, N1, N2, N3, O1, O2, O3, P1, P2, P3, Q1, Q2, Q3, R1, R2, R3, S1, S2, S3, T1, T2, T3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, K1, L1, M1, N1, O1, P1, Q1, R1, S1, T1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2, L2, M2, N2, O2, P2, Q2, R2, S2, T2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3, K3, L3, M3, N3, O3, P3, Q3, R3, S3, T3
#define _macro_demux_args_3tupel_63(A1, A2, A3, B1, B2, B3, C1, C2, C3, D1, D2, D3, E1, E2, E3, F1, F2, F3, G1, G2, G3, H1, H2, H3, I1, I2, I3, J1, J2, J3, K1, K2, K3, L1, L2, L3, M1, M2, M3, N1, N2, N3, O1, O2, O3, P1, P2, P3, Q1, Q2, Q3, R1, R2, R3, S1, S2, S3, T1, T2, T3, U1, U2, U3) \
	A1, B1, C1, D1, E1, F1, G1, H1, I1, J1, K1, L1, M1, N1, O1, P1, Q1, R1, S1, T1, U1, A2, B2, C2, D2, E2, F2, G2, H2, I2, J2, K2, L2, M2, N2, O2, P2, Q2, R2, S2, T2, U2, A3, B3, C3, D3, E3, F3, G3, H3, I3, J3, K3, L3, M3, N3, O3, P3, Q3, R3, S3, T3, U3
//
#define _GET_NTH_ARG_MUX_ARGS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, N, ...) N
//
#define DEMUX_ARGS_3TUPEL(...) DEMUX_ARGS_3TUPEL_EVALUATED(__VA_ARGS__)
#define DEMUX_ARGS_3TUPEL_EVALUATED(...) \
    _GET_NTH_ARG_MUX_ARGS("ignored", ##__VA_ARGS__, \
    _macro_demux_args_3tupel_63, _macro_demux_args_3tupel_62, _macro_demux_args_3tupel_61, _macro_demux_args_3tupel_60, _macro_demux_args_3tupel_59, _macro_demux_args_3tupel_58, _macro_demux_args_3tupel_57, _macro_demux_args_3tupel_56, _macro_demux_args_3tupel_55, _macro_demux_args_3tupel_54, _macro_demux_args_3tupel_53, _macro_demux_args_3tupel_52, _macro_demux_args_3tupel_51, _macro_demux_args_3tupel_50, _macro_demux_args_3tupel_49, _macro_demux_args_3tupel_48, _macro_demux_args_3tupel_47, _macro_demux_args_3tupel_46, _macro_demux_args_3tupel_45, _macro_demux_args_3tupel_44, _macro_demux_args_3tupel_43, _macro_demux_args_3tupel_42, _macro_demux_args_3tupel_41, _macro_demux_args_3tupel_40, _macro_demux_args_3tupel_39, _macro_demux_args_3tupel_38, _macro_demux_args_3tupel_37, _macro_demux_args_3tupel_36, _macro_demux_args_3tupel_35, _macro_demux_args_3tupel_34, _macro_demux_args_3tupel_33, _macro_demux_args_3tupel_32, _macro_demux_args_3tupel_31, _macro_demux_args_3tupel_30, _macro_demux_args_3tupel_29, _macro_demux_args_3tupel_28, _macro_demux_args_3tupel_27, _macro_demux_args_3tupel_26, _macro_demux_args_3tupel_25, _macro_demux_args_3tupel_24, _macro_demux_args_3tupel_23, _macro_demux_args_3tupel_22, _macro_demux_args_3tupel_21, _macro_demux_args_3tupel_20, _macro_demux_args_3tupel_19, _macro_demux_args_3tupel_18, _macro_demux_args_3tupel_17, _macro_demux_args_3tupel_16, _macro_demux_args_3tupel_15, _macro_demux_args_3tupel_14, _macro_demux_args_3tupel_13, _macro_demux_args_3tupel_12, _macro_demux_args_3tupel_11, _macro_demux_args_3tupel_10, _macro_demux_args_3tupel_9, _macro_demux_args_3tupel_8, _macro_demux_args_3tupel_7, _macro_demux_args_3tupel_6, _macro_demux_args_3tupel_5, _macro_demux_args_3tupel_4, _macro_demux_args_3tupel_3, _macro_demux_args_3tupel_2, _macro_demux_args_3tupel_1, _macro_demux_args_3tupel_0)(__VA_ARGS__)
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


















//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Split Arguments List  ----------------------------------------------------------------------//
//----  (Divide the Args List in Parts and extracts certain ones  ----------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
// 3 Tupel
//--------
//--------
//--------
//--------
////////////////
#define _macro_split_args_3s_part3_0(...) "ERROR. To few variadic arguments in overloaded macro: SPLIT_ARGS_3s"ERROR"Macro-Idx: 0"
#define _macro_split_args_3s_part3_1(...) _macro_split_args_3s_part3_0(__VA_ARGS__)"Macro-Idx: 1"
#define _macro_split_args_3s_part3_2(...) _macro_split_args_3s_part3_0(__VA_ARGS__)"Macro-Idx: 2"
#define _macro_split_args_3s_part3_4(...) _macro_split_args_3s_part3_0(__VA_ARGS__)"Macro-Idx: 4"
#define _macro_split_args_3s_part3_5(...) _macro_split_args_3s_part3_0(__VA_ARGS__)"Macro-Idx: 5"
#define _macro_split_args_3s_part3_7(...) _macro_split_args_3s_part3_0(__VA_ARGS__)"Macro-Idx: 7"
#define _macro_split_args_3s_part3_8(...) _macro_split_args_3s_part3_0(__VA_ARGS__)"Macro-Idx: 8"
#define _macro_split_args_3s_part3_10(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_11(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_13(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_14(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_16(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_17(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_19(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_20(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_22(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_23(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_25(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_26(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_28(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_29(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_31(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_32(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_34(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_35(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_37(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_38(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_40(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_41(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_43(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_44(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_46(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_47(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_49(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_50(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_52(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_53(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_55(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_56(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_58(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_59(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_61(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_62(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
#define _macro_split_args_3s_part3_64(...) _macro_split_args_3s_part3_0(__VA_ARGS__)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define _macro_split_args_3s_part3_3(A, B, C, ...) \
	C
#define _macro_split_args_3s_part3_6(A1, A2, A3, A4, A5, A6, ...) \
	A5, A6
#define _macro_split_args_3s_part3_9(A1, A2, A3, A4, A5, A6, A7, A8, A9, ...) \
	A7, A8, A9
#define _macro_split_args_3s_part3_12(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, ...) \
	A9, A10, A11, A12
#define _macro_split_args_3s_part3_15(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, ...) \
	A11, A12, A13, A14, A15
#define _macro_split_args_3s_part3_18(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, ...) \
	A13, A14, A15, A16, A17, A18
#define _macro_split_args_3s_part3_21(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, ...) \
	A15, A16, A17, A18, A19, A20, A21
#define _macro_split_args_3s_part3_24(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, ...) \
	A17, A18, A19, A20, A21, A22, A23, A24
#define _macro_split_args_3s_part3_27(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, ...) \
	A19, A20, A21, A22, A23, A24, A25, A26, A27
#define _macro_split_args_3s_part3_30(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, ...) \
	A21, A22, A23, A24, A25, A26, A27, A28, A29, A30
#define _macro_split_args_3s_part3_33(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, ...) \
	A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33
#define _macro_split_args_3s_part3_36(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, ...) \
	A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36
#define _macro_split_args_3s_part3_39(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, ...) \
	A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39
#define _macro_split_args_3s_part3_42(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, ...) \
	A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42
#define _macro_split_args_3s_part3_45(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, ...) \
	A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45
#define _macro_split_args_3s_part3_48(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, ...) \
	A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48
#define _macro_split_args_3s_part3_51(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, ...) \
	A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51
#define _macro_split_args_3s_part3_54(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, ...) \
	A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54
#define _macro_split_args_3s_part3_57(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, ...) \
	A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57
#define _macro_split_args_3s_part3_60(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, A58, A59, A60, ...) \
	A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, A58, A59, A60
#define _macro_split_args_3s_part3_63(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29, A30, A31, A32, A33, A34, A35, A36, A37, A38, A39, A40, A41, A42, A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, A58, A59, A60, A61, A62, A63, ...) \
	A43, A44, A45, A46, A47, A48, A49, A50, A51, A52, A53, A54, A55, A56, A57, A58, A59, A60, A61, A62, A63
////////////////
//
#define _GET_NTH_ARG_SPLIT_ARGS_3s(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, N, ...) N
//
#define SPLIT_ARGS_3s_1(...) EXPAND(SPLIT_ARGS_3s_1_EVALUATED(__VA_ARGS__))
#define SPLIT_ARGS_3s_2(...) EXPAND(SPLIT_ARGS_3s_2_EVALUATED(__VA_ARGS__))
#define SPLIT_ARGS_3s_3(...) EXPAND(SPLIT_ARGS_3s_3_EVALUATED(__VA_ARGS__))
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define SPLIT_ARGS_3s_1_EVALUATED(...) \
		_GET_NTH_ARG_SPLIT_ARGS_3s("ignored", ##__VA_ARGS__, \
		_macro_split_args_3s_part3_63, _macro_split_args_3s_part3_62, _macro_split_args_3s_part3_61, _macro_split_args_3s_part3_60, _macro_split_args_3s_part3_59, _macro_split_args_3s_part3_58, _macro_split_args_3s_part3_57, _macro_split_args_3s_part3_56, _macro_split_args_3s_part3_55, _macro_split_args_3s_part3_54, _macro_split_args_3s_part3_53, _macro_split_args_3s_part3_52, _macro_split_args_3s_part3_51, _macro_split_args_3s_part3_50, _macro_split_args_3s_part3_49, _macro_split_args_3s_part3_48, _macro_split_args_3s_part3_47, _macro_split_args_3s_part3_46, _macro_split_args_3s_part3_45, _macro_split_args_3s_part3_44, _macro_split_args_3s_part3_43, _macro_split_args_3s_part3_42, _macro_split_args_3s_part3_41, _macro_split_args_3s_part3_40, _macro_split_args_3s_part3_39, _macro_split_args_3s_part3_38, _macro_split_args_3s_part3_37, _macro_split_args_3s_part3_36, _macro_split_args_3s_part3_35, _macro_split_args_3s_part3_34, _macro_split_args_3s_part3_33, _macro_split_args_3s_part3_32, _macro_split_args_3s_part3_31, _macro_split_args_3s_part3_30, _macro_split_args_3s_part3_29, _macro_split_args_3s_part3_28, _macro_split_args_3s_part3_27, _macro_split_args_3s_part3_26, _macro_split_args_3s_part3_25, _macro_split_args_3s_part3_24, _macro_split_args_3s_part3_23, _macro_split_args_3s_part3_22, _macro_split_args_3s_part3_21, _macro_split_args_3s_part3_20, _macro_split_args_3s_part3_19, _macro_split_args_3s_part3_18, _macro_split_args_3s_part3_17, _macro_split_args_3s_part3_16, _macro_split_args_3s_part3_15, _macro_split_args_3s_part3_14, _macro_split_args_3s_part3_13, _macro_split_args_3s_part3_12, _macro_split_args_3s_part3_11, _macro_split_args_3s_part3_10, _macro_split_args_3s_part3_9, _macro_split_args_3s_part3_8, _macro_split_args_3s_part3_7, _macro_split_args_3s_part3_6, _macro_split_args_3s_part3_5, _macro_split_args_3s_part3_4, _macro_split_args_3s_part3_3, _macro_split_args_3s_part3_2, _macro_split_args_3s_part3_1, _macro_split_args_3s_part3_0)\
		EXPAND((RSHIFT_ONE_3rd(__VA_ARGS__) RSHIFT_ONE_3rd(__VA_ARGS__) __VA_ARGS__))
#define SPLIT_ARGS_3s_2_EVALUATED(...) \
		_GET_NTH_ARG_SPLIT_ARGS_3s("ignored", ##__VA_ARGS__, \
		_macro_split_args_3s_part3_63, _macro_split_args_3s_part3_62, _macro_split_args_3s_part3_61, _macro_split_args_3s_part3_60, _macro_split_args_3s_part3_59, _macro_split_args_3s_part3_58, _macro_split_args_3s_part3_57, _macro_split_args_3s_part3_56, _macro_split_args_3s_part3_55, _macro_split_args_3s_part3_54, _macro_split_args_3s_part3_53, _macro_split_args_3s_part3_52, _macro_split_args_3s_part3_51, _macro_split_args_3s_part3_50, _macro_split_args_3s_part3_49, _macro_split_args_3s_part3_48, _macro_split_args_3s_part3_47, _macro_split_args_3s_part3_46, _macro_split_args_3s_part3_45, _macro_split_args_3s_part3_44, _macro_split_args_3s_part3_43, _macro_split_args_3s_part3_42, _macro_split_args_3s_part3_41, _macro_split_args_3s_part3_40, _macro_split_args_3s_part3_39, _macro_split_args_3s_part3_38, _macro_split_args_3s_part3_37, _macro_split_args_3s_part3_36, _macro_split_args_3s_part3_35, _macro_split_args_3s_part3_34, _macro_split_args_3s_part3_33, _macro_split_args_3s_part3_32, _macro_split_args_3s_part3_31, _macro_split_args_3s_part3_30, _macro_split_args_3s_part3_29, _macro_split_args_3s_part3_28, _macro_split_args_3s_part3_27, _macro_split_args_3s_part3_26, _macro_split_args_3s_part3_25, _macro_split_args_3s_part3_24, _macro_split_args_3s_part3_23, _macro_split_args_3s_part3_22, _macro_split_args_3s_part3_21, _macro_split_args_3s_part3_20, _macro_split_args_3s_part3_19, _macro_split_args_3s_part3_18, _macro_split_args_3s_part3_17, _macro_split_args_3s_part3_16, _macro_split_args_3s_part3_15, _macro_split_args_3s_part3_14, _macro_split_args_3s_part3_13, _macro_split_args_3s_part3_12, _macro_split_args_3s_part3_11, _macro_split_args_3s_part3_10, _macro_split_args_3s_part3_9, _macro_split_args_3s_part3_8, _macro_split_args_3s_part3_7, _macro_split_args_3s_part3_6, _macro_split_args_3s_part3_5, _macro_split_args_3s_part3_4, _macro_split_args_3s_part3_3, _macro_split_args_3s_part3_2, _macro_split_args_3s_part3_1, _macro_split_args_3s_part3_0)\
		EXPAND((RSHIFT_ONE_3rd(__VA_ARGS__) __VA_ARGS__))
#define SPLIT_ARGS_3s_3_EVALUATED(...) \
		_GET_NTH_ARG_SPLIT_ARGS_3s("ignored", ##__VA_ARGS__, \
		_macro_split_args_3s_part3_63, _macro_split_args_3s_part3_62, _macro_split_args_3s_part3_61, _macro_split_args_3s_part3_60, _macro_split_args_3s_part3_59, _macro_split_args_3s_part3_58, _macro_split_args_3s_part3_57, _macro_split_args_3s_part3_56, _macro_split_args_3s_part3_55, _macro_split_args_3s_part3_54, _macro_split_args_3s_part3_53, _macro_split_args_3s_part3_52, _macro_split_args_3s_part3_51, _macro_split_args_3s_part3_50, _macro_split_args_3s_part3_49, _macro_split_args_3s_part3_48, _macro_split_args_3s_part3_47, _macro_split_args_3s_part3_46, _macro_split_args_3s_part3_45, _macro_split_args_3s_part3_44, _macro_split_args_3s_part3_43, _macro_split_args_3s_part3_42, _macro_split_args_3s_part3_41, _macro_split_args_3s_part3_40, _macro_split_args_3s_part3_39, _macro_split_args_3s_part3_38, _macro_split_args_3s_part3_37, _macro_split_args_3s_part3_36, _macro_split_args_3s_part3_35, _macro_split_args_3s_part3_34, _macro_split_args_3s_part3_33, _macro_split_args_3s_part3_32, _macro_split_args_3s_part3_31, _macro_split_args_3s_part3_30, _macro_split_args_3s_part3_29, _macro_split_args_3s_part3_28, _macro_split_args_3s_part3_27, _macro_split_args_3s_part3_26, _macro_split_args_3s_part3_25, _macro_split_args_3s_part3_24, _macro_split_args_3s_part3_23, _macro_split_args_3s_part3_22, _macro_split_args_3s_part3_21, _macro_split_args_3s_part3_20, _macro_split_args_3s_part3_19, _macro_split_args_3s_part3_18, _macro_split_args_3s_part3_17, _macro_split_args_3s_part3_16, _macro_split_args_3s_part3_15, _macro_split_args_3s_part3_14, _macro_split_args_3s_part3_13, _macro_split_args_3s_part3_12, _macro_split_args_3s_part3_11, _macro_split_args_3s_part3_10, _macro_split_args_3s_part3_9, _macro_split_args_3s_part3_8, _macro_split_args_3s_part3_7, _macro_split_args_3s_part3_6, _macro_split_args_3s_part3_5, _macro_split_args_3s_part3_4, _macro_split_args_3s_part3_3, _macro_split_args_3s_part3_2, _macro_split_args_3s_part3_1, _macro_split_args_3s_part3_0)\
		(__VA_ARGS__)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// This is broken:
// Maybe i have to rework the SWITCH Macro, but i doubt, that it will be possible, what i would like to achieve.
/*
//#define SPLIT_ARGS_3s(...) SPLIT_ARGS_3s_EVALUATED(__VA_ARGS__)
//#define SPLIT_ARGS_3s_EVALUATED(PART_NR,...) \
//	SWITCH( \
//			EQUAL(PART_NR,1), \
//				(SPLIT_ARGS_3s_1_EVALUATED(__VA_ARGS__)) \
//				, \
//			EQUAL(PART_NR,2), \
//				(SPLIT_ARGS_3s_2_EVALUATED(__VA_ARGS__)) \
//				, \
//			EQUAL(PART_NR,3), \
//				(SPLIT_ARGS_3s_3_EVALUATED(__VA_ARGS__)) \
//				, \
//			ERROR"ERROR in SPLIT_ARGS"; \
//		)
*/
////////////////
//--------
//-- Right Shift one third
//--------
////////////////
#define _macro_rshift_one_3rd_0(...) "ERROR. To few variadic arguments in overloaded macro: RSHIFT_ONE_3rd"ERROR
#define _macro_rshift_one_3rd_1(...) _macro_rshift_one_3rd_0(__VA_ARGS__)"Macro IDx: 1"
#define _macro_rshift_one_3rd_2(...) _macro_rshift_one_3rd_0(__VA_ARGS__)"Macro IDx: 2"
#define _macro_rshift_one_3rd_4(...) _macro_rshift_one_3rd_0(__VA_ARGS__)"Macro IDx: 4"
#define _macro_rshift_one_3rd_5(...) _macro_rshift_one_3rd_0(__VA_ARGS__)"Macro IDx: 5"
#define _macro_rshift_one_3rd_7(...) _macro_rshift_one_3rd_0(__VA_ARGS__)"Macro IDx: 7"
#define _macro_rshift_one_3rd_8(...) _macro_rshift_one_3rd_0(__VA_ARGS__)"Macro IDx: 8"
#define _macro_rshift_one_3rd_10(...) _macro_rshift_one_3rd_0(__VA_ARGS__)"Macro IDx: 10"
#define _macro_rshift_one_3rd_11(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_13(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_14(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_16(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_17(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_19(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_20(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_22(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_23(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_25(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_26(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_28(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_29(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_31(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_32(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_34(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_35(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_37(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_38(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_40(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_41(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_43(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_44(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_46(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_47(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_49(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_50(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_52(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_53(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_55(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_56(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_58(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_59(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_61(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_62(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_64(...) _macro_rshift_one_3rd_0(__VA_ARGS__)
#define _macro_rshift_one_3rd_3(...) _,
#define _macro_rshift_one_3rd_6(...) _, _,
#define _macro_rshift_one_3rd_9(...) _, _, _,
#define _macro_rshift_one_3rd_12(...) _, _, _, _,
#define _macro_rshift_one_3rd_15(...) _, _, _, _, _,
#define _macro_rshift_one_3rd_18(...) _, _, _, _, _, _,
#define _macro_rshift_one_3rd_21(...) _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_24(...) _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_27(...) _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_30(...) _, _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_33(...) _, _, _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_36(...) _, _, _, _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_39(...) _, _, _, _, _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_42(...) _, _, _, _, _, _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_45(...) _, _, _, _, _, _, _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_48(...) _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_51(...) _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_54(...) _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_57(...) _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_60(...) _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _,
#define _macro_rshift_one_3rd_63(...) _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _,
////////////////
//
#define _GET_NTH_ARG_RIGHT_SHIFT_ONE_3rd(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, N, ...) N
//
#define RSHIFT_ONE_3rd(...) RSHIFT_ONE_3rd_EVALUATED(__VA_ARGS__)
#define RSHIFT_ONE_3rd_EVALUATED(...) \
    _GET_NTH_ARG_RIGHT_SHIFT_ONE_3rd("ignored", ##__VA_ARGS__, \
    _macro_rshift_one_3rd_63, _macro_rshift_one_3rd_62, _macro_rshift_one_3rd_61, _macro_rshift_one_3rd_60, _macro_rshift_one_3rd_59, _macro_rshift_one_3rd_58, _macro_rshift_one_3rd_57, _macro_rshift_one_3rd_56, _macro_rshift_one_3rd_55, _macro_rshift_one_3rd_54, _macro_rshift_one_3rd_53, _macro_rshift_one_3rd_52, _macro_rshift_one_3rd_51, _macro_rshift_one_3rd_50, _macro_rshift_one_3rd_49, _macro_rshift_one_3rd_48, _macro_rshift_one_3rd_47, _macro_rshift_one_3rd_46, _macro_rshift_one_3rd_45, _macro_rshift_one_3rd_44, _macro_rshift_one_3rd_43, _macro_rshift_one_3rd_42, _macro_rshift_one_3rd_41, _macro_rshift_one_3rd_40, _macro_rshift_one_3rd_39, _macro_rshift_one_3rd_38, _macro_rshift_one_3rd_37, _macro_rshift_one_3rd_36, _macro_rshift_one_3rd_35, _macro_rshift_one_3rd_34, _macro_rshift_one_3rd_33, _macro_rshift_one_3rd_32, _macro_rshift_one_3rd_31, _macro_rshift_one_3rd_30, _macro_rshift_one_3rd_29, _macro_rshift_one_3rd_28, _macro_rshift_one_3rd_27, _macro_rshift_one_3rd_26, _macro_rshift_one_3rd_25, _macro_rshift_one_3rd_24, _macro_rshift_one_3rd_23, _macro_rshift_one_3rd_22, _macro_rshift_one_3rd_21, _macro_rshift_one_3rd_20, _macro_rshift_one_3rd_19, _macro_rshift_one_3rd_18, _macro_rshift_one_3rd_17, _macro_rshift_one_3rd_16, _macro_rshift_one_3rd_15, _macro_rshift_one_3rd_14, _macro_rshift_one_3rd_13, _macro_rshift_one_3rd_12, _macro_rshift_one_3rd_11, _macro_rshift_one_3rd_10, _macro_rshift_one_3rd_9, _macro_rshift_one_3rd_8, _macro_rshift_one_3rd_7, _macro_rshift_one_3rd_6, _macro_rshift_one_3rd_5, _macro_rshift_one_3rd_4, _macro_rshift_one_3rd_3, _macro_rshift_one_3rd_2, _macro_rshift_one_3rd_1, _macro_rshift_one_3rd_0)(__VA_ARGS__)
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////











/*////////////////////
 * A Macro for use a list of args, like in
 * If-Then-Else Ladder, i.e. a switch-instruction
 */////////////////////
/*////////////////////
 * Usage:
 * - Pass the "switch_condition", "instructions" after each other as a list, with a succeeding "default"
 * 		- default: Instructions, that get executed, if no preceding condition got matched. (In other words: The last "else" in an If-Then-Else-Ladder)
 * - SWITCH(condition1, instructions1, condition2, instructions2, ... n times ..., defaultInstructions)
 */////////////////////
// Similarly to the CALL_MACRO_X_FOR_EACH, but with a recursive Call, instead of a cascaded.
#define _macro_switch_0(_macroCall, ...)
#define _macro_switch_1(_macroCall, x) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_2(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_3(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, false_inst)
#define _macro_switch_4(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_5(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_3(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_6(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_7(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_5(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_8(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_9(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_7(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_10(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_11(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_9(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_12(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_13(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_11(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_14(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_15(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_13(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_16(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_17(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_15(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_18(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_19(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_17(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_20(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_21(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_19(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_22(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_23(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_21(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_24(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_25(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_23(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_26(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_27(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_25(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_28(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_29(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_27(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_30(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_31(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_29(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_32(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_33(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_31(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_34(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_35(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_33(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_36(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_37(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_35(_macroCall, false_inst, __VA_ARGS__))
#define _macro_switch_38(_macroCall, x, ...) "ERROR. To few variadic arguments in overloaded macro: SWITCH"ERROR
#define _macro_switch_39(_macroCall, cond, true_inst, false_inst, ...) _macroCall(cond)(true_inst, _macro_switch_37(_macroCall, false_inst, __VA_ARGS__))
// the "false_inst" doesn't have to be present. Would also work without it. But i wrote it as well to make things clearer.
////////////////////
//The length of the defined _GET_NTH_ARG and the used inside the SWITCH_EVALUATED has to be the same
// So here he gets an own one to secure that.
#define _GET_NTH_ARG_SWITCH(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,N,...) N
////////////////////
//The actual Macro
// Supplies a Switch-Instruction on the Preprocessor Layer. Supports the number of args like the highest number inside _GET_NTH_ARG_SWITCH -1.
// You see, how you could expand it ;oP (Up to the Max of 63, whats the limit of the Preprocessor for arguments.
//   To make it work both with directly passed many arguments and also with
//   predefined lists we need an additional Expansion-Step.
//   Therefore the two chained Macros
#define SWITCH(...) SWITCH_EVALUATED(__VA_ARGS__)
#define SWITCH_EVALUATED(...) \
    _GET_NTH_ARG_SWITCH("ignored", ##__VA_ARGS__, \
    _macro_switch_39, _macro_switch_38, _macro_switch_37, _macro_switch_36, _macro_switch_35, _macro_switch_34, _macro_switch_33, _macro_switch_32, _macro_switch_31, _macro_switch_30, _macro_switch_29, _macro_switch_28, _macro_switch_27, _macro_switch_26, _macro_switch_25, _macro_switch_24, _macro_switch_23, _macro_switch_22, _macro_switch_21, _macro_switch_20, _macro_switch_19, _macro_switch_18, _macro_switch_17, _macro_switch_16, _macro_switch_15, _macro_switch_14, _macro_switch_13, _macro_switch_12, _macro_switch_11, _macro_switch_10, _macro_switch_9, _macro_switch_8, _macro_switch_7, _macro_switch_6, _macro_switch_5, _macro_switch_4, _macro_switch_3, _macro_switch_2, _macro_switch_1, _macro_switch_0)(IF, ##__VA_ARGS__)
//////////////////////
////////////////////
/*
// Simple Example (So you can see, that you can format it nicely ;o) )
//		SWITCH( \
//			EQUAL(precision,nano), \
//				getRealTime_nanoseconds(variable); \
//				, \
//			EQUAL(precision,micro), \
//				getRealTime_microseconds(variable); \
//				, \
//			EQUAL(precision,timespec), \
//				getRealTime_nanoseconds(variable); \
//				, \
//			EQUAL(precision,timeval), \
//				getRealTime_microseconds(variable); \
//				, \
//			getRealTime(); \
//		)
*/
// !!! IMPORTANT NOTE: !!!
// You need a
//     #define COMPARE_value(x) x
// for every EQUAL(...) Operation you want to perform. And so you need ones for the SWITCH(...)
// E.g. for "EQUAL(variable, file)" you need "#define COMPARE_file(x) x"
//     With this "variable" would be an argument, which you pass to a macro
//     If you now hand over "file" as the variable (hand it clean, i.e. no parenthesis, linguistic sign or something else, just file)
//     The EQUAL "evaluates" to "TRUE".
//     Remember, we talk about PreProcessor here, so it isn't really a variable, it's just a #defined Label or Plain-Text
// You have to be careful with the Expansion-Steps taken, if you want to pass #defines
// Also have a Look further above at the Definition of EQUAL itself for some more Information
////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////








//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Some further, fine, helpful Macros  --------------------------------------------------------//
//----    OK, to be honest... I organized all this not completely pursuing one holistic track...  --//
//----    Soooo... be sure to also check the "auxiliary.h" of "DenKr_essentials"...  ---------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
////////////////////////////////
//////// Helps with the use of structs
////////////////////////////////
#define member_size(type, member) sizeof(((type *)0)->member)
////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////











//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Some basic little 'Helper-Values'  ---------------------------------------------------------//
//----  (Don't really care about them, expect maybe extending them)  -------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
////////////////////////////////
//////// Supporting Values for the INC() & DEC() Macro
////////////////////////////////
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INC_9 10
#define INC_10 11
#define INC_11 12
#define INC_12 13
#define INC_13 14
#define INC_14 15
#define INC_15 16
#define INC_16 17
#define INC_17 18
#define INC_18 19
#define INC_19 20
#define INC_20 21
#define INC_21 22
#define INC_22 23
#define INC_23 24
#define INC_24 25
#define INC_25 26
#define INC_26 27
#define INC_27 28
#define INC_28 29
#define INC_29 30
#define INC_30 31
#define INC_31 32
#define INC_32 33
#define INC_33 34
#define INC_34 35
#define INC_35 36
#define INC_36 37
#define INC_37 38
#define INC_38 39
#define INC_39 40
#define INC_40 41
#define INC_41 42
#define INC_42 43
#define INC_43 44
#define INC_44 45
#define INC_45 46
#define INC_46 47
#define INC_47 48
#define INC_48 49
#define INC_49 50
#define INC_50 51
#define INC_51 52
#define INC_52 53
#define INC_53 54
#define INC_54 55
#define INC_55 56
#define INC_56 57
#define INC_57 58
#define INC_58 59
#define INC_59 60
#define INC_60 61
#define INC_61 62
#define INC_62 63
#define INC_63 64
#define INC_64 65
#define INC_65 66
#define INC_66 67
#define INC_67 68
#define INC_68 69
#define INC_69 70
#define INC_70 71
#define INC_71 72
#define INC_72 73
#define INC_73 74
#define INC_74 75
#define INC_75 76
#define INC_76 77
#define INC_77 78
#define INC_78 79
#define INC_79 80
#define INC_80 81
#define INC_81 82
#define INC_82 83
#define INC_83 84
#define INC_84 85
#define INC_85 86
#define INC_86 87
#define INC_87 88
#define INC_88 89
#define INC_89 90
#define INC_90 91
#define INC_91 92
#define INC_92 93
#define INC_93 94
#define INC_94 95
#define INC_95 96
#define INC_96 97
#define INC_97 98
#define INC_98 99
#define INC_99 100
#define INC_100 101
#define INC_101 102
#define INC_102 103
#define INC_103 104
#define INC_104 105
#define INC_105 106
#define INC_106 107
#define INC_107 108
#define INC_108 109
#define INC_109 110
#define INC_110 111
#define INC_111 112
#define INC_112 113
#define INC_113 114
#define INC_114 115
#define INC_115 116
#define INC_116 117
#define INC_117 118
#define INC_118 119
#define INC_119 120
#define INC_120 121
#define INC_121 122
#define INC_122 123
#define INC_123 124
#define INC_124 125
#define INC_125 126
#define INC_126 127
#define INC_127 128
#define INC_128 129
#define INC_129 130
#define INC_130 131
#define INC_131 132
#define INC_132 133
#define INC_133 134
#define INC_134 135
#define INC_135 136
#define INC_136 137
#define INC_137 138
#define INC_138 139
#define INC_139 140
#define INC_140 141
#define INC_141 142
#define INC_142 143
#define INC_143 144
#define INC_144 145
#define INC_145 146
#define INC_146 147
#define INC_147 148
#define INC_148 149
#define INC_149 150
#define INC_150 151
#define INC_151 152
#define INC_152 153
#define INC_153 154
#define INC_154 155
#define INC_155 156
#define INC_156 157
#define INC_157 158
#define INC_158 159
#define INC_159 160
#define INC_160 161
#define INC_161 162
#define INC_162 163
#define INC_163 164
#define INC_164 165
#define INC_165 166
#define INC_166 167
#define INC_167 168
#define INC_168 169
#define INC_169 170
#define INC_170 171
#define INC_171 172
#define INC_172 173
#define INC_173 174
#define INC_174 175
#define INC_175 176
#define INC_176 177
#define INC_177 178
#define INC_178 179
#define INC_179 180
#define INC_180 181
#define INC_181 182
#define INC_182 183
#define INC_183 184
#define INC_184 185
#define INC_185 186
#define INC_186 187
#define INC_187 188
#define INC_188 189
#define INC_189 190
#define INC_190 191
#define INC_191 192
#define INC_192 193
#define INC_193 194
#define INC_194 195
#define INC_195 196
#define INC_196 197
#define INC_197 198
#define INC_198 199
#define INC_199 200
#define INC_200 201
#define INC_201 202
#define INC_202 203
#define INC_203 204
#define INC_204 205
#define INC_205 206
#define INC_206 207
#define INC_207 208
#define INC_208 209
#define INC_209 210
#define INC_210 211
#define INC_211 212
#define INC_212 213
#define INC_213 214
#define INC_214 215
#define INC_215 216
#define INC_216 217
#define INC_217 218
#define INC_218 219
#define INC_219 220
#define INC_220 221
#define INC_221 222
#define INC_222 223
#define INC_223 224
#define INC_224 225
#define INC_225 226
#define INC_226 227
#define INC_227 228
#define INC_228 229
#define INC_229 230
#define INC_230 231
#define INC_231 232
#define INC_232 233
#define INC_233 234
#define INC_234 235
#define INC_235 236
#define INC_236 237
#define INC_237 238
#define INC_238 239
#define INC_239 240
#define INC_240 241
#define INC_241 242
#define INC_242 243
#define INC_243 244
#define INC_244 245
#define INC_245 246
#define INC_246 247
#define INC_247 248
#define INC_248 249
#define INC_249 250
#define INC_250 251
#define INC_251 252
#define INC_252 253
#define INC_253 254
#define INC_254 255
#define INC_255 256
#define INC_256 257
#define INC_257 258
#define INC_258 259
#define INC_259 260
#define INC_260 261
#define INC_261 262
#define INC_262 263
#define INC_263 264
#define INC_264 265
#define INC_265 266
#define INC_266 267
#define INC_267 268
#define INC_268 269
#define INC_269 270
#define INC_270 271
#define INC_271 272
#define INC_272 273
#define INC_273 274
#define INC_274 275
#define INC_275 276
#define INC_276 277
#define INC_277 278
#define INC_278 279
#define INC_279 280
#define INC_280 281
#define INC_281 282
#define INC_282 283
#define INC_283 284
#define INC_284 285
#define INC_285 286
#define INC_286 287
#define INC_287 288
#define INC_288 289
#define INC_289 290
#define INC_290 291
#define INC_291 292
#define INC_292 293
#define INC_293 294
#define INC_294 295
#define INC_295 296
#define INC_296 297
#define INC_297 298
#define INC_298 299
#define INC_299 300
//----------------------------------------------------------------------------------------------------
#define DEC_0 -1
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8
#define DEC_10 9
#define DEC_11 10
#define DEC_12 11
#define DEC_13 12
#define DEC_14 13
#define DEC_15 14
#define DEC_16 15
#define DEC_17 16
#define DEC_18 17
#define DEC_19 18
#define DEC_20 19
#define DEC_21 20
#define DEC_22 21
#define DEC_23 22
#define DEC_24 23
#define DEC_25 24
#define DEC_26 25
#define DEC_27 26
#define DEC_28 27
#define DEC_29 28
#define DEC_30 29
#define DEC_31 30
#define DEC_32 31
#define DEC_33 32
#define DEC_34 33
#define DEC_35 34
#define DEC_36 35
#define DEC_37 36
#define DEC_38 37
#define DEC_39 38
#define DEC_40 39
#define DEC_41 40
#define DEC_42 41
#define DEC_43 42
#define DEC_44 43
#define DEC_45 44
#define DEC_46 45
#define DEC_47 46
#define DEC_48 47
#define DEC_49 48
#define DEC_50 49
#define DEC_51 50
#define DEC_52 51
#define DEC_53 52
#define DEC_54 53
#define DEC_55 54
#define DEC_56 55
#define DEC_57 56
#define DEC_58 57
#define DEC_59 58
#define DEC_60 59
#define DEC_61 60
#define DEC_62 61
#define DEC_63 62
#define DEC_64 63
#define DEC_65 64
#define DEC_66 65
#define DEC_67 66
#define DEC_68 67
#define DEC_69 68
#define DEC_70 69
#define DEC_71 70
#define DEC_72 71
#define DEC_73 72
#define DEC_74 73
#define DEC_75 74
#define DEC_76 75
#define DEC_77 76
#define DEC_78 77
#define DEC_79 78
#define DEC_80 79
#define DEC_81 80
#define DEC_82 81
#define DEC_83 82
#define DEC_84 83
#define DEC_85 84
#define DEC_86 85
#define DEC_87 86
#define DEC_88 87
#define DEC_89 88
#define DEC_90 89
#define DEC_91 90
#define DEC_92 91
#define DEC_93 92
#define DEC_94 93
#define DEC_95 94
#define DEC_96 95
#define DEC_97 96
#define DEC_98 97
#define DEC_99 98
#define DEC_100 99
#define DEC_101 100
#define DEC_102 101
#define DEC_103 102
#define DEC_104 103
#define DEC_105 104
#define DEC_106 105
#define DEC_107 106
#define DEC_108 107
#define DEC_109 108
#define DEC_110 109
#define DEC_111 110
#define DEC_112 111
#define DEC_113 112
#define DEC_114 113
#define DEC_115 114
#define DEC_116 115
#define DEC_117 116
#define DEC_118 117
#define DEC_119 118
#define DEC_120 119
#define DEC_121 120
#define DEC_122 121
#define DEC_123 122
#define DEC_124 123
#define DEC_125 124
#define DEC_126 125
#define DEC_127 126
#define DEC_128 127
#define DEC_129 128
#define DEC_130 129
#define DEC_131 130
#define DEC_132 131
#define DEC_133 132
#define DEC_134 133
#define DEC_135 134
#define DEC_136 135
#define DEC_137 136
#define DEC_138 137
#define DEC_139 138
#define DEC_140 139
#define DEC_141 140
#define DEC_142 141
#define DEC_143 142
#define DEC_144 143
#define DEC_145 144
#define DEC_146 145
#define DEC_147 146
#define DEC_148 147
#define DEC_149 148
#define DEC_150 149
#define DEC_151 150
#define DEC_152 151
#define DEC_153 152
#define DEC_154 153
#define DEC_155 154
#define DEC_156 155
#define DEC_157 156
#define DEC_158 157
#define DEC_159 158
#define DEC_160 159
#define DEC_161 160
#define DEC_162 161
#define DEC_163 162
#define DEC_164 163
#define DEC_165 164
#define DEC_166 165
#define DEC_167 166
#define DEC_168 167
#define DEC_169 168
#define DEC_170 169
#define DEC_171 170
#define DEC_172 171
#define DEC_173 172
#define DEC_174 173
#define DEC_175 174
#define DEC_176 175
#define DEC_177 176
#define DEC_178 177
#define DEC_179 178
#define DEC_180 179
#define DEC_181 180
#define DEC_182 181
#define DEC_183 182
#define DEC_184 183
#define DEC_185 184
#define DEC_186 185
#define DEC_187 186
#define DEC_188 187
#define DEC_189 188
#define DEC_190 189
#define DEC_191 190
#define DEC_192 191
#define DEC_193 192
#define DEC_194 193
#define DEC_195 194
#define DEC_196 195
#define DEC_197 196
#define DEC_198 197
#define DEC_199 198
#define DEC_200 199
#define DEC_201 200
#define DEC_202 201
#define DEC_203 202
#define DEC_204 203
#define DEC_205 204
#define DEC_206 205
#define DEC_207 206
#define DEC_208 207
#define DEC_209 208
#define DEC_210 209
#define DEC_211 210
#define DEC_212 211
#define DEC_213 212
#define DEC_214 213
#define DEC_215 214
#define DEC_216 215
#define DEC_217 216
#define DEC_218 217
#define DEC_219 218
#define DEC_220 219
#define DEC_221 220
#define DEC_222 221
#define DEC_223 222
#define DEC_224 223
#define DEC_225 224
#define DEC_226 225
#define DEC_227 226
#define DEC_228 227
#define DEC_229 228
#define DEC_230 229
#define DEC_231 230
#define DEC_232 231
#define DEC_233 232
#define DEC_234 233
#define DEC_235 234
#define DEC_236 235
#define DEC_237 236
#define DEC_238 237
#define DEC_239 238
#define DEC_240 239
#define DEC_241 240
#define DEC_242 241
#define DEC_243 242
#define DEC_244 243
#define DEC_245 244
#define DEC_246 245
#define DEC_247 246
#define DEC_248 247
#define DEC_249 248
#define DEC_250 249
#define DEC_251 250
#define DEC_252 251
#define DEC_253 252
#define DEC_254 253
#define DEC_255 254
#define DEC_256 255
#define DEC_257 256
#define DEC_258 257
#define DEC_259 258
#define DEC_260 259
#define DEC_261 260
#define DEC_262 261
#define DEC_263 262
#define DEC_264 263
#define DEC_265 264
#define DEC_266 265
#define DEC_267 266
#define DEC_268 267
#define DEC_269 268
#define DEC_270 269
#define DEC_271 270
#define DEC_272 271
#define DEC_273 272
#define DEC_274 273
#define DEC_275 274
#define DEC_276 275
#define DEC_277 276
#define DEC_278 277
#define DEC_279 278
#define DEC_280 279
#define DEC_281 280
#define DEC_282 281
#define DEC_283 282
#define DEC_284 283
#define DEC_285 284
#define DEC_286 285
#define DEC_287 286
#define DEC_288 287
#define DEC_289 288
#define DEC_290 289
#define DEC_291 290
#define DEC_292 291
#define DEC_293 292
#define DEC_294 293
#define DEC_295 294
#define DEC_296 295
#define DEC_297 296
#define DEC_298 297
#define DEC_299 298
#define DEC_300 299
////////////////////////////////
//////// Supporting Values for the EQUAL() Macro
////////////////////////////////
#define COMPARE_0(x) x
#define COMPARE_1(x) x
#define COMPARE_2(x) x
#define COMPARE_3(x) x
#define COMPARE_4(x) x
#define COMPARE_5(x) x
#define COMPARE_6(x) x
#define COMPARE_7(x) x
#define COMPARE_8(x) x
#define COMPARE_9(x) x
#define COMPARE_10(x) x
#define COMPARE_11(x) x
#define COMPARE_12(x) x
#define COMPARE_13(x) x
#define COMPARE_14(x) x
#define COMPARE_15(x) x
#define COMPARE_16(x) x
#define COMPARE_17(x) x
#define COMPARE_18(x) x
#define COMPARE_19(x) x
#define COMPARE_20(x) x
#define COMPARE_21(x) x
#define COMPARE_22(x) x
#define COMPARE_23(x) x
#define COMPARE_24(x) x
#define COMPARE_25(x) x
#define COMPARE_26(x) x
#define COMPARE_27(x) x
#define COMPARE_28(x) x
#define COMPARE_29(x) x
#define COMPARE_30(x) x
#define COMPARE_31(x) x
#define COMPARE_32(x) x
#define COMPARE_33(x) x
#define COMPARE_34(x) x
#define COMPARE_35(x) x
#define COMPARE_36(x) x
#define COMPARE_37(x) x
#define COMPARE_38(x) x
#define COMPARE_39(x) x
#define COMPARE_40(x) x
#define COMPARE_41(x) x
#define COMPARE_42(x) x
#define COMPARE_43(x) x
#define COMPARE_44(x) x
#define COMPARE_45(x) x
#define COMPARE_46(x) x
#define COMPARE_47(x) x
#define COMPARE_48(x) x
#define COMPARE_49(x) x
#define COMPARE_50(x) x
#define COMPARE_51(x) x
#define COMPARE_52(x) x
#define COMPARE_53(x) x
#define COMPARE_54(x) x
#define COMPARE_55(x) x
#define COMPARE_56(x) x
#define COMPARE_57(x) x
#define COMPARE_58(x) x
#define COMPARE_59(x) x
#define COMPARE_60(x) x
#define COMPARE_61(x) x
#define COMPARE_62(x) x
#define COMPARE_63(x) x
#define COMPARE_64(x) x
#define COMPARE_65(x) x
#define COMPARE_66(x) x
#define COMPARE_67(x) x
#define COMPARE_68(x) x
#define COMPARE_69(x) x
#define COMPARE_70(x) x
#define COMPARE_71(x) x
#define COMPARE_72(x) x
#define COMPARE_73(x) x
#define COMPARE_74(x) x
#define COMPARE_75(x) x
#define COMPARE_76(x) x
#define COMPARE_77(x) x
#define COMPARE_78(x) x
#define COMPARE_79(x) x
#define COMPARE_80(x) x
#define COMPARE_81(x) x
#define COMPARE_82(x) x
#define COMPARE_83(x) x
#define COMPARE_84(x) x
#define COMPARE_85(x) x
#define COMPARE_86(x) x
#define COMPARE_87(x) x
#define COMPARE_88(x) x
#define COMPARE_89(x) x
#define COMPARE_90(x) x
#define COMPARE_91(x) x
#define COMPARE_92(x) x
#define COMPARE_93(x) x
#define COMPARE_94(x) x
#define COMPARE_95(x) x
#define COMPARE_96(x) x
#define COMPARE_97(x) x
#define COMPARE_98(x) x
#define COMPARE_99(x) x
#define COMPARE_100(x) x
#define COMPARE_101(x) x
#define COMPARE_102(x) x
#define COMPARE_103(x) x
#define COMPARE_104(x) x
#define COMPARE_105(x) x
#define COMPARE_106(x) x
#define COMPARE_107(x) x
#define COMPARE_108(x) x
#define COMPARE_109(x) x
#define COMPARE_110(x) x
#define COMPARE_111(x) x
#define COMPARE_112(x) x
#define COMPARE_113(x) x
#define COMPARE_114(x) x
#define COMPARE_115(x) x
#define COMPARE_116(x) x
#define COMPARE_117(x) x
#define COMPARE_118(x) x
#define COMPARE_119(x) x
#define COMPARE_120(x) x
#define COMPARE_121(x) x
#define COMPARE_122(x) x
#define COMPARE_123(x) x
#define COMPARE_124(x) x
#define COMPARE_125(x) x
#define COMPARE_126(x) x
#define COMPARE_127(x) x
#define COMPARE_128(x) x
#define COMPARE_129(x) x
#define COMPARE_130(x) x
#define COMPARE_131(x) x
#define COMPARE_132(x) x
#define COMPARE_133(x) x
#define COMPARE_134(x) x
#define COMPARE_135(x) x
#define COMPARE_136(x) x
#define COMPARE_137(x) x
#define COMPARE_138(x) x
#define COMPARE_139(x) x
#define COMPARE_140(x) x
#define COMPARE_141(x) x
#define COMPARE_142(x) x
#define COMPARE_143(x) x
#define COMPARE_144(x) x
#define COMPARE_145(x) x
#define COMPARE_146(x) x
#define COMPARE_147(x) x
#define COMPARE_148(x) x
#define COMPARE_149(x) x
#define COMPARE_150(x) x
#define COMPARE_151(x) x
#define COMPARE_152(x) x
#define COMPARE_153(x) x
#define COMPARE_154(x) x
#define COMPARE_155(x) x
#define COMPARE_156(x) x
#define COMPARE_157(x) x
#define COMPARE_158(x) x
#define COMPARE_159(x) x
#define COMPARE_160(x) x
#define COMPARE_161(x) x
#define COMPARE_162(x) x
#define COMPARE_163(x) x
#define COMPARE_164(x) x
#define COMPARE_165(x) x
#define COMPARE_166(x) x
#define COMPARE_167(x) x
#define COMPARE_168(x) x
#define COMPARE_169(x) x
#define COMPARE_170(x) x
#define COMPARE_171(x) x
#define COMPARE_172(x) x
#define COMPARE_173(x) x
#define COMPARE_174(x) x
#define COMPARE_175(x) x
#define COMPARE_176(x) x
#define COMPARE_177(x) x
#define COMPARE_178(x) x
#define COMPARE_179(x) x
#define COMPARE_180(x) x
#define COMPARE_181(x) x
#define COMPARE_182(x) x
#define COMPARE_183(x) x
#define COMPARE_184(x) x
#define COMPARE_185(x) x
#define COMPARE_186(x) x
#define COMPARE_187(x) x
#define COMPARE_188(x) x
#define COMPARE_189(x) x
#define COMPARE_190(x) x
#define COMPARE_191(x) x
#define COMPARE_192(x) x
#define COMPARE_193(x) x
#define COMPARE_194(x) x
#define COMPARE_195(x) x
#define COMPARE_196(x) x
#define COMPARE_197(x) x
#define COMPARE_198(x) x
#define COMPARE_199(x) x
#define COMPARE_200(x) x
#define COMPARE_201(x) x
#define COMPARE_202(x) x
#define COMPARE_203(x) x
#define COMPARE_204(x) x
#define COMPARE_205(x) x
#define COMPARE_206(x) x
#define COMPARE_207(x) x
#define COMPARE_208(x) x
#define COMPARE_209(x) x
#define COMPARE_210(x) x
#define COMPARE_211(x) x
#define COMPARE_212(x) x
#define COMPARE_213(x) x
#define COMPARE_214(x) x
#define COMPARE_215(x) x
#define COMPARE_216(x) x
#define COMPARE_217(x) x
#define COMPARE_218(x) x
#define COMPARE_219(x) x
#define COMPARE_220(x) x
#define COMPARE_221(x) x
#define COMPARE_222(x) x
#define COMPARE_223(x) x
#define COMPARE_224(x) x
#define COMPARE_225(x) x
#define COMPARE_226(x) x
#define COMPARE_227(x) x
#define COMPARE_228(x) x
#define COMPARE_229(x) x
#define COMPARE_230(x) x
#define COMPARE_231(x) x
#define COMPARE_232(x) x
#define COMPARE_233(x) x
#define COMPARE_234(x) x
#define COMPARE_235(x) x
#define COMPARE_236(x) x
#define COMPARE_237(x) x
#define COMPARE_238(x) x
#define COMPARE_239(x) x
#define COMPARE_240(x) x
#define COMPARE_241(x) x
#define COMPARE_242(x) x
#define COMPARE_243(x) x
#define COMPARE_244(x) x
#define COMPARE_245(x) x
#define COMPARE_246(x) x
#define COMPARE_247(x) x
#define COMPARE_248(x) x
#define COMPARE_249(x) x
#define COMPARE_250(x) x
#define COMPARE_251(x) x
#define COMPARE_252(x) x
#define COMPARE_253(x) x
#define COMPARE_254(x) x
#define COMPARE_255(x) x
#define COMPARE_256(x) x
#define COMPARE_257(x) x
#define COMPARE_258(x) x
#define COMPARE_259(x) x
#define COMPARE_260(x) x
#define COMPARE_261(x) x
#define COMPARE_262(x) x
#define COMPARE_263(x) x
#define COMPARE_264(x) x
#define COMPARE_265(x) x
#define COMPARE_266(x) x
#define COMPARE_267(x) x
#define COMPARE_268(x) x
#define COMPARE_269(x) x
#define COMPARE_270(x) x
#define COMPARE_271(x) x
#define COMPARE_272(x) x
#define COMPARE_273(x) x
#define COMPARE_274(x) x
#define COMPARE_275(x) x
#define COMPARE_276(x) x
#define COMPARE_277(x) x
#define COMPARE_278(x) x
#define COMPARE_279(x) x
#define COMPARE_280(x) x
#define COMPARE_281(x) x
#define COMPARE_282(x) x
#define COMPARE_283(x) x
#define COMPARE_284(x) x
#define COMPARE_285(x) x
#define COMPARE_286(x) x
#define COMPARE_287(x) x
#define COMPARE_288(x) x
#define COMPARE_289(x) x
#define COMPARE_290(x) x
#define COMPARE_291(x) x
#define COMPARE_292(x) x
#define COMPARE_293(x) x
#define COMPARE_294(x) x
#define COMPARE_295(x) x
#define COMPARE_296(x) x
#define COMPARE_297(x) x
#define COMPARE_298(x) x
#define COMPARE_299(x) x
#define COMPARE_300(x) x
#define COMPARE_301(x) x
#define COMPARE_302(x) x
#define COMPARE_303(x) x
#define COMPARE_304(x) x
#define COMPARE_305(x) x
#define COMPARE_306(x) x
#define COMPARE_307(x) x
#define COMPARE_308(x) x
#define COMPARE_309(x) x
#define COMPARE_310(x) x
#define COMPARE_311(x) x
#define COMPARE_312(x) x
#define COMPARE_313(x) x
#define COMPARE_314(x) x
#define COMPARE_315(x) x
#define COMPARE_316(x) x
#define COMPARE_317(x) x
#define COMPARE_318(x) x
#define COMPARE_319(x) x
#define COMPARE_320(x) x
#define COMPARE_321(x) x
#define COMPARE_322(x) x
#define COMPARE_323(x) x
#define COMPARE_324(x) x
#define COMPARE_325(x) x
#define COMPARE_326(x) x
#define COMPARE_327(x) x
#define COMPARE_328(x) x
#define COMPARE_329(x) x
#define COMPARE_330(x) x
#define COMPARE_331(x) x
#define COMPARE_332(x) x
#define COMPARE_333(x) x
#define COMPARE_334(x) x
#define COMPARE_335(x) x
#define COMPARE_336(x) x
#define COMPARE_337(x) x
#define COMPARE_338(x) x
#define COMPARE_339(x) x
#define COMPARE_340(x) x
#define COMPARE_341(x) x
#define COMPARE_342(x) x
#define COMPARE_343(x) x
#define COMPARE_344(x) x
#define COMPARE_345(x) x
#define COMPARE_346(x) x
#define COMPARE_347(x) x
#define COMPARE_348(x) x
#define COMPARE_349(x) x
#define COMPARE_350(x) x
#define COMPARE_351(x) x
#define COMPARE_352(x) x
#define COMPARE_353(x) x
#define COMPARE_354(x) x
#define COMPARE_355(x) x
#define COMPARE_356(x) x
#define COMPARE_357(x) x
#define COMPARE_358(x) x
#define COMPARE_359(x) x
#define COMPARE_360(x) x
#define COMPARE_361(x) x
#define COMPARE_362(x) x
#define COMPARE_363(x) x
#define COMPARE_364(x) x
#define COMPARE_365(x) x
#define COMPARE_366(x) x
#define COMPARE_367(x) x
#define COMPARE_368(x) x
#define COMPARE_369(x) x
#define COMPARE_370(x) x
#define COMPARE_371(x) x
#define COMPARE_372(x) x
#define COMPARE_373(x) x
#define COMPARE_374(x) x
#define COMPARE_375(x) x
#define COMPARE_376(x) x
#define COMPARE_377(x) x
#define COMPARE_378(x) x
#define COMPARE_379(x) x
#define COMPARE_380(x) x
#define COMPARE_381(x) x
#define COMPARE_382(x) x
#define COMPARE_383(x) x
#define COMPARE_384(x) x
#define COMPARE_385(x) x
#define COMPARE_386(x) x
#define COMPARE_387(x) x
#define COMPARE_388(x) x
#define COMPARE_389(x) x
#define COMPARE_390(x) x
#define COMPARE_391(x) x
#define COMPARE_392(x) x
#define COMPARE_393(x) x
#define COMPARE_394(x) x
#define COMPARE_395(x) x
#define COMPARE_396(x) x
#define COMPARE_397(x) x
#define COMPARE_398(x) x
#define COMPARE_399(x) x
//----------------------------------------------------------------------------------------------------
#define COMPARE_a(x) x
#define COMPARE_b(x) x
#define COMPARE_c(x) x
#define COMPARE_d(x) x
#define COMPARE_e(x) x
#define COMPARE_f(x) x
#define COMPARE_g(x) x
#define COMPARE_h(x) x
#define COMPARE_i(x) x
#define COMPARE_j(x) x
#define COMPARE_k(x) x
#define COMPARE_l(x) x
#define COMPARE_m(x) x
#define COMPARE_n(x) x
#define COMPARE_o(x) x
#define COMPARE_p(x) x
#define COMPARE_q(x) x
#define COMPARE_r(x) x
#define COMPARE_s(x) x
#define COMPARE_t(x) x
#define COMPARE_u(x) x
#define COMPARE_v(x) x
#define COMPARE_w(x) x
#define COMPARE_x(x) x
#define COMPARE_y(x) x
#define COMPARE_z(x) x
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////








#endif /* DENKR_ESSENTIALS_PREC_DENKR_PREC_H */
