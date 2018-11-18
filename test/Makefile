# Simple Makefile for test files

CC = g++
CFLAGS = -Wall -Wextra -pedantic -g -std=c++17
LINKER = -pthread -lsfml-graphics -lsfml-window -lsfml-system

TEST_SRC = Menu_test Editor_test
OBJECTS =
EXE = Menu
ALL_EXES = Menu Editor

default: all

all:	$(TEST_SRC)

run: Menu_test
	./$(EXE)

Menu_test:
	$(CC) $(CFLAGS) ../src/MainMenu.cpp ../src/UI.cpp ../src/button.cpp MainMenu_test.cpp -o Menu $(LINKER)

Editor_test:
	$(CC) $(CFLAGS) ../src/LevelEditor.cpp ../src/UI.cpp ../src/image_button.cpp ../src/button.cpp LevelEditor_test.cpp -o Editor $(LINKER)

clean:
	$(RM) ${OBJECTS} ${ALL_EXES}
