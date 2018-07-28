#ifndef __RETROSNAKE_H__
#define __RETROSNAKE_H__ 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <Windows.h>


typedef struct Point
{
	int x;
	int y;
}Point;

typedef struct Node
{
	Point point;
	struct Node* pNext;
}Node;

typedef enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}Direction;

typedef struct Snake
{
	Direction direction;
	Node* pHead;
}Snake;

typedef struct Game
{
	int score;		  //当前得分
	int scorePerFood; //每个食物的得分
	int interval;	  //速度

	Snake snake;	  //蛇
	Point foodPoint;  //食物

	int width;		  //长
	int height;		  //宽
}Game;

typedef struct UI
{
	int gameZoneWight;
	int gameZoneHeight;
	char* wallBlock;
	char* snakeBlock;
	char* foodBlock;
	int marginLeft;//边界
	int marginTop; //
}UI;


void UIInit(UI* pUI, int wight, int height);
void SetCursorPosition(int x, int y);
void DisplayWall(UI* pUI);
void DisplaySnakeBlock(const UI* pUI, int gameZoneX, int gameZoneY);
void DisplayFoodBlock(const UI* pUI, int gameZoneX, int gameZoneY);
void CleanBlock(const UI* pUI, int gameZoneX, int gameZoneY);
void DisplaySnake(const Snake* pSnake, UI* pUI);
void SnakeInit(Snake *snake);
bool IsOverLapSnake(int x, int y, const Snake *pSnake);
void GetFood(int width, int height, const Snake *pSnake, Point* pFood);
void GameInit(Game* pGame);
Point GetPoint(Snake* pSnake);
bool IsEatFood(Point point, Point foodPoint);
void AddHead(Point point, Snake* pSnake, const UI* pUI);
void RemoveTail(Snake* pSnake, const UI* pUI);
bool IsKillByWall(int wight, int height, Point point);
bool IsKillBySelf(const Snake* pSnake, Point point);
void GameDeatroy(Game* pGame);


#endif //__RETROSNAKE_H__