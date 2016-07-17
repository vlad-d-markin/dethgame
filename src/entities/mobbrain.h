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
    int m_active_state;
    float m_agr_range;
    float m_attack_range;

    Vector2 m_pos_player;
    Vector2 m_pos_mob;
    Vector2 m_pos_spawn;

public:
    MobBrain(float agr_range, float attack_range, Vector2 pos_spawn);

    int getState();
    void setState(State state);
    void setPosPlayer(Vector2 pos);
    void setMobPosition(Vector2 pos);

    void stateAttack();
    void stateWait();
    void statePursuit();
    void stateGoBack();

    virtual void doUpdate(const UpdateState& us);

};

#endif // MOBBRAIN_H
