#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

void parentProces(void * shmem, int control);

void* create_shared_memory(size_t size);

void Palindromos(char *palabra, void *shmem, int control);

int cuentaSlashs(char *palabrita);

char* eliminaSlash(char *palabrita);

int main() {

  int control = 0;
  char* pr = "homeReconocerCaSacasaasahazaasa";
  char* salida;
  char* salida2;
  int tamano = sizeof(pr);


  void* shmem = create_shared_memory(tamano);

  //memcpy(shmem, pr, strlen(pr));

  int pid = fork();

  if (pid == 0) {
    printf("Child read: %s\n", pr);
    salida = eliminaSlash(pr);
    //printf("SALIDA %s\n",salida );
    //memcpy(shmem, salida, strlen(salida)+1);
    Palindromos(salida, shmem, control);
    //memcpy(shmem, salida2, strlen(salida2)+1);
    //printf("Child wrote: %s\n", salida2);
    //exit(0);
  }
  else if (pid < 0) {
    perror("Hubo un problema al realizar el fork");
    exit(-1);
  }
  else {
    //wait(NULL);
    parentProces(shmem, control);
    //sleep(1);
    //printf("After 1s, parent read: %s\n", shmem);
  }

  printf("\n");

  return 0;
}

void* create_shared_memory(size_t size) {
  // Our memory buffer will be readable and writable:
  int protection = PROT_READ | PROT_WRITE;

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it:
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  return mmap(NULL, size, protection, visibility, 0, 0);
}

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

        //printf("El mem: %s\n\n", shmem);

        //free(pal);

        /*printf("para ver quecarrizo consigue: %s\n", pal);

        largo = strlen(pal);
        largo2 = strlen(final2);

        printf("largo de final2: %d\n", largo2);

        if(largo2 != 0)
        {
          //final = realloc(final, sizeof(char) * (largo + largo2 +1));
          printf("final2 antes del cambio: %s\n", final2);

          final2 = malloc((sizeof(char))*(largo + largo2 + 1));

          strcpy(final2, final);

          printf("final le pasa a final2: %s\n", final);
          printf("final2 copiando lo que tiene final: %s\n", final2);

          final = malloc((sizeof(char))*(largo + largo2 + 1));


          printf("final2 no  wi: %s\n", final2);

          printf("pal: %s\n", pal);

          sprintf(final2, "%s%c", final2, ',');
          sprintf(final2, "%s%c", final2, ' ');
          sprintf(final2, "%s%s", final2, pal);
          sprintf(final2, "%s%c", final2, ' ');

          strcpy(final, final2);

          printf("pal: %s\n", pal);
          printf("final2 en procesamiento: %s\n\n", final2);
        }

        else
        {
          //final = (char*)realloc(final, (sizeof(char)) * (largo + largo2));
          final = malloc((sizeof(char))*(largo + largo2 +1));
          final2 = malloc((sizeof(char))*(largo + largo2 +1));

          sprintf(final, "%s", pal);
          sprintf(final2, "%s", pal);
          printf("pal 1 aqui: %s\n", pal);
          printf("final2 con primer elemento: %s\n\n", final2);
        }

        free(pal);
        free(final);
        free(final2);*/

      }
    }
  }

  //free(final);
  //free(final2);
  //printf("final2: %s\n", final2);

  //return final2;
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

void parentProces(void * shmem, int control){

  if(control == 1 && strlen(shmem) != 0)
  {
    control = 1;
    printf("%s", shmem);
  }

  else if(control == 0 && strlen(shmem) != 0)
  {
    printf(", %s", shmem);
  }

}
