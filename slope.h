#ifndef SLOPE_H
#define SLOPE_H

#include <vector>
#include <string>
#include "context.h"
#include "game_object.h"
#include "context.h"
#include <SFML/Graphics.hpp>
#include "player.h"
#include "slope_objects.h"
#include <map>


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
    void read_track(Context& context,  std::map<std::string, std::vector<float>>& constantMap);
    void initialize_context(bool side, sf::RenderWindow& window);
    float const x_speed { 200.0f };
    sf::Font font{};
    sf::Text text{};
    Snow_Text* snow_text;
    Background* background;
    Progress_Bar* progress_bar;
    void delete_vector(std::vector<Game_Object*>& object_vector, bool del = true);
};


#endif
