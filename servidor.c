/***************************************************************
*Fecha: 14/10/2025
*Autor: Xamuel Perez
*Materia: Sistemas operativos
*Tema: Funcion fork pipe named
*  Implementacion del servidor para que reciba cadenas de texto
*  desde un cliente a traves de una FIFO, las invierta y las
*  envie de vuelta al cliente. El servidor termina cuando recibe
*  la cadena "end".
***************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//revisar en ejecucion la creacion y terminacion del fichero
#define FIFO_FILE "/tmp/CLASE_MARTES" //Definicion del nombre del fichero FIFO
void reverse_string(char *str); //Prototipo de la funcion para invertir cadenas
int main() {
   int fd;//descriptor del fichero FIFO
   char readbuf[80];//buffer para leer las cadenas
   char end[10];//cadena para comparar el fin del proceso
   int to_end;//variable para comparar cadenas
   int read_bytes;//numero de bytes leidos
   
   /* Create the FIFO if it does not exist */
   mkfifo(FIFO_FILE, S_IFIFO|0640);
   strcpy(end, "end");//cadena para comparar el fin del proceso
   fd = open(FIFO_FILE, O_RDWR);//abrir el fichero FIFO en modo lectura y escritura
   while(1) {
      read_bytes = read(fd, readbuf, sizeof(readbuf));//leer la cadena enviada por el cliente
      readbuf[read_bytes] = '\0';//agregar el caracter nulo al final de la cadena
      //imprimir la cadena recibida y su longitud
      printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      to_end = strcmp(readbuf, end);//comparar la cadena recibida con la cadena de fin
      
      if (to_end == 0) {//si la cadena es "end", cerrar el fichero y terminar el proceso
         close(fd);//cerrar el fichero FIFO
         break;
      }
      reverse_string(readbuf);//invertir la cadena recibida
      //imprimir la cadena invertida y su longitud
      printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int) strlen(readbuf));
      write(fd, readbuf, strlen(readbuf));//enviar la cadena invertida al cliente
      /*
      sleep - This is to make sure other process reads this, otherwise this
      process would retrieve the message
      */
      sleep(2);
   }
   return 0;
}

void reverse_string(char *str) {//funcion para invertir cadenas
   int last, limit, first;//variables para invertir la cadena
   char temp;//variable temporal para intercambiar caracteres
   last = strlen(str) - 1;//indice del ultimo caracter
   limit = last/2;//limite para invertir la cadena
   first = 0;//indice del primer caracter
   
   while (first < last) {//invertir la cadena
      temp = str[first];//intercambiar caracteres
      str[first] = str[last];//intercambiar caracteres
      str[last] = temp;//intercambiar caracteres
      first++;//incrementar el indice del primer caracter
      last--;//decrementar el indice del ultimo caracter
   }
   return;
}
