#include "game_object.h"
#include "modifier.h"
#include "moving_object.h"
#include "slope.h"
#include "temporary_modifier.h"


//Temporary_Modifier
/*_______________________________________________________________________________________*/

Temporary_Modifier::Temporary_Modifier(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier)
    : Moving_Object(xpos, ypos, xspeed), width{width}, 
    height{height}, speedmodifier{speedmodifier}
{}


 double Temporary_Modifier::get_width() const
 {
    return width;
 }

double Temporary_Modifier::get_height() const
{
    return height;
}

double Temporary_Modifier::get_speedmodifier() const
{
    return speedmodifier;
}

//Chalmerist
/*_______________________________________________________________________________________*/

Chalmerist::Chalmerist(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier)
    : Temporary_Modifier(xpos, ypos, xspeed, width, height, speedmodifier)
{}

//Can
/*_______________________________________________________________________________________*/

Can::Can(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier)
    : Temporary_Modifier(xpos, ypos, xspeed, width, height, speedmodifier)
{}

//Kir
/*_______________________________________________________________________________________*/

Kir::Kir(double xpos, double ypos, double xspeed,
        double width, double height, double speedmodifier)
    : Temporary_Modifier(xpos, ypos, xspeed, width, height, speedmodifier)
{}