/* sender.h file */
#ifndef SENDER_H
// Define once
#define SENDER_H

#include <linux/if_arp.h>
#include <sys/ioctl.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "tictactoe.h"

#ifndef ETH_P_CUSTOM
#define ETH_P_CUSTOM 0x8888
#endif

struct sockaddr_ll send_sall;
char* send_frame;
char* send_fdata;

// Configure sender
int send_conf(char* int_name, char* dest_mac, int sfd);

//Send your mark
void send_mark(int sfd, char* mark);

//Send starting signal
void send_start(int sfd);

// Sending turn
void send_turn(int sfd, MyBoard board);

#endif
/* end of sender.h file */
