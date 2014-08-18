INCLUDE_PATH=/usr/include/
OUTPUT_PATH=../

CC=g++
CFLAGS=-c -Wall -I$(INCLUDE_PATH) -std=c++0x

all : main.o

main.o : main.cpp  TcpSocket.cpp
	$(CC) $(CFLAGS) main.cpp TcpSocket.cpp