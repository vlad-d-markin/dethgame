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
    RectT<Vector2> new_rect_player_y(player->getPosition() + player->getDirectionY(), player->getSize());

    if(map->checkObstacle(new_rect_player_x) == false)
        player->moveX();
    else
        std::cout << "obstacle X" << std::endl;

    if(map->checkObstacle(new_rect_player_y) == false)
        player->moveY();
    else
        std::cout << "obstacle Y" << std::endl;
}
