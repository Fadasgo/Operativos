
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

typedef struct Pila{

    int N;
    int max_size;
    char **S;

}Pila;

int listar_directorios(Pila* st, char* name, int *files);

void inicializar_p(Pila *st);

int elementos_p(Pila *st);

int vacia_p(Pila *st);

char* tope(Pila *st);

void pop(Pila *st);

void push(Pila *st, char *name);

void destruir_p(Pila *st);

int main(){

	int files = 0;
	char *dir = ".";
	Pila st;

    inicializar_p(&st);

	int b = listar_directorios(&st, dir, &files);

    printf("Numerillo de cosas en pila: %d\n", elementos_p(&st));

    while(!(vacia_p(&st))){

        int len = 0;
        char *nombre = tope(&st);
        printf("nombre del directorio: %s\n", nombre);
        pop(&st);
        printf("nombre del directorio: %s\n", nombre);
        // FAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACK
    }
}

int listar_directorios( Pila *st, char *name, int *files ){

    DIR *dir;             // Se usa un apuntador a DIR para abrir los directorios
    struct dirent *entry; /* En *entry habrá información sobre el archivo 
                             que se está "sacando" a cada momento*/

    if(!(dir = opendir(name))){

    	printf("Algo salio mal al abrir el archivo\n");
        return -1;
    }

    while((entry = readdir(dir)))                     
    {                   
        char *path;
        int l = strlen(name)+strlen(entry->d_name) + 3;
        printf("l almacena el espacio que se debe guardar para nombre del archivo: %d\n", l);
        path = malloc(sizeof(char) * l);
        //guardamos en path la ruta del directorio
        sprintf(path, "%s/%s", name, entry->d_name);
        printf("direccion en path: %s\n", path);

        //aqui se pregunta si es un directorio
        if(entry->d_type == DT_DIR)                         
        {
            if(strcmp(entry->d_name, ".") == 0 ||        
               strcmp(entry->d_name, "..") == 0 )
            {       
                free(path);
                continue;
            }
            printf("Es un directorio\n\n");
            push(st, path);                      
        }

        //aqui se pregunta si es un archivo
        else if(entry->d_type == DT_REG)
        {        
            (*files)++;
            printf("Es un archivo.\nNumero de archivos: %d\n\n", *files);
        }                                          

        free(path);                              
    }

    closedir(dir);

    return 0;

} // Fin de la funcion listar_directorios

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