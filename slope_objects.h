#ifndef SLOPE_OBJECTS_H
#define SLOPE_OBJECTS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "context.h"
#include "player.h"
#include "static_obstacle.h"

//Deklaration av Snow_Text
/*_______________________________________________________________________________________*/
class Snow_Text
{
public:
    Snow_Text(Context& context);
    ~Snow_Text() = default;

    void update(Context& context);
    void render(sf::RenderWindow& window);

private:
    sf::Font font{};
    sf::Text text{};
};


//Deklaration av Background
/*_______________________________________________________________________________________*/
class Background
{
    public:
        Background(Context& context);
        ~Background() = default;

        void update(sf::Time delta, Context& context);
        void render(sf::RenderWindow& window);
        void set_graphics(float scale, Context const& context);

    private:
        sf::Texture texture_background;
        std::vector<sf::Sprite> backgrounds; 
};


//Deklaration av Progress_Bar
/*_______________________________________________________________________________________*/
class Progress_Bar 
{
public:
    Progress_Bar(Context& context);
    ~Progress_Bar() = default;

    void update(Game_Object*& player, Game_Object*& goal);
    void render(sf::RenderWindow& window);

private:
    void set_graphics(sf::RectangleShape& graphics, Context const& context, sf::Color color);
    sf::RectangleShape background;
    sf::RectangleShape foreground;
    float height;
    float total_distance;
};

#endif