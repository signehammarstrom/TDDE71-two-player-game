#ifndef TEMPORARY_MODIFIER_H
#define TEMPORARY_MODIFIER_H

#include <SFML/Graphics.hpp>
#include <string>

#include "game_object.h"
#include "context.h"
#include "modifier.h"
#include "moving_object.h"


//Temporary_Modifier
/*_______________________________________________________________________________________*/

class Temporary_Modifier : public Moving_Object
{
public:
    Temporary_Modifier(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier, std::string filename);
    ~Temporary_Modifier() = default;

    double get_width() const;
    double get_height() const;
    double get_speedmodifier() const; 
    
protected:
    double width{};
    double height{};
    double speedmodifier{};
    
};

//Chalmerist
/*_______________________________________________________________________________________*/

class Chalmerist : public Temporary_Modifier
{
public: 
    Chalmerist(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier, std::string filename = "tire.png");
    ~Chalmerist() = default;

    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;
    void render(sf::RenderWindow& window) override;
    void perform_collision(Game_Object* const& other) override;

private: 

};

//Can
/*_______________________________________________________________________________________*/

class Can : public Temporary_Modifier
{
public: 
    Can(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier, std::string filename = "tire.png");
    ~Can() = default;

    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;
    void render(sf::RenderWindow& window) override;
    void perform_collision(Game_Object* const& other) override;

private: 

};

//Kir
/*_______________________________________________________________________________________*/

class Kir : public Temporary_Modifier
{
public: 
    Kir(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier, std::string filename = "tire.png");
    ~Kir() = default;

    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;
    void render(sf::RenderWindow& window) override;
    void perform_collision(Game_Object* const& other) override;

private: 

};

#endif
