/*
 * game.c file
 * 2022 JH139940 SK139959
 *
 * PLAYER:      X or O 
 * NOTE:        Player is written in capital letters.
 * If you enter X you get first player mode,
 * else you are second no matter what input you enter.
 * 
 * Compilation: make
 * Usage:       ./game INTERFACE_NAME PLAYER 
 * NOTE:        This program requires root privileges.
*/

// Included libs
#include <unistd.h>
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

int _connect(char* in_name){  
  int sfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_CUSTOM));
  receive_conf(in_name, sfd);
  send_conf(in_name,MAC_BROADCAST, sfd);
  return sfd;
}

int main(int argc, char** argv) {
  // Open descriptors
  int sfd = _connect(argv[1]);
  // Input Output game loops
  if(strcmp(argv[2],"X") == 0){
      // For first player
      first_player_ioLoop(sfd);
  }
  else if (strcmp(argv[2],"O") == 0){
      // For second player
      second_player_ioLoop(sfd);
  }
  else{
      printf("Invalid argument, terminating program.\n");
  }
  // Close descriptors 
  close(sfd);
  return EXIT_SUCCESS;
}

/* End of game.c file */
