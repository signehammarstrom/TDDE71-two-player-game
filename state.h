#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include "slope.h"
#include <stack>
#include <vector>
#include <string>

#define Max_Menu 3

class State
{
public:
    State(sf::RenderWindow& window);
    virtual ~State() = default;

    virtual void handle(sf::Event event, std::stack<State*>& stack) = 0;
    virtual void update(sf::Time delta) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

protected:
    std::vector<std::string> read_highscore();
    sf::RenderWindow& window;
    sf::Vector2u window_size;
    sf::Font font;
    sf::Sprite menu_background;
    sf::Texture menu_background_texture;

}; 

class Game_State : public State
{
public:

    Game_State(sf::RenderWindow& window);
    ~Game_State();
    
    void handle(sf::Event event, std::stack<State*>& stack) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

    Slope* left_slope{};
    Slope* right_slope{};

private:
    void create_track();
    void sort_highscores(std::vector<std::string>);

    sf::Text p1_text;
    sf::Text p2_text;

    sf::Text prompt;
    sf::Text typed_name;
    std::string name;

    bool new_highscore;
    double new_highscore_time;
    std::vector<std::string> highscores;

    bool game_started;
    sf::Clock clock;
    sf::Texture one;
    sf::Texture two;
    sf::Texture three;
    sf::Sprite digit;
};

class Menu_State : public State
{
public:

    Menu_State(sf::RenderWindow& window);
    ~Menu_State() = default;
    
    void handle(sf::Event event, std::stack<State*>& stack) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

    void move_up();
    void move_down();
    
private:
    int selected_menu;
    sf::Text menu[Max_Menu];
    //sf::Sprite menu_background[Max_Menu];
    //sf::Texture menu_texture;

    sf::Text text;
    sf::Text header;
    sf::Texture texture;
    sf::Sprite sprite;

    //  Test för periodicitet
    float elapsed_time { 0.0f };
};

class Highscore : public State
{
public:
    Highscore(sf::RenderWindow& window);
    ~Highscore() = default;

    void handle(sf::Event event, std::stack<State*>& stack) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Text score[6];
    sf::Text instruction;
};


// CONTROLS
/*___________________________________________________________________________________________________________*/
class Controls : public State
{
public:
    Controls(sf::RenderWindow& window);
    ~Controls() = default;

    void handle(sf::Event event, std::stack<State*>& stack) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Text instruction;

};


#endif
