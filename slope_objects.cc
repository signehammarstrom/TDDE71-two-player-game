#include <SFML/Graphics.hpp>
#include <iostream>
#include "context.h"
#include "slope_objects.h"
#include "player.h"
#include "static_obstacle.h"

using namespace std;

//Snow_Text
/*_______________________________________________________________________________________*/
Snow_Text::Snow_Text(Context& context)
    :font{}, text{}
{
    if (!font.loadFromFile("gamefont.ttf"))
    {
        throw runtime_error { "Kan inte öppna: gamefont.ttf" };
    }

    text.setFont(font);
    
    string snow_text{"Snowball count: " + to_string(0)};
    text.setString(snow_text);
    text.setFillColor(sf::Color(255, 20, 147));
    text.setPosition(context.left_bound, 0);
}
void Snow_Text::update(Context& context)
{
    text.setString("Snowball count: " + to_string(context.snow_count));
}
void Snow_Text::render(sf::RenderWindow& window)
{
    window.draw(text);
}


//Background
/*_______________________________________________________________________________________*/
Background::Background(Context& context)
    :texture_background{}, backgrounds{}

{
    if(context.side) 
    {
        if (!texture_background.loadFromFile("leftlane_signe.png"))
            {
                throw runtime_error("Kan inte öppna: leftlane_signe.png");
            }
    }
    else
    {
        if (!texture_background.loadFromFile("rightlane_signe.png"))
            {
                throw runtime_error("Kan inte öppna: rightlane_signe.png");
            }
    }
    sf::Sprite bg{};
    for (unsigned int i = 0; i < 3; i++)
    {
        backgrounds.push_back(bg);
    }

    sf::Vector2u texture_size { texture_background.getSize() };
    float scale {((context.window_size.x)/2.0f)/texture_size.x};
    
    set_graphics(scale, context);
}

void Background::set_graphics(float scale, Context const& context)
{
    for(unsigned int i = 0; i < 3; i++)
    {
        sf::Sprite bg {};
        bg.setTexture(texture_background);
        if (i == 0)
        {
            bg.setPosition(context.left_bound, 0);
        }
        else 
        {
            bg.setPosition(context.left_bound, 
                backgrounds.back().getGlobalBounds().top + backgrounds.back().getGlobalBounds().height);
        }
        bg.setScale(scale, scale);
        backgrounds.push_back(bg);
    }
}

void Background::update(sf::Time delta, Context& context) 
{   
    float distance {delta.asSeconds() * context.y_speed};

    for(unsigned int i = 0; i < backgrounds.size(); i++)
    {
        backgrounds.at(i).move({0, -distance});
        if (backgrounds.at(i).getGlobalBounds().top +backgrounds.at(i).getGlobalBounds().height < 0 )
        {
            if (i == 0)
            {
                backgrounds.at(i).setPosition(context.left_bound, 
                    backgrounds.back().getGlobalBounds().top - 10 + backgrounds.back().getGlobalBounds().height );
            }
            else 
            {
                backgrounds.at(i).setPosition(context.left_bound, 
                    backgrounds.at(i-1).getGlobalBounds().top + backgrounds.at(i-1).getGlobalBounds().height);
                
            }
        }
    }
}

void Background::render(sf::RenderWindow& window)
{
    for(sf::Sprite bg : backgrounds)
    {
        window.draw(bg);
    }
}


//Progress_Bar
/*_______________________________________________________________________________________*/
Progress_Bar::Progress_Bar(Context& context)
:  background{}, foreground{}, height{}, total_distance{0}
{
    height = context.window_size.y/3;
    set_graphics(background, context, sf::Color::Black);
    set_graphics(foreground, context, sf::Color::Blue);
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

void Progress_Bar::set_graphics(sf::RectangleShape& graphics, Context const& context, sf::Color color)
{
    graphics.setSize(sf::Vector2f(context.side_tire_size/5.f,height));
    graphics.setFillColor(color);
    graphics.setPosition(context.left_bound + context.side_tire_size, context.window_size.y/6.f);
}