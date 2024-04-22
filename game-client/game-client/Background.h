#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "TextureManager.h"

class Background {


public:
    Background(sf::RenderWindow& window, TextureManager& textureManager);
    ~Background() = default;

    void update(sf::Time dt);
    std::vector<sf::Sprite*>& getSprites();
private:
    void loadBackgroundSprites();
    void animateBackground(float moveSpeed, std::vector<sf::Sprite*>& sprites);
    float getScalar(sf::Sprite& sprite);

    float mAccumulator;
    std::vector<sf::Sprite*> mSprites;
    std::vector<sf::Sprite*> mBackgroundSprites;
    std::vector<sf::Sprite*> mForegroundSprites;
    TextureManager& mTextureManager;
    sf::RenderWindow& mWindow;
};

#endif // !BACKGROUND_H