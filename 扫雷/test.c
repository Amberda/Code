#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void menu()
{
	printf("*******************************\n");
	printf("******  1.play   0.exit  ******\n");
	printf("*******************************\n");
}
void game()
{
	char mine[ROWS + 2][COLS + 2] = { 0 };
	char show[ROWS + 2][COLS + 2] = { 0 };
	init_board(mine, ROWS + 2, COLS + 2, '0');
	init_board(show, ROWS + 2, COLS + 2, '*');
	//display(mine, ROWS + 2, COLS + 2);
	display(show, ROWS + 2, COLS + 2);
	set_mine(mine, ROWS + 2, COLS + 2);
	//display(mine, ROWS + 2, COLS + 2);
	sweep(mine, show);
}
int main()
{
	int input = 0;
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf("选择错误，请重新选择:<");
			break;
		}
	} while (input);
	system("pause\n");
	return 0;
}

