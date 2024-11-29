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
    Static_Obstacle(double xpos, double ypos, std::string filename);
    ~Static_Obstacle() = default;

};


//Deklaration av den härledda klassen Tire
/*_____________________________________________________________________*/
class Tire : public Static_Obstacle
{

public:

    Tire(double xpos, double ypos, double radius, std::string filename = "tire.png");
        //ritar ut ett däck med höjd 2*radien och bredd 2*radien. 
        //x och ykoordinat är mittpunkten på däcket. 
    ~Tire() = default;

    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;
    void perform_collision(Game_Object* const& other) override;

private:
    double radius;

};
    

//Deklaration av den härledda klassen Hole
/*____________________________________________________________________*/
class Hole : public Static_Obstacle
{

public:
    Hole(double xpos, double ypos, double radius, std::string filename = "hole.png");
    ~Hole() = default;

    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;
    void perform_collision(Game_Object* const& other) override;

private:
    double radius;
};


//Deklaration av den härledda klassen Goal
/*____________________________________________________________________*/
class Goal : public Static_Obstacle
{

public:
    Goal(double xpos, double ypos, double width, double height, std::string filename = "finish.png");
    ~Goal() = default;
 
    bool handle(sf::Event event, Context& context) override;
    void update(sf::Time delta, Context& context) override;
    void perform_collision(Game_Object* const& other) override;


private:
    double width;
    double height;
};

#endif
