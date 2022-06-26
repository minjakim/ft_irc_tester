#!/bin/bash

trap "pkill -P $$; exit" SIGINT
trap "pkill -P $$; exit" SIGTERM
trap "pkill -P $$; exit" SIGQUIT

if [ $# -eq 2 ]; then
	IP=$1
else
	IP="127.0.0.1"
fi

make re -C ../
make re -C ./resources/terminator/
rm -rf diff/$1

../ircserv 6667 6667 > /dev/null 2> /dev/null&
clear

CASE=$(/bin/ls ./testcases/case/$1)
for case in ${CASE[@]}
do
	echo $1
	echo $case
	./resources/terminator/tester ./testcases/case/$1/$case $IP
done

make fclean -C ../
make fclean -C ./resources/terminator/

pkill -P $$
