#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct datos_{
   char*  ruta[8000];
   char*  palab[1000];
   int hashNum;
}datos;

pthread_mutex_t lock;

void* pasoDeDatos(void* dat);
//pthread_mutex_t lock;

int main(){
  // memset y strcpy
  // El shellscript me pasa la ruta y palabra
  char* prueba = "./home/ruta/casa";
  char* pa = "casa";
  int h1;

  datos* para = malloc(sizeof(datos));
  para->hashNum = 5555;
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
  int HashNumber;

  prueba = dato->ruta;
  palab = dato->palab;
  HashNumber = dato->hashNum;
  //free(dato);

  // Realizamos Mutex (lock)
  pthread_mutex_lock(&lock);

  // Aqui va la funcion de Albert
  printf(prueba);
  printf("\n");
  printf(palab);
  printf("\n");
  printf("HashNumber %d",HashNumber);

  pthread_mutex_unlock(&lock);
}
