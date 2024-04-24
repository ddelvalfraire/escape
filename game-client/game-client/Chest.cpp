#include "Chest.h"

const std::string FILE_PATH = "Entities/";
const std::string CHEST_OPEN = "chest_opened.png";
const std::string CHEST_CLOSE = "chest_closed.png";
sf::Vector2i CHEST_PIXEL_SIZE = { 32, 32 };

/**
 * @brief Construct a new Chest:: Chest object
 * 
 * @param position unscaled x, y coordinates to place the chest
 * @param resourceContainer Dependeny container reference
 */
Chest::Chest(sf::Vector2f position, ResourceContainer& resourceContainer)
	:Chest(position, resourceContainer.textureManager(), resourceContainer.world())
{
}

/**
 * @brief Construct a new Chest:: Chest object
 * 
 * @param position unscaled x, y coordinates to place the chest
 * @param textureManager TextureManager reference
 * @param physicsWorld World reference
 */
Chest::Chest(sf::Vector2f position, TextureManager& textureManager, b2World& physicsWorld)
{

	if (textureManager.hasTexture(FILE_PATH + CHEST_OPEN))
		onTexture = textureManager.getTexture(FILE_PATH + CHEST_OPEN);
	else
		onTexture = textureManager.loadTexture(FILE_PATH + CHEST_OPEN);

	if (textureManager.hasTexture(FILE_PATH + CHEST_CLOSE))
		offTexture = textureManager.getTexture(FILE_PATH + CHEST_CLOSE);
	else
		offTexture = textureManager.loadTexture(FILE_PATH + CHEST_CLOSE);

	const auto CHEST_SCALAR = 3.0F;

	const int x = position.x, y = position.y;
	sf::IntRect physicsRect({ x, y }, CHEST_PIXEL_SIZE);
	sf::IntRect frame({ 0, 0 }, CHEST_PIXEL_SIZE);

	mpPhysicsBody = initPhysicsBody(physicsRect, physicsWorld, b2_staticBody, CHEST_SCALAR, true);
	mpDrawable = initDrawable(frame, offTexture, position, false, CHEST_SCALAR);
}

/**
 * @brief Update the chest texture based on the state of the base Toggle class
 * 
 * @param dt elapsed time
 */
void Chest::update(sf::Time dt)
{
	auto sprite = static_cast<sf::Sprite*>(mpDrawable);
	if (isOn() == true)
		sprite->setTexture(*onTexture);
	else
		sprite->setTexture(*offTexture);

}
