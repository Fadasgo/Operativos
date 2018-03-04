

/* Librerias */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "buscadorDirectorios.h"

void Palindromos(char *palabra, void *shmem, int control){

  int i = 0;
  int j = 0;
  int k = 0;
  int a = 0;
  int b = 0;
  int c = 0;
  //int control = 0;
  int palindromo = 1;
  int intermedio = strlen(palabra);
  char *pal;
  char *final = malloc((sizeof(char)) * 1);
  char *final2 = "";

  for(int m = 2; m < intermedio; m++)
  {
    for(j = m, i = 0; j <= intermedio; i++, j++)
    {
      b = i;
      c = j;

      for(a = 0; a <= m/2; a++)
      {
        if(tolower(*(palabra + b)) != tolower(*(palabra + c)))
        {
          palindromo = 0;
          break;
        }

        b++;
        c--;

        if(a == m/2)
        {
          palindromo = 1;
        }
      }

      if(palindromo == 1)
      {

        int largo = 0;
        int largo2 = 0;

        pal = malloc((sizeof(char)) * m);
        strncpy(pal, palabra + i, m + 1);

        //printf("Palcito: %s\n", pal);

        memcpy(shmem, pal, strlen(pal)+1);

        parentProces(shmem, control);

      }
    }
  }
}

int cuentaSlashs(char *palabrita) {
  int i = 0;
  int backSlash = 0;
  int len = strlen(palabrita);

  for(i = 0; i < len; i++)
  {
    if(*(palabrita + i) == '/')
      backSlash++;
  }

  return backSlash;

}

char* eliminaSlash(char *palabrita) {
  int i = 0;
  int backSlash = 0;
  char *resultado;
  int len = strlen(palabrita);

  for(i = 0; i < len; i++)
  {
    if(*(palabrita + i) == '/')
      backSlash++;
  }

  resultado = malloc(sizeof(char) * (len - backSlash));

  for(i = 0; i < len; i++)
  {
    if(*(palabrita + i) == '/')
      continue;

    sprintf(resultado, "%s%c", resultado, *(palabrita + i));
  }

  return resultado;

}