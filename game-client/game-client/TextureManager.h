#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	sf::Texture* loadTexture(const std::string& fileName);
	sf::Texture* getTexture(const std::string& fileName);
	bool hasTexture(const std::string& fileName);
	void deleteTexture(const std::string& fileName);
private:
	std::unordered_map<std::string, sf::Texture*> mTextures;
};


#endif // !TEXTURE_MANAGER_H


