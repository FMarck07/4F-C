#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*Scrivere un programma concorrente che realizzi il seguente comando:

cat costituzione.txt | more */



int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Numero errato di argomenti");
        exit(1);
    }
    int p1p0[2];
    pipe(p1p0);
    int pid = fork();
    if(pid == 0){ //cat --> scrivere
        close(p1p0[0]);
        close(1);
        dup(p1p0[1]);
        close(p1p0[1]);
        execl("/bin/cat", "cat", argv[1], (char *)0);
        return -1;
    }
    close(p1p0[1]);
    close(0);
    dup(p1p0[0]);
    close(p1p0[0]);
    execl("/bin/more", "more", (char *)0);

    close(p1p0[0]);

    return 0;

}
