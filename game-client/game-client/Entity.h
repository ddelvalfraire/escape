#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <typeinfo>
#include <stdexcept>
#include <memory>
#include <utility>

#include "Component.h"

/**
 * @brief Entity container for the ECS
 * 
 */
class Entity 
{
public:
	/**
	 * @brief Construct a new Entity object
	 * 
	 */
	Entity() = default;

	/**
	 * @brief Destroy the Entity object
	 * 
	 */
	~Entity()
	{
		for (auto& it : mComponents)
		{
			delete it.second;
		}
	}

	/**
	 * @brief searches through components map for a particular component type
	 * 
	 * @tparam T Super of the Component class
	 * @return true when component T exists in the map
	 * @return false when component T does not exist in the map
	 */
	template<typename T>
	bool hasComponent() const 
	{
		return mComponents.find(&typeid(T)) != mComponents.end();
	}

	/**
	 * @brief Get the Component object
	 * 
	 * @tparam T Super of Component class
	 * @return T& reference to the 
	 */
	template<typename T>
	T& getComponent()
	{
		auto it = mComponents.find(&typeid(T));
		if (it != mComponents.end()) 
		{
			return *static_cast<T*>(it->second);
		}
		else
		{
			throw std::runtime_error("Attempting to fetch a non existent component");
		}
	}


	/**
	 * @brief Creates a map entry containing an allocated reference to component T
	 * 
	 * @tparam T Super of Component class
	 * @tparam Args constructor args for the T class
	 * @param args constructor args for the T class
	 */
	template<typename T, typename... Args>
	void addComponent(Args&&... args) 
	{
		using namespace std;
		mComponents.emplace(&typeid(T), new T {std::forward<Args>(args)...});
	}

private:
	std::unordered_map<const std::type_info*, Component*> mComponents;
};

#endif // !ENTITY_H
