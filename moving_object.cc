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
   : Modifier(xpos, ypos, scale, filename), xspeed{xspeed}, right_direction{right_direction}
{}

void Moving_Object::update(sf::Time delta, Context& context) 
{
   float dx{};
   dx = 2.f;
   float distance_y {delta.asSeconds() * context.y_speed};
   sf::Vector2f old_position {sprite.getPosition()};

   float distance_x{delta.asSeconds() * xspeed};
   if(right_direction)
   {
      if(context.right_bound - old_position.x - context.side_tire_size < dx)
      {
         right_direction = false;
         sprite.move(-distance_x, -distance_y);
      }
      else
      {
         sprite.move(distance_x, -distance_y);
      }
   }

   if(!right_direction)
   {
      if(old_position.x - context.left_bound - context.side_tire_size< dx)
      {
         right_direction = true;
         sprite.move(distance_x, -distance_y);
      }
      else
      {
         sprite.move(-distance_x, -distance_y);
      }
   }
   return;

}

double Moving_Object::get_xspeed() const
{
   return xspeed;
}

//Snowball_Mod
/*_______________________________________________________________________________________*/



Snowball_Mod::Snowball_Mod(double xpos, double ypos, float scale, double xspeed, std::string filename, bool right_direction)
   : Moving_Object(xpos, ypos, scale, xspeed, filename, right_direction)
{}

bool Snowball_Mod::handle(sf::Event event, Context& context)
{
   return false;
}

void Snowball_Mod::render(sf::RenderWindow& window)
{
   window.draw(sprite);
}



/*void Snowball_Mod::update(sf::Time delta, Context& context) 
{

   float distance_y {delta.asSeconds() * context.y_speed};
   sf::Vector2f old_position {sprite.getPosition()};

   float distance_x{delta.asSeconds() * xspeed};
   if(right_direction)
   {
      if(context.right_bound - old_position.x < 2.f)
      {
         right_direction = false;
         sprite.move(-distance_x, -distance_y);
      }
      else
      {
         sprite.move(distance_x, -distance_y);
      }
   }

   if(!right_direction)
   {
      if(old_position.x - context.left_bound < 2.f)
      {
         right_direction = true;
         sprite.move(distance_x, -distance_y);
      }
      else
      {
         sprite.move(-distance_x, -distance_y);
      }
   }
   return;

}*/

void Snowball_Mod::perform_collision(Game_Object* const& other, Context& context)
{
   context.snow_count += 3;
   remove();
}

/*
double Snowball_Mod::get_radius() const
{
   return radius;
}
*/