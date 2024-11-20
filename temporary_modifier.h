#ifndef TEMPORARY_MODIFIER_H
#define TEMPORARY_MODIFIER_H
#include "game_object.h"
#include "modifier.h"
#include "moving_object.h"
#include "slope.h"

class Temporary_Modifier : public Moving_Object
{
public:
    Temporary_Modifier(/* args */);
    ~Temporary_Modifier();

    void affect_context(Context context&, double speedmodifier);
    

protected:
    double width{};
    double height{};
    double speedmodifier{};
    
};

class Chalmerist : public Temporary_Modifier
{
public: 
    Chalmerist(/*args*/);
    ~Chalmerist();
    bool handle(sf::Event event);
    void update(sf::Time delta, /* ... */);
    void render(sf::RenderWindow& window);
    void perform_collision(Game_Object &);
    bool collides(Game_Object &) ;

private: 

}

class Can : public Temporary_Modifier
{
public: 
    Can(/*args*/);
    ~Can();
    bool handle(sf::Event event);
    void update(sf::Time delta, /* ... */);
    void render(sf::RenderWindow& window);
    void perform_collision(Game_Object &);
    bool collides(Game_Object &) ;

private: 

}

class Kir : public Temporary_Modifier
{
public: 
    Kir(/*args*/);
    ~Kir();
    bool handle(sf::Event event);
    void update(sf::Time delta, /* ... */);
    void render(sf::RenderWindow& window);
    void perform_collision(Game_Object &);
    bool collides(Game_Object &) ;

private: 

}

#endif
