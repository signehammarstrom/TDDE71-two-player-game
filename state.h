#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include "slope.h"

class State
{
public:
    
    virtual ~State() = default;

    virtual void handle(sf::Event event) = 0;
    virtual void update(sf::Time delta) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    
}; 

class Game_State : public State
{
public:

    Game_State();
    
    void handle(sf::Event event) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

    Slope* left_slope{};
    Slope* right_slope{};
};


class Menu_State : public State
{
public:

    Menu_State();
    
    void handle(sf::Event event) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;
    
};


#endif