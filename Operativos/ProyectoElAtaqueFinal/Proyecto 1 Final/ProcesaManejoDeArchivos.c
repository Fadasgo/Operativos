

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

int countlines(char *filename){
    FILE *fp;
    int count = 0; 
    char c;  

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }

    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n')
        {
            count = count + 1;
        }
    }

    fclose(fp);
    return count;
}

Paths* readd(int numLines, char *filename){

    Paths* arrayP = malloc(numLines * sizeof(Paths));
    Paths* InicioArray = arrayP;
    char* line = NULL;
    size_t len = 0;
    ssize_t readd;
    char *token;
    Paths ruta;

    FILE *file = fopen ( filename, "r" );

    if (file == NULL)
    {
		exit(EXIT_FAILURE);
    }

	while ((readd = getline(&line, &len, file)) != -1)
	{
	    char* dirs;
	    token = strtok(line,"\n");
	    strcpy(ruta.name,token);
	    *arrayP = ruta;
	    arrayP++;
    }

    free(line);
    fclose(file);
    return InicioArray;
}