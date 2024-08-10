#ifndef COLORS_H
#define COLORS_H
#include <raylib.h>
#include <vector>
struct Colors
{
	Color col1, col2;
};
const extern std::vector<Colors> color_pairs;
#endif