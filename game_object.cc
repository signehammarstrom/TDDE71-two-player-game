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


// bool Game_Object::collides(Game_Object const* object2) const
// {
//     return bounds().intersects(object2->bounds());
// }

double Game_Object::get_xpos() const
{
    return xpos;
}

double Game_Object::get_ypos() const
{
    return ypos;
}

// ..
