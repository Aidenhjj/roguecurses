#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdbool.h>

typedef struct Node Node;

typedef struct Node
{
	Node * next;
	Node * prev;
	void * data;
} Node;

typedef struct LinkedList
{
	Node * nil;// sentinal
	int (*getKey)(const Node * node);// key extracting function
} LinkedList;

Node * createNode(void * data);
int listDeleteNode(LinkedList * list, Node * node);
Node * listSearchKey(LinkedList * list, const int key);
int listInsertNode(LinkedList * list, Node * node);

LinkedList * createLinkedList(int (*getKey)(const Node * node));
int deleteLinkedList(LinkedList * list);
void * listPop(LinkedList * list);
bool listEmpty(LinkedList * list);

// for testing
int basicIntKey(const Node * node);

#endif