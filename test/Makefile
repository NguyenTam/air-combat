# Simple Makefile for test files

CC = g++
CFLAGS = -Wall -Wextra -pedantic -g -std=c++17
LINKER = -pthread -lsfml-graphics -lsfml-window -lsfml-system

TEST_SRC = Menu_test Editor_test LevelEntity_test
OBJECTS = button.o image_button.o LevelEntity.o Level.o UI.o LevelEditor.o MainMenu.o TextInput.o
EXE_OBJECTS = MainMenu_test.o LevelEditor_test.o LevelEntity_test.o
EXE = Menu
ALL_EXES = Menu Editor LevelEntityTest
SRC = ../src/

default: all

all:	$(TEST_SRC)

run: Menu_test
	./$(EXE)

Menu_test:	$(OBJECTS)
	$(CC) $(CFLAGS)  ${OBJECTS} MainMenu_test.cpp $(LINKER) -o Menu

Editor_test: $(OBJECTS)
	$(CC) $(CFLAGS) ${OBJECTS} LevelEditor_test.cpp $(LINKER) -o Editor

LevelEntity_test:	$(LevelEntity.o)
	$(CC) $(CFLAGS) LevelEntity.o LevelEntity_test.cpp $(LINKER) -o LevelEntityTest

# Objects

LevelEntity.o:
	$(CC) $(CFLAGS) -c $(SRC)LevelEntity.cpp

LevelEditor.o:
	$(CC) $(CFLAGS) -c $(SRC)LevelEditor.cpp

button.o:
	$(CC) $(CFLAGS) -c $(SRC)button.cpp

image_button.o:
	$(CC) $(CFLAGS) -c $(SRC)image_button.cpp

Level.o:
	$(CC) $(CFLAGS) -c $(SRC)Level.cpp

UI.o:
	$(CC) $(CFLAGS) -c $(SRC)UI.cpp

MainMenu.o:
	$(CC) $(CFLAGS) -c $(SRC)MainMenu.cpp

TextInput.o:
	$(CC) $(CFLAGS) -c $(SRC)TextInput.cpp


# Clean

clean:
	$(RM) ${OBJECTS} $(EXE_OBJECTS) ${ALL_EXES}

clean-objects:
	$(RM) ${OBJECTS} $(EXE_OBJECTS)
