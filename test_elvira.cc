#include "catch.hpp"
#include "player.h"
#include "game_object.h"
#include "modifier.h"
#include "moving_object.h"
#include "temporary_modifier.h"

TEST_CASE("player")
{
    Player P1{31, 43, 5, 4};
    CHECK(P1.get_xpos()==31);
    CHECK(P1.get_ypos()==43);
    CHECK(P1.get_width()==4);
    CHECK(P1.get_height()==5);
    
}

TEST_CASE("Modifier")
{
    Modifier m1{31, 43};
    CHECK(m1.get_xpos()==31);
    CHECK(m1.get_ypos()==43);
}

TEST_CASE("moving_object")
{
    Moving_Object m2{31, 43, 5.3};
    CHECK(m2.get_xpos()==31);
    CHECK(m2.get_ypos()==43);
    CHECK(m2.get_xspeed()== 5.3);
}

TEST_CASE("Snowball_Mod")
{
    Snowball_Mod S1{31, 43, 5.3, 4};
    CHECK(S1.get_xpos()==31);
    CHECK(S1.get_ypos()==43);
    CHECK(S1.get_xspeed()== 5.3);
    CHECK(S1.get_radius()== 4);
}

TEST_CASE("Temporary Modifier")
{
    Temporary_Modifier S1{31, 43, 5.3, 4, 7, 8};
    CHECK(S1.get_xpos()==31);
    CHECK(S1.get_ypos()==43);
    CHECK(S1.get_xspeed()== 5.3);
    CHECK(S1.get_width()== 4);
    CHECK(S1.get_height()== 7);
    CHECK(S1.get_speedmodifier()== 8);
}

TEST_CASE("Kir, can, chalmerist")
{
    Kir S1{31, 43, 5.3, 4, 7, 8};
    CHECK(S1.get_xpos()==31);
    CHECK(S1.get_ypos()==43);
    CHECK(S1.get_xspeed()== 5.3);
    CHECK(S1.get_width()== 4);
    CHECK(S1.get_height()== 7);
    CHECK(S1.get_speedmodifier()== 8);

    Can S2{31, 43, 5.3, 4, 7, 8};
    CHECK(S2.get_xpos()==31);
    CHECK(S2.get_ypos()==43);
    CHECK(S2.get_xspeed()== 5.3);
    CHECK(S2.get_width()== 4);
    CHECK(S2.get_height()== 7);
    CHECK(S2.get_speedmodifier()== 8);

    Chalmerist S3{31, 43, 5.3, 4, 7, 8};
    CHECK(S3.get_xpos()==31);
    CHECK(S3.get_ypos()==43);
    CHECK(S3.get_xspeed()== 5.3);
    CHECK(S3.get_width()== 4);
    CHECK(S3.get_height()== 7);
    CHECK(S3.get_speedmodifier()== 8);

}
