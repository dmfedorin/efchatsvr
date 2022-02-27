#include "server.h"

int main(void)
{
        struct server svr;

        struct serverdesc desc = {
                .port = 1234,
                .type = SOCK_STREAM,
        };

        initsvr(&svr, &desc);

        cleansvr(&svr);

        return 0;
}