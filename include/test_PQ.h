#include <stdbool.h>

#ifndef __TEST_PQ_H__
#define __TEST_PQ_H__

/* typedef struct Test */
typedef struct Test_Struct
{
	int a;
	int b;
} Test_Struct;

// ctor and dtor
Test_Struct * testNew(int a, int b);
int testDelete(Test_Struct * test);

/* test comparison functions: */
int gtComp(const void *d1, const void *d2, const void * _, const size_t t_width);
int ltComp(const void *d1, const void *d2, const void * _, const size_t t_width);
bool testEqual(const void *d1, const void *d2);

#endif