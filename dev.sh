#! /bin/bash

trap "pkill -P $$; exit" SIGINT
trap "pkill -P $$; exit" SIGTERM
trap "pkill -P $$; exit" SIGQUIT

#make re -C ../
#../ircserv 6667 6667 > /dev/null 2> /dev/null&

make re -C ./testserver/
./testserver/receiver 6666 6667 > /dev/null&
sleep 2

#DIR="./testcases/case"

#if [ $# -eq 0 ]; then
#	LIST=$(/bin/ls $DIR)
#else
#	LIST=$(/bin/ls $DIR | grep $1)
#fi

#for list in ${LIST[@]}
#do
#	CASE=$(/bin/ls $DIR/$list)
#	for case in ${CASE[@]}
#	do
#		nc localhost 6666 < $DIR/$list/$case/case
#	done
#done

nc localhost 6666 < ./testcases/case/01_pass/00_no_parameter/case
nc localhost 6666 < ./testcases/case/01_pass/01_wrong_password/case
nc localhost 6666 < ./testcases/case/01_pass/02_already_registered/case
nc localhost 6666 < ./testcases/case/02_nick/00_no_parameter/case
nc localhost 6666 < ./testcases/case/02_nick/01_nickcname_length_over_9/case
nc localhost 6666 < ./testcases/case/02_nick/02_first_letter_not_alphabet/case
nc localhost 6666 < ./testcases/case/02_nick/03_not_allowed_letter/case
nc localhost 6666 < ./testcases/case/02_nick/04_normal_nickname/case
nc localhost 6666 < ./testcases/case/02_nick/05_already_registered/case
nc localhost 6666 < ./testcases/case/02_nick/06_already_in_use/case
nc localhost 6666 < ./testcases/case/03_user/00_not_enough_parameter/case
nc localhost 6666 < ./testcases/case/03_user/01_normal/case
nc localhost 6666 < ./testcases/case/03_user/02_already_registered/case
nc localhost 6666 < ./testcases/case/04_quit/00_before_register/case
nc localhost 6666 < ./testcases/case/04_quit/01_after_register/case
nc localhost 6666 < ./testcases/case/04_quit/02_after_join_channel/case
nc localhost 6666 < ./testcases/case/05_join/00_before_register/case
nc localhost 6666 < ./testcases/case/05_join/01_no_parameter/case
nc localhost 6666 < ./testcases/case/05_join/02_invalid_channel_name/case
nc localhost 6666 < ./testcases/case/05_join/03_valid_channel_name/case
nc localhost 6666 < ./testcases/case/05_join/04_client_join_channels_to_max/case
nc localhost 6666 < ./testcases/case/05_join/05_full_channel/case
nc localhost 6666 < ./testcases/case/06_part/00_before_register/case
nc localhost 6666 < ./testcases/case/06_part/01_no_parameter/case
nc localhost 6666 < ./testcases/case/06_part/02_no_such_channel/case
nc localhost 6666 < ./testcases/case/06_part/03_not_on_channel/case
nc localhost 6666 < ./testcases/case/06_part/04_part/case
nc localhost 6666 < ./testcases/case/06_part/05_part_from_channels/case
nc localhost 6666 < ./testcases/case/07_topic/00_before_register/case
nc localhost 6666 < ./testcases/case/07_topic/01_no_parameter/case
nc localhost 6666 < ./testcases/case/07_topic/02_no_such_channel/case
nc localhost 6666 < ./testcases/case/07_topic/03_not_on_channel/case
nc localhost 6666 < ./testcases/case/07_topic/04_not_channel_operator/case
nc localhost 6666 < ./testcases/case/07_topic/05_protected_topic_mode_channel/case
nc localhost 6666 < ./testcases/case/07_topic/06_topic/case
nc localhost 6666 < ./testcases/case/08_names/00_before_register/case
nc localhost 6666 < ./testcases/case/08_names/01_no_parameter/case
nc localhost 6666 < ./testcases/case/08_names/02_channel/case
nc localhost 6666 < ./testcases/case/09_list/00_before_register/case
nc localhost 6666 < ./testcases/case/09_list/01_no_such_channel/case
nc localhost 6666 < ./testcases/case/09_list/02_no_parameter/case
nc localhost 6666 < ./testcases/case/09_list/03_channels/case
nc localhost 6666 < ./testcases/case/10_invite/00_before_register/case
nc localhost 6666 < ./testcases/case/10_invite/01_no_paramter/case
nc localhost 6666 < ./testcases/case/10_invite/02_no_such_nick/case
nc localhost 6666 < ./testcases/case/10_invite/03_no_such_channel/case
nc localhost 6666 < ./testcases/case/10_invite/04_not_on_channel/case
nc localhost 6666 < ./testcases/case/10_invite/05_already_on_channel/case
nc localhost 6666 < ./testcases/case/10_invite/06_invite_only_mode_channel/case
nc localhost 6666 < ./testcases/case/10_invite/07_invite/case
nc localhost 6666 < ./testcases/case/11_kick/00_before_register/case
nc localhost 6666 < ./testcases/case/11_kick/01_not_enough_parameter/case
nc localhost 6666 < ./testcases/case/11_kick/02_no_such_channel/case
nc localhost 6666 < ./testcases/case/11_kick/03_not_operator/case
nc localhost 6666 < ./testcases/case/11_kick/04_no_such_nick/case
nc localhost 6666 < ./testcases/case/11_kick/05_target_is_not_on_channel/case
nc localhost 6666 < ./testcases/case/11_kick/06_one_to_one/case
nc localhost 6666 < ./testcases/case/11_kick/07_one_to_many/case
nc localhost 6666 < ./testcases/case/11_kick/08_many_to_one/case
nc localhost 6666 < ./testcases/case/11_kick/09_many_to_many/case
nc localhost 6666 < ./testcases/case/12_mode/00_before_register/case
nc localhost 6666 < ./testcases/case/12_mode/01_no_parameter/case
nc localhost 6666 < ./testcases/case/12_mode/02_no_such_channel/case
nc localhost 6666 < ./testcases/case/12_mode/03_not_channel_operator/case
nc localhost 6666 < ./testcases/case/12_mode/04_no_such_nick/case
nc localhost 6666 < ./testcases/case/12_mode/05_not_equal_nickname/case
nc localhost 6666 < ./testcases/case/12_mode/06_unknown_flag/case
nc localhost 6666 < ./testcases/case/12_mode/07_channel_mode/case
nc localhost 6666 < ./testcases/case/13_privmsg/00_before_register/case
nc localhost 6666 < ./testcases/case/13_privmsg/01_not_enough_parameter/case
nc localhost 6666 < ./testcases/case/13_privmsg/02_no_such_channel/case
nc localhost 6666 < ./testcases/case/13_privmsg/03_no_message_channel_mode/case
nc localhost 6666 < ./testcases/case/13_privmsg/04_to_channel/case
nc localhost 6666 < ./testcases/case/13_privmsg/05_to_client/case
nc localhost 6666 < ./testcases/case/13_privmsg/06_send_to_list/case
nc localhost 6666 < ./testcases/case/14_notice/00_before_register/case
nc localhost 6666 < ./testcases/case/14_notice/01_not_enough_parameter/case
nc localhost 6666 < ./testcases/case/14_notice/02_no_such_channel/case
nc localhost 6666 < ./testcases/case/14_notice/03_no_message_channel_mode/case
nc localhost 6666 < ./testcases/case/14_notice/04_to_channel/case
nc localhost 6666 < ./testcases/case/14_notice/05_to_client/case
nc localhost 6666 < ./testcases/case/14_notice/06_send_to_list/case
nc localhost 6666 < ./testcases/case/15_unknown/00_before_register/case
nc localhost 6666 < ./testcases/case/15_unknown/01_after_register/case
nc localhost 6666 < ./testcases/case/16_bot/00_invalid/case
nc localhost 6666 < ./testcases/case/16_bot/01_valid/case

pkill -P $$
