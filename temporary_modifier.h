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
    Temporary_Modifier(double xpos, double ypos, float scale, float xspeed,
         double speedmodifier, std::string filename);
    ~Temporary_Modifier() = default;

    double get_speedmodifier() const; 
    void update_time(sf::Time delta);
    void remove_if_inactual(Context& context);
    void perform_collision(Game_Object* const& other, Context& context) override;
    
protected:
    double speedmodifier{};
    sf::Time time_passed{};
};

//Chalmerist
/*_______________________________________________________________________________________*/

class Chalmerist : public Temporary_Modifier
{
public: 
    Chalmerist(double xpos, double ypos, float scale, float xspeed,
         double speedmodifier, std::string filename = "Chalmerist.png");
    ~Chalmerist() = default;

private: 

};

//Can
/*_______________________________________________________________________________________*/

class Can : public Temporary_Modifier
{
public: 
    Can(double xpos, double ypos, float scale, float xspeed,
        double speedmodifier, std::string filename = "eybro.png");
    ~Can() = default;

private: 

};

//Kir
/*_______________________________________________________________________________________*/

class Kir : public Temporary_Modifier
{
public: 
    Kir(double xpos, double ypos, float scale, float xspeed,
        double speedmodifier, std::string filename = "kir.png");
    ~Kir() = default;

private: 

};

#endif
