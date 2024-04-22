#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "ResourceContainer.h"

struct AnimationData
{
	std::string textureKey;
	std::vector<sf::IntRect> frames;
	std::string name;
	int frameCount;
	float frameRate;
};


class Player : public Entity
{
public:
	Player(sf::Vector2f position, ResourceContainer& resourceContainer);
	Player(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld);

	~Player();

	void handleKeyInputs();
	void update(sf::Time dt);
	AnimationData& currentAnimation();
	void setAnimation(const std::string& name);

	bool isInteracting();
	void isInteracting(bool flag);

private:
	void updateAnimation(sf::Time dt);
	void initAnimationData();
	void loadAnimation(const std::string& name, int frameCount, float frameRate);

	float mAccumulator;
	AnimationData* mCurrentAnimation;
	b2World* mWorld;
	int currentFrame;
	std::unordered_map<std::string, AnimationData> mAnimations;
	TextureManager& mTextureManager;
	bool mIsJumping;
	bool mIsInteracting;
};
#endif // !PLAYER_H
