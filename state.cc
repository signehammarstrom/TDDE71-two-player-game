#include "state.h"

Game_State::Game_State()
: left_slope{new Slope(true)}, right_slope{new Slope(false)}
{

}

void Game_State::handle(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Down)
            {
                right_slope->handle(event);
            }
            if (event.key.code == sf::Keyboard::S)
            {
                left_slope->handle(event);
            }
        }

}

void Game_State::update(sf::Time delta)
{

}

void Game_State::render(sf::RenderWindow& window)
{
    left_slope->render(window);
    right_slope->render(window);
}


Menu_State::Menu_State()
{

}

void Menu_State::handle(sf::Event event)
{

}

void Menu_State::update(sf::Time delta)
{

}

void Menu_State::render(sf::RenderWindow& window)
{

}