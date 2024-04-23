#include "Game.h"
#include "Background.h"
#include "Level.h"
#include "PlayerView.h"
#include "ContactHandler.h"

const auto PROXIMITY_THRESHOLD = 50.0f;
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
void Game::eventHandler(Player* player, std::vector<Entity*>& entities)
{
	for (auto entity : entities)
	{
		// handle non interactive events first
		if (Emerald* emerald = dynamic_cast<Emerald*>(entity))
		{
		}


		if (player->isInteracting() && isInProximity(player, entity))
		{

		}
	}


}

bool Game::isInProximity(Entity* a, Entity* b)
{
	b2DistanceJointDef jDef;
	jDef.bodyA = a->physicsBody();
	jDef.bodyB = b->physicsBody();
	jDef.length = PROXIMITY_THRESHOLD;

	b2DistanceJoint* joint = (b2DistanceJoint*)mResourceContainer.world().CreateJoint(&jDef);

	return joint->GetLength() <= PROXIMITY_THRESHOLD;
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


