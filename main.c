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

struct my_head
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
	struct my_head *new = (struct my_head *)calloc(1, sizeof(struct my_head));
	void *data;
	int name_size = 10;
	int choice;
	
	new->name = (char *)calloc(name_size, sizeof(char));

	if(tokin<3) choice = -1;
	else choice = StringSwitch(&rule, rule_size, toked[1]);

	switch(choice){
		case 0:  // list
			data = (void *)calloc(1, sizeof(struct my_list));
			list_init((struct list *)data);

			strcpy(new->name, toked[2]);
			new->data = data;

			list_push_back(L, &(new->main));
			break;
		case 1:  // hashtable
			data = (void *)calloc(1, sizeof(struct hash));
			hash_init((struct hash *)data,
					hash_int, NULL, NULL);

			strcpy(new->name, toked[2]);
			new->data = data;

			list_push_back(L, &(new->main));
			break;
		case 2:  // bitmap
			if(tokin<4)
				//if(_MY_DEBUG)
					printf("UNSUPPORTED COMMAND!\n");
			data = (void *)bitmap_create(atoi(toked[3]));
			strcpy(new->name, toked[2]);
			new->data = data;
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


void lCommandsHandler(char **toked){
	int rule_size = 1;
	char *rule[] = {
		"asdf"      // 0
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

void TrashAll(struct list *list){
	free(list);
}

int main(){
	struct list *L = (struct list *)calloc(1, sizeof(struct list));
	list_init(L);
	while(!InputHandler(L)){}
	TrashAll(L);
	return 0;
}
