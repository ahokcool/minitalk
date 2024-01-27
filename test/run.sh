#!/bin/bash

gnome-terminal --window --hide-menubar --title "ASTEINS MINITALK SERVER" --geometry=60x70+630+100 --working-directory="$PWD" -- "./run_server.sh"
SERVER_PID=0
while [ $SERVER_PID -eq 0 ]
do
    sleep 1
    SERVER_PID=$(pidof 'server')
done
echo "Server PID: $SERVER_PID"
gnome-terminal --window --hide-menubar --title "ASTEINS MINITALK CLIENT" --geometry=60x70+10+100 --working-directory="$PWD" -- "./run_client.sh" $SERVER_PID
