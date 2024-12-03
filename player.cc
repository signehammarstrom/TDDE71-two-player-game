#include "game_object.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "context.h"
#include "snowball_projectile.h"
#include "static_obstacle.h"
#include "temporary_modifier.h"



// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Player::Player(double x, double y, float scale, std::string filename )
    : Game_Object(x,y, scale, filename), x_speed{200}
{
}

// Medlemsfunktioner

bool Player::handle(sf::Event event, Context& context)
{
    sf::Vector2f curr_position {sprite.getPosition()};
    if (context.snow_count > 0)
    {
        context.snowball_lst.push_back(new Snowball_Projectile(curr_position.x, curr_position.y, 80));
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

    float distance {delta.asSeconds() * x_speed};
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
        sf::FloatRect bounds = sprite.getGlobalBounds();
        sf::FloatRect other_bounds = other->bounds();

        float overlap_X = std::min(bounds.left + bounds.width, other_bounds.left + other_bounds.width) - std::max(bounds.left, other_bounds.left);
        float overlap_Y = std::min(bounds.top + bounds.height, other_bounds.top + other_bounds.height) - std::max(bounds.top, other_bounds.top);
        
        if (overlap_X < overlap_Y)
        {
            sf::Vector2f temp {};
            temp = {old_position.x, sprite.getPosition().y};
            if (old_position.x > sprite.getPosition().x)
            {
                temp = {old_position.x + sprite.getGlobalBounds().width*x_speed/10000, sprite.getPosition().y};
            }
            else if (old_position.x < sprite.getPosition().x)
            {
                temp = {old_position.x - sprite.getGlobalBounds().width*x_speed/10000, sprite.getPosition().y};
            }
            sprite.setPosition(temp);
        }
    }
        /*
        if(fabs(sprite.getPosition().y + sprite.getGlobalBounds().height/2 - other->get_position()) > sprite.getGlobalBounds().height/50 )
        {
            sf::Vector2f temp {};
            if (old_position.x > sprite.getPosition().x)
            {
                temp = {old_position.x + sprite.getGlobalBounds().width*x_speed/10000, sprite.getPosition().y};
            }
            else if (old_position.x < sprite.getPosition().x)
            {
                temp = {old_position.x - sprite.getGlobalBounds().width*x_speed/10000, sprite.getPosition().y};
            }
            else if (old_position.x == sprite.getPosition().x)
            {
                temp = {old_position.x, sprite.getPosition().y};
            }
            sprite.setPosition(temp);
        }*/


    Temporary_Modifier* temp_mod = dynamic_cast<Temporary_Modifier*>(other);
    if (temp_mod)
    {
        x_speed = temp_mod->get_speedmodifier()*x_speed;

    }
    stat_obst = nullptr;
    temp_mod = nullptr;


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

float Player::get_position() const
{
    return sprite.getPosition().y + sprite.getGlobalBounds().height/2;
}


void Player::stop_effect(Game_Object*& object)
{
    Temporary_Modifier* temp_mod = dynamic_cast<Temporary_Modifier*>(object);
    if (temp_mod)
    {
        x_speed = x_speed/temp_mod->get_speedmodifier();
    }
    temp_mod = nullptr;
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
