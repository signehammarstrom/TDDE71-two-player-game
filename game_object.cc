#include <SFML/Graphics.hpp>
#include <iostream>
#include "game_object.h"

using namespace std;

Game_Object::Game_Object(double x, double y, float size, sf::Vector2u window_size, string filename)
    : sprite{}, texture{}, scale{}, removed {false}
{
    if (!texture.loadFromFile(filename))
    {
        throw  runtime_error{"Couldn't open filename"};
    }
    sprite.setTexture(texture);
    sf::Vector2u texture_size { texture.getSize() };
    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    sprite.setPosition(x, y);
    scale = size*window_size.x/(1136*texture_size.x);
    sprite.setScale(scale, scale);
}

bool Game_Object::collides(Game_Object* const& object) const
{
    return bounds().intersects(object->bounds());
}

void Game_Object::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool Game_Object::is_removed() const
{
    return removed;
}

void Game_Object::remove()
{
    removed = true;
}

sf::FloatRect Game_Object::bounds() const
{
    return sprite.getGlobalBounds();
}

float Game_Object::get_position() const
{
    return sprite.getPosition().y + bounds().height/2;
}