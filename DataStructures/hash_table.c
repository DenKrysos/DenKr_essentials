/*
 * hash_table.c
 *
 * Authored by
 * Dennis Krummacker (19.07.2018 - )
 */

#define DENKR_ESSENTIALS__HASH_TABLE__C
#define NO__DENKR_ESSENTIALS__HASH_TABLE__C__FUNCTIONS


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
#include <stdint.h>
#include <math.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
//#include ""
//---------------------------------------------------------------------------------
#include "DenKr_essentials/auxiliary.h"
#include "prime_number.h"
#include "hash_table.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//

//TODO:
// - Create two new Data-structures:
//     -> DenKr_HashTabNum_hash_table and related  -- for numeric Keys
//         -> !! Numeric standalone solutions is done!!
//     -> DenKr_HashTabStr_hash_table and related  -- will be exactly the one like now
// - Change the current into one, the has an additional property: "KeyType" reflecting which one it is
//   -> Change the accessing functions into a way, that as Key they get a void* and according to the KeyType, they automatically treat the table as appropriate
// Why?
//  - The first ones are more performant because of known function-parameters and now KeyType check
//  - The latter one is easier to use and require the user only to care about, while using the _htInit function
// "General" TODO
// - Extend it to be able to pass custom hash-function for Key-Hashing
// - Change to my use of the "Function-Creator-Macro" Construct to DRY up repeated code-segments
// - Extend it to store/index/keep track of all currently stored Keys


//#define DEBUG_HASHTABLE
//#define DEBUG_HASHTABLE_2







static DenKr_HashTabNum_ht_item* DenKr_HashTabNum_new_item(const DenKr_HashTabNum_Key__type k, const void* v, const int val_s){
	DenKr_HashTabNum_ht_item* i = malloc(sizeof(*i));
	i->key = k;
	i->value = malloc(val_s);
	memcpy(i->value,v,val_s);
	i->value_size=val_s;
	return i;
}

static DenKr_HashTab_ht_item* DenKr_HashTab_new_item(const char* k, const void* v, const int val_s){
	DenKr_HashTab_ht_item* i = malloc(sizeof(DenKr_HashTab_ht_item));
	i->key = strdup(k);
	i->value = malloc(val_s);
	memcpy(i->value,v,val_s);
	i->value_size=val_s;
	return i;
}





static void DenKr_HashTabNum_del_item(DenKr_HashTabNum_ht_item* i){
	free(i->value);
	free(i);
}

static void DenKr_HashTab_del_item(DenKr_HashTab_ht_item* i){
	free(i->key);
	free(i->value);
	free(i);
}





//More or less a generalized Version of the function. Amongst others used for resizing, respectively accordingly accessed by the first init-function
static int DenKr_HashTab_htInit_t_resize(DenKr_HashTab_hash_table** target, int min_size, int new_size, int prime1, int prime2){
	*target = malloc(sizeof(**target));

	new_size=DenKr_next_prime(new_size);
	(*target)->size_min = min_size;
	(*target)->size_current = new_size;
	(*target)->prime1=prime1;
	(*target)->prime2=prime2;
	(*target)->count = 0;
	memset(&((*target)->deletedItem),0,sizeof((*target)->deletedItem));
	(*target)->items = calloc((size_t)((*target)->size_current), sizeof(*((*target)->items)));
	return 0;
}
static int DenKr_HashTabNum_htInit_t_resize(DenKr_HashTabNum_hash_table** target, int min_size, int new_size, int prime1){
	*target = malloc(sizeof(**target));

	new_size=DenKr_next_prime(new_size);
	(*target)->size_min = min_size;
	(*target)->size_current = new_size;
	(*target)->prime1=prime1;
	(*target)->count = 0;
	memset(&((*target)->deletedItem),0,sizeof((*target)->deletedItem));
	(*target)->items = calloc((size_t)((*target)->size_current), sizeof(*((*target)->items)));
	return 0;
}





//prime: A prime number larger than the alphabet used by the hashed string.
//entry_c: The number of of entries in the associative array, used by the hash-table to store its items
static int DenKr_HashTab_hash(const char* str, const int prime, const int entry_c){
	long hash = 0;
	const int len_s = strlen(str);
	int i;
	for(i=0;i<len_s;i++){
		hash += (long)pow(prime, len_s - (i+1)) * str[i];
		hash = hash % entry_c;
	}
	return (int)hash;
}

static int DenKr_HashTab_get_hash(const char* s, const int entry_c, const int attempt, DenKr_HashTab_hash_table* hashtab){
	const int hash_a = DenKr_HashTab_hash(s, hashtab->prime1, entry_c);
	const int hash_b = DenKr_HashTab_hash(s, hashtab->prime2, entry_c);
	return (hash_a + (attempt * (hash_b + 1))) % entry_c;
}


static int DenKr_HashTabNum_hash1(const DenKr_HashTabNum_Key__type key, const int entry_c){
	return key % entry_c;
}
static int DenKr_HashTabNum_hash2(const DenKr_HashTabNum_Key__type key, const int prime){
	return prime - (key % prime);
}

static int DenKr_HashTabNum_get_hash(const DenKr_HashTabNum_Key__type k, const int entry_c, const int attempt, DenKr_HashTabNum_hash_table* hashtab){
	const int hash_a = DenKr_HashTabNum_hash1(k, entry_c);
	if(attempt){
		const int hash_b = DenKr_HashTabNum_hash2(k, hashtab->prime1);
		return (hash_a + (attempt * (hash_b + 1))) % entry_c;
	}else{
		return hash_a % entry_c;
	}
}





static void DenKr_HashTab_resize(DenKr_HashTab_hash_table* ht, const int new_size) {
	int i;
	#ifdef DEBUG_HASHTABLE
		printf("Hash-Table: Checking for resize\n");
	#endif
	if(new_size < (ht->size_min)){
		return;
	}
	#ifdef DEBUG_HASHTABLE
		printf("Hash-Table: Resizing\n");
	#endif
	DenKr_HashTab_hash_table* new_ht;
	DenKr_HashTab_htInit_t_resize(&new_ht, ht->size_min, new_size, ht->prime1, ht->prime2);
	{
		DenKr_HashTab_ht_item* item;
		for(i = 0; i < ht->size_current; i++){
			item = ht->items[i];
			if (item != NULL && item != &(ht->deletedItem)) {
				DenKr_HashTab_insert(new_ht, item->key, item->value, item->value_size);
			}
		}
	}

	ht->size_current = new_ht->size_current;
	ht->count = new_ht->count;

	// To delete new_ht, we give it ht's size and items
	const int tmp_size = ht->size_current;
	ht->size_current = new_ht->size_current;
	new_ht->size_current = tmp_size;

	DenKr_HashTab_ht_item** tmp_items = ht->items;
	ht->items = new_ht->items;
	new_ht->items = tmp_items;

	DenKr_HashTab_htFree(new_ht);
}

static void DenKr_HashTab_resize_up(DenKr_HashTab_hash_table* ht) {
    const int new_size = ht->size_current * 2;
    DenKr_HashTab_resize(ht, new_size);
}

static void DenKr_HashTab_resize_down(DenKr_HashTab_hash_table* ht) {
    const int new_size = ht->size_current / 2;
    DenKr_HashTab_resize(ht, new_size);
}





static void DenKr_HashTabNum_resize(DenKr_HashTabNum_hash_table* ht, const int new_size) {
	int i;
	#ifdef DEBUG_HASHTABLE
		printf("Hash-Table: Checking for resize\n");
	#endif
	if(new_size < (ht->size_min)){
		return;
	}
	#ifdef DEBUG_HASHTABLE
		printf("Hash-Table: Resizing\n");
	#endif
	DenKr_HashTabNum_hash_table* new_ht;
	DenKr_HashTabNum_htInit_t_resize(&new_ht, ht->size_min, new_size, ht->prime1);
	{
		DenKr_HashTabNum_ht_item* item;
		for(i = 0; i < ht->size_current; i++){
			item = ht->items[i];
			if (item != NULL && item != &(ht->deletedItem)) {
				DenKr_HashTabNum_insert(new_ht, item->key, item->value, item->value_size);
			}
		}
	}

	ht->size_current = new_ht->size_current;
	ht->count = new_ht->count;

	// To delete new_ht, we give it ht's size and items
	const int tmp_size = ht->size_current;
	ht->size_current = new_ht->size_current;
	new_ht->size_current = tmp_size;

	DenKr_HashTabNum_ht_item** tmp_items = ht->items;
	ht->items = new_ht->items;
	new_ht->items = tmp_items;

	DenKr_HashTabNum_htFree(new_ht);
}

static void DenKr_HashTabNum_resize_up(DenKr_HashTabNum_hash_table* ht) {
    const int new_size = ht->size_current * 2;
    DenKr_HashTabNum_resize(ht, new_size);
}

static void DenKr_HashTabNum_resize_down(DenKr_HashTabNum_hash_table* ht) {
    const int new_size = ht->size_current / 2;
    DenKr_HashTabNum_resize(ht, new_size);
}





int DenKr_HashTab_htInit_t(DenKr_HashTab_hash_table** target, int init_size, int prime1, int prime2){
	init_size=DenKr_next_prime(init_size);
	DenKr_HashTab_htInit_t_resize(target, init_size, init_size, prime1, prime2);
	return 0;
}

int DenKr_HashTabNum_htInit_t(DenKr_HashTabNum_hash_table** target, int init_size, int prime1){
	init_size=DenKr_next_prime(init_size);
//	depr(1,"initsize: %d",init_size)
	DenKr_HashTabNum_htInit_t_resize(target, init_size, init_size, prime1);
	return 0;
}





void DenKr_HashTab_htFree(DenKr_HashTab_hash_table* target){
	int i;
	for (i=0;i<target->size_current;i++) {
		DenKr_HashTab_ht_item* item = target->items[i];
		if(item != NULL){
			DenKr_HashTab_del_item(item);
		}
	}
	free(target->items);
	free(target);
}

void DenKr_HashTabNum_htFree(DenKr_HashTabNum_hash_table* target){
	int i;
	for (i=0;i<target->size_current;i++) {
		DenKr_HashTabNum_ht_item* item = target->items[i];
		if(item != NULL){
			DenKr_HashTabNum_del_item(item);
		}
	}
	free(target->items);
	free(target);
}





// If insert() is told to insert an entry with an already present key, it fills the new key-value-pair in and overrides the previously existent one.
//    See the update() function for "updating/meshing" the entries.
void DenKr_HashTab_insert_t(DenKr_HashTab_hash_table* ht, const char* key, const void* value, const int val_size){
	#ifdef DEBUG_HASHTABLE
		printf("Hash-Table: Inserting Key: %s, size: %d\n",key, val_size);
	#endif
	const int load = ht->count * 100 / ht->size_current;
	if(load > 70){
		DenKr_HashTab_resize_up(ht);
	}
	DenKr_HashTab_ht_item* item = DenKr_HashTab_new_item(key, value, val_size);
	#ifdef DEBUG_HASHTABLE_2
		printf("Hash-Table: New Item on Address: %llu / %llu\n",(unsigned long long)(uintptr_t)item,(unsigned long long)(uintptr_t)(item->value));
	#endif
	int index = DenKr_HashTab_get_hash(item->key, ht->size_current, 0, ht);
	DenKr_HashTab_ht_item* cur_item = (ht->items)[index];
	int i = 1;
	while(cur_item != NULL){
		if(cur_item != &(ht->deletedItem)){
			if(strcmp(cur_item->key, key) == 0){
				DenKr_HashTab_del_item(cur_item);
				(ht->items)[index] = item;
				#ifdef DEBUG_HASHTABLE
					printf("Hash-Table: Inserting at Index (overwriting existing): %d\n",index);
				#endif
				return;
			}
		}else{
			//Reuse deletedItem
			(ht->items)[index] = item;
			ht->count++;
			#ifdef DEBUG_HASHTABLE
				printf("Hash-Table: Inserting at Index (reusing deleted entry): %d\n",index);
			#endif
			return;
		}
        index = DenKr_HashTab_get_hash(item->key, ht->size_current, i, ht);
        cur_item = (ht->items)[index];
        i++;
	}
	(ht->items)[index] = item;
	#ifdef DEBUG_HASHTABLE
		printf("Hash-Table: Inserting at Index: %d\n",index);
	#endif
	ht->count++;
}

void DenKr_HashTabNum_insert_t(DenKr_HashTabNum_hash_table* ht, const DenKr_HashTabNum_Key__type key, const void* value, const int val_size){
	#ifdef DEBUG_HASHTABLE
		printf("Hash-Table: Inserting Key: %llu, size: %d\n",(long long unsigned)key, val_size);
	#endif
	const int load = ht->count * 100 / ht->size_current;
	if(load > 70){
		DenKr_HashTabNum_resize_up(ht);
	}
	DenKr_HashTabNum_ht_item* item = DenKr_HashTabNum_new_item(key, value, val_size);
	#ifdef DEBUG_HASHTABLE_2
		printf("Hash-Table: New Item on Address: %llu / %llu\n",(unsigned long long)(uintptr_t)item,(unsigned long long)(uintptr_t)(item->value));
	#endif
	int index = DenKr_HashTabNum_get_hash(item->key, ht->size_current, 0, ht);
	DenKr_HashTabNum_ht_item* cur_item = (ht->items)[index];
	int i = 1;
	while(cur_item != NULL){
		//TODO: Not totally sure, but with a certain combination of bad hash-function and Data-Set, this could lead to a live-lock. At latest, when extending to the use of custom hash-functions, here should some safety-check be introduced to avoid this. (Tracking of already checked indices (the first one) and check for equality with current)
		if(cur_item != &(ht->deletedItem)){
			if(cur_item->key == key){
				DenKr_HashTabNum_del_item(cur_item);
				(ht->items)[index] = item;
				#ifdef DEBUG_HASHTABLE
					printf("Hash-Table: Inserting at Index (overwriting existing): %d\n",index);
				#endif
				return;
			}
		}else{
			//Reuse deletedItem
			(ht->items)[index] = item;
			ht->count++;
			#ifdef DEBUG_HASHTABLE
				printf("Hash-Table: Inserting at Index (reusing deleted entry): %d\n",index);
			#endif
			return;
		}
        index = DenKr_HashTabNum_get_hash(item->key, ht->size_current, i, ht);
        cur_item = (ht->items)[index];
        i++;
	}
	(ht->items)[index] = item;
	#ifdef DEBUG_HASHTABLE
		printf("Hash-Table: Inserting at Index: %d\n",index);
	#endif
	ht->count++;
}





//DEBUGING, You can delete this outcommented without any harm.
//#include "DenKr_essentials/multi_threading.h"
//static void DenKr_ContextBroker_get_ent_from_HashTab(struct DenKr_InfBroker_HashTab_Entry_Val_t** ht_ent, DenKr_HashTab_hash_table* hashtab, char* context){
//	DenKr_HashTab_ht_item* ht_it;
//	ht_it = DenKr_HashTab_search(hashtab,context);
//	if(ht_it){
//		(*ht_ent)=ht_it->value;
//	}else{
//		*ht_ent=NULL;
//	}
//}
void DenKr_HashTab_insert(DenKr_HashTab_hash_table* ht, const char* key, const void* value, const int val_size){
	DenKr_HashTab_insert_t(ht,key,value,val_size);
	//To do some Post-Steps, mostly for Debugging...
//#define htEnt_arr(HashTabEntry,ArrayIndex) ((HashTabEntry->entries)[ArrayIndex])
//#ifdef DEBUG
//	int i;
//	struct DenKr_InfBroker_HashTab_Entry_Val_t* ht_ent;
//	DenKr_ContextBroker_get_ent_from_HashTab(&ht_ent,ht,"test");
//	printfc(gray,"DEBUG");printf(" Checked Context in Hash-Table: %s\n","test");
//	printfc(gray,"DEBUG");printf(" Number of Entries for this: %d\n",ht_ent->num);
//	for(i=0;i<ht_ent->num;i++){
//		int nothing_to_print=1;
//		printf("\tID: %d",htEnt_arr(ht_ent,i).threadID);
//		if(htEnt_arr(ht_ent,i).iface){
//			nothing_to_print=0;
//			printf(" |  via Interface-Storage: %d\n",(htEnt_arr(ht_ent,i).iface->hidden).ownID);
//		}
//		if(htEnt_arr(ht_ent,i).callback){
//			nothing_to_print=0;
//			printf(" |  Callback-Addr: %llu\n",(htEnt_arr(ht_ent,i).callback));
//		}
//		if(nothing_to_print){puts("");}
//	}
//	//TEMP, remember to delete this:
//	struct DenKr_InfBroker_HashTab_Entry_Val_t* ht_ent2;
//	DenKr_ContextBroker_get_ent_from_HashTab(&ht_ent2,ht,"test_consumer_callback");
//	if(ht_ent2){
//		printfc(gray,"DEBUG");printf(" Number of Entries for test_consumer_callback: %d\n",ht_ent2->num);
//		for(i=0;i<ht_ent2->num;i++){
//			int nothing_to_print=1;
//			printf("\tID: %d",htEnt_arr(ht_ent2,i).threadID);
//			if(htEnt_arr(ht_ent2,i).iface){
//				nothing_to_print=0;
//				printf(" |  via Interface-Storage: %d\n",(htEnt_arr(ht_ent2,i).iface->hidden).ownID);
//			}
//			if(htEnt_arr(ht_ent2,i).callback){
//				nothing_to_print=0;
//				printf(" |  Callback-Addr: %llu\n",(htEnt_arr(ht_ent2,i).callback));
//			}
//			if(nothing_to_print){puts("");}
//		}
//	}
//	printf("\nBoth Addresses:\n%llu\n%llu\n\n\n",ht_ent,ht_ent2);
//#endif
}

void DenKr_HashTabNum_insert(DenKr_HashTabNum_hash_table* ht, const DenKr_HashTabNum_Key__type key, const void* value, const int val_size){
	DenKr_HashTabNum_insert_t(ht,key,value,val_size);
}





// If Item is found: Pointer to item is returned
//    Otherwise: NULL
DenKr_HashTab_ht_item* DenKr_HashTab_search(DenKr_HashTab_hash_table* ht, const char* key){
	#ifdef DEBUG_HASHTABLE
		printf("Hash-Table: Searching Key: %s\n",key);
	#endif
	int index = DenKr_HashTab_get_hash(key, ht->size_current, 0, ht);
	DenKr_HashTab_ht_item* item = (ht->items)[index];
	int i = 1;
	while(item != NULL){
		if (item != &(ht->deletedItem)) {
			if(strcmp(item->key, key) == 0){
				#ifdef DEBUG_HASHTABLE
					printf("Hash-Table: Returning Index: %d\n",index);
				#endif
				return item;
			}
		}
		index = DenKr_HashTab_get_hash(key, ht->size_current, i, ht);
		item = (ht->items)[index];
		i++;
	}
	return NULL;
}

DenKr_HashTabNum_ht_item* DenKr_HashTabNum_search(DenKr_HashTabNum_hash_table* ht, const DenKr_HashTabNum_Key__type key){
	#ifdef DEBUG_HASHTABLE
		printf("Hash-Table: Searching Key: %llu\n",(long long unsigned)key);
	#endif
	int index = DenKr_HashTabNum_get_hash(key, ht->size_current, 0, ht);
	DenKr_HashTabNum_ht_item* item = (ht->items)[index];
	int i = 1;
	while(item != NULL){
		if (item != &(ht->deletedItem)) {
			if(key == item->key){
				#ifdef DEBUG_HASHTABLE
					printf("Hash-Table: Returning Index: %d\n",index);
				#endif
				return item;
			}
		}
		index = DenKr_HashTabNum_get_hash(key, ht->size_current, i, ht);
		item = (ht->items)[index];
		i++;
	}
	return NULL;
}





void DenKr_HashTab_delete(DenKr_HashTab_hash_table* ht, const char* key){
	const int load = ht->count * 100 / ht->size_current;
	if(load < 10){
		DenKr_HashTab_resize_down(ht);
	}
	int index = DenKr_HashTab_get_hash(key, ht->size_current, 0, ht);
	DenKr_HashTab_ht_item* item = (ht->items)[index];
	int i = 1;
	while(item != NULL){
		if(item != &(ht->deletedItem)){
			if(strcmp(item->key, key) == 0){
				DenKr_HashTab_del_item(item);
				(ht->items)[index] = &(ht->deletedItem);
			}
		}
		index = DenKr_HashTab_get_hash(key, ht->size_current, i, ht);
		item = (ht->items)[index];
		i++;
	}
	(ht->count)--;
}

void DenKr_HashTabNum_delete(DenKr_HashTabNum_hash_table* ht, const DenKr_HashTabNum_Key__type key){
	const int load = ht->count * 100 / ht->size_current;
	if(load < 10){
		DenKr_HashTabNum_resize_down(ht);
	}
	int index = DenKr_HashTabNum_get_hash(key, ht->size_current, 0, ht);
	DenKr_HashTabNum_ht_item* item = (ht->items)[index];
	int i = 1;
	while(item != NULL){
		if(item != &(ht->deletedItem)){
			if(key==item->key){
				DenKr_HashTabNum_del_item(item);
				(ht->items)[index] = &(ht->deletedItem);
			}
		}
		index = DenKr_HashTabNum_get_hash(key, ht->size_current, i, ht);
		item = (ht->items)[index];
		i++;
	}
	(ht->count)--;
}





//TO-DO, eventually: Function for updating the value
// But in most cases such a function is useless. To make it really powerful it has to be specifically tightened for
//    special type of data behind the item.
// But this here is more or less a general solution. For specific ones, the using application can implement its own island-solutions
// Or otherwise just: Get Data, modify Data, insert new Data (which overrides)
//void DenKr_HashTab_update(DenKr_HashTab_hash_table* ht, const char* key, const char* value){
//
//}





#undef DENKR_ESSENTIALS__HASH_TABLE__C
#undef NO__DENKR_ESSENTIALS__HASH_TABLE__C__FUNCTIONS
