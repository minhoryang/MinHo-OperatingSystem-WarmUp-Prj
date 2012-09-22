/**
	@file	basic_handler.c
	@date	2012-09-22
	@author	"양민호, 20091631, minhoryang@gmail.com"
	@brief	"Create/Delete/Dump 핸들러를 포함."
*/
#include "main.h"

/**
	@brief
		"요구되는 자료구조를 생성Create한다."
	@remarks
		"List와 Hashtable, Bitmap을 메인자료구조에 붙여준다."
*/
void CreateHandler(
		struct list *L,  ///< "메인자료구조."
		char **toked,  ///< "Tokenize된 User의 Input Array."
		int tokin  ///< "Tokenize된 User의 Input 갯수."
		){
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
					my_hash_hash_func, my_hash_less_func, NULL);
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

/**
	@brief
		"요구되는 자료구조를 삭제Delete한다."
	@remarks
		"지정된 List와 Hashtable, Bitmap을 메인자료구조에서 제거한다."
	@warning
*/
void DeleteHandler(
		struct list *L,  ///< "메인자료구조."
		char **toked,  ///< "Tokenize된 User의 Input Array."
		int tokin  ///< "Tokenize된 User의 Input 갯수."
		){
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

/**
	@brief
		"요구되는 자료구조를 출력Dump한다."
	@remarks
		"지정된 List와 Hashtable, Bitmap을 보여준다."
*/
void DumpHandler(
		struct list *L,  ///< "메인자료구조."
		char **toked,  ///< "Tokenize된 User의 Input Array."
		int tokin  ///< "Tokenize된 User의 Input 갯수."
		){
	struct my_head *target;
	int type;
	// Used for <LIST>
	struct list *list;
	struct list_elem *find; // list
	struct my_list *my_list; // my_list
	// Used for <BITMAP>
	struct bitmap *bitmap;
	size_t i;
	// Used for <HASHTABLE>
	struct hash *hash;
	struct hash_iterator hi;
	struct my_hash *my_hash;
	// Used for printing
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
			free(str);
			break;
		case 1:
			str = (char *)calloc(str_size, sizeof(char));
			hash = (struct hash *)target->data;
			hash_first(&hi, hash);
			while(hash_next(&hi)){
				my_hash = hash_entry(hash_cur(&hi), struct my_hash, main);
				if(_MY_DEBUG) printf("found: %x\n", (unsigned)my_hash);
				str_now += sprintf(str + str_now, "%d ", my_hash->number);
				type = 0;  // reuse this as flag.
			}
			if(!type) str_now += sprintf(str + str_now, "\n");
			printf("%s", str);
			free(str);
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

/**
	@brief
		"요구되는 자료구조를 검색한다."
	@remarks
		"지정된 List와 Hashtable, Bitmap을 메인자료구조에서 찾아준다."
	@return
		"찾은 자료구조."
*/
struct my_head *SearchHandler(
		struct list *L,  ///< "메인자료구조."
		char *name  ///< "찾고싶은 자료구조 이름."
		){
	struct my_head *chk;
	struct list_elem *find;
	for(find = list_begin(L); find != list_end(L); find = list_next(find)){
		// Get <struct my_head>* by <my_head>.<main>'s location(<find>).
		chk = list_entry(find, struct my_head, main);
		if(_MY_DEBUG)
			printf("find: '%s' vs '%s'\n", chk->name, name);
		if(!strcmp(chk->name, name))
			break;
	}
	return chk;
}

/**
	@brief
		"프로그램 종료이후 모든 자료구조를 정리한다."
	@warning
*/
void TrashAllHandler(struct list *L){
	// Recursively delete all.
	free(L);
}

