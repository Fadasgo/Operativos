#!/bin/bash
#Busqueda directa a traves
echo -e "\nIngrese la direccion COMPLETA a buscar \n"
#variable para ingresar una direccion a buscar
read dirToSearch

echo $dirToSearch

#variable que indentifica si es directorio o archivo
echo "Ingrese el tipo de busqueda: Si es archivo f, si es directorio: d "
read $tipo

if [[ $tipo == "d" ]];
then
  Busca_Dir=`find $dirToSearch -type d -name "$1"`

  if [ $Busca_Dir -z ]
  then
    echo "la direccion ingresada esta vacia - aborta"
    exit 1
  else
    echo -e "$Busca_Dir \n"
  fi

elif [[ $tipo == "f" ]];
then
  Busca_Dir=`find $dirToSearch -type f -name "$1"`

  if [ $Busca_Dir -z ]
  then
    echo "la direccion ingresada esta vacia - aborta"
    exit 1
  else
    echo -e "$Busca_Dir \n"
  fi
fi


#estructura de verificacion
