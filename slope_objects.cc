#include <iostream>

#include "context.h"
#include "slope_objects.h"
#include "player.h"
#include "static_obstacle.h"


Snow_Text::Snow_Text(bool side)
{
    if (!font.loadFromFile("font.ttf"))
    {
        throw std::runtime_error { "Kan inte öppna: font.ttf" };
    }

    text.setFont(font);

    double left_bound{0};
    if (!side)
    {
        left_bound = 1136/2;
    }

    std::string snow_text{"Snowball count: " + std::to_string(0)};
    text.setString(snow_text);
    text.setFillColor(sf::Color(255, 20, 147));
    text.setPosition(left_bound, 0);
}
void Snow_Text::update(Context& context)
{
    text.setString("Snowball count: " + std::to_string(context.snow_count));
}
void Snow_Text::render(sf::RenderWindow& window)
{
    window.draw(text);
}

Background::Background(bool side)
{
if (!texture_background.loadFromFile("white_background.png"))
    {
        throw std::runtime_error("Kan inte öppna: white_background.png");
    }
    double left_bound{0};
    if (!side)
    {
        left_bound = 1136/2;
    }

    background.setTexture(texture_background);
    background.setPosition(left_bound, 0);
}

void Background::render(sf::RenderWindow& window)
{
    window.draw(background);
}


Progress_Bar::Progress_Bar(bool side)
{
    background.setSize(sf::Vector2f(20,300));
    background.setFillColor(sf::Color::Black);
    double left_bound{0};
    if (!side)
    {
        left_bound = 1136/2;
    }
    background.setPosition(left_bound+10, 200);

    foreground.setSize(sf::Vector2f(20,0));
    foreground.setFillColor(sf::Color::Blue);
    foreground.setPosition(left_bound + 10, 200);

    total_distance = 0;

    this->width = 300;
}

void Progress_Bar::update(Game_Object*& player, Game_Object*& goal) 
{
    if (total_distance == 0)
    {
        total_distance = goal->get_position() -  player->get_position();
    }
    float progress {1 - (goal->get_position() -  player->get_position())/total_distance};
    foreground.setSize(sf::Vector2f(foreground.getSize().x, width * progress));
}

void Progress_Bar::render(sf::RenderWindow &window)
{
    window.draw(background);
    window.draw(foreground);
}