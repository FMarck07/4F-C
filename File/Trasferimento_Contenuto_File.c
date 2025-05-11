#include <stdio.h>
#include <stdlib.h>

/*Scrivere un programma che trasferisca il contenuto di un file origine in un file destinazione*/

#define BUFFER_DIM 1024

int main(int argc, char *argv[])
{
    // Dichiarazione delle variabili
    FILE *origine, *destinazione; 
    unsigned char buffer[BUFFER_DIM];
    int n;
    
    // Controllo che l'utente abbia inserimento il numero corretto di argomenti
    if(argc != 3){
        printf("Errore nell'inserimento del numero di argomenti");
        exit(1);
    }
    
    origine = fopen(argv[1] , "r");
    //Controllo che il file origine sia stato aperto correttamente
    if(origine == NULL){
        printf("Errore nell'apertura del file origine");
        exit(1);
    }
    
    destinazione = fopen(argv[2] , "w");
    
    //Controllo che il file destinazione sia stato aperto correttamente
    if(destinazione == NULL){
        printf("Errore nell'apertura del file destinazione");
        exit(1);
    }
    
    while(!feof(origine)){
        n = fread(buffer, 1, BUFFER_DIM, origine); 
        if(n > 0){
            fwrite(buffer, 1, n, destinazione);
        }
    }
    
    fclose(origine);
    fclose(destinazione);
    
    return 0;
}
