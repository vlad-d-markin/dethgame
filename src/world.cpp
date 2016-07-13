#include "world.h"
#include "map.h"
#include "entities/testmob.h"

#include <iostream>

World::World(GameScreen *gs)
{
    map = new Map();
    player = new Player();
    gamescreen = gs;

    spTestMob kaban = new TestMob();
    kaban->setPosition(100, 100);
    m_mobs.push_back(kaban);
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

    // TODO: No to do like this again
    m_mobs[0]->attachTo(this);

    map->drawTop(gamescreen);

    // TODO: Somebody remove it, pls
    m_mobs[0]->getHit(100);
}

void World::doUpdate(const UpdateState &us)
{
    // Remove decayed corpses
    for(auto it = m_mobs.begin(); it != m_mobs.end(); it++)
    {
        spMob mob = *it;
        if(mob->isDecayed())
        {
//            m_mobs.erase(it);
//            it++;
//
//            this->removeChild(mob);
        }
    }



    if( player->getDirection() == Vector2(0,0) )
        return;

    int num_steps = 10;
    float step_speed_x = (player->getDirection().x) / num_steps;
    float step_speed_y = (player->getDirection().y) / num_steps;

    for(int i = 0; i < num_steps; i++) {

        RectT<Vector2> new_rect_player_x(player->getPosition()+Vector2(step_speed_x,0), player->getSize());
        if(map->checkObstacle(new_rect_player_x) == false) {
            player->setDirection(step_speed_x, 0);
            player->moveX();
        }

        RectT<Vector2> new_rect_player_y(player->getPosition()+Vector2(0, step_speed_y), player->getSize());
        if(map->checkObstacle(new_rect_player_y) == false) {
            player->setDirection(0, step_speed_y);
            player->moveY();
        }

    }

}
