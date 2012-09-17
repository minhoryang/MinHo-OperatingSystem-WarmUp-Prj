#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib_hw1/bitmap.h"
#include "lib_hw1/debug.h"
#include "lib_hw1/hash.h"
#include "lib_hw1/limits.h"
#include "lib_hw1/list.h"
#include "lib_hw1/round.h"

#define _MY_DEBUG 0

int ValidateTokenKey(char s){
	char token[5] = {
		(char)' ',
		(char)'\n',
		(char)'\t',
		(char)EOF,
		(char)NULL
	};
	int token_size = 5;
	int idx;
	for(idx=0;idx<token_size;idx++)
		if(s == token[idx])
			return 1;
	return 0;
}

char *Tokenize(char **str, int *str_size){
	char *rets;
	int idx, cnt=0;  // Only for looping.
	if(_MY_DEBUG)
		printf("%d\n", *str_size);
	if(!*str_size){
		return NULL;
	}
	rets = (char *)calloc(*str_size, sizeof(char)); 
	for(idx=0; idx<*str_size; idx++){
		if(!(*str)[idx]){
			*str_size = 0;
			break;
		}
		if(ValidateTokenKey((*str)[idx])){
			if(ValidateTokenKey((*str)[idx+1])){
				idx++;
			}
			rets[cnt++] = 0;
			*str = &((*str)[idx+1]);
			break;
		}else{
			rets[cnt++] = (*str)[idx];
		}
	}
	*str_size -= cnt;
	if(cnt)
		return rets;
	else{
		free(rets);
		return NULL;
	}
}

int StringSwitch(char *list[], int cases, char *string){
	int i;
	for(i=cases-1;i>=0;i--){
		if(_MY_DEBUG)
			printf("'%s' <?>  %d:'%s'\n", string, i, list[i]);
		if(!strcmp(string, list[i])){
			break;
		}
	}
	return i;
}

int InputHandler(struct list *L){
	// Handle Rules!
	int rule_size = 4;
	char *rule[] = {
		"create",   // 0
		"delete",   // 1
		"dumpdata", // 2
		"quit"      // 3
	};
	// Buffers
	int str_size = 50;
	char *str;
	// Pointers
	char *now, **toked;
	// Indexes
	int i, cnt = 0, ret = 0;

	str = (char *)calloc(str_size - 1, sizeof(char)); 
	toked = (char **)calloc(str_size - 1, sizeof(char *)); 
	
	fgets(str, str_size, stdin);
	if(_MY_DEBUG)
		printf("%s", str);
	
	now=str;
	while(toked[cnt] = Tokenize(&now, &str_size)){
		if(_MY_DEBUG)
			printf("'%s'\n", toked[cnt]);
		cnt++;
	}

	switch(StringSwitch(&rule, rule_size, toked[0])){
		case 0:  // create
			break;
		case 1:  // delete
			break;
		case 2:  // dumpdata
			break;
		case 3:  // quit
			return 1;
		case -1:  // *
			break;
	}

	for(i=0;i<cnt;i++){
		free(toked[i]);
	}
	free(toked);
	free(str);
	return ret;
}

void TrashAll(struct list *list){
	//
}

int main(){
	struct list L;
	list_init(&L);
	while(!InputHandler(&L)){}
	TrashAll(&L);
	return 0;
}
