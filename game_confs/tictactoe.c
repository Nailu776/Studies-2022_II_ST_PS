/* tictactoe.c file */
#include "tictactoe.h"

#include "sender.h"
#include "receiver.h"

// Make move on board
MyBoard move(MyBoard my_board, int input, char mark){
  my_board.last_mark = mark;
  my_board.tab[input] = mark;
  return my_board;
}

// Print whole board
void print_board(MyBoard board){
  // Index in board
  int index = 0;
  // print x's possible coordinates
  printf("Last move: %c\n",board.last_mark);
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
      my_board.last_mark = '_';
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
bool match_result(MyBoard my_board, char mark){
    //win
    if(is_win(my_board, mark) == true){
        printf("You win!\n");
        return true;
    }
    //lose
    if(mark == 'X'){
        if(is_win(my_board, 'O')){
            printf("You lose.\n");
            return true;
        }
    }
    else if(is_win(my_board, 'X')){
        printf("You lose.\n");
        return true;
    }
    //game still in progress
    for(int i=0; i<9;++i){
        if(my_board.tab[i] != 'X' && my_board.tab[i] != 'O'){
            return false;
        }
    }
    //draw
    printf("Stalemate!\n");
    return true;
}


bool is_illegal(int x, int y, MyBoard board){
    if(x<0 || x>2 || y<0 || y>2){
        printf("Out of bound coordinates.\n");
        return true;
    }else if(board.tab[x+3*y] == '_')
        return false;
    else{
        printf("\nSpace occupied.\n");
        return true;
    }
}
// X player game input-output loop
void X_player_ioLoop(int sfd){
    MyBoard board = init_board();
    printf("Init board: \n");
    print_board(board);
    while(true){
        do{
            printf("x: \t");
            scanf("%i",&x);
            printf("y: \t");
            scanf("%i",&y);
        }while(is_illegal(x,y, board));
        board = move(board, (x+3*y), 'X');

        send_turn(sfd, board);
        printf("\nBoard sent: \n");
        print_board(board);
        if(match_result(board, 'X'))
            break;
        printf("Waiting for your turn...\n");
        // do {
        board = receive_board(sfd);
        // }while(board.last_mark == 'X');
        printf("\nBoard received: \n");
        print_board(board);
        if(match_result(board, 'X'))
            break;
    }
}

// O player game input-output loop
void O_player_ioLoop(int sfd){
    
    MyBoard board;
    while(true){
        printf("Waiting for your turn...\n");
        // do {
            board = receive_board(sfd);
        // }while(board.last_mark == 'O');
        printf("\nBoard received: \n");
        print_board(board);
        if (match_result(board, 'O'))
            break;

        do{
            printf("x: \t");
            scanf("%i",&x);
            printf("y: \t");
            scanf("%i",&y);
        }while(is_illegal(x,y, board));
        board = move(board, (x+3*y), 'O');

        send_turn(sfd, board);
        printf("\nBoard sent: \n");
        print_board(board);
        if(match_result(board, 'O'))
            break;
    }
}

/* end of tictactoe.c file */
