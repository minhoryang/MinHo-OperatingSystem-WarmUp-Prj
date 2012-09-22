/**
	@file	tokenize.c
	@date	2012-09-22
	@author	"양민호, 20091631, minhoryang@gmail.com"
	@brief	"User의 Input을 핸들할 수 있도록 도와준다. (Tokenize, StringSwitch)."
*/
#include "main.h"
#define TOKEN_SIZE 5

/**
	@brief
		"잘라야 할때를 정해주자."
	@return
		"True면 잘라야함."
*/
bool ValidateTokenKey(
		char s  ///< "확인하고싶은 한char"
		){
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
			return true;
	return false;
}

/**
	@brief
		"<str>을 한 덩어리만 잘라서 Return한다."
	@remarks
		"제공된 <str>이 자르고 난 다음 잘린 뒤로 이동하게 만들어 지속가능한
		Tokenize을 하게해준다."
	@return
		"자르고 난 한 덩어리의 스트링, 없으면 NULL."
*/
char *Tokenize(
		char **str,  ///< "잘라야 하는 스트링,"
		int *str_size  ///< "의 사이즈."
		){
	char *rets;
	int idx, cnt=0;
	if(_MY_DEBUG)
		printf("%d\n", *str_size);

	///< "1. 자를게 없나?"
	if(!*str_size)
		return NULL;
	rets = (char *)calloc(*str_size, sizeof(char)); 

	for(idx=0; idx<*str_size; idx++){
		///< "2. Null을 만났나?"
		if(!(*str)[idx]){
			*str_size = 0;
			break;
		}
		if(!ValidateTokenKey((*str)[idx]))
			///< "3. 복사!"
			rets[cnt++] = (*str)[idx];
		else{
			///< "4. 토큰을 찾았다!"
			if(ValidateTokenKey((*str)[idx+1]))
				///< "4-a. 두개 이상 찾았다!"
				idx++;
			///< "글자를 자르고 포인터를 그 뒤로 넘긴다."
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

/**
	@brief
		"물어보는 String이 List에서 몇번째인지 알려준다."
	@remarks
		"이걸로 인해 String도 Switch-Case문을 사용할 수 있다."
	@return
		"String이 해당하는 List의 Index."
	@warning
		"warning: passing argument 1 of ‘StringSwitch’ from incompatible pointer type
		과 note: expected ‘char **’ but argument is of type ‘char * (*)[갯수]’에러가
		뜰거임. 근데 무시ㄱㄱ (거슬리긴함)."
*/
int StringSwitch(
		char* list[],  ///< "해당할거라고 예상하는 리스트,"
		int list_size,  ///< "의 크기."
		char *string  ///< "물어보고싶은 String."
		){
	int i;
	for(i=list_size-1;i>=0;i--){
		if(_MY_DEBUG)
			printf("'%s' <?>  %d:'%s'\n", string, i, list[i]);
		if(!strcmp(string, list[i])){
			break;
		}
	}
	return i;
}
