#include "setup.h"
#include "constants.h"
#include "board.h"
void setup()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			board[i][j] = NOTHING;
			board_color[i][i] = { BLANK, BLANK};
		}
			
	for (int i = 0; i < height; i++)
		board[i][0] = board[i][width - 1] = WALL;
	for (int i = 0; i < width; i++)
		 board[height - 1][i] = board[0][i] = WALL;

	
}