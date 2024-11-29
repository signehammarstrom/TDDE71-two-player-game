#include <SFML/Graphics.hpp>

#include "game_object.h"

// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Game_Object::Game_Object(double x, double y, std::string filename)
    : xpos {x}, ypos {y}, texture{}, sprite{}
{

    texture.loadFromFile(filename);
    if (!texture.loadFromFile(filename))
    {
        throw std::runtime_error{"Couldn't open filename"};
    }

    sprite.setTexture(texture);
    sf::Vector2u texture_size { texture.getSize() };
    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    sprite.setPosition(xpos, ypos);
    
}

// Medlemsfunktioner
/*_____________________________________________________*/

void Game_Object::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}


bool Game_Object::collides(Game_Object* const& object2) const
{
    return bounds().intersects(object2->bounds());
}

sf::FloatRect Game_Object::bounds() const
{
    return sprite.getGlobalBounds();
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
