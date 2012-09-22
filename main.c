/**
	@file	main.c
	@date	2012-09-22
	@author	"양민호, 20091631, minhoryang@gmail.com"
	@brief	"Pintos Data Structure Analysis를 위한 CLI."
*/
#include "main.h"

int main(){
	struct list *L = (struct list *)calloc(1, sizeof(struct list));
	list_init(L);
	while(!InputHandler(L)){}
	TrashAllHandler(L);
	return 0;
}
