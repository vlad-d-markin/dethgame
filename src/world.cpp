#include "world.h"
#include "map.h"

#include <iostream>

World::World(GameScreen *gs)
{
    map = new Map();
    gamescreen = gs;
    //player = new Player(gamescreen);
}

void World::draw()
{
    map->drawGround(gamescreen);

    player = new Player(gamescreen);
    player->setAnchor(0.5, 0.5);
    player->attachTo(gamescreen);
    player->setPosition(gamescreen->getSize() / 2);
    player->setMapSize(map->getMapSize());

    map->drawTop(gamescreen);
}

void World::doUpdate(const UpdateState &us)
{
    if( player->getDirection() == Vector2(0,0) )
    {
        player->setMoving(false);
        return;
    }

    int num_steps = 10;
    float step_speed_x = (player->getDirection().x) / num_steps;
    float step_speed_y = (player->getDirection().y) / num_steps;
    bool playerMoved = false;

    for(int i = 0; i < num_steps; i++)
    {
        if(step_speed_x != 0)
        {
            RectT<Vector2> new_rect_player_x(player->getPosition()+Vector2(step_speed_x, 0), player->getSize());
            if(map->checkObstacle(new_rect_player_x) == false) {
                player->moveX(step_speed_x);
                playerMoved = true;
            }
        }

        if(step_speed_y != 0)
        {
            RectT<Vector2> new_rect_player_y(player->getPosition()+Vector2(0, step_speed_y), player->getSize());
            if(map->checkObstacle(new_rect_player_y) == false) {
                player->moveY(step_speed_y);
                playerMoved = true;
            }
        }
    }
    player->setMoving(playerMoved);
}
