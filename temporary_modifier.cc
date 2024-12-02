#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "game_object.h"
#include "context.h"
#include "modifier.h"
#include "moving_object.h"
#include "temporary_modifier.h"



//Temporary_Modifier
/*_______________________________________________________________________________________*/

Temporary_Modifier::Temporary_Modifier(double xpos, double ypos, float scale, double xspeed,
       double speedmodifier, std::string filename, bool is_active)
    : Moving_Object(xpos, ypos, scale, xspeed, filename), speedmodifier{speedmodifier}
{
   time_passed = sf::Time::Zero;
}


 double Temporary_Modifier::get_width() const
 {
    return width;
 }

double Temporary_Modifier::get_height() const
{
    return height;
}

double Temporary_Modifier::get_speedmodifier() const
{
    return speedmodifier;
}

void Temporary_Modifier::update_time(sf::Time delta)
{
   time_passed += delta;
}

void Temporary_Modifier::active(sf::Time time)
{
   return;
}

//Chalmerist
/*_______________________________________________________________________________________*/

Chalmerist::Chalmerist(double xpos, double ypos, float scale, double xspeed,
         double speedmodifier, std::string filename, bool is_active)
    : Temporary_Modifier(xpos, ypos, scale, xspeed, speedmodifier, filename)
{}

bool Chalmerist::handle(sf::Event event, Context& context)
{
   return false;
}

void Chalmerist::render(sf::RenderWindow& window)
{
   window.draw(sprite);
   return;
}

/*
void Chalmerist::update(sf::Time delta, Context& context) 
{
    
   float distance {delta.asSeconds() * context.y_speed};
   sf::Vector2f old_position {sprite.getPosition()};
    
   sprite.move({0, -distance});
   return;
}
*/

void Chalmerist::perform_collision(Game_Object* const& other, Context& context)
{
   sprite.setScale(0, 0);
   return;
}

//Can
/*_______________________________________________________________________________________*/

Can::Can(double xpos, double ypos, float scale, double xspeed,
        double speedmodifier, std::string filename, bool is_active)
    : Temporary_Modifier(xpos, ypos, scale, xspeed, speedmodifier, filename)
{}

bool Can::handle(sf::Event event, Context& context)
{
   return false;
}

void Can::render(sf::RenderWindow& window)
{
   window.draw(sprite);
   return;
}

/*
void Can::update(sf::Time delta, Context& context) 
{
    
   float distance {delta.asSeconds() * context.y_speed};
   sf::Vector2f old_position {sprite.getPosition()};
    
   sprite.move({0, -distance});
   return;
}
*/

void Can::perform_collision(Game_Object* const& other, Context& context)
{
   sprite.setScale(0, 0);
   return;
}

//Kir
/*_______________________________________________________________________________________*/

Kir::Kir(double xpos, double ypos, float scale, double xspeed,
        double speedmodifier, std::string filename, bool is_active)
    : Temporary_Modifier(xpos, ypos, scale, xspeed, speedmodifier, filename)
{}

bool Kir::handle(sf::Event event, Context& context)
{
   return false;
}

void Kir::render(sf::RenderWindow& window)
{
   window.draw(sprite);
   return;
}

/*
void Kir::update(sf::Time delta, Context& context) 
{
    
   float distance {delta.asSeconds() * context.y_speed};
   sf::Vector2f old_position {sprite.getPosition()};
    
   sprite.move({0, -distance});
   return;
}
*/

void Kir::perform_collision(Game_Object* const& other, Context& context)
{
   context.y_speed = context.y_speed * get_speedmodifier();
   context.active_temp_mods.push_back(this);
   sprite.setScale(0, 0);
}

void Kir::remove_if_inactual(Context& context)
{
   if(time_passed.asSeconds() >= 3.f)
   {
      
      context.y_speed = context.base_speed;
      remove();
   }
}