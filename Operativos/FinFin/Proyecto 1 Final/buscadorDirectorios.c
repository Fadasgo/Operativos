

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "buscadorDirectorios.h"

int main(int argc, char **argv){

	/* Variables */

    Pila st;
	int altura = 0;
	int verArchivos = 0;
    int control = 0;
    int control2 = 1;
    char* salida;
	char *dir = NULL;

    FILE* f = fopen("file.txt", "w");

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

	int opcion = procesaEntrada(argc, argv, &dir, &altura, &verArchivos);


	if(opcion == -1)
    {
        printf("¡ERROR!\nEl programa se cerrara.\n");
        return 0;
    }

    printf("Altura: %d\n", altura);

    inicializar_p(&st);

    listar_directorios(&st, dir, &verArchivos, altura, control2);

    while(!(vacia_p(&st))){

        int len = 0;
        char *nombre = tope(&st);
        char *feo = (char*)calloc(strlen(nombre)*60000, sizeof(char));
        strcpy(feo, tope(&st));
        pop(&st);
        int tamano = sizeof(feo);

        void* shmem = create_shared_memory(tamano);

        int pid = fork();

        if (pid == 0)
        {
            salida = eliminaSlash(feo);
            Palindromos(salida, shmem, control, f);
            exit(0);
        }

        else if (pid < 0)
        {
            perror("Hubo un problema al realizar el fork");
            exit(-1);
        }

        else 
        {
            wait(NULL);
            parentProces(shmem, control,f);
        }

        free(feo);
    }

    printf("\n");

    fclose(f);
    int lineas = countlines("file.txt");

    if (lineas == 0)
        printf("\n No existen \n");

    system("rm file.txt");
}
