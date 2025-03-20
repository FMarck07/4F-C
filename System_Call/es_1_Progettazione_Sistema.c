/*Scrivere un programma concorrente che realizzi il seguente comando:

cat costituzione.txt | more*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Errore negli argomenti");
        return -1;
    }
    int pipe1[2];
    pipe(pipe1);
    int f = fork();
    if (f == 0)
    {
        close(pipe1[0]); 
        close(1); //output leggere
        dup(pipe1[1]);
        close(pipe1[1]);
        execl("/bin/cat", "cat", argv[1], (char *)0);
    }
    else if(f > 0)
    {
        close(pipe1[1]);
        close(0); //input scrivere
        dup(pipe1[0]);
        close(pipe1[0]);
        execl("/bin/more", "more", (char *)0);
        //execl("/bin/less", "less", (char *)0); //Sia avanti sia indietro
    }

    close(pipe1[0]);
    close(pipe1[1]);
    return 0;
}
