#include "game_object.h"
#include <SFML/Graphics.hpp>

// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Game_Object::Game_Object(double x, double y)
    : xpos {x}, ypos {y}
{
}

// Medlemsfunktioner
/*_____________________________________________________*/
double Game_Object::get_xpos() const
{
    return xpos;
}

double Game_Object::get_ypos() const
{
    return ypos;
}

// ..
