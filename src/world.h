#ifndef WORLD_H
#define WORLD_H
#include "oxygine-framework.h"
#include "map.h"
#include "player.h"
#include "banana.h"
#include <map>
#include "entities/mob.h"
#include "direction.h"
#include "screens/gamescreen.h"
#include "resetable.h"

using namespace oxygine;
class World : public Actor,public Resetable
{
    Map* map;
    Player* player;
    GameScreen* gamescreen;

    std::map<int, spMob> m_mobs;
    float dt_zombie;

    std::vector<Banana> m_bananas;

public:
    World(GameScreen* gs);
    void draw();
    virtual void reset();

    void addMob(spMob mob);
    void corpseDecayed(Event * event);
    void checkBanana();

protected:
    void doUpdate(const UpdateState &us);
    void zombieAttacks(Event * event);

    void onPlayerPunch(Event * event);


};

#endif // WORLD_H
