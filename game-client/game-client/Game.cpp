#include "Game.h"
#include "Background.h"
#include "Level.h"
#include "PlayerView.h"
#include "ContactHandler.h"

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
/**
 * @brief game win procedure
 * 
 */
void Game::handleWin()
{
	// win loginc
}

/**
 * @brief game loss procedure
 * 
 */
void Game::handleLoss()
{
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
	
	ContactHandler contactHandler(level.entities(), mResourceContainer.world());
	world.SetContactListener(&contactHandler);

	float elapsedTime = 0.0f;
	const float PHYSICS_TIME_STEP = 1.0f / 75.0f;

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		
		pollEvents();

		player->handleKeyInputs();

		elapsedTime += dt.asSeconds();
		while (elapsedTime >= PHYSICS_TIME_STEP)
		{
			world.Step(PHYSICS_TIME_STEP, 8, 3);
			elapsedTime -= PHYSICS_TIME_STEP;
		}
		

		contactHandler.handleInteractions(player);

		background.update(dt);
	
		for (auto& entity : level.entities())
			entity->update(dt);
		
		view.update();

		contactHandler.removeDeletedBodies();

		window.clear();

		window.setView(view);

		for (auto& sprite : background.getSprites())
			window.draw(*sprite);

		for (auto& entity : level.entities())
			window.draw(*entity->sprite());

		window.display();
	}
}


