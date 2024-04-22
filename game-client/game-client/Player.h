#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "ResourceContainer.h"
#include "Animatable.h"

class Player : public Entity, protected Animatable
{
public:
	Player(sf::Vector2f position, ResourceContainer& resourceContainer);
	Player(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld);

	~Player();

	void handleKeyInputs();
	void update(sf::Time dt);

	bool isInteracting();
	void isInteracting(bool flag);

	sf::Vector2f getPosition();

private:
	void updateAnimation(sf::Time dt) override;
	void loadAnimations() override;

	b2World* mWorld;
	bool mIsJumping;
	bool mIsInteracting;
};
#endif // !PLAYER_H
