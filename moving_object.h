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
    Moving_Object(double xpos, double ypos, float scale, double xspeed, std::string filename, bool right_direction=true);
    ~Moving_Object() = default;
    virtual void update(sf::Time delta, Context& context);

    double get_xspeed() const;

protected:
    double xspeed {};
    bool right_direction{};
};

//Snowball_Mod
/*_______________________________________________________________________________________*/

class Snowball_Mod : public Moving_Object
{
public:
   Snowball_Mod(double xpos, double ypos, float scale, double xspeed, std::string filename = "snowball_pile.png", bool right_direction=true);
   ~Snowball_Mod() = default;

    bool handle(sf::Event event, Context& context) override;
   // void update(sf::Time delta, Context& context) override;
    void render(sf::RenderWindow& window) override;
    void perform_collision(Game_Object* const& other, Context& context) override;

  //  double get_radius() const;
private:
  // double radius{}; 
};

#endif
