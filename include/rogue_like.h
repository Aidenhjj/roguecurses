#ifndef __ROGUE_H__
#define __ROGUE_H__

#include <stdlib.h>

#include "player.h"
#include "room.h"

Room ** mapSetUp(const size_t num_rooms, const int max_row, const int max_col);
int screenSetUp();

#endif