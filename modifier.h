#ifndef MODIFIER_H
#define MODIFIER_H

#include <SFML/Graphics.hpp>
#include <string>

#include "game_object.h"

class Modifier : public Game_Object 
{
public:
    Modifier(double xpos, double ypos, std::string filename);
    ~Modifier() = default;
    sf::FloatRect bounds() const;

protected:
    sf::Sprite sprite;
    sf::Texture texture;

private:

    
};

#endif
