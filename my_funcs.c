/**
	@file	my_funcs.c
	@date	2012-09-22
	@author	"양민호, 20091631, minhoryang@gmail.com"
	@brief	"Skeleton만 있던 함수를 내가 채워놓은 파일."
*/
#include "main.h"

/**
	@brief
		"List_Less_Func, List를 비교한다."
	@remarks
		"Define된 Function Rule에 맞게 List_Less_Func를 구현하였다."
	@return
		"True면 a가 더 작은거다."
*/
bool my_list_less_func (
		const struct list_elem *a,
		const struct list_elem *b,
        void *aux
		){
	struct my_list *my_a = list_entry(a, struct my_list, main);
	struct my_list *my_b = list_entry(b, struct my_list, main);
	if(0) printf("%x\n", (unsigned int)aux);  // set as used.
	if(my_a->number < my_b->number) return true;
	else return false;
}

/**
	@brief
		"Hash_Hash_Func, Hash값을 생성한다."
	@remarks
		"Define된 Function Rule에 맞게 Hash_Hash_Func를 구현하였다."
	@return
		"제공된 Hash_Elem에 대한 Hash값."
*/
unsigned my_hash_hash_func (
		const struct hash_elem *e,
		void *aux
		){
	struct my_hash* wanted = hash_entry(e, struct my_hash, main);
	if(0) printf("%x\n", (unsigned int)aux);  // set as used.
	return hash_int(wanted->number) % 4;
}


/**
	@brief
		"Hash_Less_Func, Hash를 비교한다."
	@remarks
		"Define된 Function Rule에 맞게 Hash_Less_Func를 구현하였다."
	@return
		"True면 a가 더 작은거다."
*/
bool my_hash_less_func (
		const struct hash_elem *a,
		const struct hash_elem *b,
		void *aux){
	struct my_hash *my_a = hash_entry(a, struct my_hash, main);
	struct my_hash *my_b = hash_entry(b, struct my_hash, main);
	if(0) printf("%x\n", (unsigned int)aux);  // set as used.
	if(my_a->number < my_b->number) return true;
	else return false;
}

/**
	@brief
		"Hash_Action_Func:Destructor, Hash를 제거한다."
	@remarks
		"Define된 Function Rule에 맞게 Hash_Action_Func를 구현하였다.
		Hash_Clear()를 위한 Destructor이다."
*/
void my_hash_action_func_destructor (
		struct hash_elem *e,
		void *aux
		){
	struct my_hash *my_hash = hash_entry(e, struct my_hash, main);
	if(0) printf("%x\n", (unsigned int)aux);  // set as used.
	free(my_hash);
	return ;
}

/**
	@brief
		"Hash_Action_Func:Square, Hash의 값을 제곱한다."
	@remarks
		"Define된 Function Rule에 맞게 Hash_Action_Func를 구현하였다.
		Hash_Apply에서 쓸 수 있는 제곱함수다."
*/
void my_hash_action_func_square (
		struct hash_elem *e,
		void *aux
		){
	struct my_hash *my_hash = hash_entry(e, struct my_hash, main);
	if(0) printf("%x\n", (unsigned int)aux);  // set as used.
	my_hash->number = my_hash->number * my_hash->number;
	return ;
}

/**
	@brief
		"Hash_Action_Func:Triple, Hash의 값을 세제곱한다."
	@remarks
		"Define된 Function Rule에 맞게 Hash_Action_Func를 구현하였다.
		Hash_Apply에서 쓸 수 있는 세제곱함수다."
*/
void my_hash_action_func_triple (
		struct hash_elem *e,
		void *aux
		){
	struct my_hash *my_hash = hash_entry(e, struct my_hash, main);
	if(0) printf("%x\n", (unsigned int)aux);  // set as used.
	my_hash->number = my_hash->number * my_hash->number * my_hash->number;
	return ;
}
