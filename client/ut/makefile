include ../global.makefile

INCLUDE_PATH_UT=-I../src/ -Imocks/

CFLAGS_UT= $(CFLAGS) $(INCLUDE_PATH_UT) -ggdb
LFLAGS_UT= $(LFLAGS) -lgtest -lgmock

SRC=$(wildcard *.cpp) $(filter-out ../src/main.cpp, $(wildcard ../src/*.cpp))

ut : $(SRC)
	$(CC) $(CFLAGS_UT) -o $(OUTPUT_PATH)$@ $^ $(LFLAGS_UT)