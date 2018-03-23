

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

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

/* Prototipos de funciones */

void InsertarNodoEnTabla(TablaHash *Tabla, int clave1, int clave2, NodoHash *nodo);

int ConsultarNodoEnTabla(TablaHash *Tabla, char *palabra);

void MostrarElementosEnTabla(TablaHash *Tabla);

int funcionHashTabla(char *palabra);

int funcionHashTablita(char *palabra);

TablaHash *CrearTabla();

void coincidePalabra(char *ruta, char *palabra, char *clave, TablaHash *Tabla);

/* Funcion main */
// Yeeeeeiiii
int main(){

	TablaHash *Tabla = CrearTabla();

	char *p1 = "/Estructuras/Hola que haces?";
	char *p2 = "Hola que haces?";
	char *p3 = "Hola";
	char *p4 = "que";
	char *p5 = "haces?";
	char *d1 = "/Estructuras/se es";
	char *d2 = "se es";
	char *d3 = "es";
	char *d4 = "se";
	int c1 = 0;
	int c2 = 0;

	NodoHash *nodo1;
	nodo1 = malloc(sizeof(NodoHash));
	nodo1->ruta = p1;
	nodo1->palabraArchivo = p2;
	nodo1->clave = p3;
	InsertarNodoEnTabla(Tabla, funcionHashTabla(nodo1->clave), funcionHashTablita(nodo1->clave), nodo1);

	NodoHash *nodo2;
	nodo2 = malloc(sizeof(NodoHash));
	nodo2->ruta = p1;
	nodo2->palabraArchivo = p2;
	nodo2->clave = p4;
	InsertarNodoEnTabla(Tabla, funcionHashTabla(nodo2->clave), funcionHashTablita(nodo2->clave), nodo2);

	NodoHash *nodo3;
	nodo3 = malloc(sizeof(NodoHash));
	nodo3->ruta = p1;
	nodo3->palabraArchivo = p2;
	nodo3->clave = p5;
	InsertarNodoEnTabla(Tabla, funcionHashTabla(nodo3->clave), funcionHashTablita(nodo3->clave), nodo3);

	NodoHash *nodo4;
	nodo4 = malloc(sizeof(NodoHash));
	nodo4->ruta = d1;
	nodo4->palabraArchivo = d2;
	nodo4->clave = d3;
	InsertarNodoEnTabla(Tabla, funcionHashTabla(nodo4->clave), funcionHashTablita(nodo4->clave), nodo4);

	NodoHash *nodo5;
	nodo5 = malloc(sizeof(NodoHash));
	nodo5->ruta = d1;
	nodo5->palabraArchivo = d2;
	nodo5->clave = d4;
	InsertarNodoEnTabla(Tabla, funcionHashTabla(nodo5->clave), funcionHashTablita(nodo5->clave), nodo5);

	MostrarElementosEnTabla(Tabla);

	/* pruebas de coincidencia */

	char *ruta1 = "Escritorio/jupy/no se que hacer.doc";
	char *palabra1 = "no se que hacer";
	char *coin1 = "que";
	char *coin11 = "que hacer";
	char *coin12 = "no";
	printf("\nCoincidencia1\n\n");
	coincidePalabra(ruta1, palabra1, coin1, Tabla);
	printf("\nCoincidencia2\n\n");
	coincidePalabra(ruta1, palabra1, coin11, Tabla);
	printf("\nCoincidencia3\n\n");
	coincidePalabra(ruta1, palabra1, coin12, Tabla);

	char *ruta2 = "Escritorio/Musica/Beeeiiiooo.mp3";
	char *palabra2 = "Beeeiiiooo.mp3";
	char *coin2 = "Beeeiiioo";
	char *coin21 = "mp3";

	printf("\nCoincidencia4\n\n");
	coincidePalabra(ruta2, palabra2, coin2, Tabla);
	printf("\nCoincidencia5\n\n");
	coincidePalabra(ruta2, palabra2, coin21, Tabla);

	char *ruta3 = "Escritorio/Musica/fire.mp3";
	char *palabra3 = "fire.mp4";
	char *coin3 = "fir";
	char *coin31 = "fire.mp3";

	printf("\nCoincidencia6\n\n");
	coincidePalabra(ruta3, palabra3, coin3, Tabla);
	printf("\nCoincidencia7\n\n");
	coincidePalabra(ruta3, palabra3, coin31, Tabla);

	MostrarElementosEnTabla(Tabla);
}

/* Funciones */

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