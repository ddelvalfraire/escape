#ifndef EMERALD_H
#define EMERALD_H

#include "Animatable.h"
#include "ResourceContainer.h"
#include "Entity.h"

class Emerald : public Entity, protected Animatable
{
public:
	Emerald(sf::Vector2f position, ResourceContainer& resourceContainer);
	Emerald(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld);
	~Emerald() = default;

	void update(sf::Time dt) override;


private:
	// Inherited via Animatable
	void loadAnimations() override;
};


#endif // !EMERALD_H




