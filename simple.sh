#!/bin/bash

trap "pkill -P $$; exit" SIGINT
trap "pkill -P $$; exit" SIGTERM
trap "pkill -P $$; exit" SIGQUIT

if [ $# -eq 3 ]; then
	IP=$2
else
	IP="127.0.0.1"
fi

name=$(ls ./testcases/case | grep $1)

make re -C ../
make re -C ./resources/terminator/
rm -rf diff/$name

../ircserv 6667 6667 > /dev/null 2> /dev/null&
clear

CASE=$(/bin/ls ./testcases/case/$name)
for case in ${CASE[@]}
do
	echo $name
	echo $case
	./resources/terminator/tester ./testcases/case/$name/$case $IP
done

make fclean -C ../
make fclean -C ./resources/terminator/

pkill -P $$
