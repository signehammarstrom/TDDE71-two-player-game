#include "catch.hpp"
#include "slope.h"



TEST_CASE("Slope")
{
    Slope slope{true}; //vänster
    CHECK(slope.context.y_speed == 1);
}

