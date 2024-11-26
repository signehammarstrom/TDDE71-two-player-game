#include "state.h"
#include "slope.h"
#include "game_object.h"
#include "modifier.h"
#include "context.h"
#include "static_obstacle.h"
#include <SFML/Graphics.hpp>

unsigned const screen_width{1136};
unsigned const screen_height{640};

sf::RenderWindow window { sf::VideoMode { screen_width,
                                        screen_height },
                        "EPIC HARDCORE VSR Simulator" };

int main() {

    State* state {new Game_State()};

    std::vector<Game_Object*> obj_lst{};
    Context gameContext{};
    gameContext.y_speed = 100; 

    Tire tire(1000, 300, 50);

    Hole hole(70, 400, 100);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            state->handle(event);
        }
        state->update(clock.restart());
        
        
        window.clear();
        state->render(window);
        tire.update(clock.getElapsedTime(), gameContext);
        hole.update(clock.getElapsedTime(), gameContext);
        tire.render(window);
        hole.render(window);

        window.display();
    }

    delete state;
}