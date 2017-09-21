#ifndef __ROOM_H__
#define __ROOM_H__

#include "position.h"

typedef struct Room
{
	int id;
	Position pos;
	int height;
	int width;

	Position * doors;// array of Positions
	int num_doors;
	// Monster ** monsters;// array of pointers to monsters
	// Item ** items;
} Room;

/* room functions */
Room * createRoom(const int y, const int x, const int height, const int width, const int id);
int drawRoom(const Room * room);
int connectRooms(Room * room_1, Room * room_2, int max_row, int max_col);
int getRoomCentroid(const Room * room, Position * centroid);

#endif