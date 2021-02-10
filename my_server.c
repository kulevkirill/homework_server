#include "my_server.h"

#define STR "DO YOU KNOW DA WAE???\n"

int main()
{
    int sk = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sk == -1)
    {
        perror("ERROR: unable to create socket!\n");

        return 1;
    }

    const struct sockaddr_un name = {AF_UNIX, PATH};

    if (bind(sk, &name, sizeof(name)) == -1)
    {
        perror("ERROR: unable to bind socket!\n");
        close(sk);

        return 1;
    }

    if (listen(sk, 20) == -1)
    {
        perror("ERROR: unable to listen socket!\n");
        close(sk);

        return 1;
    }

    while (1)
    {
        int client_sk = accept(sk, NULL, NULL);
        if (client_sk == -1)
        {
            perror("ERROR: unable to accept!\n");

            return 1;
        }

        char command[BUFSZ] = {0};
        if (read(client_sk, command, BUFSZ) < 0)
        {
            printf("ERROR: unable to read client!\n");
            close(sk);

            return 1;
        }

        if (strcmp(command, "print") == 0)
        {
            printf(STR);
        }
        else
        {
            if (strcmp(command, "exit") == 0)
                break;

            printf("ERROR: wrong type of command!\n");
        }

        close(client_sk);
    }

    unlink(PATH);

    return 0;
}