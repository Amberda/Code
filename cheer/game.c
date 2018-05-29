#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h" 

void init_board(char board[ROWS][COLS], int rows, int cols)
{
    memset(board, ' ', cols*rows*sizeof(char));
}

void display_board(char board[ROWS][COLS], int rows, int cols)
{
	int i = 0;
	printf(" ----------- \n");
	for (i = 0; i < rows; i++)
	{
		printf("|%c  | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
		if (i != rows-1)
			printf("|---|---|---|\n");
	}
	printf(" ----------- \n");
}

void player_move(char board[ROWS][COLS], int rows, int cols)
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("请输入坐标:>");
		scanf("%d%d", &x, &y);
		x--;
		y--;
		if (((x >= 0) && (x <= 2)) && ((y >= 0) && (y <= 2)))
		{
			if (board[x][y] == ' ')
			{
				board[x][y] = 'X';
				break;
			}
			else
			{
				printf("您输入的下标无效, 重新输入！");
			}
		}
		else
		{
			printf("您输入的下标无效, 重新输入！");
		}
	}
}
void computer_move(char board[ROWS][COLS], int rows, int cols)
{
	while (1)
	{
		int x = rand() % 3;
		int y = rand() % 3;
		if (board[x][y] == ' ')
		{
			board[x][y] = '0';
			break;
		}
	}
}

int board_full(char board[ROWS][COLS], int rows, int cols)
{
	int i = 0;
	int j = 0;
	for (i = 0; i<rows; i++)
	{
		for (j = 0; j<cols; j++)
		{
			if (board[i][j] == ' ')
				return 0;
		}
	}
    return 1; 
}
char check_win(char board[ROWS][COLS], int rows, int cols)
{
	int i = 0;
	for (i = 0; i<rows; i++)
	{
		if ((board[i][0] == board[i][1])&& 
			(board[i][1] == board[i][2])&& 
			(board[i][1] != ' '))
			return board[i][1];
	}
	for (i = 0; i<cols; i++)
	{
		if ((board[0][i] == board[1][i])&& 
			(board[1][i] == board[2][i])&& 
			(board[1][i] != ' '))
			return board[1][i];
	}

	if ((board[0][0] == board[1][1])&& 
		(board[1][1] == board[2][2])&& 
		(board[1][1] != ' '))
		return board[1][1];

	if ((board[0][2] == board[1][1])&& 
		(board[1][1] == board[2][0])&& 
		(board[1][1] != ' '))
		return board[1][1];

	if (board_full(board, rows, cols))
	{
		return 'e';
	}
	return ' ';
}

