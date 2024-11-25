#include "game_object.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>



// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Player::Player(double x, double y, double height, 
    double width)
    : Game_Object(x,y), height{height}, width{width}
{
    texture.loadFromFile("fighter.png");
    if (!texture.loadFromFile("fighter.png"))
    {
        std::cerr << "Kan inte öppna: fighter.png" << std::endl;
    }

    sf::Vector2u window_size {1136, 640};

    sprite.setTexture(texture);
    sf::Vector2u texture_size { texture.getSize() };
    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    sprite.setPosition(window_size.x / 2, 3 * window_size.y / 4);


}

// Medlemsfunktioner

bool Player::handle(sf::Event event)
{


}

void Player::update(sf::Time delta)
{}

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
