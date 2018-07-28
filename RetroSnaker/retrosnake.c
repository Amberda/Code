#define _CRT_SECURE_NO_WARNINGS 1

#include "retrosnake.h"


void UIInit(UI* pUI, int wight, int height)
{
	assert(pUI != NULL);
	pUI->gameZoneWight = wight;
	pUI->gameZoneHeight = height;
	pUI->wallBlock = "#";
	pUI->foodBlock = "#";
	pUI->snakeBlock = "#";
	pUI->marginLeft = 2;
	pUI->marginTop = 1;

	char mode[1024];
	sprintf(mode, "mode con cols=%d lines=%d", pUI->gameZoneWight + 50, pUI->gameZoneHeight + 20);
	system(mode);
}

void SetCursorPosition(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(handle, coord);
}

void DisplayWall(UI* pUI)
{
	//上
	for (int i = 0; i < pUI->gameZoneWight + 2; i++)
	{
		int x = pUI->marginLeft + i;
		int y = pUI->marginTop;

		SetCursorPosition(x, y);
		printf("%s", pUI->wallBlock);
	}
	
	//下
	for (int i = 0; i < pUI->gameZoneWight + 2; i++)
	{
		int x = pUI->marginLeft + i;
		int y = pUI->marginTop + pUI->gameZoneHeight + 1;

		SetCursorPosition(x, y);
		printf("%s", pUI->wallBlock);
	}
	
	//左
	for (int i = 0; i < pUI->gameZoneHeight + 2; i++)
	{
		int x = pUI->marginLeft;
		int y = pUI->marginTop + i;

		SetCursorPosition(x, y);
		printf("%s", pUI->wallBlock);
	}

	//右
	for (int i = 0; i < pUI->gameZoneHeight + 2; i++)
	{
		int x = pUI->marginLeft + pUI->gameZoneWight + 1;
		int y = pUI->marginTop + i;

		SetCursorPosition(x, y);
		printf("%s", pUI->wallBlock);
	}
}

void DisplaySnakeBlock(const UI* pUI, int gameZoneX, int gameZoneY)
{
	SetCursorPosition(gameZoneX + pUI->marginLeft, gameZoneY + pUI->marginTop);

	printf("%s", pUI->snakeBlock);
}

void DisplayFoodBlock(const UI* pUI, int gameZoneX, int gameZoneY)
{
	SetCursorPosition(gameZoneX + pUI->marginLeft, gameZoneY + pUI->marginTop);

	printf("%s", pUI->foodBlock);
}

void CleanBlock(const UI* pUI, int gameZoneX, int gameZoneY)
{
	SetCursorPosition(gameZoneX + pUI->marginLeft, gameZoneY + pUI->marginTop);

	printf(" ");
}

void DisplaySnake(const Snake* pSnake, UI* pUI)
{
	Node* pNode = pSnake->pHead;
	while (pNode != NULL)
	{
		DisplaySnakeBlock(pUI, pNode->point.x, pNode->point.y);
		pNode = pNode->pNext;
	}
}

void SnakeInit(Snake *pSnake)
{
	int initlen = 3;
	int x = 5;
	int y = 5;

	pSnake->pHead = NULL;
	for (int i = 0; i < initlen; i++)
	{
		Node* cur = (Node*)malloc(sizeof(Node));
		assert(cur != NULL);
		cur->point.x = 5 + i;
		cur->point.y = 5;
		
		cur->pNext = pSnake->pHead;
		pSnake->pHead = cur;
	}
	pSnake->direction = RIGHT;
}

bool IsOverLapSnake(int x, int y, const Snake *pSnake)
{
	Node* pNode = pSnake->pHead; 
	while (pNode != NULL)
	{
		if (pNode->point.x == x&&pNode->point.y == y)
			return true;
		pNode = pNode->pNext;
	}
	return false;
}

void GetFood(int width, int height, const Snake *pSnake, Point* pFood)
{
	//在w*h的范围内，随机生成坐标，如果和蛇重叠继续生成
	int x = 0;
	int y = 0;

	do
	{
		x = rand() % width;
		y = rand() % height;
	} while (IsOverLapSnake(x, y, pSnake));

	pFood->x = x;
	pFood->y = y;
}

void GameInit(Game* pGame)
{
	pGame->score = 0;
	pGame->scorePerFood = 10;
	pGame->interval = 300;
	pGame->width = 16;
	pGame->height = 12;

	SnakeInit(&pGame->snake);
	GetFood(pGame->width, pGame->height, &pGame->snake, &pGame->foodPoint);
}

Point GetPoint(Snake* pSnake)
{
	Point point = pSnake->pHead->point;
	switch (pSnake->direction)
	{
	case UP:
		point.y -= 1;
		break;
	case DOWN:
		point.y += 1;
		break;
	case LEFT:
		point.x -= 1;
		break;
	case RIGHT:
		point.x += 1;
		break;
	default:
		break;
	}
	return point;
}

bool IsEatFood(Point point, Point foodPoint)
{
	if (point.x == foodPoint.x&&point.y == foodPoint.y)
		return true;
	return false;
}

void AddHead(Point point, Snake* pSnake, const UI* pUI)
{
	Node* pNode = (Node*)malloc(sizeof(Node));
	pNode->pNext = pSnake->pHead;
	pSnake->pHead = pNode;
	pSnake->pHead->point = point;

	DisplaySnakeBlock(pUI, point.x, point.y);
}

void RemoveTail(Snake* pSnake,const UI* pUI)
{
	Node* pNode = pSnake->pHead;
	while (pNode->pNext->pNext != NULL)
	{
		pNode = pNode->pNext;
	}

	CleanBlock(pUI, pNode->pNext->point.x, pNode->pNext->point.y);
	free(pNode->pNext);
	pNode->pNext = NULL;
}

bool IsKillByWall(int wight, int height, Point point)
{
	if (point.x < 0 || point.x >= wight || point.y < 0 || point.y >= height)
		return true;
	return false;
}

bool IsKillBySelf(const Snake* pSnake, Point point)
{
	Node* pNode = pSnake->pHead->pNext;
	while (pNode != NULL)
	{
		if (pNode->point.x == point.x&&pNode->point.y == point.y)
			return true;
	}
	return false;
}

void GameDeatroy(Game* pGame)
{
	Node* pDel = pGame->snake.pHead;
	Node* tmp = pDel;
	while (pDel != NULL)
	{
		tmp = pDel->pNext;
		free(pDel);
		pDel = pDel->pNext;
	}
}
