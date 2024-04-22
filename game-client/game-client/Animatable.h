#ifndef ANIMATABLE_H
#define ANIMATABLE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "TextureManager.h"

struct AnimationData
{
	std::string textureKey;
	std::vector<sf::IntRect> frames;
	std::string name;
	int frameCount;
	float frameRate;
};


class Animatable
{
protected:
	Animatable(TextureManager& textureManager);
	~Animatable();

	void loadAnimation(const std::string& name, int frameCount, float frameRate);
	void setAnimation(const std::string& name);
	AnimationData& currentAnimation();

	virtual void loadAnimations() = 0;
	virtual void updateAnimation(sf::Time dt) = 0;

	float mAccumulator;
	int currentFrame;
	AnimationData* mCurrentAnimation;
	std::unordered_map<std::string, AnimationData> mAnimations;
	TextureManager& mTextureManager;
};
#endif // !ANIMATABLE_H

