#include <vector>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>

#include "slope.h"
#include "game_object.h"
#include "modifier.h"
#include "static_obstacle.h"
#include "moving_object.h"
#include "temporary_modifier.h"


Slope::Slope(bool side)
    :context{}
{
    context.side = side;
    context.snow_count = 3;
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

    context.player = new Player {1,1, context};
    context.y_speed = 300; 


    context.mod_lst.push_back(new Hole(70, 400, 100));
    context.mod_lst.push_back(new Tire (1000, 300, 50));
    context.mod_lst.push_back(new Goal (1000, 300, 50, 60));


/*
    if (!font.loadFromFile("font.ttf"))
    {
        throw std::runtime_error { "Kan inte öppna: font.ttf" };
    }

    text.setFont(font);

    std::string snow_text{"Snowball count: " + std::to_string(context.snow_count)};
    text.setString(snow_text);

    sf::FloatRect bounds { text.getGlobalBounds() };
    
    text.setOrigin(bounds.width / 2, bounds.height / 2);
    text.setPosition(context.left_bound/ 2, context.right_bound/2);
    */
};


void Slope::handle(sf::Event event)
{
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down )
    {
        context.player->handle(event, context);
    }
}

void Slope::update(sf::Time delta)
{   

    context.player->update(delta, context);

    for (unsigned int i=0;i<context.snowball_lst.size();i++)
    {
        context.snowball_lst[i]->update(delta, context);
    }
    for (unsigned int i=0;i<context.mod_lst.size();i++)
    {
        context.mod_lst[i]->update(delta, context);
    }


    for (Game_Object* obstacle : context.mod_lst)
        if (obstacle -> collides(context.player))
        {
            obstacle -> perform_collision(context.player);
            context.player -> perform_collision(obstacle);
        }

    for (Game_Object* obstacle : context.mod_lst)
        for(Game_Object* projectile : context.snowball_lst)
            if (obstacle -> collides(projectile))
            {
                obstacle -> perform_collision(projectile);
                projectile -> perform_collision(obstacle);
            }
        
    //Loopa igenom Game_Objects och kolla om nån kolliderar

    //Kolla active_mod och se hur mycket tid som gått, ska vi ändra hastigheten i context??


}


void Slope::render(sf::RenderWindow& window)
{
    //loopa igenom alla object och rita upp dem!!
    context.player->render(window);

    for (unsigned int i=0;i<context.snowball_lst.size();i++)
    {
        context.snowball_lst[i]->render(window);
    }

    for (unsigned int i=0;i<context.mod_lst.size();i++)
    {
        context.mod_lst[i]->render(window);
    }

    //window.draw(text);

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

