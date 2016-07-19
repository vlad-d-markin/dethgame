#ifndef BANANA_H
#define BANANA_H
#include "core/oxygine.h"
#include "Sprite.h"
#include <iostream>
#include "screens/gamescreen.h"

using namespace oxygine;

class Banana
{
    Resources * banana_resources;
    bool is_found;
    RectT<Vector2> collision_box;
    spSprite banana;

public:
    Banana(Vector2 pos, GameScreen *gs);
    RectT<Vector2> getCollisionBox();
    bool isFound();
    void found();
    void deleteBanana();
};

#endif
