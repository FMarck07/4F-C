#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TITOLO_FILE "titolo.txt"
#define OPERA_FILE "opera.txt"
#define FINALE_FILE "finale.txt"

#define DIM_TESTO 1000

int main() {
    char stringa_titolo[] = "Il mistero della montagna";
    char testo_opera[DIM_TESTO];
    pid_t pid1, pid2;

    // Primo processo figlio
    pid1 = fork();

    if (pid1 < 0) {
        perror("Errore nella generazione del primo processo figlio");
        exit(1);
    }

    if (pid1 == 0) {
        FILE *ftitolo = fopen(TITOLO_FILE, "w");
        if (ftitolo == NULL) {
            perror("Errore nell'apertura del file titolo.txt");
            exit(1);
        }
        fprintf(ftitolo, "%s", stringa_titolo);
        fclose(ftitolo);
        exit(0);
    }

    // Aspetta che il primo figlio finisca prima di avviare il secondo
    waitpid(pid1, NULL, 0);

    // Secondo processo figlio
    pid2 = fork();

    if (pid2 < 0) {
        perror("Errore nella generazione del secondo processo figlio");
        exit(1);
    }

    if (pid2 == 0) {
        FILE *fopera = fopen(OPERA_FILE, "w");
        if (fopera == NULL) {
            perror("Errore nell'apertura del file opera.txt");
            exit(1);
        }

        printf("Inserisci il testo dell'opera: ");
        fgets(testo_opera, DIM_TESTO, stdin);

        fprintf(fopera, "\n%s", testo_opera);
        fclose(fopera);
        exit(0);
    }

    // Processo padre: attende il secondo figlio
    waitpid(pid2, NULL, 0);

    // Apertura dei file per la copia finale
    FILE *ftitolo = fopen(TITOLO_FILE, "r");
    if (ftitolo == NULL) {
        perror("Errore nell'apertura del file titolo.txt");
        exit(1);
    }

    FILE *fopera = fopen(OPERA_FILE, "r");
    if (fopera == NULL) {
        perror("Errore nell'apertura del file opera.txt");
        fclose(ftitolo);
        exit(1);
    }

    FILE *ffinale = fopen(FINALE_FILE, "w");  // Sovrascrivi anziché fare append
    if (ffinale == NULL) {
        perror("Errore nell'apertura del file finale.txt");
        fclose(ftitolo);
        fclose(fopera);
        exit(1);
    }

    int ch;
    while ((ch = fgetc(ftitolo)) != EOF) {
        fputc(ch, ffinale);
    }

    printf("\nCopia completata da '%s' a '%s'.\n", TITOLO_FILE, FINALE_FILE);

    while ((ch = fgetc(fopera)) != EOF) {
        fputc(ch, ffinale);
    }

    printf("Copia completata da '%s' a '%s'.\n", OPERA_FILE, FINALE_FILE);

    fclose(ftitolo);
    fclose(fopera);
    fclose(ffinale);

    return 0;
}
