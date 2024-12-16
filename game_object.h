#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include "context.h"

// Sättet kollisionshanteringen är implementerad på, med bounds och collides
// är tagen från föreläsning 8.
// https://gitlab.liu.se/chrho44/tddc76-sfml/-/raw/main/handout_slides.pdf?ref_type=heads

class Game_Object
{
public:
    Game_Object(double xpos, double ypos, float size
        , sf::Vector2u& window_size, std::string& filename);
    virtual ~Game_Object() = default;

    virtual void update(sf::Time delta, Context& context) = 0;
    virtual void perform_collision(Game_Object* const& other, Context& context) = 0;
    void render(sf::RenderWindow& window);
    bool collides(Game_Object* const&) const;
    sf::FloatRect bounds() const;

    bool is_removed() const;
    void remove();
    float get_position() const;

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float scale;
    bool removed;
};

#endif


