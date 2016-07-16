#include "mobbrain.h"
#include "../player.h"

#include <iostream>

MobBrain::MobBrain()
{
    activeState = WAIT;
}


void MobBrain::setState(State state)
{
    activeState = state;
}


void MobBrain::updateState()
{

}


void MobBrain::stateWait()
{

}


void MobBrain::stateAttack()
{

}


void MobBrain::statePursuit()
{

}


void MobBrain::stateGoBack()
{

}


void MobBrain::doUpdate(const UpdateState& us)
{

}


void MobBrain::setPosPlayer(Vector2 pos)
{
    posPlayer = pos;
}
