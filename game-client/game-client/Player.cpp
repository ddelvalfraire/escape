#include <box2d/box2d.h>

#include "Player.h"

constexpr auto MOVE_SPEED = 3.0f;
constexpr auto JUMP_FORCE = 5.0f;
constexpr auto ACCELERATION = 0.5f;
constexpr auto DECELERATION = 0.5f;
constexpr auto LADDER_SPEED = 3.0f;
constexpr auto INTERACTION_RANGE = 50.0f;


constexpr auto SCALAR = 5.0F;
constexpr auto FALL = "Fall.png";
constexpr auto IDLE = "Idle.png";
constexpr auto RUN = "Run.png";
constexpr auto JUMP = "Jump.png";


/**
 * @brief Construct a new Player:: Player object
 * 
 * @param position world spawn coordinates
 * @param textureManager TextureManager reference
 * @param physicsWorld b2World reference
 */
Player::Player(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld)
	:Entity(),
	mTextureManager(textureManager),
	mCurrentAnimation(nullptr),
	mAccumulator(0.0f),
	currentFrame(0)
{
	initAnimationData();
	setAnimation(IDLE);

	sf::IntRect _ = mCurrentAnimation->frames[currentFrame]; 

	sf::FloatRect frame(sf::Vector2f(_.getPosition()), sf::Vector2f(_.getSize()));
	sf::Texture tex = mCurrentAnimation->texture;

	sf::FloatRect physicsRect(position, frame.getSize());

	mpPhysicsBody = initPhysicsBody(physicsRect, physicsWorld, b2_dynamicBody, SCALAR);
	mpSprite = initSprite(frame, true, &tex,sf::Color::Red, SCALAR);

}

/**
 * @brief Loads and creates animation data
 * 
 */
void Player::initAnimationData()
{
	loadAnimation(FALL, 1, 0.0f);
	loadAnimation(IDLE, 11, 50.0f);
	loadAnimation(RUN, 12, 50.0f);
	loadAnimation(JUMP, 1, 0);
}

/**
 * @brief Creates an AnimationData struct and adds it animations map
 * 
 * @param name filename of the animation png
 * @param frameCount number of frames in png
 * @param frameRate frame display rate for accumulator
 */
void Player::loadAnimation(const std::string& name, int frameCount, float frameRate)
{
	std::vector<sf::IntRect> frames;
	for (int i = 0; i < frameCount; ++i)
	{
		sf::IntRect frame(32 * i, 0, 32, 32);
		frames.push_back(frame);
	}
	mTextureManager.loadTexture(name);
	
	AnimationData animData = {
		*mTextureManager.getTexture(name),
		frames,
		name,
		frameCount,
		frameRate,
	};
	
	mAnimations.emplace(name, animData);
}

/**
 * @brief Updates the current animation based on game state
 * 
 * @param dt delta time
 */
void Player::updateAnimation(sf::Time dt)
{
	auto sprite = static_cast<sf::Sprite*>(mpSprite);
	b2Vec2 velocity = mpPhysicsBody->GetLinearVelocity();

	if (velocity.y > 0)
		setAnimation(FALL);
	else if (velocity.y < 0)
		setAnimation(JUMP);
	else if (velocity.x > 0)
		setAnimation(RUN);
	else if (velocity.x < 0)
		setAnimation(RUN);
	else
		setAnimation(IDLE);


	mAccumulator += dt.asMilliseconds();

	if (mAccumulator >= mCurrentAnimation->frameRate)
	{
		currentFrame = (currentFrame + 1) % mCurrentAnimation->frameCount;
		mAccumulator = 0.0f;
	}
	
	if (!sprite)
		throw std::runtime_error("Player does not have a sprite loaded");

	if (sprite->getTexture() != &mCurrentAnimation->texture) // do not update if texture is the same
		sprite->setTexture(mCurrentAnimation->texture);

	sf::IntRect frame = mCurrentAnimation->frames[currentFrame];

	sprite->setTextureRect(frame);

}

/**
 * @brief Handles keyboard inputs
 * 
 */
void Player::handleKeyInputs()
{
	if (!mpPhysicsBody)
		throw std::runtime_error("Physics body uninitialized");

	b2Vec2 velocity = mpPhysicsBody->GetLinearVelocity();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		velocity.x = b2Max(velocity.x - ACCELERATION, -MOVE_SPEED);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocity.x = b2Min(velocity.x + ACCELERATION, MOVE_SPEED);
	else
		velocity.x = velocity.x * DECELERATION;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mIsJumping) 
	{
		velocity.y = -JUMP_FORCE;
		mIsJumping = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !mIsInteracting)
		mIsInteracting = true;;

	mpPhysicsBody->SetLinearVelocity(velocity);
}

/**
 * @brief updates the player based on its current state and then syncs physics with display info
 * 
 * @param dt delta time
 */
void Player::update(sf::Time dt)
{
	if (mpPhysicsBody->GetLinearVelocity().y == 0.0f)
		mIsJumping = false;

	updateAnimation(dt);

	syncPositions();
}

/**
 * @brief Retrieves the current animation playing
 * 
 * @return AnimationData& reference to the animation currently playing
 */
AnimationData& Player::currentAnimation()
{
	if (!mCurrentAnimation)
		throw std::runtime_error("Player does not have animation loaded");

	return *mCurrentAnimation;
}

/**
 * @brief Changes the current animation being played
 * 
 * @param name filename of the animation to play
 */
void Player::setAnimation(const std::string& name)
{
	if (mAnimations.count(name) == 0)
		throw std::runtime_error("Animation does not exist in Player");
	

	mCurrentAnimation = &mAnimations.at(name);
}

/**
 * @brief mIsInteracting getter
 */
bool Player::isInteracting()
{
	return mIsInteracting;
}

/**
 * @brief mIsInteracting setter
 * 
 * @param flag new interacting state
 */
void Player::isInteracting(bool flag)
{
	mIsInteracting = flag;
}
