#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <iomanip>
#include "game_object.h"
#include "modifier.h"
#include "static_obstacle.h"
#include "context.h"
#include "player.h"
#include "snowball_projectile.h"

using namespace std;

//Static_Obstacle
/*_____________________________________________________________________*/
Static_Obstacle::Static_Obstacle(double xpos, double ypos, float size, sf::Vector2u& window_size, string& filename)
    :Modifier(xpos, ypos, size, window_size, filename)
{}

void Static_Obstacle::update(sf::Time delta, Context& context) 
{   
    float distance {delta.asSeconds() * context.y_speed};
    sf::Vector2f old_position {sprite.getPosition()};
    
    sprite.move({0, -distance});
}


//Goal
/*____________________________________________________________________*/
Goal::Goal(double xpos, double ypos, float size, sf::Vector2u& window_size, string filename)
    :Static_Obstacle(xpos, ypos, size, window_size, filename)
{
}

void Goal::perform_collision(Game_Object* const& other, Context& context)
{
    Player* player = dynamic_cast<Player*>(other);
    if (player)
    {
        context.y_speed = 0;
        context.game_finished = true;
        context.goal_time = context.clock.getElapsedTime();
    }
    player = nullptr;
}


//Actual_Obstacle
/*____________________________________________________________________*/
Actual_Obstacle::Actual_Obstacle(double xpos, double ypos, float size, sf::Vector2u& window_size, string& filename)
    :Static_Obstacle(xpos, ypos, size, window_size, filename)
{
}

void Actual_Obstacle::perform_collision(Game_Object* const& other, Context& context)
{
    Player* player = dynamic_cast<Player*>(other);
    if (player)
    {
        if (context.y_speed != 0)
        {
            context.prev_speed = context.y_speed;
        }
        sf::FloatRect bounds = sprite.getGlobalBounds();
        sf::FloatRect other_bounds = other->bounds();
        if (other_bounds.top + other_bounds.height <= bounds.top + 5)
        {
            context.y_speed = 0;
            context.is_colliding = true;
            context.coll_count += 1;
        }
    }
    player = nullptr;
}


//Tire
/*_____________________________________________________________________*/
Tire::Tire(double xpos, double ypos, float size, sf::Vector2u& window_size, string filename)
    :Actual_Obstacle(xpos, ypos, size, window_size, filename)
{
}


//Hole
/*____________________________________________________________________*/
Hole::Hole(double xpos, double ypos, float size, sf::Vector2u& window_size, string filename)
    :Actual_Obstacle(xpos, ypos, size, window_size, filename)
{
}


