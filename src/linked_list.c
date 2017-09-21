#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"

Node * createNode(void * data)
{
	Node * node = malloc(sizeof(Node));
	node->prev = NULL;
	node->next = NULL;
	node->data = data;

	return node;
}

LinkedList * createLinkedList(int (*getKey)(const Node * node))
{
	LinkedList * list = malloc(sizeof(LinkedList));
	list->nil = createNode(NULL);
	list->nil->next = list->nil;
	list->nil->prev = list->nil;

	list->getKey = getKey;

	return list;
}

int deleteLinkedList(LinkedList * list)
{
	Node * next;
	Node * tmp = list->nil->next;
	while (tmp != list->nil) {
		listDeleteNode(list, tmp);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(list);
}

int listDeleteNode(LinkedList * list, Node * node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;

	return 1;
}

void * listPop(LinkedList * list)
{
	Node * out = list->nil->next;
	if (out) {
		listDeleteNode(list, out);
		return out->data;
	}
	return NULL;
}

bool listEmpty(LinkedList * list)
{
	return (list->nil == list->nil->next);
}

Node * listSearchKey(LinkedList * list, const int key)
{
	Node * tmp = list->nil->next;
	while ((tmp != list->nil) && (key != list->getKey(tmp))) {
		tmp = tmp->next;
	}
	return tmp;
}

int listInsertNode(LinkedList * list, Node * node)
{
	node->next = list->nil->next;
	list->nil->next->prev = node;
	list->nil->next = node;
	node->prev = list->nil;
}

// for testing
int basicIntKey(const Node * node)
{
	return *(int*)(node->data);
}

