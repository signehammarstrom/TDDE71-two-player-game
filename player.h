#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"

class player : public game_object
{
public:

    //bool handle(sf::Event event);
    //void update(sf::Time delta ;
    //void render(sf::RenderWindow& window);
    //void throw_snowball();
    //void perform_collision(game_object const&);
    //bool collides(game_object const&) const;
private:
   int height{};
   int weight{};
 
};



#endif