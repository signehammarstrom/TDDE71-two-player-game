#include <SFML/Graphics.hpp>
#include <string>
#include "game_object.h"
#include "modifier.h"

using namespace std; 

Modifier::Modifier(double xpos, double ypos, float size, sf::Vector2u& window_size, 
    string& filename)
    :Game_Object(xpos, ypos, size, window_size, filename)
{
}
