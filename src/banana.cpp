#include "banana.h"
#include "dethgame.h"

Banana::Banana(Vector2 pos, GameScreen *gs)
{
    is_found = false;
    banana_resources = new Resources();
    banana_resources->loadXML(DethGame::instance()->getBananaResPath());
    banana = new Sprite;
    banana->setResAnim(banana_resources->getResAnim("banana"));
    banana->setPosition(pos);
    banana->attachTo(gs);

    collision_box.setSize(banana->getSize());
    collision_box.setPosition(pos);
}

RectT<Vector2> Banana::getCollisionBox()
{
    return collision_box;
}

bool Banana::isFound()
{
    return is_found;
}

void Banana::found()
{
    is_found = true;
}

void Banana::deleteBanana()
{
    banana->detach();
}
