#include <SFML/Graphics.hpp>
#include <string>

#include "game_object.h"
#include "context.h"
#include "modifier.h"
#include "moving_object.h"
#include "temporary_modifier.h"



//Temporary_Modifier
/*_______________________________________________________________________________________*/

Temporary_Modifier::Temporary_Modifier(double xpos, double ypos, float scale, double xspeed,
       double speedmodifier, std::string filename)
    : Moving_Object(xpos, ypos, scale, xspeed, filename), speedmodifier{speedmodifier}
{}


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

//Chalmerist
/*_______________________________________________________________________________________*/

Chalmerist::Chalmerist(double xpos, double ypos, float scale, double xspeed,
         double speedmodifier, std::string filename)
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
   return;
}

//Can
/*_______________________________________________________________________________________*/

Can::Can(double xpos, double ypos, float scale, double xspeed,
        double speedmodifier, std::string filename)
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
   return;
}

//Kir
/*_______________________________________________________________________________________*/

Kir::Kir(double xpos, double ypos, float scale, double xspeed,
        double speedmodifier, std::string filename)
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
   return;
}