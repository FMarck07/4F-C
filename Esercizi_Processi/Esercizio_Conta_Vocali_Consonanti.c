/*Contiene un array prestabilito di stringhe.
Crea due processi figli:
Il primo figlio calcola la lunghezza totale delle vocali nelle stringhe.
Il secondo figlio calcola la lunghezza totale delle consonanti nelle stringhe.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

int calcolaLunghezzaVocali(char *array[], int size) {
    int somma = 0;
    for (int i = 1; i < size; i++) {
        for(int j = 0; j < strlen(array[i]); j++){
            if(array[i][j] == 'a' || array[i][j] == 'e' || array[i][j] == 'i' || array[i][j] == 'o' || array[i][j] == 'u'){
               somma++; 
            }
        }
        /*
        char primoCarattere = tolower(array[i][0]); // Controllo primo carattere della stringa
        if (primoCarattere == 'a' || primoCarattere == 'e' || primoCarattere == 'i' || primoCarattere == 'o' || primoCarattere == 'u') {
            somma += strlen(array[i]);
        }*/
    }
    return somma;
}

int calcolaLunghezzaConsonanti(char *array[], int size) {
    int somma = 0;
    for (int i = 1; i < size; i++) {
        for(int j = 0; j < strlen(array[i]); j++){
            if(array[i][j] != 'a' && array[i][j] != 'e' && array[i][j] != 'i' && array[i][j] != 'o' && array[i][j] != 'u'){
               somma++; 
            }
        }
    }
    return somma;
}

int main(int argc, char *argv[])
{
    int f1 = fork();
    
    // Figlio 1
    if(f1 == 0){
        printf("Sono il figlio PID = %d, mio padre ha PID = %d\n\n", getpid(), getppid());
        int lunghezza = calcolaLunghezzaVocali(argv, argc);
        printf("Lunghezza %d\n\n", lunghezza);
        exit(0);
    }else  if(f1 < 0){
        printf("Errore nella generazione del figlio");
    }
    
    else{
        wait(&f1);
        printf("Sono il padre PID = %d, mio figlio ha PID = %d\n\n", getpid(), f1);
        int f2 = fork();
        
        // Figlio 2
        
        if(f2 == 0){
            printf("Sono il figlio PID = %d, mio padre ha PID = %d\n\n", getpid(), getppid());
            int lunghezzaconsonanti = calcolaLunghezzaConsonanti(argv, argc);
            printf("Lunghezza %d\n\n", lunghezzaconsonanti);
            exit(0);
        }else if(f2 < 0){
            printf("Errore nella generazione del figlio");
            
        }else if(f2>0){
            wait(&f2);
            printf("Sono il padre PID = %d, mio figlio ha PID = %d\n\n", getpid(), f2);
        }
    }
    
    printf("Fine programma");

    return 0;
}