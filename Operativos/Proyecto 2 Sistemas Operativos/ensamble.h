#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

/* Estructuras */

typedef struct NodoHash{

	char *ruta;
	char *palabraArchivo;
	char *clave;
	struct NodoHash *siguiente;

}NodoHash;

typedef struct Lista{

	NodoHash *head;
	NodoHash *tail;

}Lista;

typedef struct TablaInternaHash{

	Lista *lista[100];

}TablaInternaHash;

typedef struct TablaHash
{
	TablaInternaHash *Tablitas[100];

}TablaHash;

typedef struct datos_{

	char* txtName[25];
	TablaHash* tabla;

}datos;

typedef struct shellConsola_{

	char* txtName[25];
	char* argumento[50];

}consola;

pthread_mutex_t lock;

/* Prototipos de funciones */

int procesaEntrada(int argc, char **argv, char **dir, int *altura,
                char **indice, int *noupdate, int *noadd, char **palabraClave);

int comparaString(char *contenidoArgv, char *Acomparar);

void* pasoDeDatos(void* dat);

void InsertarNodoEnTabla(TablaHash *Tabla, int clave1, int clave2, NodoHash *nodo);

int ConsultarNodoEnTabla(TablaHash *Tabla, char *palabra);

void MostrarElementosEnTabla(TablaHash *Tabla);

int funcionHashTabla(char *palabra);

int funcionHashTablita(char *palabra);

void shell(void* txt);

int countlines(char *filename);

void readd(int numLines, char *filename, TablaHash *Tabla);

int comparaString2(char *str1, char *str2);

TablaHash *CrearTabla();

void coincidePalabra(char *ruta, char *palabra, char *clave, TablaHash *Tabla);