CC=g++
CPPFLAGS=-g -std=c++17 -Wall -Wextra -pedantic -D NDEBUG 
SFMLFLAGS=-pthread -lsfml-graphics -lsfml-window -lsfml-system -lBox2D -lstdc++fs
SOURCES=$(filter-out main.cpp, $(wildcard *.cpp))
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game

all: $(SOURCES) $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) main.cpp $(SFMLFLAGS) -o $(EXECUTABLE)
%.o: %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@
run: $(EXECUTABLE)
	./$(EXECUTABLE)
clean:
	rm -rf *.o  $(EXECUTABLE)
