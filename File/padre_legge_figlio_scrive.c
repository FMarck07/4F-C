#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>  // Per strlen()

#define NOME_FILE "dato.txt"

int main() {
    char buffer[1024];        // Buffer per leggere il file
    size_t n;                 // Numero di byte letti
    char *stringa = "Contenuto importante";
    int pid, status;

    pid = fork();

    if (pid == 0) {
        // Processo figlio: scrive nel file
        FILE *file = fopen(NOME_FILE, "w");
        if (file == NULL) {
            perror("Errore nell'apertura del file");
            exit(1);
        }

        // Scrittura senza fprintf()
        fwrite(stringa, 1, strlen(stringa), file);

        fclose(file);
        exit(0);
    }

    // Processo padre: attende il figlio
    wait(&status);

    if (WIFEXITED(status)) {
        printf("Il file è stato creato dal figlio.\n");

        // Padre apre il file in lettura
        FILE *file = fopen(NOME_FILE, "r");
        if (file == NULL) {
            perror("Errore nell'apertura del file in lettura");
            exit(1);
        }

        // Legge e stampa il contenuto a video usando fread()
        while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, n, stdout); // stdout = schermo
        }

        fclose(file);
    } else {
        printf("Il figlio non è terminato correttamente.\n");
    }

    return 0;
}
