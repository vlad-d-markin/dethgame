#ifndef WORLD_H
#define WORLD_H
#include "oxygine-framework.h"
#include "map.h"
#include "player.h"
#include <vector>
#include "entities/mob.h"


using namespace oxygine;

class World : public Actor
{
    Map* map;
    Player* player;
    GameScreen* gamescreen;

    std::vector<Mob *> m_mobs;

public:
    World(GameScreen* gs);
    void draw();

    void corpseDecayed(Event * event);

protected:
    void doUpdate(const UpdateState &us);

};

#endif // WORLD_H
