#include "pch.h"

#include "../game-client/EntityFactory.h"
#include "../game-client/LeverPuzzle.h"

class LeverPuzzleTest : public ::testing::Test
{
public:
	LeverPuzzleTest() : entityFactory(EntityFactory::getInstance()) {}

	void SetUp() override
	{
		entities.push_back(entityFactory.createPlayer());
		for (int i = 0; i < 3; ++i)
		{
			sf::Vector2f defaultSpawn = { 0.0f, 0.0f };
			entities.push_back(entityFactory.createLever(defaultSpawn));
		}

		puzzle = new LeverPuzzle(entities);

	}
	void TearDown() override
	{
		for (auto& entity : entities)
		{
			delete entity;
		}
		delete puzzle;
	}

	EntityFactory& entityFactory;
	std::vector<Entity*> entities;
	LeverPuzzle* puzzle;
};

TEST_F(LeverPuzzleTest, isSolvedTestAndSolve)
{
	EXPECT_FALSE(puzzle->isSolved());

	for (auto& entity : entities)
	{
		if (entity->hasComponent<LeverStateComponent>())
		{
			auto& lever = entity->getComponent<LeverStateComponent>();
			lever.isOn = true;
		}
	}

	puzzle->solve();

	EXPECT_TRUE(puzzle->isSolved());
}