#include <SFML/Graphics.hpp>
#include <string>

#include "game_object.h"
#include "modifier.h"


Modifier::Modifier(double xpos, double ypos, std::string filename)
    :Game_Object(xpos, ypos), texture{}, sprite{}
{
    texture.loadFromFile(filename);
    if (!texture.loadFromFile(filename))
    {
        throw std::runtime_error{"Couldn't open filename"};
    }
    sprite.setTexture(texture);
    sf::Vector2u texture_size{texture.getSize()};
    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    sprite.setPosition(xpos, ypos);
    sprite.setScale(0.1f, 0.1f);

}
