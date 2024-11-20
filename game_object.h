#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// includes
/*_______________________________________________________________________________________*/
#include <SFML/Graphics.hpp>


// GameObject
/*_______________________________________________________________________________________*/

class Game_Object
{
public:
    // Konstruktor & särskilda medlemsfuntkioner
    /*_____________________________________________________*/
    Game_Object(double xpos, double ypos);
    //GameObject(GameObject const& other) = delete;
    //GameObejct& operator=(GameObject const& other) = delete;
    //GameObject(GameObejct && other) = delete;
    //GameObejct& operator=(GameObject && other) = delete;
    //virtual ~GameObject() = default;

    // Medlemsfunktioner
    /*_____________________________________________________*/
    void handle(sf::Event event);
    bool update(sf::Time delta /*...*/);
    void render(sf::RenderWindow& window);
    //virtual bool collides(GameObject const&) const = 0;
    //virtual void perform_collision(GameObject const&) = 0;

protected:
    // ...
    double xpos;
    double ypos;
    
private:
    // ...
};

#endif