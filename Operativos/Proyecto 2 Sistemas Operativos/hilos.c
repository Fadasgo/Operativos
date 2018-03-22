#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct datos_{
   char*  ruta[8000];
   char*  palab[1000];
}datos;

pthread_mutex_t lock;

void* pasoDeDatos(void* dat);
//pthread_mutex_t lock;

int main(){
  // memset y strcpy
  // El shellscript me pasa el apuntador a la coincidencia
  // debo revisar en el txt de los hash el match con alguna de las palabras del hash
  // en caso de que no haga match meterla en la funcion de hash y guardarla al final del txt
  char* prueba = "./home/ruta/casa";
  char* pa = "casa";
  int h1;

  datos* para = malloc(sizeof(datos));
  strcpy(para->ruta,prueba);
  strcpy(para->palab,pa);

  pthread_t thread1;


  h1 = pthread_create(&thread1,NULL,pasoDeDatos,(void *)para);// Le pasamos la palabra que hay que buscar
  // en el indizador

  pthread_join(thread1, NULL);// 2do parametro es el return de la funcion
  printf(" \n FIN \n");
  return 0;
}
void* pasoDeDatos(void* dat){

  datos* dato = (datos *)dat;
  char* prueba;
  char* palab;

  prueba = dato->ruta;
  palab = dato->palab;
  //free(dato);

  // Realizamos lock (Mutex)
  pthread_mutex_lock(&lock);

  // Aqui va la funcion de Albert
  printf(prueba);
  printf("\n");
  printf(palab);

  pthread_mutex_unlock(&lock);
}
