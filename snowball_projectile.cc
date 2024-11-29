#include "snowball_projectile.h"
#include <SFML/Graphics.hpp>
#include "game_object.h"


Snowball_Projectile::Snowball_Projectile(double xpos, double ypos, std::string filename)
:Game_Object(xpos,ypos, filename), radius{}, y_speed{50}
{

}


bool Snowball_Projectile::handle(sf::Event event, Context& context)
{}

void Snowball_Projectile::update(sf::Time delta, Context& context)
{
    float distance {delta.asSeconds() * (y_speed + context.y_speed)};
    sf::Vector2f old_position {sprite.getPosition()};
    
    sprite.move({0, distance});


}


void Snowball_Projectile::perform_collision(Game_Object* const& other, Context& context)
{}