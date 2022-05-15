/*

 */

#include <arpa/inet.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#define ETH_P_CUSTOM 0x8888

struct Board {
  char tab[9];
}typedef MyBoard;

int reciv_conf(char* argv1){
  int sfd; 
  struct ifreq ifr;
  struct sockaddr_ll sall;

  sfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_CUSTOM));
  strncpy(ifr.ifr_name, argv1, IFNAMSIZ);
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


MyBoard reciv_turn(int sfd){
  char* frame;
  char* fdata;
  frame = malloc(ETH_FRAME_LEN);
  memset(frame, 0, ETH_FRAME_LEN);
  fdata = frame + ETH_HLEN;
  recvfrom(sfd, frame, ETH_FRAME_LEN, 0, NULL, NULL);

  MyBoard recived_board;
  for(int j = 0; j< strlen(fdata); j++){
      recived_board.tab[j] = fdata[j];
  }

  printf("Recived board: %s\n", fdata);
  free(frame);
  return recived_board;
}

void print_board(MyBoard recived_board){
  int index = 0;
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
        printf("%c", recived_board.tab[index++]);
    }
    printf("\n");
  }
}

MyBoard init_board(MyBoard my_board){
  for(int j = 0; j< 9; ++j){
      my_board.tab[j] = '_';
  }
  return my_board;
}



struct sockaddr_ll send_sall;
char* send_frame;
char* send_fdata;
int send_conf(char* argv1, char* argv2){
  int sfd, ifindex;
  struct ethhdr* fhead;
  struct ifreq ifr;

  sfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_CUSTOM));
  send_frame = malloc(ETH_FRAME_LEN);
  memset(send_frame, 0, ETH_FRAME_LEN);
  fhead = (struct ethhdr*) send_frame;
  send_fdata = send_frame + ETH_HLEN;
  strncpy(ifr.ifr_name, argv1, IFNAMSIZ);
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
  sscanf(argv2, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
         &send_sall.sll_addr[0], &send_sall.sll_addr[1], &send_sall.sll_addr[2],
         &send_sall.sll_addr[3], &send_sall.sll_addr[4], &send_sall.sll_addr[5]);
  memcpy(fhead->h_dest, &send_sall.sll_addr, ETH_ALEN);
  memcpy(fhead->h_source, &ifr.ifr_hwaddr.sa_data, ETH_ALEN);
  fhead->h_proto = htons(ETH_P_CUSTOM);
  return sfd;
}

void send_turn(int sfd, MyBoard board){
  memcpy(send_fdata, board.tab, strlen(board.tab) + 1);
  sendto(sfd, send_frame, ETH_HLEN + strlen(board.tab) + 1, 0,
         (struct sockaddr*) &send_sall, sizeof(struct sockaddr_ll));
}

MyBoard move(MyBoard my_board, int input, char OX){
  my_board.tab[input] = OX;
  return my_board;
}

int main(int argc, char** argv) {
  MyBoard board;
  board = init_board(board); 
  print_board(board);



  int send_sfd = send_conf(argv[1],argv[2]);
  int reciv_sfd = reciv_conf(argv[1]);
  int input;
  if(atoi(argv[3])==1){
    while(1){
      scanf("%i",&input);
      board = move(board, input, 'X');
      send_turn(send_sfd, board);
      board = reciv_turn(reciv_sfd);
      print_board(board);
    }
  }
  else{
    while(1){
      board = reciv_turn(reciv_sfd);
      print_board(board);
      scanf("%i",&input);
      board = move(board, input, 'O');
      send_turn(send_sfd, board);
    }
  }



  free(send_frame);
  close(reciv_sfd);
  close(send_sfd);
  return EXIT_SUCCESS;
}
