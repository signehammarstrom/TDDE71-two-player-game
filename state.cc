#include <stdexcept>
#include <cmath> // behöver std::sin
#include "state.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <random>
#include <time.h>

using namespace std;
#include <sstream>

// STATE
/*___________________________________________________________________________________________________________*/

State::State(sf::RenderWindow& window)
: window {window}
{
    if (!menu_background_texture.loadFromFile("background_signe.png"))
    {
        throw std::runtime_error("Kan inte öppna: background.png");
    }
    if (!font.loadFromFile("gamefont.ttf"))
    {
        throw std::runtime_error("Kan inte öppna: gamefont.ttf");
    }

    menu_background.setTexture(menu_background_texture);
    sf::Vector2u texture_size { menu_background_texture.getSize() };
    float scale {1200.0f/texture_size.x};
    menu_background.setScale(scale, scale);
    window_size = window.getSize();
}

std::vector<std::string> State::read_highscore()
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

Game_over::Game_over(sf::RenderWindow& window, double timeL, double timeR)
    : State{window}, left_time{timeL}, right_time{timeR}, highscores{read_highscore()}
{
    p2_text.setFont(font);
    p2_text.setString("SPELARE 2 VINNER!!!");
    p2_text.setFillColor(sf::Color(255, 20, 147));
    sf::FloatRect p2_text_bounds {p2_text.getGlobalBounds()};
    p2_text.setOrigin(p2_text_bounds.width / 2, p2_text_bounds.height / 2);
    p2_text.setPosition(window_size.x / 2, window_size.y / 4);

    p1_text.setFont(font);
    p1_text.setString("SPELARE 1 VINNER!!!");
    p1_text.setFillColor(sf::Color(255, 20, 147));
    sf::FloatRect p1_text_bounds {p1_text.getGlobalBounds()};
    p1_text.setOrigin(p1_text_bounds.width / 2, p1_text_bounds.height / 2);
    p1_text.setPosition(window_size.x / 2, window_size.y / 4);

    prompt.setFont(font);
    prompt.setString("ENTER NAME:");
    prompt.setFillColor(sf::Color::Black);
    sf::FloatRect prompt_text_bounds {prompt.getGlobalBounds()};
    prompt.setOrigin(prompt_text_bounds.width / 2, prompt_text_bounds.height / 2);
    prompt.setPosition(window_size.x / 2, window_size.y / 2);

    typed_name.setFont(font);
    typed_name.setString("");
    typed_name.setFillColor(sf::Color::Black);
    sf::FloatRect typed_text_bounds {typed_name.getGlobalBounds()};
    typed_name.setOrigin(typed_text_bounds.width / 2, typed_text_bounds.height / 2);
    typed_name.setPosition(window_size.x / 2 + prompt_text_bounds.width / 2 + 5, window_size.y / 2 );

    check_highscore();

}

void Game_over::handle(sf::Event event, stack<State*>& stack)
{   
    if ( new_highscore )
    {
        if (event.type == sf::Event::TextEntered) 
        {
            if (event.text.unicode == '\r' || event.text.unicode == '\n') 
            {
                sort_highscores();
                delete stack.top();
                stack.pop();
            }
            else if (event.text.unicode == '\b' && !name.empty()) 
            {
                name.pop_back(); // Ta bort sista bokstaven
            }
            else if (event.text.unicode < 128) 
            { 
                name += static_cast<char>(event.text.unicode);
            }
        }
        typed_name.setString(name);
    }
    else
    {
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                delete stack.top();
                stack.pop();
            }
        }
    }
}

void Game_over::check_highscore()
{

    std::istringstream iss {highscores.back()};
    std::string throwaway{};
    double worst_time{};

    if (!(iss >> throwaway >> worst_time))
    {
        if (left_time < right_time)
        {
            new_highscore = true;
            new_highscore_time = left_time;
            cout << "left slope: " << new_highscore_time << endl;
        }
        else if (worst_time > right_time && left_time > right_time)
        {
            new_highscore = true;
            new_highscore_time = right_time;
            cout << "right slope: " << new_highscore_time << endl;
        }
    }
    else
    {
        if (worst_time > left_time && left_time < right_time)
        {
            iss >> throwaway >> worst_time;
            new_highscore = true;
            new_highscore_time = left_time;
            cout << "left slope: " << new_highscore_time << endl;
        }
        else if (worst_time > right_time && left_time > right_time)
        {
            iss >> throwaway >> worst_time;
            new_highscore = true;
            new_highscore_time = right_time;
            cout << "right slope: " << new_highscore_time << endl;
        }
    }
}

void Game_over::update(sf::Time delta)
{
    
}

void Game_over::render(sf::RenderWindow& window)
{
    window_size = window.getSize();

     
    window.draw(menu_background);

    if ( left_time < right_time )
    {
        window.draw(p1_text);
    }
    else
    {
        window.draw(p2_text);
    }
    if (new_highscore)
    {
        window.draw(prompt);
        window.draw(typed_name);
    }
    
}

void Game_over::sort_highscores()
{
    double time {};
    std::string throwaway;
    bool inserted = false;

    for (unsigned int i = 0; i < highscores.size(); i++)
    {
        std::istringstream iss {highscores.at(i)};
        iss >> throwaway >> time; 

        if (time > new_highscore_time && !inserted)
        {
            highscores.insert(highscores.begin() + i, name + " " + std::to_string(new_highscore_time));
            inserted = true;
            if (highscores.size() > 6)
            {
                highscores.pop_back();
            }
            break;
        }
    }

    std::ofstream outFile("highscore.txt");

    if (!outFile)
    {
        throw std::runtime_error("Kan inte öppna: highscore.txt");
    }

    for (unsigned int i = 0; i < highscores.size(); ++i) 
    {
        outFile << highscores[i];
        
        if (i < highscores.size() - 1) 
        {
            outFile << '\n';
        }
    }
    outFile.close();
}

// GAME_STATE
/*___________________________________________________________________________________________________________*/
Game_State::Game_State(sf::RenderWindow& window)
: State{window}, left_slope{new Slope(true)}, right_slope{new Slope(false)}, clock{}, game_started{false}
{
    if (!one.loadFromFile("one.png"))
    {
        throw  runtime_error{"Couldn't open filename"};
    }
    if (!two.loadFromFile("two.png"))
    {
        throw  runtime_error{"Couldn't open filename"};
    }
    if (!three.loadFromFile("three.png"))
    {
        throw  runtime_error{"Couldn't open filename"};
    }

    
    digit.setTexture(three);
    sf::Vector2u texture_size { one.getSize() };
    digit.setOrigin(texture_size.x / 2, texture_size.y / 2);
    digit.setPosition(window_size.x / 2, window_size.y / 2);
    digit.setScale(1.5, 1.5);

    create_track();
}

Game_State::~Game_State()
{
    std::cout << "Game state destruktor körs" << std::endl;
    delete left_slope;
    delete right_slope;
}

void Game_State::handle(sf::Event event, stack<State*>& stack)
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
    
    if (left_slope->context.game_finished && right_slope->context.game_finished)
    {
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                State* wtf {new Game_over{window, left_slope->context.goal_time.asSeconds(), right_slope->context.goal_time.asSeconds()}};
                delete stack.top();
                stack.pop();
                stack.push(wtf);
            }
        }
    }
    
}   


void Game_State::update(sf::Time delta)
{
    if (!game_started)
    {
        if(clock.getElapsedTime().asSeconds() > 3)
        {
            game_started = true;
        }
        else if (clock.getElapsedTime().asSeconds() > 2)
        {
            digit.setTexture(one);
        }
        else if(clock.getElapsedTime().asSeconds() > 1)
        {
            digit.setTexture(two);
        }
    }
    if(game_started)
    {
        if(left_slope->context.game_finished == false || right_slope->context.game_finished == false)
        {
            left_slope->update(delta);
            right_slope->update(delta);
        }
    }
}

void Game_State::render(sf::RenderWindow& window)
{
    window_size = window.getSize();
    
    left_slope->render(window);
    right_slope->render(window);

    if (left_slope->context.game_finished && right_slope->context.game_finished)
    {   
        window.draw(menu_background);
    }
    if (!game_started)
    {
        window.draw(digit);
    }
}

void Game_State::create_track()
{
    srand(time(NULL));
    int track_length {5000};
    int modifier_xpos{};
    int modifier_ypos{500};
    
    vector<string> StatObjs {"Hole", "Tire"};
    vector<string> MovObjs {"Chalmerist", "Kir", "Can", "Snowball"};
    
    ofstream mod_info ("track.txt");
    if (!mod_info.is_open())
    {
        throw runtime_error{"trackinfo_file couldn't be opened!"};
    }
    else
    {
        int x{0};
        for(modifier_ypos = 600; modifier_ypos < (track_length-400); modifier_ypos = modifier_ypos + 100)
        {
            modifier_xpos =  30 + rand()%540;
            modifier_ypos = modifier_ypos + rand()%50;
            mod_info << StatObjs.at(rand()%StatObjs.size()) << ' ' << modifier_xpos << ' ' << modifier_ypos << '\n';
            if (x%4 == 0)
                {
                    int modifier_xpos2{0};
                    modifier_xpos2 = 30 + rand()%540;
                    if (modifier_xpos2 > 540)
                        {
                            modifier_xpos2 - 580;
                        }
                    mod_info << StatObjs.at(rand()%StatObjs.size()) << ' ' << modifier_xpos2 << ' ' << modifier_ypos << '\n';
                }
            x = x + 1;
        }
        for(modifier_ypos = 1000; modifier_ypos < (track_length-100); modifier_ypos = modifier_ypos + 450)
        {
            modifier_xpos =  30 + rand()%540;
            modifier_ypos = modifier_ypos + rand()%100;

            int randValue{};
            randValue = rand() % 100 + 1;

            string selectedObject{};
            if (randValue <= 40) {
                selectedObject = "Can";  // 30% chance for Can
            } else if (randValue <= 65) {
                selectedObject = "Kir";  // 30% chance for Kir
            } else if (randValue <= 85) {
                selectedObject = "Chalmerist";  // 20% chance for Kir
            } else {
                selectedObject = "Snowball";  // 20% chance for Snowball
            }

            mod_info << selectedObject << ' ' << modifier_xpos << ' ' << modifier_ypos << '\n';
        }
    }
    mod_info << "Goal" << " 284" << ' ' << track_length <<'\n';
    mod_info << "Snowball" << " 284" << ' ' << 500 << '\n';

    //skapa random genererade däkc och hål. 
    //hål och däck kommer med ett bestämt avstånd mellan varandra - ex. 300 pts
    //x-koordinat slumpas utifrån context.left_bound() och right_bound()
    //spara i txt-fil.
}


// MENU_STATE
/*___________________________________________________________________________________________________________*/
Menu_State::Menu_State(sf::RenderWindow& window)
: State{window}
{
    if (!texture.loadFromFile("y6_logo.png"))
    {
        throw runtime_error("Kan inte öppna: y6_logo.png");
    }
    if (!texture_buttons.loadFromFile("Charcoal_bricks_color1.png"))
    {
        throw runtime_error("Kan inte öppna: Charcoal_bricks_color1.png");
    }

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

    menu_buttons[0].setTexture(texture_buttons);
    menu_buttons[0].setTextureRect(sf::IntRect(0, 0, play_bounds.width + 40, play_bounds.height + 20));
    sf::FloatRect play_bounds_b { menu_buttons[0].getGlobalBounds() };
    menu_buttons[0].setOrigin(play_bounds_b.width / 2, play_bounds_b.height / 2 - 7);
    menu_buttons[0].setPosition(menu[0].getPosition());
    

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::Black);
    menu[1].setString("CONTROLS");
    sf::FloatRect control_bounds { menu[1].getGlobalBounds() };
    menu[1].setOrigin(control_bounds.width / 2, control_bounds.height / 2);
    menu[1].setPosition(window_size.x / 2, window_size.y / 2);

    menu_buttons[1].setTexture(texture_buttons);
    menu_buttons[1].setTextureRect(sf::IntRect(0, 0, control_bounds.width + 40, control_bounds.height + 20));
    sf::FloatRect control_bounds_b { menu_buttons[1].getGlobalBounds() };
    menu_buttons[1].setOrigin(control_bounds_b.width / 2, control_bounds_b.height / 2 - 7);
    menu_buttons[1].setPosition(menu[1].getPosition());
    

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::Black);
    menu[2].setString("HIGHSCORE");
    sf::FloatRect highscore_bounds { menu[2].getGlobalBounds() };
    menu[2].setOrigin(highscore_bounds.width / 2, highscore_bounds.height / 2);
    menu[2].setPosition(window_size.x / 2, window_size.y * 3 / 4 );

    menu_buttons[2].setTexture(texture_buttons);
    menu_buttons[2].setTextureRect(sf::IntRect(0, 0, highscore_bounds.width + 40, highscore_bounds.height + 20));
    sf::FloatRect highscore_bounds_b { menu_buttons[2].getGlobalBounds() };
    menu_buttons[2].setOrigin(highscore_bounds_b.width / 2 , highscore_bounds_b.height / 2 - 7);
    menu_buttons[2].setPosition(menu[2].getPosition());
    
    

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

void Menu_State::handle(sf::Event event, stack<State*>& stack )
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
    window.draw(menu_background);
    for (int i = 0; i < Max_Menu ; ++i)
    {
        window.draw(menu_buttons[i]);//menu_buttons[0]);
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
    : State{window}
{

    std::vector<std::string> highscores {read_highscore()};

    for (unsigned int i = 0; i < highscores.size() ; ++i)
    {
        score[i].setFont(font);
        score[i].setFillColor(sf::Color::Black);
        score[i].setString(highscores.at(i));
        sf::FloatRect bounds { score[i].getGlobalBounds() };
        score[i].setOrigin(bounds.width / 2, bounds.height / 2);
        score[i].setPosition(window_size.x / 2, window_size.y * 1 / 7 * (i + 1));
    }

    instruction.setFont(font);
    instruction.setString("Press 'esc' to go back");
    instruction.setFillColor(sf::Color(255, 20, 147));
    sf::FloatRect instruction_bounds {instruction.getGlobalBounds()};
    instruction.setOrigin(instruction_bounds.width / 2, instruction_bounds.height / 2);
    instruction.setPosition(window_size.x / 2, window_size.y / 12);
}

void Highscore::handle(sf::Event event, stack<State*>& stack)
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

void Highscore::update([[maybe_unused]]sf::Time delta)
{

}

void Highscore::render(sf::RenderWindow& window)
{
    window.draw(menu_background);

    for (int i = 0; i < 6 ; ++i)
    {
        window.draw(score[i]);
    }

    window.draw(instruction);
}



// CONTROLS
/*___________________________________________________________________________________________________________*/
Controls::Controls(sf::RenderWindow& window)
    :  State{window}
{   
    /*
    if (!white_arrow.loadFromFile("RightArrowBlackWhite-removebg-preview.png"))
    {
        throw std::runtime_error("Kan inte ladda RightArrowBlackWhite.png");
    }
    */

    // Texter
    for ( sf::Text& t : text)
    {
        t.setFont(font);
        t.setFillColor(sf::Color(255, 20, 147));
    }

    text[0].setString("Press 'esc' to go back!"); // Överskrift
    text[1].setString("PLAYER 1");
    text[2].setString("PLAYER 2");

    text[3].setString("Go 'LEFT' / 'RIGHT':"); // Svänga
    text[4].setString("'A' / 'D'");
    text[5].setString("'LeftArrow' / 'RightArrow'");

    text[6].setString("Shoot Snowball:"); // Skjuta
    text[7].setString("'S'");
    text[8].setString("'DownArrow'");

    text[9].setString("PICK-UPS:"); // Modifiers
    text[10].setString("SNOWBALLS - Replenishes snowballs");
    text[11].setString("CAPRICE KIR - Become a speed devil for a short period of time");
    text[12].setString("CAN - Slows you down (littering is not cool!)");
    text[13].setString("CHALMERIST - You dont want to collide with this buffoon...");

    for ( sf::Text& t : text)
    {
        sf::FloatRect t_bounds { t.getGlobalBounds() };
        t.setOrigin(t_bounds.width / 2, t_bounds.height / 2);
    }

    text[0].setPosition( window_size.x / 2, 1 * window_size.y  / 10); // Överskrift
    text[1].setPosition(3 * window_size.x / 10, 1.5 * window_size.y / 10);
    text[2].setPosition(7 * window_size.x / 10, 1.5 * window_size.y / 10);

    text[3].setPosition(1 * window_size.x / 10, 3.5 * window_size.y / 10); // Svänga
    text[4].setPosition(4 * window_size.x / 10, 3.5 * window_size.y / 10);
    text[5].setPosition(8 * window_size.x / 10, 3.5 * window_size.y / 10);

    text[6].setPosition(1 * window_size.x / 10, 5.5 * window_size.y / 10); // Skjuta
    text[7].setPosition(4 * window_size.x / 10, 5.5 * window_size.y / 10);
    text[8].setPosition(8 * window_size.x / 10, 5.5 * window_size.y / 10);

    text[9].setPosition(1 * window_size.x / 10, 6.5 * window_size.y / 10); // Modifiers
    text[10].setPosition(1 * window_size.x / 10, 7 * window_size.y / 10);
    text[11].setPosition(1 * window_size.x / 10, 7.5 * window_size.y / 10);
    text[12].setPosition(1 * window_size.x / 10, 8 * window_size.y / 10);
    text[13].setPosition(1 * window_size.x / 10, 8.5 * window_size.y / 10);

    /*
    // Instruktionsöverskrift
    instruction.setFont(font);
    //instruction.setString("Press 'esc' to go back");
    instruction.setFillColor(sf::Color(255, 20, 147));
    sf::FloatRect instruction_bounds {instruction.getGlobalBounds()};
    instruction.setOrigin(instruction_bounds.width / 2, instruction_bounds.height / 2);
    instruction.setPosition(window_size.x / 2, window_size.y / 12);
    


    // Sprites
    sf::Vector2u arrow_size { white_arrow.getSize() };
    // double scale { arrow_size.x / 500 };

    down_arrow.setTexture(white_arrow);
    down_arrow.setOrigin(arrow_size.x / 2, arrow_size.y / 2);
    down_arrow.setPosition(2 * window_size.x / 4, window_size.y / 2);
    down_arrow.rotate(90);
    down_arrow.setScale(0.4f, 0.4f);
    
    left_arrow.setTexture(white_arrow);
    left_arrow.setOrigin(arrow_size.x / 2, arrow_size.y / 2);
    left_arrow.setPosition(3 * window_size.x / 4, window_size.y / 2);
    left_arrow.rotate(180);

    right_arrow.setTexture(white_arrow);
    right_arrow.setOrigin(arrow_size.x / 2, arrow_size.y / 2);
    right_arrow.setPosition(4 * window_size.x / 4, window_size.y / 2);
    */
}

void Controls::handle(sf::Event event, stack<State*>& stack)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Escape)
        {
            delete stack.top();
            stack.pop();
        }
        /*
        else if (event.key.code == sf::Keyboard::Key::Right)
        {
            arrow.setTexture(green_arrow);
        }
        */
    }
}

void Controls::update([[maybe_unused]]sf::Time delta)
{

}

void Controls::render(sf::RenderWindow& window)
{
    window.draw(menu_background);
    for ( sf::Text t : text )
    {
        window.draw(t);
    }
    // window.draw(down_arrow);
    // window.draw(left_arrow);
    // window.draw(right_arrow);
}
