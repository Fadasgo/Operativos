ADDR1=/home/jcellomarcano/Tarea.odf/fabio/mierdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
IFS='/' read -ra ADDR <<< "$ADDR1"
len=${#ADDR[@]}
echo "$len"
for  i in "${ADDR[@]}" ; do
<<<<<<< HEAD
  echo ${ADDR[$len - 1]}
=======
>>>>>>> cdecd081427b6dede40a44971014c5c4178501c7
done

if [[ -n ${#ADDR[@]} ]]; then
  echo "Lo sentimos ha ingresado caracteres invalidos"
fi
