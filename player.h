#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "context.h"
#include "game_object.h"

class Player : public Game_Object
{
public:
    Player(double xpos, double ypos, float size, sf::Vector2u window_size, 
        std::string filename = "saucer_signe.png", std::string filename2 = "saucerbw_signe.png", 
        std::string filename3 = "saucercolor_signe.png"); 
    ~Player() = default;
    
    void update(sf::Time delta, Context& context) override;
    void perform_collision(Game_Object* const& other, Context& context) override;
    void handle(sf::Event event, Context& context);
    
    bool out_of_bounds(Context const& context);
    void stop_effect(Game_Object*& object, Context const& context);

private:
    float x_speed;
    float snowball_size;
    sf::Vector2f old_position;
    sf::Texture texture2;
    sf::Texture texture3;
};

#endif