

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

using namespace std;

unsigned const screen_width  { 800 };
unsigned const screen_height { 800 };

void handle(sf::Event event, Context& context);
void render(sf::RenderWindow& window, Context& context);
void update(sf::Time delta, Context& context);
void initiate_context(Context& context, sf::RenderWindow& window);

int main()
{
    sf::RenderWindow window { sf::VideoMode { screen_width,
                                              screen_height },
                              "playertest" };

    Context context {};
    initiate_context(context, window);

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
                delete context.mod_lst.back();
                context.mod_lst.back() = nullptr;
                context.mod_lst.pop_back();
            }
        }
        //Ta bort inaktuella snöbollar
        for(Game_Object* projectile : context.snowball_lst)
        {
            if(projectile->is_removed())
            {
                swap(projectile, context.snowball_lst.back());
                delete context.snowball_lst.back();
                context.snowball_lst.back() = nullptr;
                context.snowball_lst.pop_back();
            }
        }

        //Ta bort inaktuella temporary modifiers
       
        if(context.active_temp_mods.size() != 0)
        {
            
            for(Game_Object* activemod : context.active_temp_mods)
            {
                Temporary_Modifier* tempmodtest = dynamic_cast<Temporary_Modifier*>(activemod);
                if (tempmodtest)
                {
                    tempmodtest -> remove_if_inactual(context);
                    tempmodtest -> update_time(delta);
                }

                if(activemod -> is_removed())
                {
                    Player* player = dynamic_cast<Player*>(context.player);
                    player->stop_effect(activemod, context);
                    player = nullptr;

                    std::swap(activemod, context.active_temp_mods.back());
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

void initiate_context(Context& context, sf::RenderWindow& window)
{
    context.y_speed = 300;     
    context.base_speed = context.y_speed;
    context.prev_speed = context.y_speed;                   
    sf::Vector2u window_size { window.getSize() };
    context.side = false;
    context.side_tire_size = 0;
    context.left_bound = 0;
    context.right_bound = screen_width;
    context.snow_count = 3;

    context.player = new Player(window_size.x/2, window_size.y/6, 100);
    context.mod_lst.push_back(new Tire(window_size.x/2, window_size.y, 100));
    context.mod_lst.push_back(new Tire(window_size.x/2, window_size.y+100, 100));

    context.mod_lst.push_back(new Tire(window_size.x/6, 3*window_size.y, 100));
    context.mod_lst.push_back(new Tire(3*window_size.x/6, 3*window_size.y, 100));
    context.mod_lst.push_back(new Tire(2*window_size.x/6, 3*window_size.y, 100));
    context.mod_lst.push_back(new Tire(4*window_size.x/6, 3*window_size.y, 100));
    context.mod_lst.push_back(new Tire(5*window_size.x/6, 3*window_size.y, 100));
    context.mod_lst.push_back(new Can(window_size.x/2, 5*window_size.y, 50, 0, 0.5));
    context.mod_lst.push_back(new Tire(window_size.x/6, 5.7*window_size.y, 100));
    context.mod_lst.push_back(new Goal(window_size.x/2, 7*window_size.y, 800));
    
    context.mod_lst.push_back(new Can(window_size.x/2, 7.5*window_size.y, 50, 0, 0.5));

}