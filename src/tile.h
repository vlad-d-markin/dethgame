#ifndef TILE_H
#define TILE_H
#include "player.h"
#include "Sprite.h"

enum tiletype
{
    BACKGROUND,
    BACKGROUND_OBJECTS,
    COLLISIONS,
    TOP_OBJECTS
};

class Tile
{
    Sprite *tile;
    int tiletype;

public:
    Tile(Sprite *t, int tt);
    Sprite* getTile();
    int getTiletype();
};

#endif // TILE_H
