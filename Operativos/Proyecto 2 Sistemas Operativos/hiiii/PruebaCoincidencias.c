

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

int cuentaSlashs(char *palabrita);

char* eliminaSlash(char *palabrita);

void CoincidenciaEnPalabras(char *coincidencia, char *palabra);

int main(){

	char *prueba = "veamosComo Es EsteBeta";
	char *prueba2 = "te te tetetetete te te te tebete";
	char *coincidencia1 = "Veamos";
	char *coincidencia2 = "EsEste";
	char *coincidencia3 = "beta";
	char *coincidencia4 = "Como Es";
	char *coincidencia5 = "Como Este";
	char *coincidencia6 = "tebe";

	coincidencia1 = eliminaSlash(coincidencia1);
	coincidencia2 = eliminaSlash(coincidencia2);
	coincidencia3 = eliminaSlash(coincidencia3);
	coincidencia4 = eliminaSlash(coincidencia4);
	coincidencia5 = eliminaSlash(coincidencia5);

	printf("|%s| con la coincidencia |%s|\n", prueba, coincidencia1);
	CoincidenciaEnPalabras(coincidencia1, prueba);
	printf("|%s| con la coincidencia |%s|\n", prueba, coincidencia2);
	CoincidenciaEnPalabras(coincidencia2, prueba);
	printf("|%s| con la coincidencia |%s|\n", prueba, coincidencia3);
	CoincidenciaEnPalabras(coincidencia3, prueba);
	printf("|%s| con la coincidencia |%s|\n", prueba, coincidencia4);
	CoincidenciaEnPalabras(coincidencia4, prueba);
	printf("|%s| con la coincidencia |%s|\n", prueba, coincidencia5);
	CoincidenciaEnPalabras(coincidencia5, prueba);

	printf("|%s| con la coincidencia |%s|\n", prueba2, coincidencia6);
	CoincidenciaEnPalabras(coincidencia6, prueba2);

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

char* eliminaSlash(char *palabrita){

    int i = 0;
    int backSlash = 0;
    char *resultado;
    int len = strlen(palabrita);

    for(i = 0; i < len; i++)
    {
        if(*(palabrita + i) == '/')
            backSlash++;
    }

    resultado = (char*)calloc((len - backSlash)*100000, sizeof(char));

    for(i = 0; i < len; i++)
    {
        if(*(palabrita + i) == '/')
            continue;

        sprintf(resultado, "%s%c", resultado, *(palabrita + i));
    }

    return resultado;
}

void CoincidenciaEnPalabras(char *coincidencia, char *palabra){

	int i = 0;
	int j = 0;
	int k = 0;
	int coincide = 0;
	int FlagPunto = 0;
	int FlagEspaciosPalabra = 0;
	int FlagEspaciosCoincidencia = 0;
	int lenPalabra = strlen(palabra);
	int lenConincidencia = strlen(coincidencia);

	printf("lenPalabra: %d\n", lenPalabra);
	printf("lenConincidencia: %d\n", lenConincidencia);

	for(i = 0; i < lenPalabra; i++)
	{
		if(*(palabra + i) == ' ')
			FlagEspaciosPalabra = 1;

		if(*(palabra + i) == '.')
			FlagPunto = 1;
	}

	for(i = 0; i < lenConincidencia; i++)
	{
		if(*(coincidencia + k) == ' ')
			FlagEspaciosCoincidencia = 1;
	}

	for(i = 0; i < lenPalabra; i++)
	{
		if(tolower(*(palabra + i)) == tolower(*(coincidencia + k)))
		{
			//printf("carater de palabra: %c\nCaracter de coincidencia: %c\n",*(palabra + i) ,*(coincidencia + k));
			//printf("carater de palabra: %c\nCaracter de coincidencia: %c\n",*(palabra + i) ,*(coincidencia + k));
			coincide = 1;
			k = i;
			
			for(j = 0; j < lenConincidencia; j++, k++)
			{
				//printf("carater de palabra: %c\nCaracter de coincidencia: %c\n",*(palabra + k) ,*(coincidencia + j));
				//printf("j: %d\nk: %d\ni: %d\n",j ,k, i);
				if((tolower(*(palabra + k)) != tolower(*(coincidencia + j))) ||
				   (tolower(*(palabra + k)) == ' '))
				{
					coincide = 0;
					break;
				}
			}

			k = 0;
		}

		if(coincide == 1)
			break;

	}

	if(coincide == 1)
		printf("Si se pudo :D\n\n");

	else
		printf("fijate que no :(\n\n");
}