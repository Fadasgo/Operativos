IFS=' ' read -ra ADDR
for  i in "${ADDR[@]}" ; do
done
if [[ -n ${#ADDR[@]} ]]; then
  echo "Lo sentimos ha ingresado caracteres invalidos"
fi
