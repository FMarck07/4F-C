#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    execlp("cat","cat", "costituzione.txt", (char *)NULL);

    return 0;
}
