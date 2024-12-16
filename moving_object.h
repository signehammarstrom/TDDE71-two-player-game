#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include "game_object.h"
#include "modifier.h"
#include "context.h"

//Deklaration av Moving_Object
/*_______________________________________________________________________________________*/
class Moving_Object : public Modifier
{
public:
    Moving_Object(double xpos, double ypos, float size, float xspeed,
        sf::Vector2u& window_size,std::string& filename);
    ~Moving_Object() = default;

    void update(sf::Time delta, Context& context) override;
    float get_xspeed() const;
    
protected:
    float xspeed {};
    bool right_direction{};
};


//Deklaration av Snowball_Mod
/*_______________________________________________________________________________________*/
class Snowball_Mod : public Moving_Object
{
public:
    Snowball_Mod(double xpos, double ypos, float size, float xspeed,
        sf::Vector2u& window_size, std::string filename = "snowball_pile.png");
    ~Snowball_Mod() = default;

    void perform_collision(Game_Object* const& other, Context& context) override;
};

#endif
