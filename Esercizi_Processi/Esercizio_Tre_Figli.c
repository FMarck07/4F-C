#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

// Funzioni per calcoli
int sommaPari(int array[], int size) {
    int somma = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 == 0) {
            somma += array[i];
        }
    }
    return somma;
}

int sommaDispari(int array[], int size) {
    int somma = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 != 0) {
            somma += array[i];
        }
    }
    return somma;
}

int numeroMax(int array[], int size) {
    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

int main() {
    int array[] = {1, 3, 5, 6, 8};
    int size = sizeof(array) / sizeof(array[0]);

    // Primo figlio
    int f1 = fork();
    if (f1 == 0) {
        printf("Sono il primo figlio con PID = %d, mio padre ha PID = %d\n", getpid(), getppid());
        int somma = sommaPari(array, size);
        printf("La somma dei numeri pari è: %d\n", somma);
        exit(0);
    } else if (f1 < 0) {
        printf("Errore nella creazione del primo figlio");
        exit(1);
    }

    // Secondo figlio
    int f2 = fork();
    if (f2 == 0) {
        printf("Sono il secondo figlio con PID = %d, mio padre ha PID = %d\n", getpid(), getppid());
        int somma = sommaDispari(array, size);
        printf("La somma dei numeri dispari è: %d\n", somma);
        exit(0);
    } else if (f2 < 0) {
        printf("Errore nella creazione del secondo figlio");
        exit(1);
    }

    // Terzo figlio
    int f3 = fork();
    if (f3 == 0) {
        printf("Sono il terzo figlio con PID = %d, mio padre ha PID = %d\n", getpid(), getppid());
        int max = numeroMax(array, size);
        printf("Il massimo valore dell'array è: %d\n", max);
        exit(0);
    } else if (f3 < 0) {
        printf("Errore nella creazione del terzo figlio");
        exit(1);
    }

   
    printf("Tutti i figli hanno terminato. Processo padre (PID = %d) conclude.\n", getpid());
    return 0;
}
