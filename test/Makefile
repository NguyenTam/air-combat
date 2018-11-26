# Simple Makefile for test files

CC = g++
CFLAGS = -Wall -Wextra -pedantic -g -std=c++17
LINKER = -pthread -lsfml-graphics -lsfml-window -lsfml-system

OBJECTS = button.o image_button.o LevelEntity.o Level.o UI.o LevelEditor.o MainMenu.o TextInput.o
EXE_OBJECTS = MainMenu_test.o LevelEditor_test.o LevelEntity_test.o
EXE = Menu

SRC = ../src/

all:	Menu_test Editor_test LevelEntity_test ResourceManager_test

run: Menu_test
	./$(EXE)

Menu_test: $(OBJECTS) MainMenu_test.cpp
	$(CC) $(CFLAGS)  $^  $(LINKER) -o $@

Editor_test: $(OBJECTS) LevelEditor_test.cpp
	$(CC) $(CFLAGS) $^ $(LINKER) -o $@

LevelEntity_test: LevelEntity.o LevelEntity_test.cpp
	$(CC) $(CFLAGS) $^ $(LINKER) -o $@

ResourceManager_test: ResourceManager.o ResourceManager_test.cpp
	$(CC) $(CFLAGS) $^ $(LINKER) -o $@

# Objects
%.o:	$(SRC)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	$(RM) *.o *_test

clean-objects:
	$(RM) *.o

