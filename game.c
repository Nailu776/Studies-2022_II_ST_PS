/*
 * game.c file
 * 2022 JH139940 SK139959
 *
 * Compilation: make
 * Usage:       ./game INTERFACE_NAME  
 * NOTE:        This program requires root privileges.
*/

// Included libs
#include <unistd.h>
#include <time.h>
#include "./game_confs/tictactoe.h"
#include "./game_confs/receiver.h"
#include "./game_confs/sender.h"

#define MAC_BROADCAST "FF:FF:FF:FF:FF:FF"

// Wait untill readable or timed out
int readable(int fd, int tout) {
  fd_set rset;
  struct timeval tv;
  FD_ZERO(&rset);
  FD_SET(fd, &rset);
  tv.tv_sec = tout;
  tv.tv_usec = 0;
  return select(fd + 1, &rset, NULL, NULL, &tv);
}

void player_loop(int sfd, bool decision){
  if(decision){
    printf("Yourmark: X\n");
    send_mark(sfd,"O");
    X_player_ioLoop(sfd);
  }
  else{
    printf("Yourmark: O\n");
    send_mark(sfd,"X");
    O_player_ioLoop(sfd);
  }
}

void _connect(char* if_name){  
  // Creating socket descriptor
  int sfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_CUSTOM));
  // Configuring receiver
  receive_conf(if_name, sfd);
  // Configuring sender
  send_conf(if_name, MAC_BROADCAST, sfd);
  // JOIN or START the game
  printf("Trying to join the game...\n");
  // Sending join message
  send_start(sfd);
  // Trying to receive mark for 10 sec
  if (readable(sfd, 10) > 0){
    // Receiveing your mark and choosing player loop
    player_loop(sfd, strcmp(receive_mark(sfd), "X") == 0);
  }  else{
    printf("Nobody is waiting for another player...\n");
    printf("Trying to start new game...\n");
    printf("Waiting for another player to join the game.\n");
    if(receive_start(sfd)){
      printf("The game is about to start.\n");
      // Choosing mark by random
      srand(time(0));
      // Choosing player loop
      player_loop(sfd, rand() % 2);
    }
    else{
      printf("Didn't receive a correct start signal, terminating.");
      exit(0);
    }
  }
}

int main(int argc, char** argv) {
  _connect(argv[1]);
  return EXIT_SUCCESS;
}

/* End of game.c file */
