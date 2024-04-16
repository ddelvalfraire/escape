#ifndef PUZZLE_H
#define PUZZLE_H

class Puzzle
{
public:
	Puzzle() : mIsSolved(false) {}
	virtual bool isSolved() = 0;
	virtual void solve() = 0;

protected:
	bool mIsSolved;
};
#endif // !PUZZLE_H
