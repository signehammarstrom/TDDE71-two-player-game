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

private:
    //Avvakta


protected:
    //Avvakta

};


//Deklaration av den härledda klassen Tire
/*_____________________________________________________________________*/
class Tire : public Static_Obstacle
{

public:

    Tire(double xpos, double ypos, double radius);
        //ritar ut ett däck med höjd 2*radien och bredd 2*radien. 
        //x och ykoordinat är mittpunkten på däcket. 
    ~Tire() = default;

    // bool handle(sf::Event event) overrßide;
    // void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;
    // void perform_collision(GameObject&) override;
    // sf::FloatRect bounds() const override;

private:
    double radius;
    sf::Texture texture;
    sf::Sprite sprite;

protected:
    //Avvakta

};
    

//Deklaration av den härledda klassen Hole
/*____________________________________________________________________*/
class Hole : public Static_Obstacle
{

public:
    Hole(double xpos, double ypos, double radius);
    ~Hole() = default;

    // bool handle(sf::Event event) override;
    // void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;
    // void perform_collision(GameObject&) override;
    // sf::FloatRect bounds() const override;

private:
    double radius;
    sf::Texture texture;
    sf::Sprite sprite;


protected:
    //Avvakta
};


//Deklaration av den härledda klassen Goal
/*____________________________________________________________________*/
class Goal : public Static_Obstacle
{

public:
    Goal(double xpos, double ypos, double width, double height);
    ~Goal() = default;
 
    // bool handle(sf::Event event) override;
    // void update(sf::Time delta) override;
    // void render(sf::RenderWindow& window) override;
    // void perform_collision(GameObject&) override;
    // sf::FloatRect bounds() const override;


private:
    double width;
    double height;


protected:
    //Avvakta

};

#endif
