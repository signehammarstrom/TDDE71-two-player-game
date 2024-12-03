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
    virtual void perform_collision(Game_Object* const& other, Context& context) = 0;
    bool collides(Game_Object* const&) const;


    double get_xpos() const; 
    double get_ypos() const;
    virtual sf::FloatRect bounds() const = 0;
    bool is_removed() const;
    void remove();
    virtual void update_time(sf::Time delta); //Används för kiren
    virtual void remove_if_inactual(Context& context); //Används för kiren
    virtual float get_position() const;
    virtual void stop_effect(Game_Object*& object);


protected:
    // ...
    double xpos;
    double ypos;
    sf::Sprite sprite;
    sf::Texture texture;
    bool removed{false};
    float scale;
    
private:
    // ...
};

#endif


