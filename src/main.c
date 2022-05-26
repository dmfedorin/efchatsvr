#include "server.h"

#include <stdlib.h>

static struct server svr;

static inline void clean(void)
{
        cleansvr(&svr);
}

int main(void)
{
        atexit(clean);

        struct serverdesc desc = {
                .port = 80, .proto = IPPROTO_TCP, .type = SOCK_STREAM,
        };

        printf("port %d\n", 80);

        initsvr(&svr, &desc);

        acceptclients(&svr, 1);

        for (int i = 0; i <= svr.maxclientsd; i++) {
                if (!FD_ISSET(i, &svr.clientsds))
                        continue;

                serveclient(&svr, i);
        }

        return 0;
}
