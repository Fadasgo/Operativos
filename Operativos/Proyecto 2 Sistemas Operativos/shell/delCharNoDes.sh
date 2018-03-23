ADDR1=/home/jcellomarcano/Tarea.odf/fabio/mierdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
IFS='/' read -ra ADDR <<< "$ADDR1"
len=${#ADDR[@]}
echo "$len"
for  i in "${ADDR[@]}" ; do
  echo ${ADDR[$len - 1]}
done

if [[ -n ${#ADDR[@]} ]]; then
  echo "Lo sentimos ha ingresado caracteres invalidos"
fi
