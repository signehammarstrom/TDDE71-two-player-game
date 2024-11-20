#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H
#include "game_object.h"
#include "modifier.h"
#include "slope.h"

//Moving_Object
/*_______________________________________________________________________________________*/

class Moving_Object : public Modifier
{
public:
    Moving_Object(double xpos, double ypos, double xspeed);
    ~Moving_Object() = default;

    //virtual void affect_context(Context context&) = 0;
    double get_xspeed() const;
private:
    double xspeed {};
};

//Snowball_Mod
/*_______________________________________________________________________________________*/

class Snowball_Mod : public Moving_Object
{
public:
   Snowball_Mod(double xpos, double ypos, double xspeed, double radius);
   ~Snowball_Mod() = default;
   //void affect_context(Context context&);
    double get_radius() const;
private:
   double radius{}; 
};

#endif
