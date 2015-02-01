INCLUDE_PATH=external/cereal/include
OUTPUT_PATH=bin/client

CC=gcc
CFLAGS= -Wall -I$(INCLUDE_PATH) -std=c++11 -pthread
LFLAGS= -lboost_system -lstdc++

all : main

main : src/main.cpp src/TcpSocket.cpp src/Client.cpp src/Console.cpp src/MessageQueue.cpp src/MessageWriter.cpp src/CommunicationService.cpp
	$(CC) $(CFLAGS) src/main.cpp src/TcpSocket.cpp src/Client.cpp src/Console.cpp  src/MessageQueue.cpp src/MessageWriter.cpp src/CommunicationService.cpp -o$(OUTPUT_PATH) $(LFLAGS)