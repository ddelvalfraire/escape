#include "StartScreen.h"


StartScreen::StartScreen(sf::RenderWindow& window) :window(window) {}

MenuAction StartScreen::displayMenu()
{
	window.create(sf::VideoMode(1280, 720), "Escape the Game"); //creates the window

	sf::Texture COW; //creates texture
	COW.loadFromFile("Summer1.png");
	sf::Sprite cow; //creates sprite
	cow.setTexture(COW); //sets the texture to the spirte 
	sf::Vector2f backgroundSize = cow.getLocalBounds().getSize(); //gets size to fit texture
	sf::Vector2u windowSize = window.getSize();

	float scalar = std::min(windowSize.x / backgroundSize.x, windowSize.y / backgroundSize.y);
	cow.setScale(scalar, scalar);

	sf::Texture transparant;
	transparant.loadFromFile("background102.png");
	sf::Sprite youspinmy;
	youspinmy.setTexture(transparant);
	youspinmy.setPosition(0, 0);

	sf::Texture texture;
	texture.loadFromFile("UnderButton.png");
	sf::Sprite button;
	button.setTexture(texture);
	button.setTextureRect(sf::IntRect(20, 20, 290, 35));
	button.setPosition(150, 413);

	sf::Sprite button2;
	button2.setTexture(texture);
	button2.setTextureRect(sf::IntRect(20, 20, 300, 35)); //sets size
	button2.setPosition(150, 315); //sets location

	sf::Sprite button3;
	button3.setTexture(texture);
	button3.setTextureRect(sf::IntRect(20, 20, 310, 35)); //sets size
	button3.setPosition(150, 215); //sets location

	sf::Sprite background;
	background.setTexture(texture);
	background.setPosition(150, 300); //sets location

	sf::Font font;
	font.loadFromFile("Chatlong-zrro3.ttf"); //loads font
	sf::Text TitleGame;
	TitleGame.setFont(font); //sets font
	TitleGame.setString("Welcome to Escape"); //displays the text
	TitleGame.setPosition(140, 100); //sets location
	TitleGame.setCharacterSize(65); //sets size (pixels)
	TitleGame.setFillColor(sf::Color::Blue); //sets up text color

	sf::Text Player1;
	Player1.setFont(font);
	Player1.setString("Single Player"); //displays the text
	Player1.setPosition(150, 200);
	Player1.setCharacterSize(50); //sets size (pixels)
	Player1.setFillColor(sf::Color::Blue); //sets up text color

	sf::Text Player2;
	Player2.setFont(font);
	Player2.setString("Multi Player"); //displays the text
	Player2.setPosition(150, 300);
	Player2.setCharacterSize(50); //sets size (pixels)
	Player2.setFillColor(sf::Color::Blue); //sets up text color

	sf::Text Rules;
	Rules.setFont(font);
	Rules.setString("How To Play"); //displays the text
	Rules.setPosition(150, 400);
	Rules.setCharacterSize(50); //sets size (pixels)
	Rules.setFillColor(sf::Color::Blue); //sets up text color

	sf::Text howtoplay;
	howtoplay.setFont(font);
	howtoplay.setString("The goal of the game is to collect the emeralds and open all chest (by pressing E and standing on it),\nUsing the arrow keys to move around Gerald,\ntake him on an adventure to find every emerald so he can feed his famliy.\nFor every emerald you fail to collect, a familiy member will parish."); //displays the text
	howtoplay.setPosition(150, 555);
	howtoplay.setCharacterSize(20); //sets size (pixels)
	howtoplay.setFillColor(sf::Color::Transparent); //sets up text color

	while (window.isOpen())//runs as long as the window is open
	{

		sf::Event event; //checks events
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed) //event is closeing the window
			{
				return Exit;
			}

			if (event.type == sf::Event::MouseButtonPressed) //sets up event
			{
				if (event.mouseButton.button == sf::Mouse::Left) //if the left click used
				{
					sf::Vector2f map;
					map.x = sf::Mouse::getPosition(window).x; //location of mouse
					map.y = sf::Mouse::getPosition(window).y;//location of mouse
					sf::Mouse::getPosition(window); //gets new postion of mouse


					

					if (button2.getGlobalBounds().contains(map.x, map.y)) //if mouse is over the button location
					{
						printf("button 2 pressed");
						//button2.setColor(sf::Color::Red);
						Player2.setFillColor(sf::Color::Cyan);
						howtoplay.setFillColor(sf::Color::Transparent);
						Rules.setFillColor(sf::Color::Blue);
						Player1.setFillColor(sf::Color::Blue);

						//milti player
					}

					else if (button3.getGlobalBounds().contains(map.x, map.y)) //if mouse is over the button location
					{
						printf("button 3 pressed");
						//button3.setColor(sf::Color::Green);
						Player1.setFillColor(sf::Color::Cyan);
						howtoplay.setFillColor(sf::Color::Transparent);
						Rules.setFillColor(sf::Color::Blue);
						Player2.setFillColor(sf::Color::Blue);
						window.close();
						return StartGame;
					}
					else if (button.getGlobalBounds().contains(map.x, map.y)) //if mouse is over the button location
					{
						printf("button 1 pressed");
						//button.setColor(sf::Color::Cyan);
						Rules.setFillColor(sf::Color::Cyan);
						howtoplay.setFillColor(sf::Color::Blue);
						Player1.setFillColor(sf::Color::Blue);
						Player2.setFillColor(sf::Color::Blue);

						
						//play game for single player
					}

				}
			}

			window.clear(); //clears widow then makes it nothing

			window.draw(cow);
			window.draw(youspinmy);
			window.draw(TitleGame);
			window.draw(button);
			window.draw(button2);
			window.draw(button3);

			window.draw(Player1);
			window.draw(Player2);
			window.draw(Rules);
			window.draw(howtoplay);


			window.display();



		}

	}

}
