#include "main.h"
#define TOKEN_SIZE 5

int ValidateTokenKey(char s){
	char token[TOKEN_SIZE] = {
		(char)' ',
		(char)'\n',
		(char)'\t',
		(char)EOF,
		(char)NULL
	};
	int idx;
	for(idx=0;idx<TOKEN_SIZE;idx++)
		if(s == token[idx])
			return 1;
	return 0;
}

char *Tokenize(char **str, int *str_size){
	char *rets;
	int idx, cnt=0;
	if(_MY_DEBUG)
		printf("%d\n", *str_size);

	// 1. No String?
	if(!*str_size)
		return NULL;
	rets = (char *)calloc(*str_size, sizeof(char)); 

	for(idx=0; idx<*str_size; idx++){
		// 2. Check Null?
		if(!(*str)[idx]){
			*str_size = 0;
			break;
		}
		if(!ValidateTokenKey((*str)[idx]))
			// 3. Copy Letter.
			rets[cnt++] = (*str)[idx];
		else{
			// 4. Found Token!
			if(ValidateTokenKey((*str)[idx+1]))
				// 4-a. 2+ Token found!
				idx++;
			// -> Cut words and Reset str to next.
			rets[cnt++] = 0;
			*str = &((*str)[idx+1]);
			break;
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

int StringSwitch(char* list[], int cases, char *string){
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
