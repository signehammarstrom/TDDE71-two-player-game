#ifndef SLOPE_H
#define SLOPE_H

#include <vector>
#include "context.h"
#include "game_object.h"
#include <SFML/Graphics.hpp>
#include "player.h"


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
    float const x_speed { 128.0f };

};


#endif
