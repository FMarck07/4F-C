#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    pid_t f1, f2;
    FILE *file;
    char contenuto[1000];
    char nome_completo[100];

    // Processo padre crea input.txt
    printf("Inserisci un piccolo contenuto per input.txt: ");
    fgets(contenuto, sizeof(contenuto), stdin);
    
    file = fopen("input.txt", "w");
    if (file == NULL) {
        perror("Errore creazione input.txt");
        exit(1);
    }
    fprintf(file, "%s", contenuto);
    fclose(file);

    // Creazione processi figli
    f1 = fork();
    if (f1 < 0) {
        perror("Fork fallita");
        exit(1);
    }

    if (f1 == 0) {
        // Processo F1
        file = fopen("input.txt", "r");
        FILE *copia = fopen("copia.txt", "w");
        if (file == NULL || copia == NULL) {
            perror("Errore apertura file");
            exit(1);
        }
        fprintf(copia, "Copia ");
        char c;
        while ((c = fgetc(file)) != EOF) {
            fputc(c, copia);
        }
        fclose(file);
        fclose(copia);
        exit(0);
    } else {
        f2 = fork();
        if (f2 < 0) {
            perror("Fork fallita");
            exit(1);
        }

        if (f2 == 0) {
            // Processo F2
            printf("Inserisci il tuo cognome e nome: ");
            fgets(nome_completo, sizeof(nome_completo), stdin);
            
            file = fopen("copia.txt", "a");
            if (file == NULL) {
                perror("Errore apertura copia.txt");
                exit(1);
            }
            fprintf(file, "%s", nome_completo);
            fclose(file);
            
            // Visualizzazione contenuto copia.txt
            file = fopen("copia.txt", "r");
            if (file == NULL) {
                perror("Errore lettura copia.txt");
                exit(1);
            }
            printf("\nContenuto di copia.txt:\n");
            char c;
            while ((c = fgetc(file)) != EOF) {
                putchar(c);
            }
            fclose(file);
            exit(0);
        } else {
            // Processo padre aspetta i figli
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}






#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    pid_t f1, f2;
    FILE *file;
    char contenuto_opera[1000];

    // Creazione processi figli
    f1 = fork();
    if (f1 < 0) {
        perror("Fork fallita");
        exit(1);
    }

    if (f1 == 0) {
        // Processo F1
        file = fopen("titolo.txt", "w");
        if (file == NULL) {
            perror("Errore creazione titolo.txt");
            exit(1);
        }
        fprintf(file, "Il mistero della montagna");
        fclose(file);
        exit(0);
    } else {
        f2 = fork();
        if (f2 < 0) {
            perror("Fork fallita");
            exit(1);
        }

        if (f2 == 0) {
            // Processo F2
            printf("Inserisci il testo dell'opera: ");
            fgets(contenuto_opera, sizeof(contenuto_opera), stdin);
            
            file = fopen("opera.txt", "w");
            if (file == NULL) {
                perror("Errore creazione opera.txt");
                exit(1);
            }
            fprintf(file, "%s", contenuto_opera);
            fclose(file);
            exit(0);
        } else {
            // Processo padre aspetta i figli
            wait(NULL);
            wait(NULL);
            
            // Creazione file finale.txt
            FILE *titolo = fopen("titolo.txt", "r");
            FILE *opera = fopen("opera.txt", "r");
            file = fopen("finale.txt", "w");
            
            if (titolo == NULL || opera == NULL || file == NULL) {
                perror("Errore apertura file");
                exit(1);
            }
            
            char c;
            while ((c = fgetc(titolo)) != EOF) {
                fputc(c, file);
            }
            fputc('\n', file);
            while ((c = fgetc(opera)) != EOF) {
                fputc(c, file);
            }
            
            fclose(titolo);
            fclose(opera);
            fclose(file);
            
            printf("File finale.txt creato con successo!\n");
        }
    }

    return 0;
}
