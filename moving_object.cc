#include <SFML/Graphics.hpp>
#include <string>
#include <cmath> 
#include <iostream>
#include <stdlib.h>
#include <random>
#include "game_object.h"
#include "context.h"
#include "modifier.h"
#include "moving_object.h"

//Moving_Object
/*_______________________________________________________________________________________*/
Moving_Object::Moving_Object(double xpos, double ypos, float size, float xspeed,
   sf::Vector2u window_size, std::string filename)
   : Modifier(xpos, ypos, size, window_size, filename), xspeed{xspeed}, right_direction{}
{
   right_direction = rand()%2;
}

void Moving_Object::update(sf::Time delta, Context& context) 
{
   float dx{2.f};
   float rotationSpeed{120.0f};
   float distance_y {delta.asSeconds() * context.y_speed};
   float distance_x{delta.asSeconds() * xspeed};
   sf::Vector2f old_position {sprite.getPosition()};

   if(right_direction)
   {
      if(context.right_bound - old_position.x + context.side_tire_size < dx)
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
      if(old_position.x - context.left_bound - context.side_tire_size< dx)
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
}

float Moving_Object::get_xspeed() const
{
   return xspeed;
}


//Snowball_Mod
/*_______________________________________________________________________________________*/
Snowball_Mod::Snowball_Mod(double xpos, double ypos, float size, float xspeed, 
   sf::Vector2u window_size, std::string filename)
   : Moving_Object(xpos, ypos, size, xspeed, window_size, filename)
{}

void Snowball_Mod::perform_collision([[maybe_unused]]Game_Object* const& other, Context& context)
{
   context.snow_count += 3;
   remove();
}

