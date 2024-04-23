#ifndef CHEST_H
#define CHEST_H

#include "Toggle.h"
#include "Entity.h"
#include "ResourceContainer.h"

class Chest : public Toggle, public Entity
{
public:
	Chest(sf::Vector2f position, ResourceContainer& resourceContainer);
	Chest(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld);

	void update(sf::Time dt) override;

};
#endif // !CHEST_H
