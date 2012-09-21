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
			new->data = (void *)calloc(1, sizeof(struct list));
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
			bitmap_destroy((struct bitmap *)target->data);
			free(target);
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
	struct hash *hash;
	int type;
	// Used for BITMAP
	struct bitmap *bitmap;
	size_t i;
	// Used for list
	struct list *list;
	struct list_elem *find; // list
	struct my_list *my_list; // my_list
	int str_size = 100;
	int str_now = 0;
	char *str;

	if(tokin<2) type = -1;
	else		type = (target = SearchHandler(L, toked[1]))->type;

	switch(type){
		case 0:
			str = (char *)calloc(str_size, sizeof(char));
			list = (struct list *)(target->data);
			// <!-- FIND by looping.
			for(find = list_begin(list);  // ELEM CONTROL
				find != list_end(list);
				find = list_next(find)){
					my_list = list_entry(find, struct my_list, main);
					str_now += sprintf(str + str_now, "%d ", my_list->number);
					type = 1;  // reuse this as flag.
			}
			// -->
			if(type) str_now += sprintf(str + str_now, "\n");
			printf("%s", str);
			break;
		case 1:
			hash = (struct hash *)target->data;
			break;
		case 2:
			bitmap = (struct bitmap *)target->data;
			for(i=0;i < bitmap->bit_cnt;i++)
				printf("%d", bitmap_test(bitmap, i));
			printf("\n");
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

// NEW!
bool my_list_less_func (const struct list_elem *a,
						const struct list_elem *b,
                        void *aux){
	struct my_list *my_a = list_entry(a, struct my_list, main);
	struct my_list *my_b = list_entry(b, struct my_list, main);
	if(0) printf("%x\n", (void *)aux);  // set as used.
	if(my_a->number < my_b->number) return true;
	else return false;
}
