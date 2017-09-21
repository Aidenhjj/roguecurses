#include <limits.h>
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "level.h"
#include "rogue_like.h"
#include "room.h"
#include "player.h"
#include "position.h"
#include "priority_queue.h"




int main()
{
	Level level;
	Room ** rooms;
	Player * user;

	int input_ch;
	int num_rooms = 6;

	// initialises rand()
	srand(time(NULL));

	screenSetUp();

	// get the width and height of the terminal
	int max_row, max_col;
	getmaxyx(stdscr, max_row, max_col);

	rooms = mapSetUp(num_rooms, max_row, max_col);
	level = saveLevel(max_row, max_col);

	Position playerStart;
	getRoomCentroid(rooms[0], & playerStart);
	user = playerFactory(& playerStart, & level);

	/* GAME LOOP */
	while ((input_ch = getch()) != 'q')
	{
		handleInput(input_ch, user, & level);
	}

	getch();

	endwin();

	// cleanup
	for (int i = 0; i < num_rooms; i++) {
		free(rooms[i]);
	}
	free(rooms);
	free(user);

	return 0;
}

int screenSetUp()
{
	initscr();
	// printw("Hello world!");
	noecho();//stops typed chars from going into terminal
	// cbreak();
	keypad(stdscr, TRUE);  /* enable keyboard mapping */
	refresh();

	if (has_colors())
    {
        start_color();

        /*
         * Set colours
         */
        // init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(1, COLOR_WHITE, COLOR_RED);//foreground / background
        init_pair(2, COLOR_WHITE,   COLOR_GREEN);
        init_pair(3, COLOR_WHITE,  COLOR_YELLOW);
        init_pair(4, COLOR_WHITE,    COLOR_BLUE);
        init_pair(5, COLOR_WHITE,    COLOR_CYAN);
        init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    }

	return 1;
}

Room ** mapSetUp(const size_t num_rooms, const int max_row, const int max_col)
{
	Room ** rooms;
	rooms = malloc(sizeof(Room) * num_rooms);
	
	// create rooms
	// int test_y[6] = {10, 25, 2, 20, 5, 20};
	// int test_x[6] = {80, 10, 50, 75, 2, 60};
	// int test_width[6] = {20, 40, 10, 20, 40, 8};
	// int test_height[6] = {8, 6, 15, 10, 10, 5};
	int temp_y, temp_x, temp_width, temp_height;
	for (int i = 0; i < num_rooms; i++)
	{
		temp_height = (rand() % (max_row / 4)) + 3;
		temp_width = (rand() % (max_col / 4)) + 3;
		temp_y = (rand() % (max_row - temp_height));
		temp_x = (rand() % (max_col - temp_width));

		// temp_height = test_height[i];
		// temp_width = test_width[i];
		// temp_y = test_y[i];
		// temp_x = test_x[i];	

		rooms[i] = createRoom(temp_y, temp_x, temp_height, temp_width, i);
	}

	// print coord numbers for debugging:
	for (int j = 0; j < max_row; j++) {
		mvprintw(j, 0, "%d", j);
	}
	for (int i = 0; i < max_col; i++) {
		mvprintw(0, i, "%d", i%10);
	}
	// connect rooms
	for (int i = 0; i < num_rooms; i++) {
		int j = i;
		while (j == i) {
			j = rand() % num_rooms;
		}
		connectRooms(rooms[i], rooms[(i + 1)%num_rooms], max_row, max_col);
		refresh();
	}

	// delete unused doors

	return rooms;
}

