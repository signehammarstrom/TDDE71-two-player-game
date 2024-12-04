#include <SFML/Graphics.hpp>
#include <string>

#include "game_object.h"
#include "modifier.h"


Modifier::Modifier(double xpos, double ypos, float scale, std::string filename)
    :Game_Object(xpos, ypos, scale, filename)
{
}

bool Modifier::handle(sf::Event event, Context& context) 
{
    return false;
}
