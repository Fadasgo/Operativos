

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

void inicializar_p(Pila *st){

    st->N = 0;
    st->max_size = 50;
    st->S = (char**)calloc(st->max_size*50, sizeof(char *));

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

    st->S[N] = (char*)calloc(l+1*100000, sizeof(char));

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