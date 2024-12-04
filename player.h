#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"
#include <SFML/Graphics.hpp>
#include "context.h"


class Player : public Game_Object
{
public:
    Player(double xpos, double ypos, float scale = 0.05, std::string filename = "skier.png", std::string filename2 = "skier_bw.png", std::string filename3 = "skier_saturated.png"); //x och ypos behövs inte!!
    ~Player() = default;

    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;
    void perform_collision(Game_Object* const& other, Context& context) override;
    bool out_of_bounds(Context const& context);
    float get_position() const override;
    void stop_effect(Game_Object*& object) override;

private:
    sf::Vector2f old_position{};
    float x_speed;
    sf::Texture texture2{};
    sf::Texture texture3{};
};

#endif