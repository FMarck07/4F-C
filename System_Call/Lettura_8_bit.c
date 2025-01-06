#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      printf("Errore numero di argomenti\n");
      exit(1);
   }   

   int fd = open(argv[1], O_RDONLY);

   if(fd == -1)
   {
      printf("Errore\n");
      return -1;
   }

   char buff[8];
   int nRead; 

   while((nRead = read(fd, &buff, sizeof(buff)))>0)
   {
      write(1, buff, nRead);
   }
   close(fd);

}
