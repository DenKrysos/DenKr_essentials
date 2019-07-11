/*
 * Context_Broker_Interface.c
 *
 * Authored by
 * Dennis Krummacker (20.07.2018 - 25.07.2018)
 */




#define DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER_INTERFACE__C
#define NO__DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER_BROKER_INTERFACE__C__FUNCTIONS


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
#include "./global/global_variables.h"
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
#include <string.h>
#include <stdarg.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
//#include ""
//---------------------------------------------------------------------------------
#include "DenKr_essentials/auxiliary.h"
#include "DenKr_essentials/multi_threading.h"
#include "DenKr_essentials/Context_Broker/context_broker.h"
#include "DenKr_essentials/Context_Broker/context_broker_interface.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//




int DenKr_ContextBroker_send_onlyHeader(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__type type, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags){
	int err=0;
	struct DenKr_InfBroker_Msg_Header msgh;
	memset(&msgh,0,sizeof(msgh));
	msgh.type=type;
	msgh.subtype=subtype;
	msgh.src=(iface->hidden).ownID;
	msgh.flags=flags;
	msgh.len=0;
	sem_wait(&((((iface->hidden).send_to_Broker)->hidden).mutex));
	senddetermined(((iface->hidden).send_to_Broker)->sock,(char*)(&msgh),sizeof(msgh));
	sem_post(&((((iface->hidden).send_to_Broker)->hidden).mutex));
	return err;
}


int DenKr_ContextBroker_send_noPayload(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__type type, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags, char* context){
	int err=0;
	int contextsiz;
	int msgsiz;
	char* send_msg=NULL;
	char* send_msg_after_head=NULL;

	if(context){
		contextsiz=strlen(context)+1;
		msgsiz=sizeof(struct DenKr_InfBroker_Msg_Header)+contextsiz;
		send_msg=malloc(msgsiz);
		memset(send_msg,0,msgsiz);
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->type=type;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->subtype=subtype;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->src=(iface->hidden).ownID;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->flags=flags;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->len=contextsiz;

		send_msg_after_head=send_msg+sizeof(struct DenKr_InfBroker_Msg_Header);
		memcpy(send_msg_after_head,context,contextsiz);

		sem_wait(&((((iface->hidden).send_to_Broker)->hidden).mutex));
		senddetermined(((iface->hidden).send_to_Broker)->sock,send_msg,msgsiz);
		sem_post(&((((iface->hidden).send_to_Broker)->hidden).mutex));
		if(send_msg)
			free(send_msg);
		err=0;
	}else{
		err=CONTEXT_BROKER__WARN__NO_CONTEXT;
	}
	return err;
}


//send (DenKr_InfBroker_Iface_Client, type, context_as-null-terminated-string, msg_as-null-terminated-string)
//  Sure, you could add some method to ensure that at least the context really is Null-terminated, but that would cost performance.
//  So just assume no malicious intrusion for now...
int DenKr_ContextBroker_sendInfo_Str(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__type type, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags, char* context, char* msg){
	int err=0;
	int payloadsiz, temp1, temp2, msgsiz;
	char *send_msg=NULL;
	char* send_msg_after_head=NULL;

	if(context){
		if(msg){
			temp1=strlen(context)+1;
			temp2=strlen(msg)+1;
			payloadsiz=temp1+temp2;
			msgsiz=sizeof(struct DenKr_InfBroker_Msg_Header)+payloadsiz;
			send_msg=malloc(msgsiz);
			memset(send_msg,0,msgsiz);
			((struct DenKr_InfBroker_Msg_Header*)send_msg)->type=type;
			((struct DenKr_InfBroker_Msg_Header*)send_msg)->subtype=subtype;
			((struct DenKr_InfBroker_Msg_Header*)send_msg)->src=(iface->hidden).ownID;
			((struct DenKr_InfBroker_Msg_Header*)send_msg)->flags=flags;
			((struct DenKr_InfBroker_Msg_Header*)send_msg)->len=payloadsiz;

			send_msg_after_head=send_msg+sizeof(struct DenKr_InfBroker_Msg_Header);
			memcpy(send_msg_after_head,context,temp1);
			memcpy(send_msg_after_head+temp1,msg,temp2);

			sem_wait(&((((iface->hidden).send_to_Broker)->hidden).mutex));
			senddetermined(((iface->hidden).send_to_Broker)->sock,send_msg,msgsiz);
			sem_post(&((((iface->hidden).send_to_Broker)->hidden).mutex));
			if(send_msg)
				free(send_msg);
		}else{
			DenKr_ContextBroker_send_noPayload(iface,type,subtype,flags,context);
		}
	}else{
		DenKr_ContextBroker_send_onlyHeader(iface,type,subtype,flags);
	}

	return err;
}

int DenKr_ContextBroker_sendInfo_withSize(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__type type, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags, char* context, void* msg, int msgsize){
	int err=0;
	int payloadsiz, temp1, sendmsgsiz;
	char *send_msg=NULL;
	char* send_msg_after_head=NULL;

	if(context){
		if(msg){
			temp1=strlen(context)+1;
			payloadsiz=temp1+msgsize;
			sendmsgsiz=sizeof(struct DenKr_InfBroker_Msg_Header)+payloadsiz;
			send_msg=malloc(sendmsgsiz);
			memset(send_msg,0,sendmsgsiz);
			((struct DenKr_InfBroker_Msg_Header*)send_msg)->type=type;
			((struct DenKr_InfBroker_Msg_Header*)send_msg)->subtype=subtype;
			((struct DenKr_InfBroker_Msg_Header*)send_msg)->src=(iface->hidden).ownID;
			((struct DenKr_InfBroker_Msg_Header*)send_msg)->flags=flags;
			((struct DenKr_InfBroker_Msg_Header*)send_msg)->len=payloadsiz;

			send_msg_after_head=send_msg+sizeof(struct DenKr_InfBroker_Msg_Header);
			memcpy(send_msg_after_head,context,temp1);
			memcpy(send_msg_after_head+temp1,msg,msgsize);

			sem_wait(&((((iface->hidden).send_to_Broker)->hidden).mutex));
			senddetermined(((iface->hidden).send_to_Broker)->sock,send_msg,sendmsgsiz);
			sem_post(&((((iface->hidden).send_to_Broker)->hidden).mutex));
			if(send_msg)
				free(send_msg);
		}else{
			DenKr_ContextBroker_send_noPayload(iface,type,subtype,flags,context);
		}
	}else{
		DenKr_ContextBroker_send_onlyHeader(iface,type,subtype,flags);
	}

	return err;
}

int DenKr_ContextBroker_send_noContext(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__type type, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags, void* msg, int msgsize){
	int err=0;
	int sendmsgsiz;
	char *send_msg=NULL;
	char* send_msg_after_head=NULL;

	if(msg){
		sendmsgsiz=sizeof(struct DenKr_InfBroker_Msg_Header)+msgsize;
		send_msg=malloc(sendmsgsiz);
		memset(send_msg,0,sendmsgsiz);
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->type=type;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->subtype=subtype;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->src=(iface->hidden).ownID;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->flags=flags;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->len=msgsize;

		send_msg_after_head=send_msg+sizeof(struct DenKr_InfBroker_Msg_Header);
		memcpy(send_msg_after_head,msg,msgsize);

		sem_wait(&((((iface->hidden).send_to_Broker)->hidden).mutex));
		senddetermined(((iface->hidden).send_to_Broker)->sock,send_msg,sendmsgsiz);
		sem_post(&((((iface->hidden).send_to_Broker)->hidden).mutex));
		if(send_msg)
			free(send_msg);
	}else{
		DenKr_ContextBroker_send_onlyHeader(iface,type,subtype,flags);
	}

	return err;
}

// Arguments:
//  The 'subtype' decided of which type the 'Values' are. This divides the variadic arguments after 'context' into two Alternatives:
//  The variadic arguments after 'context' are passed as a sequence of Pairs, succeeded by NULL
//  - subtype 'DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int': "Numeric Values"
//      Pair, Alternative 1: (string(/char*) key, long long value)
//  - subtype 'DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str': "Array-alike / Interpretation-dependend Values". Could be 'misused' for every Array-alike data-structure. As 'Key1=Value1' use something like 'Type=uint16_t' or 'sizeof=2', extend the sent array(s) with a Null-termination, accordingly interpret the recvd msg and your good to go...
//      Pair, Alternative 2: (string(/char*) key, string(/char*) value)
//     -> Example:
//          A1: DenKr_ContextBroker_register_Consumer_socket(InfBrokerIface,DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int,0,"Key1",12,"Key2",38,NULL);
//          A2: DenKr_ContextBroker_register_Consumer_socket(InfBrokerIface,DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str,0,"Key1","ValueString1","Key2","ValueString2",NULL);
//  You can only send Values of one Type at a time. If you want to send both, numeric and str/array send them separated in two succeeding Function-Calls
//
// Be extra careful with the passed arguments. It isn't save against "missing last value after key"
//TODO: Possible Future Extension: Mixed msg. (But keep in mind, such a solution would be much more inefficient.
int DenKr_ContextBroker_sendInfo_CSV(DenKr_InfBroker_Iface_Client* iface, DenKr_InfBroker_Msg_Header__subtype subtype, DenKr_InfBroker_Msg_Header__flags flags, char* context, ...){
	int err=0,i=0;
	int payloadsiz, msgsiz;
	char *send_msg=NULL;
	char* send_msg_after_head=NULL;
//	int num_varargs;
	char* key;
	va_list vap;
	int tmplen;

	payloadsiz=0;
	va_start(vap, context);
	switch(subtype){
	case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int:
		;
		//If changing in the future: Stay sure to make it's type (or at least its Bitwidth...) the same as:
		//    member_size(DenKr_InfBroker_msg_CSV_KeyVal_Int,val)
		DenKr_InfBroker_msg_CSV_numeric val;
		//		for(i=0;i<=num_varargs;i++){
		//			val=va_arg(vap,char*);
		//		}
		while(NULL!=(key=va_arg(vap,char*))){
			val=va_arg(vap,DenKr_InfBroker_msg_CSV_numeric);
			tmplen=strlen(key);
			payloadsiz+=tmplen+sizeof(val)+2;//+2 for the '=' and the ',' respectively the 'EOF'
			for(i=0;i<tmplen;i++){
				if( ('='==key[i]) || (','==key[i]) || ('/'==key[i]) )
					payloadsiz++;
			}
		}
		va_end(vap);
		payloadsiz++;//I want one sign more, because at the very last i would like to end the message with "KEYn=VALUEn,\n"
		payloadsiz+=strlen(context)+1;
		msgsiz=sizeof(struct DenKr_InfBroker_Msg_Header)+payloadsiz;
		send_msg=malloc(msgsiz);
		memset(send_msg,0,msgsiz);
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->type=DenKr_InfBroker_Msg_Type__KeyEqualValue_CSV;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->subtype=DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->src=(iface->hidden).ownID;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->flags=flags;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->len=payloadsiz;

		send_msg_after_head=send_msg+sizeof(struct DenKr_InfBroker_Msg_Header);
		memcpy(send_msg_after_head,context,strlen(context)+1);
		send_msg_after_head+=strlen(context)+1;

		va_start(vap, context);
		while(NULL!=(key=va_arg(vap,char*))){
			val=va_arg(vap,DenKr_InfBroker_msg_CSV_numeric);
			tmplen=strlen(key);
//			memcpy(send_msg_after_head,key,tmpsiz);
//			send_msg_after_head+=tmpsiz;
//			*send_msg_after_head='=';
			for(i=0;i<tmplen;i++){
				if( ('='==key[i]) || (','==key[i]) || ('/'==key[i]) ){
					*send_msg_after_head='/';
					send_msg_after_head++;
				}
				*send_msg_after_head=key[i];
				send_msg_after_head++;
			}
			*send_msg_after_head='=';
			send_msg_after_head++;
			*((DenKr_InfBroker_msg_CSV_numeric*)(send_msg_after_head))=val;
			send_msg_after_head+=sizeof(val);
			*send_msg_after_head=',';
			send_msg_after_head++;
		}
		*(send_msg_after_head)='\n';
//		*(send_msg_after_head-1)='\n';
		break;
	case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str:
		;
		char* valp;
		int tmplen2;
		while(NULL!=(key=va_arg(vap,char*))){
			valp=va_arg(vap,char*);
			tmplen=strlen(key);
			tmplen2=strlen(valp);
			payloadsiz+=tmplen+tmplen2+2;//+2 for the '=' and the ',' respectively the 'EOF'
			for(i=0;i<tmplen;i++){
				if( ('='==key[i]) || (','==key[i]) || ('/'==key[i]) )
					payloadsiz++;
			}
			for(i=0;i<tmplen2;i++){
				if( ('='==valp[i]) || (','==valp[i]) || ('/'==valp[i]) )
					payloadsiz++;
			}
		}
		va_end(vap);
		payloadsiz++;//I want one sign more, because at the very last i would like to end the message with "KEYn=VALUEn,\n"
		payloadsiz+=strlen(context)+1;
		msgsiz=sizeof(struct DenKr_InfBroker_Msg_Header)+payloadsiz;
		send_msg=malloc(msgsiz);
		memset(send_msg,0,msgsiz);
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->type=DenKr_InfBroker_Msg_Type__KeyEqualValue_CSV;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->subtype=DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->src=(iface->hidden).ownID;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->flags=flags;
		((struct DenKr_InfBroker_Msg_Header*)send_msg)->len=payloadsiz;

		send_msg_after_head=send_msg+sizeof(struct DenKr_InfBroker_Msg_Header);
		memcpy(send_msg_after_head,context,strlen(context)+1);
		send_msg_after_head+=strlen(context)+1;

		va_start(vap, context);
		while(NULL!=(key=va_arg(vap,char*))){
			valp=va_arg(vap,char*);
			tmplen=strlen(key);
			tmplen2=strlen(valp);
			for(i=0;i<tmplen;i++){
				if( ('='==key[i]) || (','==key[i]) || ('/'==key[i]) ){
					*send_msg_after_head='/';
					send_msg_after_head++;
				}
				*send_msg_after_head=key[i];
				send_msg_after_head++;
			}
			*send_msg_after_head='=';
			send_msg_after_head++;
			for(i=0;i<tmplen2;i++){
				if( ('='==valp[i]) || (','==valp[i]) || ('/'==valp[i]) ){
					*send_msg_after_head='/';
					send_msg_after_head++;
				}
				*send_msg_after_head=valp[i];
				send_msg_after_head++;
			}
			*send_msg_after_head=',';
			send_msg_after_head++;
		}
		*(send_msg_after_head)='\n';
		//		*(send_msg_after_head-1)='\n';
		break;
	default:
//		ArgumentError:
		printfc(red,"ERROR:");printf(" inside 'DenKr_ContextBroker_sendInfo_CSV'. Invalid Arguments passed.\n");
		va_end(vap);
		return FUNC_ERR_BAD_ARG;
		break;
	}

	va_end(vap);

	sem_wait(&((((iface->hidden).send_to_Broker)->hidden).mutex));
	senddetermined(((iface->hidden).send_to_Broker)->sock,send_msg,msgsiz);
	sem_post(&((((iface->hidden).send_to_Broker)->hidden).mutex));
	if(send_msg)
		free(send_msg);

	return err;
}

int DenKr_ContextBroker_requestInfo(DenKr_InfBroker_Iface_Client* iface, char* context){
	return DenKr_ContextBroker_send_noPayload(iface,DenKr_InfBroker_Msg_Type__Request,0,DenKr_InfBroker_Msg_FLAG__Request,context);
}


//register permanent Listener (target_socket, thread-id, number_of_contexts, contexts_as-pointer-to-argv)
//		Sends to Broker: msg-type,
//                       thread-id,
//                       socket_to_send_infos_to,
//                       (optional) number_of_contexts (makes processing easier),
//                       contexts as directly succeeding, null-terminated strings

//It checks, if the socket-variable inside the Interface-Object is already a valid one.
//  If: Just use this one and send it to the Broker
//  If not: Create new socketpair.
// Arguments:
//    Pass it a sequence of strings, succeeded by NULL
//     -> Example: DenKr_ContextBroker_register_Consumer_socket(InfBrokerIface,"test","Hurz","SDN","Schedule",NULL);
int DenKr_ContextBroker_register_Consumer_socket(DenKr_InfBroker_Iface_Client* iface, ...){
	int err=0;
	char* msg;
		//msg will look like:  Header | Iface-Pointer | "String1 \0 String2 \0 ... StringN \0 \0"
		//                   msgsize:  [_________________________________________________________]
	int payloadsiz=0;
	va_list vap;

	//Check if socket is valid. If not: create
	if(!FLAG_CHECK((iface->hidden).flags,DenKr_InfBroker_Iface_Client__FLAG__SOCK_FROM_BROKER_VALID)){
		int sockpair[2];
		if(-1==socketpair(AF_LOCAL, SOCK_STREAM, 0, sockpair)) {
			printfc(red,"ERROR:");printf(" Register at ContextBroker: Could not create socketpair.\n");
			exit(EXIT_FAILURE);
		}
		(iface->hidden).recv_from_Broker.socket=sockpair[0];
		(iface->hidden).recv_from_Broker.BrokerSock=sockpair[1];
		FLAG_SET((iface->hidden).flags,DenKr_InfBroker_Iface_Client__FLAG__SOCK_FROM_BROKER_VALID);
	}

	va_start(vap, iface);
	char* tempp;
	while(NULL!=(tempp=va_arg(vap,char*))){
//		printf("%s\n",tempp);
		while(*tempp!='\0'){
			payloadsiz++;
			tempp++;
		}
		payloadsiz++;
	}
	payloadsiz++;
	va_end(vap);

	msg=malloc(payloadsiz+sizeof(DenKr_InfBroker_Iface_Client*)+sizeof(struct DenKr_InfBroker_Msg_Header));
	memset(msg,0,payloadsiz+sizeof(DenKr_InfBroker_Iface_Client*)+sizeof(struct DenKr_InfBroker_Msg_Header));
	((struct DenKr_InfBroker_Msg_Header*)msg)->len=payloadsiz+sizeof(DenKr_InfBroker_Iface_Client*);
	((struct DenKr_InfBroker_Msg_Header*)msg)->src=(iface->hidden).ownID;
	((struct DenKr_InfBroker_Msg_Header*)msg)->type=DenKr_InfBroker_Msg_Type__Management;
	((struct DenKr_InfBroker_Msg_Header*)msg)->subtype=DenKr_InfBroker_Msg_SubType__Management__RegConsumerSocket;
	char* msghelpp;
//	msghelpp=msg+sizeof(struct DenKr_InfBroker_Msg_Header);
//	*((DenKr_InfBroker_Iface_Client**)msghelpp)=iface;
	memcpy(msg+sizeof(struct DenKr_InfBroker_Msg_Header),&iface,sizeof(iface));
	msghelpp=msg+sizeof(DenKr_InfBroker_Iface_Client*)+sizeof(struct DenKr_InfBroker_Msg_Header);
//	printf("!!! %d\n",((*((DenKr_InfBroker_Iface_Client**)(msg+sizeof(struct DenKr_InfBroker_Msg_Header))))->hidden).ownID);
//	printf("\nIface: %llu | from msg: %llu\n\n\n",iface,*((DenKr_InfBroker_Iface_Client**)(msg+sizeof(struct DenKr_InfBroker_Msg_Header))));

	va_start(vap,iface);
	while(NULL!=(tempp=va_arg(vap,char*))){
		while(*tempp!='\0'){
			*msghelpp=*tempp;
			tempp++;
			msghelpp++;
		}
		*msghelpp='\0';
		msghelpp++;
	}
	*msghelpp='\0';
	va_end(vap);

	senddetermined((iface->hidden).send_to_Broker->sock,msg,((struct DenKr_InfBroker_Msg_Header*)msg)->len + sizeof(struct DenKr_InfBroker_Msg_Header));
	if(msg)
		free(msg);

	return err;
}
int DenKr_ContextBroker_register_Producer_socket(DenKr_InfBroker_Iface_Client* iface, ...){
	int err=0;
	char* msg;
		//msg will look like:  Header | Iface-Pointer | "String1 \0 String2 \0 ... StringN \0 \0"
		//                   msgsize:  [_________________________________________________________]
	int payloadsiz=0;
	va_list vap;

	//Check if socket is valid. If not: create
	if(!FLAG_CHECK((iface->hidden).flags,DenKr_InfBroker_Iface_Client__FLAG__SOCK_FROM_BROKER_VALID)){
		int sockpair[2];
		if(-1==socketpair(AF_LOCAL, SOCK_STREAM, 0, sockpair)) {
			printfc(red,"ERROR:");printf(" Register at ContextBroker: Could not create socketpair.\n");
			exit(EXIT_FAILURE);
		}
		(iface->hidden).recv_from_Broker.socket=sockpair[0];
		(iface->hidden).recv_from_Broker.BrokerSock=sockpair[1];
		FLAG_SET((iface->hidden).flags,DenKr_InfBroker_Iface_Client__FLAG__SOCK_FROM_BROKER_VALID);
	}

	va_start(vap, iface);
	char* tempp;
	while(NULL!=(tempp=va_arg(vap,char*))){
		while(*tempp!='\0'){
			payloadsiz++;
			tempp++;
		}
		payloadsiz++;
	}
	payloadsiz++;
	va_end(vap);
	msg=malloc(payloadsiz+sizeof(DenKr_InfBroker_Iface_Client*)+sizeof(struct DenKr_InfBroker_Msg_Header));
	memset(msg,0,payloadsiz+sizeof(DenKr_InfBroker_Iface_Client*)+sizeof(struct DenKr_InfBroker_Msg_Header));
	((struct DenKr_InfBroker_Msg_Header*)msg)->len=payloadsiz+sizeof(DenKr_InfBroker_Iface_Client*);
	((struct DenKr_InfBroker_Msg_Header*)msg)->src=(iface->hidden).ownID;
	((struct DenKr_InfBroker_Msg_Header*)msg)->type=DenKr_InfBroker_Msg_Type__Management;
	((struct DenKr_InfBroker_Msg_Header*)msg)->subtype=DenKr_InfBroker_Msg_SubType__Management__RegProducerSocket;
	char* msghelpp;
//	msghelpp=((struct DenKr_InfBroker_Msg_Header*)msg)+1;//msg+sizeof(struct DenKr_InfBroker_Msg_Header)
//	*msghelpp=iface;
	memcpy(msg+sizeof(struct DenKr_InfBroker_Msg_Header),&iface,sizeof(iface));
	msghelpp=msg+sizeof(DenKr_InfBroker_Iface_Client*)+sizeof(struct DenKr_InfBroker_Msg_Header);

	va_start(vap,iface);
	while(NULL!=(tempp=va_arg(vap,char*))){
		while(*tempp!='\0'){
			*msghelpp=*tempp;
			tempp++;
			msghelpp++;
		}
		*msghelpp='\0';
		msghelpp++;
	}
	*msghelpp='\0';
	va_end(vap);

	senddetermined((iface->hidden).send_to_Broker->sock,msg,((struct DenKr_InfBroker_Msg_Header*)msg)->len + sizeof(struct DenKr_InfBroker_Msg_Header));
	if(msg)
		free(msg);

	return err;
}


//register Callback
//		Callback Functions have to free the passed msg inside. They get the msg passed via a point behind which space is malloced that isn't freed anywhere else.
//      -> Consider using "int DenKr_ContextBroker_parsemsg_callback(void* parse, DenKr_InfBroker_msg** msg)"
int DenKr_ContextBroker_register_Consumer_callback(DenKr_InfBroker_Iface_Client* iface, InfBrok_Func_Callback callback, ...){
	int err=0;
	char* msg;
		//msg will look like:  Header | Callback-Func(void-Pointer) | "String1 \0 String2 \0 ... StringN \0 \0"
		//                   msgsize:  [_______________________________________________________________________]
	int payloadsiz=0;
	va_list vap;

	va_start(vap, callback);
	char* tempp;
	while(NULL!=(tempp=va_arg(vap,char*))){
		while(*tempp!='\0'){
			payloadsiz++;
			tempp++;
		}
		payloadsiz++;
	}
	payloadsiz++;
	va_end(vap);

	msg=malloc(payloadsiz+sizeof(InfBrok_Func_Callback)+sizeof(struct DenKr_InfBroker_Msg_Header));
	memset(msg,0,payloadsiz+sizeof(InfBrok_Func_Callback)+sizeof(struct DenKr_InfBroker_Msg_Header));
	((struct DenKr_InfBroker_Msg_Header*)msg)->len=payloadsiz+sizeof(InfBrok_Func_Callback);
	((struct DenKr_InfBroker_Msg_Header*)msg)->src=(iface->hidden).ownID;
	((struct DenKr_InfBroker_Msg_Header*)msg)->type=DenKr_InfBroker_Msg_Type__Management;
	((struct DenKr_InfBroker_Msg_Header*)msg)->subtype=DenKr_InfBroker_Msg_SubType__Management__RegConsumerCallback;
	char* msghelpp;
//	msghelpp=((struct DenKr_InfBroker_Msg_Header*)msg)+1;//msg+sizeof(struct DenKr_InfBroker_Msg_Header)
//	*msghelpp=iface;
	memcpy(msg+sizeof(struct DenKr_InfBroker_Msg_Header),&callback,sizeof(callback));
	msghelpp=msg+sizeof(InfBrok_Func_Callback)+sizeof(struct DenKr_InfBroker_Msg_Header);

	va_start(vap,callback);
	while(NULL!=(tempp=va_arg(vap,char*))){
		while(*tempp!='\0'){
			*msghelpp=*tempp;
			tempp++;
			msghelpp++;
		}
		*msghelpp='\0';
		msghelpp++;
	}
	*msghelpp='\0';
	va_end(vap);

	senddetermined((iface->hidden).send_to_Broker->sock,msg,((struct DenKr_InfBroker_Msg_Header*)msg)->len + sizeof(struct DenKr_InfBroker_Msg_Header));
	if(msg)
		free(msg);

	return err;
}
int DenKr_ContextBroker_register_Producer_callback(DenKr_InfBroker_Iface_Client* iface, InfBrok_Func_Callback callback, ...){
	int err=0;
	char* msg;
		//msg will look like:  Header | Callback-Func(void-Pointer) | "String1 \0 String2 \0 ... StringN \0 \0"
		//                   msgsize:  [_______________________________________________________________________]
	int payloadsiz=0;
	va_list vap;

	va_start(vap, callback);
	char* tempp;
	while(NULL!=(tempp=va_arg(vap,char*))){
		while(*tempp!='\0'){
			payloadsiz++;
			tempp++;
		}
		payloadsiz++;
	}
	payloadsiz++;
	va_end(vap);
	msg=malloc(payloadsiz+sizeof(InfBrok_Func_Callback)+sizeof(struct DenKr_InfBroker_Msg_Header));
	memset(msg,0,payloadsiz+sizeof(InfBrok_Func_Callback)+sizeof(struct DenKr_InfBroker_Msg_Header));
	((struct DenKr_InfBroker_Msg_Header*)msg)->len=payloadsiz+sizeof(InfBrok_Func_Callback);
	((struct DenKr_InfBroker_Msg_Header*)msg)->src=(iface->hidden).ownID;
	((struct DenKr_InfBroker_Msg_Header*)msg)->type=DenKr_InfBroker_Msg_Type__Management;
	((struct DenKr_InfBroker_Msg_Header*)msg)->subtype=DenKr_InfBroker_Msg_SubType__Management__RegProducerCallback;
	char* msghelpp;
//	msghelpp=((struct DenKr_InfBroker_Msg_Header*)msg)+1;//msg+sizeof(struct DenKr_InfBroker_Msg_Header)
//	*msghelpp=iface;
	memcpy(msg+sizeof(struct DenKr_InfBroker_Msg_Header),&callback,sizeof(callback));
	msghelpp=msg+sizeof(InfBrok_Func_Callback)+sizeof(struct DenKr_InfBroker_Msg_Header);
//	printf("!!! %llu\n",*((void**)(msg+sizeof(struct DenKr_InfBroker_Msg_Header))));

	va_start(vap,callback);
	while(NULL!=(tempp=va_arg(vap,char*))){
		while(*tempp!='\0'){
			*msghelpp=*tempp;
			tempp++;
			msghelpp++;
		}
		*msghelpp='\0';
		msghelpp++;
	}
	*msghelpp='\0';
	va_end(vap);

	senddetermined((iface->hidden).send_to_Broker->sock,msg,((struct DenKr_InfBroker_Msg_Header*)msg)->len + sizeof(struct DenKr_InfBroker_Msg_Header));
	if(msg)
		free(msg);

	return err;
}



//Hm, just if you like to know: The return value is, if positive, the length of the context string. Not that this is a really desirable Information... But hey, it's a byproduct.
//REMEMBER to use "int DenKr_ContextBroker_free_msg(DenKr_InfBroker_msg* msg)" after you are done with the message!
int DenKr_ContextBroker_recvmsg_socket(DenKr_InfBroker_Iface_Client* iface,DenKr_InfBroker_msg** msg){
	int err=0;//aka context_length (real length, not strlen)
	int b_recvd;
	char* msg_temp;

	*msg=malloc(sizeof(**msg));
	memset(*msg,0,sizeof(**msg));
	(*msg)->head=malloc(sizeof(*((*msg)->head)));

	b_recvd=recv((iface->hidden).recv_from_Broker.socket,(char*)((*msg)->head),sizeof(*((*msg)->head)), 0);
	while(b_recvd<sizeof(*((*msg)->head))){
		int b_recvd_temp;
		b_recvd_temp=recv((iface->hidden).recv_from_Broker.socket,((char*)((*msg)->head))+b_recvd,sizeof(*((*msg)->head))-b_recvd,0);
		if(0>b_recvd_temp){
			//TODO
			printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at receiving inside DenKr_ContextBroker_recvmsg_socket 1.\n");
		}else if(0==b_recvd_temp){
			//TODO
			printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at receiving inside DenKr_ContextBroker_recvmsg_socket 2.\n");
		}
		b_recvd+=b_recvd_temp;
	}

	msg_temp=malloc(((*msg)->head)->len);
	b_recvd=recv((iface->hidden).recv_from_Broker.socket,msg_temp,((*msg)->head)->len,0);
	while(b_recvd<((*msg)->head)->len){
		int b_recvd_temp;
		b_recvd_temp=recv((iface->hidden).recv_from_Broker.socket,msg_temp+b_recvd,(((*msg)->head)->len)-b_recvd,0);
		if(0>b_recvd_temp){
			//TODO
			printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at receiving inside DenKr_ContextBroker_recvmsg_socket 3.\n");
		}else if(0==b_recvd_temp){
			//TODO
			printfc(red,"\n!ERROR!!!ERROR! TODO. Some Error at receiving inside DenKr_ContextBroker_recvmsg_socket 4.\n");
		}
		b_recvd+=b_recvd_temp;
	}

	err=strlen(msg_temp)+1;
	(*msg)->context=malloc(err);
	memcpy((*msg)->context,msg_temp,err);
	((*msg)->head)->len-=err;
	if(((*msg)->head)->len){
		(*msg)->msg=malloc(((*msg)->head)->len);
		memcpy((*msg)->msg,msg_temp+err,((*msg)->head)->len);
	}else{
		(*msg)->msg=NULL;
	}
	if(msg_temp)
		free(msg_temp);

	return err;
}

//Just gets the message and fills in the 'DenKr_InfBroker_msg' struct. Extracts context, header and stuff. Just for a bit comfort.
// This frees the passed msg.
//REMEMBER to use "int DenKr_ContextBroker_free_msg(DenKr_InfBroker_msg* msg)" after you are done with the parsed message-struct created by this!
int DenKr_ContextBroker_parsemsg_callback(void* parse, DenKr_InfBroker_msg** msg){
	int err=0;
	char* parse_msg;

	err=sizeof(**msg);
	*msg=malloc(err);
//	memset(*msg,0,err);
	(*msg)->head=malloc(sizeof(*((*msg)->head)));

	memcpy((*msg)->head,parse,sizeof(*((*msg)->head)));
	parse_msg=parse+sizeof(*((*msg)->head));

	err=strlen(parse_msg)+1;
	(*msg)->context=malloc(err);
	memcpy((*msg)->context,parse_msg,err);
	((*msg)->head)->len-=err;
	if(((*msg)->head)->len){
		(*msg)->msg=malloc(((*msg)->head)->len);
		memcpy((*msg)->msg,parse_msg+err,((*msg)->head)->len);
	}else{
		(*msg)->msg=NULL;
	}

	free(parse);

	return err;
}

//It replaces the original "msg-Pointer" inside the 'DenKr_InfBroker_msg' with a "DenKr_InfBroker_msg_CSV", i.e. frees the old content behind the pointer and creates the new one with the new format
//TO USE it: cast the 'void* msg' inside the 'DenKr_InfBroker_msg' to a 'DenKr_InfBroker_msg_CSV*' or use the macro
//     -> InfBrokMsgCSV(DenKr_InfBroker_msg_Point)
//REMEMBER to use "int DenKr_ContextBroker_free_msg(DenKr_InfBroker_msg* msg)" after you are done with the parsed message-struct created by this!
int DenKr_ContextBroker_parsemsg_CSV(DenKr_InfBroker_msg* msg){
	//TODO
	//Important:
	//  malloc the space for the whole stuff in one and than manually connect the pointers. In this way it is possible to use the common free_msg function
	//    and also is secured: locality.

	if(msg->head->type != DenKr_InfBroker_Msg_Type__KeyEqualValue_CSV){
		printfc(yellow,"Warning:");printf(" Bug? Passed InfBroker-msg to CSV-parse not of Type 'DenKr_InfBroker_Msg_Type__KeyEqualValue_CSV'\n");
		return FUNC_ERR_BAD_ARG;
	}

	int err=0,i;
	char* old_msg;
	int numpairs=0;
	int keyvalsiz=msg->head->len;
//	char* keyvalp;
	char* targetcur;
	char* srccur;

	switch(msg->head->subtype){
	case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int:
		old_msg = msg->msg;
		////////////////
		for(i=0;i<msg->head->len;i++){
		}
		////////////////
		for(i=0;i<msg->head->len;i++){
			if( ('/'==old_msg[i]) && ('/'!=old_msg[i+1]) ){
				keyvalsiz--;
			}
			if( ('='==old_msg[i]) && ('/'!=old_msg[i-1]) ){
				numpairs++;
				i+=sizeof(member_size(DenKr_InfBroker_msg_CSV_KeyVal_Int,val));
				keyvalsiz-=sizeof(member_size(DenKr_InfBroker_msg_CSV_KeyVal_Int,val))+1;//-1 for the ',' after every Value-Number. In the String-Value Case we use this to insert a '\0', but for the numerics this is not needed. Note: Written as "+1" because of the usage of "-="
			}
		}
		msg->head->len=sizeof(DenKr_InfBroker_msg_CSV)+numpairs*sizeof(DenKr_InfBroker_msg_CSV_KeyVal_Int)+keyvalsiz-1;//-1 for the final '\n', closing the message
		msg->msg=malloc(msg->head->len);
		InfBrokMsgCSV(msg)->count=numpairs;
		if(!numpairs){
			(InfBrokMsgCSV(msg)->pairs).numeric=NULL;
		}else{
			(InfBrokMsgCSV(msg)->pairs).numeric=msg->msg+sizeof(DenKr_InfBroker_msg_CSV);
//			keyvalp=msg->msg+sizeof(DenKr_InfBroker_msg_CSV)+numpairs*sizeof(DenKr_InfBroker_msg_CSV_KeyVal_Int);
//			targetcur=keyvalp;
			targetcur=msg->msg+sizeof(DenKr_InfBroker_msg_CSV)+numpairs*sizeof(DenKr_InfBroker_msg_CSV_KeyVal_Int);
			srccur=old_msg;
			for(i=0;i<InfBrokMsgCSV(msg)->count;i++){
				(((InfBrokMsgCSV(msg)->pairs).numeric)[i]).key=targetcur;
//				while( !( ('='==*srccur) && ('/'!=*(srccur-1)) ) ){
//					if('/'==*srccur){
//						srccur++;
//					}
//				}
//				Nopes. this can be done better...
				while(1){
					if('/'==*srccur){
						srccur++;
						*targetcur=*srccur;
						targetcur++;
						srccur++;
					}else if('='==*srccur){
						//This is the break condition. We found the equal-sign after the key.
						//  Recognize: We can only reach here with unmasked '='. The masked section above already skips two signs together.
						*targetcur='\0';
						targetcur++;
						srccur++;
						break;
					}else{
						*targetcur=*srccur;
						targetcur++;
						srccur++;
					}
				}
				//Key is copied over and connected. Now the Value.
				(((InfBrokMsgCSV(msg)->pairs).numeric)[i]).val=*((DenKr_InfBroker_msg_CSV_numeric *)srccur);
				srccur+=sizeof(DenKr_InfBroker_msg_CSV_numeric)+1;//+1 for the trailing ','
			}
		}
		break;
	case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str:
		old_msg = msg->msg;
		for(i=0;i<msg->head->len;i++){
			if( ('/'==old_msg[i]) && ('/'!=old_msg[i+1]) ){
				keyvalsiz--;
			}
			if( ('='==old_msg[i]) && ('/'!=old_msg[i-1]) ){
				numpairs++;
			}
		}
		msg->head->len=sizeof(DenKr_InfBroker_msg_CSV)+numpairs*sizeof(DenKr_InfBroker_msg_CSV_KeyVal_Str)+keyvalsiz-1;//-1 for the final '\n', closing the message
		msg->msg=malloc(msg->head->len);
		InfBrokMsgCSV(msg)->count=numpairs;
		if(!numpairs){
			(InfBrokMsgCSV(msg)->pairs).string=NULL;
		}else{
			(InfBrokMsgCSV(msg)->pairs).string=msg->msg+sizeof(DenKr_InfBroker_msg_CSV);
//			keyvalp=msg->msg+sizeof(DenKr_InfBroker_msg_CSV)+numpairs*sizeof(DenKr_InfBroker_msg_CSV_KeyVal_Str);
//			targetcur=keyvalp;
			targetcur=msg->msg+sizeof(DenKr_InfBroker_msg_CSV)+numpairs*sizeof(DenKr_InfBroker_msg_CSV_KeyVal_Str);
			srccur=old_msg;
			for(i=0;i<InfBrokMsgCSV(msg)->count;i++){
				(((InfBrokMsgCSV(msg)->pairs).string)[i]).key=targetcur;
//				while( !( ('='==*srccur) && ('/'!=*(srccur-1)) ) ){
//					if('/'==*srccur){
//						srccur++;
//					}
//				}
//				Nopes. this can be done better...
				while(1){
					if('/'==*srccur){
						srccur++;
						*targetcur=*srccur;
						targetcur++;
						srccur++;
					}else if('='==*srccur){
						//This is the break condition. We found the equal-sign after the key.
						//  Recognize: We can only reach here with unmasked '='. The masked section above already skips two signs together.
						*targetcur='\0';
						targetcur++;
						srccur++;
						break;
					}else{
						*targetcur=*srccur;
						targetcur++;
						srccur++;
					}
				}
				//Key is copied over and connected. Now the Value.
				(((InfBrokMsgCSV(msg)->pairs).string)[i]).val=targetcur;
				while(1){
					if('/'==*srccur){
						srccur++;
						*targetcur=*srccur;
						targetcur++;
						srccur++;
					}else if(','==*srccur){
						//This is the break condition. We found the comma-sign after the value.
						//  Recognize: We can only reach here with unmasked ','. The masked section above already skips two signs together.
						*targetcur='\0';
						targetcur++;
						srccur++;
						break;
//					}else if('\n'==*srccur){
					}else{
						*targetcur=*srccur;
						targetcur++;
						srccur++;
					}
				}
			}
		}
		break;
	default:
		printfc(yellow,"Warning:");printf(" Bug? Passed InfBroker-msg to CSV-parse of unknown/wrong subtype.\n");
		return FUNC_ERR_BAD_ARG;
		break;
	}

	free(old_msg);

	return err;
}

void DenKr_ContextBroker_free_msg(DenKr_InfBroker_msg* msg){
	if(msg){
		if(msg->head)
			free(msg->head);
		if(msg->context)
			free(msg->context);
		if(msg->msg)
			free(msg->msg);
		free(msg);
	}
}









//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Data-Structure Grasp  ----------------------------------------------------------------------//
//----      Some Stuff, helpful to access Information inside Structures (like msgs)  ---------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
//RECOGNIZE that the same key could occur multiple times!
#define MsgKeyNum ((((InfBrokMsgCSV(msg)->pairs).numeric)[i]).key)
#define MsgKeyStr ((((InfBrokMsgCSV(msg)->pairs).string)[i]).key)
//Return Values:
// 0  - Successful run. Number of found Key occurrences returned in "int* res"
// FUNC_ERR_BAD_ARG  - A "DenKr_essentials Error". Passed Pointer was no valid "DenKr_InfBroker_msg*"
int DenKr_ContextBroker_CSV_countKeyTimes(DenKr_InfBroker_msg* msg, char* search, int* res){
	int keyTimes=0;
	if(msg->head->type == DenKr_InfBroker_Msg_Type__KeyEqualValue_CSV){
		int i, j;
		switch(msg->head->subtype){
		case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int:
			for(i=0;i<InfBrokMsgCSV(msg)->count;i++){
				//Pro Key auf search prüfen. Würde ich pro character machen, erzeugt schnellere und effizientere Terminierungsbedingungen.
				//Damit kommst du auf die Array-Inhalte
				// (((InfBrokMsgCSV(msg)->pairs).numeric)[i]).key //String
				// (((InfBrokMsgCSV(msg)->pairs).numeric)[i]).val //Numerischer Wert
//				char* cp=(((InfBrokMsgCSV(msg)->pairs).numeric)[i]).key;
				j=0;
				while(1){
					if('\0'==MsgKeyNum[j]){
						if('\0' == search[j]){
							//Termination condition (assuming every other action corresponds correctly...)
							//Key completely traversed, Key and search matched until now
							//-> Search Term found
							keyTimes++;
							break;
						}else{
							//Partial Termination Condition
							//Key completely traversed. search still ongoing.
							//-> No match
							//Continue with next Key
							break;
						}
					}else if('\0' == search[j]){
						//Partial Termination Condition
						//search completely traversed. key actually still ongoing.
						//-> No match
						//Continue with next Key
						break;
					}
					if(MsgKeyNum[j]!=search[j]){
						break;
					}
					j++;
				}
				//Key not found
			}
			//Every Key traversed, Number of occurrences counted
			break;
		case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str:
			for(i=0;i<InfBrokMsgCSV(msg)->count;i++){
				//Pretty much same as above, except that the Values here also are Strings
				j=0;
				while(1){
					if('\0'==MsgKeyStr[j]){
						if('\0' == search[j]){
							//Termination condition (assuming every other action corresponds correctly...)
							//Key completely traversed, Key and search matched until now
							//-> Search Term found
							keyTimes++;
							break;
						}else{
							//Partial Termination Condition
							//Key completely traversed. search still ongoing.
							//-> No match
							//Continue with next Key
							break;
						}
					}else if('\0' == search[j]){
						//Partial Termination Condition
						//search completely traversed. key actually still ongoing.
						//-> No match
						//Continue with next Key
						break;
					}
					if(MsgKeyStr[j]!=search[j]){
						break;
					}
					j++;
				}
				//Key not found
			}
			//Every Key traversed, Number of occurrences counted
			break;
		default:
			printfc(gray,"   DEBUG");printfc(DENKR__COLOR_ANSI__DL_LIBS," (Plugin)");printfc(gray,":");printf(" Msg to countKeyTimes (CSV) not of type CSV\n");
			return FUNC_ERR_BAD_ARG;
			break;
		}
	}else{
		printfc(gray,"   DEBUG");printfc(DENKR__COLOR_ANSI__DL_LIBS," (Plugin)");printfc(gray,":");printf(" Msg to countKeyTimes (CSV) not of type CSV\n");
		return FUNC_ERR_BAD_ARG;
	}
	*res=keyTimes;
	return 0;
}

//Return Values:
// 0  - Successful run. Index returned in "int* resIndex"
// 1  - Key not found / Not that many Key occurrences present
// FUNC_ERR_BAD_ARG  - A "DenKr_essentials Error". Passed Pointer was no valid "DenKr_InfBroker_msg*"
int DenKr_ContextBroker_CSV_getNthIndex(DenKr_InfBroker_msg* msg, char* search, int nthIndex, int* resIndex){
	if(0>=nthIndex){
		return FUNC_ERR_BAD_ARG;
	}
	int seen=0;
	if(msg->head->type == DenKr_InfBroker_Msg_Type__KeyEqualValue_CSV){
		int i, j;
		switch(msg->head->subtype){
		case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int:
			for(i=0;i<InfBrokMsgCSV(msg)->count;i++){
				j=0;
				while(1){
					if('\0'==MsgKeyNum[j]){
						if('\0' == search[j]){
							//Termination condition (assuming every other action corresponds correctly...)
							//Key completely traversed, Key and search matched until now
							//-> Search Term found
							seen++;
							break;
						}else{
							//Partial Termination Condition
							//Key completely traversed. search still ongoing.
							//-> No match
							//Continue with next Key
							break;
						}
					}else if('\0' == search[j]){
						//Partial Termination Condition
						//search completely traversed. key actually still ongoing.
						//-> No match
						//Continue with next Key
						break;
					}
					if(MsgKeyNum[j]!=search[j]){
						break;
					}
					j++;
				}
				if(seen==nthIndex){
					*resIndex=i;
					return 0;
				}
			}
			//Termination Condition not met
			//-> requested Index too high, not existent for Key.
			*resIndex=0;
			return 1;
			break;
		case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str:
			for(i=0;i<InfBrokMsgCSV(msg)->count;i++){
				j=0;
				while(1){
					if('\0'==MsgKeyStr[j]){
						if('\0' == search[j]){
							//Termination condition (assuming every other action corresponds correctly...)
							//Key completely traversed, Key and search matched until now
							//-> Search Term found
							seen++;
							break;
						}else{
							//Partial Termination Condition
							//Key completely traversed. search still ongoing.
							//-> No match
							//Continue with next Key
							break;
						}
					}else if('\0' == search[j]){
						//Partial Termination Condition
						//search completely traversed. key actually still ongoing.
						//-> No match
						//Continue with next Key
						break;
					}
					if(MsgKeyStr[j]!=search[j]){
						break;
					}
					j++;
				}
				if(seen==nthIndex){
					*resIndex=i;
					return 0;
				}
			}
			//Termination Condition not met
			//-> requested Index too high, not existent for Key.
			*resIndex=0;
			return 1;
			break;
		default:
			printfc(gray,"   DEBUG");printfc(DENKR__COLOR_ANSI__DL_LIBS," (Plugin)");printfc(gray,":");printf(" Msg to getNthIndex (CSV) not of type CSV\n");
			return FUNC_ERR_BAD_ARG;
			break;
		}
	}else{
		printfc(gray,"   DEBUG");printfc(DENKR__COLOR_ANSI__DL_LIBS," (Plugin)");printfc(gray,":");printf(" Msg to getNthIndex (CSV) not of type CSV\n");
		return FUNC_ERR_BAD_ARG;
	}
	return FUNC_ERR_BAD_ARG;
}

//Return Values:
// 0  - Index not found (requested Index higher than number of elements)
// 1  - msgType & Result are of Type "Numeric". Returns Pointer to Value inside "void** res". As a User cast the past pointer afterwards to appropriate Type, according to function return Value.
// 2  - msgType & Result are of Type "String"
// FUNC_ERR_BAD_ARG  - A "DenKr_essentials Error". Passed Pointer was no valid "DenKr_InfBroker_msg*"
// Behind keyReturn, the Key of the requested Index is returned (In case you want to check it...)
int DenKr_ContextBroker_CSV_getValbyIndex(DenKr_InfBroker_msg* msg, int index, void** res, char** keyReturn){
	if(index>=InfBrokMsgCSV(msg)->count){
		return 0;
	}
	if(msg->head->type == DenKr_InfBroker_Msg_Type__KeyEqualValue_CSV){
		switch(msg->head->subtype){
		case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int:
			if(keyReturn)
				*keyReturn=(((InfBrokMsgCSV(msg)->pairs).numeric)[index]).key;
			*res=&((((InfBrokMsgCSV(msg)->pairs).numeric)[index]).val);
			return 1;
			break;
		case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str:
			if(keyReturn)
				*keyReturn=(((InfBrokMsgCSV(msg)->pairs).string)[index]).key;
			*res=(((InfBrokMsgCSV(msg)->pairs).string)[index]).val;
			return 2;
			break;
		default:
			printfc(gray,"   DEBUG");printfc(DENKR__COLOR_ANSI__DL_LIBS," (Plugin)");printfc(gray,":");printf(" Msg to getValbyIndex (CSV) not of type CSV\n");
			return FUNC_ERR_BAD_ARG;
			break;
		}
	}else{
		printfc(gray,"   DEBUG");printfc(DENKR__COLOR_ANSI__DL_LIBS," (Plugin)");printfc(gray,":");printf(" Msg to getValbyIndex (CSV) not of type CSV\n");
		return FUNC_ERR_BAD_ARG;
	}
	return FUNC_ERR_BAD_ARG;
}

// !! Search just by Key not done (yet). Rather use the chain of "(countKeyTimes ->) getNthIndex -> getValbyIndex"
//Return Values:
// 0  - Key not found
// 1  - msgType & Result are of Type "Numeric". Returns Pointer to Value inside "void** res". As a User cast the past pointer afterwards to appropriate Type, according to function return Value.
// 2  - msgType & Result are of Type "String"
// FUNC_ERR_BAD_ARG  - A "DenKr_essentials Error". Passed Pointer was no valid "DenKr_InfBroker_msg*"
//int DenKr_ContextBroker_CSV_getValue(DenKr_InfBroker_msg* msg, char* search, int index, void** res){
//
//}
#undef MsgKeyNum
#undef MsgKeyStr









//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Debugging  ---------------------------------------------------------------------------------//
//----      Some Stuff, helpful at Debugging  ------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
int DenKr_ContextBroker_Debug_printmsg(DenKr_InfBroker_msg* msg){
	printfc(gray,"   DEBUG");printfc(DENKR__COLOR_ANSI__DL_LIBS," (Plugin)");printfc(gray,":");printf(" received Msg from Context-Broker:\n\tsize: %lli | src: %d | type: %d | subtype %d | context: %s | ",(long long int)(*msg).head->len,(*msg).head->src,(*msg).head->type,(*msg).head->subtype,(*msg).context);
	if(msg->msg){
		printf("msg: %s\n",(char*)((*msg).msg));
	}else{
		printf("No attached msg, i.e. only Header.\n");
	}
	return 0;
}

int DenKr_ContextBroker_Debug_printmsg_CSV(DenKr_InfBroker_msg* msg){
	if(msg->head->type == DenKr_InfBroker_Msg_Type__KeyEqualValue_CSV){
		int i;
		switch(msg->head->subtype){
		case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__int:
			printfc(gray,"   DEBUG");printfc(DENKR__COLOR_ANSI__DL_LIBS," (Plugin)");printfc(gray,":");printf(" received Msg (CSV) from Context-Broker:\n\tsize: %lli | src: %d | type: %d | subtype %d | context: %s\n",(long long int)(*msg).head->len,(*msg).head->src,(*msg).head->type,(*msg).head->subtype,(*msg).context);
			printf("\tparsed to CSV-Key-Value-Pairs: (Numeric Values) (Number of Pairs: %d)  [Print-Format:] 'KEY' = 'VALUE'\n",InfBrokMsgCSV(msg)->count);
			printf("\t[\n");
			for(i=0;i<InfBrokMsgCSV(msg)->count;i++){
				printf("\t  '%s' = '%lli'\n",(((InfBrokMsgCSV(msg)->pairs).numeric)[i]).key,(((InfBrokMsgCSV(msg)->pairs).numeric)[i]).val);
			}
			printf("\t]\n");
			break;
			break;
		case DenKr_InfBroker_Msg_SubType__KeyEqualValue_CSV__str:
			printfc(gray,"   DEBUG");printfc(DENKR__COLOR_ANSI__DL_LIBS," (Plugin)");printfc(gray,":");printf(" received Msg (CSV) from Context-Broker:\n\tsize: %lli | src: %d | type: %d | subtype %d | context: %s\n",(long long int)(*msg).head->len,(*msg).head->src,(*msg).head->type,(*msg).head->subtype,(*msg).context);
			printf("\tparsed to CSV-Key-Value-Pairs: (String-Values) (Number of Pairs: %d)  [Print-Format:] 'KEY' = 'VALUE'\n",InfBrokMsgCSV(msg)->count);
			printf("\t[\n");
			for(i=0;i<InfBrokMsgCSV(msg)->count;i++){
				printf("\t  '%s' = '%s'\n",(((InfBrokMsgCSV(msg)->pairs).string)[i]).key,(((InfBrokMsgCSV(msg)->pairs).string)[i]).val);
			}
			printf("\t]\n");
			break;
		default:
			break;
		}
	}else{
		printfc(gray,"   DEBUG");printfc(DENKR__COLOR_ANSI__DL_LIBS," (Plugin)");printfc(gray,":");printf(" Msg to Debug_print (CSV) not of type CSV\n");
		return FUNC_ERR_BAD_ARG;
	}
	return 0;
}






#undef DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER_INTERFACE__C
#undef NO__DENKR_ESSENTIALS__CONTEXT_BROKER__CONTEXT_BROKER_BROKER_INTERFACE__C__FUNCTIONS
