#include <SFML/Graphics.hpp>
#include <string>

#include "game_object.h"
#include "modifier.h"
#include "static_obstacle.h"
#include "context.h"
#include "player.h"
#include "snowball_projectile.h"
#include <iostream>
#include <iomanip>

// Static_Obstacle
///////////////////////////////
Static_Obstacle::Static_Obstacle(double xpos, double ypos, float scale, std::string filename)
    :Modifier(xpos, ypos, scale, filename)
{}

// Tire
///////////////////////////////

Tire::Tire(double xpos, double ypos, float scale, std::string filename)
    :Static_Obstacle(xpos, ypos, scale, filename)
{   
    sf::Vector2u texture_size { texture.getSize() };
    double scale {radius/(texture_size.x/2)};
    sprite.setScale(scale, scale);
}

bool Tire::handle(sf::Event event, Context& context)
{
    return false;
}

void Tire::update(sf::Time delta, Context& context) 
{
    
    float distance {delta.asSeconds() * context.y_speed};
    sf::Vector2f old_position {sprite.getPosition()};
    
    sprite.move({0, -distance});
}

void Tire::perform_collision(Game_Object* const& other, Context& context)
{
    Player* player = dynamic_cast<Player*>(other);
    if (player)
    {
        context.y_speed = 0;
        context.is_colliding = true;
        context.coll_count += 1;
        player = nullptr;
    }
    Snowball_Projectile* snowball = dynamic_cast<Snowball_Projectile*>(other);
    if (snowball)
    {
  //      delete snowball;
        snowball = nullptr;
        //Oklar implementering, behövs den ens?
    }
}

// Hole
///////////////////////////////

Hole::Hole(double xpos, double ypos, float scale, std::string filename)
    :Static_Obstacle(xpos, ypos, scale, filename)
{}

bool Hole::handle(sf::Event event, Context& context)
{
    return false;
}


void Hole::update(sf::Time delta, Context& context) 
{
    
    float distance {delta.asSeconds() * context.y_speed};
    sf::Vector2f old_position {sprite.getPosition()};
    
    sprite.move({0, -distance});
}

void Hole::perform_collision(Game_Object* const& other, Context& context)
{
    Player* player = dynamic_cast<Player*>(other);
    if (player)
    {
        context.y_speed = 0;
        context.is_colliding = true;
        context.coll_count += 1;
        player = nullptr;
    }
    Snowball_Projectile* snowball = dynamic_cast<Snowball_Projectile*>(other);
    if (snowball)
    {
  //      delete snowball;
        snowball = nullptr;
        //Oklar implementering, behövs den ens?
    }
}

// Goal
///////////////////////////////

Goal::Goal(double xpos, double ypos, float scale, std::string filename)
    :Static_Obstacle(xpos, ypos, scale, filename)
{}

bool Goal::handle(sf::Event event, Context& context)
{
    return false;
}


void Goal::update(sf::Time delta, Context& context) 
{
    
    float distance {delta.asSeconds() * context.y_speed};
    sf::Vector2f old_position {sprite.getPosition()};
    
    sprite.move({0, -distance});
}

void Goal::perform_collision(Game_Object* const& other, Context& context)
{
    Player* player = dynamic_cast<Player*>(other);
    if (player)
    {
        context.y_speed = 0;
        context.game_finished = true;
        context.goal_time = context.clock.getElapsedTime();



        player = nullptr;
    }
}

