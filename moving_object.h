#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include <SFML/Graphics.hpp>
#include <string>

#include "game_object.h"
#include "modifier.h"
#include "context.h"

//Moving_Object
/*_______________________________________________________________________________________*/

class Moving_Object : public Modifier
{
public:
    Moving_Object(double xpos, double ypos, double xspeed, std::string filename);
    ~Moving_Object() = default;

    double get_xspeed() const;

private:
    double xspeed {};
};

//Snowball_Mod
/*_______________________________________________________________________________________*/

class Snowball_Mod : public Moving_Object
{
public:
   Snowball_Mod(double xpos, double ypos, double xspeed, double radius, std::string filename = "snowball.png");
   ~Snowball_Mod() = default;

    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;
    void perform_collision(Game_Object* const& other) override;

    double get_radius() const;
private:
   double radius{}; 
};

#endif
