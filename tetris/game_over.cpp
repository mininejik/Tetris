#include "game_over.h"
#include "constants.h"
#include <raylib.h>
#include <string>
#include <iostream>
void game_over(const char* score) {
	while (!IsKeyPressed(KEY_ESCAPE))
	{
		BeginDrawing();
		ClearBackground(WHITE);
		DrawText("GAME OVER", width * px / 2 - 3 * px, height * px / 2, px, RED);
		DrawText(score, width * px / 2 - px, height * px / 2 + px, px, RED);
		EndDrawing();
	}
	CloseWindow();
}