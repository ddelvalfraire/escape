#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "Level.h"
#include "PlayerView.h"

/**
 * @brief Construct a new Game:: Game object
 * 
 * @param window reference to the main window
 * @param textureManager reference to the texture manager
 */
Game::Game(sf::RenderWindow& window)
	:mResourceContainer(window) {}


/**
 * @brief Polls for window events
 * 
 */
void Game::pollEvents()
{
	sf::RenderWindow& window = mResourceContainer.window();

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}
sf::Vector2f convertBox2dToSFML(const b2Vec2& vector, const float& scale) {
	return sf::Vector2f(vector.x * scale, vector.y * scale);
}

/**
 * @brief Entry point for the game
 * 
 */
void Game::run()
{
	sf::RenderWindow& window = mResourceContainer.window();
	b2World& world = mResourceContainer.world();

	Background background(mResourceContainer);
	Level level("tiled/1.tmx", { 400, 100 },mResourceContainer);
	Player* player = level.player();
	PlayerView view(window, player, level.metaData());

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		
		pollEvents();

		player->handleKeyInputs();

		world.Step(1.0f / 60.0f, 8, 3);

		if (player->isInteracting()) {
			player->isInteracting(false); 
		}

		player->update(dt); // updates need to happen after interactions
		background.update(dt);

	
		view.update();

		window.clear();

		window.setView(view);

		for (auto& sprite : background.getSprites())
			window.draw(*sprite);

		for (auto& entity : level.entities())
			window.draw(*entity->sprite());
		
		
		window.display();
	}
}


