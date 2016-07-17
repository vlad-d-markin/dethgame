#include "entity.h"

#include <iostream>

Entity::Entity() {

}


void Entity::doUpdate(const UpdateState &us)
{
    m_collision_box.setPosition(getPosition());
    m_collision_box.setSize(getSize());
}

RectT<Vector2> Entity::getCollisionBox()
{
    return m_collision_box;
}
