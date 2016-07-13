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
    player->setPosition(gamescreen->getSize() / 2);
    player->setMapSize(map->getMapSize());

    map->drawTop(gamescreen);
}

void World::doUpdate(const UpdateState &us)
{
    std::cout << "x = " << player->getSize().y << std::endl;
    RectT<Vector2> new_rect_player_x(player->getPosition() + player->getDirectionX(), player->getSize());

    if(map->checkObstacle(new_rect_player_x) == true)
        std::cout << "obstacle X" << std::endl;
    else
        player->moveX();


    RectT<Vector2> new_rect_player_y(player->getPosition() + player->getDirectionY(), player->getSize());

    if(map->checkObstacle(new_rect_player_y) == true)
        std::cout << "obstacle Y" << std::endl;
    else
        player->moveY();
}
