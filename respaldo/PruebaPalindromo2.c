
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

	int i = 0;
	int j = 0;
	int k = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int palindromo = 1;
	int intermedio = 0;

	char *boletaso = "casacama";

	printf("longitud del string: %d\n", strlen(boletaso));

	intermedio = strlen(boletaso);

	printf("string: %s\n\n", boletaso);

	for(int m = 2; m < intermedio; m++)
	{
		//printf("variable m: %d primer for\n\n", m);

		for(j = m, i = 0; j <= intermedio; i++, j++)
		{
			b = i;
			c = j;

			//printf("variables b: %d y c: %d segundo for\n", b, c);

			for(a = 0; a <= m/2; a++)
			{
				//printf("valores de a: %d y m/2: %d\n", a, m/2);
				//printf("letras a comparar, ¿%c == %c? tercer for\n", *(boletaso + b), *(boletaso + c));
				if(*(boletaso + b) != *(boletaso + c))
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
				//printf("valores de i: %d y j: %d\n", i, j);
				char *aaaiiiuuuda = malloc((sizeof(char)) * m); 
				strncpy(aaaiiiuuuda, boletaso+i, m+1);
				printf("palindromaso: %s\n", aaaiiiuuuda);
			}

			//printf("\n");
		}

		//printf("\n");

	}
}