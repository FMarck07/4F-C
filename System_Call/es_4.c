#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Errore: numero insufficiente di argomenti.\n");
        exit(1);
    }

    char carattere = argv[argc - 2][0];
    char *outputFile = argv[argc - 1];
    int count = 0;


    int fd_output = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_output == -1)
    {
        printf("Errore apertura file di output");
        exit(1);
    }
    
    write(fd_output, "Il carattere %c compare nelle seguenti occorrenze: \n", carattere);

    for (int i = 1; i < argc - 2; i++)  
    {
        int fd = open(argv[i], O_RDONLY);  
        if (fd == -1)
        {
            printf("Errore apertura file");
            exit(1);
        }

        char buff;
        int nRead;
        int fileCount = 0;

        while ((nRead = read(fd, &buff, sizeof(buff))) > 0)
        {
            if (buff == carattere)
            {
                fileCount++;
                count++;
            }
        }

        if (fileCount > 0)
        {
            write(fd_output, "%s: %d occorrenze\n", argv[i], fileCount);
            printf("%s: %d occorrenze\n", argv[i], fileCount);
        }        
        close(fd);
    }

    write(fd_output, "\nIl carattere %c compare %d volte nei file.\n", carattere, count);
    printf("\nIl carattere %c compare %d volte nei file.\n", carattere, count);

    close(fd_output);

    return 0;
}
