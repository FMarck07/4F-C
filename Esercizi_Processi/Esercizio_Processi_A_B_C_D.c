/*Scrivi il codice sorgente di un programma in cui il processo padre genera tre processi figli.
I processi dovranno visualizzare rispettivamente:
_ "Io sono il padre A, il mio PID=..."
_ "Io sono il figlio B, il mio PID=..., il mio nome è Qui"
_ "Io sono il figlio C, il mio PID=..., il mio nome è Quo"
_ "Io sono il figlio D, il mio PID=..., il mio nome è Qua"*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int a, b, c;

    printf("Io sono il padre A, il mio PID = %d\n", getpid());

    a = fork();
    if (a == 0) {
        printf("Io sono il figlio B, il mio PID = %d, il mio nome è Qui\n", getpid());
        exit(0);
    } else if (a > 0) {
        b = fork();
        if (b == 0) {
            printf("Io sono il figlio C, il mio PID = %d, il mio nome è Quo\n", getpid());
            exit(0);
        } else if (b > 0) {
            c = fork();
            if (c == 0) {
                printf("Io sono il figlio D, il mio PID = %d, il mio nome è Qua\n", getpid());
                exit(0);
            }
        }
    }

    return 0;
}
