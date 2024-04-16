#include "LeverPuzzle.h"

/**
 * @brief Construct a new Lever Puzzle:: Lever Puzzle object
 * 
 * @param entities entities in currne tuse
 */
LeverPuzzle::LeverPuzzle(std::vector<Entity*>& entities)
{
	for (auto entity : entities)
	{
		if (entity->hasComponent<LeverStateComponent>())
		{
			mLevers.push_back(entity);
		}
	}
}

/**
 * @brief getter for mIsSolved
 * 
 */
bool LeverPuzzle::isSolved()
{
	return mIsSolved;
}

/**
 * @brief Iterates through a list of levers and sets the puzzle to solved when 
 * 		  they are all in the "on" state
 * 
 */
void LeverPuzzle::solve()
{
	for (Entity* lever : mLevers)
	{
		LeverStateComponent& state = lever->getComponent<LeverStateComponent>();
		if (!state.isOn)
		{
			mIsSolved = false;
			return;
		}
	}
	mIsSolved = true;
}
