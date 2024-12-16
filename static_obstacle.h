#ifndef STATIC_OBSTACLE_H
#define STATIC_OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <string>
#include "game_object.h"
#include "modifier.h"
#include "context.h"

//Deklaration av Static_Obstacle
/*_____________________________________________________________________*/
class Static_Obstacle : public Modifier
{
public:
    Static_Obstacle(double xpos, double ypos, float size, sf::Vector2u& window_size, std::string& filename);
    ~Static_Obstacle() = default;

    void update(sf::Time delta, Context& context) override;
};


//Deklaration av Goal
/*____________________________________________________________________*/
class Goal : public Static_Obstacle
{
public:
    Goal(double xpos, double ypos, float size, sf::Vector2u& window_size, std::string filename = "finish.png");
    ~Goal() = default;

    void perform_collision(Game_Object* const& other, Context& context) override;
};


//Deklaration av Actual_Obstacle
/*____________________________________________________________________*/
class Actual_Obstacle : public Static_Obstacle
{
public:
    Actual_Obstacle(double xpos, double ypos, float size, sf::Vector2u& window_size, std::string& filename);
    ~Actual_Obstacle() = default;

    void perform_collision(Game_Object* const& other, Context& context) override;
};


//Deklaration av Tire
/*_____________________________________________________________________*/
class Tire : public Actual_Obstacle
{
public:
    Tire(double xpos, double ypos, float size, sf::Vector2u& window_size, std::string filename = "tire_signe.png");
    ~Tire() = default;
};
    

//Deklaration av Hole
/*____________________________________________________________________*/
class Hole : public Actual_Obstacle
{
public:
    Hole(double xpos, double ypos, float size, sf::Vector2u& window_size, std::string filename = "hole.png");
    ~Hole() = default;
};

#endif
