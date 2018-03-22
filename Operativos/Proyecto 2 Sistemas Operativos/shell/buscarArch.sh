#!/bin/bash
if [ $# -ne 1 ]
then
    echo "Usage - $0  file-name"
    exit 1
fi

if [ -d $1 ]
then
    echo "el directorio: $1   exist"

elif [ -f $1 ]
then
  echo "el archivo: $1   existe"

else
    echo "Sorry, $1 file does not exist"
fi

ATRIBUTOS_SCRIPT=`find $1 ~/Operativos/`
echo -e "$ATRIBUTOS_SCRIPT \n"
