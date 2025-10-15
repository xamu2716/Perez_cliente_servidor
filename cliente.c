/**************************************************************
*Fecha: 14/10/2025
*Autor: Xamuel Perez
*Materia: Sistemas operativos
*Tema: Funcion fork pipe named
*  Implementacion del cliente para enviar cadenas de texto
*  al servidor a traves de una FIFO, recibir las cadenas
*  invertidas y mostrarlas en pantalla. El cliente termina
*  cuando envia la cadena "end".
*************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//revisar en ejecucion la creacion y terminacion del fichero
#define FIFO_FILE "/tmp/CLASE_MARTES"
int main() {
   int fd; //descriptor de fichero
   int end_process;//variable para terminar el proceso
   int stringlen;//longitud de la cadena
   int read_bytes;//numero de bytes leidos
   char readbuf[80];//buffer de lectura
   char end_str[5];//cadena para terminar el proceso
   printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");
   fd = open(FIFO_FILE, O_CREAT|O_RDWR);//abrir la FIFO en modo lectura y escritura
   strcpy(end_str, "end");//cadena para terminar el proceso
   
   while (1) {
      printf("Enter string: ");//pedir cadena al usuario
      fgets(readbuf, sizeof(readbuf), stdin);//leer cadena de la entrada estandar
      stringlen = strlen(readbuf);//calcular longitud de la cadena
      readbuf[stringlen - 1] = '\0';//eliminar el salto de linea
      end_process = strcmp(readbuf, end_str);//comparar la cadena con "end"
      
      //printf("end_process is %d\n", end_process);
      if (end_process != 0) {
         write(fd, readbuf, strlen(readbuf));//enviar la cadena al servidor
         //imprimir la cadena enviada y su longitud
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         read_bytes = read(fd, readbuf, sizeof(readbuf));//leer la cadena invertida del servidor
         readbuf[read_bytes] = '\0';//anadir el caracter nulo al final de la cadena
         //imprimir la cadena recibida y su longitud
         printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      } else {
         write(fd, readbuf, strlen(readbuf));//enviar la cadena "end" al servidor
         //imprimir la cadena enviada y su longitud
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         close(fd);//cerrar el descriptor de fichero
         break;
      }
   }
   return 0;//fin del programa
}
