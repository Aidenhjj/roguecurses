#include <ncurses.h>
#include <stdlib.h>

#include "level.h"
#include "position.h"
#include "player.h"

Player * playerFactory(const Position * start, const Level * level)
{
	Player * newPlayer = malloc(sizeof(Player));

	newPlayer->health = 20;
	newPlayer->pos.x = 0;
	newPlayer->pos.y = 0;

	// temporary stuff
	playerMove(start->y, start->x, newPlayer, level);

	return newPlayer;
}

int playerMove(const int dy, const int dx, Player * user, const Level * level) 
{
	/* moves the player avatar */
	Position newPos;
	newPos.y = user->pos.y + dy;
	newPos.x = user->pos.x + dx;

	int check = checkPosition(& newPos);

	if (check == 0) {
		move(user->pos.y, user->pos.x);
		return 0;
	}

	mvprintw(user->pos.y, user->pos.x, "%c", getLevelIndex(level, user->pos.y, user->pos.x));

	user->pos.x = newPos.x;
	user->pos.y = newPos.y;
	mvprintw(user->pos.y, user->pos.x, "@");
	move(user->pos.y, user->pos.x);
	return 1;
}

int handleInput(const int input, Player * user, const Level * level)
{
	switch (input)
	{
		/* move up */
		case 'w':
		case 'W':
			playerMove(-1, 0, user, level);
			break;

		/* move down */
		case 's':
		case 'S':
			playerMove(1, 0, user, level);
			break;

		/* move left */
		case 'a':
		case 'A':
			playerMove(0, -1, user, level);
			break;

		/* move right */
		case 'd':
		case 'D':
			playerMove(0, 1, user, level);
			break;

		default:
			break;
	}
}