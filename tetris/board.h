#ifndef BOARD_H
#define BOARD_H
#include "constants.h"
#include <vector>
#include "Colors.h"
enum types_of_block {
	WALL, BLOCK, NOTHING
};
struct Point {
	int x, y;
};
extern types_of_block board[height][width];
extern Colors board_color[height][width];
extern int score;
extern std::vector<Point> next_object;
#endif