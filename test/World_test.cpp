
#include "../src/World.hpp"
#include "../src/ResourceManager.hpp"
#include "../src/GameEngine.hpp"


int main() {
	sf::RenderWindow window;
	sf::RenderWindow dialog_window;
	sf::RenderWindow help_window;
		// Create window, size and name don't matter, createMainScreen handles those
	window.create(sf::VideoMode(800, 600), "", sf::Style::Close);
	std::string str = "../data/level_files/Level1.txt";
	ResourceManager manager;
	manager.init();
	World world(window, manager);
	world.read_level(str);
	world.update();
	window.display();
}