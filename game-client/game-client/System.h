#ifndef SYSTEM_H
#define SYSTEM_H

/**
 * @brief abstract base class for system controllers
 * 
 */
class System 
{
public:
	virtual void _update(float dt) = 0;
};
#endif // !SYSTEM_H
