/*Si scriva un programma in C che legge in input da argv[] una frase o una stringa o un carattere, quindi istanzi un processo figlio
il quale deve convertire il carattere in maiuscolo e terminare. Il padre attende la terminazione del processo figlio. */

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
    if(p == 0){
        int lenght;
        for(int j = 1; j < argc; j++){
            lenght = strlen(argv[j]);
            for(int i = 0; i < lenght; i++){
                printf("%c", toupper(argv[j][i]));
            }
            printf(" ");
        }
        
        exit(0);
    }
    else if(p > 0){
        wait(&p);
    }else{
        printf("\nProcesso figlio non generato con successo");
    }
    printf("\nFine programma");
}