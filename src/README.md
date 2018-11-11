apt install libspdlog-dev
g++ -c Game.cpp
g++ Game.o -o sfml-app -pthread -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app

