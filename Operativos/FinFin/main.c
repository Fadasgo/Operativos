#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

// Estructuras

typedef struct ruta{
   char name[2000]; // contiene la direccion de un directorio hoja
}Paths;

 // Prototipos de funciones

int countlines(char *filename);

Paths* readd(int numLines, char *filename);

int procesaEntrada(int argc, char **argv, char **dir, int *altura, int *verArchivos);

void parentProces(void * shmem, int control);

void* create_shared_memory(size_t size);

void Palindromos(char *palabra, void *shmem, int control);

int cuentaSlashs(char *palabrita);

char* eliminaSlash(char *palabrita);

int main(int argc, char **argv) {

  /* Variables */
	int altura = 20; // por defecto
	int verArchivos = 0; // falso 0 si el usuario no uso el  flag -f. 1 en caso contrario
	char *dir = NULL;
  int booleanoD = 0; // falso si el usuario no uso el el flag -d. 1 en caso contrario
  char *resultado;

	int opcion = procesaEntrada(argc, argv, &dir, &altura, &verArchivos);

	if(opcion < 0){
    printf("¡ERROR!\nEl programa se cerrara.\n");
    return 0;
  }

  // primero buscamos los directorios hojas para luego buscar las rutas de los archivos
  #define SIZEP 1000 // tamaño del arreglo que va a contener la direccion inicial
  long size;
  char *buf;
  char *ptr;
  char startPath[SIZEP];
  char cortadera[SIZEP];
  char* c1 = "find ";
  char* c2 = " -type d -links 2 -print | tee directorio.txt";
  char* c3 = "sed 's/^[^:]*";
  //char* c3 = "sed 's/^[^:]*Descargas/Descargas/' casa.txt > cosa.txt";
  char* c4 = "/";
  char* c5 = "/' directorio.txt > dirFinal.txt";

  // Buscamos la direcchttps://www.youtube.com/watch?v=efUThp7fTl4ion del path donde estamos situados para despues poder buscar el archivo.txt creado mas adelante
  size = pathconf(".", _PC_PATH_MAX);
  if ((buf = (char *)malloc((size_t)size)) != NULL);
  ptr = getcwd(buf, (size_t)size); // poner condicional para saber si la ruta que vamos a usar es la de donde estamos parados o la dada por el flag

  //printf("PATH %s \n", ptr); // print para verificar el path

  // caso si el usuario no coloca una ruta en especifica
  if (dir == "."){
    //printf("NO PASASTE LA RUTA \n");
    // guardamos el ultimo directorio de la derecha del path
    char *arr = ptr;

    for(int i = strlen(arr); i >= 0; i--)
    {
      //printf("posicion: %c\ni: %d\n\n", *(arr+i), i);

      if(*(arr+i) == '/')
      {
        //printf("total a copiar: %d\n", strlen(arr)-i);
        resultado = malloc(sizeof(char) * strlen(arr)-i+1);
        strncpy(resultado, (arr + i+1), strlen(arr)-i+1);
        break;
      }
    }
    memset(startPath,0,SIZEP);
    strcat(startPath,c1);
    strcat(startPath,ptr);
    strcat(startPath,c2);
    //strcat(startPath,resultado);
    //strcat(startPath,c3);
    system(startPath);
    int fin1 = strlen(c1) + strlen(ptr) + strlen(c2);
    //memcpy((startPath + strlen(fin1)+1), '\0',1);
    //cortamos inicios de paths
    memset(cortadera,0,SIZEP);
    strcat(cortadera,c3);
    strcat(cortadera,resultado);
    strcat(cortadera,c4);
    strcat(cortadera,resultado);
    strcat(cortadera,c5);
    system(cortadera);
    system("clear");

  }
  else if (dir != ".") {
    //printf("ASI ES COMPARTIENDO LA RUTA \n");
    char *arr = dir;

    for(int i = strlen(arr); i >= 0; i--)
    {
      //printf("posicion: %c\ni: %d\n\n", *(arr+i), i);

      if(*(arr+i) == '/')
      {
        //printf("total a copiar: %d\n", strlen(arr)-i);
        resultado = malloc(sizeof(char) * strlen(arr)-i+1);
        strncpy(resultado, (arr + i+1), strlen(arr)-i+1);
        break;
      }
    }
    booleanoD = 1; // se uso el flag -d
    memset(startPath,0,SIZEP);
    strcat(startPath,c1);
    strcat(startPath,dir);
    strcat(startPath,c2);
    //strcat(startPath,resultado);
    //strcat(startPath,c3);
    system(startPath);
    int fin = strlen(c1) + strlen(dir) + strlen(c2);
    //memcpy((startPath + strlen(fin)+1), '\0',1);
    memset(cortadera,0,SIZEP);
    strcat(cortadera,c3);
    strcat(cortadera,resultado);
    strcat(cortadera,c4);
    strcat(cortadera,resultado);
    strcat(cortadera,c5);
    system(cortadera);
    //printf("PATH %s\n",dir );
    // guardamos el ultimo directorio de la derecha del path
    system("clear");
  }


  // ahora procedemos a leer el archivo creado para buscar los archivos de los directorios hojas

  // si se usa el flag -f
  if (verArchivos == 1) {

    Paths* arrayDirs;
    Paths* copiaArrayDirs; // Copia de la direccion en donde comienza la lista de productos
    int lines;   // lines contiene el numero de lineas en el archivo
    char* cod1 = "find ";
    char* cod2 = " -type d -links 2 -print | find -type f >> rutas.txt";
    //-type d -links 2
    //char* cod3 = " >> rutas.txt";
    //char* cod3 = "sed 's/^[^:]*";
    //char* c3 = "sed 's/^[^:]*Descargas/Descargas/' casa.txt > cosa.txt";
    ///char* cod4 = "/";
    //char* cod5 = "/' ruta.txt > rutFinal.txt";

    lines = countlines("directorio.txt");
    //printf("LINES: %d\n",lines);
    //printf("Lineas \n");
    // Recibimos la direccion donde comienza el arreglo
    arrayDirs = readd(lines,"directorio.txt");
    copiaArrayDirs = arrayDirs; // creamos copia del inicio del arreglo dinamico

    //printf("PATH i: %s\n",copiaArrayDirs->name);

    system("touch rutas.txt"); // Creamos un archivo nuevo en el cual se van a encontrar las rutas finales
    #define SIZEPATHF 2000 // tamaño del arreglo que va a contener la direccion de los archivos contenidos en los directorios hojas
    char path[SIZEPATHF*lines];
    char re[SIZEPATHF*lines];

    // Procedemos a buscar por cada directorio hoja sus archivos
    for (int i = 0; i < lines; i++) {
      //printf("%s \n",arrayDirs->name);
      memset(path,0,SIZEPATHF*lines); // reseteamos el arreglo temporal
      strcat(path,cod1);
      strcat(path,arrayDirs->name);
      strcat(path,cod2);

      system(path);
      arrayDirs++;
      //printf("RE %s\n",re );
    }
    printf("%s\n",arrayDirs->name );
    system("clear");
    printf("RUTA %s\n",dir);

  }
  int lin;
  Paths* arrayyF;
  Paths* copiaArrayyF;
  Paths* p;
  //char* pr[SIZEPATHF*lin];

  printf("\n Palindromos -- \n");
  // leemos los archivos en caso de haber usado -f y aplicamos procesos
  if (verArchivos == 1) {
    lin = countlines("rutas.txt");
    char* pr[SIZEPATHF*lin];
    //printf("LINES: %d\n",lines);
    //printf("Lineas \n");
    // Recibimos la direccion donde comienza el arreglo
    arrayyF = readd(lin,"rutas.txt");
    copiaArrayyF = arrayyF; // creamos copia del inicio del arreglo dinamico

    for (int i = 0; i < lin; i++) {
      //printf("%s \n",arrayDirs->name)
      //strcat(pr,"echo ");
      strcat(pr,arrayyF->name);

      int control = 0;
      char* salida;
      char* salida2;
      int tamano = sizeof(pr);

      void* shmem = create_shared_memory(tamano);

      //memcpy(shmem, pr, strlen(pr));

      int pid = fork();

      if (pid == 0) {
        //printf("Child read: %s\n", pr);
        salida = eliminaSlash(pr);
        //printf("SALIDA %s\n",salida );
        //memcpy(shmem, salida, strlen(salida)+1);
        Palindromos(salida, shmem, control);
        //memcpy(shmem, salida2, strlen(salida2)+1);
        //printf("Child wrote: %s\n", salida2);
        exit(0);
      }
      else if (pid < 0) {
        perror("Hubo un problema al realizar el fork");
        exit(-1);
      }
      else {
        //wait(NULL);
        parentProces(shmem, control);
        //sleep(1);
        //printf("After 1s, parent read: %s\n", shmem);
      }
      memset(pr,0,SIZEPATHF*lin); // reseteamos el arreglo temporal
      //printf("\n");


      //system(pr);
      arrayyF++;
      //printf("RE %s\n",re );
    }

    /*for(int i = 0; i < lin;i++){
      int control = 0;
      //p->name = arrayyF;
      strcpy(p->name, arrayyF);
      //char* pr = p->name;
      strcat(pr, p->name);
      printf("%s\n",pr );
      char* salida;
      char* salida2;
      int tamano = sizeof(pr);

      void* shmem = create_shared_memory(tamano);

      //memcpy(shmem, pr, strlen(pr));

      int pid = fork();

      if (pid == 0) {
        printf("Child read: %s\n", pr);
        salida = eliminaSlash(pr);
        //printf("SALIDA %s\n",salida );
        //memcpy(shmem, salida, strlen(salida)+1);
        Palindromos(salida, shmem, control);
        //memcpy(shmem, salida2, strlen(salida2)+1);
        //printf("Child wrote: %s\n", salida2);
        exit(0);
      }
      else if (pid < 0) {
        perror("Hubo un problema al realizar el fork");
        exit(-1);
      }
      else {
        //wait(NULL);
        parentProces(shmem, control);
        //sleep(1);
        //printf("After 1s, parent read: %s\n", shmem);
      }

      printf("\n");
      arrayyF++;

    }*/
  }
  // leemos los archivos en caso de no haber usado -f y aplicamos procesos
  /*else if (verArchivos == 0) {
    //int lin;
    //Paths* arrayyF;
    //Paths* copiaArrayyF;
    //Paths* p;
    lin = countlines("dirFinal.txt");
    //printf("LINES: %d\n",lines);
    //printf("Lineas \n");
    // Recibimos la direccion donde comienza el arreglo
    arrayyF = readd(lin,"dirFinal.txt");
    copiaArrayyF = arrayyF; // creamos copia del inicio del arreglo dinamico
    //p->name = arrayyF;
    strcpy(p->name, arrayyF);
    char* pr = p->name;
    int control = 0;
    char* salida;
    char* salida2;
    int tamano = sizeof(pr);

    void* shmem = create_shared_memory(tamano);
    //memcpy(shmem, pr, strlen(pr));
    //memset(shmem,0,typeof(Paths)*lin);

    int pid = fork();

    if (pid == 0) {
      printf("Child read: %s\n", pr);
      salida = eliminaSlash(pr);
      //printf("SALIDA %s\n",salida );
      //memcpy(shmem, salida, strlen(salida)+1);
      Palindromos(salida, shmem, control);
      //memcpy(shmem, salida2, strlen(salida2)+1);
      //printf("Child wrote: %s\n", salida2);
      exit(0);
    }
    else if (pid < 0) {
      perror("Hubo un problema al realizar el fork");
      exit(-1);
    }
    else {
      //wait(NULL);
      parentProces(shmem, control);
      //sleep(1);
      //printf("After 1s, parent read: %s\n", shmem);
    }

    printf("\n");
    arrayyF++;

  }*/
  // si falta llave es de aqui
  // hacemos clear de los archivos txts que no se usan (directorios.txt)
  //system("clear");
  printf("PTR %s\n",ptr);
  printf("resultado: %s\n", resultado);
  printf("CORTADERA %s\n",cortadera );

  return 0;
}


// Funciones
int countlines(char *filename){
    FILE *fp;
    int count = 0;  // contador de lineas
    char c;  // To store a character read from file

    // Abrimos el archivo
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
}

Paths* readd(int numLines, char *filename){
  Paths* arrayP = malloc(numLines * sizeof(Paths));
  Paths* InicioArray = arrayP;
  char* line = NULL;
  //char *line2 = NULL;
  size_t len = 0;
  ssize_t readd;
  char *token;
  Paths ruta;

  FILE *file = fopen ( filename, "r" );

  if (file == NULL){
		exit(EXIT_FAILURE);
  }

	while ((readd = getline(&line, &len, file)) != -1) {
    char* dirs;
    token = strtok(line,"\n");
    //printf("%s \n", token);
    strcpy(ruta.name,token);
    *arrayP = ruta;
    //printf("%s \n", arrayP->name);
    arrayP++;
  }

  free(line);
  fclose(file);
  return InicioArray;
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

void* create_shared_memory(size_t size) {
  // Our memory buffer will be readable and writable:
  int protection = PROT_READ | PROT_WRITE;

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it:
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  return mmap(NULL, size, protection, visibility, 0, 0);
}

void Palindromos(char *palabra, void *shmem, int control){

  int i = 0;
  int j = 0;
  int k = 0;
  int a = 0;
  int b = 0;
  int c = 0;
  //int control = 0;
  int palindromo = 1;
  int intermedio = strlen(palabra);
  char *pal;
  char *final = malloc((sizeof(char)) * 1);
  char *final2 = "";

  for(int m = 2; m < intermedio; m++)
  {
    for(j = m, i = 0; j <= intermedio; i++, j++)
    {
      b = i;
      c = j;

      for(a = 0; a <= m/2; a++)
      {
        if(tolower(*(palabra + b)) != tolower(*(palabra + c)))
        {
          palindromo = 0;
          break;
        }

        b++;
        c--;

        if(a == m/2)
        {
          palindromo = 1;
        }
      }

      if(palindromo == 1)
      {

        int largo = 0;
        int largo2 = 0;

        pal = malloc((sizeof(char)) * m);
        strncpy(pal, palabra + i, m + 1);

        //printf("Palcito: %s\n", pal);

        memcpy(shmem, pal, strlen(pal)+1);

        parentProces(shmem, control);

      }
    }
  }
}

int cuentaSlashs(char *palabrita) {
  int i = 0;
  int backSlash = 0;
  int len = strlen(palabrita);

  for(i = 0; i < len; i++)
  {
    if(*(palabrita + i) == '/')
      backSlash++;
  }

  return backSlash;

}

char* eliminaSlash(char *palabrita) {
  int i = 0;
  int backSlash = 0;
  char *resultado;
  int len = strlen(palabrita);

  for(i = 0; i < len; i++)
  {
    if(*(palabrita + i) == '/')
      backSlash++;
  }

  resultado = malloc(sizeof(char) * (len - backSlash));

  for(i = 0; i < len; i++)
  {
    if(*(palabrita + i) == '/')
      continue;

    sprintf(resultado, "%s%c", resultado, *(palabrita + i));
  }

  return resultado;

}


void parentProces(void * shmem, int control){

  if(control == 1 && strlen(shmem) != 0)
  {
    control = 1;
    printf("%s", shmem);
  }

  else if(control == 0 && strlen(shmem) != 0)
  {
    printf(", %s", shmem);
  }

}
