#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Creazione del primo figlio (F1)
    int p = fork();
    if (p > 0)
    {
        // Sono nel processo padre (P)
        printf("Io sono il padre P, PID = %d\n", getpid());
        printf("Mio figlio F1 ha PID = %d\n", p);

        // Creazione del secondo figlio (F2)
        int p2 = fork();
        if (p2 > 0)
        {
            printf("Io sono il padre P, PID = %d\n", getpid());
            printf("Mio figlio F2 ha PID = %d\n", p2);
        }
        else if (p2 == 0)
        {
            // Sono il figlio F2
            printf("Io sono F2, PID = %d\n", getpid());
            printf("Mio padre P ha PID = %d\n", getppid());

            // Creazione del figlio F4
            int p4 = fork();
            if (p4 == 0)
            {
                printf("Io sono F4, figlio di F2, PID = %d\n", getpid());
                printf("Mio padre F2 ha PID = %d\n", getppid());
            }
            else if (p4 > 0)
            {
                // Creazione del figlio F5
                int p5 = fork();
                if (p5 == 0)
                {
                    printf("Io sono F5, figlio di F2, PID = %d\n", getpid());
                    printf("Mio padre F2 ha PID = %d\n", getppid());
                }
            }
        }
    }
    else if (p == 0)
    {
        // Sono il figlio F1
        printf("Io sono F1, PID = %d\n", getpid());
        printf("Mio padre P ha PID = %d\n", getppid());

        // Creazione del figlio F3
        int p3 = fork();
        if (p3 == 0)
        {
            printf("Io sono F3, figlio di F1, PID = %d\n", getpid());
            printf("Mio padre F1 ha PID = %d\n", getppid());
        }
    }

    return 0;
}
