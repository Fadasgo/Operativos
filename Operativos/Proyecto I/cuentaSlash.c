#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cuentaSlashs(char *palabrita);

int main(){

	char *palabrita = "/Escritorio/Proyecto/respaldo/bieeeeeen/";


	printf("palabrita normal: %s\n", palabrita);
	printf("La cantidad de slashs final es: %d\n", cuentaSlashs(palabrita));

}
int cuentaSlashs(char *palabrita) {
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
	free(resultado);
	return backSlash;

}
