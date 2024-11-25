#include "state.h"
#include "slope.h"
#include <SFML/Graphics.hpp>

unsigned const screen_width{1136};
unsigned const screen_height{640};

sf::RenderWindow window { sf::VideoMode { screen_width,
                                        screen_height },
                        "EPIC HARDCORE VSR Simulator" };

int main() {

    State* state {new Game_State()};

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
        window.clear(sf::Color(255, 255, 255)); // Ändrat i IdaOskar
        state->render(window);
        window.display();
    }

    delete state;
}
