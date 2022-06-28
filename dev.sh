#! /bin/bash

trap "pkill -P $$; exit" SIGINT
trap "pkill -P $$; exit" SIGTERM
trap "pkill -P $$; exit" SIGQUIT

make re -C ../
../ircserv 6667 6667 > /dev/null 2> /dev/null&

make re -C ./testserver/
./testserver/receiver 6666 6667 > /dev/null&
sleep 2

DIR="./testcases/"

if [ $# -eq 0 ]; then
	LIST=$(/bin/ls $DIR)
else
	LIST=$(/bin/ls $DIR | grep $1)
fi

for list in ${LIST[@]}
do
	CASE=$(/bin/ls $DIR/$list)
	for case in ${CASE[@]}
	do
		echo $list/$case
		cat $DIR/$list/$case/case | nc localhost 6666
	done
done

make fclean -C ./testserver/

pkill -P $$

./diff.sh
