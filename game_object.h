#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// includes
/*_______________________________________________________________________________________*/
#include <SFML/Graphics.hpp>


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
    //virtual void handle(sf::Event event) = 0;
    //virtual bool update(sf::Time delta /*...*/) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    bool collides(Game_Object const& object2) const;
    virtual sf::FloatRect bounds() const = 0;

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

