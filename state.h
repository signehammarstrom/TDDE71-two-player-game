#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include "slope.h"
#include <stack>

class State
{
public:
    
    virtual ~State() = default;

    virtual void handle(sf::Event event, std::stack<State*>& stack) = 0;
    virtual void update(sf::Time delta) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

}; 

class Game_State : public State
{
public:

    Game_State(sf::RenderWindow& window);
    
    void handle(sf::Event event, std::stack<State*>& stack) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

    Slope* left_slope{};
    Slope* right_slope{};
private:
    sf::RenderWindow& window;
};


class Menu_State : public State
{
public:

    Menu_State(sf::RenderWindow& window);
    
    void handle(sf::Event event, std::stack<State*>& stack) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;
    
private:
    sf::Font font;
    sf::Text text;
    sf::Text header;
    sf::Texture texture;
    sf::Sprite sprite;

    //  Test för periodicitet
    float elapsed_time { 0.0f };
    sf::RenderWindow& window;

};


#endif