#include "Toggle.h"

Toggle::Toggle() :mIsOn(false)
{
}

Toggle::~Toggle()
{
}

void Toggle::setOn(bool flag)
{
	mIsOn = flag;
}

bool Toggle::isOn()
{
	return mIsOn;
}
