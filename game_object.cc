#include <SFML/Graphics.hpp>

#include "game_object.h"

// Konstruktor & särskilda medlemsfuntkioner
/*_____________________________________________________*/
Game_Object::Game_Object(double x, double y, std::string filename)
    : xpos {x}, ypos {y}, texture{}, sprite{}
{
    // texture.loadFromFile("snowball.png");
    // if (!texture.loadFromFile("snowball.png"))
    // {
    //     throw std::logic_error{"Kan inte Öppna texturefil"};
    // }

    texture.loadFromFile(filename);
    if (!texture.loadFromFile(filename))
    {
        throw std::runtime_error{"Couldn't open filename"};
    }
    sf::Vector2u window_size {1136, 640};

    sprite.setTexture(texture);
    sf::Vector2u texture_size { texture.getSize() };
    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    sprite.setPosition(xpos, ypos);
    sprite.setScale(0.05f, 0.05f);
}

// Medlemsfunktioner
/*_____________________________________________________*/

void Game_Object::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}


bool Game_Object::collides(Game_Object* const&) const
{
    // return bounds().intersects(object2->bounds());
    return false;
}

// sf::FloatRect Game_Object::bounds() const
// {
//     return sprite.getGlobalbounds();
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
