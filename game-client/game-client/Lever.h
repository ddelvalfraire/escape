#ifndef LEVER_H
#define LEVER_H

#include <unordered_map>
#include <queue>

#include "Entity.h"
#include "TextureManager.h"

//class for Lever interactable object
class Lever : public Entity
{
public:
	Lever(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld);

private:
	TextureManager& mTextureManager;
	b2World& mWorld;

};

#endif

