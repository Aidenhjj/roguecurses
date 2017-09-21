#include <ncurses.h>
#include <stdlib.h>

#include "level.h"

Level saveLevel(const int max_row, const int max_col)
{
	/* outputs a malloc'ed array with the current level state */
	Level level;
	
	level.map = malloc(sizeof(char) * max_col * max_row);
	level.width = max_col;
	level.height = max_row;

	for (int j = 0; j < max_row; j++) {
		for (int i = 0; i < max_col; i++) {
			(level.map)[j][i] = mvinch(j, i);
		}
	}

	return level;
}

int loadLevel(const Level * level)
{
	for (int j = 0; j < level->height; j++) {
		for (int i = 0; i < level->width; i++) {
			mvprintw(j, i, "%c", (level->map)[j][i]);
		}
	}
}

char getLevelIndex(const Level * level, const int y, const int x) 
{
	if ((y < 0) || (y >= level->height) ||
		(x < 0) || (x >= level->width)) {
		return '!';
	}
	return (level->map)[y][x];
}