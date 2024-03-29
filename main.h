#ifndef _MY_DEBUG
  #define _MY_DEBUG 0
#endif

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib_hw1/bitmap.h"
#include "lib_hw1/debug.h"
#include "lib_hw1/hash.h"
#include "lib_hw1/limits.h"
#include "lib_hw1/list.h"
#include "lib_hw1/round.h"

struct my_head  // ALL Created Use This!
{
	struct list_elem main;
	char *name;
	int type;  // WHY U NO HAVE type_of();?!
	void *data;
	// 0. list : (struct list);
	// 1. hashtable : (struct hash);
	// 2. bitmap : (struct bitmap);
};

struct my_list
{
	struct list_elem main;
	int number;
};

struct my_hash
{
	struct hash_elem main;
	int number;
};

// -- copied from lib_hw1/bitmap.c
	typedef unsigned long elem_type;
	struct bitmap
	{
	    size_t bit_cnt;     /* Number of bits. */
	    elem_type *bits;    /* Elements that represent bits. */
	};
// --

// basic_handler.c
void CreateHandler(struct list *L, char **toked, int tokin);
void DeleteHandler(struct list *L, char **toked, int tokin);
void DumpHandler(struct list *L, char **toked, int tokin);
struct my_head *SearchHandler(struct list *L, char *name);
void TrashAllHandler(struct list *L);

// input_handler.c
bool InputHandler(struct list *L);
void lCommandsHandler(struct list *L, char **toked, int tokin);
hash_action_func *MyHashActionsHandler(char *toked);

// tokenize.c
bool ValidateTokenKey(char s);
char *Tokenize(char **str, int *str_size);
int StringSwitch(char* list[], int cases, char *string);

// my_funcs.c
bool my_list_less_func (const struct list_elem *a,
						const struct list_elem *b,
                        void *aux);
unsigned my_hash_hash_func (const struct hash_elem *e, void *aux);
bool my_hash_less_func (
		const struct hash_elem *a,
		const struct hash_elem *b,
		void *aux);
void my_hash_action_func_destructor (struct hash_elem *e, void *aux);
void my_hash_action_func_square (struct hash_elem *e, void *aux);
void my_hash_action_func_triple (struct hash_elem *e, void *aux);
void my_list_swap(struct list_elem *a, struct list_elem *b);
void my_list_shuffle(struct list *L);
void my_bitmap_expand(struct bitmap *bitmap, int size);
unsigned my_hash_int_2(int i);
