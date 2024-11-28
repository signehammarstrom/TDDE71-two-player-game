#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"
#include <SFML/Graphics.hpp>
#include "context.h"


class Player : public Game_Object
{
public:
    Player(double xpos, double ypos, Context context); //x och ypos behövs inte!!
                                                        //ändra sen så den tar fil som inparameter!!
    ~Player() = default;

    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;
    void render(sf::RenderWindow& window) override;
    void throw_snowball();
    void perform_collision(Game_Object* const& other) override;
    double get_width() const;
    double get_height() const;
    bool out_of_bounds(Context const& context);

private:
   double height{};
   double width{};
   sf::Sprite sprite;
   sf::Texture texture;
 
};

#endif