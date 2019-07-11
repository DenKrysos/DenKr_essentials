#ifndef DENKR_ESSENTIALS_INTERPROGRAM_COMMUNICATION_COMMUNICATION_TYPES_H
#define DENKR_ESSENTIALS_INTERPROGRAM_COMMUNICATION_COMMUNICATION_TYPES_H




#include <linux/types.h>
#include <sys/types.h>
#include <stdint.h>






//################################################################################################################################
//################################################################################################################################
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//				Inter-Program Communication
//________________________________________________________________________________________________________________________________
//################################################################################################################################
//################################################################################################################################
//################################################################################################################################

//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//				Python
//--------------------------------------------------------------------------------------------------------------------------------

//The Msg-Size is only used for the Payload! I.e. After gotten Header receive msgsize!
typedef uint64_t _msgsize_from_Python;
typedef _msgsize_from_Python msgsizePy;

typedef uint8_t _msgtype_from_Python;
typedef _msgtype_from_Python msgtypePy;
typedef uint8_t _msgsubtype_from_Python;
typedef _msgsubtype_from_Python msgsubtypePy;

typedef uint8_t _msgflags_from_Python;
typedef _msgflags_from_Python msgflagsPy;


struct DenKr_PyC_Msg_Header{
	msgsizePy len;
	msgtypePy type;
	msgsubtypePy subtype;
	uint32_t src;
	msgflagsPy flags;
};


typedef unsigned char msg_to_Py_Block_Idx;// !! ATTENTION !! Carefully adjust the SIZEOF below, when changing the type
#define SIZEOF_msg_to_Py_Block_Idx 1



struct MsgFromPythonBsp1 {
	int a;
	char b;
};



/* OK, throw the union-approach into trash. This carries us into some troubles,
 * because of this unified Space-Allocation and padding and stuff. I don't like unions...
 * In my Mind better Solution see below */
//union MsgPythonContent {
//	char misc;//A String, if the received Msg was "Misc". Null-terminated after Reception, Sent without Null-Termination.
//			//Take its address, if you need a char*, like for String-Operations.
//			//This is the first char, of a malloced sequence.
//	msg_to_Py_Block_Idx block_idx;//GOT_BLOCKS, WANT_BLOCKS
//	struct MsgFromPythonBsp1 bsp1;
//};
//struct MsgPython {
//	msgtypePy type;
//	union MsgPythonContent content;
//};

/* In general it works like this:
 * There is some allocated Mem-Space. At the Beginning stays the Msg-Type and right after it
 * completely without padding or spare space or something follows the Msg-Content (if any).
 * To use this content cast the Msg-Address to a appropriate struct-Pointer from below or read it out
 * with raw address-calculation.
 * At the very Beginning just create a "struct MsgPython *pname" and pass this or its address to my
 * functions. They allocate something or read them out.
 */

/* Use this for determining the Type or the address of content for Misc-Type-Msgs */
struct MsgPython{
	msgtypePy type;
	void* content;
};
/* You could also use this for Misc or Array, Str Msgs. Just use "&(entityname.misc)" */
struct MsgPythonMisc{
	msgtypePy type;
	char misc;
};
/* Cast to such a Pointer for reading/writing BlockIdx */
struct MsgPythonBlockIdx{
	msgtypePy type;
	msg_to_Py_Block_Idx block_idx;
};










#endif /* DENKR_ESSENTIALS_INTERPROGRAM_COMMUNICATION_COMMUNICATION_TYPES_H */
