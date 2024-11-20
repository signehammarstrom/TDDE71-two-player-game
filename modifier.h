#ifndef MODIFIER_H
#define MODIFIER_H
#include "game_object.h"

class Modifier : public Game_Object 
{
public:
    Modifier(/* args */);
    ~Modifier();
    virtual void perform_collision(Player player const&) = 0;
    virtual void perform_collision(Snowball_Projectile snowball const&) = 0;
private:
    /* data */
};

#endif
