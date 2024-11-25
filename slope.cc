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

    if (side)
    {
        context.left_bound = 0;
        context.right_bound = 1136/2;
    }

    else
    {
        context.left_bound = 1136/2;
        context.right_bound = 1136;
    }

    context.player = new Player {1,1,1,1, context.left_bound,
                                        context.right_bound, context.side};
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

    context.player->update(delta);


    //Loopa igenom Game_Objects och kolla om nån kolliderar


}


void Slope::render(sf::RenderWindow& window)
{
    //loopa igenom alla object och rita upp dem!!
    context.player->render(window);

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

