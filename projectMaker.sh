#!/bin/zsh

UP=$(pgrep mysql | wc -l);
if [ "$UP" -gt 0 ];
then
	echo "MySQL detected as up and running.";
	echo "Database builder will be here in the future..."
	cmake -G "Unix Makefiles"
	make
else
	echo "MySQL is down or not installed. Fix that before trying again.";
fi