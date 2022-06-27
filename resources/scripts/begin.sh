#! /bin/bash
trap "pkill -P $$; exit" SIGINT
trap "pkill -P $$; exit" SIGTERM
trap "pkill -P $$; exit" SIGQUIT
