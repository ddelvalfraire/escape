#include "pch.h"

#include "../game-client/EntityFactory.h"

class EntityFactoryTest : public ::testing::Test
{
public:
	EntityFactoryTest() : entityFactory(EntityFactory::getInstance()) {}
	EntityFactory& entityFactory;
};

TEST_F(EntityFactoryTest, createPlayerTest)
{
	Entity* player = entityFactory.createPlayer();

	EXPECT_NE(player, nullptr);
	EXPECT_TRUE(player->hasComponent<PositionComponent>());
	EXPECT_TRUE(player->hasComponent<VelocityComponent>());
	EXPECT_TRUE(player->hasComponent<MovementStateComponent>());

	delete player;
}