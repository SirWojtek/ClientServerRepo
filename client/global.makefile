.PHONY: all client ut

INCLUDE_PATH=-I../external/cereal/include
OUTPUT_PATH=../bin/

CFLAGS= -Wall -std=c++11 -pthread $(INCLUDE_PATH)
LFLAGS= -lboost_system -lstdc++

CC=gcc
