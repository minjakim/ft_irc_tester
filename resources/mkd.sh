#!/bin/bash

LIST=$(/bin/ls $1)

for list in ${LIST[@]}
do
	CASE=$(/bin/ls ./$1/$list)
	for case in ${CASE[@]}
	do
		echo $list/$case/ >> ./$1/$list/$case/case
	done
done
