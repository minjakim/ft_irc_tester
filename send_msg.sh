#! /bin/bash

trap "pkill -P $$; exit" SIGINT
trap "pkill -P $$; exit" SIGTERM
trap "pkill -P $$; exit" SIGQUIT

make re -C ./testserver/

./testserver/receiver 6666 6667&
sleep 3

#DIR="./testcases/case"

#LIST=$(/bin/ls $DIR)

#for list in ${LIST[@]}
#do
#	CASE=$(/bin/ls $DIR/$list)
#	for case in ${CASE[@]}
#	do
#		nc localhost 6666 < $DIR/$list/$case/case
#	done
#done

#nc localhost 6666 < testcases/case/10_invite/06_invite_only_mode_channel/case
nc localhost 6666 < testcases/case/11_kick/01_not_enough_parameter/case

pkill -P $$
