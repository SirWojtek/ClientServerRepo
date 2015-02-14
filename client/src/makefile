include ../global.makefile

SRC=$(wildcard *.cpp) $(wildcard ../../common/messages/*.cpp)

all : client

client : $(SRC)
	$(CC) $(CFLAGS) -o $(OUTPUT_PATH)$@ $^ $(LFLAGS)