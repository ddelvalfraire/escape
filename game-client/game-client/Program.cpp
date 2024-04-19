#include <SFML/Graphics.hpp>

#include "Program.h"
#include "Game.h"


/**
 * @brief Program entry point
 * 
 */
void Program::run()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Escape");
	Game game(window, mTexManager);

	game.run();
}
