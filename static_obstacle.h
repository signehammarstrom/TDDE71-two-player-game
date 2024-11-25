#ifndef STATIC_OBSTACLE_H
#define STATIC_OBSTACLE_H
#include "modifier.h"
#include <SFML/Graphics.hpp>

//Deklaration av basklassen Static_Obstacle. Abstrakt datatyp som ärver av Modifier.
/*_____________________________________________________________________*/
class Static_Obstacle : public Modifier
{

public:
    Static_Obstacle(double xpos, double ypos);
    ~Static_Obstacle() = default;

    bool handle(sf::Event event) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;
    void perform_collision(GameObject&) override;
    bool collides(GameObject&) override;


private:
    //Avvakta


protected:
    //Avvakta

};


//Deklaration av den härledda klassen Tire
/*_____________________________________________________________________*/
class Tire : public Static_Object
{

public:
    Tire(double xpos, double ypos, double radius);
    ~Tire() = default;

private:
    double radius;


protected:
    //Avvakta

};
    

//Deklaration av den härledda klassen Hole
/*____________________________________________________________________*/
class Hole : public Static_Object
{

public:
    Hole(double xpos, double ypos, double radius);
    ~Hole() = default;


private:
    double radius;


protected:
    //Avvakta
};


//Deklaration av den härledda klassen Goal
/*____________________________________________________________________*/
class Goal : public Static_Object
{

public:
    Goal(double xpos, double ypos, double width, double height);
    ~Goal() = default;
 
    bool handle(sf::Event event) override;
    void update(ef::Time delta) override;
    void render(sf::RenderWindow& window) override;
    void perform_collision(GameObject&) override;
    bool collides(GameObject&) override;


private:
    double width;
    double height;


protected:
    //Avvakta

};

#endif
