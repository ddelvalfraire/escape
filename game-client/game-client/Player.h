#ifndef PLAYER_H
#define PLAYER_H

#include "Emerald.h"
#include "ResourceContainer.h"
#include "Animatable.h"
#include "Entity.h"

#include "Entity.h"
#include "TextureManager.h"

struct AnimationData
{
	sf::Texture& texture;
	std::vector<sf::IntRect> frames;
	std::string name;
	int frameCount;
	float frameRate;
};


class Player : public Entity
{
public:
	Player(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld);
	
	void handleKeyInputs();
	void collectEmerald();
	void update(sf::Time dt);
	AnimationData& currentAnimation();
	void setAnimation(const std::string& name);

	bool isInteracting();
	void isInteracting(bool flag);
	void onInteract(Emerald* interactable);
	sf::Vector2f getPosition();

private:
	void loadAnimations() override;

	float mAccumulator;
	AnimationData* mCurrentAnimation;
	int currentFrame;
	std::unordered_map<std::string, AnimationData> mAnimations;
	TextureManager& mTextureManager;
	bool mIsJumping;
	bool mIsInteracting;
	int mEmeraldCount;
};
#endif // !PLAYER_H
