#ifndef SLOPE_OBJECTS_H
#define SLOPE_OBJECTS_H
#include "context.h"

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
        void render(sf::RenderWindow& window);

    private:
        sf::Texture texture_background;
        sf::Sprite background;
};


#endif