#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"

class Player : public Game_Object
{
public:
    Player(double xpos, double ypos, double height, double width);
    ~Player() = default;
    //bool handle(sf::Event event);
    //void update(sf::Time delta, double x_speed);
    //void render(sf::RenderWindow& window);
    //void throw_snowball();
    //void perform_collision(game_object const&);
    //bool collides(game_object const&) const;
    double get_xpos() const; 
    double get_ypos() const;
    double get_width() const;
    double get_height() const;


private:
   double height{};
   double width{};
 
};

#endif