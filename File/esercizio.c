#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_DIM 1024

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("Uso: %s <file_origine> <file_destinazione>\n", argv[0]);
        exit(1);
    }

    pid_t pid = fork();

    if(pid < 0){
        perror("Errore nella fork");
        exit(1);
    }
    else if(pid == 0){
        // FIGLIO: legge il file origine e restituisce il numero totale di byte letti (fino a 255)
        FILE *origine;
        unsigned char buffer[BUFFER_DIM];
        int n, totale = 0;

        origine = fopen(argv[1], "r");
        if(origine == NULL){
            perror("Errore apertura file origine");
            exit(2);
        }

        while(!feof(origine)){
            n = fread(buffer, 1, BUFFER_DIM, origine);
            totale += n;
        }

        fclose(origine);

        // Se il file è più grande di 255 byte, ritorniamo solo 255 (limite exit)
        if (totale > 255) {
            totale = 255;
        }

        exit(totale);
    }
    else {
        // PADRE: aspetta il figlio, prende il valore e lo scrive nel file destinazione
        int status;
        wait(&status);

        if(WIFEXITED(status)){
            int byte_letti = WEXITSTATUS(status);

            FILE *destinazione = fopen(argv[2], "w");
            if(destinazione == NULL){
                perror("Errore apertura file destinazione");
                exit(3);
            }

            fprintf(destinazione, "Il file origine ha %d byte letti dal figlio.\n", byte_letti);
            fclose(destinazione);

            printf("Padre: valore ricevuto dal figlio = %d\n", byte_letti);
        } else {
            printf("Il figlio non è terminato correttamente.\n");
        }
    }

    return 0;
}
