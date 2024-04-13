// game-client.cpp : Defines the entry point for the application.
//
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

int main(int, char* [])
{
    // testing a new commit and push from new device
    b2BodyDef b;
    auto&& window = sf::RenderWindow({ 1280, 720 }, "CMake Example");
    auto&& circle = sf::CircleShape(50.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(640.f, 360.f);
    circle.setOrigin(50.f, 50.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}