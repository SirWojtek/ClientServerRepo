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
		RESULT=`mysqlshow --user=root --password=root test_db | grep -v Wildcard | grep -o test_db`
		if [ "$RESULT" == "test_db" ];
		then
			echo "Dumping current game_db to backup file backups/backup_$DATE.sql"
			mysqldump -u root -proot game_db > backups/backup_"$DATE".sql
			echo "Loading database from game_db.sql"
			mysql -u root -proot game_db < game_db.sql
			echo "Loading database from test_db.sql"
			mysql -u root -proot test_db < test_db.sql
			cmake -G "Unix Makefiles"
			make
		else
			echo "Error checking test database status. Attempting to create database..."
			RESULT=`mysql -uroot -proot -e "CREATE DATABASE IF NOT EXISTS test_db;"`
			if [ "$RESULT" == "" ];
			then
				echo "Database created successfully, running script again."
				./projectMaker.sh
			else
				echo "Error: $RESULT"
			fi
		fi
	else
		echo "Error checking production database status. Attempting to create database..."
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
