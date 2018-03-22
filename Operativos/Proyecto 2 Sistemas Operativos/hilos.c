#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct datos {
   char*  coinci[600];
   char*  palab[600];
}Datos;

void CoincidenciaEnPalabras(char *coincidencia, char *palabra);

int main(){
  // memset y strcpy
  // El shellscript me pasa el apuntador a la coincidencia
  // debo revisar en el txt de los hash el match con alguna de las palabras del hash
  // en caso de que no haga match meterla en la funcion de hash y guardarla al final del txt
  char *prueba = "veamosComo Es EsteBeta";
  char *coincidencia1 = "Veamos"; // podriamos hacer un memset cada vez y guardar la nueva info

  struct param *para = malloc(sizeof(Datos));
  para->coinci = prueba;
  para->palab = coincidencia1;

  pthread_t thread1, thread2;
  pthread_mutex_t *lock;
  int h1,h2;
  // (void *)
  //Iteramos sobre todas los hash del txt
  h1 = pthread_create(&thread1,NULL,CoincidenciaEnPalabras,para);// Le pasamos la palabra que hay que buscar
  // en el indizador

  pthread_join(thread1, NULL);// 2do parametro es el return de la funcion

  return 0;
}
// devuelve 0 si no hubo match, 1 en caso contrario
void CoincidenciaEnPalabras(Datos* dat){

  char *pruebaa;
  char *coinciden;

  struct dimension* dim = (struct datos*)datos;

  coinciden = dim->coinci;
  pruebaa = dim->palab;
  free(dim);

  int i = 0;
	int j = 0;
	int k = 0;
	int coincide = 0;
	int FlagPunto = 0;
	int FlagEspaciosPalabra = 0;
	int FlagEspaciosCoincidencia = 0;
	int lenPalabra = strlen(palabra);
	int lenConincidencia = strlen(coincidencia);

  // Realizamos lock (Mutex)

  pthread_mutex_lock(&lock);

	printf("lenPalabra: %d\n", lenPalabra);
	printf("lenConincidencia: %d\n", lenConincidencia);

	for(i = 0; i < lenPalabra; i++)
	{
		if(*(palabra + i) == ' ')
			FlagEspaciosPalabra = 1;

		if(*(palabra + i) == '.')
			FlagPunto = 1;
	}

	for(i = 0; i < lenConincidencia; i++)
	{
		if(*(coincidencia + k) == ' ')
			FlagEspaciosCoincidencia = 1;
	}

	for(i = 0; i < lenPalabra; i++)
	{
		if(tolower(*(palabra + i)) == tolower(*(coincidencia + k)))
		{
			//printf("carater de palabra: %c\nCaracter de coincidencia: %c\n",*(palabra + i) ,*(coincidencia + k));
			//printf("carater de palabra: %c\nCaracter de coincidencia: %c\n",*(palabra + i) ,*(coincidencia + k));
			coincide = 1;
			k = i;

			for(j = 0; j < lenConincidencia; j++, k++)
			{
				//printf("carater de palabra: %c\nCaracter de coincidencia: %c\n",*(palabra + k) ,*(coincidencia + j));
				//printf("j: %d\nk: %d\ni: %d\n",j ,k, i);
				if((tolower(*(palabra + k)) != tolower(*(coincidencia + j))) ||
				   (tolower(*(palabra + k)) == ' '))
				{
					coincide = 0;
					break;
				}
			}

			k = 0;
		}

		if(coincide == 1)
			break;

	}

	if(coincide == 1)
		printf("Si se pudo :D\n\n");

	else
		printf("fijate que no :(\n\n");
    // Hacer lo de la funcion de hash y agregarlo al txt
    // probablemente aqui tambien es buena idea hacer el unico lock (momento de escribir en el txt)

    pthread_mutex_unlock(&lock);
}
