#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include "ensamble.h"

/* Funcion main */
int main(int argc, char **argv){

	// Procesado de Entrada
	/*int altura = 20;
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
	}*/

	char* txt = "archIndx.txt"; // parametro por defecto a menos que se cambie por flag
  int h1;
	int h2;
	TablaHash *Tabla = CrearTabla();

	consola* con = malloc(sizeof(consola));
	strcpy(con->argumento,argv[1]);
	//printf("ARGUMENTO  %s\n",con->argumento);
	strcpy(con->txtName,txt);
	//printf("TXT NAME %s\n",con-> txtName );

	datos* dat = malloc(sizeof(datos));
	dat->tabla = Tabla;
	strcpy(dat->txtName,txt);

  pthread_t thread1;
	pthread_t thread2;

  h1 = pthread_create(&thread1,NULL,shell,(void *)con); // 1er hilo para buscar los parametros
	h2 = pthread_create(&thread2,NULL,pasoDeDatos,(void *)dat); // 2do hilo para cargarlos en la tabla de hash

  pthread_join(thread1, NULL);// 2do parametro es el return de la funcion
	pthread_join(thread2, NULL);

}
