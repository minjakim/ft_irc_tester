#!/bin/bash

CASE=$(/bin/ls ./testcases/case/$1)
for case in ${CASE[@]}
do
	echo $1
	echo $case
	./resources/terminator/tester ./testcases/case/$1/$case $2
	read
	clear
done
