#include "context.h"
#include "slope_objects.h"


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