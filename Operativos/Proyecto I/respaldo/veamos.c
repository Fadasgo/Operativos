#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
  char frase[100];
  char fraseResultante[100];
  char caracter[1];
  int i, j;

  clrscr ();
  printf ("Introduzca una frase y pulse INTRO (máximo 100 caracteres): ");
  gets (frase);
  printf ("\nIntroduzca el carácter a eliminar y pulse INTRO: ");
  gets (caracter);
  i = 0;
  j = 0;
  while (frase[i] != '\0')
  {
    if (caracter[0] != frase[i])
    {
      fraseResultante[j] = frase[i];
	  j++;
    }
    i++;
  }
  fraseResultante[j] = '\0';
  printf ("\n\nFrase resultante sin '%s': \n\n%s", caracter, fraseResultante);
  printf ("\n\n\nPulsa cualquier tecla para salir.");
  getch ();
  return 0;
}