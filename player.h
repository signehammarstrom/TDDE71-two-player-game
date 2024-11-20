#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"

class Player : public Game_Object
{
public:
    Player(/*arg*/);
    ~Player();
    //bool handle(sf::Event event);
    //void update(sf::Time delta ;
    //void render(sf::RenderWindow& window);
    //void throw_snowball();
    //void perform_collision(game_object const&);
    //bool collides(game_object const&) const;
private:
   double height{};
   double width{};
 
};

#endif