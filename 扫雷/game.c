#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void init_board(char arr[ROWS + 2][COLS + 2], int row, int col, char ch)
{
	//int i = 0;
	//int j = 0;
	//for (i = 1; i < row; i++)
	//{
	//	for (j = 1; j < col; j++)
	//	{
	//		arr[i][j] = '0';
	//	}
	//}
	memset(arr, ch, row*col);
}
int get_mine_num(int x, int y)
{
	return rand() % (y - x + 1) + x;
}
void set_mine(char arr[ROWS + 2][COLS + 2], int row, int col)
{
	int x = 0;
	int y = 0;
	int count = DEFAULT_COUNT;
	srand((unsigned)time(NULL));
	while (count)
	{
		x = get_mine_num(1, 10);
		y = get_mine_num(1, 10);
		if (arr[x][y] != '1')
		{
			arr[x][y] = '1';
			count--;
		}

	}

}
void display(char arr[ROWS + 2][COLS + 2], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("   ");
	for (i = 0; i < col - 2; i++)
	{
		printf("%d ", i + 1);
	}
	printf("\n");

	for (i = 0; i < row - 2; i++)
	{
		printf("%2d ", i + 1);
		for (j = 0; j < col - 2; j++)
		{
			printf("%c ", arr[i + 1][j + 1]);
		}
		printf("\n");
	}
}
void sweep(char mine[ROWS + 2][COLS + 2], char show[ROWS + 2][COLS + 2])
{
	int x = 0;
	int y = 0;
	int count = 0;
	while (count != (ROWS*COLS - DEFAULT_COUNT))
	{
		printf("ÇëÊäÈë×ø±ê:>");
		scanf("%d %d", &x, &y);
		if (mine[x][y] == '1')
		{
			printf("°¥Ñ½£¬²ÈÀ×ÁË:<\n");
			break;
		}
		else
		{
			int ret = get_mine(mine, x, y);
			show[x][y] = ret + '0';
			display(show, ROWS + 2, COLS + 2);
			count++;
		}
	}
	if (count == ROWS*COLS - DEFAULT_COUNT)
		printf("¹§Ï²Äã£¬ÄãÓ®ÁË£¡\n");
	display(mine, ROWS + 2, COLS + 2);
}
int get_mine(char mine[ROWS + 2][COLS + 2], int x, int y)
{
	return (mine[x + 1][y + 1] - '0') +
		(mine[x + 1][y - 1] - '0') +
		(mine[x - 1][y + 1] - '0') +
		(mine[x - 1][y - 1] - '0') +
		(mine[x + 1][y] - '0') +
		(mine[x - 1][y] - '0') +
		(mine[x][y + 1] - '0') +
		(mine[x][y - 1] - '0');
	/*int count = 0;
	if (mine[x + 1][y + 1] == '1')count++;
	if (mine[x + 1][y - 1] == '1')count++;
	if (mine[x + 1][y] == '1')count++;

	if (mine[x - 1][y + 1] == '1')count++;
	if (mine[x - 1][y - 1] == '1')count++;
	if (mine[x - 1][y] == '1')count++;

	if (mine[x][y + 1] == '1')count++;
	if (mine[x][y - 1] == '1')count++;

	return count;*/
}