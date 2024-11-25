#include "game_object.h"
#include "player.h"


// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Player::Player(double x, double y, double height, 
    double width)
    : Game_Object(x,y), height{height}, width{width}
{
}

// Medlemsfunktioner

bool Player::handle(sf::Event event)
{}

void Player::update(sf::Time delta)
{}

void Player::render(sf::RenderWindow& window)
{}

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
