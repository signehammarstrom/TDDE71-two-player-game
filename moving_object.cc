#include <SFML/Graphics.hpp>
#include <string>

#include "game_object.h"
#include "context.h"
#include "modifier.h"
#include "moving_object.h"

//Moving_Object
/*_______________________________________________________________________________________*/


Moving_Object::Moving_Object(double xpos, double ypos, double xspeed, std::string filename)
   : Modifier(xpos, ypos, filename), xspeed{xspeed}
{}

double Moving_Object::get_xspeed() const
{
   return xspeed;
}

//Snowball_Mod
/*_______________________________________________________________________________________*/



Snowball_Mod::Snowball_Mod(double xpos, double ypos, double xspeed, double radius, std::string filename)
   : Moving_Object(xpos, ypos, xspeed, filename), radius{radius}
{
   sprite.setScale(0.05f, 0.05f);
}

bool Snowball_Mod::handle(sf::Event event, Context& context)
{
   return false;
}


void Snowball_Mod::update(sf::Time delta, Context& context) 
{
    
   float distance {delta.asSeconds() * context.y_speed};
   sf::Vector2f old_position {sprite.getPosition()};
    
   sprite.move({0, -distance});
   return;
}

void Snowball_Mod::perform_collision(Game_Object* const& other, Context& context)
{
   return;
}

double Snowball_Mod::get_radius() const
{
   return radius;
}