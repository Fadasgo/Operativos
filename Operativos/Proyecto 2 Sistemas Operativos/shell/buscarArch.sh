#!/bin/bash
#Busqueda directa a traves
echo -e "\nIngrese la direccion COMPLETA a buscar:"
#variable para ingresar una direccion a buscar
read dirToSearch

#echo $dirToSearch

#variable que indentifica si es directorio o archivo
echo "Ingrese el tipo de busqueda: Si es archivo: f, si es directorio: d "
read tipo

if [[ "$tipo" = "d" ]];
then
  Buscada_Dir=`find $dirToSearch -type d -name *$1*`
  if [ $Buscada_Dir -z ]
  then
    echo "la direccion ingresada esta vacia - aborta"
    exit 1
  else
    echo -e "$Buscada_Dir \n"
  fi

elif [[ "$tipo" == "f" ]];
then
  Buscada_Dir=`find $dirToSearch -type f -name *$1*`

  if [ $Buscada_Dir -z ]
  then
    echo "la direccion ingresada esta vacia - aborta"
    exit 1
  else
    echo -e "$Buscada_Dir \n"
  fi
fi
# fin de estructura de verificacion

#escritura del txt

archIndx=archIndx.txt

if [ -f $archIndx ] #aqui se encarga de revisar si es directorio
then
    IFS='/' read -ra ADDR <<< "$Buscada_Dir"
    len=${#ADDR[@]}
    echo "${ADDR[$len - 1]}" >> "$archIndx"

    echo "$1" >> "$archIndx"
    echo "$Buscada_Dir" >> "$archIndx"

else
    echo "Se creara un archivo indice, $archIndx"
    touch $archIndx
fi
