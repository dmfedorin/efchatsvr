#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "util/debug.h"

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

struct server {
        int sd, maxclientsd;
        fd_set clientsds;
        bool running;
};

struct serverdesc {
        int type, proto;
        uint16_t port;
};

void initsvr(struct server *svr, const struct serverdesc *desc);

void cleansvr(struct server *svr);

// should be running in a separate thread
void acceptclients(struct server *svr, int maxcons);

// a new thread should be started for every client connection
void serveclient(struct server *svr, int clientsd);

#endif