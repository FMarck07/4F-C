#include <fcntl.h>    // open
#include <unistd.h>   // read, write, close
#include <stdlib.h>   // exit
#include <stdio.h>    // printf, perror

#define BUFFER_DIM 1024

int main(int argc, char *argv[])
{
    int origine, destinazione;
    unsigned char buffer[BUFFER_DIM];
    ssize_t n;

    // Controllo argomenti
    if (argc != 3) {
        printf("Errore: numero di argomenti non corretto\n");
        exit(1);
    }

    // Apertura file origine in sola lettura
    origine = open(argv[1], O_RDONLY);
    if (origine < 0) {
        perror("Errore nell'apertura del file origine");
        exit(1);
    }

    // Apertura file destinazione in scrittura, lo crea se non esiste, lo svuota se esiste
    destinazione = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destinazione < 0) {
        perror("Errore nell'apertura del file destinazione");
        close(origine);
        exit(1);
    }

    // Copia del contenuto
    while ((n = read(origine, buffer, BUFFER_DIM)) > 0) {
        if (write(destinazione, buffer, n) != n) {
            perror("Errore in scrittura");
            close(origine);
            close(destinazione);
            exit(1);
        }
    }

    if (n < 0) {
        perror("Errore in lettura");
    }

    // Chiusura file
    close(origine);
    close(destinazione);

    return 0;
}
