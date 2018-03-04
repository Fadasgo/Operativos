

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

/* Estructura */

typedef struct ruta{

    char name[2000]; // contiene la direccion de un directorio hoja

}Paths;

 // Prototipos de funciones

int countlines(char *filename);

Paths* readd(int numLines, char *filename);

int procesaEntrada(int argc, char **argv, char **dir, int *altura, int *verArchivos);

void parentProces(void * shmem, int control);

void* create_shared_memory(size_t size);

void Palindromos(char *palabra, void *shmem, int control);

int cuentaSlashs(char *palabrita);

char* eliminaSlash(char *palabrita);