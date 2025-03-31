#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/*Realizzare il comando cat file.txt | sort in linguaggio C utilizzando
le pipe e la programmazione concorrente

Osservazione: 
P0 generi P1 e successivamente generi P2*/


int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Numero errato di argomenti");
        exit(1);
    }
    int p1p0[2];
    pipe(p1p0);
    int pid = fork();
    if(pid == 0){
        close(p1p0[0]);
        close(1);
        dup(p1p0[1]);
        close(p1p0[1]);
        execl("/bin/cat","cat", argv[1], (char *)0);
        return -1;
    }

    pid = fork();
    if(pid == 0){
        close(p1p0[1]);
        close(0);
        dup(p1p0[0]);
        close(p1p0[0]);
        execl("/bin/sort","sort", (char *)0);
        return -1;
    }
    close(p1p0[1]);
    close(p1p0[0]);

    return 0;
}
