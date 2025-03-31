#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdbool.h>

/*Si vuole realizzare un software concorrente in linguaggio C che legga un file di testo da argv[1] e
conteggi il numero di vocali presenti nel file.
Una volta effettuato il conteggio il programma principale deve mostrarlo a video.

Note operative:
P0 genera P1 il quale legge il contenuto del file usando il comando cat. 
P2 legge da pipe il flusso di caratteri e per ogni carattere verifica se è una vocale,
in caso positivo aggiorna il conteggio. 
P2 invia a P0 il totale 
P0 stampa a video il totale.

Esempio:
$ ./a.out file.txt
Nel file sono presenti 10 vocali. */

bool Vocale(char c) {
    char l = tolower(c);
    return (l == 'a' || l == 'e' || l == 'i' || l == 'o' || l == 'u');
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Numero errato di argomenti\n");
        exit(1);
    }

    int p1p0[2];
    int p2p0[2];
    char buff[10];
    int c = 0;

    // Creazione delle pipe
    if (pipe(p1p0) == -1 || pipe(p2p0) == -1) {
        perror("pipe");
        exit(1);
    }

    // Primo figlio P1: usa cat per leggere il file
    int pid = fork();
    if (pid == 0) {
        close(p1p0[0]);  // Chiudo il lato di lettura della pipe
        dup2(p1p0[1], STDOUT_FILENO);  // Redirigo lo standard output alla pipe
        close(p1p0[1]);  // Chiudo il descrittore duplicato
        execl("/bin/cat", "cat", argv[1], (char *)0);
        perror("execl");
        exit(1);
    }

    // Secondo figlio P2: conta le vocali
    pid = fork();
    if (pid == 0) {
        close(p1p0[1]);  // Chiudo il lato di scrittura della pipe P1
        close(p2p0[0]);  // Chiudo il lato di lettura della pipe P2
        char carattere;

        while (read(p1p0[0], &carattere, sizeof(carattere)) > 0) {
            if (Vocale(carattere)) {
                c++;
            }
        }
        close(p1p0[0]);  // Chiudo il lato di lettura dopo aver finito

        sprintf(buff, "%d", c);
        write(p2p0[1], buff, strlen(buff) + 1);  // Invio il conteggio al processo principale
        close(p2p0[1]);  // Chiudo il lato di scrittura
        exit(0);
    }

    // Processo principale P0: visualizza il risultato
    close(p1p0[0]);  // Chiudo entrambi i lati della prima pipe
    close(p1p0[1]);
    close(p2p0[1]);  // Chiudo il lato di scrittura della seconda pipe

    // Lettura del risultato dalla seconda pipe
    read(p2p0[0], buff, sizeof(buff));
    printf("Nel file sono presenti %s vocali.\n", buff);
    close(p2p0[0]);  // Chiudo il lato di lettura

    // Attendo i processi figli per evitare zombie
    wait(NULL);
    wait(NULL);

    return 0;
}
