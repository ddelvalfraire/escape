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
	:mResourceContainer(window), mStatus(InGame), mElapsedTime(0) {}

void Game::handlePostGame()
{
	auto& window = mResourceContainer.window();
	auto& texManager = mResourceContainer.textureManager();

	std::string filePath = "Banners/";
	sf::IntRect rect;

	if (mStatus == Loss)
	{
		filePath += "Loser.png";
		rect = sf::IntRect(0, 0, 1024, 362);
	}
	
	else if (mStatus == Win)
	{
		filePath += "Winner.png";
		rect = sf::IntRect(0, 0, 1024, 325);
	}
		

	sf::Texture* tex;

	if (texManager.hasTexture(filePath))
		tex = texManager.getTexture(filePath);
	else
		tex = texManager.loadTexture(filePath);

}

/**
 * @brief Entry point for the game
 * 
 */
MenuAction Game::run()
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
	const int CHEST_GOAL = 3, EMERALD_GOAL = 9;
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		
		if (player->chestsOpened() == CHEST_GOAL && player->emeraldsCollected() == EMERALD_GOAL)
			return InMenu;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return Exit;
			}
		}

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


		window.clear();

		window.setView(view);

		for (auto& sprite : background.getSprites())
			window.draw(*sprite);

		for (auto& entity : level.entities())
			window.draw(*entity->sprite());

		window.display();

		contactHandler.removeDeletedBodies();
	}

	return InMenu;
}


