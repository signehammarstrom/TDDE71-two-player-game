#include <SFML/Graphics.hpp>

#include "game_object.h"

// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Game_Object::Game_Object(double x, double y)
    : xpos {x}, ypos {y}
{
}

// Medlemsfunktioner
/*_____________________________________________________*/


bool Game_Object::collides(Game_Object* const&) const
{
    // return bounds().intersects(object2->bounds());
    return false;
}

double Game_Object::get_xpos() const
{
    return xpos;
}

double Game_Object::get_ypos() const
{
    return ypos;
}

// ..
