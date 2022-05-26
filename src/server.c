#include "server.h"

#define RECVBUFSIZE 4096

void initsvr(struct server *svr, const struct serverdesc *desc)
{
        svr->sd = socket(AF_INET, desc->type, desc->proto);

        if (svr->sd == -1)
                error("failed to create server socket");

        struct sockaddr_in addr = {
                .sin_addr = INADDR_ANY, .sin_family = AF_INET,
                .sin_port = htons(desc->port),
        };

        if (bind(svr->sd, (const struct sockaddr *)&addr, sizeof(addr)) < 0)
                error("failed to bind server socket");

        FD_ZERO(&svr->clientsds);

        svr->running = true;
}

void cleansvr(struct server *svr)
{
        close(svr->sd);
}

// should be running in a separate thread
void acceptclients(struct server *svr, int maxcons)
{
        if (listen(svr->sd, maxcons) == -1)
                error("failed to listen on server socket");

        int remcons = maxcons;

        while (remcons > 0 && svr->running) {
                struct sockaddr_in incaddr = { 0 };
                int addrsize = sizeof(struct sockaddr_in);

                int incsd = accept(svr->sd, (struct sockaddr *)&incaddr,
                                   &addrsize);

                if (incsd == -1)
                        error("failed to accept server connection");

                printf("client connection on %d from %s\n", incsd,
                       inet_ntoa(incaddr.sin_addr));

                FD_SET(incsd, &svr->clientsds);

                if (incsd > svr->maxclientsd)
                        svr->maxclientsd = incsd;

                remcons--;
        }
}

static void sendall(struct server *svr, const char *msg)
{
        for (int i = 0; i <= svr->maxclientsd; i++) {
                if (!FD_ISSET(i, &svr->clientsds))
                        continue;

                if (send(i, msg, strlen(msg), 0) == -1)
                        error("failed to send server message");
        }

        printf("send: \"%s\" to all\n", msg);
}

// a new thread should be started for every client connection
void serveclient(struct server *svr, int clientsd)
{
        while (svr->running) {
                char recvbuf[RECVBUFSIZE] = { 0 };

                if (recv(clientsd, recvbuf, RECVBUFSIZE, 0) < 0)
                        warning("failed to recieve client message");

                printf("recv: \"%s\" from %d\n", recvbuf, clientsd);

                if (strcmp(recvbuf, ">exit") == 0)
                        svr->running = false;
                
                sendall(svr, recvbuf);
        }
}
