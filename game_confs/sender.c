/* 
 * sender.c file 
 * 2022 JH139940 SK139959
 * Compilation: make
*/
#include "sender.h"

// Configure sender
int send_conf(char* int_name, char* dest_mac, int sfd){
  int ifindex;
  struct ethhdr* fhead;
  struct ifreq ifr;

  send_frame = malloc(ETH_FRAME_LEN);
  memset(send_frame, 0, ETH_FRAME_LEN);
  fhead = (struct ethhdr*) send_frame;
  send_fdata = send_frame + ETH_HLEN;
  strncpy(ifr.ifr_name, int_name, IFNAMSIZ);
  ioctl(sfd, SIOCGIFINDEX, &ifr);
  ifindex = ifr.ifr_ifindex;
  ioctl(sfd, SIOCGIFHWADDR, &ifr);
  memset(&send_sall, 0, sizeof(struct sockaddr_ll));
  send_sall.sll_family = AF_PACKET;
  send_sall.sll_protocol = htons(ETH_P_CUSTOM);
  send_sall.sll_ifindex = ifindex;
  send_sall.sll_hatype = ARPHRD_ETHER;
  send_sall.sll_pkttype = PACKET_OUTGOING;
  send_sall.sll_halen = ETH_ALEN;
  sscanf(dest_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
         &send_sall.sll_addr[0], &send_sall.sll_addr[1], &send_sall.sll_addr[2],
         &send_sall.sll_addr[3], &send_sall.sll_addr[4], &send_sall.sll_addr[5]);
  memcpy(fhead->h_dest, &send_sall.sll_addr, ETH_ALEN);
  memcpy(fhead->h_source, &ifr.ifr_hwaddr.sa_data, ETH_ALEN);
  fhead->h_proto = htons(ETH_P_CUSTOM);
  return sfd;
}

//Sending game Start
void send_mark(int sfd, char* mark){
  //message containg X or O
  int message_len = 1;
  //loading message
  memcpy(send_fdata, mark, strlen(mark) + 1);
  //sending frame; 
  sendto(sfd, send_frame, ETH_HLEN + message_len + 1, 0,
         (struct sockaddr*) &send_sall, sizeof(struct sockaddr_ll));
}

//Sending game Start
void send_start(int sfd){
  //message containg the word "START"
  char* start_msg = "START";
  //loading start message 
  memcpy(send_fdata, start_msg, strlen(start_msg) + 1);
  //sending frame; 
  sendto(sfd, send_frame, ETH_HLEN + strlen(start_msg) + 1, 0,
         (struct sockaddr*) &send_sall, sizeof(struct sockaddr_ll));
}

// Sending turn
void send_turn(int sfd, MyBoard board){
  //message containg 9 fields and a mark
  int message_len = 10;
  //loading all 9 fields on the board
  memcpy(send_fdata, board.tab, strlen(board.tab));
  //loading last mark put on the board
  memcpy(send_fdata+9, &(board.last_mark), 1);
  //sending frame; 
  sendto(sfd, send_frame, ETH_HLEN + message_len + 1, 0,
         (struct sockaddr*) &send_sall, sizeof(struct sockaddr_ll));
}
/* end of sender.c file */
