
#ifndef _HEAD_H_
# define _HEAD_H_

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# include <signal.h>
# include <time.h>
# include <ctype.h>
# include <fcntl.h>
# include <pthread.h>

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# include <string>
# include <iostream>
# include <map>
# include <sstream>

# include "inits.hh"
# include "utils.hh"
# include "color.hh"
# include "core.hh"
# include "listener.hh"
# include "Packet.hh"
# include "server.hh"
# include "user.hh"
# include "actions.hh"
# include "clientrcv.hh"
# include "dataBuilder.hh"

// Declaration of global variables
extern Datas * data;
extern Utils * utils;
extern Colors * col;
extern void killed(int sig);

/* main.c */
pthread_t listen_tome(Clientrcv * crcv);
void * client_listener(void * cli);

#endif
