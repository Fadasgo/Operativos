

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

/* Estructuras */

/* Prototipos de funciones */

int procesaEntrada(int argc, char **argv, char **dir, int *altura, 
                   char **indice, int *noupdate, int *noadd);

int cuentaSlashs(char *palabrita);

char* eliminaSlash(char *palabrita);

int main(int argc, char **argv){

	/* Variables */
	int altura = 20;
    int noadd = 0;
    int noupdate = 0;
	char *indice = NULL;
	char *dir = NULL;
	int opcion = procesaEntrada(argc, argv, &dir, &altura, &indice, 
                                &noupdate, &noadd);

	if(opcion < 0)                                                
    {                                                
        printf("¡ERROR!\nEl programa se cerrara.\n");
        return 0;
    }

    printf("Altura: %d\n", altura);
    printf("Direccion: %s\n", dir);
    printf("indice: %s\n", indice);
    printf("noupdate: %d\n", noupdate);
    printf("noadd: %d\n", noadd);

    printf("Todo correcto\n");
}

int procesaEntrada(int argc, char **argv, char **dir, int *altura, 
                   char **indice, int *noupdate, int *noadd){

	int opcion = 0;    // valor a retornar
	int flagD = 0;     // comprobamos si en la entrada esta presente -d
	int flagM = 0;     // comprobamos si en la entrada esta presente -m
	int c = 0;         // para guardar los valores que encuentra getotp
	int contador = 0;  // contador para el ciclo for
	int contador2 = 0; // contador para los condicionales
	int opterr = 0;    // necesario para getopt     

	while ((c = getopt(argc, argv, "uad:m:i:")) != -1) 
    { 
        switch(c)                                        
        {                                       
            case 'i':

                //Aqui hay algo mas, pero de momento lo dejare asi
                *indice = optarg;                                   
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
                
                break;

            case 'a':

                *noupdate = 1;
                break;

            case 'u':

                *noadd = 1;
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
