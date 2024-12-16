#ifndef MODIFIER_H
#define MODIFIER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "game_object.h"

class Modifier : public Game_Object 
{
public:
    Modifier(double xpos, double ypos, float size, sf::Vector2u& window_size , 
        std::string& filename);
    ~Modifier() = default;
};

#endif
