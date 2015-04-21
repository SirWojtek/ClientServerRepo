#!/bin/bash

if [ ! -d "simpleClientLogs" ]; 
then
	mkdir simpleClientLogs
fi

rm simpleClientLogs/*

for i in {1..80}
do
   bin/simpleClient > simpleClientLogs/$i.log &
   sleep 0.5
done
