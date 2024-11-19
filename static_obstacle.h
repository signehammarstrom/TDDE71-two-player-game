#ifndef STATIC_OBSTACLE_H
#define STATIC_OBSTACLE_H

//Deklaration av basklassen StaticObstacle
/*_____________________________________________________________________*/
class StaticObstacle
{

public:
    virtual bool handle(sf::Event event) = 0;
    virtual void update(sf::Time delta) = 0; //Parameterlistan behöver justeras
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void perform_collision(GameObject&) = 0;


private:
    //Avvakta


protected:
    //Avvakta

};


//Deklaration av den härledda klassen Tire
/*_____________________________________________________________________*/
class Tire : public StaticObject
{

public:
    //Avvakta


private:
    //Avvakta


protected:
    //Avvakta

};
    

//Deklaration av den härledda klassen Hole
/*____________________________________________________________________*/
class Hole : public StaticObject
{

public:
    //Avvakta


private:
    //Avvakta


protected:
    //Avvakta
};


//Deklaration av den härledda klassen Goal
/*____________________________________________________________________*/
class Goal : public StaticObject
{

public:
    //Avvakta


private:
    //Avvakta


protected:
    //Avvakta

};

#endif
