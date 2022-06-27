#!/bin/bash

trap "pkill -P $$" SIGINT
trap "pkill -P $$" SIGTERM
trap "pkill -P $$" SIGQUIT

make re -C ./resources/terminator/
rm -rf diff/

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
			./resources/terminator/tester ./testcases/case/$test/$case $1
		done
done

make fclean -C ../
make fclean -C ./resources/terminator/
pkill -P $$
