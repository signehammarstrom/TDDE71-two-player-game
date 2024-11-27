#include "state.h"

Game_State::Game_State(sf::RenderWindow& window)
: left_slope{new Slope(true)}, right_slope{new Slope(false)}, window {window}
{

}

void Game_State::handle(sf::Event event, std::stack<State*>& stack)
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
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        left_slope->update(delta);
    }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        right_slope->update(delta);
    }
}

void Game_State::render(sf::RenderWindow& window)
{
    left_slope->render(window);
    right_slope->render(window);
}


Menu_State::Menu_State(sf::RenderWindow& window)
: window {window}
{
    if (!font.loadFromFile("font.ttf"))
    {
        throw std::runtime_error("Kan inte öppna font.ttf!");
    }

    text.setFont(font);
    text.setString("Press <Enter> to start!");

    sf::Vector2u const window_size { window.getSize() };

    sf::FloatRect bounds { text.getGlobalBounds() };
        
    text.setOrigin(bounds.width / 2, bounds.height / 2);
    text.setPosition(window_size.x / 2, window_size.y / 2);
}

void Menu_State::handle(sf::Event event, std::stack<State*>& stack )
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        stack.push(new Game_State{window});
    }
}

void Menu_State::update(sf::Time delta) //, std::stack<State*>& stack)
{

}

void Menu_State::render(sf::RenderWindow& window)
{
    window.draw(text);
}