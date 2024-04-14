#include "pch.h"

#include "../game-client/Entity.h"
#include "../game-client/PositionComponent.h"
#include "../game-client/VelocityComponent.h"

class EntityTest : public::testing::Test
{
protected:
	Entity e;
};

TEST_F(EntityTest, hasComponent)
{
	e.addComponent<PositionComponent>(1.0f, 1.0f);
	EXPECT_TRUE(e.hasComponent<PositionComponent>());
	EXPECT_FALSE(e.hasComponent<VelocityComponent>());
}

TEST_F(EntityTest, getComponent)
{
	e.addComponent<PositionComponent>(1.0f, 1.0f);
	PositionComponent& position = e.getComponent<PositionComponent>();
	EXPECT_FLOAT_EQ(position.x, 1.0f);
	EXPECT_FLOAT_EQ(position.y, 1.0f);
}

TEST_F(EntityTest, addComponent)
{
	e.addComponent<PositionComponent>(1.0f, 2.0f);
	EXPECT_TRUE(e.hasComponent<PositionComponent>());
}

