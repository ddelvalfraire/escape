#ifndef TYPE_MAP_H
#define TYPE_MAP_H

#include <unordered_map>
#include <typeinfo>
#include <stdexcept>
#include <memory>
#include <utility>

/**
 * @brief Entity container for the ECS
 *
 */
template<typename T>
class TypeMap
{
public:
	TypeMap() = default;

	/**
	 * @brief Destroy the Entity object
	 *
	 */
	~TypeMap()
	{
		for (auto& it : mMap)
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
	template<typename U>
	bool hasComponent() const
	{
		return mMap.find(&typeid(U)) != mMap.end();
	}

	/**
	 * @brief Get the Component object
	 *
	 * @tparam T Super of Component class
	 * @return T& reference to the
	 */
	template<typename U>
	U& getComponent()
	{
		auto it = mMap.find(&typeid(U));
		if (it != mMap.end())
		{
			return *static_cast<U*>(it->second);
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
	template<typename U, typename... Args>
	void addComponent(Args&&... args)
	{
		using namespace std;
		mMap.emplace(&typeid(U), new U{ std::forward<Args>(args)... });
	}

	template<typename U>
	void removeComponent()
	{
		auto it =  mMap.find(&typeid(U));
		if (it != mMap.end())
		{
			delete it->second;
			mMap.erase(it);
		}
	}

private:
	std::unordered_map<const std::type_info*, T*> mMap;
};

#endif // !TYPE_MAP_H
