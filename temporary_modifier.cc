#include <SFML/Graphics.hpp>
#include <string>

#include "game_object.h"
#include "context.h"
#include "modifier.h"
#include "moving_object.h"
#include "temporary_modifier.h"



//Temporary_Modifier
/*_______________________________________________________________________________________*/

Temporary_Modifier::Temporary_Modifier(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier, std::string filename)
    : Moving_Object(xpos, ypos, xspeed, filename), width{width}, 
    height{height}, speedmodifier{speedmodifier}
{
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

//Chalmerist
/*_______________________________________________________________________________________*/

Chalmerist::Chalmerist(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier, std::string filename)
    : Temporary_Modifier(xpos, ypos, xspeed, width, height, speedmodifier, filename)
{
    sf::Vector2u texture_size { texture.getSize() };
    double scale {width/(texture_size.x/2)};
    double scale2 {height/(texture_size.y/2)};
    sprite.setScale(scale, scale2);
}

bool Chalmerist::handle(sf::Event event, Context& context)
{
   return false;
}


void Chalmerist::update(sf::Time delta, Context& context) 
{
    
   float distance {delta.asSeconds() * context.y_speed};
   sf::Vector2f old_position {sprite.getPosition()};
    
   sprite.move({0, -distance});
   return;
}

void Chalmerist::perform_collision(Game_Object* const& other, Context& context)
{
   return;
}

//Can
/*_______________________________________________________________________________________*/

Can::Can(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier, std::string filename)
    : Temporary_Modifier(xpos, ypos, xspeed, width, height, speedmodifier, filename)
{
    sf::Vector2u texture_size { texture.getSize() };
    double scale {width/(texture_size.x/2)};
    double scale2 {height/(texture_size.y/2)};
    sprite.setScale(scale, scale2);
}

bool Can::handle(sf::Event event, Context& context)
{
   return false;
}

void Can::update(sf::Time delta, Context& context) 
{
    
   float distance {delta.asSeconds() * context.y_speed};
   sf::Vector2f old_position {sprite.getPosition()};
    
   sprite.move({0, -distance});
   return;
}

void Can::perform_collision(Game_Object* const& other, Context& context)
{
   return;
}

//Kir
/*_______________________________________________________________________________________*/

Kir::Kir(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier, std::string filename)
    : Temporary_Modifier(xpos, ypos, xspeed, width, height, speedmodifier, filename)
{
    sf::Vector2u texture_size { texture.getSize() };
    double scale {width/(texture_size.x/2)};
    double scale2 {height/(texture_size.y/2)};
    sprite.setScale(scale, scale2);
}

bool Kir::handle(sf::Event event, Context& context)
{
   return false;
}


void Kir::update(sf::Time delta, Context& context) 
{
    
   float distance {delta.asSeconds() * context.y_speed};
   sf::Vector2f old_position {sprite.getPosition()};
    
   sprite.move({0, -distance});
   return;
}

void Kir::perform_collision(Game_Object* const& othe, Context& contextr)
{
   return;
}