#! /bin/bash

function nomini()
{
	c++ ../bridge/srcs/main.cpp -o ../bridge/mini
	../bridge/mini mini$1 6667 &
}

trap "pkill -P $$" SIGINT
trap "pkill -P $$" SIGTERM
trap "pkill -P $$" SIGQUIT

#for var in {1..500}
#do
#	nomini $var
#done

pkill -P $$
