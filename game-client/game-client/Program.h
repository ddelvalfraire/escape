#ifndef PROGRAM_H
#define PROGRAM_H

#include "Game.h"

class Program
{
public:
	Program() = default;
	~Program() = default;

	void run();


private:
	// TODO add global resources here
	Game mGame;
};
#endif // !PROGRAM_H
