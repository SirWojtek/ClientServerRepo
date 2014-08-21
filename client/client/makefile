INCLUDE_PATH=-I../external/cereal/include
OUTPUT_PATH=../Debug/main

CC=g++
CFLAGS= -Wall $(INCLUDE_PATH) -std=c++11 -lboost_system -o$(OUTPUT_PATH) -static-libstdc++

all : main

main : main.cpp TcpSocket.cpp Client.cpp Console.cpp
	$(CC) $(CFLAGS) main.cpp TcpSocket.cpp Client.cpp Console.cpp