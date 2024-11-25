#ifndef SLOPE_H
#define SLOPE_H

#include <vector>
#include "game_object.h"
#include <SFML/Graphics.hpp>


struct Context
{
    std::vector<Game_Object*> obj_lst{};

    double y_speed {};

    bool side {}; // true ger vänster

    Game_Object* active_mod{};

    sf::Clock clock;

    unsigned int snow_count{};

    bool game_finished{};

};


class Slope
{
public:
    Slope(bool side);
    
    void handle(sf::Event event);
    void update(sf::Time delta);
    void render(sf::RenderWindow& window);
    
    Context context;
    
private:
    void read_track();
};


#endif