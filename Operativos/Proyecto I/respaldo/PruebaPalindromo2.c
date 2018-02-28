
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){

	int i = 0;
	int j = 0;
	int k = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int palindromo = 1;
	int intermedio = 0;

	char *bol = "cCasacAma";

	printf("longitud del string: %d\n", strlen(bol));

	intermedio = strlen(bol);

	printf("string: %s\n\n", bol);

	for(int m = 2; m < intermedio; m++)
	{
		for(j = m, i = 0; j <= intermedio; i++, j++)
		{
			b = i;
			c = j;

			for(a = 0; a <= m/2; a++)
			{
				if(tolower(*(bol + b)) != tolower(*(bol + c)))
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
				char *aaaiiiuuuda = malloc((sizeof(char)) * m); 
				strncpy(aaaiiiuuuda, bol+i, m+1);
				printf("palindromaso: %s\n", aaaiiiuuuda);
			}
		}
	}
}