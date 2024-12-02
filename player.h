#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"
#include <SFML/Graphics.hpp>
#include "context.h"


class Player : public Game_Object
{
public:
    Player(double xpos, double ypos, float scale = 0.05, std::string filename = "skier.png"); //x och ypos behövs inte!!
                                                        //ändra sen så den tar fil som inparameter!!
    ~Player() = default;

    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;
    void render(sf::RenderWindow& window) override;
    void throw_snowball();
    void perform_collision(Game_Object* const& other, Context& context) override;
    double get_width() const;
    double get_height() const;
    bool out_of_bounds(Context const& context);
    sf::FloatRect bounds() const;
    float get_position() const override;
    void stop_effect(Game_Object*& object) override;

private:
   double height{};
   double width{};
    sf::Vector2f old_position{};
    float x_speed;
};

#endif