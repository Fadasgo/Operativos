

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

/* Estructuras */

typedef struct Pila{

    int N;
    int max_size;
    char **S;

}Pila;

/* Prototipos de funciones */

void listar_directorios(Pila* st, char* name, int *verArchivos, int altura, int control2s);

void inicializar_p(Pila *st);

int elementos_p(Pila *st);

int vacia_p(Pila *st);

char* tope(Pila *st);

void pop(Pila *st);

void push(Pila *st, char *name);

void destruir_p(Pila *st);

int procesaEntrada(int argc, char **argv, char **dir, int *altura, int *verArchivos);

void parentProces(void * shmem, int control, FILE* f);

void* create_shared_memory(size_t size);

void Palindromos(char *palabra, void *shmem, int control, FILE* f);

int cuentaSlashs(char *palabrita);

char* eliminaSlash(char *palabrita);

int countlines(char *filename);