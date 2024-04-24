#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <SFML/Graphics.hpp>
#include "MenuAction.h"

class StartScreen
{
public:
	StartScreen(sf::RenderWindow& window);
	~StartScreen() = default;
	
	MenuAction displayMenu();

private:
	sf::RenderWindow& window;
};
#endif // !START_SCREEN_H
