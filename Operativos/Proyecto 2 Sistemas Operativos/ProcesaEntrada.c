
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include "ensamble.h"

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