/* 
 * tictactoe.h 
 * 2022 JH139940 SK139959
 * Compilation: make
*/

#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <stdio.h>
#include <stdbool.h>

// Board 
struct Board {
  char tab[9];
  char last_mark;
}typedef MyBoard;

// Coords
int x, y;

// Print received board
void print_board(MyBoard received_board);

// Init new board
MyBoard init_board();

// Make move on board
MyBoard move(MyBoard my_board, int input, char mark);

// Check if someone won
bool is_win(MyBoard my_board, char mark);

// Match result
bool match_result(MyBoard my_board, char mark);

// X player game input-output loop
void X_player_ioLoop(int sfd);

// O player game input-output loop
void O_player_ioLoop(int sfd);

#endif

/* end of tictactoe.h file */
