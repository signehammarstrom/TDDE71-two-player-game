#ifndef TEMPORARY_MODIFIER_H
#define TEMPORARY_MODIFIER_H
#include "game_object.h"
#include "modifier.h"
#include "moving_object.h"
#include "slope.h"

//Temporary_Modifier
/*_______________________________________________________________________________________*/

class Temporary_Modifier : public Moving_Object
{
public:
    Temporary_Modifier(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier);
    ~Temporary_Modifier() = default;

    //void affect_context(Context context&);
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
        double width, double height, double speedmodifier);
    ~Chalmerist() = default;
    //bool handle(sf::Event event);
    //void update(sf::Time delta, /* ... */);
    //void render(sf::RenderWindow& window);
    //void perform_collision(Game_Object &);
   // sf::FloatRect bounds() const override;

private: 

};

//Can
/*_______________________________________________________________________________________*/

class Can : public Temporary_Modifier
{
public: 
    Can(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier);
    ~Can() = default;
    //bool handle(sf::Event event);
    //void update(sf::Time delta, /* ... */);
    //void render(sf::RenderWindow& window);
    //void perform_collision(Game_Object &);
    // sf::FloatRect bounds() const override;

private: 

};

//Kir
/*_______________________________________________________________________________________*/

class Kir : public Temporary_Modifier
{
public: 
    Kir(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier);
    ~Kir() = default;
    //bool handle(sf::Event event);
    //void update(sf::Time delta, /* ... */);
    //void render(sf::RenderWindow& window);
    //void perform_collision(Game_Object &);
    // sf::FloatRect bounds() const override;

private: 

};

#endif
