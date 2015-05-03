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

for i in {0..159}
do
	let "a=160-$i"
	echo $a
	bin/simpleClient $i 160 > /dev/null &
	sleep 0.5
done
