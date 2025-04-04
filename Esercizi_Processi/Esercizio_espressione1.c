#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int p1, p2, status1, status2;

    // Creazione del primo figlio F1
    p1 = fork();
    if (p1 == 0) {
        // Codice eseguito da F1
        printf("F1: mio PID=%d, mio padre P ha PID=%d\n", getpid(), getppid());
        int somma1 = 1 + 2;
        printf("F1: somma 1 + 2 = %d\n", somma1);
        exit(somma1); // Restituisce il risultato al padre
    } else if (p1 > 0) {
        // Codice eseguito da P
        printf("P: mio PID=%d, mio figlio F1 ha PID=%d\n", getpid(), p1);

        // Creazione del secondo figlio F2
        p2 = fork();
        if (p2 == 0) {
            // Codice eseguito da F2
            printf("F2: mio PID=%d, mio padre P ha PID=%d\n", getpid(), getppid());
            int somma2 = 3 + 4;
            printf("F2: somma 3 + 4 = %d\n", somma2);
            exit(somma2); // Restituisce il risultato al padre
        } else if (p2 > 0) {
            // Codice eseguito da P
            printf("P: mio PID=%d, mio figlio F2 ha PID=%d\n", getpid(), p2);

            // Attesa della terminazione di F1 e F2
            wait(&status1);
            wait(&status2);

            // Estrazione dei risultati
            int risultato1 = WEXITSTATUS(status1);
            int risultato2 = WEXITSTATUS(status2);

           
            int somma_totale = risultato1 + risultato2;
            printf("P: somma totale = %d\n", somma_totale);
        } else {
            printf("Errore nella creazione di F2\n");
            return 1; 
        }
    } else {
        printf("Errore nella creazione di F1\n");
        return 1; 
    }

    return 0;
}
