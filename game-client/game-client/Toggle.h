#ifndef TOGGLE_H
#define TOGGLE_H

#include <SFML/Graphics.hpp>

class Toggle
{
public:
	Toggle();
	virtual ~Toggle();

	void setOn(bool flag);
	bool isOn();
protected:
	sf::Texture* onTexture;
	sf::Texture* offTexture;
	bool mIsOn;
};

#endif // !TOGGLE_H
