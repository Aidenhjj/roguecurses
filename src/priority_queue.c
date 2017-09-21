#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "priority_queue.h"

extern inline size_t parent(size_t i);
extern inline size_t left(size_t i);
extern inline size_t right(size_t i);

// int blankCmp(const void *d1, const void *d2, const void * void_ptr, const size_t t_width)
// {
// 	// blank cmp function for deleting PQ
// 	return 0;
// }

Priority_Queue * createPQ(const size_t init_size, 
	int (*cmp)(const void * d1, const void * d2, const void * table, const size_t t_width))
{
	Priority_Queue * Q = malloc(sizeof(Priority_Queue));

	Q->cmp = cmp;
	Q->array_size = init_size;
	Q->heap_size = 0;
	Q->array = malloc(sizeof(*(Q->array)) * Q->array_size);

	return (Q);
}

int deletePQ(Priority_Queue * PQ)
{
	if (PQ != NULL) {
		// PQ->cmp = blankCmp;
		// while (!(PQEmpty(PQ))) {
		// 	void * ptr = PQDequeue(PQ, NULL, 0);
		// 	free(ptr);
		// }
		free(PQ->array);
		free(PQ);
		return 1;
	}
	return 0;
}

bool checkPQContains(Priority_Queue * PQ, const void * elem, 
	bool (*areEqual)(const void * d1, const void * d2))
{
	for (int i = 0; i < PQ->heap_size; i++) {
		if (areEqual(PQ->array[i], elem)) {
			return true;
		}
	}
	return false;
}

int PQInsert(Priority_Queue * PQ, const void * elem, const void * table, const size_t t_width)
{
	size_t i;
	void * tmp = NULL;

	if (PQ->heap_size >= PQ->array_size) {
		// need to expand the base array
		fprintf(stderr, "Warning! PQ overflow, doubling size of PQ->array [%d -> %d]\n",
			PQ->array_size, PQ->array_size * 2);
		void ** reallocArray = realloc(PQ->array, sizeof(*(PQ->array)) * 2 * PQ->array_size);
		if (reallocArray == NULL) {
			// realloc failed:
			free(reallocArray);
			return 0;
		}
		else {
			PQ->array = reallocArray;
			PQ->array_size *= 2;
		}
	}

	PQ->array[PQ->heap_size] = (void *) elem;
	i = PQ->heap_size;
	PQ->heap_size++;
	// keep swapping with parent until new elem is in right place:
	while ((i > 0) && 
		PQ->cmp(PQ->array[i], PQ->array[parent(i)], table, t_width) > 0) {

		tmp = PQ->array[i];
		PQ->array[i] = PQ->array[parent(i)];
		PQ->array[parent(i)] = tmp;
		i = parent(i);
	}
	return 1;
}

void * PQTop(const Priority_Queue * PQ)
{
	return PQ->array[0];
}

bool PQEmpty(Priority_Queue * PQ)
{
	if (PQ->heap_size < 1) {
		return true;
	}
	return false;
}

void * PQDequeue(Priority_Queue * PQ, const void * table, const size_t t_width)
{
	void * out;
	if (PQ->heap_size < 1) {
		fprintf(stderr, "Error! Priority queue underflow\n");
		return NULL;
	}
	out = PQ->array[0];
	PQ->array[0] = PQ->array[PQ->heap_size - 1];
	PQ->heap_size--;
	// restore heap property
	PQHeapify(PQ, 0, table, t_width);
	return (out);
}

int PQHeapify(Priority_Queue * PQ, size_t i, const void * table, const size_t t_width)
{
	size_t l = left(i);
	size_t r = right(i);
	size_t largest;
	void * tmp = NULL;

	if ((l < PQ->heap_size) && PQ->cmp(PQ->array[l], PQ->array[i], table, t_width) > 0) {
		largest = l;
	}
	else {
		largest = i;
	}

	if ((r < PQ->heap_size) && PQ->cmp(PQ->array[r], PQ->array[largest], table, t_width) > 0) {
		largest = r;
	}

	if (largest != i) {
		// swap PQ->array[i] and PQ->array[largest]
		tmp = PQ->array[i];
		PQ->array[i] = PQ->array[largest];
		PQ->array[largest] = tmp;
		// Heapify:
		PQHeapify(PQ, largest, table, t_width);
	}
	return 1;
}



