#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "linked_list.h"

int main()
{
	printf("--------------------------------\n");
	printf("TESTING linked_list.c\n");
	printf("--------------------------------\n");
	LinkedList * test_list = createLinkedList(basicIntKey);
	int * ptr;
	Node * tmp_node;

	srand(time(NULL));

	printf("IN:\n");
	for (int i = 0; i < 10; i++) {
		ptr = malloc(sizeof(int));
		*ptr = i;
		tmp_node = createNode(ptr);

		listInsertNode(test_list, tmp_node);
		printf("	%d\n", *ptr);
	}
	printf("CHANGE:\n");
	for (int i = 0; i < 10; i++) {
		tmp_node = listSearchKey(test_list, i);

		printf("	%d -> %d\n", *(int*)(tmp_node->data), *(int*)(tmp_node->data)*2);

		*(int*)(tmp_node->data) = *(int*)(tmp_node->data) * 2;
	}

	printf("OUT:\n");
	for (int i = 0; i < 10; i++) {
		tmp_node = listSearchKey(test_list, i);
		if (tmp_node->data) {
			printf("	FOUND	%d\n", *(int*)(tmp_node->data));
		}
		else {
			printf("	N/F	%d\n", i);	
		}
	}
	printf("EMPTYING LIST\n");
	while (!listEmpty(test_list)) {
		ptr = (int*)listPop(test_list);
		printf("	%d\n", *ptr);
		free(ptr);
	}

	printf("FILLING LIST AGAIN:\n");
	for (int i = 0; i < 20; i++) {
		ptr = malloc(sizeof(int));
		*ptr = rand() % 100;
		tmp_node = createNode(ptr);

		listInsertNode(test_list, tmp_node);
		printf("	%d. %d\n", i, *ptr);
	}

	printf("CYCLING LIST MANUALLY:\n");
	tmp_node = test_list->nil->next;
	while (tmp_node != test_list->nil) {
		ptr = (int*)(tmp_node->data);
		printf("	%d\n", *ptr);
		tmp_node = tmp_node->next;
	}
	deleteLinkedList(test_list);

	return 0;
}