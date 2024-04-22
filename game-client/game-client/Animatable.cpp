#include "Animatable.h"

Animatable::Animatable(TextureManager& textureManager)
	:mTextureManager(textureManager),
	mCurrentAnimation(nullptr),
	mAccumulator(0.0f),
	mCurrentFrame(0)
{}

Animatable::~Animatable()
{
	for (auto& data : mAnimations)
		mTextureManager.deleteTexture(data.second.textureKey);
}

/**
 * @brief Creates an AnimationData struct and adds it animations map
 *
 * @param name filename of the animation png
 * @param frameCount number of frames in png
 * @param frameRate frame display rate for accumulator
 */
void Animatable::loadAnimation(const std::string & name, int frameCount, float frameRate, sf::Vector2i size)
{
	std::vector<sf::IntRect> frames;
	for (int i = 0; i < frameCount; ++i)
	{
		sf::IntRect frame(size.x * i, 0, size.x, size.y);
		frames.push_back(frame);
	}
	mTextureManager.loadTexture(name);

	AnimationData animData = {
		name,
		frames,
		name,
		frameCount,
		frameRate,
	};

	mAnimations.emplace(name, animData);
}

/**
 * @brief Retrieves the current animation playing
 *
 * @return AnimationData& reference to the animation currently playing
 */
AnimationData& Animatable::currentAnimation()
{
	if (!mCurrentAnimation)
		throw std::runtime_error("Animatable does not have animation loaded");

	return *mCurrentAnimation;
}


/**
 * @brief Changes the current animation being played
 *
 * @param name filename of the animation to play
 */
void Animatable::setAnimation(const std::string& name)
{
	if (mAnimations.count(name) == 0)
		throw std::runtime_error("Animation does not exist on Animatable");


	mCurrentAnimation = &mAnimations.at(name);
}

