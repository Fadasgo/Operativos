#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  long size;
  char *buf;
  char *ptr;

  // Buscamos la direccion del path donde estamos situados para despues poder buscar el archivo.txt creado mas adelante
  size = pathconf(".", _PC_PATH_MAX);
  if ((buf = (char *)malloc((size_t)size)) != NULL);
  ptr = getcwd(buf, (size_t)size); // poner condicional para saber si la ruta que vamos a usar es la de donde estamos parados o la dada por el flag

  //printf("%s\n",ptr ); // print para verificar el path

  char *comand = "find /home/fadasgo/Escritorio/Operativos -type d -print | tee archivo.txt";
  system(comand);
  return 0;
}
