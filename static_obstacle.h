#ifndef STATIC_OBSTACLE_H
#define STATIC_OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <string>

#include "game_object.h"
#include "modifier.h"
#include "context.h"

//Deklaration av basklassen Static_Obstacle. Abstrakt datatyp som ärver av Modifier.
/*_____________________________________________________________________*/
class Static_Obstacle : public Modifier
{
public:
    Static_Obstacle(double xpos, double ypos, float scale, std::string filename);
    ~Static_Obstacle() = default;
    void update(sf::Time delta, Context& context) override;
};


//Deklaration av den härledda klassen Tire
/*_____________________________________________________________________*/
class Tire : public Static_Obstacle
{
public:
    Tire(double xpos, double ypos, float scale, std::string filename = "tire.png");
    ~Tire() = default;

    void perform_collision(Game_Object* const& other, Context& context) override;
private:
};
    

//Deklaration av den härledda klassen Hole
/*____________________________________________________________________*/
class Hole : public Static_Obstacle
{
public:
    Hole(double xpos, double ypos, float scale, std::string filename = "hole.png");
    ~Hole() = default;

    void perform_collision(Game_Object* const& other, Context& context) override;
private:
};


//Deklaration av den härledda klassen Goal
/*____________________________________________________________________*/
class Goal : public Static_Obstacle
{
public:
    Goal(double xpos, double ypos, float scale, std::string filename = "finish.png");
    ~Goal() = default;

    void perform_collision(Game_Object* const& other, Context& context) override;
private:
};

#endif
