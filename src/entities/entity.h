#ifndef DETHGAME_ENTITY_H
#define DETHGAME_ENTITY_H

#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(Entity, spEntiy)
class Entity : public Sprite
{
private:
    RectT<Vector2> m_collision_box;
    // m_sprite
public:
    Entity();
    virtual RectT<Vector2> getCollisionBox();
protected:
    virtual void doUpdate(const UpdateState& us);
};


#endif //DETHGAME_ENTITY_H
