#ifndef CONTACT_HANDLER_H
#define CONTACT_HANDLER_H

#include <box2d/box2d.h>
#include <algorithm>

#include "Emerald.h"
#include "Player.h"

template<typename T, typename U>
struct EntityPair
{
	T* x;
	U* y;
};

class ContactHandler : public b2ContactListener
{
public:
	ContactHandler(std::vector<Entity*>& entities, b2World& world) 
		: mEntities(entities), mWorld(world) {}

	inline void BeginContact(b2Contact* contact) override
	{
		auto a = reinterpret_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		auto b = reinterpret_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (a && b)
		{
			auto pair = isBoth<Player, Emerald>(a, b);

			if (pair.x != nullptr && pair.y != nullptr)
				playerCollectEmerald(pair.x, pair.y);
		}
	}
	inline void removeDeletedBodies()
	{
		for (auto body : mDeleteList)
			mWorld.DestroyBody(body);

		mDeleteList.clear();
	}

private:
	template<typename T, typename U>
	EntityPair<T, U> isBoth(Entity* a, Entity* b)
	{
		auto A = dynamic_cast<T*>(a);
		auto B = dynamic_cast<U*>(b);

		if (A && B)
			return { A, B };

		A = dynamic_cast<T*>(b);
		B = dynamic_cast<U*>(a);

		if (A && B)
			return { A, B };

		return { nullptr, nullptr };
	}

	inline void playerCollectEmerald(Player* player, Emerald* emerald) 
	{
		auto body = emerald->physicsBody();
		mDeleteList.push_back(body);
		player->collectEmerald();
		mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), emerald), mEntities.end());
		delete emerald;
	}

	b2World& mWorld;
	std::vector<Entity*>& mEntities;
	std::vector<b2Body*> mDeleteList;
};

#endif // !CONTACT_HANDLER_H
