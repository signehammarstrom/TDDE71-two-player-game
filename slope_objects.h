#ifndef SLOPE_OBJECTS_H
#define SLOPE_OBJECTS_H
#include "context.h"
#include "player.h"
#include "static_obstacle.h"

class Snow_Text
{
public:
    Snow_Text(bool side);
    void update(Context& context);
    void render(sf::RenderWindow& window);
private:
    sf::Font font{};
    sf::Text text{};


};

class Background
{
    public:
        Background(bool side);
        void update(sf::Time delta, Context& context);
        void render(sf::RenderWindow& window);

    private:
        sf::Texture texture_background;
        sf::Sprite background;
};



class Progress_Bar {

public:
    Progress_Bar(bool side);

    // Uppdaterar framsteg (0.0 - 1.0)
    void update(Game_Object*& player, Game_Object*& goal);
    void render(sf::RenderWindow &window);

private:
    sf::RectangleShape background;
    sf::RectangleShape foreground;
    float width;
    float total_distance;

};


#endif