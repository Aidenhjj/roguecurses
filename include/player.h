#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "position.h"

typedef struct Player
{
	Position pos;
	int health;
	// Room * room;
} Player;

Player * playerFactory(const Position * start, const Level * level);
int playerMove(const int dy, const int dx, Player * user, const Level * level);
int handleInput(const int input, Player * user, const Level * level);

#endif