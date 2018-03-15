

#include <stdio.h>
#include <string.h>

#define LEN 45

int funcionHash(char *palabra);

int main(){

	char *prueba1 = "hola :D";
	char *prueba2 = "me parece correcto";
	char *prueba3 = "esto va a quedar peluche";

	int a = funcionHash(prueba1);
	int b = funcionHash(prueba2);
	int c = funcionHash(prueba3);
}

int funcionHash(char *palabra){

	int i = 0;
	int lenPalabra = strlen(palabra);
	int total = 0;

	for(i = 0; i < lenPalabra; i++)
	{
		total = *(palabra + i) + total;
	}

	printf("total: %d\n", total%LEN);	

	return total%LEN;
}