#!/bin/bash

git submodule update --init

if [ ! -d "backups" ]; 
then
	mkdir backups
fi

DATE=$(date +"%H:%M:%S_%d-%m-%Y");
UP=$(pgrep mysql | wc -l);
if [ "$UP" -gt 0 ];
then
	echo "MySQL detected as up and running.";
	RESULT=`mysqlshow --user=root --password=root game_db | grep -v Wildcard | grep -o game_db`
	if [ "$RESULT" == "game_db" ]; 
	then
		echo "Dumping current game_db to backup file backups/backup_$DATE.sql"
		mysqldump -u root -proot game_db > backups/backup_"$DATE".sql
		echo "Loading database from game_db.sql"
		mysql -u root -proot game_db < game_db.sql
		cmake -G "Unix Makefiles"
		make
	else
		echo "Error checking database status. Attempting to create database..."
		RESULT=`mysql -uroot -proot -e "CREATE DATABASE IF NOT EXISTS game_db;"`
		if [ "$RESULT" == "" ];
		then
			echo "Database created successfully, running script again."
			./projectMaker.sh
		else
			echo "Error: $RESULT"
		fi
	fi
else
	echo "MySQL is down or not installed. Fix that before trying again.";
fi
