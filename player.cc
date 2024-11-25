#include "game_object.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>



// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Player::Player(double x, double y, double height, 
    double width, double left_bound, double right_bound, bool side)
    : Game_Object(x,y), height{height}, width{width}, side{side},
        left_bound{left_bound}, right_bound{right_bound}
{
    texture.loadFromFile("skier.png");
    if (!texture.loadFromFile("skier.png"))
    {
        std::cerr << "Kan inte öppna: fighter.png" << std::endl;
    }

    sf::Vector2u window_size {1136, 640};

    sprite.setTexture(texture);
    sf::Vector2u texture_size { texture.getSize() };
    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    sprite.setPosition((right_bound + left_bound) / 2, window_size.y / 6);
    sprite.setScale(0.1f, 0.1f);
}

// Medlemsfunktioner

bool Player::handle(sf::Event event)
{


}

void Player::update(sf::Time delta)
{

    float distance {delta.asSeconds() * 200.0f};
    sf::Vector2f old_position {sprite.getPosition()};

    if (side)
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

    if (out_of_bounds())
    {
        sprite.setPosition(old_position);
    }
}



void Player::render(sf::RenderWindow& window)
{
    window.draw(sprite);

}

void Player::throw_snowball()
{}

void Player::perform_collision(Game_Object const&)
{}

bool Player::collides(Game_Object const&) const
{}


bool Player::out_of_bounds()
{
    sf::FloatRect bounds {sprite.getGlobalBounds()};

    if (bounds.left < left_bound)
    {
        return true;
    }
    else if (bounds.left + bounds.width > right_bound)
    {
        return true;
    }
    else
    {
        return false;
    }
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
