

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

/* Estructuras */

typedef struct Pila{

    int N;
    int max_size;
    char **S;

}Pila;

/* Prototipos de funciones */

void listar_directorios(Pila* st, char* name, int *verArchivos);

void inicializar_p(Pila *st);

int elementos_p(Pila *st);

int vacia_p(Pila *st);

char* tope(Pila *st);

void pop(Pila *st);

void push(Pila *st, char *name);

void destruir_p(Pila *st);

int procesaEntrada(int argc, char **argv, char **dir, int *altura, int *verArchivos);

int main(int argc, char **argv){

	/* Variables */

    Pila st;
	int altura = 0;
	int verArchivos = 0;
	char *dir = NULL;
	int opcion = procesaEntrada(argc, argv, &dir, &altura, &verArchivos);

	if(opcion == -1)                                                
    {                                                
        printf("¡ERROR!\nEl programa se cerrara.\n");
        return 0;
    }

    printf("Altura: %d\n", altura);
    printf("Direccion: %s\n", dir);
    printf("Ver Archivos: %d\n", verArchivos);
    printf("Todo correccto\n\n");

    inicializar_p(&st);

    listar_directorios(&st, dir, &verArchivos);

    printf("Numerillo de cosas en pila: %d\n", elementos_p(&st));

    while(!(vacia_p(&st))){

        int len = 0;
        char *nombre = tope(&st);
        printf("nombre del directorio: %s\n", nombre);
        pop(&st);
        //printf("nombre del directorio: %s\n", nombre);
        // FAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACK
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++Procesar la entrada+++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

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

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++Pila++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void inicializar_p(Pila *st){

    st->N = 0;                                                   
    st->max_size = 10;                                            
    st->S = (char **) malloc(st->max_size*sizeof(char *)); 

} // Fin de la funcion inicializar_p



/*
 * elementos_p: Tamaño de la pila.
 *    st: Estructura pila de directorios.
 *
 * Descripcion: Encuentra el tamaño entero de la pila.
 *
 * Retorna: Tamaño de la pila.
 */
int elementos_p(Pila *st){

    return st->N; 

} // Fin de la funcion elementos_p



/*
 * vacia_p: Verifica si hay espacio en la pila.
 *    st: Estructura pila de directorios.
 *
 * Descripcion: Verifica si la pila esta vacia o no.
 *
 * Retorna: 0 Si la pila no esta vacia.
 *          1 Si la pila esta vacia.
 */
int vacia_p( Pila *st ){

    return st->N == 0 ? 1 : 0;

} // Fin de la funcion vacia_p



 /*
  * tope: Verifica el primero en la pila.
  *    st: Estructura pila de directorios.
  *
  * Descripcion: Verifica el primero en la pila.
  *
  * Retorna: El primer elemento de la pila.
  */
char* tope(Pila *st){

    if( st->N == 0 )                       
    {        
        printf( "¡ERROR, PILA VACIA!\n" ); 
    }

    return st->S[( st->N )-1];             

} // Fin de la funcion tope



/*
 * pop: Remueve un elemento de la pila.
 *    st: Estructura pila de directorios.
 *
 * Description: Remueve el elemento en el tope de la pila.
 */
void pop(Pila *st){ 

    char *dir;

    if( st->N == 0 )                       
    {                     
        printf( "¡ERROR, PILA VACIA!\n" );
    }

    ( st->N )--;                           
    free( st->S[st->N] );
    
} // Fin de la funcion pop



/*
 * push: Añade un elemento a la pila.
 *    st:   Estructura pila de directorios.
 *    name: Caracter a añadir en la pila.
 *
 * Description: Añade un elemento en el tope de la pila.
 */

void push(Pila *st, char *name){

    int N = st->N;               // Numero de elementos en la pila
    int max_size = st->max_size; // Numero maximo de elementos que caben en la pila
    int l=strlen( name );        // Lo que se va a agregar a la pila
    int i;                       // Contador
    
    if( N == max_size )                                                    
    {                                                  
        st->max_size = 2 * max_size;                                       
        st->S = ( char ** ) realloc( st->S, 2*max_size*sizeof( char * ) ); 
    }

    st->S[N] = ( char * ) malloc( sizeof( char )*( l+1 ) );                

    for( i = 0; i < l+1; i++ )
        st->S[N][i] = name[i];                                             

    ( st->N )++;                                                           

} // Fin de la funcion push

 /*
  * destruir_p: Elimina la pila.
  *    st: Estructura pila de directorios.
  *
  * Description: Elimina completamente una pila.
  */
void destruir_p( Pila *st ){

    int N = st->N;           
    int i;                   
    st->N = 0;               
    st->max_size = 0;        
    
    for( i = 0; i < N; i++ ) 
        free( st->S[i] );    

    free( st->S );

} // Fin de la funcion destruir_p

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++Sin definir+++++++++++++++++++++++++++++++++++++++++*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void listar_directorios(Pila *st, char *name, int *verArchivos){

    int flagDirectorio = 0;
    int contador = 0;
    int contador2 = 0;
    DIR *dir;             // Se usa un apuntador a DIR para abrir los directorios
    struct dirent *entry; /* En *entry habrá información sobre el archivo 
                             que se está "sacando" a cada momento*/

    if(!(dir = opendir(name))){

        printf("Algo salio mal al abrir el archivo\n");
        return;
    }

    while((entry = readdir(dir)))
    {
        char *path;
        int l = strlen(name)+strlen(entry->d_name) + 3;
        //printf("l almacena el espacio que se debe guardar para nombre del archivo: %d\n", l);
        path = malloc(sizeof(char) * l);
        //guardamos en path la ruta del directorio
        sprintf(path, "%s/%s", name, entry->d_name);
        printf("direccion en path antes de los if's: %s\n\n", path);

        //aqui se pregunta si es un directorio
        if(entry->d_type == DT_DIR)                         
        {
            //contador++;
            flagDirectorio = 1;

            if(strcmp(entry->d_name, ".") == 0 ||        
               strcmp(entry->d_name, "..") == 0 )
            {       
                free(path);
                continue;
            }
            printf("direccion en path: %s\n", path);
            printf("Es un directorio\n\n");
            push(st, path);
            listar_directorios(st, path, verArchivos);
        }

        /*else
            flagDirectorio = 0;*/

        //aqui se pregunta si es un archivo
        else if((entry->d_type == DT_REG) && (*verArchivos == 1) && (flagDirectorio == 0))
        {

            printf("direccion en path: %s\n", path);
            printf("Es un archivo.\n\n");
            push(st, path);
        }

        free(path);                              
    }

    /*printf("verArchivos: %d\n"
           "flagDirectorio: %d\n" 
           "contador: %d\n", *verArchivos, flagDirectorio, contador);

    if(!(dir = opendir(name))){

        printf("Algo salio mal al abrir el archivo\n");
        return;
    }

    if((*verArchivos == 1) && (flagDirectorio == 0))
    {
        while((entry = readdir(dir)))
        {
            char *path;
            int l = strlen(name)+strlen(entry->d_name) + 3;
            path = malloc(sizeof(char) * l);
            sprintf(path, "%s/%s", name, entry->d_name);

            printf("direccion en path: %s\n", path);
            printf("Es un archivo\n\n");
            push(st, path);
        }
    }*/

    closedir(dir);

} // Fin de la funcion listar_directorios