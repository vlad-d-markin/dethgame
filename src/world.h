#ifndef WORLD_H
#define WORLD_H
#include "oxygine-framework.h"
#include "map.h"
#include "player.h"

using namespace oxygine;

class World : public Actor
{
    Map* map;
    Player* player;
    GameScreen* gamescreen;
public:
    World(GameScreen* gs);
    void draw();
protected:
    void doUpdate(const UpdateState &us);
};

#endif // WORLD_H
