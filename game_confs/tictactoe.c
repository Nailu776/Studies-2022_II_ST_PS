/* tictactoe.c file */
#include "tictactoe.h"

#include "sender.h"
#include "receiver.h"

// Try another coords
bool retry = true;

// Make move on board
MyBoard move(MyBoard my_board, int input, char OX){
  my_board.tab[input] = OX;
  return my_board;
}

// Print whole board
void print_board(MyBoard board){
  // Index in board
  int index = 0;
  // print x possible co-ordinates
  printf("x: \t0\t1\t2\n");
  // print y 
  char y_tab[3] = {'0','1','2'};
  printf("y:\n");
  for(int i = 0; i < 3; ++i){
    // print y possible co-ordinates
    printf("%c\t",y_tab[i]);
    for(int j = 0; j < 3; ++j){
        // print char from board
        printf("%c\t", board.tab[index++]);
    }
    // print eol to print next row in board
    printf("\n");
  }
  printf("\n");
}

// Init new board
MyBoard init_board(){
  MyBoard my_board;
  for(int j = 0; j< 9; ++j){
      // "_" as blank space
      my_board.tab[j] = '_';
  }
  return my_board;
}

// Check if someone won
bool check_char_won(MyBoard my_board, char OX){
    bool temp = false;
    int i = 0, j = 0;
    // X X X 
    // _ _ _ X X X 
    // _ _ _ _ _ _ X X X
    for(j = 0; j < 3; ++j){
        for(i = 0; i < 3; ++i){
            if(my_board.tab[i+3*j] != OX){
                temp = false; 
                break;
            }
            temp = true;
        }
        if(temp) return temp;
    }
    i = 0, j = 0;
    // X _ _ | _ X _ | _ _ X
    // X _ _ | _ X _ | _ _ X
    // X _ _ | _ X _ | _ _ X
    for(j = 0; j < 3; ++j){
        for(i = 0; i < 3; ++i){
            if(my_board.tab[i*3+j] != OX){
                temp = false; 
                break;
            }
            temp = true;
        }
        if(temp) return temp;
    }
    // X _ _
    // _ X _
    // _ _ X 
    if( my_board.tab[0] == OX && my_board.tab[4] == OX && my_board.tab[8] == OX )
        return true;
    // _ _ X
    // _ X _
    // X _ _ 
    if( my_board.tab[2] == OX && my_board.tab[4] == OX && my_board.tab[6] == OX )
        return true;
    // not yet
    return false;
}

// First player game input-output loop
void first_player_ioLoop(int reciv_sfd, int send_sfd){
    MyBoard board = init_board();
    printf("Init board: \n");
    print_board(board);
    while(true){
      while(retry){
        printf("x: \t");
        scanf("%i",&x);
        printf("y: \t");
        scanf("%i",&y);
        if(board.tab[x+3*y] == '_')
            retry = false;
        else
            printf("\nTry enter unoccupied/correct coords.\n");
      }
      retry = true;
      board = move(board, (x+3*y), 'X');

      send_turn(send_sfd, board);
      printf("\nBoard sent: \n");
      print_board(board);
      if (check_char_won(board, 'X')){
          printf("You won.\n");
          break;
      }

      board = reciv_board(reciv_sfd);
      printf("\nBoard recived: \n");
      print_board(board);
      if (check_char_won(board, 'O')){
          printf("You lost.\n");
          break;
      }
    }
}

// Secound player game input-output loop
void secound_player_ioloop(int reciv_sfd, int send_sfd){
    MyBoard board;
    printf("Wait for opponent.\n");
    while(true){
      board = reciv_board(reciv_sfd);
      printf("Board recived: \n");
      print_board(board);
      if (check_char_won(board, 'X')){
          printf("You lost.\n");
          break;
      }

      while(retry){
        printf("x: \t");
        scanf("%i",&x);
        printf("y: \t");
        scanf("%i",&y);
        if(board.tab[x+3*y] == '_')
            retry = false;
        else
            printf("\nTry enter unoccupied/correct coords.\n");
      }
      retry = true;
      board = move(board, (x+3*y), 'O');

      send_turn(send_sfd, board);
      printf("\nBoard sent: \n");
      print_board(board);
      if (check_char_won(board, 'O')){
          printf("You won.\n");
          break;
      }
    }
}

/* end of tictactoe.c file */
