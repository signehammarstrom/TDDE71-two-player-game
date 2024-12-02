#include <SFML/Graphics.hpp>
#include <iostream>

#include "game_object.h"

// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Game_Object::Game_Object(double x, double y, std::string filename)
    : xpos {x}, ypos {y}, texture{}, sprite{}
{

    texture.loadFromFile(filename);
    if (!texture.loadFromFile(filename))
    {
        throw std::runtime_error{"Couldn't open filename"};
    }

    sprite.setTexture(texture);
    sf::Vector2u texture_size { texture.getSize() };
    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    sprite.setPosition(xpos, ypos);
    
}

// Medlemsfunktioner
/*_____________________________________________________*/


bool Game_Object::collides(Game_Object* const& object) const
{
    return bounds().intersects(object->bounds());
    //return false;
}

bool Game_Object::is_removed() const
{
    return removed;
}

void Game_Object::remove()
{
    removed = true;
}

double Game_Object::get_xpos() const
{
    return xpos;
}

double Game_Object::get_ypos() const
{
    return ypos;
}

void Game_Object::update_time(sf::Time delta)
{}

void Game_Object::remove_if_inactual(Context& context)
{}

float Game_Object::get_top_position() const
{}
// ..
