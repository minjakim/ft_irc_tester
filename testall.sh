#!/bin/bash

make -C ../
make -C ./resources/terminator/

../ircserv 6667 6667 > /dev/null 2> /dev/null&
clear

TEST=$(/bin/ls ./testcases/case)

for test in ${TEST[@]}
do
	clear
	./test.sh $test
done
