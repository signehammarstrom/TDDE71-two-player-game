#include <vector>
#include "game_object.h"
#include <SFML/Graphics.hpp>


Slope::Slope(bool side)
    :context{}
{
    context.side = side;
    read_track();
};


Slope::read_track()
{
    open file tracks;
    take random track;
    context = track{i}
}
