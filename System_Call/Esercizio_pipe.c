#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();

    if (pid == 0)
    {
        // Processo figlio
        close(0); // Chiudi STDIN nel processo figlio
        printf("PID del processo figlio: %d\n", getpid());

        // Eseguire il comando ls -l /proc/<pid>/fd/
        sleep(1000);
    }
    else if (pid > 0)
    {
        // Processo padre
        printf("PID del processo padre: %d\n", getpid());
        wait(NULL); // Attendi che il processo figlio termini
    }
    else
    {
        // Errore nella fork
        printf("Errore nella generazione del figlio");
    }

    return 0;
}