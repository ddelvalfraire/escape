#ifndef PROGRAM_H
#define PROGRAM_H

#include "Game.h"
#include "Entity.h"
#include "GraphicsResourceManager.h"

class Program
{
public:
	Program() = default;
	~Program() = default;

	void run();

private:
	void initResources();
	// TODO add global resources here
	std::vector<Entity*> mEntities;
	GraphicsResourceManager mGraphicsResourceManager;
};
#endif // !PROGRAM_H
