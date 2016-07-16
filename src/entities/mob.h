#ifndef DETHGAME_MOB_H
#define DETHGAME_MOB_H

#include "oxygine-framework.h"
#include "entity.h"
#include "mobbrain.h"


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


class Mob : public Entity {

   // MobBrain brain;

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
    int m_health;
    int m_attack_damage;
    RectT<Vector2> m_attack_area;
    State m_state;
    bool m_decayed;

    float m_agr_range;
    float m_attack_range;

    float m_dead_time;

    bool m_state_changed;

    RectT<Vector2> mob_box;
    Vector2 m_pos_spawn;

    MobBrain * brain;

public:
    Mob();
    virtual ~Mob();

    void getHit(int damage);  
    void die();
    void walkTo(Vector2 dest);
    RectT<Vector2> getMobBox();

    void setState(State s);

    bool isDecayed();

    void attack(/*Entity (Character) * target*/);

    void setPosPlayer(Vector2 pos);

protected:
    virtual void doUpdate(const UpdateState& us);

    virtual void onDie() {}

};


#endif //DETHGAME_MOB_H
