#include "ResourceContainer.h"

const b2Vec2 GRAVITY_RATE(0.0f, 15.0f);

/**
 * @brief Construct a new Resource Container:: Resource Container object
 * 
 * @param window main window reference 
 */
ResourceContainer::ResourceContainer(sf::RenderWindow& window)  
    : mWindow(window), mWorld(GRAVITY_RATE), mTextureManager()
{
}

/**
 * @brief getter for the main window
 * 
 * @return sf::RenderWindow& main window reference
 */
sf::RenderWindow& ResourceContainer::window()
{
    return mWindow;
}

/**
 * @brief getter for the texture manager
 * 
 * @return TextureManager& texture manager reference
 */
TextureManager& ResourceContainer::textureManager()
{
    return mTextureManager;
}

/**
 * @brief physics world reference getter
 * 
 * @return b2World& physics world reference
 */
b2World& ResourceContainer::world()
{
    return mWorld;
}
