#!/bin/bash

make -C ./resources/terminator/

TEST=$(/bin/ls ./testcases/case)

for test in ${TEST[@]}
do
	clear
	./test.sh $test
done
