#ifndef __POSITION_H__
#define __POSITION_H__

#include <stdbool.h>
#include <stdlib.h>

typedef struct Position
{
	int x;
	int y;
} Position;

/* Position functions */
Position * positionFactory(const int y, const int x);
int checkPosition(const Position * newPos);
int getHeuristic(const Position * pos_1, const Position * pos_2);
int getManhattanDistance(const Position * pos_1, const Position * pos_2, int * dy, int * dx);
int cmpPosition(const void * d1, const void * d2, const void * table, const size_t t_width);
bool equalPosition(const void * d1, const void * d2);
int findPositionPath(const Position * start, const Position * end, int max_row, int max_col);
int drawPath(Position ** came_from, Position * current, const Position * target, int max_col);

#endif