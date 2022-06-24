#!/bin/bash

trap "pkill -P $$" SIGINT
trap "pkill -P $$" SIGTERM
trap "pkill -P $$" SIGQUIT

make re -C ../
make re -C ./resources/terminator/
rm -rf diff/

../ircserv 6667 6667 > /dev/null 2> /dev/null&
clear

TEST=$(/bin/ls ./testcases/case)

for test in ${TEST[@]}
do
	clear
	./test.sh $test $1
done

make fclean -C ../
make fclean -C ./resources/terminator/




pkill -P $$
