/*Scrivere un programma in linguaggio C che usa il comando 
della shell rm per eliminare tutti files presenti
nell'intervallo [argv[1], argv[argc-1]]

esempio:
$ ./a.out /tmp/1.txt /tmp/3.txt /tmp/2.txt*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    for(int i = 1; i<argc; i++){
        int f = fork();
        if(f == 0){
            execlp("rm", "rm", argv[i], (char *)NULL);
        }
    }
    
    return 0;
}

