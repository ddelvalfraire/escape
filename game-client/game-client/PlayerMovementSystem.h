#ifndef PLAYER_MOVEMENT_SYSTEM_H
#define PLAYER_MOVEMENT_SYSTEM_H

#include <Thor/Input.hpp>
#include <SFML/Graphics.hpp>

#include "System.h"
#include "Entity.h"

constexpr float MOVE_SPEED = 100.0f;
constexpr float JUMP_VELOCITY = -550.f;
constexpr float GRAVITY = 0.25f;

class PlayerMovementSystem : protected System
{
public:
	PlayerMovementSystem(sf::RenderWindow& window, Entity& player);
	void _update(float dt) override;
	void _update(sf::Event event, float dt);

private:
	void initKeybindings();
	void handleActions();
	void updatePlayerPosition(float dt);

	thor::ActionMap<const char*> mActions;
	sf::RenderWindow& mWindow;
	Entity& mPlayer;
};


#endif // !PLAYER_MOVEMENT_SYSTEM_H
