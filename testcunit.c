#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100000

typedef struct heap heap;
typedef struct tree tree;
struct heap
{
    int begin;
    int size;
    tree *tree[256];
};

typedef struct tree tree;
typedef struct heap heap;

struct tree
{
    void* byte;//element
    long long unsigned freq;//frequency
    tree *left;
    tree *right;
};


tree* create_new_tree(long long unsigned freq, void* byte)
{
    tree *new_tree = (tree*) malloc(sizeof(tree));
    new_tree->freq = freq;
    new_tree->byte = malloc(sizeof(unsigned char));
    *((unsigned char*)new_tree->byte) = *((unsigned char*)byte);
    new_tree->right = NULL;
    new_tree->left = NULL;
    return new_tree;
}

// creates heap and sets size to 0 and begin to 1
heap* create_heap()
{
    heap *new_heap = (heap*) malloc(sizeof(heap));
    new_heap->begin = 1;
    new_heap->size = 0;
    return new_heap;
}
// swaps the two sent trees
void swap(tree *a, tree *b)
{
	tree *aux;
	aux = a;
	a = b;
	b = aux;
}
// gets index of parent of that index in the heap
int get_parent_i(heap* heap,int i)
{
    return i/2;
}
// gets index of left of that index in the heap
int get_left_i(heap* heap,int i)
{
    return 2*i;
}
// gets index of right of that index in the heap
int get_right_i(heap* heap,int i)
{
    return 2*i + 1;
}

/* puts in heap checking the frequency of the new element to put it in the right place.
 This functions only enqueues the elements that aren't trees yet, creating a new tree and putting in the heap*/
unsigned char enqueue(heap *heap, long long unsigned freq, void* byte)
{
    tree *auxtree = NULL;

    if(heap->size >= MAX_SIZE)
    {
        printf("Overflow\n");
    }
    else
    {
        tree* new_tree = create_new_tree(freq,byte);
        heap->tree[++heap->size] = new_tree;
        int key_i = heap->size;
        int parent_i = get_parent_i(heap,heap->size);
        while(parent_i >= 1 && heap->tree[key_i]->freq > heap->tree[parent_i]->freq)
        {
            auxtree = heap->tree[key_i];
            heap->tree[key_i] = heap->tree[parent_i];
            heap->tree[key_i] = auxtree;
            key_i = parent_i;
            parent_i = get_parent_i(heap,key_i);
        }
        return (*(unsigned char*)byte);
    }
    return 0;
}

// maintains the propriety of heap making sure if the parent node is minor than or equal to the value of its children trees
void heapfy(heap* heap,int i)
{
    int smallest;
  	int left_index = get_left_i(heap,i);
    int right_index = get_right_i(heap,i);
    tree *auxtree;
  	if((left_index <= heap->size) &&  (heap->tree[left_index]->freq < heap->tree[i]->freq))smallest = left_index;	
    else smallest = i;     
    if((right_index <= heap->size) && (heap->tree[right_index]->freq < heap->tree[smallest]->freq)) smallest = right_index;
    if((heap->tree[i]->freq != heap->tree[smallest]->freq))
    {													     
    	auxtree = heap->tree[i];
        heap->tree[i] = heap->tree[smallest];
        heap->tree[smallest] = auxtree;
        heapfy(heap,smallest);
    }
}

void TestHP()
{
    heap* heap = create_heap();
    unsigned char chr = 'A';
    CU_ASSERT('A' == enqueue(heap,10,&chr));
    chr = 'B';
    CU_ASSERT('B' == enqueue(heap,8,&chr));
    chr = 'C';
    CU_ASSERT('C' == enqueue(heap,5,&chr));
    chr = 'D';
    CU_ASSERT('D' == enqueue(heap,17,&chr));
    chr = 'E';
    CU_ASSERT('E' == enqueue(heap,1,&chr));
}

int main(int argc, char const *argv[])
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("TestHP_test", 0, 0);

    CU_add_test(suite,"TestHP_fun",TestHP);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}