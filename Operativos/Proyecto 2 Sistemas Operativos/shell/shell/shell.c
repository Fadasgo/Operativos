#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(argc,argv)
char *argv[50];
int argc;
{
    //printf("%s\n",argv[1]);
    char src[50];
    char dest[50];
    strcpy(src, "bash buscarArch.sh ");
    strcpy(dest, argv[1]);
    strcat(src,dest);
    printf("puestooooo : %s\n", src );
    puts("Will execute sh with the following script :");
    puts(src);
    puts("Starting now:");
    system(src);
    return 0;
}
