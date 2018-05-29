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
		printf("���Ӯ\n");
	}
	else if (tmp == '0')
	{
		printf("�Ǻ�\n");
	}
	else if (tmp == 'e')
	{
		printf("ƽ��\n");
	}     //    
	display_board(board, ROWS, COLS);
}
int main()
{
	int input = 0;
	do
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf("ѡ�����������ѡ��:<");
			break;
		}
	}while (input);
	system("pause\n");
	return 0;
}
