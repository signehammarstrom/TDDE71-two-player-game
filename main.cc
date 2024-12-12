#include "state.h"
#include "slope.h"
#include <SFML/Graphics.hpp>
#include <stack>

unsigned const screen_width{1136};
unsigned const screen_height{640};

/*sf::RenderWindow window { sf::VideoMode { screen_width,
                                        screen_height },
                        "EPIC HARDCORE VSR Simulator" };*/

sf::RenderWindow window { sf::VideoMode::getDesktopMode(), 
        "EPIC HARDCORE VSR Simulator"};

int main() {

    std::stack<State*> states{};
    bool wtf {};
    states.push(new Menu_State{window});

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                wtf = true;  
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Key::Escape)
                {
                    wtf = true;
                }
            }
            states.top()->handle(event, states);
        }

        states.top()->update(clock.restart());

        window.clear();
        states.top()->render(window);
        window.display();
        
        if (wtf)
        {
            break;
        }
    }
    
    while (!states.empty())
    {
        delete states.top();
        states.pop();
    }
    window.close();

}
