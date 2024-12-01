#include "snowball_projectile.h"
#include <SFML/Graphics.hpp>
#include "game_object.h"


Snowball_Projectile::Snowball_Projectile(double xpos, double ypos)
:Game_Object(xpos,ypos), radius{}, y_speed{50}
{
    texture.loadFromFile("snowball.png");
    if (!texture.loadFromFile("snowball.png"))
    {
        std::cerr << "Kan inte öppna: snowball.png" << std::endl;
    }
    sf::Vector2u window_size {1136, 640};

    sprite.setTexture(texture);
    sf::Vector2u texture_size { texture.getSize() };
    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    sprite.setPosition(xpos, ypos);
    sprite.setScale(0.05f, 0.05f);

}


bool Snowball_Projectile::handle(sf::Event event, Context& context)
{}

void Snowball_Projectile::update(sf::Time delta, Context& context)
{
    float distance {delta.asSeconds() * (y_speed + context.y_speed)};
    sf::Vector2f old_position {sprite.getPosition()};
    
    sprite.move({0, distance});


}

void Snowball_Projectile::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}


void Snowball_Projectile::perform_collision(Game_Object* const& other, Context& context)
{
    remove();
}

sf::FloatRect Snowball_Projectile::bounds() const
{
    return sprite.getGlobalBounds();
}