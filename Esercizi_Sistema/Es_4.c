#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/*Si scriva un’applicazione concorrente che presenti la seguente interfaccia:

cercaStringhe FileIn.txt

dove FileIn.txt è un nome assoluto di file.

L’applicazione deve contare il numero di volte in cui un insieme di stringhe
che l’utente inserisce da terminale (una alla volta) compaiono all’interno
del file passato come parametro in argv[1].
L’applicazione termina quando l’utente inserisce la stringa “fine”.

L’applicazione deve visualizzare il numero di volte in cui ogni stringa
compare nel file e anche, al termine dell’esecuzione, il numero totale di
stringhe trovate nel file.

L'applicazione dovrà tenere conto dell'eventuale molteplicità di una parola
dentro alla stessa stringa, per fare questo si consiglia di invocare grep
con il flag -ow e redirezionare il suo output in wc (invocato con il flag -l).*/

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Numero errato di argomenti");
        exit(1);
    }
    int p1p0[2];
    char buff[1024];
    char stringa[1000];
    int ctot = 0;
    pipe(p1p0);
    while(1){
        printf("\nInserisci la parola che vuoi cercare\n");
        scanf("%s", stringa);
        if(strcmp(stringa, "fine") == 0){
            close(p1p0[0]);
            close(p1p0[1]);
            printf("Numero di parole trovate %d\n", ctot);
            exit(1);
        }
        int pid = fork();
        if(pid == 0){
            close(p1p0[0]);
            close(1);
            dup(p1p0[1]);
            close(p1p0[1]);
            execl("/bin/grep","grep", "-ow", stringa, argv[1], (char *)0);
            return -1;
        }
        int p2p0[2];
        pipe(p2p0);
        pid = fork();
        if(pid == 0){
            close(p1p0[1]);
            close(0);
            dup(p1p0[0]);
            close(p1p0[0]);

            close(p2p0[0]);
            close(1);
            dup(p2p0[1]);
            close(p2p0[1]);
            execl("/bin/wc","wc", "-l", (char *)0);
            return -1;
        }

        
        close(p1p0[1]);
        close(p2p0[1]);
        close(p1p0[0]);

        read(p2p0[0], buff, sizeof(buff));
        printf("\nNumero di stringhe trovate %d\n", atoi(buff));
        ctot+=atoi(buff);
        close(p1p0[0]);
    }
    
    return 0;
}