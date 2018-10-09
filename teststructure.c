#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_unit.h"
//#include "hash_table.h"

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
int put(hash_table *hashtable, void *byte)
{
	unsigned char index;
	index = create_index(byte); 
	if(hashtable->table[index] != NULL) // sees if byte is already in hash and if yes,increases its frequency
	{																													 
		hashtable->table[index]->freqbyte++;
		return 0;
	}
	else if(hashtable->table[index]==NULL)// if not, creates a new node to store it
	{
		element *new_element = (element*) malloc(sizeof(element));
		new_element->byte = malloc(sizeof(unsigned char));
		(*(unsigned char*)new_element->byte) = (*(unsigned char*)byte);
		new_element->freqbyte = 1;
		hashtable->table[index] = new_element;
		return 1;
	}
}

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

void TestHASH()
{
	hash_table *ht = create_hash_table();
	unsigned char chr = 'A';
	put(ht,&chr);
	chr = 'B';
	put(ht,&chr);
	chr = 'C';
	put(ht,&chr);
	chr = 'D';
	put(ht,&chr);
	chr = 'E';
	put(ht,&chr);
	chr = 'A';
	CU_ASSERT('A' == get(ht,&chr));
	chr = 'B';
	CU_ASSERT('B' == get(ht,&chr));
	chr = 'C';
	CU_ASSERT('C' == get(ht,&chr));
	chr = 'D';
	CU_ASSERT('D' == get(ht,&chr));
	chr = 'E';
	CU_ASSERT('E' == get(ht,&chr));
}

int main(int argc, char const *argv[])
{
	CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("TestHASH_test", 0, 0);

    CU_add_test(suite,"TestHASH_fun",TestHASH);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

	return 0;
}