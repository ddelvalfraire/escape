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
	sf::RenderWindow window;
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
