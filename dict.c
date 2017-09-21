#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"

typedef struct Dict
{
	LinkedList ** hash_table;
	size_t size;
	size_t num_elem;
} Dict;

Dict * createDict(size_t size)
{
	Dict * dict = malloc(sizeof(Dict));

	dict->size = size;
	dict->hash_table = malloc(sizeof(LinkedList *) * size);
	dict->num_elem = 0;

	for (size_t i = 0; i < size; i++) {
		(dict->hash_table)[i] = createLinkedList(basicIntKey);
	}

	return dict;
}

size_t hash_fcn(size_t m, )

int insertDictData(Dict * dict, void * data)
{
	Node * node = createNode(data);

}



