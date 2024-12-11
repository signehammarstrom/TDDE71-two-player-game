
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

TEST_CASE("Player perform collision static object")
{
    //Perform collision är implementerad något speciellt
    //eftersom player kommer ovanifrån. för de statiska objekten, ska endast y-hastighet stoppas
    //då spelaren kommer ovanifrån.
    
    Context context {};
    context.y_speed = 40;
    
    context.player = new Player(10, 10, 40);
    Game_Object* tire = new Tire(0, 25, 40);
    Game_Object* hole2 = new Hole(10,25,100);

    sf::FloatRect player_bounds{context.player -> bounds()};
    sf::FloatRect obst_bounds{tire -> bounds()};
    sf::FloatRect holebounds{hole2 -> bounds()};

    CHECK(player_bounds.intersects(holebounds));
    CHECK_FALSE(player_bounds.top + player_bounds.height <= holebounds.top + 5 );
    context.player -> perform_collision(hole2, context);
    hole2 -> perform_collision(context.player, context);
    CHECK(context.y_speed == 40);

    CHECK(player_bounds.intersects(obst_bounds));
    CHECK(player_bounds.top + player_bounds.height <= obst_bounds.top + 5 );
    context.player -> perform_collision(tire, context);
    tire -> perform_collision(context.player, context);
    CHECK(context.y_speed == 0);
    CHECK(context.is_colliding);
    CHECK(context.coll_count ==1);

    cout << player_bounds.top << ' ' << player_bounds.left << endl;
    cout << context.player->bounds().top << ' ' << context.player->bounds().left << endl;

}

TEST_CASE("Player perform collision goal")
{
    //Perform collision är implementerad något speciellt
    //eftersom player kommer ovanifrån. för de statiska objekten, ska endast y-hastighet stoppas
    //då spelaren kommer ovanifrån.
    
    Context context {};
    context.y_speed = 40;
    
    context.player = new Player(10, 10, 40);
    Game_Object* goal = new Goal(10, 25, 100);

    sf::FloatRect player_bounds{context.player -> bounds()};
    sf::FloatRect goalbounds{goal-> bounds()};

    CHECK(player_bounds.intersects(goalbounds));
    CHECK_FALSE(player_bounds.top + player_bounds.height <= goalbounds.top + 5 );
    context.player -> perform_collision(goal, context);
    goal-> perform_collision(context.player, context);
    CHECK(context.y_speed == 0);
    CHECK(context.game_finished == true);

    cout << player_bounds.top << ' ' << player_bounds.left << endl;
    cout << context.player->bounds().top << ' ' << context.player->bounds().left << endl;

}

TEST_CASE("Player perform collision moving object")
{
    
    Context context {};
    context.y_speed = 40;
    
    context.player = new Player(10, 10, 40);
    Game_Object* kir = new Kir(0, 25, 40, 30);
    Game_Object* can = new Can(10,25,100, 20);
    Game_Object* chalmerist = new Chalmerist(10,25,100, 20);

    sf::FloatRect player_bounds{context.player -> bounds()};
    sf::FloatRect kirbounds{kir -> bounds()};
    sf::FloatRect canbounds{can -> bounds()};
    sf::FloatRect chalbounds{chalmerist -> bounds()};

    CHECK(player_bounds.intersects(kirbounds));
    context.player -> perform_collision(kir, context);
    kir -> perform_collision(context.player, context);
    CHECK(context.y_speed == 80);
    CHECK(context.active_temp_mods.size() == 1);
    CHECK(context.active_temp_mods.at(0) == kir);


    CHECK(player_bounds.intersects(canbounds));
    context.player -> perform_collision(can, context);
    can -> perform_collision(context.player, context);
    CHECK(context.y_speed == 80*0.8);
    CHECK(context.active_temp_mods.size() == 2);
    CHECK(context.active_temp_mods.at(1) == can);
     // I spelet tas aktiva temp-mods bort av slope. 

    CHECK(player_bounds.intersects(chalbounds));
    context.player -> perform_collision(chalmerist, context);
    chalmerist -> perform_collision(context.player, context);
    CHECK(context.y_speed == 80*0.8*0.5);
    CHECK(context.active_temp_mods.size() == 3);
    CHECK(context.active_temp_mods.at(2) == chalmerist);
}


