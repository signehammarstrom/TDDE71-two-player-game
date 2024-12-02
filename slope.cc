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

    context.player = new Player {1,1, context};
    context.y_speed = 200; 
    context.base_speed = context.y_speed;
    context.is_colliding = false;
    context.coll_count = 0;


    context.mod_lst.push_back(new Hole((context.left_bound+context.right_bound)/2, 1000, 0.1f));
    context.mod_lst.push_back(new Tire ((context.left_bound+context.right_bound)/2, 2000, 0.1f));
    context.mod_lst.push_back(new Goal ((context.left_bound+context.right_bound)/2, 3000, 0.5f));
    context.mod_lst.push_back(new Snowball_Mod ((context.left_bound+context.right_bound)/2, 500, 0.2f, 700));
    context.mod_lst.push_back(new Kir((context.left_bound+context.right_bound)/2, 750, 0.1f, 700, 3));


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
    if (!context.game_finished)
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
}

void Slope::update(sf::Time delta)
{   
    if (!context.game_finished)
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
        for(Game_Object* snowball_projectile : context.snowball_lst)
        {
            if (obstacle -> collides(snowball_projectile))
            {
                obstacle -> perform_collision(snowball_projectile, context);
                snowball_projectile -> perform_collision(obstacle, context);
            }
        }
    }
    //Ta bort inaktuella modifiers
    for (unsigned int i=0; i<context.mod_lst.size(); i++)
    {
        if (context.mod_lst.at(i)->is_removed())
        {
            std::swap(context.mod_lst.at(i), context.mod_lst.back());
            delete context.mod_lst.back(); //Borde vi inte göra nullptr också?
            context.mod_lst.pop_back();
        }
    }
    //Ta bort inaktuella snöbollar
    for (unsigned int i=0; i<context.snowball_lst.size(); i++)
    {
        if (context.snowball_lst.at(i)->is_removed())
        {
            std::swap(context.snowball_lst.at(i), context.snowball_lst.back());
            delete context.snowball_lst.back();
            context.snowball_lst.pop_back();
        }
    }

    //Ta bort inaktuella temporary modifiers
    if(context.active_temp_mods.size() != 0)
    {
        for(unsigned int i=0; i<context.active_temp_mods.size(); i++)
        {
            context.active_temp_mods.at(i)->update_time(delta);
            context.active_temp_mods.at(i)->remove_if_inactual(context);
            if(context.active_temp_mods.at(i)->is_removed())
            {
                std::swap(context.active_temp_mods.at(i), context.active_temp_mods.back());
                //delete context.active_temp_mods.back();
                context.active_temp_mods.pop_back();
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
        modifier -> update(delta, context); //Här försöker vi uppdatera ett objekt som jag tagit bort via active_temp_mods
    }

    //Kolla active_mod och se hur mycket tid som gått, ska vi ändra hastigheten i context??

    }
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

