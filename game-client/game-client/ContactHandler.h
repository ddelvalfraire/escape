#ifndef CONTACT_HANDLER_H
#define CONTACT_HANDLER_H

#include <box2d/box2d.h>
#include <algorithm>

#include "Emerald.h"
#include "Player.h"
#include "Chest.h"

template<typename T, typename U>
struct EntityPair
{
	T* x;
	U* y;

	explicit operator bool() const
	{
		return x != nullptr && y != nullptr;
	}
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
			if (auto pair = isBoth<Player, Emerald>(a, b))
				playerCollectEmerald(pair);
			else if (auto pair = isBoth<Player, Chest>(a, b))
				mInteractables.push_back(pair.y);
		}
	}

	inline void EndContact(b2Contact* contact) override
	{
		auto a = reinterpret_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		auto b = reinterpret_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (a && b)
		{
			 if (auto pair = isBoth<Player, Chest>(a, b))
				 mInteractables.erase(std::remove(mInteractables.begin(), mInteractables.end(), pair.y), mInteractables.end());
		}
	}

	inline void handleInteractions(Player* player)
	{
		if (!player->isInteracting())
			return;

		for (auto& entity : mInteractables)
		{
			if (Chest* chest = dynamic_cast<Chest*>(entity))
			{
				if (!chest->isOn()) 
				{
					chest->setOn(true);
					player->updateChestCount();
				}
				
			}
				
		}

		player->isInteracting(false);
	}

	inline void removeDeletedBodies()
	{
		for (auto& entity : mDeleteList)
		{
			mWorld.DestroyBody(entity->physicsBody());
			mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), entity), mEntities.end());
			delete entity;
		}

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

	inline void playerCollectEmerald(EntityPair<Player, Emerald>& pair) 
	{
		Player* player = pair.x;
		Emerald* emerald = pair.y;

		mDeleteList.push_back(emerald);
		player->collectEmerald();
	}



	b2World& mWorld;
	std::vector<Entity*>& mEntities;
	std::vector<Entity*> mInteractables;
	std::vector<Entity*> mDeleteList;
};

#endif // !CONTACT_HANDLER_H
