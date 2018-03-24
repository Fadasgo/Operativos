
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include "ensamble.h"

void* pasoDeDatos(void* dat){

	datos* dato = (datos *)dat;
  char* nombreTxt;
  TablaHash *Tabla;

  nombreTxt = dato->txtName;
  Tabla = dato->tabla;

  // Realizamos Mutex (lock)
  pthread_mutex_lock(&lock);
	//printf("ENTRO EN LA FUNCION 2 \n");
	int lines = countlines(nombreTxt);

  //printf("LINES: %d\n",lines);
  //printf("Lineas \n");
  readd(lines,nombreTxt,Tabla);


	//coincidePalabra(prueba, palab, HashNumber, Tabla);

	//MostrarElementosEnTabla(Tabla);

  pthread_mutex_unlock(&lock);
	//printf("SALIO DE LA FUNCION 2 \n");
}

void shell(void* txt){
	consola* dato = (consola *)txt;
  char* nombreTxt;
  char* argumento;

  nombreTxt = dato->txtName;
  argumento = dato->argumento;
	//printf("DATOOOOO%s\n",dato->argumento );// o seaesta linea pasa?

  //char* nombreTxt = (char*)txt;
	//Funciona? O sea, lo que mando el Albe;l
  pthread_mutex_lock(&lock);
	//printf("Entro en la funcion del 1\n");
  //printf("NOMBRE DEL TXT %s \n",nombreTxt );
  //La variable si esta llegando hasta el print, pero no esta llegando al codigo de bash no se por que
	char src[50];
	char dest[50];
	strcpy(src, "bash buscarArch.sh ");
	strcpy(dest, dato->argumento);
	//printf("HOLAAAA %s\n",src );

	//printf("ARGUMENTO 2 \n", argumento);
	//strcpy(dest,palabraClave);
	strcat(src,dest);
	//printf("puestooooo : %s\n", src );
	puts("Will execute sh with the following script :");
	puts(src);
	puts("Starting now:");
	system(src);

  pthread_mutex_unlock(&lock);
	//printf("Salio de la funcion del 1\n");
}