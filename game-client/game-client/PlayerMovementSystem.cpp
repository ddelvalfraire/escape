#include "PlayerMovementSystem.h"

constexpr auto WALK_BACKWARD = "w_backwards";
constexpr auto WALK_FORWARD = "w_forward";
constexpr auto CROUCH = "crouch";
constexpr auto JUMP = "jump";


/**
 * @brief Construct a new Player Movement System:: Player Movement System object
 * 
 * @param window reference to the main window
 * @param player handle to the local player object
 */
PlayerMovementSystem::PlayerMovementSystem(sf::RenderWindow& window, Entity& player)
	: mWindow(window), mPlayer(player)
{
	initKeybindings();
}

/**
 * @brief Checks window for inputs and handles their effects by updating the players position
 * 
 * @param dt delta time
 */
void PlayerMovementSystem::update(float dt)
{

	mActions.update(mWindow);
	handleActions();
	updatePlayerPosition(dt);
}

/**
 * @brief strictly for testing
 * @param event test event type to verify actions
 * @param dt delta time
 */
void PlayerMovementSystem::_update(sf::Event event,float dt)
{
	mActions.pushEvent(event);
	handleActions();
	updatePlayerPosition(dt);
}

/**
 * @brief Initializes the keybindings for the game
 * 
 */
void PlayerMovementSystem::initKeybindings()
{
	using thor::Action; using sf::Keyboard;

	Action w(Keyboard::W, Action::PressOnce);
	Action space(Keyboard::Space, Action::PressOnce);
	Action d(Keyboard::D, Action::Hold);
	Action a(Keyboard::A, Action::Hold);
	Action s(Keyboard::S, Action::Hold);
	Action dd(Keyboard::D, Action::PressOnce);
	Action aa(Keyboard::A, Action::PressOnce);
	Action ss(Keyboard::S, Action::PressOnce);

	mActions[WALK_BACKWARD] = a || aa;
	mActions[WALK_FORWARD] = d || dd;
	mActions[CROUCH] = s || ss;
	mActions[JUMP] = w || space;
}

/**
 * @brief updates the players velocity based on input actions (e.g walking, jumping )
 * 
 */
void PlayerMovementSystem::handleActions()
{
	PositionComponent& position = mPlayer.getComponent<PositionComponent>();
	VelocityComponent& velocity = mPlayer.getComponent<VelocityComponent>();
	MovementStateComponent& movState = mPlayer.getComponent<MovementStateComponent>();

	if (!movState.isJumping) 
	{
		if (mActions.isActive(WALK_BACKWARD))
		{
			velocity.x = -MOVE_SPEED;
		}
		else if (mActions.isActive(WALK_FORWARD))
		{
			velocity.x = MOVE_SPEED;
		}
		else
		{
			velocity.x = 0.0f;
		}
	}

	
	if (mActions.isActive(JUMP))
	{
		if (!movState.isJumping)
		{
			velocity.y += JUMP_VELOCITY;
			movState.isJumping = true;
			movState.isFalling = true;
		}
	}

	if (movState.isFalling) 
	{
		velocity.y += GRAVITY;

	}
	else
	{
		velocity.y = 0.0f;
		movState.isJumping = false;
	}
}

/**
 * @brief Uses delta time and velocity to update the players current position
 * 
 * @param dt 
 */
void PlayerMovementSystem::updatePlayerPosition(float dt)
{
	PositionComponent& position = mPlayer.getComponent<PositionComponent>();
	VelocityComponent& velocity = mPlayer.getComponent<VelocityComponent>();

	position += velocity * dt;
}
