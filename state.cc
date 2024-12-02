#include <stdexcept>
#include <cmath> // behöver std::sin
#include "state.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>


// GAME_STATE
/*___________________________________________________________________________________________________________*/
Game_State::Game_State(sf::RenderWindow& window)
: left_slope{new Slope(true)}, right_slope{new Slope(false)}, window {window}
{
    if (!font.loadFromFile("font.ttf"))
    {
        throw std::runtime_error("Kan inte öppna: font.ttf");
    }

    // BAKGRUND
    window_size = window.getSize();

    p2_text.setFont(font);
    p2_text.setString("SPELARE 2 VINNER!!!");
    p2_text.setFillColor(sf::Color(255, 20, 147));
    sf::FloatRect p2_text_bounds {p2_text.getGlobalBounds()};
    p2_text.setOrigin(p2_text_bounds.width / 2, p2_text_bounds.height / 2);
    p2_text.setPosition(window_size.x / 2, window_size.y / 2);

    p1_text.setFont(font);
    p1_text.setString("SPELARE 1 VINNER!!!");
    p1_text.setFillColor(sf::Color(255, 20, 147));
    sf::FloatRect p1_text_bounds {p1_text.getGlobalBounds()};
    p1_text.setOrigin(p1_text_bounds.width / 2, p1_text_bounds.height / 2);
    p1_text.setPosition(window_size.x / 2, window_size.y / 2);
}

Game_State::~Game_State()
{
    delete left_slope;
    delete right_slope;
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
            
            if (left_slope->context.game_finished && right_slope->context.game_finished 
            && event.key.code == sf::Keyboard::Enter)
            {
                delete stack.top();
                stack.pop();
                /*delete left_slope;
                delete right_slope;
                delete stack.top();
                stack.pop();
                stack.push(new Menu_State{window});*/
            }
        }

}

void Game_State::update(sf::Time delta)
{
    
    if(left_slope->context.game_finished == false || right_slope->context.game_finished == false)
    {
        left_slope->update(delta);
        right_slope->update(delta);
        //sf::Time left_time =  left_slope->context.goal_time;
        //sf::Time right_time = right_slope->context.goal_time;
    }
}

void Game_State::render(sf::RenderWindow& window)
{
    sf::Vector2u const window_size { window.getSize() };
    
    left_slope->render(window);
    right_slope->render(window);

    if (left_slope->context.game_finished && right_slope->context.game_finished)
    {   
        sf::Sprite background;
        sf::Texture texture_background;

        texture_background.loadFromFile("background.png");
        background.setTexture(texture_background);

        window.draw(background);

        if ( left_slope->context.goal_time < right_slope->context.goal_time )
        {
            window.draw(p1_text);
        }
        else
        {
            window.draw(p2_text);
        }
    }


}

// MENU_STATE
/*___________________________________________________________________________________________________________*/
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
    if (!texture_background.loadFromFile("background.png"))
    {
        throw std::runtime_error("Kan inte öppna: background.png");
    }
    /*if (!menu_texture.loadFromFile("background.png"))
    {
        throw std::runtime_error("Kan inte öppna: background.png");
    }*/



    // BAKGRUND
    window_size = window.getSize();

    texture_background.loadFromFile("background.png");
    background.setTexture(texture_background);

    // Y6 logo
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);
    
    // Menyalternativ
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Blue);
    menu[0].setString("PLAY");
    sf::FloatRect play_bounds { menu[0].getGlobalBounds() };
    menu[0].setOrigin(play_bounds.width / 2, play_bounds.height / 2);
    menu[0].setPosition(window_size.x / 2, window_size.y * 1 / 4);

    //menu_background[0].setTexture(menu_texture);
    //menu_background[0].setPosition(window_size.x / 2, window_size.y * 1 / 4);
    //menu_background[0].setTextureRect(sf::IntRect(0, 0, play_bounds.width + 10, play_bounds.height + 10));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::Black);
    menu[1].setString("CONTROLS");
    sf::FloatRect control_bounds { menu[1].getGlobalBounds() };
    menu[1].setOrigin(control_bounds.width / 2, control_bounds.height / 2);
    menu[1].setPosition(window_size.x / 2, window_size.y / 2);

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::Black);
    menu[2].setString("HIGHSCORE");
    sf::FloatRect highscore_bounds { menu[2].getGlobalBounds() };
    menu[2].setOrigin(highscore_bounds.width / 2, highscore_bounds.height / 2);
    menu[2].setPosition(window_size.x / 2, window_size.y * 3 / 4 );

    selected_menu = 0;

    // Pulserande text
    text.setFont(font);
    text.setString("Press <Enter> to start!");
    text.setFillColor(sf::Color(0, 255, 255));
    
    // Överskrift
    header.setFont(font);
    header.setString("EPIC HARDCORE VSR SIMULATOR");
    header.setFillColor(sf::Color(255, 20, 147));

    sf::Vector2u texture_size { texture.getSize() };
    sf::FloatRect text_bounds { text.getGlobalBounds() };
    sf::FloatRect header_bounds { header.getGlobalBounds()};

    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    sprite.setPosition(4 * window_size.x / 5, window_size.y / 5);
        
    text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
    text.setPosition(window_size.x / 2, window_size.y * 3 / 8);

    header.setOrigin(header_bounds.width / 2, header_bounds.height / 2);
    header.setPosition(window_size.x / 2, window_size.y / 8);
}


void Menu_State::move_up()
{
    if (selected_menu - 1 >= 0)
    {
        menu[selected_menu].setFillColor(sf::Color::Black);

        selected_menu--;
        if (selected_menu == -1)
        {
            selected_menu = 3;
        }
        menu[selected_menu].setFillColor(sf::Color::Blue);
    }
}

void Menu_State::move_down()
{
    if (selected_menu + 1 <= Max_Menu)
    {
        menu[selected_menu].setFillColor(sf::Color::Black);

        selected_menu++;
        if (selected_menu == 3)
        {
            selected_menu = 0;
        }
        menu[selected_menu].setFillColor(sf::Color::Blue);
    }
}

void Menu_State::handle(sf::Event event, std::stack<State*>& stack )
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Enter && selected_menu == 0)
        {
            stack.push(new Game_State{window});
        }
        if (event.key.code == sf::Keyboard::Key::Enter && selected_menu == 1)
        {
            stack.push(new Controls{window});
        }
        if (event.key.code == sf::Keyboard::Key::Enter && selected_menu == 2)
        {
            stack.push(new Highscore{window});
        }
        if (event.key.code == sf::Keyboard::Key::Down)
        {
            move_down();
        }
        if (event.key.code == sf::Keyboard::Key::Up)
        {
            move_up();
        }
    }

}

void Menu_State::update(sf::Time delta) //, std::stack<State*>& stack)
{
    elapsed_time += delta.asSeconds();

    // Periodiciteten för texten ska vara 1.5 sek
    float const period { 1.0f };

    // Omskalningsfaktorn ska vara i intervallet [0.9, 1.1], 
    // använder sin för det periodiska beteendet.
    // ANM: std::sin() använder radianer medan SFML använder grader.

    double const scalar { 1.0 + 0.1*sin( (2 * M_PI) * elapsed_time / period) };
    text.setScale(scalar, scalar);
}

void Menu_State::render(sf::RenderWindow& window)
{
    window.draw(background);
    for (int i = 0; i < Max_Menu ; ++i)
    {
        //window.draw(menu_background[0]);
        window.draw(menu[i]);
    }
    if ( selected_menu == 0 )
    {
        window.draw(text);
    }
    
    window.draw(header);
    window.draw(sprite);
}

// HIGHSCORE
/*___________________________________________________________________________________________________________*/
Highscore::Highscore(sf::RenderWindow& window)
    :  Menu_State{window}
{
    std::vector<std::string> highscores {read_highscore()};

    for (int i = 0; i < highscores.size() ; ++i)
    {
        score[i].setFont(font);
        score[i].setFillColor(sf::Color::Black);
        score[i].setString(highscores.at(i));
        sf::FloatRect bounds { score[i].getGlobalBounds() };
        score[i].setOrigin(bounds.width / 2, bounds.height / 2);
        score[i].setPosition(window_size.x / 2, window_size.y * 1 / 7 * (i + 1));
    }

    instruction.setFont(font);
    instruction.setString("Tryck 'esc' för att gå tillbaka");
    instruction.setFillColor(sf::Color(255, 20, 147));

    sf::FloatRect instruction_bounds {instruction.getGlobalBounds()};

    instruction.setOrigin(instruction_bounds.width / 2, instruction_bounds.height / 2);
    instruction.setPosition(window_size.x / 2, window_size.y / 12);
}

void Highscore::handle(sf::Event event, std::stack<State*>& stack)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Escape)
        {
            delete stack.top();
            stack.pop();
        }
    }
}

void Highscore::update(sf::Time delta)
{

}

void Highscore::render(sf::RenderWindow& window)
{
    window.draw(background);

    for (int i = 0; i < 6 ; ++i)
    {
        window.draw(score[i]);
    }

    window.draw(instruction);
}

std::vector<std::string> Highscore::read_highscore()
{
    std::ifstream file("highscore.txt");
    std::vector<std::string> scores;

    if (!file)
    {
        throw std::runtime_error("Kan inte öppna: highscore.txt");
    }

    std::string score;
    while (std::getline(file, score))
    {
        scores.push_back(score);
    }

    file.close();
    return scores;
}

void Highscore::sort_highscores(std::vector<std::string>) const
{
}


// CONTROLS
/*___________________________________________________________________________________________________________*/
Controls::Controls(sf::RenderWindow& window)
    :  Menu_State{window}
{
    instruction.setFont(font);
    instruction.setString("Tryck 'esc' för att gå tillbaka");
    instruction.setFillColor(sf::Color(255, 20, 147));

    sf::FloatRect instruction_bounds {instruction.getGlobalBounds()};

    instruction.setOrigin(instruction_bounds.width / 2, instruction_bounds.height / 2);
    instruction.setPosition(window_size.x / 2, window_size.y / 12);
}

void Controls::handle(sf::Event event, std::stack<State*>& stack)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Escape)
        {
            delete stack.top();
            stack.pop();
        }
    }
}

void Controls::update(sf::Time delta)
{

}

void Controls::render(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(instruction);
}
