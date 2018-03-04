
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	int i = 0;
	int backSlash = 0;
	char *palabrita = "/Escritorio/Proyecto/respaldo/bieeeeeen/";
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

	printf("palabrita normal: %s\n", palabrita);
	printf("palabrita final: %s\n", resultado);

}