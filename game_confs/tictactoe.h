/* tictactoe.h */
#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <stdio.h>
#include <stdbool.h>

// Board 
struct Board {
  char tab[9];
}typedef MyBoard;

// Coords
int x, y;

// Print received board
void print_board(MyBoard received_board);

// Init new board
MyBoard init_board();

// Make move on board
MyBoard move(MyBoard my_board, int input, char OX);

// Check if someone won
bool is_win(MyBoard my_board, char OX);

// Match result
int match_result(MyBoard my_board, char mark);

// First player game input-output loop
void first_player_ioLoop(int receive_sfd, int send_sfd);

// second player game input-output loop
void second_player_ioLoop(int receive_sfd, int send_sfd);

#endif

/* end of tictactoe.h file */
