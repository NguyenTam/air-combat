# Simple Makefile for test files

CC = g++
CFLAGS = -Wall -pedantic -g
LINKER = -pthread -lsfml-graphics -lsfml-window -lsfml-system

TEST_SRC = UI_test
OBJECTS =
EXE = UI

default: all

all:	$(TEST_SRC)

UI_test:
	$(CC) $(CFLAGS) ../src/UI.cpp UI_test.cpp -o UI $(LINKER)


clean:
	$(RM) ${OBJECTS} ${EXE}