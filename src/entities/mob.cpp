#include "mob.h"
#include "../player.h"
#include <iostream>

#define distance(x1, y1, x2, y2) sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))

Mob::Mob()
{
    setState(IDLE);
    m_decayed = false;
    m_dead_time = 0;
    m_hit_freq = 1500;
    m_last_hit_time = 0;
}



Mob::~Mob() { log::messageln("Mob was deleted"); }



void Mob::doUpdate(const UpdateState &us)
{
    Entity::doUpdate(us);

    brain->setMobPosition(getPosition());

    brain->doUpdate(us);
    switch (brain->getState()) {
    case WAIT:

        break;
    case PURSUIT:
        walkTo(m_pos_player);
        break;
    case ATTACK:
        attack(us);
        break;
    case GO_BACK:
        walkTo(m_pos_spawn);
        break;
    default:
        break;
    }

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



void Mob::attack(const UpdateState &us)
{
    if(m_last_hit_time < m_hit_freq)
        m_last_hit_time += us.dt;
    else
    {
        m_last_hit_time=0;

        float x=distance(m_pos_player.x, m_pos_player.y, m_pos_player.x, getPosition().y);
        float y=distance(getPosition().x, getPosition().y, m_pos_player.x, m_pos_player.y);
        float sin=x/y;

        if (((getPosition().x < m_pos_player.x))&&(getPosition().y > m_pos_player.y))
        {
            if(fabs(sin)<(sqrt(2)/2))
            {
                punch(right);
                return;
            }
            else
            {
                punch(up);
                return;
            }
        }

        if (((getPosition().x < m_pos_player.x))&&(getPosition().y < m_pos_player.y))
        {
            if(fabs(sin)<(sqrt(2)/2))
            {
                punch(right);
                return;
            }
            else
            {
                punch(down);
                return;
            }
        }

        if (((getPosition().x > m_pos_player.x))&&(getPosition().y < m_pos_player.y))
        {
            if(fabs(sin)<(sqrt(2)/2))
            {
                punch(left);
                return;
            }
            else
            {
                punch(down);
                return;
            }
        }

        if (((getPosition().x > m_pos_player.x))&&(getPosition().y > m_pos_player.y))
        {
            if(fabs(sin)<(sqrt(2)/2))
            {
                punch(left);
                return;
            }
            else
            {
                punch(up);
                return;
            }
        }

    }
}



void Mob::getHit(int damage)
{
    if(m_state == DEAD)
        return;

    m_health -= damage;
    std::cout << "Mob got damage " << damage << " (" << m_health << ")" << std::endl;

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

RectT<Vector2> Mob::getMobBox()
{
    mob_box.setPosition(getPosition());
    return mob_box;
}


void Mob::setPosPlayer(Vector2 pos)
{
    m_pos_player=pos;
    brain->setPosPlayer(pos);
}
