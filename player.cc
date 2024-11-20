#include "game_object.h"
#include "player.h"


// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Player::Player(double x, double y, double height, 
    double width)
    : Game_Object(x,y), height{height}, width{width}
{
}

double Player::get_xpos() const
{
    return xpos;
}

double Player::get_ypos() const
{
    return ypos;
}

double Player::get_width() const
{
    return width;
}

double Player::get_height() const 
{
    return height;
}
// Medlemsfunktioner
/*_____________________________________________________*/

// ...
