

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "buscadorDirectorios.h"

void parentProces(void * shmem, int control, FILE* f){

    char c = '1';

    if(control == 0 && strlen(shmem) != 0)
    {
        printf("%s ", shmem);
        fprintf(f, "A character: %c\n", c);
    }
}

void* create_shared_memory(size_t size){

    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_ANONYMOUS | MAP_SHARED;

    return mmap(NULL, size, protection, visibility, 0, 0);
}

int countlines(char *filename){

    FILE *fp;
    int count = 0;
    char c;

    // Abrimos el archivo
    fp = fopen(filename, "r");

    // chequea si el archivo existe
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }

    // extraemos los caracteres y los guardamos en la variable c
    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n')
            count = count + 1;
    }
    // cerramos el archivo
    fclose(fp);

    return count;
}