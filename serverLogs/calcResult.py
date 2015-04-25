#!/usr/bin/python

import os

timeCounter = 0.0
responceCounter = 0
environmentCounter = 0
fileAmount = len([name for name in os.listdir('.') if (os.path.isfile(name) and ".log" in name) ])

for filename in os.listdir(os.getcwd()):
	if ".log" not in filename:
		continue
	foo = open(filename, "r")
	timeCounter += float(foo.readline())
	environmentCounter += int(foo.readline())
	responceCounter += int(foo.readline())

print (timeCounter/fileAmount)
print (int(environmentCounter/fileAmount))
print (int(responceCounter/fileAmount))
