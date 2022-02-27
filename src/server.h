#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "util/debug.h"

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdint.h>

struct server {
        int sd;
        fd_set clientsds;
};

struct serverdesc {
        int type;
        uint16_t port;
};

void initsvr(struct server *svr, const struct serverdesc *desc);

void cleansvr(struct server *svr);

void listensvr(struct server *svr);

#endif