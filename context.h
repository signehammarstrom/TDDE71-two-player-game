#ifndef CONTEXT_H
#define CONTEXT_H

#include <SFML/Graphics.hpp>
#include <vector>



class Game_Object;  //måste fördeklarera

struct Context
{

    //std::vector<Game_Object*> mod_lst{};
    Game_Object* player;
    //std::vector<Game_Object*> snowball_lst{}; //aktiva snöbollar


    double y_speed {};

    bool side {}; // true ger vänster

    Game_Object* active_mod{};

    sf::Clock clock;

    unsigned int snow_count{};

    bool game_finished{};

    double left_bound{};

    double right_bound{};

};

#endif
