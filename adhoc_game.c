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
#include <stdbool.h>
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

//   printf("Recived board: %s\n", fdata);
  free(frame);
  return recived_board;
}

void print_board(MyBoard recived_board){
  int index = 0;
  char tab[3] = {'0','1','2'};
//   printf("BOARD:\n");
  printf("x: \t0\t1\t2\n");
  printf("y:\n");
  for(int i = 0; i < 3; ++i){
    printf("%c\t",tab[i]);
    for(int j = 0; j < 3; ++j){
        printf("%c\t", recived_board.tab[index++]);
    }
    printf("\n");
  }
  printf("\n");
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

int main(int argc, char** argv) {
  MyBoard board;
  board = init_board(board); 
  printf("Init board: \n");
  print_board(board);



  int send_sfd = send_conf(argv[1],argv[2]);
  int reciv_sfd = reciv_conf(argv[1]);
  int x, y;
  bool retry = true;
  if(atoi(argv[3])==1){
    while(1){
      while(retry){
        printf("x: \t");
        scanf("%i",&x);
        printf("y: \t");
        scanf("%i",&y);
        if(board.tab[x+3*y] == '_')
            retry = false;
        else
            printf("\nTry enter unoccupied coords.\n");
      }
      retry = true;
      board = move(board, (x+3*y), 'X');

      send_turn(send_sfd, board);
      printf("\nBoard sended: \n");
      print_board(board);
      if (check_char_won(board, 'X')){
          printf("You won.\n");
          break;
      }

      board = reciv_turn(reciv_sfd);
      printf("\nBoard recived: \n");
      print_board(board);
      if (check_char_won(board, 'O')){
          printf("You lost.\n");
          break;
      }
    }
  }
  else{
    while(1){
      board = reciv_turn(reciv_sfd);
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
            printf("\nTry enter unoccupied coords.\n");
      }
      retry = true;
      board = move(board, (x+3*y), 'O');

      send_turn(send_sfd, board);
      printf("Board sended: \n");
      print_board(board);
      if (check_char_won(board, 'O')){
          printf("You won.\n");
          break;
      }
    }
  }



  free(send_frame);
  close(reciv_sfd);
  close(send_sfd);
  return EXIT_SUCCESS;
}
