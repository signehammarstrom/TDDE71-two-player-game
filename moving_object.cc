#include <SFML/Graphics.hpp>
#include <string>
#include <cmath> //För sinusberäkningar.
#include <iostream>

#include "game_object.h"
#include "context.h"
#include "modifier.h"
#include "moving_object.h"

//Moving_Object
/*_______________________________________________________________________________________*/


Moving_Object::Moving_Object(double xpos, double ypos, float scale, double xspeed, std::string filename, bool right_direction)
   : Modifier(xpos, ypos, scale, filename), xspeed{xspeed}, 
      right_direction{right_direction}
{}

void Moving_Object::update(sf::Time delta, Context& context) 
{
   float dx{2.f};
   float rotationSpeed{120.0f};
   float distance_y {delta.asSeconds() * context.y_speed};
   sf::Vector2f old_position {sprite.getPosition()};

   float distance_x{delta.asSeconds() * xspeed};
   if(right_direction)
   {
      if(context.right_bound - old_position.x < dx)
      {
         right_direction = false;
         sprite.move(-distance_x, -distance_y);
      }
      else
      {
         sprite.move(distance_x, -distance_y);
      }
      sprite.rotate(rotationSpeed * delta.asSeconds());
   }

   if(!right_direction)
   {
      if(old_position.x - context.left_bound < dx)
      {
         right_direction = true;
         sprite.move(distance_x, -distance_y);
      }
      else
      {
         sprite.move(-distance_x, -distance_y);
      }
      sprite.rotate(-rotationSpeed * delta.asSeconds());
   }
   return;

}

double Moving_Object::get_xspeed() const
{
   return xspeed;
}

//Snowball_Mod
/*_______________________________________________________________________________________*/



Snowball_Mod::Snowball_Mod(double xpos, double ypos, float scale, double xspeed, 
   std::string filename, bool right_direction)
   : Moving_Object(xpos, ypos, scale, xspeed, filename, right_direction)
{}

void Snowball_Mod::perform_collision(Game_Object* const& other, Context& context)
{
   context.snow_count += 3;
   remove();
}

