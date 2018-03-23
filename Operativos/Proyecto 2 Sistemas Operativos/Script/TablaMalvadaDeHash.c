

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
   char*  ruta[8000];
   char*  palab[1000];
   int hashNum;
	 TablaHash *tabla;
}datos;

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

TablaHash *CrearTabla();

void coincidePalabra(char *ruta, char *palabra, char *clave, TablaHash *Tabla);

/* Funcion main */
// Yeeeeeiiii
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
	char* prueba = "./home/ruta/casa";
  char* pa = "casa";
  int h1;

  datos* para = malloc(sizeof(datos));
  para->hashNum = 0;
  strcpy(para->ruta,prueba);
  strcpy(para->palab,pa);
	para->tabla = Tabla;

  pthread_t thread1;


  h1 = pthread_create(&thread1,NULL,pasoDeDatos,(void *)para);// Le pasamos la palabra que hay que buscar
  // en el indizador

  pthread_join(thread1, NULL);// 2do parametro es el return de la funcion
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

void* pasoDeDatos(void* dat){

  datos* dato = (datos *)dat;
  char* prueba;
  char* palab;
  int HashNumber;
	TablaHash* Tabla;


  prueba = dato->ruta;
  palab = dato->palab;
  HashNumber = dato->hashNum;
	Tabla = dato->tabla;
  //free(dato);

  // Realizamos Mutex (lock)
  pthread_mutex_lock(&lock);

  // Aqui va la funcion de Albert
  printf(prueba);
  printf("\n");
  printf(palab);
  printf("\n");
  printf("HashNumber %d",HashNumber);

	NodoHash *nodo1;
	nodo1 = malloc(sizeof(NodoHash));
	nodo1->ruta = prueba;
	nodo1->palabraArchivo = palab;
	nodo1->clave = HashNumber;

	InsertarNodoEnTabla(Tabla, funcionHashTabla(nodo1->clave), funcionHashTablita(nodo1->clave), nodo1);

	MostrarElementosEnTabla(Tabla);

	/* pruebas de coincidencia */

	/*char *ruta1 = "Escritorio/jupy/no se que hacer.doc";
	char *palabra1 = "no se que hacer";*/
	char *coin1 = "que";
	char *coin11 = "que hacer";
	char *coin12 = "no";

	printf("\nCoincidencia1\n\n");
	coincidePalabra(prueba, palab, coin1, Tabla);
	printf("\nCoincidencia2\n\n");
	coincidePalabra(prueba, palab, coin11, Tabla);
	printf("\nCoincidencia3\n\n");
	coincidePalabra(prueba, palab, coin12, Tabla);

	MostrarElementosEnTabla(Tabla);

  pthread_mutex_unlock(&lock);
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
