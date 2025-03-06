#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define DIM 5  // Dimensione del vettore

int main() {
    pid_t p2, p3, p4, p5;  // PID dei processi figli
    int v[DIM];            // Vettore di numeri
    int somma = 0, minimo, massimo;
    float media = 0;
    int status;  // Stato di uscita dei processi figli

    // P1 genera P2
    p2 = fork();
    if (p2 == 0) {
        // Sono P2
        printf("P2: mio PID=%d, mio padre P1 ha PID=%d\n", getpid(), getppid());

        // Chiedo all'utente di inserire 5 numeri
        printf("P2: Inserisci 5 numeri interi:\n");
        for (int i = 0; i < DIM; i++) {
            scanf("%d", &v[i]);
        }

        // Mostro il vettore
        printf("P2: Vettore = [");
        for (int i = 0; i < DIM; i++) {
            printf("%d", v[i]);
            if (i < DIM - 1) printf(", ");
        }
        printf("]\n");

        // Calcolo la somma
        for (int i = 0; i < DIM; i++) {
            somma += v[i];
        }
        printf("P2: La somma è %d\n", somma);  // Stampo la somma direttamente in P2
        
        // P2 genera P3
        p3 = fork();
        if (p3 == 0) {
            // Sono P3
            printf("P3: mio PID=%d, mio padre P2 ha PID=%d\n", getpid(), getppid());

            // Calcolo il minimo
            minimo = v[0];
            for (int i = 1; i < DIM; i++) {
                if (v[i] < minimo) {
                    minimo = v[i];
                }
            }
            printf("P3: Il valore minimo è %d\n", minimo);
            exit(minimo);  // Termino P3 e restituisco il minimo
        } else {
            // P2 aspetta che P3 finisca e ottiene il valore di ritorno
            waitpid(p3, &status, 0);
            if (WIFEXITED(status)) {
                minimo = WEXITSTATUS(status);
                printf("P2: P3 ha calcolato il minimo = %d\n", minimo);
            }

            // P2 genera P4
            p4 = fork();
            if (p4 == 0) {
                // Sono P4
                printf("P4: mio PID=%d, mio padre P2 ha PID=%d\n", getpid(), getppid());

                // Calcolo il massimo
                massimo = v[0];
                for (int i = 1; i < DIM; i++) {
                    if (v[i] > massimo) {
                        massimo = v[i];
                    }
                }
                printf("P4: Il valore massimo è %d\n", massimo);
                exit(massimo);  // Termino P4 e restituisco il massimo
            } else {
                // P2 aspetta che P4 finisca e ottiene il valore di ritorno
                waitpid(p4, &status, 0);
                if (WIFEXITED(status)) {
                    massimo = WEXITSTATUS(status);
                    printf("P2: P4 ha calcolato il massimo = %d\n", massimo);
                }

                // P2 genera P5
                p5 = fork();
                if (p5 == 0) {
                    // Sono P5
                    printf("P5: mio PID=%d, mio padre P2 ha PID=%d\n", getpid(), getppid());

                    // Calcolo la media
                    for (int i = 0; i < DIM; i++) {
                        media += v[i];
                    }
                    media /= DIM;
                    printf("P5: La media è %.2f\n", media);
                    exit((int)media);  // Termino P5 e restituisco la media (troncata a intero)
                } else {
                    // P2 aspetta che P5 finisca e ottiene il valore di ritorno
                    waitpid(p5, &status, 0);
                    if (WIFEXITED(status)) {
                        media = WEXITSTATUS(status);
                        printf("P2: P5 ha calcolato la media = %.2f\n", (float)media);
                    }
                    exit(somma);

                    // P2 termina
                    exit(0);
                }
            }
        }
    } else {
        // Sono P1
        printf("P1: mio PID=%d, ho generato P2 con PID=%d\n", getpid(), p2);

        // P1 aspetta che P2 finisca e ottiene il valore di ritorno
        waitpid(p2, &status, 0);
        if (WIFEXITED(status)) {
            somma = WEXITSTATUS(status);
            printf("P1: P2 ha calcolato la somma = %d\n", somma);
        }
    }

    return 0;
}