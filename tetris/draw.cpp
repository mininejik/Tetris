#include "draw.h"
#include "board.h"
#include <raylib.h>
#include "int_to_str.h"
#include "Colors.h"
void draw()
{
	BeginDrawing();
	auto custom_color = Color{10, 10, 10, 255};
	ClearBackground(BLACK);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (board[i][j] == WALL) {
				DrawRectangle(j * px, i * px, px, px, DARKBLUE);
				if (!((i == 0 || i == 1 || i == 2) && (j == 0 || j == 1)))DrawRectangle(j * px + 4, i * px + 4, px - 8, px - 8, BLUE);
			}
			else if (board[i][j] == BLOCK) {
				DrawRectangle(j * px, i * px, px, px, board_color[i][j].col1);
				DrawRectangle(j * px + 4, i * px + 4, px - 8, px - 8, board_color[i][j].col2);
			}
			else {
				DrawRectangle(j * px + 2, i * px + 2, px - 4, px - 4, custom_color);
			}
	DrawText(int_to_str(score).c_str(), 10, 10, px, GREEN);
	DrawText("NEXT", 0, 2 * px - px / 4, px * 0.37, RED);
	for (int i = 0; i < next_object.size(); i++)
	{
		DrawRectangle(next_object[i].x * px / 5 - px, next_object[i].y * px / 5 +  2 * px, px / 5, px / 5, DARKGREEN);
		DrawRectangle(next_object[i].x * px / 5 - px + 2, next_object[i].y * px / 5 + 2 * px + 2, px / 5 - 4, px / 5 - 4, GREEN);
	}
	EndDrawing();	
}