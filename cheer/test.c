#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"


void menu()
{
	printf("*******************************\n");
	printf("******  1.play   0.exit  ******\n");
	printf("*******************************\n");
}
void game()
{
	int tmp = 0;
	char board[ROWS][COLS];
    init_board(board, ROWS, COLS);
	display_board(board, ROWS, COLS);
	srand((unsigned int)time(NULL));
	while (1)
	{
		player_move(board, ROWS, COLS);
		if ((tmp = check_win(board, ROWS, COLS)) != ' ')
			break;
		display_board(board, ROWS, COLS);
		computer_move(board, ROWS, COLS);
		if ((tmp = check_win(board, ROWS, COLS)) != ' ')
			break;
		display_board(board, ROWS, COLS);
	}         
	if (tmp == 'X')
	{
		printf("玩家赢\n");
	}
	else if (tmp == '0')
	{
		printf("呵呵\n");
	}
	else if (tmp == 'e')
	{
		printf("平局\n");
	}     //    
	display_board(board, ROWS, COLS);
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
	}while (input);
	system("pause\n");
	return 0;
}
