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


int vocale(char lettera)
{
    lettera = tolower(lettera);
    if (lettera == 'a' || lettera == 'i' || lettera == 'u' || lettera == 'o' || lettera == 'e')
    {
        return 0;
    }

    return -1;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Numero argomenti sbagliato\n");
        exit(1);
    }

    int p1p2[2], p2p0[2], pid;
    char str_vocali[10];

    pipe(p1p2);

    pid = fork();
    if (pid == 0)
    {
        close(p1p2[0]);

        close(1);
        dup(p1p2[1]);
        close(p1p2[1]);

        execl("/usr/bin/cat", "cat", argv[1], NULL);
        return -1;
    }

    close(p1p2[1]);

    pipe(p2p0);
    pid = fork();
    if (pid == 0)
    {
        close(p2p0[0]);

        int vocali = 0;
        char carattere;

        while (read(p1p2[0], &carattere, sizeof(carattere)) > 0)
        {
            if (vocale(carattere) == 0)
            {
                vocali++;
            }
        }

        close(p1p2[0]);
        sprintf(str_vocali, "%d", vocali);

        write(p2p0[1], str_vocali, strlen(str_vocali));

        close(p2p0[1]);
        exit(0);
    }

    read(p2p0[0], str_vocali, sizeof(str_vocali));

    close(p2p0[0]);
    close(p2p0[1]);

    close(p1p2[0]);
    wait(&pid);
    wait(&pid);

    printf("Il file %s contiene %s vocali\n", argv[1], str_vocali);

    return 0;
}
