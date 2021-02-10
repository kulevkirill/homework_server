#include "my_server.h"


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("ERROR: number of arguments!\n");

        return 0;
    }

    int sk = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sk == -1)
    {
        perror("ERROR: unable to create socket!\n");

        return 1;
    }

    struct sockaddr_un name = {AF_UNIX, PATH};

    if (connect(sk, &name, sizeof(name)) == -1)
    {
        perror("ERROR: unable to connect to socket!\n");

        return 1;
    }

    if (write(sk, argv[1], strlen(argv[1])) == -1)
    {
        perror("ERROR: unable to write");

        return 1;
    }   

    close (sk);
    
    return 0;
}