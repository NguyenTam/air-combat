# Simple Makefile for test files

# About automatic variables $^ and $@. $^ equals to target name. $@ equals to list of dependency.
# Example:
# output_test: foo1.o foo2.o foo3_test.cpp
# => $^ is "foo1.o foo2.o foo3_test.cpp"
# => $@ is "output_test"

CC = g++
CFLAGS = -Wall -Wextra -pedantic -g -std=c++17
LINKER = -pthread -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs -lBox2D

OBJECTS = PhysicsWorld.o Plane.o Artillery.o Infantry.o Bullet.o World.o Entity.o button.o image_button.o LevelEntity.o Level.o UI.o LevelEditor.o MainMenu.o TextInput.o CommonDefinitions.o ResourceManager.o Plane.o Artillery.o Infantry.o Bullet.o World.o PhysicsWorld.o GameEngine.o Tree.o Stone.o Ground.o Base.o Hangar.o InvisibleWall.o AI.o
UI_OBJECTS = UI.o button.o image_button.o CommonDefinitions.o ResourceManager.o TextInput.o

SRC = ../src/

all:	World_test Menu_test Editor_test LevelEntity_test ResourceManager_test GameEngine_test Stats_test

run: Menu_test
	./Menu_test

Menu_test:	$(UI_OBJECTS) MainMenu.o MainMenu_test.cpp
	$(CC) $(CFLAGS)  $^  $(LINKER) -o $@

World_test:$(OBJECTS)  World_test.cpp
	$(CC) $(CFLAGS)  $^  $(LINKER) -o $@

Editor_test:  $(UI_OBJECTS) LevelEntity.o Level.o LevelEditor.o LevelEditor_test.cpp
	$(CC) $(CFLAGS) $^ $(LINKER) -o $@

LevelEntity_test: LevelEntity.o LevelEntity_test.cpp
	$(CC) $(CFLAGS) $^ $(LINKER) -o $@

ResourceManager_test: CommonDefinitions.o ResourceManager.o ResourceManager_test.cpp
	$(CC) $(CFLAGS) $^ $(LINKER) -o $@

GameEngine_test: $(OBJECTS) CommonDefinitions.o ResourceManager.o GameEngine.o GameEngine_test.cpp
	$(CC) $(CFLAGS) $^ $(LINKER) -o $@

Stats_test:	$(UI_OBJECTS) Stats.o Stats_test.cpp
	$(CC) $(CFLAGS) $^ $(LINKER) -o $@

# Instruction to compile from cpp-files in src-folder to object-files.
%.o:	$(SRC)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	$(RM) *.o *_test

clean-objects:
	$(RM) *.o
