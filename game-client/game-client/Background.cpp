#include "Background.h"

/**
 * @brief Construct a new Background:: Background object
 * 
 * @param window main window reference
 * @param textureManager texture manager reference
 */
Background::Background(sf::RenderWindow& window, TextureManager &textureManager) 
    :mWindow(window), mTextureManager(textureManager)
{
    loadBackgroundSprites();
}

/**
 * @brief Calculate the appropriate scalar for background sprites
 *        based on the windowsize and sprite
 * 
 * @param sprite background sprite reference
 * @return float calculated scalar
 */
float Background::getScalar(sf::Sprite& sprite)
{
    sf::Vector2f spriteSize = sprite.getLocalBounds().getSize();
    sf::Vector2u windowSize = mWindow.getSize();
    return std::min(windowSize.x / spriteSize.x, windowSize.y / spriteSize.y);

}
/**
 * @brief loads and stores the background sprites
 * 
 */
void Background::loadBackgroundSprites()
{
    std::vector<std::string> layerFileNames = 
    {
          "sky.png",
          "clouds_1.png",
          "rocks.png",
          "clouds_2.png",
          "ground_1.png",
          "ground_2.png",
          "ground_3.png",
          "plant.png",
    };

    for (auto& fileName : layerFileNames)
    {
        mTextureManager.loadTexture(fileName);
        sf::Texture* tex = mTextureManager.getTexture(fileName);

        mSprites.emplace_back(new sf::Sprite(*tex));
        sf::Sprite* sprite = mSprites.back();

        float scalar = getScalar(*sprite);
        sprite->setScale(scalar, scalar);

        if (fileName != "clouds_1.png" && fileName != "clouds_2.png")
            continue;

        mSprites.emplace_back(new sf::Sprite(*sprite));
        sf::Sprite* copy = mSprites.back();

        copy->setPosition(mWindow.getSize().x, 0);

        auto& list = fileName == "clouds_2.png" ? mForegroundSprites : mBackgroundSprites;

        list.push_back(copy);
        list.push_back(sprite);
        
    }

}

/**
 * @brief Animates a list of sprites by moving them across the screen
 * 
 * @param moveSpeed offset to apply to sprite posisitons
 * @param sprites sprites to move
 */
void Background::animateBackground(float moveSpeed, std::vector<sf::Sprite*> &sprites)
{
    for (auto sprite : sprites)
    {
        sprite->move(-moveSpeed, 0);

        const float currPos = sprite->getPosition().x + sprite->getGlobalBounds().width;
        
        if (currPos < 0)
        {
            sf::Vector2f newPos(mWindow.getSize().x, sprite->getPosition().y);
            sprite->setPosition(newPos);
        }

    }
}

/**
 * @brief updates the background animation by a preset frequency
 * 
 * @param dt delta time
 */
void Background::update(sf::Time dt)
{
    constexpr auto UPDATE_FREQ = 8.0f;
    constexpr auto MOVE_SPEED = 1.0f;

    mAccumulator += dt.asMilliseconds();
   
    if (mAccumulator >= UPDATE_FREQ)
    {
        animateBackground(2.0f * MOVE_SPEED, mBackgroundSprites);
        animateBackground(MOVE_SPEED, mForegroundSprites);
        mAccumulator = 0.0f;
    }


}

/**
 * @brief mSprites getter
 * 
 * @return std::vector<sf::Sprite*>& reference to the sprite list
 */
std::vector<sf::Sprite*>& Background::getSprites()
{
    return mSprites;
}
