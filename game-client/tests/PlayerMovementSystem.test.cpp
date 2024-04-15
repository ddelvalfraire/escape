#include "pch.h"

#include "../game-client/Entity.h"
#include "../game-client/EntityFactory.h"
#include "../game-client/PositionComponent.h"
#include "../game-client/VelocityComponent.h"
#include "../game-client/PlayerMovementSystem.h"
#include "../game-client/MovementStateComponent.h"

struct PlayerData
{
	PositionComponent& position;
	VelocityComponent& velocity;
	MovementStateComponent& moveState;
};

PlayerData getPlayerData(Entity &player) 
{
	return {
		player.getComponent<PositionComponent>(),
		player.getComponent<VelocityComponent>(),
		player.getComponent<MovementStateComponent>()
	};
}

sf::Event createEvent(sf::Keyboard::Key key)
{
	sf::Event::KeyEvent data;
	data.code = key;
	data.alt = false;
	data.control = false;
	data.shift = false;
	data.system = false;

	// create an key press event
	sf::Event e;
	e.type = sf::Event::KeyPressed;
	e.key = data;
	return e;
}

Entity* getTestPlayer()
{
	EntityFactory& entityFactory = EntityFactory::getInstance();
	return entityFactory.createPlayer();
}

class PlayerMovementSystemTest : public ::testing::Test
{
public:
	PlayerMovementSystemTest()
		: window(sf::VideoMode(720, 1280), "PlayerMovementSystemTest"), player(getTestPlayer()), system(nullptr)
	{
		system = new PlayerMovementSystem(window, *player);
	}

	void TearDown() override
	{
		delete system;
		delete player;
	}

	sf::RenderWindow window;
	PlayerMovementSystem* system;
	Entity* player;
	

};


TEST_F(PlayerMovementSystemTest, walkForwardTest)
{
	
	// update with known value
	sf::Event event = createEvent(sf::Keyboard::D);

	system->_update(event,1.0f);

	PlayerData data = getPlayerData(*player);

	EXPECT_FLOAT_EQ(data.position.x, MOVE_SPEED);
	EXPECT_FLOAT_EQ(data.velocity.x, MOVE_SPEED);
}

TEST_F(PlayerMovementSystemTest, walkBackwardTest)
{
	sf::Event event = createEvent(sf::Keyboard::A);
	system->_update(event, 1.0f);

	PlayerData data = getPlayerData(*player);

	EXPECT_FLOAT_EQ(data.position.x, -MOVE_SPEED);
	EXPECT_FLOAT_EQ(data.velocity.x, -MOVE_SPEED);
}

TEST_F(PlayerMovementSystemTest, jumpTest)
{
	sf::Event event = createEvent(sf::Keyboard::W);

	system->_update(event, 1.0f);

	PlayerData data = getPlayerData(*player);

	EXPECT_LT(data.velocity.y, 0.0F);
	EXPECT_TRUE(data.moveState.isJumping);
	EXPECT_TRUE(data.moveState.isFalling);
}