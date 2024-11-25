#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"
#include <SFML/Graphics.hpp>


class Player : public Game_Object
{
public:
    Player(double xpos, double ypos, double height, double width,
             double left_bound, double right_bound, bool side);
    ~Player() = default;

    bool handle(sf::Event event) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;
    void throw_snowball();
    void perform_collision(Game_Object const&);
    bool collides(Game_Object const&) const override;
    double get_width() const;
    double get_height() const;
    bool out_of_bounds();

private:
   double height{};
   double width{};
   sf::Sprite sprite;
   sf::Texture texture;
   double side{};
   double left_bound{};
   double right_bound{};
 
};

#endif