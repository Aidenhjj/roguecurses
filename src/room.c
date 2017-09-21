#include <ncurses.h>
#include <stdlib.h>

#include "room.h"

Room * createRoom(const int y, const int x, const int height, const int width, const int id)
{
	Room * newRoom = malloc(sizeof(Room));

	int r;
	
	newRoom->pos.y = y;
	newRoom->pos.x = x;
	newRoom->height = height;
	newRoom->width = width;
	newRoom->id = id;

	newRoom->num_doors = 4;
	newRoom->doors = malloc( newRoom->num_doors * sizeof(Position) );

	// // populate doors array with -1s (not doors yet!)
	// for (int i = 0; i < newRoom->num_doors; i++) {
	// 	newRoom->doors[i].x = -1;
	// 	newRoom->doors[i].y = -1;
	// }

	// TOP DOOR
	newRoom->doors[0].x = (rand() % (width - 2)) + x + 1;
	newRoom->doors[0].y = y;

	// RIGHT DOOR
	newRoom->doors[1].y = (rand() % (height - 2)) + y + 1;
	newRoom->doors[1].x = x + width;

	// BOTTOM DOOR
	newRoom->doors[2].x = (rand() % (width - 2)) + x + 1;
	newRoom->doors[2].y = y + height;

	// fprintf(stderr, "room[%d] door[2] x, y: %d, %d\n", newRoom->id, 
	// 	newRoom->doors[2].x, newRoom->doors[2].y);

	// LEFT DOOR
	newRoom->doors[3].y = (rand() % (height - 2)) + y + 1;
	newRoom->doors[3].x = x;

	drawRoom(newRoom);

	return newRoom;
}

int connectRooms(Room * room_1, Room * room_2, int max_row, int max_col)
{
	Position centroid_1, centroid_2;
	getRoomCentroid(room_1, & centroid_1);
	getRoomCentroid(room_2, & centroid_2);

	// Position startDoor, finishDoor;

	// int dy, dx;
	// int manhattan = getManhattanDistance(& centroid_1, & centroid_2, & dy, & dx);

	// fprintf(stderr, "#2 room[%d] door[2] x, y: %d, %d\n", room_1->id, 
	// 	room_1->doors[2].x, room_1->doors[2].y);

	// select start and finish doors with element of randomness
	// if (dy < 0) {
	// 	startDoor = room_1->doors[2];
	// 	finishDoor = room_2->doors[0];
	// }
	// else {
	// 	startDoor = room_1->doors[0];
	// 	finishDoor = room_2->doors[2];
	// }


	// if (dx < 0) {
	// 	if ((rand() % manhattan) > dy) {
	// 		// fprintf(stderr, "changing startDoor to RHS\n");
	// 		startDoor = room_1->doors[1];
	// 	}
	// 	if ((rand() % manhattan) > dy) {
	// 		// fprintf(stderr, "changing finishDoor to LHS\n");
	// 		finishDoor = room_2->doors[3];
	// 	}
	// }
	// else {
	// 	if ((rand() % manhattan) > dy) {
	// 		// fprintf(stderr, "changing startDoor to LHS\n");
	// 		startDoor = room_1->doors[3];
	// 	}
	// 	if ((rand() % manhattan) > dy) {
	// 		// fprintf(stderr, "changing finishDoor to RHS\n");
	// 		finishDoor = room_2->doors[1];
	// 	}
	// }

	// test code:
	// attron(0 | COLOR_PAIR(1));
	// mvprintw(startDoor.y, startDoor.x, "K");
	// mvprintw(finishDoor.y, finishDoor.x, "K");
	// attroff(0 | COLOR_PAIR(1));
	// use_default_colors();

	// find 'optimal' path
	findPositionPath(& centroid_1, & centroid_2, max_row, max_col);
}

int getRoomCentroid(const Room * room, Position * centroid)
{
	centroid->x = room->pos.x + (room->width/2);
	centroid->y = room->pos.y + (room->height/2);
	return 1;
}

int drawRoom(const Room * room)
{
	int startX = room->pos.x;
	int startY = room->pos.y;
	int finalX = room->pos.x + room->width;
	int finalY = room->pos.y + room->height;

	bool labelled = false;

	for (int j = startY; j <= finalY; j++) {
		for (int i = startX; i <= finalX; i++) {
			if (mvinch(j, i) == '.') {
				//do nothing
			}
			else if ((j == startY) || (j == finalY)) {
				if (!labelled) {
					mvprintw(j, i, "%d", room->id);
					labelled = true;
				}
				else {
					mvprintw(j, i, "-");
				}
			}
			else if ((i == startX) || (i == finalX)) {
				if (!labelled) {
					mvprintw(j, i, "%d", room->id);
					labelled = true;
				}
				else {
					mvprintw(j, i, "|");
				}
			}
			else {
				mvprintw(j, i, ".");
			}
		}
	}

	// draw doors:
	for (int k = 0; k < room->num_doors; k++) {
		mvprintw(room->doors[k].y, room->doors[k].x, "+");
	}
	return 1;
}
