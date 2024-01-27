#!/bin/bash

CMD="../server"
echo $CMD
sleep 1
$CMD
echo $CMD >> ~/.bash_history
exec bash -i
