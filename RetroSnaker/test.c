#define _CRT_SECURE_NO_WARNINGS 1

#include "retrosnake.h"

int main()
{
	Game game;
	UI ui;

	GameInit(&game);
	UIInit(&ui, game.width, game.height);

	DisplayWall(&ui);
	DisplaySnake(&game.snake, &ui);
	DisplayFoodBlock(&ui, game.foodPoint.x, game.foodPoint.y);
	SetCursorPosition(0, 20);

	while (1)
	{
		if (GetAsyncKeyState(VK_UP))//∞¥…œ¡À
		{
			if (game.snake.direction!=DOWN)
				game.snake.direction = UP;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (game.snake.direction!=UP)
				game.snake.direction = DOWN;
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			if (game.snake.direction != RIGHT)
				game.snake.direction = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			if (game.snake.direction != LEFT)
				game.snake.direction = RIGHT;
		}

		Point nextPoint = GetPoint(&game.snake);
		if (IsEatFood(nextPoint, game.foodPoint))
		{
			AddHead(nextPoint, &game.snake, &ui);
			GetFood(game.width, game.height, &game.snake, &game.foodPoint);
			game.score += game.scorePerFood;
		}
		else
		{
			AddHead(nextPoint, &game.snake, &ui);
			RemoveTail(&game.snake, &ui);
		}

		if (IsKillByWall(game.width,game.height,nextPoint))
		{
			break;
		}
		if (IsKillBySelf(&game.snake, nextPoint))
		{
			break;
		}

		Sleep(game.interval);
	}

	GameDeatroy(&game);
	system("pause");
	return 0;
}