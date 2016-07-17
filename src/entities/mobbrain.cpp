#include "mobbrain.h"
#include "../player.h"

#include <iostream>

#define distance(x1, y1, x2, y2) sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1))


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


void MobBrain::updateState()
{

}


void MobBrain::stateWait()
{
    if(distance(m_pos_mob.x, m_pos_mob.y, m_pos_player.x, m_pos_player.y) < m_agr_range)
        setState(PURSUIT);
}


void MobBrain::stateAttack()
{
    std::cout << distance(m_pos_mob.x, m_pos_mob.y, m_pos_player.x, m_pos_player.y) << "  and  " << m_agr_range << std::endl;

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
    if( distance(m_pos_mob.x, m_pos_mob.y, m_pos_player.x, m_pos_player.y)< m_agr_range)
        setState(PURSUIT);

    if ( distance(m_pos_mob.x, m_pos_mob.y, m_pos_spawn.x, m_pos_spawn.x) < 20 ) //  TODO
         setState(WAIT);
}


void MobBrain::doUpdate(const UpdateState& us)
{
    switch(m_active_state)
    {
    case WAIT:
        //std::cout << "WAIT" << std::endl;
        stateWait();
        break;
    case PURSUIT:
        //std::cout << "PURSUIT" << std::endl;
        statePursuit();
        break;
    case ATTACK:
        //std::cout << "ATTACK" << std::endl;
        stateAttack();
        break;
    case GO_BACK:
        //std::cout << "GO BACK" << std::endl;
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
