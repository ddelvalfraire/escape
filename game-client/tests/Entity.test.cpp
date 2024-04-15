#include "pch.h"

#include "../game-client/EntityFactory.h"
#include "../game-client/PositionComponent.h"
#include "../game-client/VelocityComponent.h"

class EntityTest : public::testing::Test
{
	void SetUp() override
	{
		EntityFactory& factory = EntityFactory::getInstance();
		e = factory.createPlayer();
	}

	void TearDown() override 
	{
		delete e;
	}
protected:
	Entity* e;
};

TEST_F(EntityTest, hasComponent)
{
	EXPECT_TRUE(e->hasComponent<PositionComponent>());
	EXPECT_TRUE(e->hasComponent<VelocityComponent>());
}

TEST_F(EntityTest, getComponent)
{
	PositionComponent& position = e->getComponent<PositionComponent>();
	EXPECT_FLOAT_EQ(position.x, 0.0f);
	EXPECT_FLOAT_EQ(position.y, 0.0f);
}

TEST_F(EntityTest, addComponent)
{
	e->addComponent<PositionComponent>(1.0f, 2.0f);
	EXPECT_TRUE(e->hasComponent<PositionComponent>());
}

