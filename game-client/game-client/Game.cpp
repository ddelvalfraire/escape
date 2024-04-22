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
	Emerald em({ 500, 100 }, mResourceContainer);

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
	
		em.update(dt);
		
		view.update();

		window.clear();

		window.setView(view);

		for (auto& sprite : background.getSprites())
			window.draw(*sprite);

		for (auto& entity : level.entities())
			window.draw(*entity->sprite());

		window.draw(*em.sprite());
		
		
		window.display();
	}
}


