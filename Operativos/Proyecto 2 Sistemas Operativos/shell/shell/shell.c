#include <stdio.h>
#include <stdlib.h>

#define SHELLSCRIPT "\
#Busqueda directa a traves;\n\
echo -e "Ingrese la direccion COMPLETA a buscar ";\n\
#variable para ingresar una direccion a buscar;\n\
read dirToSearch;\n\
#echo $dirToSearch;\n\
#variable que indentifica si es directorio o archivo;\n\
echo "Ingrese el tipo de busqueda: Si es archivo f, si es directorio: d ";\n\
read tipo;\n\
if [[ "$tipo" = "d" ]];\n\
then;\n\
  Buscada_Dir=`find $dirToSearch -type d -name *$1*`;\n\
  if [ $Buscada_Dir -z ];\n\
  then;\n\
    echo "la direccion ingresada esta vacia - aborta";\n\
    exit 1;\n\
  else;\n\
    echo -e "$Buscada_Dir";\n\
  fi;\n\
elif [[ "$tipo" == "f" ]];\n\
then;\n\
  Buscada_Dir=`find $dirToSearch -type f -name *$1*`;\n\
  if [ $Buscada_Dir -z ];\n\
  then;\n\
    echo "la direccion ingresada esta vacia - aborta";\n\
    exit 1;\n\
  else;\n\
    echo -e "$Buscada_Dir";\n\
  fi;\n\
fi;\n\
# fin de estructura de verificacion;\n\
#escritura del txt;\n\
archIndx=archIndx.txt;\n\
if [ -f $archIndx ];\n\
then;\n\
    IFS='/' read -ra ADDR <<< "$Buscada_Dir";\n\
    len=${#ADDR[@]};\n\
    echo "${ADDR[$len - 1]}" >> "$archIndx";\n\
    echo "$1" >> "$archIndx";\n\
    echo "$Buscada_Dir" >> "$archIndx";\n\
else;\n\
    echo "Se creara un archivo indice, $archIndx";\n\
    touch $archIndx;\n\
fi;\n\
"

int main()
{
    puts("Will execute sh with the following script :");
    puts(SHELLSCRIPT);
    puts("Starting now:");
    system(SHELLSCRIPT);
    return 0;
}
