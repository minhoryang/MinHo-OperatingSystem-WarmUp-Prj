/**
	@file	command.c
	@date	2012-09-22
	@author	"양민호, 20091631, minhoryang@gmail.com"
	@brief	"모든 Commands를 라이브러리와 연결해주는 InputHandler를 포함."
*/
#include "main.h"


/**
	@brief
		"들어온 Input을 처리."
	@remarks
		"Tokenize를 통한 Input을 룰에 따라 처리한다."
	@return
		"QUIT일때만 1, 나머지는 0. (잘못된 Input이라도 0을 리턴한다.)"
*/
bool InputHandler(
		struct list *L	///< "메인자료구조."
		){
	///< "정의된 룰!"
	int rule_size = 4;
	char *rule[4] = {
		"create",   // 0
		"delete",   // 1
		"dumpdata", // 2
		"quit"      // 3
	};
	///< ".Buffers"
	int str_size = 100;
	char *str = (char *)calloc(str_size, sizeof(char)); 
	///< ".Pointers"
	char *now, **toked = (char **)calloc(str_size, sizeof(char *)); 
	///< ".Indexes"
	int i, cnt = 0;
	bool ret = false;

	
	fgets(str, str_size, stdin);
	if(_MY_DEBUG)
		printf("%s", str);
	
	///< "Tokenizing : 들어온 문자열을 나눠서 toked[]에 저장."
	now=str;
	while(toked[cnt] = Tokenize(&now, &str_size)){
		if(_MY_DEBUG)
			printf("'%s'\n", toked[cnt]);
		cnt++;
	}
	for(i=cnt;i<str_size;i++)
		toked[i] = NULL;

	///< "정의된 룰에 따라 핸드러를 할당."
	switch(StringSwitch(&rule, rule_size, toked[0])){
		case 0:  // create
			CreateHandler(L, toked, cnt);
			break;
		case 1:  // delete
			DeleteHandler(L, toked, cnt);
			break;
		case 2:  // dumpdata
			DumpHandler(L, toked, cnt);
			break;
		case 3:  // quit
			return true;
		case -1:  ///< "나머지 모든 추가정의된 룰 핸들러."
			lCommandsHandler(L, toked, cnt);
			break;
	}

	for(i=0;i<cnt;i++){
		free(toked[i]);
	}
	free(toked);
	free(str);
	return ret;
}

/**
	@brief
		"추가정의된 룰을 처리."
	@remarks
		"자료구조별 함수를 처리. (ex/ list_insert, ...)."
*/
void lCommandsHandler(struct list *L, char **toked, int tokin){
	int rule_size = 42;
	char *rule[] = {  // WTF!!!! WHY U NO USE ENUM!!!!!!!
		"list_insert",	// 0 (ok)
		"list_splice",	// 1 (ok)
		"list_push",	// 2 (not found)
		   // ref> http://dcclab.sogang.ac.kr/dcc2/xe/
		   //       ?mid=under_os_2012f&document_srl=40265
		"list_push_front",	// 3 (ok)
		"list_push_back",	// 4 (ok)
		"list_remove",	// 5 (ok)
		"list_pop_front",	// 6 (ok)
		"list_pop_back",	// 7 (ok)
		"list_front",	// 8 (ok)
		"list_back",	// 9 (ok)
		"list_size",	// 10 (ok)
		"list_empty",	// 11 (ok)
		"list_reverse",	// 12 (ok
		"list_sort",	// 13 (ok)
		"list_insert_ordered",	// 14 (ok)
		"list_unique",	// 15 (ok)
		"list_max",	// 16 (ok)
		"list_min",	// 17 (ok)
		"hash_insert",	// 18 (ok)
		"hash_replace",	// 19 (ok)
		"hash_find",	// 20 (ok)
		"hash_delete",	// 21 (ok)
		"hash_clear",	// 22 (ok)
		"hash_size",	// 23 (ok)
		"hash_empty",	// 24 (ok)
		"hash_apply",	// 25 (ok)
		"bitmap_size",	// 26 (ok)
		"bitmap_set",	// 27 (ok)
		"bitmap_mark",	// 28 (ok)
		"bitmap_reset",	// 29 (ok)
		"bitmap_flip",	// 30 (ok)
		"bitmap_test",	// 31 (ok)
		"bitmap_set_all",	// 32 (ok)
		"bitmap_set_multiple",	// 33 (ok)
		"bitmap_count",	// 34 (ok)
		"bitmap_contains",	// 35 (ok)
		"bitmap_any",	// 36 (ok)
		"bitmap_none",	// 37 (ok)
		"bitmap_all",	// 38 (ok)
		"bitmap_scan",	// 39 (ok)
		"bitmap_scan_and_flip",	// 40 (ok)
		"bitmap_dump"	// 41 (ok)
	};
	struct my_head *target;  // GLOBAL toked[1]
	int type;  // GLOBAL type of FoundOne.
	struct my_head *duplicates;
	struct my_list *cur_list, *new_list;
	struct my_hash *cur_hash, *new_hash;
	struct list_elem *find, *first, *last;

	if(tokin==1) type = -1;
	else		type = (target = SearchHandler(L, toked[1]))->type;

	switch(StringSwitch(&rule, rule_size, toked[0])){
		case 0:  // list_insert
			if(tokin==4 && type==0){
				// <!-- FIND -th Object.
				cur_list = list_entry(
						(((struct list *)(target->data))->head).next,
						struct my_list, main);
				for(type=0; type < atoi(toked[2]); type++)
					cur_list = list_entry(
							(cur_list->main).next, struct my_list, main);
				// -->
				new_list = (struct my_list *)calloc(1, sizeof(struct my_list));
				new_list->number = atoi(toked[3]);
				list_insert(cur_list, &(new_list->main));
			}
			break;
		case 1:  // list_splice
			if(tokin==6 && type==0){
				find = (  // before
					((struct list *)(target->data))->head).next;
				for(type=0; type < atoi(toked[2]); type++)
					find = find->next;
				first = (last = (
					((struct list *)(SearchHandler(L, toked[3])->data))->head).next);
				for(type=0; type < atoi(toked[4]); type++)
					first = first->next;
				for(type=0; type < atoi(toked[5]); type++)
					last = last->next;
				list_splice(find, first, last);
			}
			break;
		//case 2:
		case 3:  // list_push_front
			if(tokin==3 && type==0){
				new_list = (struct my_list *)calloc(1, sizeof(struct my_list));
				new_list->number = atoi(toked[2]);
				list_push_front((struct list *)target->data, &(new_list->main));
			}
			break;
		case 4:  // list_push_back
			if(tokin==3 && type==0){
				new_list = (struct my_list *)calloc(1, sizeof(struct my_list));
				new_list->number = atoi(toked[2]);
				list_push_back((struct list *)target->data, &(new_list->main));
			}
			break;
		case 5:  // list_remove
			if(tokin==3 && type==0){
				cur_list = list_entry(
						(((struct list *)(target->data))->head).next,
						struct my_list, main);
				for(type=0; type < atoi(toked[2]); type++)
					cur_list = list_entry(
							(cur_list->main).next,
							struct my_list,
							main);    // REVIEW: NO NEED TO DO IT! REDUCE COST!
				list_remove(cur_list);
			}
			break;
		case 6:  // list_pop_front
			if(tokin==2 && type==0)
				list_pop_front((struct list*)(target->data) );
			break;
		case 7:  // list_pop_back
			if(tokin==2 && type==0)
				list_pop_back((struct list*)(target->data) );
			break;
		case 8:  // list_front
			if(tokin==2 && type==0)
				printf("%d\n", list_entry(
									list_front((struct list*)(target->data)),
									struct my_list, main)->number );
			break;
		case 9:  // list_back
			if(tokin==2 && type==0)
				printf("%d\n", list_entry(
									list_back((struct list*)(target->data)),
									struct my_list, main)->number );
			break;
		case 10:  // list_size
			if(tokin==2 && type==0)
				printf("%u\n", list_size((struct list*)(target->data)) );
			break;
		case 11:  // list_empty
			if(tokin==2 && type==0)
				printf("%s\n", (
					list_empty((struct list*)(target->data))
					) ? "true" : "false" );
			break;
		case 12:  // list_reverse
			if(tokin==2 && type==0)
				list_reverse((struct list*)(target->data));
			break;
		case 13:  // list_sort
			if(tokin==2 && type==0)
				list_sort((struct list*)(target->data), my_list_less_func, NULL);
			break;
		case 14:  // list_insert_ordered
			if(tokin==3 && type==0){
				new_list = (struct my_list *)calloc(1, sizeof(struct my_list));
				new_list->number = atoi(toked[2]);
				list_insert_ordered(
						(struct list*)(target->data),
						&(new_list->main),
						my_list_less_func,
						NULL);
			}
			break;
		case 15:  // list_unique
			if(tokin<4 && type==0){
				if(tokin==2)
					list_unique(
						(struct list*)(target->data),
						(struct list*)NULL,
						my_list_less_func,
						NULL);
				else if(((duplicates = SearchHandler(L, toked[2]))->type)==0)
					list_unique(
						(struct list*)(target->data),
						(struct list*)(duplicates->data),
						my_list_less_func,
						NULL);
				//else break;
			}
			break;
		case 16:  // list_max
			if(tokin==2 && type==0)
				printf("%d\n", list_entry(
							list_max((struct list*)(target->data),
								my_list_less_func, NULL),
							struct my_list, main)->number );
			break;
		case 17:  // list_min
			if(tokin==2 && type==0)
				printf("%d\n", list_entry(
							list_min((struct list*)(target->data),
								my_list_less_func, NULL),
							struct my_list, main)->number );
			break;
		case 18:  // hash_insert	
			if(tokin==3 && type==1){
				new_hash = (struct my_hash *)calloc(1, sizeof(struct my_hash));
				new_hash->number = atoi(toked[2]);
				if(_MY_DEBUG) printf("new: %x\n", (unsigned)new_hash);
				hash_insert((struct hash *)target->data, &(new_hash->main));
			}
			break;
		case 19:  // hash_replace
			if(tokin==3 && type==1){
				new_hash = (struct my_hash *)calloc(1, sizeof(struct my_hash));
				new_hash->number = atoi(toked[2]);
				if(_MY_DEBUG) printf("new: %x\n", (unsigned)new_hash);
				hash_replace((struct hash *)target->data, &(new_hash->main));
			}
			break;
		case 20:  // hash_find
			if(tokin==3 && type==1){
				new_hash = (struct my_hash *)calloc(1, sizeof(struct my_hash));
				new_hash->number = atoi(toked[2]);
				if(_MY_DEBUG) printf("new: %x\n", (unsigned)new_hash);
				cur_hash = hash_find((struct hash *)(target->data), &(new_hash->main));
				if(cur_hash) printf("%d\n", cur_hash->number);
			}
			break;
		case 21:  // hash_delete
			if(tokin==3 && type==1){
				new_hash = (struct my_hash *)calloc(1, sizeof(struct my_hash));
				new_hash->number = atoi(toked[2]);
				if(_MY_DEBUG) printf("new: %x\n", (unsigned)new_hash);
				hash_delete((struct hash *)(target->data), &(new_hash->main));
			}
			break;
		case 22:  // hash_clear
			if(tokin==2 && type==1){
				hash_clear(
						(struct hash *)(target->data),
						my_hash_action_func_destructor);
			}
			break;
		case 23:  // hash_size
			if(tokin==2 && type==1){
				printf("%u\n", hash_size((struct hash *)(target->data)));
			}
			break;
		case 24:  // hash_empty
			if(tokin==2 && type==1){
				printf("%s\n",
						hash_empty((struct hash *)(target->data))?"true":"false");
			}
			break;
		case 25:  // hash_apply
			if(tokin==3 && type==1){
				hash_apply(
					(struct hash *)(target->data),
					MyHashActionsHandler(toked[2]));
			}
			break;
		case 26:  // bitmap_size
			if(tokin==2 && type==2)
				printf("%d\n",
					bitmap_size((struct bitmap *)target->data) );
			break;
		case 27:  // bitmap_set
			if(tokin==4 && type==2)
				bitmap_set(
					(struct bitmap *)target->data,
					atoi(toked[2]),
					!strcmp(toked[3], "true") ? 1 : 0 );
			break;
		case 28:  // bitmap_mark
			if(tokin==3 && type==2)
				bitmap_mark(
					(struct bitmap *)target->data,
					atoi(toked[2]) );
			break;
		case 29:  // bitmap_reset
			if(tokin==3 && type==2)
				bitmap_reset(
					(struct bitmap *)target->data,
					atoi(toked[2]) );
			break;
		case 30:  // bitmap_flip
			if(tokin==3 && type==2)
				bitmap_flip(
					(struct bitmap *)target->data,
					atoi(toked[2]) );
			break;
		case 31:  // bitmap_test
			if(tokin==3 && type==2)
				printf("%s\n",
					bitmap_test(
						(struct bitmap *)target->data,
						atoi(toked[2])
					) ? "true" : "false" );
			break;
		case 32:  // bitmap_set_all
			if(tokin==3 && type==2)
				bitmap_set_all(
					(struct bitmap *)target->data,
					!strcmp(toked[2], "true") ? 1 : 0 );
			break;
		case 33:  // bitmap_set_multiple
			if(tokin==5 && type==2)
				bitmap_set_multiple(
					(struct bitmap *)target->data,
					atoi(toked[2]),
					atoi(toked[3]),
					!strcmp(toked[4], "true") ? 1 : 0 );
			break;
		case 34:  // bitmap_count
			if(tokin==5 && type==2)
				printf("%d\n",
					bitmap_count(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3]),
						!strcmp(toked[4], "true") ? 1 : 0)	);
			break;
		case 35:  // bitmap_contains
			if(tokin==5 && type==2)
				printf("%s\n",
					bitmap_contains(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3]),
						!strcmp(toked[4], "true") ? 1 : 0
					) ? "true" : "false" );
			break;
		case 36:  // bitmap_any
			if(tokin==4 && type==2)
				printf("%s\n",
					bitmap_any(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3])
					) ? "true" : "false" );
			break;
		case 37:  // bitmap_none
			if(tokin==4 && type==2)
				printf("%s\n",
					bitmap_none(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3])
					) ? "true" : "false" );
			break;
		case 38:  // bitmap_all
			if(tokin==4 && type==2)
				printf("%s\n",
					bitmap_all(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3])
					) ? "true" : "false" );
			break;
		case 39:  // bitmap_scan
			if(tokin==5 && type==2)
				printf("%u\n",
					bitmap_scan(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3]),
						!strcmp(toked[4], "true") ? 1 : 0) );
			break;
		case 40:  // bitmap_scan_and_flip
			if(tokin==5 && type==2)
				printf("%u\n",
					bitmap_scan_and_flip(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3]),
						!strcmp(toked[4], "true") ? 1 : 0) );
			break;
		case 41:  // bitmap_dump
			if(tokin==2 && type==2)
				bitmap_dump((struct bitmap *)target->data);
			break;
		case -1:
		default:
			if(_MY_DEBUG)
				printf("UNSUPPORTED COMMAND!\n");
	}
}

hash_action_func *MyHashActionsHandler(char *toked){
	int rule_size = 2;
	char *rule[2] = {
		"square",   // 0
		"triple"   // 1
	};
	switch(StringSwitch(&rule, rule_size, toked)){
		case 0:
			return my_hash_action_func_square;
		case 1:
			return my_hash_action_func_triple;
		default:
			return NULL;
	}
}
