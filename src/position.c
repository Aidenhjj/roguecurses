#include <limits.h>
#include <math.h>
#include <ncurses.h>
#include <stdlib.h>

#include "position.h"
#include "priority_queue.h"

int checkPosition(const Position * newPos)
{
	/* allows you to check type of char at next position */
	// get char at next position!
	char next = mvinch(newPos->y, newPos->x);
	if (next == '.') {
		return 1;
	}
	else if (next == '#') {
		return 2;
	}
	else {
		return 0;
	}
}

Position * positionFactory(const int y, const int x)
{
	Position * pos = malloc(sizeof(Position));

	pos->y = y;
	pos->x = x;

	return pos;
}

int cmpPosition(const void * d1, const void * d2, const void * table, const size_t t_width)
{
	// NEED TO TEST THIS TO MAKE SURE IT'S WORKING AS INTENDED
	int fScore_d1 = *((int *)table + (((Position*)d1)->y * t_width) + ((Position*)d1)->x);
	int fScore_d2 = *((int *)table + (((Position*)d2)->y * t_width) + ((Position*)d2)->x);
	return fScore_d2 - fScore_d1;
}

bool equalPosition(const void * d1, const void * d2)
{
	return ((((Position*)d1)->y == ((Position*)d2)->y) && 
		(((Position*)d1)->x == ((Position*)d2)->x));
}

int getHeuristic(const Position * pos_1, const Position * pos_2)
{
	int dy = pos_1->y - pos_2->y;
	int dx = pos_1->x - pos_2->x;
	int heur = sqrt((dy * dy) + (dx * dx));
	// fprintf(stderr, "for [%d, %d] to [%d, %d], dy: %d, dx: %d, heur: %d\n", 
	// 				pos_1->y, pos_1->x, pos_2->y, pos_2->x, dy, dx, heur);

	return heur;
}

int getManhattanDistance(const Position * pos_1, const Position * pos_2, int * dy, int * dx) 
{
	*dy = pos_1->y - pos_2->y;
	*dx = pos_1->x - pos_2->x;

	return (*dy + *dx);
}

int findPositionPath(const Position * start, const Position * end, int max_row, int max_col)
{
	/* Implementation of A* Algorithm */
	/* based on https://en.wikipedia.org/wiki/A*_search_algorithm */
	fprintf(stderr, "------------------------------\n");
	fprintf(stderr, "find door path from door[%d, %d] to door [%d, %d]\n", 
					start->y, start->x, end->y, end->x);

	// set up variables
	int heuristic;
	Position * current, * neighbour;
	int neighbour_deltas[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // in format [dy, dx]
	
	// create 2D array of bools for closed_set - true means visited, false means not
	bool closed_set_array[max_row][max_col];

	// create 2D array of Position pointers for came_from (used to retrace steps)
	Position * came_from[max_row][max_col];

	// g_score is the cost of getting from start to every node
	int g_score[max_row][max_col];

	// f_score is the estimated cost of getting from start to finish via node yx
	int f_score[max_row][max_col];

	// initialise f_score, g_score, closed_set_array and came_from
	for (int j = 0; j < max_row; j++) {
		for (int i = 0; i < max_col; i++) {
			g_score[j][i] = INT_MAX;
			f_score[j][i] = INT_MAX;
			closed_set_array[j][i] = false;
			came_from[j][i] = NULL;
		}
	}

	heuristic = getHeuristic(start, end);
	g_score[start->y][start->x] = 0;
	f_score[start->y][start->x] = heuristic;

	// create min PQ for open_set
	Priority_Queue * open_set_PQ = createPQ(100, cmpPosition);
	PQInsert(open_set_PQ, start, f_score, max_col);

	// create min PQ for cleanup of Position pointers:
	Priority_Queue * cleanup_PQ = createPQ(100, cmpPosition);
	PQInsert(cleanup_PQ, start, f_score, max_col);

	// int count = 0;
	// int col = 1;

	while (!PQEmpty(open_set_PQ)) {
		current = PQDequeue(open_set_PQ, f_score, max_col);

		// fprintf(stderr, "*************CONSUMING**************\n");
		// fprintf(stderr, "#-%d current [%d, %d], g_score: %d, f_score: %d\n", 
		// 				count, current->y, current->x, 
		// 				g_score[current->y][current->x],
		// 				f_score[current->y][current->x]);

		// if ((count % 10) == 0) {
		// 	col = ((col + 1)% 7) + 1;
		// }
		// attron(0 | COLOR_PAIR(col));
		// mvprintw(current->y, current->x, "%d", (count++)%10);
		// attroff(0 | COLOR_PAIR(col));
		// use_default_colors();

		heuristic = getHeuristic(current, end);
		if (heuristic == 0) {
			int out = drawPath(& came_from[0][0], current, start, max_col);
			// TO DO: proper cleanup - don't know why these don't cleanup
			// while (!(PQEmpty(cleanup_PQ))) {
			// 	Position * ptr = PQDequeue(cleanup_PQ, f_score, max_col);
			// 	free(ptr);
			// }
			// for (int j = 0; j < max_row; j++) {
			// 	for (int i = 0; i < max_col; i++) {
			// 		void * ptr = came_from[j][i];
			// 		if (ptr != NULL) {
			// 			free(ptr);
			// 		}
			// 	}
			// }
			deletePQ(cleanup_PQ);
			deletePQ(open_set_PQ);

			return out;
		}

		// fprintf(stderr, "--------------------------\n");
		// fprintf(stderr, "next: [%d, %d]\n", current->y, current->x);

		closed_set_array[current->y][current->x] = true;

		// loop through neighbours
		for (int i = 0; i < 4; i++) {
			// neighbour location:
			neighbour = positionFactory(current->y + neighbour_deltas[i][0],
										current->x + neighbour_deltas[i][1]);

			int neighbour_char = mvinch(neighbour->y, neighbour->x);
			// fprintf(stderr, "neighbour: [%d, %d]\n", neighbour->y, neighbour->x);
			
			// check if it's outside map, a wall, or we've already been there
			if ((neighbour->y < 0) || (neighbour->y >= max_row) || 
					(neighbour->x < 0) || (neighbour->x >= max_col) ||
					closed_set_array[neighbour->y][neighbour->x] || 
					neighbour_char == '|' || 
					neighbour_char == '-') {
				continue;
			}

			// fprintf(stderr, "		neighbour [%d, %d], g_score: %d, f_score: %d\n", 
			// 			neighbour->y, neighbour->x, 
			// 			g_score[neighbour->y][neighbour->x],
			// 			f_score[neighbour->y][neighbour->x]);			

			// if not in open_set_PQ, add it
			if (!checkPQContains(open_set_PQ, neighbour, equalPosition)) {
				// create memory and pointer to memory
				neighbour = positionFactory(neighbour->y, neighbour->x);
				PQInsert(open_set_PQ, neighbour, f_score, max_col);
				PQInsert(cleanup_PQ, neighbour, f_score, max_col);
			}

			// check if path to neighbour this way is better than that recorded
			// here, we have also added in a preferance to explore the room first
			int step_cost = 1;
			if (neighbour_char == '.') {
				step_cost = 0;
			}
			else if (neighbour_char == '#') {
				step_cost = 0;
			}
			int tentative_g_score = g_score[current->y][current->x] + step_cost;
			if (tentative_g_score >= g_score[neighbour->y][neighbour->x]) {
				continue;
			}

			// found the best path to this node!
			came_from[neighbour->y][neighbour->x] = current;
			g_score[neighbour->y][neighbour->x] = tentative_g_score;

			heuristic = getHeuristic(neighbour, end);
			f_score[neighbour->y][neighbour->x] = tentative_g_score + heuristic;
		}
	}

	// if we're here, then we've failed!
	fprintf(stderr, "FAILED!!!\n");
	return 0;
}

int drawPath(Position ** came_from, Position * current, const Position * target, int max_col)
{
	int temp_char;
	temp_char = mvinch(current->y, current->x);

	if ((temp_char != '-') && (temp_char != '|') && (temp_char != '.')) {
		mvprintw(current->y, current->x, "#");
	}
	if ((current->y == target->y) && (current->x == target->x)) {
		return 1;
	}
	int prev_y = (came_from[(current->y) * max_col + current->x])->y;
	int prev_x = (came_from[(current->y) * max_col + current->x])->x;
	
	current->y = prev_y;
	current->x = prev_x;

	// sleep(1);

	drawPath(came_from, current, target, max_col);

}