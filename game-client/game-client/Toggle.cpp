#include "Toggle.h"

/**
 * @brief Construct a new Toggle:: Toggle object
 * 
 */
Toggle::Toggle() :mIsOn(false)
{
}

/**
 * @brief Destroy the Toggle:: Toggle object
 * 
 */
Toggle::~Toggle()
{
}

/**
 * @brief mIsOn setter
 * 
 * @param flag state of the toggle
 */
void Toggle::setOn(bool flag)
{
	mIsOn = flag;
}

/**
 * @brief mIsOn getter
 * 
 */
bool Toggle::isOn()
{
	return mIsOn;
}
