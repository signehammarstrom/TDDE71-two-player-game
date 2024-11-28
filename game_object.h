#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// includes
/*_______________________________________________________________________________________*/
#include <SFML/Graphics.hpp>
#include "context.h"


// Game_Object
/*_______________________________________________________________________________________*/

class Game_Object
{
public:
    // Konstruktor & särskilda medlemsfuntkioner
    /*_____________________________________________________*/
    Game_Object(double xpos, double ypos);
    //Game_Object(Game_Object const& other) = delete;
    //Game_Object& operator=(Game_Object const& other) = delete;
    //Game_Object(Game_Object && other) = delete;
    //Game_Object& operator=(Game_Object && other) = delete;
    virtual ~Game_Object() = default;

    // Medlemsfunktioner
    /*_____________________________________________________*/
    virtual bool handle(sf::Event event, Context& context) = 0;
    virtual void update(sf::Time delta, Context& context) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void perform_collision(Game_Object* const& other);
    bool collides(Game_Object* const&) const;
    double get_xpos() const; 
    double get_ypos() const;

protected:
    // ...
    double xpos;
    double ypos;
    
private:
    // ...
};

#endif


