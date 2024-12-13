#include <iostream>

#include "context.h"
#include "slope_objects.h"
#include "player.h"
#include "static_obstacle.h"


Snow_Text::Snow_Text(Context& context)
{
    if (!font.loadFromFile("gamefont.ttf"))
    {
        throw std::runtime_error { "Kan inte öppna: gamefont.ttf" };
    }

    text.setFont(font);
    
    std::string snow_text{"Snowball count: " + std::to_string(0)};
    text.setString(snow_text);
    text.setFillColor(sf::Color(255, 20, 147));
    text.setPosition(context.left_bound, 0);
}
void Snow_Text::update(Context& context)
{
    text.setString("Snowball count: " + std::to_string(context.snow_count));
}
void Snow_Text::render(sf::RenderWindow& window)
{
    window.draw(text);
}

Background::Background(Context& context)
{
    if(context.side) //Left slope
    {
        if (!texture_background.loadFromFile("leftlane_signe.png"))
            {
                throw std::runtime_error("Kan inte öppna: leftlane_signe.png");
            }
    }
    else //Right slope
    {
        if (!texture_background.loadFromFile("rightlane_signe.png"))
            {
                throw std::runtime_error("Kan inte öppna: rightlane_signe.png");
            }
    }

    background.setTexture(texture_background);
    background.setPosition(context.left_bound, 0);

    sf::Vector2u texture_size { texture_background.getSize() };
    float scale {((context.window_size.x)/2.f)/texture_size.x};

    background.setScale(scale, scale);
    background2.setTexture(texture_background);
    background2.setPosition(context.left_bound, background.getGlobalBounds().top + background.getGlobalBounds().height);
    background2.setScale(scale, scale);
}

void Background::update(sf::Time delta, Context& context) 
{   
    float distance {delta.asSeconds() * context.y_speed};
    sf::Vector2f old_position {background.getPosition()};
    
    background.move({0, -distance});
    background2.move({0, -distance});
    
    if (background.getGlobalBounds().top + background.getGlobalBounds().height < 0)
    {
        background.setPosition(context.left_bound, background2.getGlobalBounds().top + background2.getGlobalBounds().height);
    }
     if (background2.getGlobalBounds().top + background2.getGlobalBounds().height < 0)
    {
        background2.setPosition(context.left_bound, background.getGlobalBounds().top + background.getGlobalBounds().height);
    }
    
}

void Background::render(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(background2);
}


Progress_Bar::Progress_Bar(Context& context)
: height{}
{
    height = context.window_size.y/3;

    background.setSize(sf::Vector2f(context.side_tire_size/5.f,height));
    background.setFillColor(sf::Color::Black);
    background.setPosition(context.left_bound + context.side_tire_size, context.window_size.y/6.f);
    
    foreground.setSize(sf::Vector2f(context.side_tire_size/5.f,0));
    foreground.setFillColor(sf::Color::Blue);
    foreground.setPosition(context.left_bound  + context.side_tire_size, 200);

    total_distance = 0;

}

void Progress_Bar::update(Game_Object*& player, Game_Object*& goal) 
{
    if (total_distance == 0)
    {
        total_distance = goal->get_position() -  player->get_position();
    }
    float progress {1 - (goal->get_position() -  player->get_position())/total_distance};
    foreground.setSize(sf::Vector2f(foreground.getSize().x, height* progress));
}

void Progress_Bar::render(sf::RenderWindow &window)
{
    window.draw(background);
    window.draw(foreground);
}