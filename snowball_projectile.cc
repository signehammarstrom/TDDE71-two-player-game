#include <SFML/Graphics.hpp>
#include "snowball_projectile.h"
#include "game_object.h"
#include "modifier.h"

using namespace std;

Snowball_Projectile::Snowball_Projectile(double xpos, double ypos, float size, 
    sf::Vector2u& window_size, string filename)
:Game_Object(xpos, ypos, size, window_size, filename), y_speed{50}
{}

void Snowball_Projectile::update(sf::Time delta, Context& context)
{
    float distance {delta.asSeconds() * (y_speed + context.y_speed)};
    sf::Vector2f old_position {sprite.getPosition()};
    sprite.move({0, distance});
}

void Snowball_Projectile::perform_collision(Game_Object* const& other, 
    Context&)
{
    Modifier* mod = dynamic_cast<Modifier*>(other);
    if (mod)
    {
        remove();
    }
    mod = nullptr;
}