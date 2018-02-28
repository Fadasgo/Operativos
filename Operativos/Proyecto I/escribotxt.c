#include <stdio.h>

int main(int argc, char **arg) {
  FILE *esc;
  char caracter;
  // llamamos a la funcion para crear y escribir el txt y le pasamos los parametro para escribir al final del texto
  esc = fopen("cosa.txt","a+t");
  printf("\n Introducir texto que lleva cosa.txt: ");

  while ((caracter = getchar()) != '\n') {

    printf("%c", fputc(caracter,esc) );

  }

  fclose(esc);
}
