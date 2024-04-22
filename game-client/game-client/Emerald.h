#ifndef EMERALD_H
#define EMERALD_H

#include "Entity.h"
#include "Animatable.h"
#include "ResourceContainer.h"

class Emerald : public Entity, protected Animatable
{
public:
	Emerald(sf::Vector2f position, ResourceContainer& resourceContainer);
	~Emerald() = default;

	void update(sf::Time dt) override;

private:
	// Inherited via Animatable
	void loadAnimations() override;
	void updateAnimation(sf::Time dt) override;

	b2World& mWorld;
};


#endif // !EMERALD_H




