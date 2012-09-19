#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib_hw1/bitmap.h"
#include "lib_hw1/debug.h"
#include "lib_hw1/hash.h"
#include "lib_hw1/limits.h"
#include "lib_hw1/list.h"
#include "lib_hw1/round.h"
#include "tokenize.h"
#include "main.h"

struct my_head *SearchHandler(struct list *L, char *name);

struct my_head  // ALL Created Use This!
{
	struct list_elem main;
	char *name;
	void *data;
	// list : (struct my_list);
	// hashtable : (struct hash);
	// bitmap : (struct bitmap);
};

struct my_list
{
	struct list_elem prev;
	int number;
	struct list_elem next;
};

struct my_bitmap
{
	struct list_elem prev;
	struct bitmap *data;
	struct list_elem next;
};

void CreateHandler(struct list *L, char **toked, int tokin){
	int rule_size = 3;
	char *rule[] = {
		"list",			// 0
		"hashtable", 	// 1
		"bitmap"		// 2
	};
	struct my_head *new = (
			struct my_head *)calloc(1, sizeof(struct my_head));
	int name_size = 10;
	int choice;
	
	new->name = (char *)calloc(name_size, sizeof(char));

	if(tokin<3) choice = -1;
	else		choice = StringSwitch(&rule, rule_size, toked[1]);

	switch(choice){
		case 0:  // list
			new->data = (void *)calloc(1, sizeof(struct my_list));
			list_init((struct list *)new->data);
			sprintf(new->name, "%s", toked[2]);
			list_push_back(L, &(new->main));
			break;
		case 1:  // hashtable
			new->data = (void *)calloc(1, sizeof(struct hash));
			hash_init((struct hash *)new->data,
					hash_int, NULL, NULL);
			sprintf(new->name, "%s", toked[2]);
			list_push_back(L, &(new->main));
			break;
		case 2:  // bitmap
			if(tokin<4){
				//if(_MY_DEBUG)
					printf("UNSUPPORTED COMMAND!\n");
					break;
			}
			new->data = (void *)bitmap_create(atoi(toked[3]));
			sprintf(new->name, "%s", toked[2]);
			list_push_back(L, &(new->main));
			break;
		case -1:
		default:
			free(new->name);
			free(new);
			//if(_MY_DEBUG)
				printf("UNSUPPORTED COMMAND!\n");
			break;
	}
}

void DeleteHandler(struct list *L, char **toked, int tokin){
	struct my_head *target;
	int type;

	if(tokin<2) type = -1;
	else		type = TypeHandler(target = SearchHandler(L, toked[1]));

	switch(type){
		case 0:  // list
			break;
		case 1:  // hashtable
			break;
		case 2:  // bitmap
			break;
		case -1:
		default:
			if(_MY_DEBUG)
				printf("UNSUPPORTED COMMAND!\n");
			break;
	}

	return ;
}

int TypeHandler(struct my_head *target){
	return -1;
}

struct my_head *SearchHandler(struct list *L, char *name){
	struct my_head *chk;
	struct list_elem *find;
	for(find = list_begin(L); find != list_end(L); find = list_next(find)){
		chk = list_entry(find, struct my_head, main);  	// Get <struct my_head>* by <my_head>.<main>'s location(<find>).
		if(_MY_DEBUG)
			printf("find: '%s' vs '%s'\n", chk->name, name);
		if(!strcmp(chk->name, name))
			break;
	}
	return chk;
}



void lCommandsHandler(char **toked){
	int rule_size = 42;
	char *rule[] = {  // WTF!!!! WHY U NO USE ENUM!!!!!!!
		"list_insert",	// 0
		"list_splice",	// 1
		"list_push",	// 2
		"list_push_front",	// 3
		"list_push_back",	// 4
		"list_remove",	// 5
		"list_pop_front",	// 6
		"list_pop_back",	// 7
		"list_front",	// 8
		"list_back",	// 9
		"list_size",	// 10
		"list_empty",	// 11
		"list_reverse",	// 12
		"list_sort",	// 13
		"list_insert_ordered",	// 14
		"list_unique",	// 15
		"list_max",	// 16
		"list_min",	// 17
		"hash_insert",	// 18
		"hash_replace",	// 19
		"hash_find",	// 20
		"hash_delete",	// 21
		"hash_clear",	// 22
		"hash_size",	// 23
		"hash_empty",	// 24
		"hash_apply",	// 25
		"bitmap_size",	// 26
		"bitmap_set",	// 27
		"bitmap_mark",	// 28
		"bitmap_reset",	// 29
		"bitmap_flip",	// 30
		"bitmap_test",	// 31
		"bitmap_set_all",	// 32
		"bitmap_set_multiple",	// 33
		"bitmap_count",	// 34
		"bitmap_contains",	// 35
		"bitmap_any",	// 36
		"bitmap_none",	// 37
		"bitmap_all",	// 38
		"bitmap_scan",	// 39
		"bitmap_scan_and_flip",	// 40
		"bitmap_dump"	// 41
	};
	switch(StringSwitch(&rule, rule_size, toked[0])){
		case 0:  // 
			break;
		case -1:
		default:
			//if(_MY_DEBUG)
				printf("UNSUPPORTED COMMAND!\n");
	}
}

void TrashAll(struct list *L){
	// Recursively delete all.
	free(L);
}

int main(){
	struct list *L = (struct list *)calloc(1, sizeof(struct list));
	list_init(L);
	while(!InputHandler(L)){}
	TrashAll(L);
	return 0;
}
