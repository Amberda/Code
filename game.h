#ifndef __GAME_H__
#define __GAME_H__ 

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define ROWS 3 
#define COLS 3 

void init_board(char board[ROWS][COLS], int rows, int cols);
void display_board(char board[ROWS][COLS], int rows, int cols);
void player_move(char board[ROWS][COLS], int rows, int cols);
void computer_move(char board[ROWS][COLS], int rows, int cols);
int board_full(char board[ROWS][COLS], int rows, int cols);
char check_win(char board[ROWS][COLS], int rows, int cols);

#endif //__GAME_H__