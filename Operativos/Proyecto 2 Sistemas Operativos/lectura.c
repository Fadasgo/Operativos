#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/* Prototipos de funciones */
int countlines(char *filename);

void readd(int numLines, char *filename);

int comparaString2(char *str1, char *str2);

int main(int argc, char const *argv[]) {
  int lines = countlines("shell.txt");
  printf("LINES: %d\n",lines);
  printf("Lineas \n");
  //Recibimos la direccion donde comienza el arreglo
  readd(lines,"shell.txt");
  return 0;
}

int countlines(char *filename){
    FILE *fp;
    int count = 0;  // contador de lineas
    char c;  // To store a character read from file

    // Open the file
    fp = fopen(filename, "r");

    // chequea si el archivo existe
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }

    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp)){
        if (c == '\n'){
            count = count + 1;
        }
    }
    // Close the file
    fclose(fp);
    //printf("The file %s has %d lines\n ", filename, count);

    return count;
};

void readd(int numLines, char *filename){
  //Rutas *arrayP = malloc(numLines * sizeof(Rutas));
  //Rutas *InicioArray = arrayP;
  int character, whitespace = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *token;
  int contador = 0;
  int numero = 0; // numero del producto
  //TablaHash* Tabla;
  char *ruta;
  char *palabraArchivo;
  char *clave;
  char* abrir = "()";
  char* Fin = "FinDelBloque";


  FILE *file = fopen ( filename, "r" );

  if (file == NULL){
		exit(EXIT_FAILURE);
  }

	while ((read = getline(&line, &len, file)) != -1) {
    token = strtok(line,"\t");
    /* iteramos sobre los otros token */
    while( token != NULL ) {

      if (contador == 0) {
        if (comparaString2(token,abrir)) {
          printf("ENTROOOOO\n");
          contador = 0;
          numero = numero + 1;
          contador = contador + 1;
        }
      }
      else if (contador == 1 ) {
        clave = token;
        contador = contador + 1;
        printf("CLAVE %s\n",clave);
      }
      else if (contador == 2) {
        palabraArchivo = token;
        contador = contador + 1;
        printf("archivo %s\n",palabraArchivo);
      }
      else if(contador > 2){
        if(comparaString2(token,Fin) != 1) {
          ruta = token;
          printf("RUTA %s\n",ruta);
          // llamamos a la funcion de hash de Albert para pasarle los parametros
          //coincidePalabra(ruta, palabraArchivo, clave, Tabla);
        }

        else if(comparaString2(token,Fin)) {
          contador = 0;
        }
      }
      //printf("contador %d\n", contador );
      //printf( "token %s\n", token ); //--------> Imprime y muestra que esta leyendo bien
      token = strtok(NULL,"\t");
      //contador++;
    }
  }
	free(line);
	fclose(file);
	//exit(EXIT_SUCCESS);

}

int comparaString2(char *str1, char *str2){

  int i = 0;
  int len1 = strlen(str1) - 1;
  int len2 = strlen(str2);

  //printf("Dentro de la funcion comparar\n");
  //printf("strlen(str1): %d\nstr1: %s\nstrlen(str2): %d\nstr2: %s\n", strlen(str1), str1, strlen(str2), str2);

  if(len1 != len2)
  {
    return 0; //no son iguales
  }

	for(i = 0; i < len1; i++)
	{
    if(tolower(*(str1 + i)) != tolower(*(str2 + i)))
      return 0; // no son iguales
	}

  return 1; // son iguales
}
