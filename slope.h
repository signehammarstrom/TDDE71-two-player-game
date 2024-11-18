#include <vector>
#include "game_object.h"
#include <SFML/Graphics.hpp>



struct Context
{
    std::vector<Game_Object*> obj_lst{};

    unsigned int speed {};

    bool side {}; // true ger vänster

    std::vector<Game_Object*> mod_lst{};

    sf::Clock clock;

    unsigned int snow_count{0};

    bool game_finished{false};

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
