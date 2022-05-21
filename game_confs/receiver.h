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
int reciv_conf(char* in_name);

// Recive next turn board function
MyBoard reciv_board(int sfd);

#endif
/* end of receiver.h file */
