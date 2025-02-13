#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "game_object.h"
#include "context.h"
#include "modifier.h"
#include "moving_object.h"
#include "temporary_modifier.h"
#include "player.h"
#include "snowball_projectile.h"

using namespace std;

//Temporary_Modifier
/*_______________________________________________________________________________________*/
Temporary_Modifier::Temporary_Modifier(double xpos, double ypos, float size, float xspeed,
   double speedmodifier, sf::Vector2u& window_size, string& filename)
   : Moving_Object(xpos, ypos, size, xspeed,window_size, filename), 
      speedmodifier{speedmodifier}, time_passed{}
{
   time_passed = sf::Time::Zero;
}

void Temporary_Modifier::perform_collision(Game_Object* const& other, Context& context)
{
   Player* player = dynamic_cast<Player*>(other);
   if (player)
   {
      context.y_speed = context.y_speed * get_speedmodifier();
      context.active_temp_mods.push_back(this);
      sprite.setScale(0, 0);
   }

   Snowball_Projectile* snowball = dynamic_cast<Snowball_Projectile*>(other);
   if (snowball)
   {
      remove();
   }
   player = nullptr;
   snowball = nullptr;
}

double Temporary_Modifier::get_speedmodifier() const
{
   return speedmodifier;
}

void Temporary_Modifier::update_time(sf::Time delta)
{
   time_passed += delta;
}

void Temporary_Modifier::remove_if_inactual(Context& context)
{
   if(time_passed.asSeconds() >= 3.f)
   {
      context.y_speed = context.base_speed;
      remove();
   }
}


//Chalmerist
/*_______________________________________________________________________________________*/
Chalmerist::Chalmerist(double xpos, double ypos, float size, float xspeed,
         double speedmodifier, sf::Vector2u& window_size, string filename)
    : Temporary_Modifier(xpos, ypos, size, xspeed, speedmodifier, window_size, filename)
{
}


//Can
/*_______________________________________________________________________________________*/
Can::Can(double xpos, double ypos, float size, float xspeed,
    double speedmodifier, sf::Vector2u& window_size, string filename)
    : Temporary_Modifier(xpos, ypos, size, xspeed, speedmodifier, window_size, filename)
{
}


//Kir
/*_______________________________________________________________________________________*/
Kir::Kir(double xpos, double ypos, float size, float xspeed,
    double speedmodifier, sf::Vector2u& window_size, string filename)
    : Temporary_Modifier(xpos, ypos, size, xspeed, speedmodifier, window_size, filename)
{
}

