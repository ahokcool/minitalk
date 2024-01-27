#!/bin/bash

MSG_LONG=$(cat test_msg_long)
MSG_MID=$(cat test_msg_mid)
MSG_SHORT=$(cat test_msg_short)
CMD_1="../client '$MSG_LONG' $1"
CMD_2="../client '$MSG_MID' $1"
CMD_3="../client '$MSG_SHORT' $1"
echo $CMD_1 >> ~/.bash_history
echo $CMD_2 >> ~/.bash_history
echo $CMD_3 >> ~/.bash_history
echo -e "\npress arrow up...\n"
exec bash -i
