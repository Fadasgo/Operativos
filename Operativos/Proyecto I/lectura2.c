#include<stdio.h>
#include <string.h>
#include <stdlib.h>

// Lectura Proyecto II

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

    // extraemos los caracteres y los guardamos en la variable c
    for (c = getc(fp); c != EOF; c = getc(fp)){
        if (c == '\n'){
            count = count + 1;
        }
    }
    // cerramos el archivo
    fclose(fp);

    return count;
};

char* readd(int numLines, char *filename){
  char* arrayP = malloc(numLines * sizeof(char));
  char* InicioArray = arrayP;
  char* line = NULL;
  //char *line2 = NULL;
  size_t len = 0;
  ssize_t readd;
  char *token;

  FILE *file = fopen ( filename, "r" );

  if (file == NULL){
		exit(EXIT_FAILURE);
  }

	while ((readd = getline(&line, &len, file)) != -1) {
		//printf("Retrieved line of length %zu :\n", readd);
		//printf("%s", line);
    //line2 = line;
    char* dirs;
    token = strtok(line,"\n");
    printf("%s \n", token);
    arrayP = token;
    arrayP++;
  }
  free(line);
  fclose(file);
  return InicioArray;
}

int main(int argc, char *argv[]) {
  char* arrayDirs;
  char* copiaArrayDirs; // Copia de la direccion en donde comienza la lista de productos
  int lines;
  // lines contiene el numero de lineas en el archivo
  lines = countlines(argv[1]);
  printf("LINES: %d\n",lines);
  printf("Lineas \n");
  // Recibimos la direccion donde comienza el arreglo
  arrayDirs = readd(lines,argv[1]);
  return 0;
}
