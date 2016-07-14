#ifndef DETHGAME_ZOMBIE_H
#define DETHGAME_ZOMBIE_H

#include "mob.h"
#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(Zombie, spZombie)
class Zombie : public Mob
{
public:
    enum Direction {
        NORTH,
        SOUTH,
        EAST,
        WEST
    };

private:
    Resources resources;

    ResAnim * m_walk_north_anim;
    ResAnim * m_walk_south_anim;
    ResAnim * m_walk_east_anim;
    ResAnim * m_walk_west_anim;

    ResAnim * m_attack_south;

    ResAnim * m_die_anim;
    ResAnim * m_idle_anim;

    spTween m_current_tween;


public:
    Zombie();
    virtual ~Zombie();

    void punch(Direction dir);

protected:
    virtual void doUpdate(UpdateState& us);

    virtual void onDie();

    void onPunchFinished(Event * e);


};


#endif //DETHGAME_ZOMBIE_H
