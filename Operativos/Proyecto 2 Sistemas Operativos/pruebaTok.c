
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

int main(){

	char *queBonito = "esto es una prueba.pdff";
	char *prueba = "una";
	char *prueba2 = "pdf";

	int len = strlen(queBonito);
	int lenPrueba = strlen(prueba);
	int i = 0;
	int j = 0;
	int k = 0;
	int control = 0;
	int coincide = 0;

	for(i = 0; i < len; i++)
	{
		if((*(queBonito + i) == ' ' || *(queBonito + i) == '.' || i == len-1))
		{
			for(j = 0; j < lenPrueba; j++)
			{
				if(tolower(*(queBonito + k)) != tolower(*(prueba + j)))
				{
					control = 1;
					break;
				}
				k++;
			}

			if(control == 0)    // si coincide se imprime la carita
			{
				coincide = 1;
			}

			k = i+1;
			control = 0;
		}
	}

	if(coincide)
	{
		k = 0;

		for(i = 0; i < len; i++)
		{
			if((*(queBonito + i) == ' ' || *(queBonito + i) == '.' || i == len-1))
			{

	    		char *tak = malloc(sizeof(char)*((i - k) + 1));

	    		int o = k;
	    		
				for(j = 0; j < (i - o); j++)
				{
					printf("*(queBonito + k): %c\n", *(queBonito + k));
					sprintf(tak, "%s%c", tak, *(queBonito + k));
					k++;
				}

				printf("tak: %s\nstrlen(tak): %d\n", tak, strlen(tak));

				k = i+1;
			}
		}
	}

	return 0;
}