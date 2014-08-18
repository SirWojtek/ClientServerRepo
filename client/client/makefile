INCLUDE_PATH=../cereal/include
OUTPUT_PATH=../

CC=g++
CFLAGS= -Wall -I$(INCLUDE_PATH) -std=c++11 -lboost_system -o ../Debug/main -static-libstdc++

all : main

main : main.cpp  TcpSocket.cpp
	$(CC) $(CFLAGS) main.cpp TcpSocket.cpp