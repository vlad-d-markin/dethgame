#ifndef DETHGAME_MOB_H
#define DETHGAME_MOB_H

#include "oxygine-framework.h"
#include "entity.h"


DECLARE_SMART(Mob, spMob)
class Mob : public Entity {
public:
    enum State {
        IDLE,
        WALKING_NORTH,
        WALKING_SOUTH,
        WALKING_WEST,
        WALKING_EAST,
        DEAD
    };

    /*
    enum Effects {
        STUN = 1,
        BLEEDING = 1 << 1,
        REGENERATING = 1 << 2
    };
     */

private:
    int m_health;
    int m_attack_damage;
    RectT<Vector2> m_attack_area;
    State m_state;
    bool m_decayed;

public:
    Mob();
    virtual ~Mob();

    void getHit(int damage);
    void attack(/*Entity (Character) * target*/);
    void die();
    void walkTo(Vector2 dest);

    bool isDecayed();


protected:
    virtual void doUpdate(const UpdateState& us);

};


#endif //DETHGAME_MOB_H
