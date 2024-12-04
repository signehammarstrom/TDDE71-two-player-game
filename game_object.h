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
    Game_Object(double xpos, double ypos, float radius, std::string filename);
    virtual ~Game_Object() = default;

    // Medlemsfunktioner
    /*_____________________________________________________*/
    virtual bool handle(sf::Event event, Context& context) = 0;
    virtual void update(sf::Time delta, Context& context) = 0;
    void render(sf::RenderWindow& window);
    virtual void perform_collision(Game_Object* const& other, Context& context) = 0;
    bool collides(Game_Object* const&) const;


    virtual sf::FloatRect bounds() const = 0;
    bool is_removed() const;
    void remove();
    virtual float get_position() const;
    virtual void stop_effect(Game_Object*& object);


protected:
    // ...
    sf::Sprite sprite;
    sf::Texture texture;
    bool removed{false};
    float scale;
    
private:
    // ...
};

#endif


