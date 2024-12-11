

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "game_object.h"
#include "modifier.h"
#include "static_obstacle.h"
#include "moving_object.h"
#include "temporary_modifier.h"
#include "player.h"
#include "snowball_projectile.h"



unsigned const screen_width  { 800 };
unsigned const screen_height { 800 };

void handle(sf::Event event, Context& context);
void render(sf::RenderWindow& window, Context& context);
void update(sf::Time delta, Context& context);

int main()
{
    sf::RenderWindow window { sf::VideoMode { screen_width,
                                              screen_height },
                              "playertest" };

    Context context {};
    context.y_speed = 300;                        
    sf::Vector2u window_size { window.getSize() };
    context.side = false;
    context.side_tire_size = 0;
    context.left_bound = 0;
    context.right_bound = 640;
    context.snow_count = 3;

    context.player = new Player(window_size.x/2, window_size.y/6, 200);
    context.mod_lst.push_back(new Tire(window_size.x/2, window_size.y, 200));
    context.mod_lst.push_back(new Tire(window_size.x/2, window_size.y+100, 200));

    context.mod_lst.push_back(new Tire(window_size.x/6, 3*window_size.y, 200));
    context.mod_lst.push_back(new Tire(3*window_size.x/6, 3*window_size.y, 200));
    context.mod_lst.push_back(new Tire(2*window_size.x/6, 3*window_size.y, 200));
    context.mod_lst.push_back(new Tire(4*window_size.x/6, 3*window_size.y, 200));
    context.mod_lst.push_back(new Tire(5*window_size.x/6, 3*window_size.y, 200));

    sf::Clock clock;    
    while (window.isOpen())
    {
        sf::Time frame_duration { clock.restart() };
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            handle(event, context);
        }  


        update(frame_duration, context);
        
        window.clear();
        render(window, context);
        
        window.display();
    }
    
}

void handle(sf::Event event, Context& context)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Down)
        {
            Player* player = dynamic_cast<Player*>(context.player);
            player->handle(event, context);
            player = nullptr;
        }
    }
}

void update(sf::Time delta, Context& context)
{   
    if (!context.game_finished)
    {
        if (context.y_speed == 0)
        {
            if (context.stuck_time.asSeconds() == 0)
            {
                context.stuck_clock.restart();
            }
            context.stuck_time = context.stuck_clock.getElapsedTime();
            if (context.stuck_time.asSeconds() > 3)
            {
                context.stuck = true;
                context.stuck_clock.restart();
            }
        }
        else
        {
            context.stuck_clock.restart();
            context.stuck_time = sf::Time{};

        }
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
                context.y_speed = context.prev_speed;
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
                    snowball_projectile -> perform_collision(obstacle,context);
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
                context.mod_lst.back() = nullptr;
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
                context.snowball_lst.back() = nullptr;
                context.snowball_lst.pop_back();
            }
        }

        //Ta bort inaktuella temporary modifiers

        if(context.active_temp_mods.size() != 0)
        {
            for(unsigned int i = 0; i<context.active_temp_mods.size(); i++)
            {
                Temporary_Modifier* tempmodtest = dynamic_cast<Temporary_Modifier*>(context.active_temp_mods.at(i));
                if (tempmodtest)
                {
                    tempmodtest -> remove_if_inactual(context);
                    tempmodtest -> update_time(delta);
                }

                if(context.active_temp_mods.at(i) -> is_removed())
                {
                    Player* player = dynamic_cast<Player*>(context.player);
                    player->stop_effect(context.active_temp_mods.at(i), context);
                    player = nullptr;

                    std::swap(context.active_temp_mods.at(i), context.active_temp_mods.back());
                    context.active_temp_mods.back() = nullptr;
                    context.active_temp_mods.pop_back();
                }
                tempmodtest = nullptr;

            }
        }

        context.player->update(delta, context);

        for( Game_Object* snowball : context.snowball_lst)
        {
            snowball->update(delta, context);
        }

        for(Game_Object* modifier : context.mod_lst)
        {
            modifier -> update(delta, context); //Här försöker vi uppdatera ett objekt som jag tagit bort via active_temp_mods
        }
    }

}


void render(sf::RenderWindow& window, Context& context)
{
    context.player -> render(window);
    for( Game_Object* snowball : context.snowball_lst)
    {
        snowball->render(window);
    }

    for(Game_Object* modifier : context.mod_lst)
    {
        modifier -> render(window);
    }
}