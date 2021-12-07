DIR_NAME="www/joke_files/jokes"
STR="$QUERY_STRING"
printf "Content-Type: text/plain\r\n\n"

if [ -z "$STR" ]
then
	if [ -z "$(ls $DIR_NAME)" ]
	then
		echo "There are no jokes. Upload some jokes first."
		return 0
	fi
	JOKE="$(ls $DIR_NAME | shuf -n 1)"
	FILE="$DIR_NAME/$JOKE"
else
	IFS="="
	set $STR
	JOKE="joke_$2"
	FILE="$DIR_NAME/$JOKE"
fi

echo "$JOKE :\n\n"

if [ -f "$FILE" ]
then
	cat $FILE
else
	echo "This joke doesn't exist"
fi