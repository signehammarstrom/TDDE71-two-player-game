
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

using namespace std;

TEST_CASE("Player perform collision")
{
    Context context {};
    context.y_speed = 40;
    
    context.player = new Player(40, 50, 40);
    Game_Object* tire = new Tire(20, 30, 40);

    sf::FloatRect player_bounds{context.player -> bounds()};
    sf::FloatRect obst_bounds{tire -> bounds()};
    cout << "obstheight : " << obst_bounds.height << " obstwidth: " << obst_bounds.width << '\n'
        << "oplayerheight : " << player_bounds.height << " playerwidth: " << player_bounds.width << endl;

      cout << "obsttop : " << obst_bounds.top << " obstleft: " << obst_bounds.left << '\n'
        << "oplayerleft : " << player_bounds.top << " playerleft: " << player_bounds.left << endl;

    CHECK(player_bounds.intersects(obst_bounds));

    context.player -> perform_collision(tire, context);
    tire -> perform_collision(context.player, context);
    CHECK(context.y_speed == 0);

}

