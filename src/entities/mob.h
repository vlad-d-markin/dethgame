#ifndef DETHGAME_MOB_H
#define DETHGAME_MOB_H

#include "oxygine-framework.h"
#include "entity.h"
#include "mobbrain.h"
#include "../direction.h"

using namespace oxygine;

class Mob;
DECLARE_SMART(Mob, spMob)

class MobCorpseDecayedEvent : public Event
{

public:
    spMob mob;

    enum { EVENT = eventID('m', 'C', 'd', 'Y') };
    MobCorpseDecayedEvent(spMob m) : Event(EVENT), mob(m) {}
};


class Mob : public Entity
{

public:
    enum State {
        IDLE,
        WALKING_NORTH,
        WALKING_SOUTH,
        WALKING_WEST,
        WALKING_EAST,
        DEAD,

        PUNCHING_SOUTH,
        PUNCHING_EAST,
        PUNCHING_WEST,
        PUNCHING_NORTH
    };

    /*
    enum Effects {
        STUN = 1,
        BLEEDING = 1 << 1,
        REGENERATING = 1 << 2
    };
     */

protected:
    MobBrain * brain;

    Vector2 m_pos_spawn;
    Vector2 m_pos_player;

    int m_health;
    int m_attack_damage;
    float m_last_hit_time;
    float m_hit_freq;

    float m_agr_range;
    float m_attack_range;
    float m_dead_time;

    State m_state;
    bool m_decayed;
    bool m_state_changed;

    RectT<Vector2> m_attack_area;
    RectT<Vector2> mob_box;


public:
    Mob();
    virtual ~Mob();

    void setState(State s);
    void setPosPlayer(Vector2 pos);

    RectT<Vector2> getMobBox();

    void getHit(int damage);  
    void walkTo(Vector2 dest);
    void attack(const UpdateState &us);

    void die();
    bool isDecayed();

    virtual void punch(Direction dir)=0;
protected:
    virtual void doUpdate(const UpdateState& us);
    virtual void onDie() {}

};


#endif //DETHGAME_MOB_H
