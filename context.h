#ifndef CONTEXT_H
#define CONTEXT_H

#include <SFML/Graphics.hpp>
#include <vector>



class Game_Object;  //måste fördeklarera

struct Context
{

    std::vector<Game_Object*> mod_lst{};
    Game_Object* player;
    Game_Object* goal;
    std::vector<Game_Object*> snowball_lst{}; //aktiva snöbollar
    std::vector<Game_Object*> active_temp_mods{}; //aktiva temporary_modifiers

    double y_speed {};

    double base_speed{};

    double prev_speed{};

    bool side {}; // true ger vänster

    sf::Clock clock;

    unsigned int snow_count{};

    bool game_finished{};

    double left_bound{};

    double right_bound{};

    bool is_colliding{};

    int coll_count{};

    sf::Time goal_time{};

    double side_tire_size{};

    bool stuck{};

    sf::Vector2u window_size;

    sf::Clock stuck_clock{};
    sf::Time stuck_time{};


};

#endif
