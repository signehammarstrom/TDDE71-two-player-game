#ifndef SLOPE_H
#define SLOPE_H

#include <vector>
#include "context.h"
#include "game_object.h"
#include "context.h"
#include <SFML/Graphics.hpp>
#include "player.h"
#include "slope_objects.h"



// struct Context
// {
//     std::vector<Game_Object*> obj_lst{};

//     double y_speed {};

//     bool side {}; // true ger vänster

//     Game_Object* active_mod{};

//     sf::Clock clock;

//     unsigned int snow_count{};

//     bool game_finished{};

// };


class Slope
{
public:
    Slope(bool side);
    ~Slope();
    void handle(sf::Event event);
    void update(sf::Time delta);
    void render(sf::RenderWindow& window);
    
    Context context;
    
private:
    void read_track(Context& context);
    float const x_speed { 200.0f };
    void create_track(Context& context);
    sf::Font font{};
    sf::Text text{};

    Snow_Text snow_text;
    Background background;
    Progress_Bar progress_bar;
    void delete_vector(std::vector<Game_Object*>& object_vector, bool del = true);
};


#endif
