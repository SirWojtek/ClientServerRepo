#!/bin/bash

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
		echo "Error checking database status. Either access is denied or databse does not exist."
	fi
else
	echo "MySQL is down or not installed. Fix that before trying again.";
fi