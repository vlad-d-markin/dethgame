#include "mobbrain.h"
#include "../player.h"

#include <iostream>

#define distance(x1, y1, x2, y2) sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))


MobBrain::MobBrain(float agr_range, float attack_range, Vector2 pos_spawn)
{
    m_agr_range = agr_range;
    m_attack_range = attack_range;
    m_pos_spawn = pos_spawn;

    m_active_state = WAIT;
}


void MobBrain::setState(State state)
{
    m_active_state = state;
}


void MobBrain::stateWait()
{
    if(distance(m_pos_mob.x, m_pos_mob.y, m_pos_player.x, m_pos_player.y) < m_agr_range)
        setState(PURSUIT);
}


void MobBrain::stateAttack()
{
    if( distance(m_pos_mob.x, m_pos_mob.y, m_pos_player.x, m_pos_player.y)  > m_attack_range)
        setState(PURSUIT);
}


void MobBrain::statePursuit()
{
    if( distance(m_pos_mob.x, m_pos_mob.y, m_pos_player.x, m_pos_player.y)  > m_agr_range)
        setState(GO_BACK);

    if( distance(m_pos_mob.x, m_pos_mob.y, m_pos_player.x, m_pos_player.y) < m_attack_range)
        setState(ATTACK);
}


void MobBrain::stateGoBack()
{
    if( distance(m_pos_mob.x, m_pos_mob.y, m_pos_player.x, m_pos_player.y) < m_agr_range)
        setState(PURSUIT);

    if ( distance(m_pos_mob.x, m_pos_mob.y, m_pos_spawn.x, m_pos_spawn.x) < 20 ) //  TODO
         setState(WAIT);
}


void MobBrain::doUpdate(const UpdateState& us)
{
    switch(m_active_state)
    {
    case WAIT:
        stateWait();
        break;
    case PURSUIT:
        statePursuit();
        break;
    case ATTACK:
        stateAttack();
        break;
    case GO_BACK:
        stateGoBack();
        break;
    default:
        break;
    }
}


void MobBrain::setPosPlayer(Vector2 pos)
{
    m_pos_player = pos;
}


void MobBrain::setMobPosition(Vector2 pos)
{
    m_pos_mob = pos;
}

int MobBrain::getState()
{
    return m_active_state;
}
