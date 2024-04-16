#include <SFML/System.hpp>

#include "EntityFactory.h"

const sf::Vector2f PLAYER_SPAWN_VEC2 = { 0.0f, 0.0f };
const sf::Vector2f DEFAULT_VELOCITY = { 0.0f, 0.0f };

/**
 * @brief Retrieves the singleton
 * 
 * @return EntityFactory& EntityFactory singleton
 */
EntityFactory& EntityFactory::getInstance()
{
    static EntityFactory entityFactory;
    
    return entityFactory;
}

/**
 * @brief Creates a player entity composed of the 
 * PositionComponent, VelocityComponent, and MovementStateComponent
 * 
 * @return Entity* player entity
 */
Entity* EntityFactory::createPlayer()
{
    auto player = new Entity();

    player->addComponent<PositionComponent>(PLAYER_SPAWN_VEC2);
    player->addComponent<VelocityComponent>(DEFAULT_VELOCITY);
    player->addComponent<MovementStateComponent>();

    return player;
}

Entity* EntityFactory::createLever(sf::Vector2f &leverSpawn)
{
    auto lever = new Entity();

    lever->addComponent<LeverStateComponent>(false); // false is off
    lever->addComponent<PositionComponent>(leverSpawn); // TODO: decide where levers go in levels

    return lever;
}
