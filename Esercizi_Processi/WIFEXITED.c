#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int p, pid, status;
    
    printf("P: mio PID = %d, sto per generare mio figlio F\n", getpid());
    
    p = fork();
    
    if (p > 0) // Processo padre
    {
        printf("P: mio PID = %d, mio figlio F ha PID = %d\n", getpid(), p);
        
        pid = wait(&status); // Il padre aspetta la terminazione del figlio
        
        if (WIFEXITED(status)) // Se il figlio è terminato normalmente
        {
            printf("P: mio figlio F %d ha terminato normalmente con valore di ritorno = %d\n", p, WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status)) // Se il figlio è stato terminato da un segnale
        {
            printf("P: mio figlio F non ha terminato normalmente, terminato da un segnale\n");
        }
    }
    else if (p == 0) // Processo figlio
    {
        printf("F: mio PID = %d, mio padre P ha PID = %d\n", getpid(), getppid());
        exit(25); // Il figlio termina con valore 25
    }
    else // Errore nella creazione del figlio
    {
        perror("Errore nella creazione del processo figlio");
    }

    return 0;
}
