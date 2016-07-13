#include "entity.h"

Entity::Entity() {

}


void Entity::doUpdate(const UpdateState &us)
{
    m_collision_box.setPosition(getPosition());
    m_collision_box.setSize(getSize());
}