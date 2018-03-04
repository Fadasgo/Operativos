#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

void* create_shared_memory(size_t size);

char *Palindromos(char *palabra);

int cuentaSlashs(char *palabrita);

char* eliminaSlash(char *palabrita);

int main() {

  char* pr = "home/assa/CaSac";
  char* salida;
  char* salida2;


  void* shmem = create_shared_memory(512);

  memcpy(shmem, pr, strlen(pr));

  int pid = fork();

  if (pid == 0) {
    printf("Child read: %s\n", shmem);
    salida = eliminaSlash(shmem);
    //printf("SALIDA %s\n",salida );
    memcpy(shmem, salida, strlen(salida)+1);
    salida2 = Palindromos(shmem);
    memcpy(shmem, salida2, strlen(salida2)+1);
    printf("Child wrote: %s\n", shmem);
  }
  else if (pid < 0) {
    perror("Hubo un problema al realizar el fork");
    exit(-1);
  }
  else {
    printf("Parent read: %s\n", shmem);
    sleep(1);
    printf("After 1s, parent read: %s\n", shmem);
  }

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

char *Palindromos(char *palabra){

  int i = 0;
  int j = 0;
  int k = 0;
  int a = 0;
  int b = 0;
  int c = 0;
  int control = 0;
  int palindromo = 1;
  int intermedio = strlen(palabra);
  char *pal;
  char *final = malloc((sizeof(char)) * 1);

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

        largo = strlen(pal);
        largo2 = strlen(final);

        if(strlen(final) != 0)
        {
          final = realloc(final, sizeof(char) * (largo + largo2 +1));
          sprintf(final, "%s%c", final, ',');
          sprintf(final, "%s%c", final, ' ');
          sprintf(final, "%s%s", final, pal);
          sprintf(final, "%s%c", final, ' ');
        }

        else
        {
          final = (char*)realloc(final, (sizeof(char)) * (largo + largo2));
          sprintf(final, "%s", pal);
        }

        free(pal);

      }
    }
  }

  return final;
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
