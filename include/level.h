#ifndef __LEVEL_H__
#define __LEVEL_H__

typedef struct Level
{
	char ** map;
	int width;//x
	int height;//y
} Level;

Level saveLevel(const int max_row, const int max_col);
int loadLevel(const Level * level);
char getLevelIndex(const Level * level, const int y, const int x);

#endif