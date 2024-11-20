#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H
#include "game_object.h"
#include "modifier.h"
#include "slope.h"

class Moving_Object : public Modifier
{
public:
    Moving_Object(/* args */);
    ~Moving_Object();

    virtual void affect_context(Context context&) = 0;

private:
    double xspeed {};
};


class Snowball_Mod : public Moving_Object
{
public:
   void affect_context(Context context&);

private:
   double radius{}; 
};

#endif
