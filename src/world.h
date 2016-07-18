#ifndef WORLD_H
#define WORLD_H
#include "oxygine-framework.h"
#include "map.h"
#include "player.h"
#include "banana.h"
#include <set>
#include "entities/mob.h"
#include "direction.h"
#include "entities/pathfinding.h"


using namespace oxygine;

class World : public Actor
{
    Map* map;
    Player* player;
    GameScreen* gamescreen;

    std::set<spMob> m_mobs;
    float dt_zombie;

    std::vector<Banana> m_bananas;

    pathFinding *pathFinder;

public:
    World(GameScreen* gs);
    void draw();

    void addMob(spMob mob);
    void corpseDecayed(Event * event);
    void checkBanana();

protected:
    void doUpdate(const UpdateState &us);
    void zombieAttacks(Event * event);

    void onPlayerPunch(Event * event);


};

#endif // WORLD_H
