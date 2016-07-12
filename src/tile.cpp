#include "tile.h"

Tile::Tile(Sprite *t, int tt)
{
    tile=t;
    tiletype=tt;
}

Sprite* Tile::getTile()
{
    return tile;
}

