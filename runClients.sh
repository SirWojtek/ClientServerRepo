#!/bin/bash

if [ ! -d "simpleClientLogs" ]; 
then
	mkdir simpleClientLogs
fi

if [ ! -d "serverLogs" ]; 
then
	mkdir serverLogs
fi

rm simpleClientLogs/*.log
rm serverLogs/*.log

for i in {0..19}
do
	let "a=20-$i"
	echo $a
	bin/simpleClient $i 20 > /dev/null &
	sleep 0.5
done
