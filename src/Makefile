CC=g++
CPPFLAGS=-c -g -std=c++17 -Wall -Wextra -pedantic
SFMLFLAGS=-pthread -lsfml-graphics -lsfml-window -lsfml-system -lBox2D
SOURCES=$(filter-out main.cpp, $(wildcard *.cpp))
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game

all: $(SOURCES) $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) main.cpp $(SFMLFLAGS) -o $(EXECUTABLE)
%.o: %.cpp
	$(CC) $(CPPFLAGS) $< -o $@
run: $(EXECUTABLE)
	./$(EXECUTABLE)
clean:
	rm -rf *.o  $(EXECUTABLE)
