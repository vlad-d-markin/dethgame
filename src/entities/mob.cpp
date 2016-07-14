#include "mob.h"

Mob::Mob()
{
    setState(IDLE);
    m_decayed = false;
    m_dead_time = 0;
}



Mob::~Mob() { log::messageln("Mob was deleted"); }



void Mob::doUpdate(const UpdateState &us)
{
    Entity::doUpdate(us);

    switch (m_state){
        case DEAD:
            if(m_decayed)
                break;

            m_dead_time += us.dt;
            if(m_dead_time >= 5000){
                log::messageln("Mob is decayed");
                m_decayed = true;
                MobCorpseDecayedEvent decayedEvent(this);
                dispatchEvent(&decayedEvent);
            }
            break;

        case IDLE:
            // Switch idle animation
            break;
    }
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
    if(m_state == DEAD)
        return;
    
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


void Mob::setState(State s) {
    m_state = s;
    m_state_changed = true;
}


void Mob::die()
{
    m_health = 0;
    m_state = DEAD;
    log::messageln("Mob is dead");
    onDie();
}


bool Mob::isDecayed()
{
    return m_decayed;
}

