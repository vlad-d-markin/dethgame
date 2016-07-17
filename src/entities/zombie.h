#ifndef DETHGAME_ZOMBIE_H
#define DETHGAME_ZOMBIE_H

#include "mob.h"
#include "oxygine-framework.h"
#include "../direction.h"

using namespace oxygine;

DECLARE_SMART(Zombie, spZombie)
class Zombie : public Mob
{
public:
    enum {
        HP = 100,
        DAMAGE = 10
    };

private:

    Resources resources;

    ResAnim * m_walk_north_anim;
    ResAnim * m_walk_south_anim;
    ResAnim * m_walk_east_anim;
    ResAnim * m_walk_west_anim;

    ResAnim * m_attack_south;
    ResAnim * m_attack_east;
    ResAnim * m_attack_west;
    ResAnim * m_attack_north;

    ResAnim * m_die_anim;
    ResAnim * m_idle_anim;

    spTween m_current_tween;
    spTween m_currentMoveTween;


public:
    Zombie(Vector2 spawn_pos);
    virtual ~Zombie();

    void punch(Direction dir);
    virtual void walk(Direction dir);

protected:
    virtual void doUpdate(UpdateState& us);

    virtual void onDie();

    void onPunchFinished(Event * e);
    void onWalkComplete(Event * e);


};

class ZombiePunchEvent : public Event
{
public:
    enum { EVENT = eventID('Z', 'p', 'H', 'R') };
    RectT<Vector2> attack_area;
    int damage;

    ZombiePunchEvent(RectT<Vector2> area, int dmg) : Event(EVENT), attack_area(area), damage(dmg) {}
};


class ZombieArrived : public Event
{
public:
    enum { EVENT = eventID('Z', 'a', 'T', 't') };
    Vector2 destination;

    ZombieArrived(Vector2 dest) : Event(EVENT), destination(dest) {}
};


#endif //DETHGAME_ZOMBIE_H
