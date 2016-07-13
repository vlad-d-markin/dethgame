#include "mob.h"

Mob::Mob()
{
    m_state = IDLE;
}



Mob::~Mob() {}



void Mob::doUpdate(const UpdateState &us)
{
    Entity::doUpdate(us);
}



void Mob::attack(/* target */)
{
    // walkTo(target)
    // if near then
    //      target->getHit(m_damage);
    //      log::messageln("Mob attacks %s", target->getName);
}



void Mob::getHit(int damage)
{
    log::messageln("Mob got damage %d (%d)", damage, m_health);
    m_health -= damage;

    if(m_health <= 0)
    {
        die();
    }
}



void Mob::walkTo(Vector2 dest)
{
    // Build path
    // and walk
    // log::messageln("Mob walks to %d,%d", dest.x, dest.y);
}



void Mob::die()
{
    m_health = 0;
    m_state = DEAD;
    log::messageln("Mob is dead");
}


bool Mob::isDecayed()
{
    return m_decayed;
}

