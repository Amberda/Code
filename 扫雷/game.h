#define _CRT_SECURE_NO_WARNINGS 1
#ifndef __GAME_H__
#define __GAME_H__

#define ROWS 10
#define COLS 10
#define DEFAULT_COUNT 20
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void init_board(char arr[ROWS + 2][COLS + 2], int row, int col, char ch);
void display(char arr[ROWS + 2][COLS + 2], int row, int col);
void set_mine(char arr[ROWS + 2][COLS + 2], int row, int col);
void sweep(char mine[ROWS + 2][COLS + 2], char show[ROWS + 2][COLS + 2]);
int get_mine(char mine[ROWS + 2][COLS + 2], int x, int y);


#endif //__GAME_H__
