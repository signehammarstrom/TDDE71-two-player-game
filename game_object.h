#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include "context.h"

class Game_Object
{
public:

    Game_Object(double xpos, double ypos, float radius, std::string filename);
    virtual ~Game_Object() = default;

    virtual bool handle(sf::Event event, Context& context) = 0;
    virtual void update(sf::Time delta, Context& context) = 0;
    void render(sf::RenderWindow& window);
    virtual void perform_collision(Game_Object* const& other, Context& context) = 0;
    bool collides(Game_Object* const&) const;

    sf::FloatRect bounds() const;
    bool is_removed() const;
    void remove();
    virtual float get_position() const;
    virtual void stop_effect(Game_Object*& object);

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    bool removed;
    float scale;

private:

};

#endif


