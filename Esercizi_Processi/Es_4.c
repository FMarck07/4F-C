/*Scriva un programma C che dato un array prestabilito, prenda in input da
riga di comando un numero e lo ricerchi all'interno dell'array.
La ricerca deve essere demandata ad un processo figlio e deve essere
implementata attraverso un'apposita funzione di nome ricerca.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>


int ricercaNumero(int array[], int num, int *c){
    for(int i = 0; i<6; i++){
        if(array[i] == num){
            (*c)++;
        }
    }
    return (*c);
}


int main(int argc, char *argv[])
{
    int array[6] = {2, 2, 2, 2, 7, 4};
    int f = fork();
    if(f == 0){
        printf("Sono il figlio con PID = %d, mio padre ha PID = %d\n", getpid(), getppid());
        int numeroDaCercare = atoi(argv[1]);
        int c = 0;
        bool ricerca = ricercaNumero(array, numeroDaCercare, &c);
        
        if(c>0){
            printf("\nIl numero è presente %d volte", c);
        }else{
            printf("\nIl numero non è presente");
        }
        exit(0);
    }else if(f > 0){
        printf("Sono il padre con PID = %d, mio figlio ha PID = %d\n", getpid(), f);
        wait(&f);
    }else{
        printf("errore nella generazione del figlio");
    }

    return 0;
}