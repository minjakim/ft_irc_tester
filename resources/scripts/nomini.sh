#! /bin/bash

./begin.sh

function nomini()
{
	c++ ../bridge/srcs/main.cpp -o ../bridge/mini
	../bridge/mini mini$1 6667 &
}

#for var in {1..500}
#do
#	nomini $var
#done

./end.sh
