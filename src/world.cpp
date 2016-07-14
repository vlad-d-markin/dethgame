#include "world.h"
#include "map.h"

#include <iostream>

World::World(GameScreen *gs)
{
    map = new Map();
    player = new Player();
    gamescreen = gs;
}

void World::draw()
{
    map->drawGround(gamescreen);

    player = new Player;
    player->setAnchor(0.5, 0.5);
    //sprite->setResAnim(gamescreen->getResources()->getResAnim("skin"));
    player->attachTo(gamescreen);
   // player->setPosition(gamescreen->getSize() / 2);
    player->setPosition(Vector2(50,50));
    player->setMapSize(map->getMapSize());

    map->drawTop(gamescreen);
}

void World::doUpdate(const UpdateState &us)
{
    if( player->getDirection() == Vector2(0,0) )
        return;

    int num_steps = 10;
    float step_speed_x = (player->getDirection().x) / num_steps;
    float step_speed_y = (player->getDirection().y) / num_steps;

    for(int i = 0; i < num_steps; i++)
    {
        // horizontal motion
        RectT<Vector2> new_rect_player_x(player->getPosition()+Vector2(step_speed_x,0), player->getSize());
        if(map->isObstacle(new_rect_player_x) == false) {
            player->setDirection(step_speed_x, 0);
            player->moveX();
        }

        // vertical motion
        RectT<Vector2> new_rect_player_y(player->getPosition()+Vector2(0, step_speed_y), player->getSize());
        if(map->isObstacle(new_rect_player_y) == false) {
            player->setDirection(0, step_speed_y);
            player->moveY();
        }

    }

}
