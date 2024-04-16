#ifndef LEVER_PUZZLE_H
#define LEVER_PUZZLE_H

#include <vector>

#include "Puzzle.h"
#include "Entity.h"

class LeverPuzzle : protected Puzzle
{
public:
	LeverPuzzle(std::vector<Entity*>& entities);
	// Inherited via Puzzle
	bool isSolved() override;
	void solve() override;

private:
	std::vector<Entity*> mLevers;
};

#endif // !LEVER_PUZZLE_H


