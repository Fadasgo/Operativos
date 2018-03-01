#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

char *Palindromos(char *palabra);

int cuentaSlashs(char *palabrita);

char* eliminaSlash(char *palabrita);

int main() {
  pid_t pid;
  int mypipefd[2];
  int ret;
  int estado;
  char buf[500];
  //char prueba[] = {"home/cCasacAma","home/assa","home/Camacasa"}
  char *pr = "home/assa";
  char *salida;

  ret = pipe(mypipefd);

  if (ret == -1) {
    perror("pipe");
    exit(1);
  }

  pid = fork();

  if (pid == 0) {
    // Proceso hijo
    //oli

    // Procesamos los palindromos
    salida = eliminaSlash(pr);
    salida = Palindromos(salida);
    printf("En el hijo: %s\n", salida);


    //escribimos los palindromos
    write(mypipefd[1],salida,strlen(salida)); // proceso hijo es el que escribe

    //free(salida);
  }

  else{
    // Proceso padre
    wait(&estado); // esperamos a que termine el proceso hijo
    // leemos las palabras palindromas que nos pasa el proceso hijo y las imprimimos
    read(mypipefd[0],buf ,strlen(salida)+1);
    printf("salida: %s\n", buf);
  }
  return 0;
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
          final = realloc(final, sizeof(char) * (largo + largo2 + 1));
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
	free(resultado);
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
