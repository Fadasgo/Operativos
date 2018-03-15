

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/* Estructuras */

typedef struct NodoHash{

	char *ruta;
	struct NodoHash *siguiente;

}NodoHash;

typedef struct Lista{

	NodoHash *head;
	NodoHash *tail;

}Lista;

typedef struct TablaHash{

	Lista *lista[15];
	int ElementosEnTabla;
	
}TablaHash;

/* Prototipos de funciones */

void InsertarNodoEnTabla(TablaHash *Tabla, int clave, NodoHash *nodo);

int ConsultarNodoEnTabla(TablaHash *Tabla, char *palabra);

void MostrarElementosEnTabla(TablaHash *Tabla);

int funcionHash(char *palabra);

TablaHash *CrearTabla();

/* Funcion main */
// Yeeeeeiiii
int main(){

	TablaHash *Tabla = CrearTabla();

	NodoHash *nodo1;
	nodo1 = malloc(sizeof(NodoHash));
	nodo1->ruta = "hola";
	InsertarNodoEnTabla(Tabla, 4, nodo1);
	//MostrarElementosEnTabla(Tabla);
	printf("\n");

	NodoHash *nodo2;
	nodo2 = malloc(sizeof(NodoHash));
	nodo2->ruta = "bien";
	InsertarNodoEnTabla(Tabla, 4, nodo2);
	//MostrarElementosEnTabla(Tabla);

	NodoHash *nodo3;
	nodo3 = malloc(sizeof(NodoHash));
	nodo3->ruta = "cuchi";
	InsertarNodoEnTabla(Tabla, 2, nodo3);
	//MostrarElementosEnTabla(Tabla);

	NodoHash *nodo4;
	nodo4 = malloc(sizeof(NodoHash));
	nodo4->ruta = "hambre";
	InsertarNodoEnTabla(Tabla, 2, nodo4);
	//MostrarElementosEnTabla(Tabla);

	NodoHash *nodo5;
	nodo5 = malloc(sizeof(NodoHash));
	nodo5->ruta = "no se";
	InsertarNodoEnTabla(Tabla, 2, nodo5);
	//MostrarElementosEnTabla(Tabla);

	NodoHash *nodo6;
	nodo6 = malloc(sizeof(NodoHash));
	nodo6->ruta = "bienvenido";
	InsertarNodoEnTabla(Tabla, 1, nodo6);
	//MostrarElementosEnTabla(Tabla);

	NodoHash *nodo7;
	nodo7 = malloc(sizeof(NodoHash));
	nodo7->ruta = "eso";
	InsertarNodoEnTabla(Tabla, 12, nodo7);

	MostrarElementosEnTabla(Tabla);

	if(ConsultarNodoEnTabla(Tabla, nodo7->ruta))
		printf(":D\n");

}

/* Funciones */

void InsertarNodoEnTabla(TablaHash *Tabla, int clave, NodoHash *nodo){

	if(Tabla->lista[clave]->head != NULL)
	{
		Tabla->lista[clave]->tail->siguiente = malloc(sizeof(nodo));
		Tabla->lista[clave]->tail->siguiente = nodo;
		Tabla->lista[clave]->tail = Tabla->lista[clave]->tail->siguiente;
		Tabla->lista[clave]->tail->siguiente = NULL;
		Tabla->ElementosEnTabla = Tabla->ElementosEnTabla + 1;
	}

	else
	{
		Tabla->lista[clave]->head = malloc(sizeof(nodo));
		//Tabla->lista[clave]->tail = malloc(sizeof(nodo));
		Tabla->lista[clave]->head = nodo;
		Tabla->lista[clave]->tail = nodo;
		Tabla->ElementosEnTabla = Tabla->ElementosEnTabla + 1;
	}
}

int ConsultarNodoEnTabla(TablaHash *Tabla, char *palabra){

	int clave = funcionHash(palabra);
	NodoHash *temporal = Tabla->lista[clave]->head;

	printf("aqui\n");

	while(temporal != NULL)
	{
		if(strcmp(temporal->ruta, palabra) == 0)
			return 1;

		temporal = temporal->siguiente;
	}

	return 0;
}

void MostrarElementosEnTabla(TablaHash *Tabla){

	int i = 0;

	for(i = 0; i < 15; i++)
	{
		NodoHash *nodoTemporal = Tabla->lista[i]->head;
	
		while(nodoTemporal != NULL)
		{
			printf("para la clave: %d\n%s\n", i, nodoTemporal->ruta);
			nodoTemporal = nodoTemporal->siguiente;
		}
	}
}

TablaHash *CrearTabla(){

	TablaHash *Tabla;
	Tabla = malloc(sizeof(TablaHash));
	Tabla->ElementosEnTabla = 0;
	int i = 0;

	for(i = 0; i < 15; i++)
	{
		Tabla->lista[i] = malloc(sizeof(Lista));
		Tabla->lista[i]->head = NULL;
		Tabla->lista[i]->tail = NULL;
	}

	return Tabla;
}

int funcionHash(char *palabra){

	int i = 0;
	int lenPalabra = strlen(palabra);
	int total = 0;

	for(i = 0; i < lenPalabra; i++)
	{
		total = *(palabra + i) + total;
	}

	return total%15;
}
