.PHONY: all client ut

OUTPUT_PATH=../bin/
INCLUDE_PATH=-I../../common -I../../common/external/cereal/include

CFLAGS= -Wall -std=c++11 -pthread $(INCLUDE_PATH) -ggdb
LFLAGS= -lboost_system -lstdc++

CC=gcc
