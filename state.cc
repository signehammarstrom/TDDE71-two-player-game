#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <cmath> 
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <map>
#include <sstream>
#include "state.h"

using namespace std;

// State
/*___________________________________________________________________________________________________________*/
State::State(sf::RenderWindow& window)
: window {window}, window_size{window.getSize()}
{
    if (!menu_background_texture.loadFromFile("background_signe.png"))
    {
        throw runtime_error("Kan inte öppna: background.png");
    }
    if (!font.loadFromFile("gamefont.ttf"))
    {
        throw runtime_error("Kan inte öppna: gamefont.ttf");
    }

    set_background();
}

void State::set_background()
{
    menu_background.setTexture(menu_background_texture);
    sf::Vector2u texture_size { menu_background_texture.getSize() };
    float scaleX {window_size.x / static_cast<float>(texture_size.x)};
    float scaleY = {window_size.y / static_cast<float>(texture_size.y)};

    menu_background.setScale(scaleX, scaleY);
    menu_background.setOrigin(texture_size.x / 2.f, texture_size.y / 2.f);
    menu_background.setPosition(window_size.x / 2.f, window_size.y / 2.f);
}

void State::resize_window(sf::Event event)
{
    sf::Vector2u new_size {event.size.width, event.size.height};
    window.setSize(new_size);
    sf::View view {sf::FloatRect(0, 0, event.size.width, event.size.height)};
    window.setView(view);
    window_size = window.getSize();

    set_sprites();
    set_background();
}

vector<string> State::read_highscore()
{
    ifstream file("highscore.txt");
    vector<string> scores;

    if (!file)
    {
        throw runtime_error("Kan inte öppna: highscore.txt");
    }

    string score;
    while (getline(file, score))
    {
        scores.push_back(score);
    }

    file.close();
    return scores;
}


// Game_State
/*___________________________________________________________________________________________________________*/
Game_State::Game_State(sf::RenderWindow& window)
: State{window}, left_slope{}, right_slope{}, settings{}, clock{}, game_started{false}
{
    read_constants();
    create_track();
    left_slope = new Slope(true, settings.constantMap, window);
    right_slope = new Slope(false, settings.constantMap, window);

    if (!one.loadFromFile("one_signe.png"))
    {
        throw  runtime_error{"Couldn't open filename: one_signe.png"};
    }
    if (!two.loadFromFile("two_signe.png"))
    {
        throw  runtime_error{"Couldn't open filename: two_signe.png"};
    }
    if (!three.loadFromFile("three_signe.png"))
    {
        throw  runtime_error{"Couldn't open filename: three_signe.png"};
    }
    if (!go.loadFromFile("go.png"))
    {
        throw  runtime_error{"Couldn't open filename: three_signe.png"};
    }

    set_sprites();
    create_track();
}

Game_State::~Game_State()
{
    delete left_slope;
    delete right_slope;
}

void Game_State::handle(sf::Event event, stack<State*>& stack)
{
    if (event.type == sf::Event::Resized)
    {
        resize_window(event);
    }
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
                double left{left_slope->context.goal_time.asSeconds()};
                double right{right_slope->context.goal_time.asSeconds()};
                State* wtf {new Game_Over{window, left, right}};
                delete stack.top();
                stack.pop();
                stack.push(wtf);
            }
        }
    }
    
}   

void Game_State::update(sf::Time delta)
{   
    int y {};
    if (!game_started)
    {
        y = 1;
        if(clock.getElapsedTime().asSeconds() > 4)
        {
            game_started = true;
        }
        else if(clock.getElapsedTime().asSeconds() > 3)
        {
            digit.setTexture(go);
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
        if (y == 1)
        {
            left_slope->context.clock.restart();
            right_slope -> context.clock.restart();
            y = 0;
        }
        if(left_slope->context.game_finished == false || right_slope->context.game_finished == false)
        {
            left_slope->update(delta);
            right_slope->update(delta);
        }
    }
}

void Game_State::render(sf::RenderWindow& window)
{
    left_slope->render(window);
    right_slope->render(window);

    if (left_slope->context.game_finished && right_slope->context.game_finished)
    {   
        window.draw(menu_background);
        window.draw(text);
    }
    if (!game_started)
    {
        window.draw(digit);
    }
}

void Game_State::set_sprites()
{
    // Instruktioner
    text.setFont(font);
    text.setString("GAME OVER!!!\nPress 'Enter' to continue!");
    text.setFillColor(sf::Color(0, 255, 255));
    text.setCharacterSize(35);
    sf::FloatRect text_bounds { text.getGlobalBounds() };
    text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
    text.setPosition(window_size.x / 2, 4 * window_size.y / 8);

    digit.setTexture(three);
    sf::Vector2u texture_size { one.getSize() };
    float scale {(window_size.x/4.f)/texture_size.x};
    digit.setScale(scale, scale);
    digit.setOrigin(texture_size.x/ 2.f, texture_size.y/ 2.f);
    digit.setPosition(window_size.x / 2.f, window_size.y / 2.f);

    clock.restart();
}

void Game_State::create_track()
{
    srand(settings.seed);
    float modifier_xpos {};
    float modifier_ypos {600};
    
    ofstream mod_info ("track.txt");
    if (!mod_info.is_open())
    {
        throw runtime_error{"track.txt couldn't be opened!"};
    }
    else
    {
        int x{0};

        mod_info << "Goal" << ' ' << window_size.x/4 << ' ' << settings.track_length <<'\n';
        mod_info << "Snowball" << ' ' << window_size.x/4 << ' ' << modifier_ypos << '\n';

        for(modifier_ypos = 600; modifier_ypos < (settings.track_length-400); modifier_ypos = modifier_ypos + settings.StatObjs_freq)
        {
            modifier_xpos = settings.constantMap["Tire"].at(0)/2 
                            + rand()%(window_size.x/2 
                            - static_cast<int>(settings.constantMap["Tire"].at(0))); 
            modifier_ypos = modifier_ypos + rand()%50;
            mod_info << settings.StatObjs.at(rand()%(settings.StatObjs.size())) 
                     << ' ' << modifier_xpos << ' ' << modifier_ypos << '\n';
            if (x%4 == 0)
                {
                    int modifier_xpos2{0};
                    modifier_xpos2 = settings.constantMap["Tire"].at(0)/2 
                                     + rand()%(window_size.x/2 
                                     - static_cast<int>(settings.constantMap["Tire"].at(0))); 
                    
                    mod_info << settings.StatObjs.at(rand()%(settings.StatObjs.size())) 
                             << ' ' << modifier_xpos2 << ' ' << modifier_ypos << '\n';
                }
            x = x + 1;
        }

        int occurence_sum {0};
        for(const auto &[key, value]: settings.constantMap)
        {
            occurence_sum = occurence_sum + settings.constantMap[key].at(1);
        }

        for(modifier_ypos = 1000; modifier_ypos < (settings.track_length-400); modifier_ypos = modifier_ypos + settings.MovObjs_freq)
        {
            modifier_xpos = settings.constantMap["Tire"].at(0)/2 
                            + rand()%(window_size.x/2) 
                            - settings.constantMap["Tire"].at(0); 
            modifier_ypos = modifier_ypos + rand()%100; 

            int randValue {};
            int current {0};
            string selectedObject{};
            randValue = rand() % occurence_sum + 1;

            for(string mov : settings.MovObjs)
            {
                current = current + settings.constantMap[mov].at(1);
                if(randValue <= current)
                {
                    selectedObject = mov;
                    break;
                }
            }
            mod_info << selectedObject << ' ' 
                     << modifier_xpos << ' ' 
                     << modifier_ypos << '\n';
        }
    }
}

void Game_State::read_constants()
{
    string line {};
    ifstream info_file {"game_object_info.txt"};
    if (!info_file.is_open())
    {
        throw runtime_error{"game_object_info.txt couldn't be opened!"};
    }
    else 
    {
        while ( getline (info_file, line))
        {
            string info_name {""};
            float size {0};
            float occurence {0};
            float xspeed {0};
            float speedmod {0};

            istringstream info(line);
            info >> info_name >> size >> occurence >> xspeed >> speedmod;

            if (!info.fail())
            {
                info.clear();
            }

            settings.constantMap[info_name] = {size,occurence};
            if (!(xspeed == 0))
            {
                settings.constantMap[info_name].push_back(xspeed);
            }

            if (!(speedmod == 0))
            {
                settings.constantMap[info_name].push_back(speedmod);
            }
        }
        info_file.close();
    }

    info_file.open("settings.txt");
    if (!info_file.is_open())
    {
        throw runtime_error{"settings.txt couldn't be opened!"};
    }
    else 
    {
        while (getline (info_file, line))
        {
            string setting_name {};
            string object {};
            istringstream info(line);
            info >> setting_name;

            if (setting_name == "Track_length:")
            {
                info >> settings.track_length;
            }
            if (setting_name == "Seed:")
            {
                info >> settings.seed;
            }
            if (setting_name == "StatObjs:")
            {
                while (info >> object)
                {
                    settings.StatObjs.push_back(object);
                }
            }
            if (setting_name == "MovObjs:")
            {
                while (info >> object)
                {
                    settings.MovObjs.push_back(object);
                }
            }
            if (setting_name == "StatObjs_freq:")
            {
                info >> settings.StatObjs_freq;
            }
            if (setting_name == "MovObjs_freq:")
            {
                info >> settings.MovObjs_freq;
            }
        }
        info_file.close();
    }
}


// Game_Over
/*___________________________________________________________________________________________________________*/
Game_Over::Game_Over(sf::RenderWindow& window, double timeL, double timeR)
    : State{window}, left_time{timeL}, right_time{timeR}, highscores{read_highscore()}
{
    set_sprites();
    check_highscore();
}

void Game_Over::handle(sf::Event event, stack<State*>& stack)
{   
    if (event.type == sf::Event::Resized)
    {
        resize_window(event);
    }
    bool push_menu{};
    if ( new_highscore )
    {
        if (event.type == sf::Event::TextEntered) 
        {
            if (event.text.unicode == '\r' || event.text.unicode == '\n') 
            {
                sort_highscores();
                push_menu = true;
                new_highscore = false;
            }
            else if (event.text.unicode == '\b' && !name.empty()) 
            {
                // Ta bort sista bokstaven
                name.pop_back(); 
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
            if (event.key.code == sf::Keyboard::Enter || push_menu)
            {
                State* next_state{new Menu_State{window}};
                delete stack.top();
                stack.pop();
                stack.push(next_state);
                next_state = nullptr;
            }
        }
    }
}

void Game_Over::update(sf::Time)
{
}

void Game_Over::render(sf::RenderWindow& window)
{
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

void Game_Over::set_sprites()
{
    p2_text.setFont(font);
    p2_text.setString("PLAYER 2 WINS!!!");
    p2_text.setFillColor(sf::Color(255, 20, 147));
    sf::FloatRect p2_text_bounds {p2_text.getGlobalBounds()};
    p2_text.setOrigin(p2_text_bounds.width / 2, p2_text_bounds.height / 2);
    p2_text.setPosition(window_size.x / 2, window_size.y / 4);

    p1_text.setFont(font);
    p1_text.setString("PLAYER 1 WINS!!!");
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
    typed_name.setPosition(window_size.x / 2 + prompt_text_bounds.width / 2 + 20, window_size.y / 2 - 10 );
}

void Game_Over::sort_highscores()
{
    double time {};
    string throwaway;
    bool inserted = false;

    for (unsigned int i = 0; i < highscores.size(); i++)
    {
        istringstream iss {highscores.at(i)};
        iss >> throwaway >> time; 

        if (time > new_highscore_time && !inserted)
        {
            if (name.size() != 0)
            {
                highscores.insert(highscores.begin() + i, name + " " + to_string(new_highscore_time));
            }
            else
            {
                highscores.insert(highscores.begin() + i, "Dr.anonymous " + to_string(new_highscore_time));
            }
            inserted = true;
            if (highscores.size() > 6)
            {
                highscores.pop_back();
            }
            break;
        }
    }

    ofstream outFile("highscore.txt");

    if (!outFile)
    {
        throw runtime_error("Kan inte öppna: highscore.txt");
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

void Game_Over::check_highscore()
{

    istringstream iss {highscores.back()};
    string throwaway{};
    double worst_time{};

    if (!(iss >> throwaway >> worst_time))
    {
        if (left_time < right_time)
        {
            new_highscore = true;
            new_highscore_time = left_time;
        }
        else if (left_time > right_time)
        {
            new_highscore = true;
            new_highscore_time = right_time;
        }
    }
    else
    {
        if (worst_time > left_time && left_time < right_time)
        {
            new_highscore = true;
            new_highscore_time = left_time;
        }
        else if (worst_time > right_time && left_time > right_time)
        {
            new_highscore = true;
            new_highscore_time = right_time;
        }
    }
}


// Menu_State
/*___________________________________________________________________________________________________________*/
Menu_State::Menu_State(sf::RenderWindow& window)
: State{window}
{
    if (!texture_buttons.loadFromFile("gamestart_signe.png"))
    {
        throw runtime_error("Kan inte öppna: Charcoal_bricks_color1.png");
    }
    selected_menu = 0;
    set_sprites();
}

void Menu_State::handle(sf::Event event, stack<State*>& stack )
{
    if (event.type == sf::Event::Resized)
    {
        resize_window(event);
        set_sprites();
    }
    if (event.type == sf::Event::KeyPressed)
    {
        State* next_state{nullptr};

        if (event.key.code == sf::Keyboard::Key::Enter && selected_menu == 0)
        {
            next_state = new Game_State{window};
            delete stack.top();
            stack.pop();
            stack.push(next_state);
        }
        if (event.key.code == sf::Keyboard::Key::Enter && selected_menu == 1)
        {
            next_state = new Controls{window};
            delete stack.top();
            stack.pop();
            stack.push(next_state);
        }
        if (event.key.code == sf::Keyboard::Key::Enter && selected_menu == 2)
        {
            next_state = new Highscore{window};
            delete stack.top();
            stack.pop();
            stack.push(next_state);
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

void Menu_State::update(sf::Time delta)
{
    // Inspirerad av källkod från https://gitlab.liu.se/chrho44/tddc76-sfml
    elapsed_time += delta.asSeconds();
    float const period { 1.0f };
    double const scalar { 1.0 + 0.05*sin( (2 * M_PI) * elapsed_time / period) };

    if ( selected_menu == 0)
    {
        menu[0].setScale(scalar, scalar);
    }
    else if ( selected_menu == 1)
    {
        menu[1].setScale(scalar, scalar);
    }
    if ( selected_menu == 2)
    {
        menu[2].setScale(scalar, scalar);
    }
}

void Menu_State::render(sf::RenderWindow& window)
{
    window.draw(menu_background);
    for (int i = 0; i < Max_Menu ; ++i)
    {
        window.draw(menu_buttons[i]);
        window.draw(menu[i]);
    }
    
    window.draw(text);  
    window.draw(header);
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

void Menu_State::set_sprites()
{
    sf::Vector2u button_size {texture_buttons.getSize()};

    vector<string> menu_text{"PLAY", "CONTROLS", "HIGHSCORE"};

    float scale_x {};
    float scale_y {};
    sf::FloatRect t_bounds {};
    sf::FloatRect t_bounds_b {};

    for (unsigned int i = 0; i < menu_text.size(); i++)
    {
        menu[i].setFont(font);
        if ( i == 0)
        {
            menu[i].setFillColor(sf::Color::Blue);
        }
        else
        {
            menu[i].setFillColor(sf::Color::Black);
        }

        menu[i].setString(menu_text.at(i));
        t_bounds = menu[i].getLocalBounds();
        menu[i].setOrigin(t_bounds.width / 2, t_bounds.height / 2);
        menu[i].setPosition(window_size.x / 2, window_size.y * (i + 1) / 4);

        scale_x = (t_bounds.width + 70)/button_size.x;
        scale_y = (t_bounds.height + 50)/button_size.y;
        menu_buttons[i].setTexture(texture_buttons);
        menu_buttons[i].setScale(scale_x, scale_y);
        t_bounds_b = menu_buttons[i].getLocalBounds();
        menu_buttons[i].setOrigin(t_bounds_b.width / 2, t_bounds.height / 2 + 190);
        menu_buttons[i].setPosition(menu[i].getPosition());
    }

    // Pulserande text
    text.setFont(font);
    text.setString("Press 'Enter' to interact!\nUse arrows to navigate!\nPress 'Q' to exit");
    text.setFillColor(sf::Color(0, 255, 255));
    
    // Överskrift
    header.setFont(font);
    header.setString("EPIC HARDCORE VSR SIMULATOR");
    header.setFillColor(sf::Color(255, 20, 147));
    text.setCharacterSize(15);

    sf::FloatRect text_bounds { text.getGlobalBounds() };
    sf::FloatRect header_bounds { header.getGlobalBounds()};
    text.setOrigin(text_bounds.width / 2, text_bounds.height / 2);
    text.setPosition(window_size.x / 2, 7 * window_size.y / 8);
    header.setOrigin(header_bounds.width / 2, header_bounds.height / 2);
    header.setPosition(window_size.x / 2, window_size.y / 8);
}


// Highscore
/*___________________________________________________________________________________________________________*/
Highscore::Highscore(sf::RenderWindow& window)
    : State{window}
{
    if (!highscore_texture.loadFromFile("highscore_signe.png"))
    {
        throw runtime_error("Kan inte öppna: highscore_signe.png");
    }

    set_sprites();
}

void Highscore::handle(sf::Event event, stack<State*>& stack)
{
    if (event.type == sf::Event::Resized)
    {
        resize_window(event);
    }
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Key::Escape)
        {
            State* next_state {new Menu_State{window}};
            delete stack.top();
            stack.pop();
            stack.push(next_state);
        }
    }
}

void Highscore::update(sf::Time)
{
}

void Highscore::render(sf::RenderWindow& window)
{
    window.draw(menu_background);

    for (int i = 0; i < 6 ; ++i)
    {
        window.draw(highscore_sprite[i]);
        window.draw(score[i]);
    }

    window.draw(instruction);
}

void Highscore::set_sprites()
{

    sf::Vector2u button_size {highscore_texture.getSize()};

    vector<string> highscores {read_highscore()};

    for (unsigned int i = 0; i < highscores.size() ; ++i)
    {
        score[i].setFont(font);
        score[i].setFillColor(sf::Color::Black);
        score[i].setString(highscores.at(i));
        sf::FloatRect bounds { score[i].getLocalBounds() };
        score[i].setOrigin(bounds.width / 2, bounds.height / 2);
        score[i].setPosition(window_size.x / 2, window_size.y * 1 / 7 * (i + 1));

        float scale_x {(bounds.width + 100)/button_size.x};
        float scale_y {(bounds.height + 50)/button_size.y};
        highscore_sprite[i].setTexture(highscore_texture);
        highscore_sprite[i].setScale(scale_x, scale_y);
        sf::FloatRect highscore_bounds_b { highscore_sprite[i].getLocalBounds() };
        highscore_sprite[i].setOrigin(highscore_bounds_b.width / 2 , highscore_bounds_b.height / 2 - 80);
        highscore_sprite[i].setPosition(score[i].getPosition());
    }

    instruction.setFont(font);
    instruction.setString("Press 'esc' to go back");
    instruction.setFillColor(sf::Color(255, 20, 147));
    sf::FloatRect instruction_bounds {instruction.getGlobalBounds()};
    instruction.setOrigin(instruction_bounds.width / 2, instruction_bounds.height / 2);
    instruction.setPosition(window_size.x / 2, window_size.y / 16);
}


// Controls
/*___________________________________________________________________________________________________________*/
Controls::Controls(sf::RenderWindow& window)
    :  State{window}
{   
    set_sprites();
}

void Controls::handle(sf::Event event, stack<State*>& stack)
{
    if (event.type == sf::Event::Resized)
    {
        resize_window(event);
    }
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Key::Escape)
        {
            State* next_state {new Menu_State{window}};
            delete stack.top();
            stack.pop();
            stack.push(next_state);
        }
    }
}

void Controls::update(sf::Time)
{
}

void Controls::render(sf::RenderWindow& window)
{
    window.draw(menu_background);
    for ( sf::Text t : text )
    {
        window.draw(t);
    }
}

void Controls::set_sprites()
{    
    for ( sf::Text& t : text)
    {
        t.setFont(font);
        t.setFillColor(sf::Color(255, 20, 147));
        t.setCharacterSize(20);
    }

    // Sätt strängar
    text[0].setString("Press 'esc' to go back!"); // Överskrift
    text[1].setString("PLAYER 1\n........");
    text[2].setString("PLAYER 2\n........");
    text[3].setString("Go 'LEFT'/'RIGHT':"); // Svänga
    text[4].setString("'A'/'D'");
    text[5].setString("'<-'/'->'");
    text[6].setString("Shoot Snowball:"); // Skjuta
    text[7].setString("'S'");
    text[8].setString("'|'\n v ");
    text[9].setString("PICK-UPS\n........"); // Modifiers
    text[10].setString("SNOWBALLS - Replenishes snowballs");
    text[11].setString("CAPRICE KIR - Become a speed devil for a short period of time");
    text[12].setString("CAN - Slows you down (littering is not cool!)");
    text[13].setString("CHALMERIST - You don't want to collide with this buffoon...");

    // Sätt vart texten ska vara
    sf::FloatRect t_bounds { text[0].getGlobalBounds() };
    text[0].setOrigin(t_bounds.width / 2, t_bounds.height / 2);
    text[0].setPosition( window_size.x / 2, 0.5 * window_size.y  / 10); // Överskrift
    text[1].setPosition(5 * window_size.x / 10, 1.5 * window_size.y / 10);
    text[2].setPosition(7 * window_size.x / 10, 1.5 * window_size.y / 10);
    text[3].setPosition( window_size.x / 100, 3 * window_size.y / 10); // Svänga
    text[4].setPosition(5 * window_size.x / 10, 3 * window_size.y / 10);
    text[5].setPosition(7 * window_size.x / 10, 3 * window_size.y / 10);
    text[6].setPosition( window_size.x / 100, 4.5 * window_size.y / 10); // Skjuta
    text[7].setPosition(5.25 * window_size.x / 10, 4.5 * window_size.y / 10);
    text[8].setPosition(7.5 * window_size.x / 10, 4.5 * window_size.y / 10);
    text[9].setPosition( window_size.x / 100, 6 * window_size.y / 10); // Modifiers
    text[10].setPosition( window_size.x / 100, 7 * window_size.y / 10);
    text[11].setPosition( window_size.x / 100, 7.5 * window_size.y / 10);
    text[12].setPosition( window_size.x / 100, 8 * window_size.y / 10);
    text[13].setPosition( window_size.x / 100, 8.5 * window_size.y / 10);
}
