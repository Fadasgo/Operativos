

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

void listar_directorios(Pila *st, char *name, int *verArchivos, int altura, int control2){

    int flaPunto = 0;
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
        path = (char*)calloc(l*100000, sizeof(char));
        sprintf(path, "%s/%s", name, entry->d_name);

        //aqui se pregunta si es un directorio
        if(entry->d_type == DT_DIR)
        {
            if(strcmp(entry->d_name, ".") == 0 ||
               strcmp(entry->d_name, "..") == 0 )
            {
                free(path);
                continue;
            }

            push(st, path);
            control2++;

            if(control2 <= altura)
                listar_directorios(st, path, verArchivos, altura, control2);
        }

        //aqui se pregunta si es un archivo
        else if((entry->d_type == DT_REG) && (*verArchivos == 1))
        {
            push(st, path);
            control2++;
        }

        control2--;

        free(path);
    }

    closedir(dir);

} // Fin de la funcion listar_directorios