#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include "c_unit.h"


// creates hash table and pointers go to NULL
hash_table* create_hash_table()
{
	int i;
	hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));
	for(i = 0;i < 256; i++)
	{
		new_hash_table->table[i] = NULL;
	}
	return new_hash_table;
}

//attributes index to each sent byte
unsigned char create_index(void *byte)
{
	return *((unsigned char*)byte) % 256;
}

//puts sent byte in its respective place in hash
void put(hash_table *hashtable, void *byte)
{
	unsigned char index;
	index = create_index(byte); 
	if(hashtable->table[index] != NULL) // sees if byte is already in hash and if yes,increases its frequency
	{																													 
		hashtable->table[index]->freqbyte++;
		return;
	}
	else if(hashtable->table[index]==NULL)// if not, creates a new node to store it
	{
		element *new_element = (element*) malloc(sizeof(element));
		new_element->byte = malloc(sizeof(unsigned char));
		(*(unsigned char*)new_element->byte) = (*(unsigned char*)byte);
		new_element->freqbyte = 1;
		hashtable->table[index] = new_element;
	}
}

//sees if the element is in the hash
unsigned char get(hash_table *hashtable,void* byte)
{
	unsigned char index;
	unsigned char error = '\\';
	index = create_index(byte);
	while(hashtable->table[index] != NULL)
	{
		if((*(unsigned char*)hashtable->table[index]->byte) == (*(unsigned char*)byte))
		{
			return (*(unsigned char*)byte);
		}
		index++;
	}
	return error;
}
