#include "ResourceContainer.h"

const b2Vec2 GRAVITY_RATE(0.0f, 25.0f);

ResourceContainer::ResourceContainer(sf::RenderWindow& window)  : mWindow(window), mWorld(GRAVITY_RATE), mTextureManager()
{
}

sf::RenderWindow& ResourceContainer::window()
{
    return mWindow;
}

TextureManager& ResourceContainer::textureManger()
{
    return mTextureManager;
}

b2World& ResourceContainer::world()
{
    return mWorld;
}
