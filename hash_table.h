#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include "c_unit.h"

typedef struct hash_table hash_table;
typedef struct element element;

struct element
{
	void *byte;//byte of file
	long long unsigned freqbyte;//frequencies of bytes
};

struct hash_table
{
	element *table[256]; //array of pointers for each element
};


hash_table* create_hash_table();

unsigned char create_index(void *byte);

void put(hash_table *hashtable, void *byte);

unsigned char get(hash_table *hashtable,void* byte);


#endif