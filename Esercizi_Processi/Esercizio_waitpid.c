#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int p1, p2, status1, status2;

    printf("P: mio PID = %d, sto per generare i miei figli F1 e F2\n", getpid());

    // Creazione del primo figlio F1
    p1 = fork();
    if (p1 == 0) {
        // Codice eseguito da F1
        printf("F1: mio PID = %d, mio padre P ha PID = %d\n", getpid(), getppid());
        sleep(2); // F1 dorme per 2 secondi
        printf("F1: ho dormito per 2 secondi\n");
        exit(2); // Restituisce 2 al padre
    } else if (p1 > 0) {
        // Codice eseguito da P
        printf("P: mio PID = %d, mio figlio F1 ha PID = %d\n", getpid(), p1);

        // Creazione del secondo figlio F2
        p2 = fork();
        if (p2 == 0) {
            // Codice eseguito da F2
            printf("F2: mio PID = %d, mio padre P ha PID = %d\n", getpid(), getppid());
            sleep(4); // F2 dorme per 4 secondi
            printf("F2: ho dormito per 4 secondi\n");
            exit(4); // Restituisce 4 al padre
        } else if (p2 > 0) {
            // Codice eseguito da P
            printf("P: mio PID = %d, mio figlio F2 ha PID = %d\n", getpid(), p2);

            // Attesa della terminazione di F2 (il figlio che dorme di più)
            wait(&status2);

            // Estrazione del risultato di F2
            if (WIFEXITED(status2)) {
                int tempo_dormito = WEXITSTATUS(status2);
                printf("P: F2 ha dormito per %d secondi\n", tempo_dormito);
            }
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
