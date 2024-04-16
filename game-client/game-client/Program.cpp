#include <SFML/Graphics.hpp>

#include "Program.h"
#include "FrameConstants.h"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;
Program::Program() mGame(entities)

void Program::initResources()
{
	mGraphicsResourceManager.loadTexture(PLAYER_IDLE);
	mGraphicsResourceManager.storeFrames(PLAYER_IDLE, PLAYER_IDLE_FRAMES);
}

/**
 * @brief Program entry point
 * 
 */
void Program::run()
{
	initResources();

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
	
		//sprite drawing goes here
		window.display();
	}
}
