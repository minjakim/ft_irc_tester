#! /bin/bash

function start_server()
{
	make re -C ../../.. > /dev/null
	../../../ircserv 6667 1234 > /dev/null 2>&1 &
	../servers/miniircd/miniircd --ports 6668 > /dev/null 2>&1 &
	cd ../servers/ergo
	./ergo run > /dev/null 2>&1 &
	cd ../../scripts
}

function start_client()
{
	c++ ../bridge/srcs/main.cpp -o ../bridge/mini
	../bridge/mini $1 6667 6668 6669
}

trap "pkill -P $$" SIGINT
trap "pkill -P $$" SIGTERM
trap "pkill -P $$" SIGQUIT


start_server
sleep 2
start_client test
pkill -P $$
