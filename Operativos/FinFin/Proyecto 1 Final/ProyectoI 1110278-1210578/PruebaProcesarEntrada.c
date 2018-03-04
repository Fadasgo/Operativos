

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

/* Estructuras */

/* Prototipos de funciones */

int procesaEntrada(int argc, char **argv, char **dir, int *altura, int *verArchivos);

int main(int argc, char **argv){

	/* Variables */
	int altura = 0;
	int verArchivos = 0;
	char *dir = NULL;
	int opcion = procesaEntrada(argc, argv, &dir, &altura, &verArchivos);

	if(opcion < 0)                                                
    {                                                
        printf("¡ERROR!\nEl programa se cerrara.\n");
        return 0;
    }

    printf("Altura: %d\n", altura);
    printf("Direccion: %s\n", dir);
    printf("Ver Archivos: %d\n", verArchivos);

    printf("Todo correccto\n");
}

int procesaEntrada(int argc, char **argv, char **dir, int *altura, int *verArchivos){

	int opcion = 0;    // valor a retornar
	int flagD = 0;     // comprobamos si en la entrada esta presente -d
	int flagM = 0;     // comprobamos si en la entrada esta presente -m
	int c = 0;         // para guardar los valores que encuentra getotp
	int contador = 0;  // contador para el ciclo for
	int contador2 = 0; // contador para los condicionales
	int opterr = 0;    // necesario para getopt     

	while ((c = getopt(argc, argv, "fd:m:")) != -1) 
    { 
        switch(c)                                        
        {                                       
            case 'f':

                *verArchivos = 1;                                   

                break;

            case 'd':
                 
                flagD = 1;
                *dir = optarg;

                break;

            case 'm':

            	sscanf(optarg, "%d", &opcion);

                flagM = 1;

                if(opcion <= 0)                                 
                	opcion = -1;

                *altura = atoi(optarg);

                /*if(isdigit(optarg))
                	*altura = atoi(optarg);

                else
                	*altura = 0;*/
                
                break;

            case '?':                                     

                if(optopt == 'd') 
                    printf ("Debe especificar el directorio\n"
                    	    "Si no lo especifica se toma el actual.\n");

                if(optopt == 'm')
                    printf("Debe especificar la altura maxima de busqueda en el arbol\n"
                    	   "Si no la especifica se asume que es cualquiera.\n"); 

                break;
        }
    }

    for(contador = optind; contador < argc; contador++, contador2++); 
   
    if(flagD == 0)
        *dir = ".";

    if(contador2 > 1)
    {
        printf( "¡ERROR!\n" );
        printf( "Los argumentos de entrada son incorrectos\n" );
        opcion = -1;
    }

    return opcion;
}