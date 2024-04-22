#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "Level.h"
#include "Lever.h"

const b2Vec2 GRAVITY_RATE( 0.0f, 25.0f );

/**
 * @brief Construct a new Game:: Game object
 * 
 * @param window reference to the main window
 * @param textureManager reference to the texture manager
 */
Game::Game(sf::RenderWindow& window, TextureManager& textureManager)
	:mWindow(window), mWorld(GRAVITY_RATE), mTextureManager(textureManager) {}


void Game::createWorldBoundaries(std::vector<Entity*> &entities)
{

	const float WINDOW_WIDTH = mWindow.getSize().x;
	const float WINDOW_HEIGHT = mWindow.getSize().y;

	auto top = new Entity({ {WINDOW_WIDTH / 2, -10}, {WINDOW_WIDTH, 20} }, mWorld, b2_staticBody, false, nullptr, sf::Color::Black);   // Top wall
	auto left = new Entity({ {-10, WINDOW_HEIGHT / 2 }, {20, WINDOW_HEIGHT} }, mWorld, b2_staticBody, false, nullptr, sf::Color::Black);   // Left wall
	auto right = new Entity({ {WINDOW_WIDTH + 10, WINDOW_HEIGHT / 2}, {20, WINDOW_HEIGHT} }, mWorld, b2_staticBody, false, nullptr, sf::Color::Black);   // Right wall
	auto ground = new Entity({ {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 10}, {WINDOW_WIDTH, 20} }, mWorld, b2_staticBody, false, nullptr, sf::Color::Green);   // Ground

}

/**
 * @brief Creates physics boundaries and loads their sprites
 * 
 * @return std::vector<Entity*> an array with all of the entities created for the level
 */
std::vector<Entity*> Game::setUpLevel()
{
	auto platform = new Entity({ {400, 500}, {200, 20} }, mWorld, b2_staticBody, false, nullptr, sf::Color::Green); // platform
	auto player = new Player({ 400.0f, 100.0f }, mTextureManager, mWorld);

	std::vector<Entity*> entities = { player, platform };

	auto levers1 = new Lever({ 500.0f, 300.0f }, mTextureManager, mWorld);

	entities.push_back(levers1);

	createWorldBoundaries(entities);

	return entities;
}



/**
 * @brief Polls for window events
 * 
 */
void Game::pollEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}
}


/**
 * @brief Entry point for the game
 * 
 */
void Game::run()
{

	std::vector<Entity*> entities = setUpLevel();

	Player* player = static_cast<Player*>(entities[0]);
	Background background(mWindow, mTextureManager);
	Level level("tiled/1.tmx", mWindow);

	sf::Clock clock;
	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		
		pollEvents();

		player->handleKeyInputs();

		mWorld.Step(1.0f / 60.0f, 8, 3);

		if (player->isInteracting()) {
			player->isInteracting(false); 
		}

		player->update(dt); // updates need to happen after interactions
		background.update(dt);

		mWindow.clear();

		for (auto& sprite : background.getSprites())
			mWindow.draw(*sprite);

		for (auto& sprite : level.sprites())
			mWindow.draw(*sprite);

		for (auto entity : entities)
			mWindow.draw(*entity->sprite());

		
		
		mWindow.display();
	}
}


