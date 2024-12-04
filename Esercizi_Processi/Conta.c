/*Scrivi il codice sorgente di un programma che permette al processo padre di generare un processo figlio:
_ sia padre che figlio visualizzano il proprio PID e il PID del proprio parente
_ padre conta da 0 a 19
_ figlio conta da 0 a 9
Manda in esecuzione più volte e descrivi il comportamento del programma.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int p = fork();
    int count = 0;
    if(p > 0){
        printf("Sono il padre PID = %d\n", getpid());
        printf("Mio figlio ha pid = %d\n", p);
        
        for(int i = 0; i < 20; i++){
            sleep(1);
            printf("%d ", count);
            count++;
        }
        printf("\n");
        count = 0;
        wait(&p);
    }else if(p == 0){
        printf("Sono il figlio PID = %d\n", getpid());
        printf("Mio padre ha pid = %d\n", getppid());
        
        for(int i = 0; i < 10; i++){
            sleep(1);
            printf("%d ", count);
            count++;
        }
        exit(0);
    }else{
        printf("Errore nella generazione del figlio");
    }
    
    return 0;
}