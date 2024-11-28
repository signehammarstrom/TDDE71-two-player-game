#include <stdexcept>
#include <cmath> // behöver std::sin
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
        throw std::runtime_error("Kan inte öppna: font.ttf");
    }
    /**/
    else if (!texture.loadFromFile("y6_logo.png"))
    {
        throw std::runtime_error("Kan inte öppna: y6_logo.png");
    }

    // Y6 logo
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);

    // Pulserande text
    text.setFont(font);
    text.setString("Press <Enter> to start!");
    text.setFillColor(sf::Color(0, 255, 255));
    
    // Överskrift
    header.setFont(font);
    header.setString("EPIC HARDCORE VSR SIMULATOR");
    header.setFillColor(sf::Color(255, 20, 147));


    sf::Vector2u const window_size { window.getSize() };

    sf::Vector2u texture_size { texture.getSize() };
    sf::FloatRect text_bounds { text.getGlobalBounds() };
    sf::FloatRect header_bounds { header.getGlobalBounds()};

    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    sprite.setPosition(4 * window_size.x / 5, window_size.y / 5);
        
    text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
    text.setPosition(window_size.x / 2, window_size.y / 2);

    header.setOrigin(header_bounds.width / 2, header_bounds.height / 2);
    header.setPosition(window_size.x / 2, window_size.y / 4);
}

void Menu_State::handle(sf::Event event, std::stack<State*>& stack )
{
    /*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        stack.push(new Game_State{window});
    }
    */
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Enter)
        {
            stack.push(new Game_State{window});
        }
    }
}

void Menu_State::update(sf::Time delta) //, std::stack<State*>& stack)
{
    elapsed_time += delta.asSeconds();

    // Periodiciteten för texten ska vara 1.5 sek
    float const period { 1.0f };

    // Omskalningsfaktorn ska vara i intervallet [0.8, 1.2], 
    // använder sin för det periodiska beteendet.
    // ANM: std::sin() använder radianer medan SFML använder grader.

    double const scalar { 1.0 + 0.1*sin( (2 * M_PI) * elapsed_time / period) };
    text.setScale(scalar, scalar);
}

void Menu_State::render(sf::RenderWindow& window)
{
    window.draw(text);
    window.draw(header);
    window.draw(sprite);
}