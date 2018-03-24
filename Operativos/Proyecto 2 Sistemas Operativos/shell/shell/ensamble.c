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

/* Funcion main */
// Yeeeeeiiii
//int main(int argc, char **argv){
int main(){
/*
	// Procesado de Entrada
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
	}*/

	char* txt = "archIndx.txt"; // parametro por defecto a menos que se cambie por flag
  int h1;
	int h2;
	TablaHash *Tabla = CrearTabla();

	datos* dat = malloc(sizeof(datos));
	dat->tabla = Tabla;
	strcpy(dat->txtName,txt);

  pthread_t thread1;
	pthread_t thread2;

  h1 = pthread_create(&thread1,NULL,shell,(void *)txt); // 1er hilo para buscar los parametros
	h2 = pthread_create(&thread2,NULL,pasoDeDatos,(void *)dat); // 2do hilo para cargarlos en la tabla de hash

  pthread_join(thread1, NULL);// 2do parametro es el return de la funcion
	pthread_join(thread2, NULL);

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

void* pasoDeDatos(void* dat){

	datos* dato = (datos *)dat;
  char* nombreTxt;
  TablaHash *Tabla;

  nombreTxt = dato->txtName;
  Tabla = dato->tabla;

  // Realizamos Mutex (lock)
  pthread_mutex_lock(&lock);
	printf("ENTRO EN LA FUNCION DE ALBERT \n");
	int lines = countlines(nombreTxt);

  //printf("LINES: %d\n",lines);
  //printf("Lineas \n");
  readd(lines,nombreTxt,Tabla);


	//coincidePalabra(prueba, palab, HashNumber, Tabla);

	//MostrarElementosEnTabla(Tabla);

  pthread_mutex_unlock(&lock);
	printf("SALIO DE LA FUNCION DE ALBERT \n");
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

void shell(void* txt){
  char* nombreTxt = (char*)txt;
  pthread_mutex_lock(&lock);
	printf("Entro en la funcion del Yisus\n");
  //printf("NOMBRE DEL TXT %s \n",nombreTxt );

  pthread_mutex_unlock(&lock);
	printf("Salio de la funcion del Yisus\n");
}

int countlines(char *filename){
    FILE *fp;
    int count = 0;  // contador de lineas
    char c;  // To store a character read from file

    // Open the file
    fp = fopen(filename, "r");

    // chequea si el archivo existe
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }

    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp)){
        if (c == '\n'){
            count = count + 1;
        }
    }
    // Close the file
    fclose(fp);
    //printf("The file %s has %d lines\n ", filename, count);

    return count;
};

int comparaString2(char *str1, char *str2){

  int i = 0;
  int len1 = strlen(str1) - 1;
  int len2 = strlen(str2);

  //printf("Dentro de la funcion comparar\n");
  //printf("strlen(str1): %d\nstr1: %s\nstrlen(str2): %d\nstr2: %s\n", strlen(str1), str1, strlen(str2), str2);

  if(len1 != len2)
  {
    return 0; //no son iguales
  }

	for(i = 0; i < len1; i++)
	{
    if(tolower(*(str1 + i)) != tolower(*(str2 + i)))
      return 0; // no son iguales
	}

  return 1; // son iguales
}

void readd(int numLines, char *filename, TablaHash *Tabla){
  int character, whitespace = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *token;
  int contador = 0;
  int numero = 0; // numero del producto
  //TablaHash* Tabla;
  char *ruta;
  char *palabraArchivo;
  char *clave;
  char* abrir = "()";
  char* Fin = "FinDelBloque";


  FILE *file = fopen ( filename, "r" );

  if (file == NULL){
		exit(EXIT_FAILURE);
  }

	while ((read = getline(&line, &len, file)) != -1) {
    token = strtok(line,"\t");
    /* iteramos sobre los otros token */
    while( token != NULL ) {

      if (contador == 0) {
        if (comparaString2(token,abrir)) {
          //printf("ENTROOOOO\n");
          contador = 0;
          numero = numero + 1;
          contador = contador + 1;
        }
      }
      else if (contador == 1 ) {
        clave = token;
        contador = contador + 1;
        //printf("CLAVE %s\n",clave);
      }
      else if (contador == 2) {
        palabraArchivo = token;
        contador = contador + 1;
        //printf("archivo %s\n",palabraArchivo);
      }
      else if(contador > 2){
        if(comparaString2(token,Fin) != 1) {
          ruta = token;
          //printf("RUTA %s\n",ruta);
          // llamamos a la funcion de hash de Albert para pasarle los parametros
          coincidePalabra(ruta, palabraArchivo, clave, Tabla);
        }

        else if(comparaString2(token,Fin)) {
          contador = 0;
        }
      }
      //printf("contador %d\n", contador );
      //printf( "token %s\n", token ); //--------> Imprime y muestra que esta leyendo bien
      token = strtok(NULL,"\t");
      //contador++;
    }
  }
	free(line);
	fclose(file);
	//exit(EXIT_SUCCESS);

}
