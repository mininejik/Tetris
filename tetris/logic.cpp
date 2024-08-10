#include "logic.h"
#include <raylib.h>
#include "board.h"
#include "game_over.h"
#include <vector>
#include <time.h>
#include "draw.h"
#include <queue>
#include "int_to_str.h"
using namespace std;
double speed()
{
	double scr = score;
	scr = (1 - scr / 100) / 2;
	if (scr < 0.2)return 0.2;
	else return scr;
}
int rotate_counter = 0;

Colors colors;
vector<Point> object;
bool used[height][width];
vector<Point> bfs(Point start)
{
	queue<Point> q;
	used[start.y][start.x] = 1;
	q.push(start);
	vector<Point> obj;
	while (!q.empty())
	{
		Point p = q.front();
		q.pop();
		obj.push_back(p);
		if (p.x - 1 > 0 && board[p.y][p.x - 1] == BLOCK && !used[p.y][p.x - 1]) {
			used[p.y][p.x - 1] = 1;
			Point point;
			point.x = p.x - 1;
			point.y = p.y;
			q.push(point);
		}
		if (p.x + 1 < width - 1 && board[p.y][p.x + 1] == BLOCK && !used[p.y][p.x + 1]) {
			used[p.y][p.x + 1] = 1;
			Point point;
			point.x = p.x + 1;
			point.y = p.y;
			q.push(point);
		}
		if (p.y + 1 < height - 1 && board[p.y + 1][p.x] == BLOCK && !used[p.y + 1][p.x]) {
			used[p.y + 1][p.x] = 1;
			Point point;
			point.x = p.x;
			point.y = p.y + 1;
			q.push(point);
		}
		if (p.y - 1 >= 0 && board[p.y - 1][p.x] == BLOCK && !used[p.y - 1][p.x]) {
			used[p.y - 1][p.x] = 1;
			Point point;
			point.x = p.x;
			point.y = p.y - 1;
			q.push(point);
		}

	}
	return obj;
}
vector<vector<Point>> search_floating_objects()
{
	
	for(int i=0;i<height;i++)
		for (int j = 0; j < width; j++)
			used[i][j] = 0;
	for (int i = 1; i < width - 1; i++)
		if (board[height - 2][i])bfs({i, height - 2});
	vector<vector<Point>> v;
	for (int i = 0; i < height - 1; i++)
		for (int j = 1; j < width - 1; j++)
			if (board[i][j] == BLOCK && !used[i][j])v.push_back(bfs({j, i}));
}
inline int random()
{
	return time(NULL) * 53 + 13;
}
inline int random_for_color()
{
	return (time(NULL) * 31) % 7;
}
void delay(int seconds)
{
	double sec1 = 0;
	while (sec1 < seconds)
		sec1 += GetFrameTime();
}
bool object_fall()
{ 
	for (int i = 0; i < object.size(); i++)
	{
		board[object[i].y][object[i].x] = NOTHING;
		board_color[object[i].y][object[i].x] = { BLANK, BLANK };
	}		
	for (int i = 0; i < object.size(); i++)
		if (board[object[i].y + 1][object[i].x] == BLOCK || object[i].y == height - 2)return 1;
	for (int i = 0; i < object.size(); i++)
		object[i].y++;
	for (int i = 0; i < object.size(); i++)
	{
		board[object[i].y][object[i].x] = BLOCK;
		board_color[object[i].y][object[i].x] = colors;
	}
		
	return 0;
}
void deleting()
{
	bool repet = 0;
	for (int i = height - 2; i > 0; i--)
	{
		bool fool = 1;
		for(int j = 1; j < width - 1;j++)
			if (board[i][j] == NOTHING) {
				fool = 0;
				break;
			}
		if (fool)
		{
			repet = 1;
			score += 10;
			for (int j = 1; j < width - 1; j++)
			{
				board[i][j] = NOTHING;
				board_color[i][j] = {BLANK, BLANK};
			}
			draw();
			for (; i > 1; i--)
				for (int j = 1; j < width - 1; j++)
				{
					board[i][j] = board[i - 1][j];
					board_color[i][j] = board_color[i - 1][j];
				}
		}
	}
	if (repet) {
		vector<vector<Point>> vec = search_floating_objects();
		for (int i = 0; i < vec.size(); i++)
		{
			object = vec[i];
			while (!object_fall())
			{
			}
		}
		deleting(); 
		delay(1);
	}
}
void create_object()
{
	colors = color_pairs[random_for_color()];
	object.clear();
	static bool firstly = 1;
	if (firstly) {
		firstly = 0;
		int type = random() % 5 + 1;
		if (type == 1) {
			object = { {width / 2, 1},{width / 2, 2},{width / 2 - 1, 3},{width / 2, 3},{width / 2 + 1, 3} };
		}
		else if (type == 2) {
			object = { {width / 2, 1},{width / 2, 2},{width / 2, 3},{width / 2, 4} };
		}
		else if (type == 3) {
			object = { {width / 2, 1},{width / 2 + 1, 1},{width / 2,2},{width / 2 + 1, 2} };
		}
		else if (type == 4) {
			object = { {width / 2, 1} };
		}
		else {
			object = { { width / 2, 1}, { width / 2 + 1, 1}, {width / 2, 2}, {width / 2 - 1, 2} };
		}
	}
	else object = next_object;
	rotate_counter = 0;
	
	int type = (random() + 2) % 5 + 1;
	if (type == 1) {
		next_object = { {width / 2, 1},{width / 2, 2},{width / 2 - 1, 3},{width / 2, 3},{width / 2 + 1, 3} };
	}
	else if(type == 2){
		next_object = { {width / 2, 1},{width / 2, 2},{width / 2, 3},{width / 2, 4} };
	}
	else if(type == 3){
		next_object = { {width / 2, 1},{width / 2 + 1, 1},{width / 2,2},{width / 2 + 1, 2} };
	}
	else if (type == 4){
		next_object = { {width / 2, 1} };
	}
	else {
		next_object = { { width / 2, 1}, { width / 2 + 1, 1}, {width / 2, 2}, {width / 2 - 1, 2} };
	}
}

void first_object()
{
	static bool first_time = 0;
	if (!first_time) {
		first_time = 1;
		create_object();

	}
}
void rotate()
{
	vector<Point> rotated_object = object;
	int x1 = 1e9, y1 = 1e9, difx = 1e9, dify = 1e9;
	for (int i = 0; i < rotated_object.size(); i++)
	{
		if (rotated_object[i].x < x1)x1 = rotated_object[i].x;
		if (rotated_object[i].y < y1)y1 = rotated_object[i].y;
	}
	for (int i = 0; i < rotated_object.size(); i++)
	{
		int x = rotated_object[i].x, y = rotated_object[i].y;
		x -= x1;
		y -= y1;
		swap(x, y);
		if (rotate_counter % 2 == 0)y = -y;
		x += x1;
		y += y1;
		

		rotated_object[i].x = x;
		rotated_object[i].y = y;
	}
	for (int i = 0; i < rotated_object.size(); i++)
		{
			if (rotated_object[i].x < difx)difx = rotated_object[i].x;
			if (rotated_object[i].y < dify)dify = rotated_object[i].y;
		}
	difx -= x1;
	dify -= y1;
	for (int i = 0; i < rotated_object.size(); i++)
	{
		rotated_object[i].x -= difx;
		rotated_object[i].y -= dify;
	}
	bool check = 1;
	for (int i = 0; i < object.size(); i++)
	{
		board[object[i].y][object[i].x] = NOTHING;
		board_color[object[i].y][object[i].x] = { BLANK, BLANK};
	}
	for (int i = 0; i < rotated_object.size(); i++)
		if (board[rotated_object[i].y][rotated_object[i].x] != NOTHING) {
			check = 0;
		}
	if (check) object = rotated_object;
	for (int i = 0; i < object.size(); i++)
	{
		board[object[i].y][object[i].x] = BLOCK;
		board_color[object[i].y][object[i].x] = colors;
	}
	
}
double frame_time = 0;

void logic()
{
	frame_time += GetFrameTime();
	first_object();
	if (IsKeyPressed(KEY_LEFT)) {
		for (int i = 0; i < object.size(); i++)
			{
				board[object[i].y][object[i].x] = NOTHING;
				board_color[object[i].y][object[i].x] = { BLANK, BLANK};
			}
		bool CanMove = 1;	
		for (int i = 0; i < object.size(); i++)
			if (board[object[i].y][object[i].x - 1] != NOTHING) {
				CanMove = 0;
			}
		if (CanMove) {
			
			for (int i = 0; i < object.size(); i++)
				object[i].x--;
			
		}
		for (int i = 0; i < object.size(); i++)
			{
				board[object[i].y][object[i].x] = BLOCK;
				board_color[object[i].y][object[i].x] = colors;
			}
	}
	else if (IsKeyPressed(KEY_RIGHT)) {
		bool CanMove = 1;
		for (int i = 0; i < object.size(); i++)
			{
				board[object[i].y][object[i].x] = NOTHING;
				board_color[object[i].y][object[i].x] = { BLANK, BLANK };
			}
		for (int i = 0; i < object.size(); i++)
			if (board[object[i].y][object[i].x + 1] != NOTHING) {
				CanMove = 0;
			}
		if (CanMove) {	
			for (int i = 0; i < object.size(); i++)
				object[i].x++;
			
		}
		for (int i = 0; i < object.size(); i++)
			{
				board[object[i].y][object[i].x] = BLOCK;
				board_color[object[i].y][object[i].x] = colors;
			}
	}
	if (IsKeyPressed(KEY_UP)) {
		rotate_counter++;
	for (int i = 0; i < object.size(); i++)
	{
		board[object[i].y][object[i].x] = NOTHING;
		board_color[object[i].y][object[i].x] = { BLANK, BLANK };
	}
		rotate();
	for (int i = 0; i < object.size(); i++)
	{
		board[object[i].y][object[i].x] = BLOCK;
		board_color[object[i].y][object[i].x] = colors;
	}
	}
	if (IsKeyPressed(KEY_DOWN)) {
		frame_time += 10000;
	}
	
	if (frame_time >= speed())
	{
		if (object_fall()) {
			
			
			for (int i = 0; i < object.size(); i++)
			{
				if (object[i].y <= 1) game_over(int_to_str(score).c_str());
				board[object[i].y][object[i].x] = BLOCK;
				board_color[object[i].y][object[i].x] = colors;
			}
			create_object();
			deleting();
		}
		frame_time = 0;
	}
	
}
