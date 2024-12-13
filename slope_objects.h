#ifndef SLOPE_OBJECTS_H
#define SLOPE_OBJECTS_H
#include "context.h"
#include "player.h"
#include "static_obstacle.h"

class Snow_Text
{
public:
    Snow_Text(Context& context);
    void update(Context& context);
    void render(sf::RenderWindow& window);
private:
    sf::Font font{};
    sf::Text text{};


};

class Background
{
    public:
        Background(Context& context);
        void update(sf::Time delta, Context& context);
        void render(sf::RenderWindow& window);

    private:
        sf::Texture texture_background;
        sf::Sprite background;
        sf::Sprite background2;
        sf::Sprite background3;
};



class Progress_Bar {

public:
    Progress_Bar(Context& context);

    // Uppdaterar framsteg (0.0 - 1.0)
    void update(Game_Object*& player, Game_Object*& goal);
    void render(sf::RenderWindow &window);

private:
    sf::RectangleShape background;
    sf::RectangleShape foreground;
    float height;
    float total_distance;

};


#endif