#include "LeverPuzzle.h"

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

bool LeverPuzzle::isSolved()
{
	return mIsSolved;
}

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
