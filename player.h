#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"
#include <SFML/Graphics.hpp>
#include "context.h"


class Player : public Game_Object
{
public:
    Player(double xpos, double ypos, float size = 150, std::string filename = "saucer_signe.png", std::string filename2 = "saucerbw_signe.png", std::string filename3 = "saucercolor_signe.png"); //x och ypos behövs inte!!
    ~Player() = default;

    void handle(sf::Event event, Context& context);
    void update(sf::Time delta, Context& context) override;
    void perform_collision(Game_Object* const& other, Context& context) override;
    bool out_of_bounds(Context const& context);
    void stop_effect(Game_Object*& object, Context const& context);

private:
    sf::Vector2f old_position;
    float x_speed;
    float snowball_size;
    sf::Texture texture2;
    sf::Texture texture3;
};

#endif