#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

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


  FILE *file = fopen ( filename, "r" );

  if (file == NULL){
		exit(EXIT_FAILURE);
  }

	while ((read = getline(&line, &len, file)) != -1) {
    token = strtok(line,"\t");
    /* iteramos sobre los otros token */
    while( token != NULL ) {
      if (strcmp("()",token) == 0) {
        contador = 0;
        numero = numero + 1;
        contador = contador + 1;
        //printf("NUMERO %d\n", newProduct.num);
        //printf("NOMBRE %s\n", newProduct.name);
      }
      if (strcmp("FinDelBloque",token) == 0) {
        contador = 0;
      }
      if (contador == 1 ) {
        clave = token;
        contador = contador + 1;
        printf("ARCHIVO %s\n",palabraArchivo );
      }
      if (contador == 2) {
        palabraArchivo = token;
        contador = contador + 1;
        printf("CLAVE %s\n",clave);
      }
      if(contador > 2){
        ruta = token;
        printf("RUTA %s\n",ruta);
        // llamamos a la funcion de hash de Albert para pasarle los parametros
        //coincidePalabra(ruta, palabraArchivo, clave, Tabla);
      }
      //printf("contador %d\n", contador );
      printf( "token %s\n", token );
      token = strtok(NULL,"\t");
      contador++;
    }
    contador = 0; // restablecemos el contador para la siguiente linea
  }
	free(line);
	fclose(file);
	//exit(EXIT_SUCCESS);

}

int main(int argc, char const *argv[]) {
  int lines = countlines("shell.txt");
  printf("LINES: %d\n",lines);
  printf("Lineas \n");
  //Recibimos la direccion donde comienza el arreglo
  readd(lines,"shell.txt");
  return 0;
}
