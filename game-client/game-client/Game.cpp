#include "Game.h"

constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 600;

constexpr auto MOVE_SPEED = 2.0f;
constexpr auto JUMP_FORCE = 4.0f;
constexpr auto ACCELERATION = 0.5f;
constexpr auto DECELERATION = 0.5f;
constexpr auto LADDER_SPEED = 3.0f;
constexpr auto INTERACTION_RANGE = 50.0f;

const b2Vec2 GRAVITY_RATE( 0.0f, 1.5f );


Game::Game(sf::RenderWindow& window, TextureManager& textureManager)
	:mWindow(window), mWorld(GRAVITY_RATE) {}

void Game::initializePhysicsWorld()
{

	//std::vector<sf::IntRect> barriers = {
	//	sf::IntRect(WINDOW_WIDTH / 2, -10, WINDOW_WIDTH, 20), // top barrier
	//	sf::IntRect(-10, WINDOW_HEIGHT / 2, 20, WINDOW_HEIGHT), // left barrier
	//	sf::IntRect(WINDOW_WIDTH + 10, WINDOW_HEIGHT / 2, 20, WINDOW_HEIGHT), // right barrier
	//	sf::IntRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 10, WINDOW_WIDTH, 20) // bottom barrier
	//};
	//b2BodyDef bDef;
	//b2FixtureDef fDef;
	//b2PolygonShape shape;

	//for (auto& barrier : barriers)
	//{
	//	sf::Vector2i pos = barrier.getPosition();
	//	sf::Vector2i dims = barrier.getSize();
	//	bDef.position.Set(pos.x / B2_SF_SCALE, pos.y / B2_SF_SCALE);
	//	bDef.type = b2_staticBody;
	//	b2Body* body = mWorld.CreateBody(&bDef);
	//	shape.SetAsBox(dims.x / 2 / B2_SF_SCALE, dims.y / 2 / B2_SF_SCALE);
	//	fDef.shape = &shape;
	//	fDef.density = 1.0f;
	//	fDef.friction = 0.3f;
	//	body->CreateFixture(&fDef);
	//	
	//}
}

std::vector<Entity*> Game::setUpLevel()
{
	std::vector<sf::IntRect> barriers = {
	sf::IntRect(WINDOW_WIDTH / 2, -10, WINDOW_WIDTH, 20), // top barrier
	sf::IntRect(-10, WINDOW_HEIGHT / 2, 20, WINDOW_HEIGHT), // left barrier
	sf::IntRect(WINDOW_WIDTH + 10, WINDOW_HEIGHT / 2, 20, WINDOW_HEIGHT), // right barrier
	sf::IntRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 10, WINDOW_WIDTH, 20) // bottom barrier
	};
	auto top = new Entity({ {400, -10}, {800, 20} }, mWorld, b2_staticBody,false, nullptr, sf::Color::Black);   // Top wall
	auto left = new Entity({ { -10, 300}, {20, 600} }, mWorld, b2_staticBody, false, nullptr, sf::Color::Black);   // Left wall
	auto right = new Entity({ {810, 300}, {20, 600} }, mWorld, b2_staticBody, false, nullptr, sf::Color::Black);   // Right wall
	auto ground = new Entity({ {400, 590}, {800, 20} }, mWorld, b2_staticBody, false, nullptr, sf::Color::Green);   // Ground
	auto platform = new Entity({ {400, 500}, {200, 20} }, mWorld, b2_staticBody, false, nullptr, sf::Color::Green); // platform
	auto player = new Entity({ {400, 100}, {40, 40} }, mWorld, b2_dynamicBody,true, nullptr, sf::Color::Red);

	return { player, top, left, right, ground, platform};
}

void Game::pollEvents(Entity* player)
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
		if (event.type == sf::Keyboard::E)
		{
			player->isInteracting(true);
		}

	}
}

void Game::handleKeyboardInput(Entity* player)
{
	if (!player->physicsBody())
		throw std::runtime_error("Physics body uninitialized");

	b2Body* physicsBody = player->physicsBody();
	b2Vec2 velocity = physicsBody->GetLinearVelocity();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		velocity.x = b2Max(velocity.x - ACCELERATION, -MOVE_SPEED);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocity.x = b2Min(velocity.x + ACCELERATION, MOVE_SPEED);
	else
		velocity.x = velocity.x * DECELERATION;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !player->isJumping())
	{
		velocity.y = -JUMP_FORCE;
		player->isJumping(true);
	}


	physicsBody->SetLinearVelocity(velocity);
}

void Game::run()
{
	initializePhysicsWorld();

	std::vector<Entity*> entities = setUpLevel();

	Entity* player = entities[0];
	sf::Clock clock;
	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		
		pollEvents(player);

		handleKeyboardInput(player);

		mWorld.Step(1.0f / 60.0f, 8, 3);

		if (player->physicsBody()->GetLinearVelocity().y == 0.0f)
			player->isJumping(false);

		if (player->isInteracting()) {
			player->isInteracting(false); 
		}

		mWindow.clear(sf::Color::White);

		player->updatePosition();

		
		for (auto entity : entities)
			mWindow.draw(*entity->sprite());
		

		mWindow.display();
	}
}


