#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include "slope.h"
#include "settings.h"
#include <stack>
#include <vector>
#include <string>
#include <map> 

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
    void set_background();
    virtual void set_sprites() = 0;
    std::vector<std::string> read_highscore();
    void resize_window(sf::Event event);
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
    void read_constants();
    Settings settings;
    
    void set_sprites() override;

    sf::Clock clock;
    bool game_started;
    sf::Texture one;
    sf::Texture two;
    sf::Texture three;
    sf::Texture go;
    sf::Sprite digit;

    sf::Text text;
};

class Game_over : public State
{
public:
    Game_over(sf::RenderWindow& window, double timeL, double timeR);
    ~Game_over() = default;

    void handle(sf::Event event, std::stack<State*>& stack) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

private:
    double left_time;
    double right_time;
    std::vector<std::string> highscores;

    void check_highscore();
    void sort_highscores();
    void set_sprites() override;

    sf::Text prompt;
    sf::Text typed_name;
    std::string name{};

    sf::Text p1_text;
    sf::Text p2_text;

    bool new_highscore{};
    double new_highscore_time{};

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
    sf::Sprite menu_buttons[Max_Menu];
    sf::Texture texture_buttons;

    sf::Text text;
    sf::Text header;

    //  Test för periodicitet
    float elapsed_time { 0.0f };
    void set_sprites() override;
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
    void set_sprites() override;
    sf::Text score[6];
    sf::Sprite highscore_sprite[6];
    sf::Texture highscore_texture;
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
    // Texter
    sf::Text text[14];
    void set_sprites() override;
    // Sprites
    /*
    sf::Texture white_arrow;
    sf::Sprite down_arrow;
    sf::Sprite left_arrow;
    sf::Sprite right_arrow;
    */
};


#endif
