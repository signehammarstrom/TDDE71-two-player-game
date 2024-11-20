#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// includes
/*_______________________________________________________________________________________*/
include <SFML/Graphics.hpp>


// GameObject
/*_______________________________________________________________________________________*/

class GameObject
{
public:
    // Konstruktor & särskilda medlemsfuntkioner
    /*_____________________________________________________*/
    GameObject(double xpos, double ypos);
    GameObject(GameObject const& other) = delete;
    GameObejct& operator=(GameObject const& other) = delete;
    GameObject(GameObejct && other) = delete;
    GameObejct& operator=(GameObject && other) = delete;
    virtual ~GameObject() = default;

    // Medlemsfunktioner
    /*_____________________________________________________*/
    virtual void handle(sf::Event event) = 0;
    virtual bool update(sf::Time delta /*...*/) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool collides(GameObject const&) const = 0;
    virtual void perform_collision(GameObject const&) = 0;

protected:
    // ...
    double xpos;
    double ypos;
    
private:
    // ...
};

#endif