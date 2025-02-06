#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    execlp("cp","cp", argv[1], argv[2], (char *)NULL);

    return 0;
}
