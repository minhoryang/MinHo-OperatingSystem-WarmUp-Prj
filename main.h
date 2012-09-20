#ifndef _MY_DEBUG
  #define _MY_DEBUG 0
#endif

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
	// 0. list : (struct my_list);
	// 1. hashtable : (struct hash);
	// 2. bitmap : (struct bitmap);
};

struct my_list
{
	struct list_elem main;
	int number;
};

// from lib_hw1/bitmap.c
typedef unsigned long elem_type;
struct bitmap
{
    size_t bit_cnt;     /* Number of bits. */
    elem_type *bits;    /* Elements that represent bits. */
};

// main.c
void CreateHandler(struct list *L, char **toked, int tokin);
void DeleteHandler(struct list *L, char **toked, int tokin);
void DumpHandler(struct list *L, char **toked, int tokin);
struct my_head *SearchHandler(struct list *L, char *name);
void TrashAll(struct list *L);

// command.c
int InputHandler(struct list *L);
void lCommandsHandler(struct list *L, char **toked, int tokin);

// tokenize.c
int ValidateTokenKey(char s);
char *Tokenize(char **str, int *str_size);
int StringSwitch(char* list[], int cases, char *string);
