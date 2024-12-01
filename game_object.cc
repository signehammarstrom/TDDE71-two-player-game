#include <SFML/Graphics.hpp>
#include <iostream>

#include "game_object.h"

// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Game_Object::Game_Object(double x, double y)
    : xpos {x}, ypos {y}
{
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

// ..
