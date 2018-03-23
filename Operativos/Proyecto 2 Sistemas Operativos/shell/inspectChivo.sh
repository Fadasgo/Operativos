#!/usr/bin/env bash
echo "Ingrese lo que desee verificar que este en el texto"

read direccion

grep "$direccion" archIndx.txt
