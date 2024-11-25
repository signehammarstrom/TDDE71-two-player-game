#include "game_object.h"
#include "player.h"
#include "modifier.h"
#include "moving_object.h"

//Moving_Object
/*_______________________________________________________________________________________*/


Moving_Object::Moving_Object(double xpos, double ypos, double xspeed)
   : Modifier(xpos,ypos), xspeed{xspeed}
{}

double Moving_Object::get_xspeed() const
{
   return xspeed;
}

//Snowball_Mod
/*_______________________________________________________________________________________*/



Snowball_Mod::Snowball_Mod(double xpos, double ypos, double xspeed, double radius)
   : Moving_Object(xpos, ypos, xspeed), radius{radius}
{}

double Snowball_Mod::get_radius() const
{
   return radius;
}