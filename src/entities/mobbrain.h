#ifndef MOBBRAIN_H
#define MOBBRAIN_H

#include "oxygine-framework.h"
#include "entity.h"

using namespace oxygine;

enum State {
    WAIT,
    PURSUIT,
    ATTACK,
    GO_BACK,
};

class MobBrain : public Sprite
{
    int activeState;
    Vector2 posPlayer;

public:
    MobBrain();

    void setState(State state);
    void updateState();

    void stateAttack();
    void stateWait();
    void statePursuit();
    void stateGoBack();

    virtual void doUpdate(const UpdateState& us);

    void setPosPlayer(Vector2 pos);

};

#endif // MOBBRAIN_H
