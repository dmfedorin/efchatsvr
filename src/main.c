#include "server.h"

#include "util/debug.h"

int main(void)
{
        int svrsd = socket(AF_INET, SOCK_STREAM, 0);

        if (svrsd == -1)
                error("failed to create socket");

        struct sockaddr_in svraddr = {
                .sin_family = AF_INET,
                .sin_addr.s_addr = INADDR_ANY,
                .sin_port = htons(1234),
        };

        int rc = bind(svrsd, (const struct sockaddr *)&svraddr,
                      sizeof(svraddr));

        if (rc < 0)
                error("failed to bind socket");

        listen(svrsd, 1);

        struct sockaddr_in cliaddr = { 0 };
        int sainsize = sizeof(struct sockaddr_in);

        int clisd = accept(svrsd, (struct sockaddr *)&cliaddr,
                           (socklen_t *)&sainsize);

        return 0;
}