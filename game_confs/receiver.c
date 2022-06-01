/* receiver.c file */
#include "receiver.h"

// Configure receiver - return socket descriptor
int receive_conf(char* in_name){
  int sfd; 
  struct ifreq ifr;
  struct sockaddr_ll sall;

  sfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_CUSTOM));
  strncpy(ifr.ifr_name, in_name, IFNAMSIZ);
  ioctl(sfd, SIOCGIFINDEX, &ifr);
  memset(&sall, 0, sizeof(struct sockaddr_ll));
  sall.sll_family = AF_PACKET;
  sall.sll_protocol = htons(ETH_P_CUSTOM);
  sall.sll_ifindex = ifr.ifr_ifindex;
  sall.sll_hatype = ARPHRD_ETHER;
  sall.sll_pkttype = PACKET_HOST;
  sall.sll_halen = ETH_ALEN;
  bind(sfd, (struct sockaddr*) &sall, sizeof(struct sockaddr_ll));
  return sfd;
}

// Receive next board in game
MyBoard receive_board(int sfd){
  // Prepare received frame
  char* frame;
  char* fdata;
  // NOTE 819: REMEMBER TO FREE ALLOCATED FRAME!
  frame = malloc(ETH_FRAME_LEN);
  memset(frame, 0, ETH_FRAME_LEN);
  // Skip eth header length
  fdata = frame + ETH_HLEN;
  // receive frame with ETH_P_CUSTOM
  recvfrom(sfd, frame, ETH_FRAME_LEN, 0, NULL, NULL);
  // New board
  MyBoard received_board;
  // Copy board from frame data
  for(int j = 0; j< strlen(fdata); j++){
      if(j == 9)
        received_board.last_mark = fdata[j];
      else
        received_board.tab[j] = fdata[j];
  }
  // NOTE 819: free alocated memory
  free(frame);
  // Return received board
  return received_board;
}

/* end of receiver.c file */
