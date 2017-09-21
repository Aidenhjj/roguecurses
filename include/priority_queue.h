#ifndef __PQUEUE_H__
#define __PQUEUE_H__

/* typedef struct Priority_Queue */
typedef struct Priority_Queue
{
	size_t array_size;
	size_t heap_size;//<= array_size
	void ** array;
	int (*cmp)(const void * d1, const void * d2, const void * table, const size_t t_width);
} Priority_Queue;

/* Priority_Queue specific functions */
// creates and returns a pointer to a Priority_Queue
Priority_Queue * createPQ(const size_t init_size, 
	int (*cmp)(const void * d1, const void * d2, const void * table, const size_t t_width));

// frees up memory allocated to a Priority_Queue
int deletePQ(Priority_Queue * PQ);

// blank cmp function for deleting
// int blankCmp(const void *d1, const void *d2, const void * void_ptr, const size_t t_width);

// enforces the heap property on the PQ (dictated by func pointer added in createPQ())
int PQHeapify(Priority_Queue * PQ, size_t i, const void * table, const size_t t_width);

// inserts an element into PQ
int PQInsert(Priority_Queue * PQ, const void * elem, const void * table, const size_t t_width);

// returns top keyed element in PQ
void * PQTop(const Priority_Queue * PQ);

// returns and removes from PQ the top keyed element
void * PQDequeue(Priority_Queue * PQ, const void * table, const size_t t_width);

// checks if PQ is empty
bool PQEmpty(Priority_Queue * PQ);

// checks the PQ whether it contains elem using areEqual() as test
bool checkPQContains(Priority_Queue * PQ, const void * elem, 
	bool (*areEqual)(const void * d1, const void * d2));

inline size_t parent(size_t i)
{
	return (i - 1)/2;
}

inline size_t left(size_t i)
{
	return (2 * i) + 1;
}

inline size_t right(size_t i)
{
	return (2 * i) + 2;
}

#endif

