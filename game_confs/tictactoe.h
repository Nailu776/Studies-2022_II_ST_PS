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
bool check_char_won(MyBoard my_board, char OX);

// First player game input-output loop
void first_player_ioLoop(int reciv_sfd, int send_sfd);

// Secound player game input-output loop
void secound_player_ioloop(int reciv_sfd, int send_sfd);

#endif

/* end of tictactoe.h file */
