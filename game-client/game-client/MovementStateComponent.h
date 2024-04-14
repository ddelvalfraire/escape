#ifndef MOVEMENT_STATE_H
#define MOVEMENT_SATE_H

#include "Component.h"

/**
 * @brief Represents the various states of movement in an entity
 * 
 */
struct MovementStateComponent : Component
{
	MovementStateComponent(bool isFalling = false, bool isJumping = false, bool isCrouched = false)
		:isFalling(isFalling), isJumping(isJumping), isCrouched(isCrouched) {}

	bool isFalling;
	bool isJumping;
	bool isCrouched;
};

#endif // !MOVEMENT_STATE_H
