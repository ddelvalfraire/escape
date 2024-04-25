#include <box2d/box2d.h>

#include "Player.h"

constexpr auto MOVE_SPEED = 8.0f;
constexpr auto JUMP_FORCE = 10.0f;
constexpr auto ACCELERATION = 0.8f;
constexpr auto DECELERATION = 0.8f;
constexpr auto DEFAULT_FRAME_RATE = 0.07F;
constexpr auto PLAYER_SCALAR = 1.1F;

constexpr auto FALL = "Fall.png";
constexpr auto IDLE = "Idle.png";
constexpr auto RUN = "Run.png";
constexpr auto JUMP = "Jump.png";


Player::Player(sf::Vector2f position, ResourceContainer& resourceContainer)
	:Player(position, resourceContainer.textureManager(), resourceContainer.world())
{
}

/**
 * @brief Construct a new Player:: Player object
 * 
 * @param position world spawn coordinates
 * @param textureManager TextureManager reference
 * @param physicsWorld b2World reference
 */
Player::Player(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld)
	:Entity(),
	Animatable(textureManager),
	mEmeraldCount(0),
	mChestCount(0),
	mKeyInputEnabled(true)
{
	loadAnimations();
	setAnimation(IDLE);

	sf::IntRect& frame = mCurrentAnimation->frames[mCurrentFrame]; 
	sf::Texture* tex = mTextureManager.getTexture(mCurrentAnimation->textureKey);

	initEntityFromAnimation(frame, tex, position, physicsWorld, PLAYER_SCALAR);
}


void Player::disableKeyInputs()
{
	mKeyInputEnabled = false;
}

/**
 * @brief Loads and creates animation data
 * 
 */
void Player::loadAnimations()
{
	sf::Vector2i sizeInPixels(32, 32);

	loadAnimation(FALL, 1, 0.0f, sizeInPixels);
	loadAnimation(IDLE, 11, DEFAULT_FRAME_RATE, sizeInPixels);
	loadAnimation(RUN, 12, DEFAULT_FRAME_RATE, sizeInPixels);
	loadAnimation(JUMP, 1, 0.0F, sizeInPixels);
}

/**
 * @brief Handles keyboard inputs
 * 
 */
void Player::handleKeyInputs()
{
	if (!mpPhysicsBody)
		throw std::runtime_error("Physics body uninitialized");


	if (!mKeyInputEnabled)
		return;

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

void Player::collectEmerald()
{
	++mEmeraldCount;
}

void Player::updateChestCount()
{
	++mChestCount;
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

	updateAnimation(dt, mpDrawable);

	syncPositions();
}

int Player::chestsOpened()
{
	return mChestCount;
}

int Player::emeraldsCollected()
{
	return mEmeraldCount;
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

void Player::onInteract(Emerald* interactable)
{
}

sf::Vector2f Player::getPosition()
{
	const auto sprite = static_cast<sf::Sprite*>(mpDrawable);
	return sprite->getPosition();
}
