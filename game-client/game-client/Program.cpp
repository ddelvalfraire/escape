#include <SFML/Graphics.hpp>

#include "Program.h"
#include "StartScreen.h"
#include "Game.h"


/**
 * @brief Program entry point
 * 
 */
void Program::run()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Escape");
	Game game(window);
	StartScreen menu(window);

	MenuAction state = InMenu;
	while (state != Exit)
	{
		if (state == InMenu)
			state = menu.displayMenu();

		if (state == StartGame)
			state = game.run();
	}

}
