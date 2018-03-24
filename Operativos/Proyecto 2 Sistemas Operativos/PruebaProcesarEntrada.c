

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

/* Prototipos de funciones */

int procesaEntrada(int argc, char **argv, char **dir, int *altura,
                char **indice, int *noupdate, int *noadd, char **palabraClave);

int comparaString(char *contenidoArgv, char *Acomparar);

int main(int argc, char **argv){

	/* Variables */
	int altura = 20;
  int noadd = 0;
  int noupdate = 0;
	char *indice = NULL;
	char *dir = NULL;
  char *palabraClave = NULL;

	int opcion = procesaEntrada(argc, argv, &dir, &altura, &indice,
                                &noupdate, &noadd, &palabraClave);

	if(opcion < 0)
    {
        printf("¡ERROR!\nLos parametros de entrada no son los correctos\nEl programa se cerrara.\n");
        return 0;
    }

    printf("Altura: %d\n", altura);
    printf("Direccion: %s\n", dir);
    printf("indice: %s\n", indice);
    printf("noupdate: %d\n", noupdate);
    printf("noadd: %d\n", noadd);
    printf("palabraClave: %s\n", palabraClave);

    printf("Todo correcto\n");
}

int procesaEntrada(int argc, char **argv, char **dir, int *altura,
                char **indice, int *noupdate, int *noadd,char **palabraClave){

	int opcion = 0;      // valor a retornar
    int i = 0;

    for(i = 0; i < argc; i++)
    {
        if(argv[i][0] == '-' && argv[i][1] != '-')
        {
            if(argv[i][1] == 'd')
            {
                if((i + 1) >= argc || argv[i+1][0] == '-')
                    opcion = -1;

                else
                    *dir = argv[i + 1];
            }

            else if(argv[i][1] == 'm')
            {
                if((i + 1) >= argc || argv[i+1][0] == '-')
                    opcion = -1;

                else
                    *altura = atoi(argv[i + 1]);
            }

            else if(argv[i][1] == 'i')
            {
                if((i + 1) >= argc || argv[i+1][0] == '-')
                    opcion = -1;

                else
                    *indice = argv[i + 1];
            }

            else if(argv[i][1] == 'b')
            {
                if((i + 1) >= argc || argv[i+1][0] == '-')
                    opcion = -1;

                else
                    *palabraClave = argv[i + 1];
            }

            else if(argv[i][1] == 'a')
            {
                *noadd = 1;
            }

            else if(argv[i][1] == 'u')
            {
                *noupdate = 1;
            }
        }

        else if(argv[i][0] == '-' && argv[i][1] == '-')
        {
            if(comparaString(argv[i], "dir"))
            {
                if((i + 1) >= argc || argv[i+1][0] == '-')
                    opcion = -1;

                else
                    *dir = argv[i + 1];
            }

            else if(comparaString(argv[i], "max"))
            {
                if((i + 1) >= argc || argv[i+1][0] == '-')
                    opcion = -1;

                else
                    *altura = atoi(argv[i + 1]);
            }

            else if(comparaString(argv[i], "index"))
            {
                if((i + 1) >= argc || argv[i+1][0] == '-')
                    opcion = -1;

                else
                    *indice = argv[i + 1];
            }

            else if(comparaString(argv[i], "noupdate"))
            {
                *noupdate = 1;
            }

            else if(comparaString(argv[i], "noadd"))
            {
                *noadd = 1;
            }
        }
    }

    return opcion;
}

int comparaString(char *contenidoArgv, char *Acomparar){

    int i = 0;
    int len = strlen(Acomparar);

    for(i = 0; i < len; i++)
    {
        if(*(contenidoArgv + (i+2)) != *(Acomparar + i))
            return 0;
    }

    return 1;
}
