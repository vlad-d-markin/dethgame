#ifndef TILE_H
#define TILE_H
#include "player.h"
#include "Sprite.h"

enum tiletype
{
    BACKGROUND,
    _COLLISION,
    OBJECT
};

class Tile
{
    Sprite *tile;
    int tiletype;
public:
    Tile(Sprite *t, int tt);
    Sprite* getTile();
};

#endif // TILE_H
