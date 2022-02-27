#include "server.h"

void initsvr(struct server *svr, const struct serverdesc *desc)
{
        svr->sd = socket(AF_INET, desc->type, 0);

        if (svr->sd == -1)
                error("failed to create server socket");

        struct sockaddr_in addr = {
                .sin_addr = INADDR_ANY,
                .sin_family = AF_INET,
                .sin_port = htons(desc->port),
        };

        if (bind(svr->sd, (const struct sockaddr *)&addr, sizeof(addr)) < 0)
                error("failed to bind server socket");
}

void cleansvr(struct server *svr)
{
        close(svr->sd);
}