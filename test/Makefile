# Simple Makefile for test files

CC = g++
CFLAGS = -Wall -Wextra -pedantic -g -std=c++17
LINKER = -pthread -lsfml-graphics -lsfml-window -lsfml-system

TEST_SRC = Menu_test Editor_test LevelEntity_test
OBJECTS = button.o image_button.o LevelEntity.o Level.o UI.o LevelEditor.o MainMenu.o
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
	$(CC) $(CFLAGS) -c $(SRC)LevelEntity.cpp $(LINKER)

LevelEditor.o:
	$(CC) $(CFLAGS) -c $(SRC)LevelEditor.cpp $(LINKER)

button.o:
	$(CC) $(CFLAGS) -c $(SRC)button.cpp $(LINKER)

image_button.o:
	$(CC) $(CFLAGS) -c $(SRC)image_button.cpp $(LINKER)

Level.o:
	$(CC) $(CFLAGS) -c $(SRC)Level.cpp $(LINKER)

UI.o:
	$(CC) $(CFLAGS) -c $(SRC)UI.cpp $(LINKER)

MainMenu.o:
	$(CC) $(CFLAGS) -c $(SRC)MainMenu.cpp $(LINKER)


# Clean

clean:
	$(RM) ${OBJECTS} $(EXE_OBJECTS) ${ALL_EXES}

clean-objects:
	$(RM) ${OBJECTS} $(EXE_OBJECTS)
