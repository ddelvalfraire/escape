#ifndef PLAYER_H
#define PLAYER_H

#include "Emerald.h"
#include "ResourceContainer.h"
#include "Animatable.h"
#include "Entity.h"

class Player : public Entity, protected Animatable
{
public:
	Player(sf::Vector2f position, ResourceContainer& resourceContainer);
	Player(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld);

	~Player() = default;

	void disableKeyInputs();
	void handleKeyInputs();
	void collectEmerald();
	void updateChestCount();
	void update(sf::Time dt);

	int chestsOpened();
	int emeraldsCollected();

	bool isInteracting();
	void isInteracting(bool flag);
	void onInteract(Emerald* interactable);
	sf::Vector2f getPosition();

private:
	void loadAnimations() override;

	b2World* mWorld;
	bool mIsJumping;
	bool mIsInteracting;
	bool mKeyInputEnabled;
	int mEmeraldCount;
	int mChestCount;
};
#endif // !PLAYER_H
