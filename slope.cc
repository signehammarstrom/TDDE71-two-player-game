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
    context.base_speed = context.y_speed;
    context.is_colliding = false;
    context.coll_count = 0;


    context.mod_lst.push_back(new Hole((context.left_bound+context.right_bound)/2, 600, 0.1f));
    context.mod_lst.push_back(new Tire ((context.left_bound+context.right_bound)/2, 1200, 0.1f));
    context.mod_lst.push_back(new Goal ((context.left_bound+context.right_bound)/2, 3000, 0.5f));


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

    for( Game_Object* snowball : context.snowball_lst)
    {
        snowball->handle(event, context);
    }

    for(Game_Object* modifier : context.mod_lst)
    {
        modifier -> handle(event, context);
    }
}

void Slope::update(sf::Time delta)
{   
    context.coll_count = 0;
    for (Game_Object* obstacle : context.mod_lst)
    {
        if (obstacle -> collides(context.player))
        {
            obstacle -> perform_collision(context.player, context);
            context.player -> perform_collision(obstacle, context);
        }
    }
    //Kollar om vi kommer från att ha kolliderat till att inte längre kollidera
    if(context.coll_count == 0)
    {
        if(context.is_colliding == true)
        {
            context.y_speed = context.base_speed;
            context.is_colliding = false;
        }
    }

    for (Game_Object* obstacle : context.mod_lst)
    {
        for(unsigned int i=0; i<context.snowball_lst.size(); i++)
        {
            if (obstacle -> collides(context.snowball_lst[i]))
            {
                obstacle -> perform_collision(context.snowball_lst[i], context);
                context.snowball_lst[i] = nullptr;
                std::swap(context.snowball_lst.at(i), context.snowball_lst.back());
                context.snowball_lst.pop_back();
            }
        }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        if (context.side)
        {
            context.player->update(delta, context);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if (!context.side)
        {
            context.player->update(delta, context);
        }
    }

    for( Game_Object* snowball : context.snowball_lst)
    {
        snowball->update(delta, context);
    }

    for(Game_Object* modifier : context.mod_lst)
    {
        modifier -> update(delta, context);
    }

    //Kolla active_mod och se hur mycket tid som gått, ska vi ändra hastigheten i context??


}


void Slope::render(sf::RenderWindow& window)
{
    //loopa igenom alla object och rita upp dem!!
    context.player->render(window);

    for( Game_Object* snowball : context.snowball_lst)
    {
        snowball->render(window);
    }

    for(Game_Object* modifier : context.mod_lst)
    {
        modifier -> render(window);
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

