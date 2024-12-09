
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "catch.hpp"
#include "player.h"
#include "game_object.h"
#include "player.h"
#include "context.h"
#include "snowball_projectile.h"
#include "static_obstacle.h"
#include "temporary_modifier.h"


TEST_CASE("Player perform collision")
{
    Context context {};
    context.player = new Player(40, 50);

    Tire tire (30, 40, 130);

    sf::FloatRect player_bounds{context.player -> bounds()};
    sf::FloatRect obst_bounds{tire.bounds()};
    CHECK(player_bounds.intersects(obst_bounds));
}

