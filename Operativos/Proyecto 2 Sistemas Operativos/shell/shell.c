#include <stdio.h>
#include <string.h>

#define SHELLSCRIPT "
#!/bin/bash
if [ $# -ne 1 ] #revisa si ha sido ingresado algun dato a buscar
then
    echo "Usage - $0  file-name"
    exit 1
fi

#$1 es la variable que contiene la palabra ingresada
if [ -d $1 ] #aqui se encarga de revisar si es directorio
then
    echo "el directorio: $1 exist"

elif [ -f $1 ] #aqui si es para verifircar si existe
then
  echo "el archivo: $1 existe"

else
    echo "Sorry, $1 file does not exist"
fi

#Busqueda directa a traves
echo -e "Ingrese la direccion a buscar \n \nSi desea la Carpeta actual ingrese: . \n"
#variable para ingresar una direccion a buscar
read dirToSearch

echo $dirToSearch

Busca_Dir=`find $dirToSearch -type d -name "$1"`

if [ $Busca_Dir -z ]
then
  echo "judete"
else
  echo -e "$Busca_Dir \n"
fi
#estructura de verificacion
"
int main(){
  system(SHELLSCRIPT);
  return 0;
}
