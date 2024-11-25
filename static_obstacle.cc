#include "static_obstacle.h"
#include <SFML/Graphics.hpp>


Static_Obstacle::Static_Obstacle(double xpos, double ypos)
    :Modifier(xpos, ypos)
{}


Tire::Tire(double xpos, double ypos, double radius)
    :Static_Obstacle(xpos, ypos), radius{radius}
{}


Hole::Hole(double xpos, double ypos, double radius)
    :Static_Obstacle(xpos, ypos), radius{radius}
{}


Goal::Goal(double xpos, double ypos, double width, double height)
    :Static_Obstacle(xpos, ypos), width{width}, height{height}
{}