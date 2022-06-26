#!/bin/bash

trap "pkill -P $$; exit" SIGINT
trap "pkill -P $$; exit" SIGTERM
trap "pkill -P $$; exit" SIGQUIT

if [ $# -eq 0 ]; then
	IP="127.0.0.1"
else
	IP=$1
fi

make re -C ../
make re -C ./resources/terminator/
rm -rf diff/

../ircserv 6667 6667 > /dev/null 2> /dev/null&
clear

TEST=$(/bin/ls ./testcases/case)

for test in ${TEST[@]}
do
	clear
	CASE=$(/bin/ls ./testcases/case/$test)
		for case in ${CASE[@]}
		do
			echo $test
			echo $case
			./resources/terminator/tester ./testcases/case/$test/$case $IP
		done
done

make fclean -C ../
make fclean -C ./resources/terminator/
pkill -P $$
