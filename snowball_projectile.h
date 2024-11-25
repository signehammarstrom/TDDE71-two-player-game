#ifndef SNOWBALL_PROJECTILE_H
#define SNOWBALL_PROJECTILE_H

// includes
/*_______________________________________________________________________________________*/
#include <SFML/Graphics.hpp>


// GameObject
/*_______________________________________________________________________________________*/

class Snowball_Projectile
{
public:
    // Konstruktor & särskilda medlemsfuntkioner
    /*_____________________________________________________*/
    Snowball_Projectile(Snowball_Projectile const& other) = delete;
    Snowball_Projectile& operator=(Snowball_Projectile const& other) = delete;
    Snowball_Projectile(Snowball_Projectile && other) = delete;
    Snowball_Projectile& operator=(Snowball_Projectile && other) = delete;
    virtual ~Snowball_Projectile() = default;

    // Medlemsfunktioner
    /*_____________________________________________________*/
    virtual void handle(sf::Event event) = 0;
    virtual bool update(sf::Time delta /*...*/) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool collides(GameObject const&) const = 0;
    virtual void perform_collision(GameObject const&) = 0;
    
private:
    float radius;
    float yspeed;
};

#endif

