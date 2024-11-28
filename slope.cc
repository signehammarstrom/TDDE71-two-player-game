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
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        //move player left
        //skicka in delta och x_speed
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        //Move player right
        //skicka in delta och x_speed
    }


    //Loopa igenom Game_Objects och kolla om nån kolliderar


}


void Slope::render(sf::RenderWindow& window)
{
    //loopa igenom alla object och rita upp dem!!


}



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
