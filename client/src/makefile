include ../global.makefile

SRC=$(wildcard *.cpp)

all : client

client : $(SRC)
	$(CC) $(CFLAGS) -o $(OUTPUT_PATH)$@ $^ $(LFLAGS)