#include <vector>
#include "game_object.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include "slope.h"


Slope::Slope(bool side)
    :context{}
{
    context.side = side;
    context.snow_count = 0;
    context.game_finished = false;
    read_track();
};


void Slope::handle(sf::Event event)
{
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down )
    {
        // Kasta snöboll
    }
}

void Slope::update(sf::Time delta)
{}


void Slope::render(sf::RenderWindow& window)
{}



void Slope::read_track()
{
    std::ifstream ifs {"track.txt"};
    ifs >> context.y_speed;
    //Loopa igenom resten å lägg in i Game_Objects.
    //För varje rad i filen
    //Typ av objekt, var den är
    //Skapa instans av Objektet - skicka in koordinater
    //Lägg in i en lista.
}
