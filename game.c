/*
 * game.c file
 * 2022 JH139940 SK139959
 *
 * OPTION:      JOIN or START 
 * NOTE:        OPTION is written in capital letters.
 * If you enter START you create a new game and have to wait for another player,
 * JOIN means that you want to join an existing game and if there is a player waiting, the game begins.
 * 
 * Compilation: make
 * Usage:       ./game INTERFACE_NAME OPTION 
 * NOTE:        This program requires root privileges.
*/

// Included libs
#include <unistd.h>
#include <time.h>
#include "./game_confs/tictactoe.h"
#include "./game_confs/receiver.h"
#include "./game_confs/sender.h"

/* 
  // Don't know if it will be used.
  // and if it works.
  // Receive an invitation
  int receive_inv(char* if_name, int receive_sfd){
    // Prepare received frame
    char* frame;
    char* fdata;
    // NOTE 818: REMEMBER TO FREE ALLOCATED FRAME!
    frame = malloc(ETH_FRAME_LEN);
    memset(frame, 0, ETH_FRAME_LEN);
    // Skip eth header length
    fdata = frame + ETH_HLEN;
    // receive frame with ETH_P_CUSTOM
    recvfrom(receive_sfd, frame, ETH_FRAME_LEN, 0, NULL, NULL);
    // Configure sending socket
    int send_sfd = send_conf(if_name, fdata);
    // NOTE 818: Release allocated memory
    free(frame);
    // Return descriptor
    return send_sfd;
  }

  //   int send_sfd = receive_inv(argv[1], receive_sfd);
//*/
#define MAC_BROADCAST "FF:FF:FF:FF:FF:FF"

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

void _connect(char* if_name, char* option){  
  //Creating socket descriptor
  int sfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_CUSTOM));
  //Configuring receiver
  receive_conf(if_name, sfd);
  //Configuring sender
  send_conf(if_name, MAC_BROADCAST, sfd);
  //JOIN or START the game
  if(strcmp(option,"START") == 0){
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
  } else if(strcmp(option,"JOIN") == 0){
    printf("Joining the game...\n");
    //sending join message
    send_start(sfd);
    //Receiveing your mark and choosing player loop
    player_loop(sfd, strcmp(receive_mark(sfd), "X") == 0);
    
  }
  else{
    printf("Incorrect OPTION, terminating.\n");
    exit(0);
  }
}

int main(int argc, char** argv) {
  _connect(argv[1],argv[2]);
  return EXIT_SUCCESS;
}

/* End of game.c file */
