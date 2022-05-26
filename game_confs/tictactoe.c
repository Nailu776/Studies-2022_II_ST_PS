/* tictactoe.c file */
#include "tictactoe.h"

#include "sender.h"
#include "receiver.h"

// Try another coords
bool retry = true;

// Make move on board
MyBoard move(MyBoard my_board, int input, char mark){
  my_board.tab[input] = mark;
  return my_board;
}

// Print whole board
void print_board(MyBoard board){
  // Index in board
  int index = 0;
  // print x's possible coordinates
  printf("x: \t0\t1\t2\n");
  // print y 
  char y_tab[3] = {'0','1','2'};
  printf("y:\n");
  for(int i = 0; i < 3; ++i){
    // print y's possible coordinates
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
bool is_win(MyBoard my_board, char mark){
    bool result = false;
    int i = 0, j = 0;
    // X X X|_ _ _|_ _ _
    // _ _ _|X X X|_ _ _ 
    // _ _ _|_ _ _|X X X
    for(j = 0; j < 3; ++j){
        for(i = 0; i < 3; ++i){
            //handling index out of bounds exception
            if(i+3*j >= sizeof(my_board.tab)){
                printf("%s\n","Index out of bounds. Terminating program.\n");
                abort();
            }
            if(my_board.tab[i+3*j] != mark){
                result = false; 
                break;
            }
            result = true;
        }
        if(result) return result;
    }
    i = 0, j = 0;
    // X _ _ | _ X _ | _ _ X
    // X _ _ | _ X _ | _ _ X
    // X _ _ | _ X _ | _ _ X
    for(j = 0; j < 3; ++j){
        for(i = 0; i < 3; ++i){
            if(my_board.tab[i*3+j] != mark){
                result = false; 
                break;
            }
            result = true;
        }
        if(result) return result;
    }
    // X _ _
    // _ X _
    // _ _ X 
    if( my_board.tab[0] == mark && my_board.tab[4] == mark && my_board.tab[8] == mark )
        return true;
    // _ _ X
    // _ X _
    // X _ _ 
    if( my_board.tab[2] == mark && my_board.tab[4] == mark && my_board.tab[6] == mark )
        return true;
    // not yet
    return false;
}
// 1 - win
// -1 - lose
// 0 - draw
// 2 - game still in progress
int match_result(MyBoard my_board, char mark){
    //win
    if(is_win(my_board, mark) == true){
        return 1;
    }
    //lose
    if(mark == 'X'){
        if(is_win(my_board, 'O') == true)
            return -1;
    }
    else if(is_win(my_board, 'X') == true)
            return -1;
    //undecided
    for(int i=0; i<9;++i){
        if(my_board.tab[i] != 'X' && my_board.tab[i] != 'O'){
            return 2;
        }
    }
    //draw
    return 0;    
}
// First player game input-output loop
void first_player_ioLoop(int receive_sfd, int send_sfd){
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
            printf("\nTry to enter unoccupied/correct coords.\n");
      }
      retry = true;
      board = move(board, (x+3*y), 'X');

      send_turn(send_sfd, board);
      printf("\nBoard sent: \n");
      print_board(board);

      if (match_result(board, 'X') == 1){
          printf("You win!\n");
          break;
      }
      else if(match_result(board, 'X') == 0){
          printf("Stalemate!\n");
          break;
      }

      board = receive_board(receive_sfd);
      printf("\nBoard received: \n");
      print_board(board);

      if (match_result(board, 'X') == -1){
          printf("You lost!\n");
          break;
      }
      else if(match_result(board, 'X') == 0){
          printf("Stalemate!\n");
          break;
      }
    }
}

// Second player game input-output loop
void second_player_ioLoop(int receive_sfd, int send_sfd){
    MyBoard board;
    printf("Wait for opponent.\n");
    while(true){
      board = receive_board(receive_sfd);
      printf("Board received: \n");
      print_board(board);
      if (is_win(board, 'X')){
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
            printf("\nTry to enter unoccupied/correct coords.\n");
      }
      retry = true;
      board = move(board, (x+3*y), 'O');

      send_turn(send_sfd, board);
      printf("\nBoard sent: \n");
      print_board(board);
      if (is_win(board, 'O')){
          printf("You won.\n");
          break;
      }
    }
}

/* end of tictactoe.c file */
