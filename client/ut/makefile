INCLUDE_PATH=-I../src/ -I../external/gmock-1.7.0/include -I../external/cereal/include
LIBRARY_PATH=../external/gmock-1.7.0/lib/
OUTPUT_PATH=../ut/

CFLAGS= -Wall $(INCLUDE_PATH) -std=c++11 -pthread
LFLAGS= -L$(LIBRARY_PATH) -lboost_system -lgmock -lstdc++

CC=gcc

SRC=$(wildcard *.cpp) $(wildcard ../src/*.cpp)

ut : $(SRC)
	$(CC) $(CFLAGS) -o $(OUTPUT_PATH)$@ $^ $(LFLAGS)