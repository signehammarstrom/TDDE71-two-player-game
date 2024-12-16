#ifndef SLOPE_H
#define SLOPE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include "game_object.h"
#include "context.h"
#include "player.h"
#include "slope_objects.h"

class Slope
{
public:
    Slope(bool side, std::map<std::string, std::vector<float>>& constantMap, sf::RenderWindow& window);
    ~Slope();

    void handle(sf::Event event);
    void update(sf::Time delta);
    void render(sf::RenderWindow& window);
    
    Context context;
    
private:

    void read_track(Context& context, std::map<std::string, std::vector<float>>& constantMap);
    void initialize_context(bool side, sf::RenderWindow& window);
    void remove_inactual(std::vector<Game_Object*>& objectlist, sf::Time delta);
    void delete_vector(std::vector<Game_Object*>& object_vector, bool del = true);

    Snow_Text* snow_text;
    Background* background;
    Progress_Bar* progress_bar;
};

#endif
