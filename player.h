#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"
#include <SFML/Graphics.hpp>
#include "context.h"


class Player : public Game_Object
{
public:
    Player(double xpos, double ypos, std::string filename = "skier.png"); //x och ypos behövs inte!!
                                                        //ändra sen så den tar fil som inparameter!!
    ~Player() = default;

    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;

    void throw_snowball();
    void perform_collision(Game_Object* const& other, Context& context) override;
    double get_width() const;
    double get_height() const;
    bool out_of_bounds(Context const& context);
    sf::FloatRect bounds() const;

private:
   double height{};
   double width{};
 
};

#endif