#ifndef SNOWBALL_PROJECTILE_H
#define SNOWBALL_PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "game_object.h"

class Snowball_Projectile: public Game_Object
{
public:
    Snowball_Projectile(double xpos, double ypos, float size , sf::Vector2u window_size, std::string filename = "snowball.png");
    ~Snowball_Projectile() = default;

    void update(sf::Time delta, Context& context) override;
    void perform_collision(Game_Object* const& other, Context& context) override;
    
private:
    float y_speed;
};

#endif
