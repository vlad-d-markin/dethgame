#ifndef WORLD_H
#define WORLD_H

#include <map>

#include "oxygine-framework.h"
#include "direction.h"

#include "map.h"
#include "player.h"
#include "banana.h"
#include "entities/mob.h"
#include "screens/gamescreen.h"
#include "resetable.h"

using namespace oxygine;


class World : public Actor, public Resetable
{
    GameScreen* gamescreen;
    Clock* m_clock_world;
    Map* m_map;
    Player* m_player;
    std::map<int, spMob> m_mobs;
    std::vector<Banana> m_bananas;
    bool m_pause_mode;
protected:
    void doUpdate(const UpdateState &us);
public:
    World(GameScreen* gs);
    virtual void reBuildWorld();
    void setMapLand();
    void setZombies();
    void setBananas();
    void setPlayer();
    void setMapTop();

    // updating methods
    void checkBanana();
    void checkPlayerMovement();

    // catching events methods
    void corpseDecayed(Event * event);
    void zombieAttacks(Event * event);
    void onPlayerPunch(Event * event);
    void onPause(Event *event);
};

#endif // WORLD_H
