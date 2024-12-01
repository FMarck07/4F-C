#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Main processo padre
    // Qui genera un processo figlio
    int p = fork();
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
    return 0;
}