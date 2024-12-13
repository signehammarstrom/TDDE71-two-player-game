#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <map>


#include "slope.h"
#include "slope_objects.h"
#include "game_object.h"
#include "player.h"
#include "modifier.h"
#include "static_obstacle.h"
#include "moving_object.h"
#include "temporary_modifier.h"


using namespace std;

Slope::Slope(bool side, map<string, vector<float>>& constantMap, sf::RenderWindow& window)
    :context{}, snow_text{nullptr}, background{nullptr}, progress_bar{nullptr}
{
    initialize_context(side, window);
    read_track(context, constantMap);

    snow_text =  new Snow_Text(context);
    background = new Background(context);
    progress_bar = new Progress_Bar(context);

};

void Slope::delete_vector(std::vector<Game_Object*>& object_vector, bool del)
{
    for (Game_Object*& object : object_vector)
    {
        if (del)
        {
            delete object;
        }
        object = nullptr;
    }
    object_vector.clear();
}

Slope::~Slope()
{
    delete context.player;
    context.player = nullptr;
    context.goal = nullptr;
    delete_vector(context.active_temp_mods, false);
    delete_vector(context.mod_lst);
    delete_vector(context.snowball_lst);
        delete snow_text;
        snow_text = nullptr;
        delete background;
        background = nullptr;
        delete progress_bar;
        progress_bar = nullptr;
}


void Slope::handle(sf::Event event)
{
    if (!context.game_finished)
    {
        Player* player = dynamic_cast<Player*>(context.player);
        player->handle(event, context);
        player = nullptr;
    }
}

void Slope::update(sf::Time delta)
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

        snow_text->update(context);
        progress_bar->update(context.player, context.goal);
        background ->update(delta, context);
    }

}


void Slope::render(sf::RenderWindow& window)
{
    background ->render(window);
    context.player->render(window);

    for( Game_Object* snowball : context.snowball_lst)
    {
        snowball->render(window);
    }

    for(Game_Object* modifier : context.mod_lst)
    {
        modifier -> render(window);
    }

    snow_text->render(window);
    progress_bar->render(window);
}

void Slope::initialize_context(bool side, sf::RenderWindow& window)
{
    context.window_size = window.getSize();
    if (side)
    {
        context.left_bound = 0;
        context.right_bound = context.window_size.x/2;
    }
    else
    {
        context.left_bound = context.window_size.x/2;
        context.right_bound = context.window_size.x;
    }

    string line {};
    ifstream info_file {"context.txt"};
    if (!info_file.is_open())
    {
        throw runtime_error{"context.txt couldn't be opened!"};
    }
    else 
    {
        while ( getline (info_file, line))
        {
            string info_name {""};
            float variable {0};

            istringstream info(line);
            info >> info_name >> variable;

            if (!info.fail())
            {
                info.clear();
            }
            if(info_name == "Snow_count:")
            {
                context.snow_count = variable;
            }
            if(info_name == "Player_size:")
            {
                context.player = new Player{(context.left_bound + 
                    context.right_bound)/2, static_cast<double>(context.window_size.y)/6, variable, context.window_size};
            }
            if(info_name == "Y_speed:")
            {
                context.y_speed = variable;
            }
            if(info_name == "Side_tire_size:")
            {
                context.side_tire_size = variable;
            }
        }
        info_file.close();

    context.base_speed = context.y_speed;
    context.prev_speed = context.y_speed;
    context.side = side;
    context.game_finished = false;
    context.is_colliding = false;
    context.coll_count = 0;
    }
}

void Slope::read_track(Context& context,  map<std::string, std::vector<float>>& constantMap)
{
    string line {};
    ifstream trackinfo_file {"track.txt"};
    if (!trackinfo_file.is_open())
    {
        throw runtime_error{"track.txt couldn't be opened!"};
    }
    else 
    {
        while ( getline (trackinfo_file, line))
        {
            string modifier_name {};
            int modifier_xpos{};
            int modifier_ypos{};

            istringstream modifierinfo(line); 
            modifierinfo >> modifier_name >> modifier_xpos>> modifier_ypos;
            if (modifier_name == "Tire")
            {
                context.mod_lst.push_back(new Tire(modifier_xpos + context.left_bound, modifier_ypos, constantMap[modifier_name].at(0), context.window_size));
            }
            else if (modifier_name == "Goal")
            {
                context.mod_lst.push_back(new Goal(modifier_xpos + context.left_bound, modifier_ypos, (context.right_bound-context.left_bound), context.window_size));
                context.goal = context.mod_lst.back();
            }
            else if (modifier_name == "Hole")
            {
                context.mod_lst.push_back(new Hole(modifier_xpos + context.left_bound, modifier_ypos, constantMap[modifier_name].at(0), context.window_size));
            }
            else if (modifier_name == "Chalmerist")
            {
                context.mod_lst.push_back(new Chalmerist(modifier_xpos + context.left_bound, modifier_ypos, constantMap[modifier_name].at(0), constantMap[modifier_name].at(2), constantMap[modifier_name].at(3), context.window_size));
            }
            else if (modifier_name == "Kir")
            {
                context.mod_lst.push_back(new Kir(modifier_xpos + context.left_bound, modifier_ypos, constantMap[modifier_name].at(0), constantMap[modifier_name].at(2), constantMap[modifier_name].at(3), context.window_size));
            }
            else if (modifier_name == "Can")
            {
                context.mod_lst.push_back(new Can(modifier_xpos+ context.left_bound, modifier_ypos, constantMap[modifier_name].at(0), constantMap[modifier_name].at(2), constantMap[modifier_name].at(3), context.window_size));
            }
            else if (modifier_name == "Snowball")
            {
                context.mod_lst.push_back(new Snowball_Mod(modifier_xpos+ context.left_bound, modifier_ypos, constantMap[modifier_name].at(0), constantMap[modifier_name].at(2), context.window_size));
            }
       }
       trackinfo_file.close();
    }

}


