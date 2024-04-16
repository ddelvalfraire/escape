#include <SFML/Graphics.hpp>

#include "Program.h"
#include "TextureManager.h"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

/**
 * @brief Program entry point
 * 
 */
void Program::run()
{

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Escape");
	sf::Clock clock;

	while (window.isOpen()) 
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		sf::Event event;

		while (window.pollEvent(event))
		{
			// keyboard input handling goes here
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		// logic updates with dt go here


		mGame.update(dt); 
	
		//sprite drawing goes here

		window.display();
	}
}
