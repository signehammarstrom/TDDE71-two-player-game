#include "game_object.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "context.h"
#include "snowball_projectile.h"
#include "static_obstacle.h"



// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Player::Player(double x, double y, std::string filename )
    : Game_Object(x,y, filename)
{
    sprite.setScale(0.05f, 0.05f);
}

// Medlemsfunktioner

bool Player::handle(sf::Event event, Context& context)
{
    sf::Vector2f curr_position {sprite.getPosition()};
    if (context.snow_count > 0)
    {
        context.snowball_lst.push_back(new Snowball_Projectile(curr_position.x, curr_position.y));
        context.snow_count = context.snow_count - 1;
    }
}
void Player::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Player::update(sf::Time delta, Context& context)
{
    old_position = sprite.getPosition();

    float distance {delta.asSeconds() * 200.0f};
    sf::Vector2f old_position {sprite.getPosition()};

    if (context.side)
    {
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            sprite.move({-distance, 0});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            sprite.move({distance, 0});
        }
    }
    else
    {
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            sprite.move({-distance, 0});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            sprite.move({distance, 0});
        }
    }

    if (out_of_bounds(context))
    {
        sprite.setPosition(old_position);
    }
}


void Player::throw_snowball()
{}

void Player::perform_collision(Game_Object* const& other, Context& context)
{
    Static_Obstacle* stat_obst = dynamic_cast<Static_Obstacle*>(other);
    if (stat_obst)
    {
        if(fabs(sprite.getPosition().y + sprite.getGlobalBounds().height/2 - other->get_top_position()) > 0.5 )
        {
            sf::Vector2f temp {old_position.x, sprite.getPosition().y};
            sprite.setPosition(temp);
        }

    }
    stat_obst = nullptr;

}


bool Player::out_of_bounds(Context const& context)
{
    sf::FloatRect bounds {sprite.getGlobalBounds()};

    if (bounds.left < context.left_bound)
    {
        return true;
    }
    else if (bounds.left + bounds.width > context.right_bound)
    {
        return true;
    }
    else
    {
        return false;
    }
}


sf::FloatRect Player::bounds() const
{
    return sprite.getGlobalBounds();
}


/*_____________________________________________________*/

//dessa funktioner skapades
//för att testa konstruktorn. Låter dem vara kvar här vid behov!

double Player::get_width() const
{
    return width;
}

double Player::get_height() const 
{
    return height;
}
// ...
