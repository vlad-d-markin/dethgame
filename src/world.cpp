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
    RectT<Vector2> new_rect_player(player->getPosition(),player->getSize());

    // works incorrectly!
    if(map->checkObstacle(new_rect_player) == true)
        std::cout << "obstacle" << std::endl;

}
