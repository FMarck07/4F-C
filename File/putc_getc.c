#include <stdio.h>
#include <stdlib.h>

int main()
{
    char car; 
    
    car = getc(stdin);
    
    putc(car, stdout);
    
    FILE *fd;
    fd = fopen("output.txt", "w");
    
    if(fd != NULL){
        printf("Apertura del file fd avventa con successo");
        putc(car, fd);
        fclose(fd);
    }else{
        printf("Errore nell'apertura del file");
        exit(1);
    }
    return 0;
}