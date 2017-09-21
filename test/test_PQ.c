#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "test_PQ.h"
#include "priority_queue.h"

/* TEST SUITE FOR priority_queue.c */

/* Basic Comparison Functions for min/maxPQ */
int gtComp(const void *d1, const void *d2, const void * _, const size_t t_width)
{
	return ((Test_Struct*)d1)->a - ((Test_Struct*)d2)->a;
}

int ltComp(const void *d1, const void *d2, const void * _, const size_t t_width)
{
	return ((Test_Struct*)d2)->a - ((Test_Struct*)d1)->a;
}


Test_Struct * testNew(int a, int b)
{
	Test_Struct * t = malloc(sizeof(Test_Struct));

	t->a = a;
	t->b = b;

	return (t);
}
int testDelete(Test_Struct * test)
{
	if (test != NULL) {
		free(test);
		return 1;
	}
	return 0;
}

bool testEqual(const void *d1, const void *d2)
{
	int test = ltComp(d1, d2, (void*)0, 0);
	return (test == 0);
}

int main()
{
	printf("--------------------------------\n");
	printf("TESTING linked_list.c\n");
	printf("--------------------------------\n");
	for (size_t i = 0; i < 5; i++) {
		printf("i, left(i), right(i), parent(i): %d, %d, %d, %d\n", 
			i, left(i), right(i), parent(i));
	}

	srand(time(NULL));

	Test_Struct * tmp = NULL;

	Priority_Queue * testPQ = createPQ(10, gtComp);

	for (int i = 0; i < 10; i++) {
		tmp = testNew(rand() % 100, i);
		printf("INSERT %d\n", tmp->a);

		PQInsert(testPQ, tmp, (void*)0, 0);
	}

	// should overflow
	int check_int = 250;
	tmp = testNew(check_int, 0);
	PQInsert(testPQ, tmp, (void*)0, 0);

	bool check_bool = checkPQContains(testPQ, tmp, testEqual);

	printf("does testPQ have %d? %s\n", check_int, check_bool ? "true" : "false");

	tmp = PQDequeue(testPQ, (void*)0, 0);
	tmp = testNew(check_int, 0);
	printf("POP: %d\n", tmp->a);

	check_bool = checkPQContains(testPQ, tmp, testEqual);

	printf("does testPQ have %d? %s\n", check_int, check_bool ? "true" : "false");

	printf("==============================\n");

	int g[3][6] = {{1, 2, 3, 4, 5, 6}, {7, 8, 9, 10, 20, 30}, {40, 50, 60, 70, 80, 90}};

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 6; i++) {
			printf("%d = %d\n", g[j][i], *((int *)g + j * 6 + i));
		}

	}

	for (int i = testPQ->heap_size; i > 0; i--) {
		tmp = PQDequeue(testPQ, (void*)0, 0);
		printf("POP: %d\n", tmp->a);
		testDelete(tmp);
	}
	printf("HERE!\n");

	return 0;
}