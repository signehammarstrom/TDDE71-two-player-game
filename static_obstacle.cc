#include "static_obstacle.h"
#include "context.h"
#include <SFML/Graphics.hpp>


Static_Obstacle::Static_Obstacle(double xpos, double ypos)
    :Modifier(xpos, ypos)
{}

bool Static_Obstacle::handle(sf::Event event, Context& context)
{}

bool Static_Obstacle::collides(Game_Object const&) const
{}


Tire::Tire(double xpos, double ypos, double radius)
    :Static_Obstacle(xpos, ypos), radius{radius}
{
    if (!texture.loadFromFile("tire.png"))
    {
        throw std::runtime_error{"Couldn't open 'tire.png'"};
    }
    sprite.setTexture(texture);

    sf::Vector2u texture_size { texture.getSize() };
    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    
    sprite.setPosition(xpos, ypos);
    double scale {radius/(texture_size.x/2)};
    sprite.setScale(scale, scale);
}

void Tire::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Tire::update(sf::Time delta, Context& context) 
{
    
    float distance {delta.asSeconds() * context.y_speed};
    sf::Vector2f old_position {sprite.getPosition()};
    
    sprite.move({0, -distance});

}

Hole::Hole(double xpos, double ypos, double radius)
    :Static_Obstacle(xpos, ypos), radius{radius}
{
    if (!texture.loadFromFile("hole.png"))
    {
        throw std::runtime_error{"Couldn't open 'hole.png'"};
    }
    sprite.setTexture(texture);

    sf::Vector2u texture_size { texture.getSize() };
    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    
    sprite.setPosition(xpos, ypos);
    double scale {radius/(texture_size.x/2)};
    sprite.setScale(scale, scale);
}

void Hole::update(sf::Time delta, Context& context) 
{
    
    float distance {delta.asSeconds() * context.y_speed};
    sf::Vector2f old_position {sprite.getPosition()};
    
    sprite.move({0, -distance});

}

void Hole::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

Goal::Goal(double xpos, double ypos, double width, double height)
    :Static_Obstacle(xpos, ypos), width{width}, height{height}
{}



