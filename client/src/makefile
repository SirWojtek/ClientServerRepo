INCLUDE_PATH=../external/cereal/include
OUTPUT_PATH=../bin/

CC=gcc
CFLAGS= -Wall -I$(INCLUDE_PATH) -std=c++11 -pthread
LFLAGS= -lboost_system -lstdc++

SRC=$(wildcard *.cpp)

all : client

client : $(SRC)
	$(CC) $(CFLAGS) -o $(OUTPUT_PATH)$@ $^ $(LFLAGS)