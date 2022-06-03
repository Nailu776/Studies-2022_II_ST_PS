/* receiver.h */
#ifndef RECEIVER_H
// Define once
#define RECEIVER_H

#include <linux/if_arp.h>
#include <sys/ioctl.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "tictactoe.h"

#ifndef ETH_P_CUSTOM
#define ETH_P_CUSTOM 0x8888
#endif

// Convigure receiver
int receive_conf(char* in_name, int sfd);

//Receive your mark
char* receive_mark(int sfd);

//Receive starting signal
bool receive_start(int sfd);

// receive next turn board function
MyBoard receive_board(int sfd);

#endif
/* end of receiver.h file */
