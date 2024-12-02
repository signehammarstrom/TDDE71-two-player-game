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
    Temporary_Modifier(double xpos, double ypos, float scale, double xspeed,
         double speedmodifier, std::string filename, bool is_active=false);
    ~Temporary_Modifier() = default;

    double get_width() const;
    double get_height() const;
    double get_speedmodifier() const; 
    virtual void active(sf::Time time);
    void update_time(sf::Time delta) override;
    void remove_if_inactual(Context& context) override;
    void perform_collision(Game_Object* const& other, Context& context) override;
    

    
    
protected:
    double width{};
    double height{};
    double speedmodifier{};
    bool is_active{};
    sf::Time time_passed{};
    
};

//Chalmerist
/*_______________________________________________________________________________________*/

class Chalmerist : public Temporary_Modifier
{
public: 
    Chalmerist(double xpos, double ypos, float scale, double xspeed,
         double speedmodifier, std::string filename = "Chalmerist.png", bool is_active=false);
    ~Chalmerist() = default;

    bool handle(sf::Event event, Context& context) override;
 //   void update(sf::Time delta, Context& context) override;
    void render(sf::RenderWindow& window) override;
 //   void remove_if_inactual() override;

private: 

};

//Can
/*_______________________________________________________________________________________*/

class Can : public Temporary_Modifier
{
public: 
    Can(double xpos, double ypos, float scale, double xspeed,
        double speedmodifier, std::string filename = "eybro.png", bool is_active=false);
    ~Can() = default;

    bool handle(sf::Event event, Context& context) override;
 //   void update(sf::Time delta, Context& context) override;
    void render(sf::RenderWindow& window) override;
 //   void remove_if_inactual(Contect& context) override;

private: 

};

//Kir
/*_______________________________________________________________________________________*/

class Kir : public Temporary_Modifier
{
public: 
    Kir(double xpos, double ypos, float scale, double xspeed,
        double speedmodifier, std::string filename = "kir.png", bool is_active=false);
    ~Kir() = default;

    bool handle(sf::Event event, Context& context) override;
//    void update(sf::Time delta, Context& context) override;
    void render(sf::RenderWindow& window) override;

private: 

};

#endif
