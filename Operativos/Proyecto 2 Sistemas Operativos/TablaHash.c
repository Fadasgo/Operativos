
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include "ensamble.h"

void InsertarNodoEnTabla(TablaHash *Tabla, int clave1, int clave2, NodoHash *nodo){

	if(Tabla->Tablitas[clave1]->lista[clave2]->head != NULL)
	{
		Tabla->Tablitas[clave1]->lista[clave2]->tail->siguiente = malloc(sizeof(nodo));
		Tabla->Tablitas[clave1]->lista[clave2]->tail->siguiente = nodo;
		Tabla->Tablitas[clave1]->lista[clave2]->tail = Tabla->Tablitas[clave1]->lista[clave2]->tail->siguiente;
		Tabla->Tablitas[clave1]->lista[clave2]->tail->siguiente = NULL;
	}

	else
	{
		Tabla->Tablitas[clave1]->lista[clave2]->head = malloc(sizeof(nodo));
		Tabla->Tablitas[clave1]->lista[clave2]->head = nodo;
		Tabla->Tablitas[clave1]->lista[clave2]->tail = nodo;
	}
}

int ConsultarNodoEnTabla(TablaHash *Tabla, char *palabra){

	int clave1 = funcionHashTabla(palabra);
	int clave2 = funcionHashTablita(palabra);
	NodoHash *temporal = Tabla->Tablitas[clave1]->lista[clave2]->head;

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
	int j = 0;

	for(i = 0; i < 100; i++)
	{
		for(j = 0; j < 100; j++)
		{
			NodoHash *nodoTemporal = Tabla->Tablitas[i]->lista[j]->head;

			while(nodoTemporal != NULL)
			{
				printf("Tabla: %d\nSlot: %d\n%s\n%s\n%s\n\n", i+1, j+1, nodoTemporal->ruta,
					                                     nodoTemporal->palabraArchivo,
					                                     nodoTemporal->clave);
				nodoTemporal = nodoTemporal->siguiente;
			}
		}
	}
}

TablaHash *CrearTabla(){

	TablaHash *Tabla;
	Tabla = malloc(sizeof(TablaHash));
	int i = 0;
	int j = 0;

	for(i = 0; i < 100; i++)
	{
		Tabla->Tablitas[i] = malloc(sizeof(TablaInternaHash));

		for(j = 0; j < 100; j++)
		{
			Tabla->Tablitas[i]->lista[j] = malloc(sizeof(Lista));
			Tabla->Tablitas[i]->lista[j]->head = NULL;
			Tabla->Tablitas[i]->lista[j]->tail = NULL;
		}
	}

	return Tabla;
}

int funcionHashTabla(char *palabra){

	int i = 0;
	int lenPalabra = strlen(palabra);
	int total = 0;

	for(i = 0; i < lenPalabra; i++)
	{
		total = *(palabra + i) + total;
	}

	return total%100;
}

int funcionHashTablita(char *palabra){

	return strlen(palabra)%100;

}

void coincidePalabra(char *ruta, char *palabra, char *clave, TablaHash *Tabla){
 //esto es un comentario
	int i = 0;
	int j = 0;
	int k = 0;
	int control = 0;
	int coincide = 0;
	int coincide2 = 0;
	int len = strlen(palabra);
	int lenClave = strlen(clave);

	if(len == lenClave)
	{
		for(i = 0; i < len; i++)
		{
			if(tolower(*(palabra + i)) != tolower(*(clave + i)))
			{
					control = 1;
					break;
			}
		}

		if(control == 0)
		{
			coincide2 = 1;
		}
	}

	k = 0;
	control = 0;

	for(i = 0; i < len; i++)
	{
		if((*(palabra + i) == ' ' || *(palabra + i) == '.' || i == len-1))
		{
			for(j = 0; j < lenClave; j++)
			{
				if(len == lenClave)
				{
					if(tolower(*(palabra + k)) != tolower(*(clave + j)))
					{
						control = 1;
						break;
					}
					k++;
				}
			}

			if(control == 0)
			{
				coincide = 1;
				break;
			}

			k = i+1;
			control = 0;
		}
	}

	if(coincide || coincide2)
	{
		k = 0;
		int c1 = 0;
		int c2 = 0;

		for(i = 0; i < len; i++)
		{
			if((*(palabra + i) == ' ' || *(palabra + i) == '.' || i == len-1))
			{
				char *tak = malloc(sizeof(char)*((i - k) + 1));

	    		int o = k;

	    		if(i == len-1)
					o--;

				for(j = 0; j < (i - o); j++)
				{
					sprintf(tak, "%s%c", tak, *(palabra + k));
					k++;
				}

				k = i+1;

				NodoHash *nodo = malloc(sizeof(NodoHash));
				nodo->ruta = ruta;
				nodo->palabraArchivo = palabra;
				nodo->clave = tak;
				InsertarNodoEnTabla(Tabla, funcionHashTabla(tak),
					                funcionHashTablita(tak), nodo);
			}
		}

		NodoHash *nodo1 = malloc(sizeof(NodoHash));
		nodo1->ruta = ruta;
		nodo1->palabraArchivo = palabra;
		nodo1->clave = palabra;
		InsertarNodoEnTabla(Tabla, funcionHashTabla(palabra),
					        funcionHashTablita(palabra), nodo1);
	}

	else
		return;
}
