#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Numero argomenti sbagliato\n");
        exit(1);
    }

    char alfabeto[] = "abcdefghijklmnopqrstuvz";
    int fd = open(argv[1], O_CREAT, 0666);
    write(fd, alfabeto, strlen(alfabeto));
    close(fd);

    return 0;
}
