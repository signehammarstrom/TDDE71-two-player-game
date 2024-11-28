#include <SFML/Graphics.hpp>
#include <string>

#include "game_object.h"
#include "modifier.h"
#include "static_obstacle.h"
#include "context.h"

// Static_Obstacle
///////////////////////////////
Static_Obstacle::Static_Obstacle(double xpos, double ypos, std::string filename)
    :Modifier(xpos, ypos, filename)
{}

// Tire
///////////////////////////////

Tire::Tire(double xpos, double ypos, double radius, std::string filename)
    :Static_Obstacle(xpos, ypos, filename), radius{radius}
{   
    // double scale {radius/(texture_size.x/2)};
    // sprite.setScale(scale, scale);
}

bool Tire::handle(sf::Event event, Context& context)
{
    return false;
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

void Tire::perform_collision(Game_Object* const& other)
{
    return;
}

// Hole
///////////////////////////////

Hole::Hole(double xpos, double ypos, double radius, std::string filename)
    :Static_Obstacle(xpos, ypos, filename), radius{radius}
{}

bool Hole::handle(sf::Event event, Context& context)
{
    return false;
}

void Hole::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Hole::update(sf::Time delta, Context& context) 
{
    
    float distance {delta.asSeconds() * context.y_speed};
    sf::Vector2f old_position {sprite.getPosition()};
    
    sprite.move({0, -distance});
}

void Hole::perform_collision(Game_Object* const& other)
{
    return;
}

// Goal
///////////////////////////////

Goal::Goal(double xpos, double ypos, double width, double height, std::string filename)
    :Static_Obstacle(xpos, ypos, filename), width{width}, height{height}
{}

bool Goal::handle(sf::Event event, Context& context)
{
    return false;
}

void Goal::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Goal::update(sf::Time delta, Context& context) 
{
    
    float distance {delta.asSeconds() * context.y_speed};
    sf::Vector2f old_position {sprite.getPosition()};
    
    sprite.move({0, -distance});
}

void Goal::perform_collision(Game_Object* const& other)
{
    return;
}

