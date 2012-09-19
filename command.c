#include "main.h"

int InputHandler(struct list *L){
	// Handle Rules!
	int rule_size = 4;
	char *rule[4] = {
		"create",   // 0
		"delete",   // 1
		"dumpdata", // 2
		"quit"      // 3
	};
	// Buffers
	int str_size = 100;
	char *str;
	// Pointers
	char *now, **toked;
	// Indexes
	int i, cnt = 0, ret = 0;


	// 1. Allocate
	str = (char *)calloc(str_size, sizeof(char)); 
	toked = (char **)calloc(str_size, sizeof(char *)); 
	
	// 2. Read
	fgets(str, str_size, stdin);
	if(_MY_DEBUG)
		printf("%s", str);
	
	// 3. Tokenizing
	now=str;
	while(toked[cnt] = Tokenize(&now, &str_size)){
		if(_MY_DEBUG)
			printf("'%s'\n", toked[cnt]);
		cnt++;
	}
	for(i=cnt;i<str_size;i++)
		toked[i] = NULL;

	// 4. Handle Commands
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
			return 1;
		case -1:  // * (commands)
			lCommandsHandler(L, toked, cnt);
			break;
	}

	// 5. Free
	for(i=0;i<cnt;i++){
		free(toked[i]);
	}
	free(toked);
	free(str);
	return ret;
}

void lCommandsHandler(struct list *L, char **toked, int tokin){
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
		"bitmap_dump"	// 41 (work...)
	};
	struct my_head *target;
	int type;

	if(tokin<2) type = -1;
	else		type = (target = SearchHandler(L, toked[1]))->type;

	switch(StringSwitch(&rule, rule_size, toked[0])){
		case 0:  // 
			break;
		case 26:  // bitmap_size
			if(tokin<2 || type==2)
				printf("%d\n",
					bitmap_size((struct bitmap *)target->data)
				);
			break;
		case 27:  // bitmap_set
			if(tokin<4 || type==2)
				bitmap_set(
					(struct bitmap *)target->data,
					atoi(toked[2]),
					!strcmp(toked[3], "true") ? 1 : 0 
				);
			break;
		case 28:  // bitmap_mark
			if(tokin<3 || type==2)
				bitmap_mark(
					(struct bitmap *)target->data,
					atoi(toked[2])
				);
			break;
		case 29:  // bitmap_reset
			if(tokin<3 || type==2)
				bitmap_reset(
					(struct bitmap *)target->data,
					atoi(toked[2])
				);
			break;
		case 30:  // bitmap_flip
			if(tokin<3 || type==2)
				bitmap_flip(
					(struct bitmap *)target->data,
					atoi(toked[2])
				);
			break;
		case 31:  // bitmap_test
			if(tokin<3 || type==2)
				printf("%s\n",
					bitmap_test(
						(struct bitmap *)target->data,
						atoi(toked[2])
					) ? "true" : "false"
				);
			break;
		case 32:  // bitmap_set_all
			if(tokin<3 || type==2)
				bitmap_set_all(
					(struct bitmap *)target->data,
					!strcmp(toked[2], "true") ? 1 : 0 
				);
			break;
		case 33:  // bitmap_set_multiple
			if(tokin<5 || type==2)
				bitmap_set_multiple(
					(struct bitmap *)target->data,
					atoi(toked[2]),
					atoi(toked[3]),
					!strcmp(toked[4], "true") ? 1 : 0 
				);
			break;
		case 34:  // bitmap_count
			if(tokin<5 || type==2)
				printf("%d\n",
					bitmap_count(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3]),
						!strcmp(toked[4], "true") ? 1 : 0
					)
				);
			break;
		case 35:  // bitmap_contains
			if(tokin<5 || type==2)
				printf("%s\n",
					bitmap_contains(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3]),
						!strcmp(toked[4], "true") ? 1 : 0
					) ? "true" : "false"
				);
			break;
		case 36:  // bitmap_any
			if(tokin<4 || type==2)
				printf("%s\n",
					bitmap_any(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3])
					) ? "true" : "false"
				);
			break;
		case 37:  // bitmap_none
			if(tokin<4 || type==2)
				printf("%s\n",
					bitmap_none(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3])
					) ? "true" : "false"
				);
			break;
		case 38:  // bitmap_all
			if(tokin<4 || type==2)
				printf("%s\n",
					bitmap_all(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3])
					) ? "true" : "false"
				);
			break;
		case 39:  // bitmap_scan
			if(tokin<5 || type==2)
				printf("%u\n",
					bitmap_scan(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3]),
						!strcmp(toked[4], "true") ? 1 : 0
					)
				);
			break;
		case 40:  // bitmap_scan_and_flip
			if(tokin<5 || type==2)
				printf("%u\n",
					bitmap_scan_and_flip(
						(struct bitmap *)target->data,
						atoi(toked[2]),
						atoi(toked[3]),
						!strcmp(toked[4], "true") ? 1 : 0
					)
				);
			break;
		case 41:  // bitmap_dump
			if(tokin<2 || type==2)
				bitmap_dump(
					(struct bitmap *)target->data
				);
			break;
		case -1:
		default:
			//if(_MY_DEBUG)
				printf("UNSUPPORTED COMMAND!\n");
	}
}
