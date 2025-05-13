/*Il padre crea un processo figlio.

Il figlio scrive "Ciao dal figlio!" in un file chiamato messaggio.txt.

Il padre attende la fine del figlio e poi stampa un messaggio 
di conferma: "Il file è stato creato dal figlio."*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TITOLO_FILE "messaggio.txt"
int main()
{
    int pid; 
    
    pid = fork();
    
    if(pid == 0){
        char *stringa = "Ciao dal figlio!";
        FILE *file = fopen(TITOLO_FILE, "w");
        if(file == NULL){
            printf("Errore nella creazione del file");
            exit(1);
        }
        fprintf(file, "%s", stringa);
        fclose(file);
        exit(0)
    }
    
    int status;
    wait(&status);
    if(WIFEXITED(status)){
        printf("Il file è stato creato dal figlio\n");
        //int byte = WIEXITSTATUS(status);
    }else{
        printf("Il figlio non è terminato correttamente.\n");
    }
    
    
    
    return 0;
}
