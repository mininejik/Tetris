#include <raylib.h>
#include "draw.h"
#include "setup.h"
#include "logic.h"
#include "constants.h"
bool WindowShouldClose()
{
	return IsKeyPressed(KEY_ESCAPE);
}
int main()
{
	InitWindow(width * px, height * px, "tetris");
	SetTargetFPS(240);
	setup();
	while(!WindowShouldClose())
	{
		BeginDrawing;
		draw();
		logic();
		EndDrawing;
	}

	return 0;
}