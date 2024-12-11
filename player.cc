
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "game_object.h"
#include "player.h"
#include "context.h"
#include "snowball_projectile.h"
#include "static_obstacle.h"
#include "temporary_modifier.h"



// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Player::Player(double x, double y, float scale, std::string filename, std::string filename2 , std::string filename3 )
    : Game_Object(x,y, scale, filename), x_speed{200}
{
    if (!texture2.loadFromFile(filename2))
    {
        throw std::runtime_error{"Couldn't open filename"};
    }
    if (!texture3.loadFromFile(filename3))
    {
        throw std::runtime_error{"Couldn't open filename"};
    }
}

// Medlemsfunktioner

void Player::handle(sf::Event event, Context& context)
{
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down )
    {
        sf::Vector2f curr_position {sprite.getPosition()};
        if (context.snow_count > 0)
        {
            context.snowball_lst.push_back(new Snowball_Projectile(curr_position.x, curr_position.y, 80));
            context.snow_count = context.snow_count - 1;
        }
    }
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

void Player::perform_collision(Game_Object* const& other, [[maybe_unused]]Context& context)
{
    Static_Obstacle* stat_obst = dynamic_cast<Static_Obstacle*>(other);
    if (stat_obst)
    {
        sf::FloatRect pbounds = bounds();
        sf::FloatRect other_bounds = other->bounds();

        float overlap_X = std::min(pbounds.left + pbounds.width, other_bounds.left + other_bounds.width) 
            - std::max(pbounds.left, other_bounds.left);
        float overlap_Y = std::min(pbounds.top + pbounds.height, other_bounds.top + other_bounds.height) 
            - std::max(pbounds.top, other_bounds.top);
        
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

bool Player::out_of_bounds(Context const& context)
{
    sf::FloatRect playerBounds {bounds()};
    
    if ((playerBounds.left  - context.side_tire_size < context.left_bound)|| 
        (playerBounds.left + playerBounds.width + context.side_tire_size > context.right_bound))
    {
        return true;
    }
    return false;
}

void Player::stop_effect(Game_Object*& object, Context const& context)
{
    Temporary_Modifier* temp_mod = dynamic_cast<Temporary_Modifier*>(object);
    if (temp_mod)
    {
        x_speed = x_speed/temp_mod->get_speedmodifier();
        if(context.active_temp_mods.size() <= 1)
        {
            sprite.setTexture(texture);
        }
    }
    temp_mod = nullptr;
}