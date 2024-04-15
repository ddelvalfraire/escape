#ifndef ITEM_H
#define ITEM_H

#include <string>


class Item // TODO needs a sprite to display on screen
{
public:
	Item(std::string& name, int quantity) : name(name), quantity(quantity) {}
	std::string name;
	int quantity;
};


struct Lever : Item
{
	Lever(int stp, std::string& name, int quantity) :strengthToPull(stp), Item(name, quantity) {}
	int strengthToPull;
};

struct Key : Item
{
	Key(int doorId, std::string& name, int quantity) : doorId(doorId), Item(name, quantity) {}
	int doorId;
};

struct MagicBanana : Item
{
	MagicBanana(std::string& name, int quantity) : Item(name, quantity) {}
};

#endif // !ITEM_H
