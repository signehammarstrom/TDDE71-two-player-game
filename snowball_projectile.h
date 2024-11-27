#ifndef SNOWBALL_PROJECTILE_H
#define SNOWBALL_PROJECTILE_H

// includes
/*_______________________________________________________________________________________*/
#include <SFML/Graphics.hpp>
#include "game_object.h"
#include <iostream>
#include <cmath>


// GameObject
/*_______________________________________________________________________________________*/

class Snowball_Projectile: public Game_Object
{
public:
    // Konstruktor & särskilda medlemsfuntkioner
    /*_____________________________________________________*/
    Snowball_Projectile(double xpos, double ypos);

    /*Snowball_Projectile(Snowball_Projectile const& other) = delete;
    Snowball_Projectile& operator=(Snowball_Projectile const& other) = delete;
    Snowball_Projectile(Snowball_Projectile && other) = delete;
    Snowball_Projectile& operator=(Snowball_Projectile && other) = delete;*/
    ~Snowball_Projectile() = default;

    // Medlemsfunktioner
    /*_____________________________________________________*/
    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;
    void render(sf::RenderWindow& window) override;
    bool collides(Game_Object const&) const override;
    void perform_collision(Game_Object const&);
    
private:
    float radius;
    float y_speed;
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif
