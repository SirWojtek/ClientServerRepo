#!/usr/bin/python

import os, sys

clientTimeCounter = 0.0
timeCounter = 0.0
responceCounter = 0
environmentCounter = 0

if len(sys.argv) != 2:
	raise Exception('usage: ./script.py <dirname>')

path = sys.argv[1]
os.chdir(path)

serverFileAmount = len([name for name in os.listdir('serverLogs') if (os.path.isfile(os.path.join('serverLogs', name)) and ".log" in name) ])
clientFileAmount = len([name for name in os.listdir('simpleClientLogs') if (os.path.isfile(os.path.join('simpleClientLogs', name)) and ".log" in name) ])
if serverFileAmount != clientFileAmount:
	raise Exception('File amount in server and client dirs does not match')

for fileIndex in range(0, serverFileAmount):
	serverFileName = "serverLogs/" + str(fileIndex) + ".log"
	fooServer = open(serverFileName, "r")
	timeCounter += float(fooServer.readline())
	environmentCounter += int(fooServer.readline())
	responceCounter += int(fooServer.readline())
	clientFileName = "simpleClientLogs/" + str(fileIndex) + ".log"
	fooClient = open(clientFileName, "r")
	clientTimeCounter += float(fooClient.readline())

print (timeCounter/serverFileAmount)
print (clientTimeCounter/serverFileAmount)
print ((clientTimeCounter/serverFileAmount - timeCounter/serverFileAmount) / 2)
print (int(environmentCounter/serverFileAmount))
print (int(responceCounter/serverFileAmount))
