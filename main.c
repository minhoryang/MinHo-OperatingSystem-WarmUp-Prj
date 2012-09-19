#include "main.h"

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
			new->type = choice;
			list_init((struct list *)new->data);
			sprintf(new->name, "%s", toked[2]);
			list_push_back(L, &(new->main));
			break;
		case 1:  // hashtable
			new->data = (void *)calloc(1, sizeof(struct hash));
			new->type = choice;
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
			new->type = choice;
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

// NOT YET!
void DeleteHandler(struct list *L, char **toked, int tokin){
	struct my_head *target;
	int type;

	if(tokin<2) type = -1;
	else		type = (target = SearchHandler(L, toked[1]))->type;

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

void DumpHandler(struct list *L, char **toked, int tokin){
	struct my_head *target;
	struct my_list *list;
	struct hash *hash;
	struct bitmap *bitmap;
	int type;
	size_t i;

	if(tokin<2) type = -1;
	else		type = (target = SearchHandler(L, toked[1]))->type;

	switch(type){
		case 0:
			list = (struct my_list *)target->data;
			break;
		case 1:
			hash = (struct hash *)target->data;
			break;
		case 2:
			bitmap = (struct bitmap *)target->data;
			for(i=0;i < bitmap->bit_cnt;i++)
				printf("%d", bitmap_test(bitmap, i));
			printf("\n");
			//bitmap_dump(bitmap);
			break;
		case -1:
		default:
			if(_MY_DEBUG)
				printf("UNSUPPORTED COMMAND!\n");
			break;
	}

	return ;
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
