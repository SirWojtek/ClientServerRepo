#!/bin/bash

if [ ! -d "simpleClientLogs" ]; 
then
	mkdir simpleClientLogs
fi

rm simpleClientLogs/*

for i in {0..19}
do
   bin/simpleClient $i > /dev/null &
   sleep 0.5
done
