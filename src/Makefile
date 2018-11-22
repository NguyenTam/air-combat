CC=g++
CPPFLAGS=-c -g -std=c++17 -Wall -Wextra -pedantic
SFMLFLAGS=-pthread -lsfml-graphics -lsfml-window -lsfml-system
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	g++ $(OBJECTS) $(SFMLFLAGS) -o $(EXECUTABLE) 
%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@
run: $(EXECUTABLE)
	./$(EXECUTABLE)
clean:
	rm -rf *.o  $(EXECUTABLE)
