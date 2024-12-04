#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Main processo padre
    // Qui genera un processo figlio
    /*int p = fork();
    if (p > 0)
    {
        // Sono nel padre
        printf("Il sono il padre PID = %d\n", getpid());
        printf("Mio figlio ha PID = %d\n", p);
    }
    else if (p < 0)
    {
        // Errore
        printf("Errore nella generazione del figlio\n");
    }
    else
    {
        // Sono il figlio
        printf("Il sono il figlio PID = %d.\n", getpid());
        printf("Mio padre ha PID = %d\n", getppid());
    }
    return 0;*/


    int p = fork();
    if(p > 0){
        printf("Sono il padre PID = %d\n", getpid());
        printf("Mio figlio ha pid = %d\n", p);
        wait(&p);
    }else if(p == 0){
        printf("Sono il figlio PID = %d\n", getpid());
        printf("Mio padre ha pid = %d\n", getppid());
        exit(0);
    }else{
        printf("Errore nella generazione del figlio");
    }
    printf("Hello World");

    return 0;
}