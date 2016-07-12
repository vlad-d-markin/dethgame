#ifndef TILE_H
#define TILE_H
#include "mySprite.h"
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
