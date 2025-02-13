#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "game_object.h"
#include "player.h"
#include "context.h"
#include "snowball_projectile.h"
#include "static_obstacle.h"
#include "temporary_modifier.h"

using namespace std;

Player::Player(double x, double y, float size, float x_speed, sf::Vector2u& window_size, 
    string filename, string filename2 , string filename3 )
    : Game_Object(x,y, size, window_size, filename), x_speed{x_speed}, snowball_size{size/3}
{
    if (!texture2.loadFromFile(filename2))
    {
        throw runtime_error{"Couldn't open filename"};
    }
    if (!texture3.loadFromFile(filename3))
    {
        throw runtime_error{"Couldn't open filename"};
    }
    
}

void Player::update(sf::Time delta, Context& context)
{
    old_position = sprite.getPosition();
    float distance {delta.asSeconds() * x_speed};
    

    if (context.side)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            sprite.move({-distance, 0});
            sprite.setScale(scale, scale);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            sprite.move({distance, 0});
            sprite.setScale(-scale, scale);
        }
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            sprite.move({-distance, 0});
            sprite.setScale(scale, scale);
            
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            sprite.move({distance, 0});
            sprite.setScale(-scale, scale);
        }
    }

    if (out_of_bounds(context))
    {
        sprite.setPosition(old_position);
    }
}

void Player::perform_collision(Game_Object* const& other, Context& context)
{
    Static_Obstacle* stat_obst = dynamic_cast<Static_Obstacle*>(other);
    if (stat_obst)
    {
        Goal* goal = dynamic_cast<Goal*>(other);
        if(!goal)
        {
            if (context.stuck)
            {
                stat_obst->remove();
                context.stuck = false;
            }
            else
            {
                sf::FloatRect pbounds = bounds();
                sf::FloatRect other_bounds = other->bounds();

                float overlap_X = min(pbounds.left + pbounds.width, other_bounds.left + other_bounds.width) 
                    - max(pbounds.left, other_bounds.left);
                float overlap_Y = min(pbounds.top + pbounds.height, other_bounds.top + other_bounds.height) 
                    - max(pbounds.top, other_bounds.top);
                
                if (overlap_X < overlap_Y)
                {
                    if (overlap_Y > pbounds.height/10)
                    {
                    sf::Vector2f temp {};
                    temp = {old_position.x, sprite.getPosition().y};
                    if (old_position.x > sprite.getPosition().x)
                    {
                        temp = {old_position.x + pbounds.width*x_speed/10000, sprite.getPosition().y};
                    }
                    else if (old_position.x < sprite.getPosition().x)
                    {
                        temp = {old_position.x - pbounds.width*x_speed/10000, sprite.getPosition().y};
                    }
                    sprite.setPosition(temp);
                    }
            }
            }
        }
        goal = nullptr;
    }

    Temporary_Modifier* temp_mod = dynamic_cast<Temporary_Modifier*>(other);
    if (temp_mod)
    {
        x_speed = temp_mod->get_speedmodifier()*x_speed;
        Kir* kir = dynamic_cast<Kir*>(temp_mod);
        if (kir)
        {
            sprite.setTexture(texture3);
        }
        else
        {
            sprite.setTexture(texture2);
        }
        kir = nullptr;
    }
    stat_obst = nullptr;
    temp_mod = nullptr;
}

void Player::handle(sf::Event event, Context& context)
{
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down )
    {
        sf::Vector2f curr_position {sprite.getPosition()};
        if (context.snow_count > 0)
        {
            context.snowball_lst.push_back(new Snowball_Projectile(curr_position.x, 
                curr_position.y, snowball_size, context.window_size));
            context.snow_count = context.snow_count - 1;
        }
    }
}

bool Player::out_of_bounds(Context const& context)
{
    sf::FloatRect playerBounds {bounds()};
    if (context.side)
    {
        return ((playerBounds.left  < context.left_bound)|| 
            (playerBounds.left + playerBounds.width + context.side_tire_size > context.right_bound));
    }
    else
    {
        return ((playerBounds.left  - context.side_tire_size < context.left_bound)|| 
            (playerBounds.left + playerBounds.width > context.right_bound));
    }
}

void Player::stop_effect(Game_Object*& object, Context const& context)
{
    Temporary_Modifier* temp_mod = dynamic_cast<Temporary_Modifier*>(object);
    if (temp_mod)
    {
        x_speed = x_speed/temp_mod->get_speedmodifier();
        if (context.active_temp_mods.size() <= 1)
        {
            sprite.setTexture(texture);
        }
    }
    temp_mod = nullptr;
}