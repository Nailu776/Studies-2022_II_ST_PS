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
 * Usage:       ./game INTERFACE_NAME DEST_MAC_ADDR PLAYER 
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
  int reciv_inv(char* if_name, int reciv_sfd){
    // Prepare recived frame
    char* frame;
    char* fdata;
    // NOTE 818: REMEMBER TO FREE ALLOCATED FRAME!
    frame = malloc(ETH_FRAME_LEN);
    memset(frame, 0, ETH_FRAME_LEN);
    // Skip eth header length
    fdata = frame + ETH_HLEN;
    // Recive frame with ETH_P_CUSTOM
    recvfrom(reciv_sfd, frame, ETH_FRAME_LEN, 0, NULL, NULL);
    // Configure sending socket
    int send_sfd = send_conf(if_name, fdata);
    // NOTE 818: Release allocated memory
    free(frame);
    // Return descriptor
    return send_sfd;
  }

  //   int send_sfd = reciv_inv(argv[1], reciv_sfd);
//*/

int main(int argc, char** argv) {
  // Open descriptors
  int reciv_sfd = reciv_conf(argv[1]);
  int send_sfd = send_conf(argv[1],argv[2]);
  // Input Output game loops
  if(strcmp(argv[3],"X") == 0){
      // For first player
      first_player_ioLoop(reciv_sfd, send_sfd);
  }
  else{
      // For secound player
      secound_player_ioloop(reciv_sfd, send_sfd);
  }
  // Close descriptors 
  close(reciv_sfd);
  close(send_sfd);
  return EXIT_SUCCESS;
}

/* End of game.c file */
