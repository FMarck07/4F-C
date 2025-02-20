#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// Funzione per generare un numero casuale tra min e max
int random_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    srand(time(NULL)); // Inizializzazione del generatore di numeri casuali

    // 1) Visualizza il proprio PID
    printf("Sono il padre, il mio PID è %d\n", getpid());

    // 2) Genera 4 figli: F1, F2, F3, F4
    int f1, f2, f3, f4;

    f1 = fork();
    if (f1 == 0) {
        // Codice per F1
        printf("Sono F1, il mio PID è %d, il PID di mio padre è %d\n", getpid(), getppid());
        exit(0);
    }

    f2 = fork();
    if (f2 == 0) {
        // Codice per F2
        printf("Sono F2, il mio PID è %d, il PID di mio padre è %d\n", getpid(), getppid());
        exit(0);
    }

    f3 = fork();
    if (f3 == 0) {
        // Codice per F3
        printf("Sono F3, il mio PID è %d, il PID di mio padre è %d\n", getpid(), getppid());
        exit(0);
    }

    f4 = fork();
    if (f4 == 0) {
        // Codice per F4
        printf("Sono F4, il mio PID è %d, il PID di mio padre è %d\n", getpid(), getppid());
        exit(0);
    }

    // 3) Genera 2 numeri interi random: n1, n2 compresi tra 1 e 20 diversi tra loro
    int n1, n2;
    do {
        n1 = random_range(1, 20);
        n2 = random_range(1, 20);
    } while (n1 == n2);

    // 4) Visualizza n1 e n2
    printf("n1 = %d, n2 = %d\n", n1, n2);

    // F2 dorme per n1 secondi e restituisce n2_dim
    if (f2 == 0) {
        sleep(n1);
        int n2_dim = random_range(2, 6);
        printf("F2: n2_dim = %d\n", n2_dim);
        exit(n2_dim);
    }

    // F3 dorme per n2 secondi e restituisce n3_dim
    if (f3 == 0) {
        sleep(n2);
        int n3_dim = random_range(2, 10);
        printf("F3: n3_dim = %d\n", n3_dim);
        exit(n3_dim);
    }

    // 5) Attende la terminazione di F2 e F3
    int status;
    waitpid(f2, &status, 0);
    int n2_dim = WEXITSTATUS(status);

    waitpid(f3, &status, 0);
    int n3_dim = WEXITSTATUS(status);

    // 6) Per ciascun figlio, il padre visualizza il proprio PID e quello del relativo figlio
    printf("Sono il padre, il mio PID è %d, il PID di F1 è %d\n", getpid(), f1);
    printf("Sono il padre, il mio PID è %d, il PID di F2 è %d\n", getpid(), f2);
    printf("Sono il padre, il mio PID è %d, il PID di F3 è %d\n", getpid(), f3);
    printf("Sono il padre, il mio PID è %d, il PID di F4 è %d\n", getpid(), f4);

    // F1 genera il vettore v di dimensioni n2_dim
    if (f1 == 0) {
        int v[n2_dim];
        int somma = 0;
        for (int i = 0; i < n2_dim; i++) {
            v[i] = random_range(1, 10);
            somma += v[i];
        }
        printf("F1: Somma del vettore = %d\n", somma);
        exit(0);
    }

    // F4 calcola la media dei numeri nel vettore
    if (f4 == 0) {
        double media = 0.0;
        for (int i = 0; i < n2_dim; i++) {
            media += v[i];
        }
        media /= n2_dim;
        printf("F4: Media del vettore = %.2f\n", media);
        exit((int)(media * 100)); // Restituisce la media moltiplicata per 100 per evitare perdita di precisione
    }

    // Attende la terminazione di F1 e F4
    waitpid(f1, &status, 0);
    waitpid(f4, &status, 0);

    // Visualizza il valore restituito da F4
    double media = WEXITSTATUS(status) / 100.0;
    printf("Sono il padre, il mio PID è %d, il valore medio con cui hai popolato il vettore vale %.2f\n", getpid(), media);

    return 0;
}

